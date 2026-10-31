#ifndef CUST_PANTECH_BLUETOOTH_H
#define CUST_PANTECH_BLUETOOTH_H

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====

               CUST_PANTECH_BLUETOOTH.h

DESCRIPTION

Copyright (c) 2014 by  Pantech All Rights Reserved.

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*======================================================================
                        EDIT HISTORY FOR MODULE

   when           who                          what,where,why
------------  ---------------     -------------------------------------------------
2014-11-12      im.heera[LS4]              Create for BLUETOOTH Defines
2014-12-02      jeong.ungbi[LS4]           Modify for LP
2015-12-04      jeong.ungbi[BS2]           Modify for MM
========================================================================*/

/*******************************************************************************
**  TEST_MENU & FACTORY_COMMAND (BLUETOOTH Common Feature) [WCN36x0]
*******************************************************************************/

#define FEATURE_PANTECH_BT_PROCESS_CMD

#define FEATURE_PANTECH_BT_TESTMENU
/* File Name   : 
   Description : BLUETOOTH TEST_MENU & FACTORY_COMMAND */

// [FEATURE_PANTECH_BT_CLASSIC_DUT_MODE]
/* File Name   : frameworks/base/core/java/android/bluetooth/IBluetooth.aidl
                 frameworks/base/core/java/android/bluetooth/BluetoothAdapter.java
                 packages/apps/Bluetooth/src/com/android/bluetooth/btservice/AdapterService.java
                 packages/apps/Bluetooth/jni/com_android_bluetooth_btservice_AdapterService.cpp
   Description : Bluetooth Classic DUT mode */

//[Removed]#define FEATURE_PANTECH_BT_SSP_DEBUG_BDROID
/* File Name   : 
   Description : SSP debug for Bluedroid 
                 Discard SSP debug because of remove 2.1- feature in HCI from MM */

/*******************************************************************************
**  BLUETOOTH PANTECH Qcom CR Patch Feature
*******************************************************************************/
#define FEATURE_PANTECH_BT_QCOM_CR_HFP_PTS
/* File Name   : system/bt/bta/ag/bta_ag_cmd.c
   Description : [HFP_AG_SLC_BV_10_I] If PTS does not support HFP 1.7, IUT reports  IUT's HFP version as 1.7*/

/* File Name   : system/bt/stack/sdp/sdp_server.c
   Description : [IOPT_SDAS_03] If PTS does not support HFP 1.7, IUT reports  IUT's HFP version as 1.7*/

#define FEATURE_PANTECH_BT_QCOM_CR_HSP_PTS
/* File Name   : system/bta/ag/bta_ag_cmd.c
   Description : [All TC] HSP AG can send ring cmd even if there is no MT call setup  */

//#define FEATURE_PANTECH_BT_QCOM_CR_HID_NAME_HANGEUL
/* File Name   : system/btif/src/btif_hh.c
   Description : [Case#02406001] Input reader in system server is died during HID PTS test */
   
/*******************************************************************************
**  BLUETOOTH PANTECH Android Security Patch Feature
*******************************************************************************/
#define FEATURE_PANTECH_BT_ANDROID_SECURITY_PATCH 
/* File Name   : system/bt/include/bt_target.h
				 system/bt/stack/btm/btm_int.h
				 system/bt/stack/btm/btm_sec.c
   Description : [2016.03][ANDROID-26551752][PATCH] DO NOT MERGE Remove Porsche car-kit pairing workaround */

/*******************************************************************************
**  BLUETOOTH PANTECH SeLinux
*******************************************************************************/
// [FEATURE_PANTECH_BT_ANDROID_SELINUX]
/* File Name   : device/qcom/sepolicy/pantech/pantech_common.te
   Description : # Read/Write BDADDR: hci_qcomm_init
				 # BT LE RF Test Mode: wdsdaemon  */
				 
/*******************************************************************************
**  BLUETOOTH PANTECH Specific Feature
*******************************************************************************/

//#if defined(T_EF63S) || defined(T_EF63K) || defined(T_EF63L) || defined(T_EF65S)
#define FEATURE_PANTECH_BT_WCN_SPECIFIC
/* Caution!    : Check BT soc type by model name
   Description : Bluetooth chip is WCN */
//#endif

//#if defined(T_EF67S) || defined(T_EF67K) || defined(T_EF67L) 
//#define FEATURE_PANTECH_BT_QCA_SPECIFIC
/* Caution!    : Check BT soc type by model name
   Description : Bluetooth chip is QCA */
//#endif

#define FEATURE_PANTECH_BT_BDROID_MAX_LOG_LEVEL
/* File Name   : system/bt/conf/bt_stack_eng.conf
                 system/bt/conf/Android.mk
				 system/bt/main/Stack_config.c
				 system/bt/main/Android.mk
				 system/bt/audio_a2dp_hw/Audio_a2dp_hw.c --> for hiding repeated logs, "out_get_format" & "out_get_channels"
   Description : Set max log level of bluedroid for printing additional debug message */
   
