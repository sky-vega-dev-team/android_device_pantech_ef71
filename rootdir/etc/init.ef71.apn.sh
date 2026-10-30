#! /vendor/bin/sh
#
# Make sure the modem has a profile for the carrier's LTE internet APN.
#
# qcril cannot create one for RIL_REQUEST_SET_INITIAL_ATTACH_APN (the QDP
# profile lookup fails), so the modem keeps attaching with the empty-APN
# profile 1 and Korean networks hand out the IMS bearer, where only DNS
# works. Once a matching profile exists qcril accepts the initial attach APN
# and the modem attaches to the internet APN.

# Vendor domain: only use the vendor toolbox
export PATH=/vendor/bin

DEV=/dev/smd11

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

case "$imsi" in
    45002*|45004*|45008*) apn=lte.ktfwing.com ;;
    45005*|45011*) apn=lte.sktelecom.com ;;
    45006*) apn=internet.lguplus.co.kr ;;
    *) exit 0 ;;
esac

profiles=$(at_cmd 'AT+CGDCONT?' | grep '^+CGDCONT: ')
if echo "$profiles" | grep -q "^+CGDCONT: [0-9]*,\"IPV4V6\",\"$apn\","; then
    exit 0
fi

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
    exit 0
fi

if at_cmd "AT+CGDCONT=$cid,\"IPV4V6\",\"$apn\"" | grep -q '^OK$'; then
    log -t ef71-apn "created modem profile $cid for $apn"
    # rild resends the initial attach APN when it comes back
    setprop ctl.restart ril-daemon
else
    log -t ef71-apn "failed to create modem profile $cid for $apn"
fi
