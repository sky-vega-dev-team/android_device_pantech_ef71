/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/android/hardware/light/BnLights.h>

#include <mutex>
#include <string>
#include <vector>

namespace aidl {
namespace android {
namespace hardware {
namespace light {

class Lights : public BnLights {
  public:
    Lights();

    ndk::ScopedAStatus setLightState(int id, const HwLightState& state) override;
    ndk::ScopedAStatus getLights(std::vector<HwLight>* lights) override;

  private:
    void setBacklight(const HwLightState& state);
    void setButtons(const HwLightState& state);
    void updateIndicatorLocked();
    void setIndicatorLocked(const HwLightState& state);

    int mLcdMaxBrightness;
    std::mutex mLock;
    HwLightState mAttention;
    HwLightState mNotification;
    HwLightState mBattery;
};

}  // namespace light
}  // namespace hardware
}  // namespace android
}  // namespace aidl
