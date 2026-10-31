/*
 * Write a carrier set of modem EFS files over /dev/diag.
 *
 * The modem only takes its IMS settings from carrier MBNs it can authenticate,
 * and the Korean carrier MBNs do not load on this modem. The settings they
 * would provide are written to EFS directly instead, the same way QPST does.
 *
 * A set file has one entry per line:
 *   w <efs path> <hex data>   the file must exist with exactly this content
 *   d <efs path>              the file must not exist
 *
 * usage: ef71_modemcfg check <set>          exit 0 if the modem matches, 1 if not
 *        ef71_modemcfg apply <set>          write the set, exit 0 when verified
 *        ef71_modemcfg save <out> <set>...  record the current state of the
 *                                           paths in the sets as a set file
 *        ef71_modemcfg version              print the modem build ID
 */

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <android/log.h>

#define TAG "ef71-modemcfg"
#define LOG(...) do { \
        __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__); \
        fprintf(stderr, __VA_ARGS__); fputc('\n', stderr); } while (0)

/* include/linux/diagchar.h */
#define USER_SPACE_DATA_TYPE 0x20
#define MEMORY_DEVICE_MODE 2
#define DIAG_IOCTL_SWITCH_LOGGING 7
#define DIAG_CON_APSS 0x1
#define DIAG_CON_MPSS 0x2

struct diag_logging_mode_param_t {
    uint32_t req_mode;
    uint32_t peripheral_mask;
    uint8_t mode_param;
} __attribute__((packed));

/* EFS2 over DIAG subsystem dispatch */
#define DIAG_SUBSYS_CMD_F 0x4b
#define DIAG_SUBSYS_FS 19
#define EFS2_DIAG_OPEN 2
#define EFS2_DIAG_CLOSE 3
#define EFS2_DIAG_READ 4
#define EFS2_DIAG_WRITE 5
#define EFS2_DIAG_UNLINK 8
#define EFS2_DIAG_MKDIR 9
#define EFS2_DIAG_STAT 15
#define EFS2_DIAG_GET 39
#define EFS2_DIAG_SYNC_NO_WAIT 48
#define EFS2_DIAG_SYNC_GET_STATUS 49

#define EFS_ENOENT 2
#define EFS_O_RDONLY 0
#define EFS_O_WRONLY 01
#define EFS_O_CREAT 0100
#define EFS_O_TRUNC 01000
#define CHUNK 512
#define MAX_FILE 65536
#define MAX_PKT 2048

static int diag_fd = -1;
static uint8_t rx[65536 + 16];
static uint8_t frame[MAX_PKT * 2];
static size_t frame_len;
static uint8_t rsp[MAX_PKT * 2];

static void on_alarm(int sig) { (void)sig; }

static uint16_t crc16(const uint8_t *p, size_t n)
{
    uint16_t crc = 0xffff;
    while (n--) {
        crc ^= *p++;
        for (int i = 0; i < 8; i++)
            crc = (crc & 1) ? (crc >> 1) ^ 0x8408 : crc >> 1;
    }
    return ~crc;
}

static int diag_open(void)
{
    struct diag_logging_mode_param_t mode = {
        .req_mode = MEMORY_DEVICE_MODE,
        .peripheral_mask = DIAG_CON_APSS | DIAG_CON_MPSS,
        .mode_param = 0,
    };
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = on_alarm;   /* no SA_RESTART: a blocked read returns EINTR */
    sigaction(SIGALRM, &sa, NULL);

    diag_fd = open("/dev/diag", O_RDWR | O_CLOEXEC);
    if (diag_fd < 0) {
        LOG("open /dev/diag: %s", strerror(errno));
        return -1;
    }
    /* The responses come back to us instead of USB until the fd is closed */
    if (ioctl(diag_fd, DIAG_IOCTL_SWITCH_LOGGING, &mode) < 0) {
        LOG("switch to memory device mode: %s", strerror(errno));
        close(diag_fd);
        diag_fd = -1;
        return -1;
    }
    return 0;
}

