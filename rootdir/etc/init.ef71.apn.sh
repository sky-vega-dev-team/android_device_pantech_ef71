#! /vendor/bin/sh
#
# Set the modem and the platform up for the inserted SIM.
#
# - VoLTE: the modem cannot load the Korean carrier MBNs, so the IMS settings
#   they carry are kept as per carrier EFS sets and written by ef71_modemcfg
#   when the modem holds another carrier's set. The modem reads them at boot.
# - LG U+: hide the CDMA feature (see init.qcom.rc).
# - Attach: Korean networks attach on the IMS APN, so modem profile 1 has to
#   be "ims" (the modem resets it when the SIM changes).
# - Data: qcril cannot create a profile for RIL_REQUEST_SET_INITIAL_ATTACH_APN
#   (the QDP profile lookup fails), so make sure one exists for the carrier's
#   LTE internet APN.
#
# Changes the modem or system_server only read at boot get one reboot; if a
# reboot did not apply them, leave things as they are instead of looping.

# Vendor domain: only use the vendor toolbox
export PATH=/vendor/bin

DEV=/dev/smd11
MODEM_BUILD='MPSS.JO.1.2.c4-00021-*'
EFS_BACKUP=/data/vendor/radio/ef71_efs_orig.cfg

at_cmd() {
    (sleep 0.5; printf '%s\r' "$1" > $DEV) &
    timeout 3 cat $DEV | tr -d '\r'
    wait
}

imsi=""
for i in 1 2 3 4 5 6 7 8 9 10 11 12; do
    imsi=$(at_cmd AT+CIMI | grep -E '^[0-9]{6,15}$' | head -n 1)
    [ -n "$imsi" ] && break
    sleep 5
done
[ -n "$imsi" ] || exit 0

case "$imsi" in
    45002*|45004*|45008*) carrier=kt; apn=lte.ktfwing.com ;;
    45005*|45011*) carrier=skt; apn=lte.sktelecom.com ;;
    45006*) carrier=lgu; apn=internet.lguplus.co.kr ;;
    *) carrier=other ;;
esac

reboot_for=""

# Modem EFS set for VoLTE, only on the modem build the sets were made on
set=/vendor/etc/ef71_modem/$carrier.cfg
if [ -f $set ]; then
    build=$(ef71_modemcfg version)
    case "$build" in
        $MODEM_BUILD)
            ef71_modemcfg check $set > /dev/null 2>&1
            case $? in
                0) ;;
                1)
                    if [ ! -f $EFS_BACKUP ]; then
                        ef71_modemcfg save $EFS_BACKUP /vendor/etc/ef71_modem/*.cfg ||
                            log -t ef71-apn "could not back up the modem EFS"
                    fi
                    if [ -f $EFS_BACKUP ] && ef71_modemcfg apply $set; then
                        log -t ef71-apn "wrote the $carrier modem EFS set"
                        reboot_for="$reboot_for modem"
                    else
                        log -t ef71-apn "failed to write the $carrier modem EFS set"
                    fi
                    ;;
                *) log -t ef71-apn "could not read the modem EFS" ;;
            esac
            ;;
        *) log -t ef71-apn "modem build '$build' has no EFS sets, leaving it alone" ;;
    esac
fi

# LG U+ cards need the CDMA feature hidden. The feature is read once at boot.
case "$carrier" in
    lgu) hide_cdma=1 ;;
    *) hide_cdma=0 ;;
esac
hidden=1
grep -q 'feature name="android.hardware.telephony.cdma"' \
        /system/etc/permissions/android.hardware.telephony.cdma.xml && hidden=0
setprop persist.vendor.ef71.hide_cdma $hide_cdma
[ "$hidden" = "$hide_cdma" ] || reboot_for="$reboot_for cdma"

# Remember which SIM the last reboot was for: never loop on one that a
# reboot did not fix, but still reboot once for the next SIM change
if [ -z "$reboot_for" ]; then
    setprop persist.vendor.ef71.sim_reboots 0
elif [ "$(getprop persist.vendor.ef71.sim_reboots)" = "$carrier" ]; then
    log -t ef71-apn "still not applied after a reboot:$reboot_for"
else
    log -t ef71-apn "SIM changed, rebooting to apply:$reboot_for"
    setprop persist.vendor.ef71.sim_reboots $carrier
    setprop vendor.ef71.sim_reboot 1
    exit 0
fi

[ -n "$apn" ] || exit 0

restart_ril=0
profiles=$(at_cmd 'AT+CGDCONT?' | grep '^+CGDCONT: ')

# Attach profile for VoLTE carriers
case "$carrier" in
    kt|lgu|skt)
        if ! echo "$profiles" | grep -qi '^+CGDCONT: 1,"IPV4V6","ims",'; then
            if at_cmd 'AT+CGDCONT=1,"IPV4V6","ims"' | grep -q '^OK$'; then
                log -t ef71-apn "set modem profile 1 to ims"
                restart_ril=1
            else
                log -t ef71-apn "failed to set modem profile 1 to ims"
            fi
        fi
        ;;
esac

if ! echo "$profiles" | grep -q "^+CGDCONT: [0-9]*,\"IPV4V6\",\"$apn\","; then
    # Reuse a profile that has the APN with another PDP type, else take a free one
    cid=$(echo "$profiles" | grep "^+CGDCONT: [0-9]*,\"[A-Z0-9]*\",\"$apn\"," | \
            sed -n 's/^+CGDCONT: \([0-9]*\),.*/\1/p' | head -n 1)
    if [ -z "$cid" ]; then
        used=$(echo "$profiles" | sed -n 's/^+CGDCONT: \([0-9]*\),.*/\1/p')
        cid=2
        while echo "$used" | grep -qx "$cid"; do
            cid=$((cid + 1))
        done
    fi
    if [ "$cid" -gt 16 ]; then
        log -t ef71-apn "no free modem profile for $apn"
    elif at_cmd "AT+CGDCONT=$cid,\"IPV4V6\",\"$apn\"" | grep -q '^OK$'; then
        log -t ef71-apn "created modem profile $cid for $apn"
        restart_ril=1
    else
        log -t ef71-apn "failed to create modem profile $cid for $apn"
    fi
fi

# rild resends the initial attach APN when it comes back
[ $restart_ril = 1 ] && setprop ctl.restart ril-daemon
exit 0
