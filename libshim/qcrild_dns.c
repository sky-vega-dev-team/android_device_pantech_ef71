/*
 * Copyright (C) 2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 *
 * qcrild: report the IPv6 DNS servers of an IPv6 PDN.
 *
 * The EF71 modem (MPSS.JO.1.2) returns its IPv4 DNS servers with the
 * runtime settings of an IPv6 PDN too. libqdi takes the IPv4 servers
 * whenever they are present and copies them into an IPv6 address, so the
 * framework gets bogus servers such as ac1b:10aa:: (172.27.16.170) and the
 * PDN has no working DNS (and so no 464xlat). Pantech's qdi preferred the
 * IPv6 servers (FEATURE_SKY_DS_SUPPROT_CLAT4_DNS); do the same by dropping
 * the IPv4 servers from any WDS GET_RUNTIME_SETTINGS response that also
 * carries IPv6 servers (the modem only adds those to IPv6 PDNs).
 *
 * The offsets are those of the stock IDL; the IDL the qcrild blobs use only
 * appends TLVs (its response is 12008 bytes instead of 8988).
 */

#define LOG_TAG "ef71-qcrild-shim"

#include <dlfcn.h>
#include <stdint.h>
#include <string.h>

#include <log/log.h>

#define QMI_WDS_GET_RUNTIME_SETTINGS 0x002D

/* wds_get_runtime_settings_resp_msg_v01 (wireless_data_service_v01.h) */
#define OFF_DNS4_PRI_VALID 220
#define OFF_DNS4_SEC_VALID 228
#define OFF_DNS6_PRI_VALID 4464
#define OFF_DNS6_SEC_VALID 4481
#define RESP_MIN_LEN (OFF_DNS6_SEC_VALID + 1 + 16)
/* wds_get_runtime_settings_req_msg_v01: requested_settings (valid + mask) */
#define REQ_LEN 8

typedef void *qmi_client_type;
typedef int (*send_msg_sync_t)(qmi_client_type, unsigned int, void *, unsigned int, void *,
                               unsigned int, unsigned int);

int qmi_client_send_msg_sync(qmi_client_type handle, unsigned int msg_id, void *req,
                             unsigned int req_len, void *resp, unsigned int resp_len,
                             unsigned int timeout_msecs) {
    static send_msg_sync_t real;
    int rc;

    if (!real) {
        real = (send_msg_sync_t)dlsym(RTLD_NEXT, "qmi_client_send_msg_sync");
        if (!real) {
            ALOGE("qmi_client_send_msg_sync not found: %s", dlerror());
            return -1;
        }
    }

    rc = real(handle, msg_id, req, req_len, resp, resp_len, timeout_msecs);
    if (rc != 0 || msg_id != QMI_WDS_GET_RUNTIME_SETTINGS || req_len != REQ_LEN || !resp ||
        resp_len < RESP_MIN_LEN)
        return rc;

    uint8_t *r = (uint8_t *)resp;
    if (r[OFF_DNS6_PRI_VALID] && r[OFF_DNS4_PRI_VALID]) {
        r[OFF_DNS4_PRI_VALID] = 0;
        ALOGI("using the IPv6 primary DNS server");
    }
    if (r[OFF_DNS6_SEC_VALID] && r[OFF_DNS4_SEC_VALID]) {
        r[OFF_DNS4_SEC_VALID] = 0;
        ALOGI("using the IPv6 secondary DNS server");
    }
    return rc;
}
