#
# Copyright (C) 2016 The CyanogenMod Project
#           (C) 2017-2022 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#
# Pantech VEGA IRON 2 (EF71) on msm-4.19: product configuration.
#

LOCAL_PATH := device/pantech/ef71

$(call inherit-product, $(SRC_TARGET_DIR)/product/userspace_reboot.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/emulated_storage.mk)
$(call inherit-product, frameworks/native/build/phone-xhdpi-2048-dalvik-heap.mk)

# Add common definitions for Qualcomm
$(call inherit-product, hardware/qcom-caf/common/common.mk)

# Boot animation
TARGET_SCREEN_HEIGHT := 1920
TARGET_SCREEN_WIDTH := 1080

# Debugfs: the legacy QCOM sepolicy still reads debugfs, which the
# restrictions neverallow
PRODUCT_SET_DEBUGFS_RESTRICTIONS := false

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.audio.low_latency.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.audio.low_latency.xml \
    frameworks/native/data/etc/android.hardware.bluetooth.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.bluetooth.xml \
    frameworks/native/data/etc/android.hardware.bluetooth_le.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.bluetooth_le.xml \
    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.front.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.front.xml \
    frameworks/native/data/etc/android.hardware.location.gps.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.location.gps.xml \
    frameworks/native/data/etc/android.hardware.nfc.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.nfc.xml \
    frameworks/native/data/etc/android.hardware.nfc.hce.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.nfc.hce.xml \
    frameworks/native/data/etc/android.hardware.nfc.hcef.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.nfc.hcef.xml \
    frameworks/native/data/etc/android.hardware.opengles.aep.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.opengles.aep.xml \
    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.compass.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.compass.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/android.hardware.sensor.stepcounter.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.stepcounter.xml \
    frameworks/native/data/etc/android.hardware.sensor.stepdetector.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.stepdetector.xml \
    frameworks/native/data/etc/android.hardware.telephony.cdma.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.telephony.cdma.xml \
    frameworks/native/data/etc/android.hardware.telephony.gsm.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.telephony.gsm.xml \
    frameworks/native/data/etc/android.hardware.telephony.ims.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.telephony.ims.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
    frameworks/native/data/etc/android.hardware.usb.accessory.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/native/data/etc/android.hardware.usb.host.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.usb.host.xml \
    frameworks/native/data/etc/android.hardware.vulkan.compute-0.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.vulkan.compute-0.xml \
    frameworks/native/data/etc/android.hardware.vulkan.level-0.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.vulkan.level-0.xml \
    frameworks/native/data/etc/android.hardware.vulkan.version-1_1.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.vulkan.version-1_1.xml \
    frameworks/native/data/etc/android.hardware.wifi.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/android.hardware.wifi.direct.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.wifi.direct.xml \
    frameworks/native/data/etc/android.hardware.wifi.passpoint.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.wifi.passpoint.xml \
    frameworks/native/data/etc/android.software.ipsec_tunnels.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.ipsec_tunnels.xml \
    frameworks/native/data/etc/android.software.midi.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.midi.xml \
    frameworks/native/data/etc/android.software.opengles.deqp.level-2020-03-01.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.opengles.deqp.level.xml \
    frameworks/native/data/etc/android.software.print.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.print.xml \
    frameworks/native/data/etc/android.software.vulkan.deqp.level-2020-03-01.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.vulkan.deqp.level.xml \
    frameworks/native/data/etc/com.android.nfc_extras.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/com.android.nfc_extras.xml \
    frameworks/native/data/etc/com.nxp.mifare.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/com.nxp.mifare.xml

# ANT+
EF71_PRODUCT_PACKAGES += \
    AntHalService \
    com.dsi.ant@1.0.vendor


# Audio
EF71_PRODUCT_PACKAGES += \
    android.hardware.audio@7.0-impl \
    android.hardware.audio.effect@7.0-impl \
    android.hardware.audio.service \
    android.hardware.bluetooth.audio-impl \
    android.hardware.soundtrigger@2.1-impl \
    audio.bluetooth.default \
    audio.r_submix.default \
    audio.usb.default \
    audio.primary.tinyhal \
    libaudiopreprocessing \
    libaudioroute \
    libaacwrapper \
    libaudio-resampler \
    libqcomvisualizer \
    libqcomvoiceprocessing

