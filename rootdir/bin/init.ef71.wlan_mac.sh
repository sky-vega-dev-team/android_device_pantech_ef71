#! /vendor/bin/sh
#
# SPDX-License-Identifier: Apache-2.0
#
# wcn36xx leaves the MAC address zero unless the bootloader passes one in
# the device tree, which the Pantech aboot does not. Derive a stable,
# locally administered address from the serial number instead, the way
# the Bluetooth address is derived.

for i in $(seq 1 60); do
    [ -e /sys/class/net/wlan0/address ] && break
    sleep 0.5
done

[ "$(cat /sys/class/net/wlan0/address)" = "00:00:00:00:00:00" ] || exit 0

serial=$(getprop ro.boot.serialno)
mac=$(printf '02%010s' "$serial" | tr ' ' '0' | cut -c1-12 | sed 's/\(..\)/\1:/g; s/:$//')

ifconfig wlan0 down
ifconfig wlan0 hw ether "$mac"
