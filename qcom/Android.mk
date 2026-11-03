#
# Copyright (C) 2026 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

LOCAL_PATH := $(call my-dir)

# The device Android.mk only looks one level down: pull in the HALs here
include $(DEVICE_SPECIFIC_AUDIO_PATH)/Android.mk
include $(DEVICE_SPECIFIC_MEDIA_PATH)/Android.mk
include $(QCOM_SOONG_NAMESPACE)/Android.mk
