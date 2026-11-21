/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/android/hardware/light/BnLights.h>

#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace aidl {
namespace android {
namespace hardware {
namespace light {

class Lights : public BnLights {
  public:
    Lights();
    ~Lights();

    ndk::ScopedAStatus setLightState(int id, const HwLightState& state) override;
    ndk::ScopedAStatus getLights(std::vector<HwLight>* lights) override;

  private:
    void setBacklight(const HwLightState& state);
    void setButtons(const HwLightState& state);
    void updateIndicatorLocked();
    void setIndicatorLocked(const HwLightState& state);
    void writeIndicator(uint32_t red, uint32_t green, uint32_t blue);
    void blinkLoop();

    int mLcdMaxBrightness;
    std::mutex mLock;
    HwLightState mAttention;
    HwLightState mNotification;
    HwLightState mBattery;

    // The indicator blinks in software: the LP5523 engines are not used
    std::condition_variable mBlinkCv;
    std::thread mBlinkThread;
    bool mExit = false;
    uint64_t mBlinkGeneration = 0;
    bool mBlinking = false;
    uint32_t mBlinkRed = 0, mBlinkGreen = 0, mBlinkBlue = 0;
    int mBlinkOnMs = 0, mBlinkOffMs = 0;
};

}  // namespace light
}  // namespace hardware
}  // namespace android
}  // namespace aidl