/* Returns the length of a decoded response that starts with match, or -1 */
static int frame_take(const uint8_t *match, size_t match_len)
{
    size_t n = 0;
    int esc = 0;

    for (size_t i = 0; i < frame_len && n < sizeof(rsp); i++) {
        if (esc) {
            rsp[n++] = frame[i] ^ 0x20;
            esc = 0;
        } else if (frame[i] == 0x7d) {
            esc = 1;
        } else {
            rsp[n++] = frame[i];
        }
    }
    frame_len = 0;
    if (n < match_len + 2 || crc16(rsp, n - 2) != (rsp[n - 2] | rsp[n - 1] << 8))
        return -1;
    if (memcmp(rsp, match, match_len))
        return -1;
    return n - 2;
}

static int diag_cmd(const uint8_t *req, size_t len)
{
    uint8_t tx[4 + MAX_PKT * 2 + 4];
    size_t n = 0;
    uint16_t crc = crc16(req, len);
    uint32_t type = USER_SPACE_DATA_TYPE;

    memcpy(tx, &type, 4);
    n = 4;
    for (size_t i = 0; i < len + 2; i++) {
        uint8_t b = i < len ? req[i] : (i == len ? crc & 0xff : crc >> 8);
        if (b == 0x7e || b == 0x7d) {
            tx[n++] = 0x7d;
            tx[n++] = b ^ 0x20;
        } else {
            tx[n++] = b;
        }
    }
    tx[n++] = 0x7e;
    frame_len = 0;
    /* The driver returns 0 rather than the length on success */
    if (write(diag_fd, tx, n) < 0) {
        LOG("diag write: %s", strerror(errno));
        return -1;
    }

    for (int tries = 0; tries < 50; tries++) {
        alarm(3);
        ssize_t r = read(diag_fd, rx, sizeof(rx));
        alarm(0);
        if (r < 0) {
            if (errno == EINTR)
                break;
            LOG("diag read: %s", strerror(errno));
            return -1;
        }
        if (r < 8 || *(uint32_t *)rx != USER_SPACE_DATA_TYPE)
            continue;
        int num = *(int32_t *)(rx + 4);
        size_t off = 8;
        for (int k = 0; k < num && off + 4 <= (size_t)r; k++) {
            int32_t blen = *(int32_t *)(rx + off);
            off += 4;
            if (blen < 0 || off + blen > (size_t)r)
                break;
            for (int32_t i = 0; i < blen; i++) {
                uint8_t b = rx[off + i];
                if (b != 0x7e) {
                    if (frame_len < sizeof(frame))
                        frame[frame_len++] = b;
                    continue;
                }
                int got = frame_take(req, len < 4 ? len : 4);
                if (got >= 0)
                    return got;
            }
            off += blen;
        }
    }
    LOG("no response to EFS command %d", req[2] | req[3] << 8);
    return -1;
}

static size_t efs_hdr(uint8_t *p, int cmd)
{
    p[0] = DIAG_SUBSYS_CMD_F;
    p[1] = DIAG_SUBSYS_FS;
    p[2] = cmd & 0xff;
    p[3] = cmd >> 8;
    return 4;
}

static void put32(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }
static int32_t get32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }

static size_t put_path(uint8_t *p, const char *path)
{
    size_t n = strlen(path) + 1;
    memcpy(p, path, n);
    return n;
}

/* Simple path commands answering with an errno right after the header */
static int efs_path_cmd(int cmd, const char *path, int extra16)
{
    uint8_t req[MAX_PKT];
    size_t n = efs_hdr(req, cmd);
    if (extra16 >= 0) {     /* mkdir takes a 16 bit mode first */
        req[n++] = extra16 & 0xff;
        req[n++] = extra16 >> 8;
    }
    n += put_path(req + n, path);
    int got = diag_cmd(req, n);
    if (got < 8)
        return -1;
    return get32(rsp + 4);
}

