/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Charging indicator for the EF71 (IM-100) in off-mode charging and
 * recovery, on the LP5523 that drives the front indicator.
 *
 * The mainline LP5523 driver applies each channel brightness as it is
 * written; the low battery blink toggles the channels itself.
 */

#include <cutils/klog.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LOG_TAG "charger_led"
#define LOG_ERROR(x...) KLOG_ERROR(LOG_TAG, x)
#define LOG_INFO(x...) KLOG_INFO(LOG_TAG, x)

#ifdef __ANDROID_RECOVERY__
#define UPDATE_INTERVAL_SEC 5
#else
#define UPDATE_INTERVAL_SEC 10
#endif

#define BAT_CAPACITY_PATH "/sys/class/power_supply/battery/capacity"
#define BAT_STATUS_PATH "/sys/class/power_supply/battery/status"
#define LP5523_CHANNEL_PATH "/sys/class/leds/lp5523:channel%d/brightness"

#define LOW_BATTERY_LEVEL 15
#define LED_BRIGHTNESS 0x40

enum lp5523_channel {
    LEFT_GREEN = 0,
    LEFT_BLUE = 1,
    RIGHT_GREEN = 2,
    RIGHT_BLUE = 3,
    LEFT_RED = 6,
    RIGHT_RED = 7,
};

enum led_mode { MODE_OFF, MODE_SOLID, MODE_BLINK };

struct led_state {
    int red;
    int green;
    int blue;
    enum led_mode mode;
};

static bool write_channel(int channel, int value) {
    char path[64];
    char buf[8];
    int fd, len;
    ssize_t ret;

    snprintf(path, sizeof(path), LP5523_CHANNEL_PATH, channel);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        LOG_ERROR("Failed to open %s\n", path);
        return false;
    }
    len = snprintf(buf, sizeof(buf), "%d\n", value);
    ret = write(fd, buf, (size_t)len);
    close(fd);
    return ret == len;
}

static bool write_color(int red, int green, int blue) {
    bool ok = true;

    ok &= write_channel(LEFT_RED, red);
    ok &= write_channel(LEFT_GREEN, green);
    ok &= write_channel(LEFT_BLUE, blue);
    ok &= write_channel(RIGHT_RED, red);
    ok &= write_channel(RIGHT_GREEN, green);
    ok &= write_channel(RIGHT_BLUE, blue);
    return ok;
}

static bool set_led(const struct led_state* state, bool on) {
    if (state->mode == MODE_OFF || (state->mode == MODE_BLINK && !on))
        return write_color(0, 0, 0);
    return write_color(state->red, state->green, state->blue);
}

static bool read_file(const char* path, char* buf, size_t size) {
    int fd;
    ssize_t len;

    fd = open(path, O_RDONLY);
    if (fd < 0) return false;
    len = read(fd, buf, size - 1);
    close(fd);
    if (len <= 0) return false;
    buf[len] = '\0';
    buf[strcspn(buf, "\n")] = '\0';
    return true;
}

static struct led_state wanted_led(void) {
    struct led_state led = {0, 0, 0, MODE_OFF};
    char status[32], capacity_str[8];
    int capacity;

    if (!read_file(BAT_STATUS_PATH, status, sizeof(status)) ||
        !read_file(BAT_CAPACITY_PATH, capacity_str, sizeof(capacity_str))) {
        LOG_ERROR("Failed to read the battery state\n");
        return led;
    }
    capacity = atoi(capacity_str);

    if (!strcmp(status, "Full") || (!strcmp(status, "Charging") && capacity >= 100)) {
        led.green = LED_BRIGHTNESS;
        led.mode = MODE_SOLID;
    } else if (!strcmp(status, "Charging")) {
        led.red = LED_BRIGHTNESS;
        led.mode = capacity <= LOW_BATTERY_LEVEL ? MODE_BLINK : MODE_SOLID;
    }
    return led;
}

int main(void) {
    struct led_state current = {0, 0, 0, MODE_OFF};
    bool applied = false, on = true;
    int tick = 0;

    while (true) {
        if (tick++ % UPDATE_INTERVAL_SEC == 0) {
            struct led_state led = wanted_led();

            if (!applied || memcmp(&led, &current, sizeof(led))) {
                LOG_INFO("LED r=%d g=%d b=%d mode=%d\n", led.red, led.green, led.blue,
                         led.mode);
                current = led;
                applied = false;
                on = true;
            }
        }

        // Blink at 1 s on, 1 s off; set a steady color once
        if (current.mode == MODE_BLINK || !applied) {
            if (set_led(&current, on)) applied = true;
            on = !on;
        }
        sleep(1);
    }
    return 0;
}
