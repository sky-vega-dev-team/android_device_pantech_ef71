#
# Copyright (C) 2026 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# thermal.c and thermal_common.[ch] are copied unchanged from
# hardware/qcom-caf/thermal (lineage-17.1, 8c677b6). That project has no
# config for MSM8937 (soc_id 294) or for the 3.18 tsens zone names, so
# without a module the default thermal HAL crashed on every call.

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := thermal.ef71
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_VENDOR_MODULE := true

LOCAL_SRC_FILES := \
    thermal.c \
    thermal_common.c \
    thermal-ef71.c

LOCAL_HEADER_LIBRARIES := libutils_headers libhardware_headers
LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_CFLAGS := -Wno-unused-parameter

include $(BUILD_SHARED_LIBRARY)
