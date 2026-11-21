/*
 * Buffer handle access for both the QTI gralloc and minigbm.
 *
 * The HAL reads the dma-buf fd and size of a gralloc buffer straight from
 * its handle. Under the mainline display stack the buffers come from
 * minigbm, whose handle has another layout, so tell the two apart by the
 * minigbm magic first.
 */
#ifndef __QCAMERA3_GRALLOC_HANDLE_H__
#define __QCAMERA3_GRALLOC_HANDLE_H__

#include <unistd.h>
#include <cutils/native_handle.h>
#include "gralloc_priv.h"
#include "cros_gralloc_handle.h"

namespace qcamera {

static const uint32_t kCrosGrallocMagic = 0xABCDDCBA;

static inline const cros_gralloc_handle *crosHandle(buffer_handle_t h)
{
    size_t words = sizeof(cros_gralloc_handle) - sizeof(native_handle_t);

    if (!h || h->numFds < 1 ||
        (size_t)(h->numFds + h->numInts) * sizeof(int) < words)
        return NULL;
    const cros_gralloc_handle *ch = (const cros_gralloc_handle *)h;
    return ch->magic == kCrosGrallocMagic ? ch : NULL;
}

static inline bool isQtiHandle(buffer_handle_t h)
{
    return h && !crosHandle(h);
}

static inline int grallocHandleFd(buffer_handle_t h)
{
    const cros_gralloc_handle *ch = crosHandle(h);

    return ch ? ch->fds[0] : ((const private_handle_t *)h)->fd;
}

static inline size_t grallocHandleSize(buffer_handle_t h)
{
    const cros_gralloc_handle *ch = crosHandle(h);

    if (ch) {
        /* The dma-buf size; total_size may count more than the fd holds */
        off_t end = lseek(ch->fds[0], 0, SEEK_END);

        lseek(ch->fds[0], 0, SEEK_SET);
        return end > 0 ? (size_t)end : (size_t)ch->total_size;
    }
    return (size_t)((const private_handle_t *)h)->size;
}

static inline int grallocHandleWidth(buffer_handle_t h)
{
    const cros_gralloc_handle *ch = crosHandle(h);

    return ch ? (int)ch->width : ((const private_handle_t *)h)->width;
}

}; // namespace qcamera

#endif