# TinyHAL drives the mainline Q6 + WCD9335 sound card
PRODUCT_VENDOR_PROPERTIES += \
    ro.hardware.audio.primary=tinyhal

# WCD9335 with one WSA8810, from the EF71 LineageOS 17.1 tree
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/audio_configs.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_configs.xml \
    $(LOCAL_PATH)/audio/audio_effects.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_effects.xml \
    $(LOCAL_PATH)/audio/audio_platform_info.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_platform_info.xml \
    $(LOCAL_PATH)/audio/audio_platform_info_extcodec.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_platform_info_extcodec.xml \
    $(LOCAL_PATH)/audio/mainline/audio.ef71.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio.ef71.xml \
    $(LOCAL_PATH)/audio/mainline/audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_policy_configuration.xml \
    $(LOCAL_PATH)/audio/mainline/primary_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/primary_audio_policy_configuration.xml \
    $(LOCAL_PATH)/audio/audio_tuning_mixer.txt:$(TARGET_COPY_OUT_VENDOR)/etc/audio_tuning_mixer.txt \
    $(LOCAL_PATH)/audio/mixer_paths.xml:$(TARGET_COPY_OUT_VENDOR)/etc/mixer_paths.xml \
    $(LOCAL_PATH)/audio/mixer_paths_wcd9335.xml:$(TARGET_COPY_OUT_VENDOR)/etc/mixer_paths_wcd9335.xml \
    $(LOCAL_PATH)/audio/mixer_paths_wcd9335.xml:$(TARGET_COPY_OUT_VENDOR)/etc/mixer_paths_tashalite.xml \
    $(LOCAL_PATH)/audio/sound_trigger_mixer_paths.xml:$(TARGET_COPY_OUT_VENDOR)/etc/sound_trigger_mixer_paths.xml \
    $(LOCAL_PATH)/audio/sound_trigger_mixer_paths_wcd9335.xml:$(TARGET_COPY_OUT_VENDOR)/etc/sound_trigger_mixer_paths_wcd9335.xml \
    $(LOCAL_PATH)/audio/sound_trigger_platform_info.xml:$(TARGET_COPY_OUT_VENDOR)/etc/sound_trigger_platform_info.xml \
    frameworks/av/services/audiopolicy/config/a2dp_in_audio_policy_configuration_7_0.xml:$(TARGET_COPY_OUT_VENDOR)/etc/a2dp_in_audio_policy_configuration_7_0.xml \
    frameworks/av/services/audiopolicy/config/audio_policy_volumes.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_policy_volumes.xml \
    frameworks/av/services/audiopolicy/config/bluetooth_audio_policy_configuration_7_0.xml:$(TARGET_COPY_OUT_VENDOR)/etc/bluetooth_audio_policy_configuration_7_0.xml \
    frameworks/av/services/audiopolicy/config/default_volume_tables.xml:$(TARGET_COPY_OUT_VENDOR)/etc/default_volume_tables.xml \
    frameworks/av/services/audiopolicy/config/r_submix_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/r_submix_audio_policy_configuration.xml \
    frameworks/av/services/audiopolicy/config/usb_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/usb_audio_policy_configuration.xml


# Bluetooth: the AOSP HAL drives the WCN3660 through the btqcomsmd hci0,
# whose public address bdaddr sets from the serial number
EF71_PRODUCT_PACKAGES += \
    android.hardware.bluetooth-service.default \
    bdaddr

# The WCN3660 controller lacks the extended APCF features
PRODUCT_VENDOR_PROPERTIES += \
    bluetooth.le.disable_apcf_extended_features=1