/* Returns the size, -EFS errno when missing, or a large negative on failure */
static int efs_stat(const char *path, int32_t *mode)
{
    uint8_t req[MAX_PKT];
    size_t n = efs_hdr(req, EFS2_DIAG_STAT);
    n += put_path(req + n, path);
    int got = diag_cmd(req, n);
    if (got < 16)
        return -1000;
    int32_t err = get32(rsp + 4);
    if (err)
        return -err;
    if (mode)
        *mode = get32(rsp + 8);
    return get32(rsp + 12);
}

static int efs_open(const char *path, int32_t flags, int32_t mode)
{
    uint8_t req[MAX_PKT];
    size_t n = efs_hdr(req, EFS2_DIAG_OPEN);
    put32(req + n, flags);
    put32(req + n + 4, mode);
    n += 8;
    n += put_path(req + n, path);
    int got = diag_cmd(req, n);
    if (got < 12)
        return -1;
    if (get32(rsp + 8)) {
        LOG("open %s: efs errno %d", path, get32(rsp + 8));
        return -1;
    }
    return get32(rsp + 4);
}

static void efs_close(int fd)
{
    uint8_t req[16];
    size_t n = efs_hdr(req, EFS2_DIAG_CLOSE);
    put32(req + n, fd);
    diag_cmd(req, n + 4);
}

/* Item files cannot be opened, efs_get reads those */
static int efs_get(const char *path, uint8_t *out, int size)
{
    uint8_t req[MAX_PKT];
    size_t n = efs_hdr(req, EFS2_DIAG_GET);
    size_t plen = strlen(path) + 1;
    put32(req + n, size);
    put32(req + n + 4, plen);
    req[n + 8] = 1;
    req[n + 9] = 0;
    n += 10;
    n += put_path(req + n, path);
    int got = diag_cmd(req, n);
    if (got < 14)
        return -1;
    int32_t num = get32(rsp + 4);
    if (get32(rsp + 8) || num < 0 || num > size || 14 + num > got)
        return -1;
    memcpy(out, rsp + 14, num);
    return num;
}

/* Returns the file length, -1 when missing, -2 on failure */
static int efs_read(const char *path, uint8_t *out)
{
    int32_t mode = 0;
    int size = efs_stat(path, &mode);
    if (size == -EFS_ENOENT)
        return -1;
    if (size < 0 || size > MAX_FILE)
        return -2;
    if ((mode & 0170000) == 0160000)
        return efs_get(path, out, size) == size ? size : -2;

    int fd = efs_open(path, EFS_O_RDONLY, 0);
    if (fd < 0)
        return -2;
    int off = 0;
    while (off < size) {
        uint8_t req[32];
        size_t n = efs_hdr(req, EFS2_DIAG_READ);
        int want = size - off > CHUNK ? CHUNK : size - off;
        put32(req + n, fd);
        put32(req + n + 4, want);
        put32(req + n + 8, off);
        int got = diag_cmd(req, n + 12);
        if (got < 20 || get32(rsp + 16) || get32(rsp + 12) <= 0 ||
                20 + get32(rsp + 12) > got)
            break;
        memcpy(out + off, rsp + 20, get32(rsp + 12));
        off += get32(rsp + 12);
    }
    efs_close(fd);
    return off == size ? size : -2;
}

static void efs_mkdirs(const char *path)
{
    char dir[256];
    for (const char *s = strchr(path + 1, '/'); s; s = strchr(s + 1, '/')) {
        size_t n = s - path;
        if (n >= sizeof(dir))
            return;
        memcpy(dir, path, n);
        dir[n] = 0;
        efs_path_cmd(EFS2_DIAG_MKDIR, dir, 0777);
    }
}

