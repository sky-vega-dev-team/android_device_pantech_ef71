LOCAL_PATH := $(call my-dir)

# The Lineage APN list with the initial attach APN of the Korean VoLTE
# carriers set to the IMS APN, bind mounted over it by init.qcom.rc
include $(CLEAR_VARS)

LOCAL_MODULE := ef71_apns-conf.xml
LOCAL_MODULE_CLASS := ETC
LOCAL_VENDOR_MODULE := true

include $(BUILD_SYSTEM)/base_rules.mk

EF71_APNS_SRC := vendor/lineage/prebuilt/common/etc/apns-conf.xml

$(LOCAL_BUILT_MODULE): $(EF71_APNS_SRC) $(LOCAL_PATH)/Android.mk
	@mkdir -p $(dir $@)
	$(hide) sed -e '/carrier="KT IA" mcc="450" mnc="08"/s/ apn="[^"]*"/ apn="ims"/' \
	    -e '/carrier="LG U+ IA" mcc="450" mnc="06"/s/ apn="[^"]*"/ apn="ims"/' \
	    $< > $@.tmp
	$(hide) grep -q 'carrier="KT IA" mcc="450" mnc="08" apn="ims"' $@.tmp
	$(hide) grep -q 'carrier="LG U+ IA" mcc="450" mnc="06" apn="ims"' $@.tmp
	$(hide) mv $@.tmp $@