# Camera: the Qualcomm camera HAL over the camera_v2 stack of the kernel
EF71_PRODUCT_PACKAGES += \
    android.frameworks.sensorservice@1.0.vendor \
    android.hardware.camera.provider@2.4-impl \
    android.hardware.camera.provider@2.4-service \
    camera.msm8937 \
    libmmcamera_interface \
    libmmjpeg_interface \
    libqomx_core \
    libstdc++_vendor \
    vendor.qti.hardware.camera.device@1.0.vendor

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/camera/imx214_chromatix.xml:$(TARGET_COPY_OUT_VENDOR)/etc/camera/imx214_chromatix.xml \
    $(LOCAL_PATH)/configs/camera/pantech_camera_tp10.xml:$(TARGET_COPY_OUT_VENDOR)/etc/camera/pantech_camera_tp10.xml \
    $(LOCAL_PATH)/configs/camera/pantech_camera_tp20.xml:$(TARGET_COPY_OUT_VENDOR)/etc/camera/pantech_camera_tp20.xml \
    $(LOCAL_PATH)/configs/camera/pantech_camera_ws10.xml:$(TARGET_COPY_OUT_VENDOR)/etc/camera/pantech_camera_ws10.xml \
    $(LOCAL_PATH)/configs/camera/s5k5e2_chromatix.xml:$(TARGET_COPY_OUT_VENDOR)/etc/camera/s5k5e2_chromatix.xml

# Configstore (msm-4.19)
EF71_PRODUCT_PACKAGES += \
    disable_configstore

# Firmware
EF71_PRODUCT_PACKAGES += \
    firmware_image_symlink

# Display (mainline: DRM/KMS through drm_hwcomposer, buffers from minigbm,
# GPU through Mesa freedreno)
EF71_PRODUCT_PACKAGES += \
    android.hardware.graphics.composer@2.4-service \
    hwcomposer.drm \
    android.hardware.graphics.allocator@4.0-service.minigbm_msm \
    android.hardware.graphics.mapper@4.0-impl.minigbm_msm \
    gralloc.minigbm_msm \
    libGLES_mesa \
    android.frameworks.displayservice@1.0.vendor

PRODUCT_VENDOR_PROPERTIES += \
    ro.hardware.egl=mesa \
    ro.hardware.gralloc=minigbm_msm \
    vendor.minigbm.debug=nocompression \
    ro.hardware.hwcomposer=drm \
    ro.opengles.version=196608

# DRM
EF71_PRODUCT_PACKAGES += \
    android.hardware.drm-service.clearkey \
    android.hardware.drm@1.4.vendor

# Fastbootd
EF71_PRODUCT_PACKAGES += \
    fastbootd

# FM
EF71_PRODUCT_PACKAGES += \
    FMRadio \
    libfmjni

# Gatekeeper
EF71_PRODUCT_PACKAGES += \
    android.hardware.gatekeeper@1.0-service.software

# GPS
include $(LOCAL_PATH)/gps/gps_vendor_product.mk

EF71_PRODUCT_PACKAGES += \
    android.hardware.gnss@2.1.vendor

# Health
EF71_PRODUCT_PACKAGES += \
    android.hardware.health-service.qti \
    android.hardware.health-service.qti_recovery

# HIDL
EF71_PRODUCT_PACKAGES += \
    android.hidl.base@1.0 \
    android.hidl.base@1.0.vendor \
    android.hidl.manager@1.0 \
    libhidltransport \
    libhidltransport.vendor \
    libhwbinder \
    libhwbinder.vendor

# IMS
EF71_PRODUCT_PACKAGES += \
    android.hardware.camera.device@3.3 \
    android.hardware.camera.device@3.4 \
    android.hardware.camera.device@3.5 \
    android.hardware.camera.provider@2.4 \
    android.hardware.camera.provider@2.5 \
    android.hardware.camera.provider@2.6 \
    libshim_imscamera \
    vendor.qti.hardware.camera.device@1.0

# Init
EF71_PRODUCT_PACKAGES += \
    init.qcom.rc \
    init.qcom.usb.rc \
    init.recovery.qcom.rc \
    init.target.rc \
    init.uclamp.rc \
    init.ef71.rc \
    ueventd.qcom.rc \
    init.acdbdata.sh \
    init.class_main.sh \
    init.ef71.apn.sh \
    init.qcom.early_boot.sh \
    init.qcom.post_boot.sh \
    init.ef71.wlan_mac.sh \
    init.qcom.sensors.sh \
    init.qcom.sh \
    init.qcom.usb.sh \
    init.qti.dcvs.sh \
    fstab.qcom \
    fstab.qcom_ramdisk

# Modem: remote file systems and the TFTP server it reads its files from
EF71_PRODUCT_PACKAGES += \
    qrtr-cfg \
    qrtr-lookup \
    rmtfs \
    tqftpserv

# Seccomp
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/seccomp_policy/mediaextractor.policy:$(TARGET_COPY_OUT_VENDOR)/etc/seccomp_policy/mediaextractor.policy

