# The global flags the stock Pantech build added to every module
# (build/envsetup.sh chooseboardver -> PANTECH_ANDROID_FLAGS, used by
# build/core/definitions.mk). Pantech sources pick their ef71 code paths from
# T_EF71S, the board revision and the CUST_PANTECH*.h features.
EF71_PANTECH_BUILD_DIR := device/pantech/ef71/camera/include
EF71_PANTECH_FLAGS := \
    -DPROJECT_NAME=\"ef71s\" \
    -DPROJECT_NAME_UPPER=\"EF71S\" \
    -DMODEL_NAME=\"IM-100S\" \
    -DPANTECH_BUILD_VER=\"S0228134\" \
    -DPANTECH_FS_VER=8 \
    -DPANTECH_BOARD_VER=tp20 \
    -DT_EF71S \
    -DPANTECH_SECURE_FS_VER=1 \
    -I$(EF71_PANTECH_BUILD_DIR) \
    -include $(EF71_PANTECH_BUILD_DIR)/CUST_PANTECH.h
