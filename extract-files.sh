#!/bin/bash
#
# Copyright (C) 2016 The CyanogenMod Project
# Copyright (C) 2017-2020 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

set -e

DEVICE=ef71
VENDOR=pantech

# Load extract_utils and do some sanity checks
MY_DIR="${BASH_SOURCE%/*}"
if [[ ! -d "${MY_DIR}" ]]; then MY_DIR="${PWD}"; fi

LINEAGE_ROOT="${MY_DIR}/../../.."

HELPER="${LINEAGE_ROOT}/tools/extract-utils/extract_utils.sh"
if [ ! -f "${HELPER}" ]; then
    echo "Unable to find helper script at ${HELPER}"
    exit 1
fi
source "${HELPER}"

# Default to sanitizing the vendor folder before extraction
CLEAN_VENDOR=true

SECTION=
KANG=

while [ "${#}" -gt 0 ]; do
    case "${1}" in
        -n | --no-cleanup )
                CLEAN_VENDOR=false
                ;;
        -k | --kang )
                KANG="--kang"
                ;;
        -s | --section )
                SECTION="${2}"; shift
                CLEAN_VENDOR=false
                ;;
        * )
                SRC="${1}"
                ;;
    esac
    shift
done

if [ -z "${SRC}" ]; then
    SRC="adb"
fi

function blob_fixup() {
    case "${1}" in
        vendor/lib/libchromaflash.so \
        | vendor/lib/libmmcamera_hdr_gb_lib.so \
        | vendor/lib/liboptizoom.so \
        | vendor/lib/libseemore.so \
        | vendor/lib/libtrueportrait.so \
        | vendor/lib/libts_detected_face_hal.so \
        | vendor/lib/libts_face_beautify_hal.so \
        | vendor/lib/libubifocus.so)
            "${PATCHELF}" --replace-needed "libstdc++.so" "libstdc++_vendor.so" "${2}"
            ;;
        vendor/lib64/libwvhidl.so|vendor/lib64/mediadrm/libwvdrmengine.so)
            "${PATCHELF}" --replace-needed "libcrypto.so" "libcrypto-v33.so" "${2}"
            sed -i 's|libprotobuf-cpp-lite-3.9.1.so|libprotobuf-cpp-full-3.9.1.so|g' "${2}"
            ;;
    esac
}

# Initialize the helper
setup_vendor "${DEVICE}" "${VENDOR}" "${LINEAGE_ROOT}" false "${CLEAN_VENDOR}"

# The camera daemon side in proprietary-files.txt is built from
# github.com/rlawoehd1879/pantech_camera_driver_rework (ef71-android10) and
# the Qualcomm blobs come from several other devices, so pulling everything
# from a stock IM-100 does not reproduce vendor/pantech/ef71. Use -n and -s to
# refresh single sections.
extract "${MY_DIR}/proprietary-files.txt" "${SRC}" ${KANG} --section "${SECTION}"
extract "${MY_DIR}/proprietary-files-qc.txt" "${SRC}" ${KANG} --section "${SECTION}"

"${MY_DIR}/setup-makefiles.sh"