#define FEATURE_PANTECH_BLUETOOTH_A2DP_ENABLED
/* File Name   : system/core/init/property_service.cpp
                 packages/apps/Bluetooth/src/com/android/bluetooth/a2dp/A2dpStateMachine.java
   Description : 20140121 pooyi check A2DP connected and play state. */

#define FEATURE_PANTECH_BT_AVRCP_ABS_VOL_DISABLE
/* File Name   : system/bt/btif/src/btif_rc.c
   Description : Use AVRCP 1.6, however, do not use Absolute volume.
                 Remove 'BTRC_FEAT_ABSOLUTE_VOLUME' feature */

#define FEATURE_PANTECH_BT_LOAD_NAME_BY_MODEL
/* File Name   : system/bt/btif/src/btif_dm.c
   Description : //20131219 LS4 KSCHOI, Device Name is Loaded from ro.product.model */
   
// [FEATURE_PANTECH_BT_SUPPORT_PROFILES]
/* File Name   : packages/apps/Bluetooth/res/values/config.xml
                 vendor/qcom/opensource/bluetooth/res/values/config.xml
				 device/qcom/common/rootdir/etc/init.qcom.bt.sh
				 device/qcom/common/device/overlay/packages/apps/Bluetooth/res/values/config.xml				 
   Description : Not support MAP, DUN, SAP */


/*******************************************************************************
**  BLUETOOTH  region specific Feature (domestic/abroad)
*******************************************************************************/
#if defined(T_EF71IE)   //abroad
#endif

#if defined(T_EF71S) || defined(T_EF71K)    //domestic
#define FEATURE_PANTECH_BT_HFP_CHANGE_CHLD
/* File Name   : system/bt/bta/ag/bta_ag_cfg.c
                 system/bt/include/bt_target.h
   Description : Discard CHLD=3 for domestic network */
   
#define FEATURE_PANTECH_BT_HFP_DISABLE_VREC
/* File Name   : system/bt/btif/src/Btif_hf.c
   Description : Disable Voice recognition feature for domestic network */
   
#endif
   
/*******************************************************************************
**  BLUETOOTH WCN36X0 specific Feature
*******************************************************************************/
#ifdef FEATURE_PANTECH_BT_WCN_SPECIFIC

//#if defined(T_EF63S) || defined(T_EF63K) || defined(T_EF63L) || defined(T_EF65S)
//#define FEATURE_PANTECH_BT_WCN_RF_POWER       ==> Temporary disabled, check it after testing EF71IE RF test
/* File Name   : vendor/qcom/proprietary/bt/hci_qcomm_init/btqsocnvmtags.c
   Description : modify BT RF Power for WCN */
//#endif

#define FEATURE_PANTECH_BT_WCN_BDADDR_FROM_BACKUP_AREA
/* File Name   : vendor/qcom/proprietary/bt/hci_qcomm_init/bthci_qcomm_linux.h
				 vendor/qcom/proprietary/bt/hci_qcomm_init/bthci_qcomm_linux.cpp
				 vendor/qcom/proprietary/bt/hci_qcomm_init/Android.mk
   Description : Read from backup area and write bdaddr to backup area if it isn't exist */
         
#endif // FEATURE_PANTECH_BT_WCN_SPECIFIC

/*******************************************************************************
**  BLUETOOTH QCA6174 specific Feature
*******************************************************************************/
#ifdef FEATURE_PANTECH_BT_QCA_SPECIFIC

#define FEATURE_PANTECH_BT_QCA_RF_POWER
/* File Name   : hardware/qcom/bt/libbt-vendor/src/hw_rome.c
   Description : modify BT RF Power for QCA */

#define FEATURE_PANTECH_BT_QCA_BDADDR_FROM_BACKUP_AREA
/* File Name   : hardware/qcom/bt/libbt-vendor/include/bt_vendor_qcom.h
                 hardware/qcom/bt/libbt-vendor/src/bt_vendor_qcom.c
				 hardware/qcom/bt/libbt-vendor/Android.mk
   Description : Read from backup area and write bdaddr to backup area if it isn't exist */

#define FEATURE_PANTECH_BT_QCA_NOTI_SSR_TO_USER
/* File Name   : vendor/qcom/proprietary/bt/hci_qcomm_init/wcnss_filter/src/bt_qxdmlog.c
   Description : enable BT SSR instead of BT Kernel Panic 
                 incomplted because of change of structure*/

#endif // FEATURE_PANTECH_BT_QCA_SPECIFIC

#endif //CUST_PANTECH_BLUETOOTH_H