static int efs_write(const char *path, const uint8_t *data, int len)
{
    /* Replace item files (and stale files) with a plain file */
    if (efs_stat(path, NULL) >= 0 && efs_path_cmd(EFS2_DIAG_UNLINK, path, -1)) {
        LOG("unlink %s failed", path);
        return -1;
    }
    efs_mkdirs(path);
    int fd = efs_open(path, EFS_O_WRONLY | EFS_O_CREAT | EFS_O_TRUNC, 0777);
    if (fd < 0)
        return -1;
    int off = 0;
    while (off < len) {
        uint8_t req[32 + CHUNK];
        size_t n = efs_hdr(req, EFS2_DIAG_WRITE);
        int chunk = len - off > CHUNK ? CHUNK : len - off;
        put32(req + n, fd);
        put32(req + n + 4, off);
        memcpy(req + n + 8, data + off, chunk);
        int got = diag_cmd(req, n + 8 + chunk);
        if (got < 20 || get32(rsp + 16) || get32(rsp + 12) <= 0)
            break;
        off += get32(rsp + 12);
    }
    efs_close(fd);
    return off == len ? 0 : -1;
}

/*
 * Ask the modem to flush EFS to modemst now instead of at its own pace. The
 * flush goes out through rmt_storage right away, but this modem keeps
 * reporting the sync as pending, so only wait for the status briefly.
 */
static void efs_sync(void)
{
    uint8_t req[64];
    size_t n = efs_hdr(req, EFS2_DIAG_SYNC_NO_WAIT);
    req[n++] = 1;
    req[n++] = 0;
    n += put_path(req + n, "/");
    int got = diag_cmd(req, n);
    if (got < 14 || get32(rsp + 10)) {
        LOG("efs sync not accepted");
        return;
    }
    uint32_t token = get32(rsp + 6);
    for (int i = 0; i < 10; i++) {
        usleep(200000);
        n = efs_hdr(req, EFS2_DIAG_SYNC_GET_STATUS);
        req[n++] = 1;
        req[n++] = 0;
        put32(req + n, token);
        n += 4;
        n += put_path(req + n, "/");
        got = diag_cmd(req, n);
        if (got >= 7 && rsp[6])
            return;
    }
}

/* DIAG_EXT_BUILD_ID_F: the build ID string follows a 12 byte header */
static int do_version(void)
{
    uint8_t req[4] = { 0x7c, 0, 0, 0 };
    int got = diag_cmd(req, 1);
    if (got <= 12)
        return 2;
    rsp[got] = 0;
    printf("%s\n", (char *)rsp + 12);
    return 0;
}

struct entry {
    char op;
    char path[200];
    uint8_t *data;
    int len;
};

static struct entry entries[256];
static int num_entries;