# Keylayout
PRODUCT_COPY_FILES += \
    $(call find-copy-subdir-files,*,$(LOCAL_PATH)/keylayout/,$(TARGET_COPY_OUT_VENDOR)/usr/keylayout/)

# KeyMint (software, mainline has no QSEECom)
EF71_PRODUCT_PACKAGES += \
    android.hardware.security.keymint-service

# Lights
EF71_PRODUCT_PACKAGES += \
    android.hardware.lights-service.ef71

# Media
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/media/msm8937/media_profiles_8937.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/media_profiles.xml \
    $(LOCAL_PATH)/media/msm8937/media_profiles_8937.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_profiles_vendor.xml \
    $(LOCAL_PATH)/media/msm8937/media_profiles_8956.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/media_profiles_8956.xml \
    $(LOCAL_PATH)/media/msm8937/media_profiles_8956.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_profiles_8956.xml \
    $(LOCAL_PATH)/media/media_codecs_mainline.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs.xml \
    $(LOCAL_PATH)/media/msm8937/media_codecs_performance_8937.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_performance.xml \
    $(LOCAL_PATH)/media/msm8937/media_codecs_performance_8937.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_performance_vendor.xml \
    $(LOCAL_PATH)/media/media_profiles.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_profiles.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_audio.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_telephony.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_telephony.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_video.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_video.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_video_le.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_video_le.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_c2.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_c2.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_c2_audio.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_c2_audio.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_c2_video.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_c2_video.xml

# Codec2: the camera stack brings up a legacy /dev/ion, which makes Codec2
# pick its ION allocator, whose buffers it then fails to map. Keep it on the
# DMA-BUF heaps.
PRODUCT_VENDOR_PROPERTIES += \
    debug.c2.use_dmabufheaps=1

EF71_PRODUCT_PACKAGES += \
    libavservices_minijail.vendor

# Modem configuration (Korean carriers)
EF71_PRODUCT_PACKAGES += \
    ef71_apns-conf.xml \
    ef71_modemcfg

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/ef71_nocdma.xml:$(TARGET_COPY_OUT_VENDOR)/etc/ef71_nocdma.xml \
    $(LOCAL_PATH)/configs/modem/kt.cfg:$(TARGET_COPY_OUT_VENDOR)/etc/ef71_modem/kt.cfg \
    $(LOCAL_PATH)/configs/modem/lgu.cfg:$(TARGET_COPY_OUT_VENDOR)/etc/ef71_modem/lgu.cfg \
    $(LOCAL_PATH)/configs/modem/skt.cfg:$(TARGET_COPY_OUT_VENDOR)/etc/ef71_modem/skt.cfg

# Net
EF71_PRODUCT_PACKAGES += \
    android.system.net.netd@1.1.vendor

# NFC (PN548 on qcom,nq-nci)
EF71_PRODUCT_PACKAGES += \
    android.hardware.nfc@1.2-service \
    com.android.nfc_extras \
    NfcNci \
    SecureElement \
    Tag

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/nfc/libnfc-nci.conf:$(TARGET_COPY_OUT_PRODUCT)/etc/libnfc-nci.conf \
    $(LOCAL_PATH)/configs/nfc/libnfc-nxp.conf:$(TARGET_COPY_OUT_VENDOR)/etc/libnfc-nxp.conf

# Overlays
DEVICE_PACKAGE_OVERLAYS += \
    $(LOCAL_PATH)/overlay \
    $(LOCAL_PATH)/overlay-lineage \
    $(LOCAL_PATH)/overlay-radio

PRODUCT_ENFORCE_RRO_TARGETS := *
PRODUCT_ENFORCE_RRO_EXCLUDED_OVERLAYS += $(LOCAL_PATH)/overlay-radio/packages/apps/CarrierConfig

# Parts
EF71_PRODUCT_PACKAGES += \
    EF71Parts

# Perf
EF71_PRODUCT_PACKAGES += \
    vendor.qti.hardware.perf@2.2 \
    vendor.qti.hardware.perf@2.2.vendor

