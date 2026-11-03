LOCAL_PATH := $(call my-dir)

# QCOM_SOONG_NAMESPACE stands for path of display subdir here
ifeq ($(QCOM_SOONG_NAMESPACE),$(LOCAL_PATH))
include $(call all-makefiles-under,$(LOCAL_PATH))
endif
