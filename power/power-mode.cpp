/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "android.hardware.power-service.ef71"

#include <aidl/android/hardware/power/BnPower.h>
#include <android-base/file.h>
#include <android-base/logging.h>

#include <unistd.h>

using ::aidl::android::hardware::power::Mode;

namespace aidl {
namespace android {
namespace hardware {
namespace power {
namespace impl {

// EF71S: Atmel mXT641T, EF71AS: FocalTech FT8716. Only the one fitted to
// the device probes, so write to whichever node exists.
static constexpr const char* kTapToWakeNodes[] = {
        "/sys/devices/platform/soc/78b7000.i2c/i2c-3/3-004a/dt2w_enable",
        "/sys/devices/virtual/touchscreen/touchscreen_dev/gesture_ctrl",
};

static const char* findTapToWakeNode() {
    for (const char* node : kTapToWakeNodes) {
        if (access(node, F_OK) == 0) return node;
    }
    return nullptr;
}

bool isDeviceSpecificModeSupported(Mode type, bool* _aidl_return) {
    switch (type) {
        case Mode::DOUBLE_TAP_TO_WAKE:
            *_aidl_return = findTapToWakeNode() != nullptr;
            return true;
        default:
            return false;
    }
}

bool setDeviceSpecificMode(Mode type, bool enabled) {
    switch (type) {
        case Mode::DOUBLE_TAP_TO_WAKE: {
            const char* node = findTapToWakeNode();
            if (!node) {
                LOG(WARNING) << "No double tap to wake node";
            } else if (!::android::base::WriteStringToFile(enabled ? "1" : "0", node)) {
                PLOG(ERROR) << "Failed to write " << node;
            }
            return true;
        }
        default:
            return false;
    }
}

}  // namespace impl
}  // namespace power
}  // namespace hardware
}  // namespace android
}  // namespace aidl