# Power
EF71_PRODUCT_PACKAGES += \
    android.hardware.power@1.2.vendor \
    android.hardware.power-service-qti

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/powerhint/system/powerhint.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/powerhint.xml \
    $(LOCAL_PATH)/configs/powerhint/vendor/powerhint.xml:$(TARGET_COPY_OUT_VENDOR)/etc/powerhint.xml \
    $(LOCAL_PATH)/configs/msm_irqbalance.conf:$(TARGET_COPY_OUT_VENDOR)/etc/msm_irqbalance.conf \
    $(LOCAL_PATH)/configs/msm_irqbalance_little_big.conf:$(TARGET_COPY_OUT_VENDOR)/etc/msm_irqbalance_little_big.conf \
    system/core/libprocessgroup/profiles/cgroups_28.json:$(TARGET_COPY_OUT_VENDOR)/etc/cgroups.json \
    system/core/libprocessgroup/profiles/task_profiles_28.json:$(TARGET_COPY_OUT_VENDOR)/etc/task_profiles.json

# QTI
EF71_PRODUCT_PACKAGES += \
    libjson \
    libnetutils.vendor:64 \
    libsqlite.vendor:64 \
    libqti_vndfwk_detect \
    libqti_vndfwk_detect.vendor \
    libvndfwk_detect_jni.qti \
    libvndfwk_detect_jni.qti.vendor

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/sec_config:$(TARGET_COPY_OUT_VENDOR)/etc/sec_config \
    $(LOCAL_PATH)/configs/qti_whitelist.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/sysconfig/qti_whitelist.xml \
    $(LOCAL_PATH)/configs/privapp-permissions-qti.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/permissions/privapp-permissions-qti.xml \
    $(LOCAL_PATH)/configs/telephony_product_privapp-permissions-qti.xml:$(TARGET_COPY_OUT_PRODUCT)/etc/permissions/telephony_product_privapp-permissions-qti.xml \
    $(LOCAL_PATH)/configs/telephony_system-ext_privapp-permissions-qti.xml:$(TARGET_COPY_OUT_SYSTEM_EXT)/etc/permissions/telephony_system-ext_privapp-permissions-qti.xml

# Radio
EF71_PRODUCT_PACKAGES += \
    android.hardware.radio@1.4.vendor \
    android.hardware.radio@1.5.vendor \
    android.hardware.radio.config@1.2.vendor \
    android.hardware.radio.deprecated@1.0.vendor \
    android.hardware.secure_element@1.0.vendor \
    android.hardware.secure_element@1.1.vendor \
    android.hardware.secure_element@1.2.vendor \
    libshim_qcrild \
    libxml2

# Resolution
PRODUCT_AAPT_CONFIG := normal
PRODUCT_AAPT_PREF_CONFIG := xxhdpi

# Sensors
EF71_PRODUCT_PACKAGES += \
    android.hardware.sensors@1.0-impl \
    android.hardware.sensors@1.0-service \
    libpower.vendor:64 \
    libsensorndkbridge

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/sensors/hals.conf:$(TARGET_COPY_OUT_VENDOR)/etc/sensors/hals.conf \
    $(LOCAL_PATH)/configs/sensors/sensor_def_qcomdev.conf:$(TARGET_COPY_OUT_VENDOR)/etc/sensors/sensor_def_qcomdev.conf

# Shims
EF71_PRODUCT_PACKAGES += \
    libcrypto-v33 \
    libprotobuf-cpp-full-3.9.1-vendorcompat

# Soong namespaces
PRODUCT_SOONG_NAMESPACES += \
    external/tinyhal \
    hardware/mainline/qcom \
    $(LOCAL_PATH)

# Telephony
EF71_PRODUCT_PACKAGES += \
    ims-ext-common \
    ims_ext_common.xml \
    qti-telephony-hidl-wrapper \
    qti_telephony_hidl_wrapper.xml \
    qti-telephony-utils \
    qti_telephony_utils.xml \
    telephony-ext

PRODUCT_BOOT_JARS += \
    telephony-ext

# Thermal
EF71_PRODUCT_PACKAGES += \
    android.hardware.thermal@2.0-service.qti.ef71


# USB
EF71_PRODUCT_PACKAGES += \
    android.hardware.usb@1.3-service.basic

# Vibrator
EF71_PRODUCT_PACKAGES += \
    vendor.qti.hardware.vibrator.service

