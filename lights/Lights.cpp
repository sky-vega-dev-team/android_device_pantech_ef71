/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "lights-ef71"

#include "Lights.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/parseint.h>
#include <android-base/strings.h>

using ::android::base::ParseInt;
using ::android::base::ReadFileToString;
using ::android::base::Trim;
using ::android::base::WriteStringToFile;

namespace aidl {
namespace android {
namespace hardware {
namespace light {

namespace {

constexpr const char* kLcdBrightness = "/sys/class/leds/lcd-backlight/brightness";
constexpr const char* kLcdMaxBrightness = "/sys/class/leds/lcd-backlight/max_brightness";

/*
 * The EF71 has one LP5523 for the front indicator (a left and a right RGB
 * LED) and the menu and back key backlights. The Pantech driver takes the
 * channel brightnesses as they are written and applies them when a command
 * is written to channel 8 (PAN_LED_LP5523_BLINK_CMD).
 */
enum Lp5523Channel {
    kLeftGreen = 0,
    kLeftBlue = 1,
    kRightGreen = 2,
    kRightBlue = 3,
    kMenuKey = 4,
    kBackKey = 5,
    kLeftRed = 6,
    kRightRed = 7,
    kCommand = 8,
};

enum Lp5523Command {
    kCmdKeys = 1,   // PWM_TK_ON_OFF: apply the menu and back key brightness
    kCmdSolid = 3,  // PWM_HOMEKEY_ON_OFF: apply the indicator brightness
    kCmdBlink = 8,  // DIMMING_ON_OFF_COLOR: blink the indicator
};

std::string channelPath(int channel) {
    return "/sys/class/leds/lp5523:channel" + std::to_string(channel) + "/brightness";
}

bool writeInt(const std::string& path, int value) {
    if (!WriteStringToFile(std::to_string(value), path)) {
        PLOG(ERROR) << "Failed to write " << value << " to " << path;
        return false;
    }
    return true;
}

void writeChannel(int channel, int value) {
    writeInt(channelPath(channel), value);
}

bool isLit(const HwLightState& state) {
    return state.color & 0x00ffffff;
}

// Brightness of an ARGB color, the alpha scaling the color as the framework intends
uint32_t argbToBrightness(uint32_t color) {
    uint32_t alpha = (color >> 24) & 0xff;
    uint32_t red = (color >> 16) & 0xff;
    uint32_t green = (color >> 8) & 0xff;
    uint32_t blue = color & 0xff;

    if (alpha != 0xff) {
        red = red * alpha / 0xff;
        green = green * alpha / 0xff;
        blue = blue * alpha / 0xff;
    }
    return (77 * red + 150 * green + 29 * blue) >> 8;
}

#define LIGHT(t) {.id = static_cast<int>(t), .ordinal = 0, .type = t}

const std::vector<HwLight> kLights = {
        LIGHT(LightType::BACKLIGHT),
        LIGHT(LightType::BUTTONS),
        LIGHT(LightType::BATTERY),
        LIGHT(LightType::NOTIFICATIONS),
        LIGHT(LightType::ATTENTION),
};

}  // namespace

Lights::Lights() : mLcdMaxBrightness(255) {
    std::string value;
    int max;

    if (ReadFileToString(kLcdMaxBrightness, &value) && ParseInt(Trim(value), &max) && max > 0) {
        mLcdMaxBrightness = max;
    }
    LOG(INFO) << "LCD max brightness " << mLcdMaxBrightness;
}

ndk::ScopedAStatus Lights::setLightState(int id, const HwLightState& state) {
    switch (static_cast<LightType>(id)) {
        case LightType::BACKLIGHT:
            setBacklight(state);
            break;
        case LightType::BUTTONS:
            setButtons(state);
            break;
        case LightType::BATTERY: {
            std::lock_guard<std::mutex> lock(mLock);
            mBattery = state;
            updateIndicatorLocked();
            break;
        }
        case LightType::NOTIFICATIONS: {
            std::lock_guard<std::mutex> lock(mLock);
            mNotification = state;
            updateIndicatorLocked();
            break;
        }
        case LightType::ATTENTION: {
            std::lock_guard<std::mutex> lock(mLock);
            mAttention = state;
            // PowerManager turns the attention light off with an empty flash
            if (mAttention.flashOnMs == 0 && mAttention.flashOffMs == 0) {
                mAttention.color = 0;
            }
            updateIndicatorLocked();
            break;
        }
        default:
            return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Lights::getLights(std::vector<HwLight>* lights) {
    *lights = kLights;
    return ndk::ScopedAStatus::ok();
}

void Lights::setBacklight(const HwLightState& state) {
    writeInt(kLcdBrightness, argbToBrightness(state.color) * mLcdMaxBrightness / 0xff);
}

void Lights::setButtons(const HwLightState& state) {
    std::lock_guard<std::mutex> lock(mLock);
    int brightness = argbToBrightness(state.color);

    writeChannel(kMenuKey, brightness);
    writeChannel(kBackKey, brightness);
    writeChannel(kCommand, kCmdKeys);
}

void Lights::updateIndicatorLocked() {
    if (isLit(mAttention)) {
        setIndicatorLocked(mAttention);
    } else if (isLit(mNotification)) {
        setIndicatorLocked(mNotification);
    } else {
        setIndicatorLocked(mBattery);
    }
}

void Lights::setIndicatorLocked(const HwLightState& state) {
    uint32_t alpha = (state.color >> 24) & 0xff;
    uint32_t red = (state.color >> 16) & 0xff;
    uint32_t green = (state.color >> 8) & 0xff;
    uint32_t blue = state.color & 0xff;

    if (alpha != 0xff) {
        red = red * alpha / 0xff;
        green = green * alpha / 0xff;
        blue = blue * alpha / 0xff;
    }

    bool blink = (state.flashMode == FlashMode::TIMED || state.flashMode == FlashMode::HARDWARE) &&
                 state.flashOnMs > 0 && state.flashOffMs > 0;

    // The blink program mixes at most two colors: drop the weakest of three
    if (blink && red && green && blue && red < 0xff && green < 0xff && blue < 0xff) {
        if (red <= green && red <= blue) {
            red = 0;
        } else if (green <= red && green <= blue) {
            green = 0;
        } else {
            blue = 0;
        }
    }

    writeChannel(kLeftRed, red);
    writeChannel(kLeftGreen, green);
    writeChannel(kLeftBlue, blue);
    writeChannel(kRightRed, red);
    writeChannel(kRightGreen, green);
    writeChannel(kRightBlue, blue);
    writeChannel(kCommand, blink ? kCmdBlink : kCmdSolid);
}

}  // namespace light
}  // namespace hardware
}  // namespace android
}  // namespace aidl