static int hexval(int c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static int load_set(const char *file)
{
    FILE *f = fopen(file, "re");
    static char line[2 * MAX_FILE + 256];

    if (!f) {
        LOG("open %s: %s", file, strerror(errno));
        return -1;
    }
    while (fgets(line, sizeof(line), f)) {
        char op, path[200], *hex;
        int pos = 0;
        if (line[0] == '#' || line[0] == '\n')
            continue;
        if (sscanf(line, "%c %199s %n", &op, path, &pos) < 2 || (op != 'w' && op != 'd'))
            goto bad;
        if (num_entries >= (int)(sizeof(entries) / sizeof(entries[0])))
            goto bad;
        struct entry *e = &entries[num_entries];
        e->op = op;
        strcpy(e->path, path);
        e->data = NULL;
        e->len = 0;
        if (op == 'w') {
            hex = line + pos;
            size_t hl = strcspn(hex, " \r\n");
            if (hl % 2 || hl / 2 > MAX_FILE)
                goto bad;
            e->data = malloc(hl / 2 + 1);
            for (size_t i = 0; i < hl / 2; i++) {
                int hi = hexval(hex[2 * i]), lo = hexval(hex[2 * i + 1]);
                if (hi < 0 || lo < 0)
                    goto bad;
                e->data[i] = hi << 4 | lo;
            }
            e->len = hl / 2;
        }
        num_entries++;
    }
    fclose(f);
    return 0;
bad:
    LOG("%s: bad entry: %.60s", file, line);
    fclose(f);
    return -1;
}

static uint8_t cur[MAX_FILE];

/* 1 when the modem matches the entry, 0 when not, -1 on failure */
static int entry_matches(const struct entry *e)
{
    int len = efs_read(e->path, cur);
    if (len == -2)
        return -1;
    if (e->op == 'd')
        return len == -1;
    return len == e->len && !memcmp(cur, e->data, len);
}

static int do_check(int verbose)
{
    int differ = 0;
    for (int i = 0; i < num_entries; i++) {
        int m = entry_matches(&entries[i]);
        if (m < 0)
            return 2;
        if (!m) {
            differ++;
            if (verbose)
                LOG("differs: %s", entries[i].path);
        }
    }
    return differ ? 1 : 0;
}

static int do_apply(void)
{
    int failed = 0, changed = 0;
    for (int i = 0; i < num_entries; i++) {
        struct entry *e = &entries[i];
        int m = entry_matches(e);
        if (m == 1)
            continue;
        changed++;
        int err = e->op == 'w' ? efs_write(e->path, e->data, e->len)
                               : efs_path_cmd(EFS2_DIAG_UNLINK, e->path, -1);
        if (err && !(e->op == 'd' && err == EFS_ENOENT)) {
            LOG("%s %s failed", e->op == 'w' ? "write" : "delete", e->path);
            failed++;
        }
    }
    if (changed)
        efs_sync();
    LOG("applied %d of %d entries, %d failed", changed - failed, num_entries, failed);
    return failed ? 1 : do_check(1);
}

static int do_save(const char *out)
{
    char tmp[256];
    snprintf(tmp, sizeof(tmp), "%s.tmp", out);
    FILE *f = fopen(tmp, "we");
    if (!f) {
        LOG("create %s: %s", tmp, strerror(errno));
        return 2;
    }
    for (int i = 0; i < num_entries; i++) {
        int dup = 0;
        for (int j = 0; j < i; j++)
            dup |= !strcmp(entries[i].path, entries[j].path);
        if (dup)
            continue;
        int len = efs_read(entries[i].path, cur);
        if (len == -2) {
            fclose(f);
            unlink(tmp);
            return 2;
        }
        if (len == -1) {
            fprintf(f, "d %s\n", entries[i].path);
            continue;
        }
        fprintf(f, "w %s ", entries[i].path);
        for (int k = 0; k < len; k++)
            fprintf(f, "%02x", cur[k]);
        fputc('\n', f);
    }
    if (fflush(f) || fsync(fileno(f)) || fclose(f) || rename(tmp, out)) {
        LOG("write %s failed", out);
        return 2;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int ret;

    if (argc == 2 && !strcmp(argv[1], "version")) {
        if (diag_open())
            return 2;
        ret = do_version();
        close(diag_fd);
        return ret;
    }
    if (argc < 3)
        goto usage;
    if (!strcmp(argv[1], "save")) {
        if (argc < 4)
            goto usage;
        for (int i = 3; i < argc; i++)
            if (load_set(argv[i]))
                return 2;
    } else if (argc != 3 || load_set(argv[2])) {
        goto usage;
    }

    if (diag_open())
        return 2;
    if (!strcmp(argv[1], "check"))
        ret = do_check(1);
    else if (!strcmp(argv[1], "apply"))
        ret = do_apply();
    else if (!strcmp(argv[1], "save"))
        ret = do_save(argv[2]);
    else
        ret = 2;
    close(diag_fd);
    return ret;

usage:
    fprintf(stderr, "usage: %s check|apply <set> | save <out> <set>... | version\n", argv[0]);
    return 2;
}