# Wi-Fi
# No vendor Wi-Fi HAL: its legacy part only knows the Qualcomm prima driver
EF71_PRODUCT_PACKAGES += \
    libwpa_client \
    hostapd \
    wificond \
    WifiOverlayEF71 \
    wpa_supplicant

# EF71 calibration, from the LineageOS 17.1 tree
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/wifi/p2p_supplicant_overlay.conf:$(TARGET_COPY_OUT_VENDOR)/etc/wifi/p2p_supplicant_overlay.conf \
    $(LOCAL_PATH)/wifi/wpa_supplicant.conf:$(TARGET_COPY_OUT_VENDOR)/etc/wifi/wpa_supplicant.conf \
    $(LOCAL_PATH)/wifi/wpa_supplicant_overlay.conf:$(TARGET_COPY_OUT_VENDOR)/etc/wifi/wpa_supplicant_overlay.conf \
    $(LOCAL_PATH)/wifi/WCNSS_cfg.dat:$(TARGET_COPY_OUT_VENDOR)/firmware/wlan/prima/WCNSS_cfg.dat \
    $(LOCAL_PATH)/wifi/WCNSS_qcom_cfg.ini:$(TARGET_COPY_OUT_VENDOR)/etc/wifi/WCNSS_qcom_cfg.ini \
    $(LOCAL_PATH)/wifi/WCNSS_qcom_wlan_nv.bin:$(TARGET_COPY_OUT_VENDOR)/etc/wifi/WCNSS_qcom_wlan_nv.bin \
    $(LOCAL_PATH)/wifi/WCNSS_wlan_dictionary.dat:$(TARGET_COPY_OUT_VENDOR)/etc/wifi/WCNSS_wlan_dictionary.dat

# Symlinks
EF71_PRODUCT_PACKAGES += \
    CneApp.libvndfwk_detect_jni.qti_symlink \
    ims_libimscamera_jni.so_symlink \
    ims_libimsmedia_jni.so_symlink \
    libEGL_adreno_symlink32 \
    libGLESv2_adreno_symlink32 \
    libq3dtools_adreno_symlink32 \
    libEGL_adreno_symlink64 \
    libGLESv2_adreno_symlink64 \
    libq3dtools_adreno_symlink64 \
    firmware_WCNSS_qcom_cfg.ini_symlink \
    firmware_WCNSS_qcom_wlan_nv.bin_symlink \
    firmware_WCNSS_wlan_dictionary.dat_symlink \
    firmware_wlan_mac.bin_symlink

PRODUCT_PACKAGES += $(EF71_PRODUCT_PACKAGES)

# Qualcomm audio, display and media HALs (LA.UM.9.6.4.r2-04300-89xx.QSSI13r2.0)
USE_DEVICE_SPECIFIC_AUDIO := true
USE_DEVICE_SPECIFIC_DISPLAY := true
USE_DEVICE_SPECIFIC_MEDIA := true

# Audio
DEVICE_SPECIFIC_AUDIO_PATH := $(LOCAL_PATH)/qcom/audio/hal
PRODUCT_SOONG_NAMESPACES += $(LOCAL_PATH)/qcom/audio
TARGET_USES_QCOM_MM_AUDIO := true

# Media
MSM_VIDC_TARGET_LIST := msm8937 msm8953
TARGET_USES_MEDIA_EXTENSIONS := true
DEVICE_SPECIFIC_MEDIA_PATH := $(LOCAL_PATH)/qcom/media/hal

# Display (QSSI compliant HAL)
TARGET_USES_COLOR_METADATA := true
# $(QCOM_SOONG_NAMESPACE) must be a soong namespace with the
# display_intf_headers module under display/
# (SOONG_CONFIG_lineageQcomVars_qcom_display_headers_namespace)
QCOM_SOONG_NAMESPACE := $(LOCAL_PATH)/qcom/display
DEVICE_SPECIFIC_DISPLAY_PATH := $(QCOM_SOONG_NAMESPACE)/hal
PRODUCT_SOONG_NAMESPACES += \
    external/mesa3d \
    vendor/qcom/opensource/commonsys-intf/display \
    $(wildcard vendor/qcom/opensource/commonsys/display) \
    $(wildcard vendor/qcom/opensource/display)

# Proprietary files
$(call inherit-product, vendor/pantech/ef71/ef71-vendor.mk)

EXTRA_DEVICE_BRACKET := low-end
