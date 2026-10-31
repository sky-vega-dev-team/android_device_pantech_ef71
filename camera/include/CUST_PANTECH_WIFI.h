#ifndef CUST_PANTECH_WIFI_H
#define CUST_PANTECH_WIFI_H

/* ========================================================================

FILE: CUST_PANTECH_WIFI.h

Copyright (c) 2014 by PANTECH Incorporated.  All Rights Reserved.

=========================================================================== */

/*===========================================================================

                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when      who       what, where, why
--------  ---      ----------------------------------------------------------
20141126  skhan    Initial relase for LP

===========================================================================*/

/* ALL CUSTOMIZED CODES ARE UNDER FEATURE_PS_WIFI */
#define FEATURE_PS_WIFI


#ifdef FEATURE_PS_WIFI
/* Getting Device Info */
#define WIFI_DEVICE_INFO          "wlan.ps.devinfo"

/* Getting Feature definition table */
#define WIFI_FEATURE_DEFINITIONS  "wlan.ps.features"

/* Getting realm type
   0 : 3gpp realm
   1 : custom realm */
#define WIFI_REALM_TYPE           "wlan.ps.realmtype"


/* FEATURE FOR INDICATING FEATURE CHECK */
#define WIFI_PS_WIFI_FEATURE_CHECK

/* wifi logging for the debugging*/
#define FEATURE_PS_WIFI_COM_PREF_LOGGING

#ifndef __ASSEMBLY__
#ifndef __ASSEMBLER__
#ifndef _ARM_ASM_
#ifndef DAL_BOOT_IMAGE_SBL1
#ifndef DAL_BOOT_IMAGE_SBL2
#ifndef CUSTAAAAANAZA_H
#ifndef TARGAAAAANAZA_H
#ifndef BUILD_MSM_MODEM
/*====================================================================================

  HOW TO CHECK A FEATURE AT THE REST OF WPA_SUPPLICANT CODES
  ----------------------------------------------------------

  1) Copy below function and paste anywhere you want.

      Code)
        static int CHECK_FEATURE( int f )
        {
        	static int bInit = 0;
        	static char features[92]; //PROP_VALUE_MAX

        	if( f>WIFI_FEATURE_MAX ) return 0;
        	if( bInit==0 );
        	{
        		memset( features, 0, sizeof(features) );
        		property_get(WIFI_FEATURE_DEFINITIONS, features, "");
        		bInit = 1;
        	}

        	return (features[f]=='1') ? 1 : 0 ;
        }


  2) Call the function with a parmeter which the feature you want to check.

      Example)
        if( CHECK_FEATURE(FEATURE_STA_BUGFIX1) ) {
              :

  3) Might be better to use "#ifdef WIFI_PS_WIFI_FEATURE_CHECK" before 1) 2)
     and "#endif" after them.

====================================================================================*/
#if 0
typedef enum  {
    /*--------------------------------------------------------------------------------------
      BELOWS ARE SET DIFFERENTLY BY MODELS OR VENDORS.
      MEMORY SHOULD BE ALLOCATED TO SET FLAGS CORRESPONDING BELOW FEATURES BY CONDITIONS.

      [ NAMING RULES FOR WIFI FEATURE DEFINITION ]
       Format : FEATAURE_[MODULE]_[FUNCTION(s)]_[DESCRIPTION]
       1) Add Prefix : FEATURE_
       2) Define module name : One of COM, STA, P2P, MHS.
       3) Add function names : One(or more) of QPATCH, PERF, ADDON, TEST, BUGFIX,
                               AUTH, SYS, REQ.
       4) Add detail description : Add your feature name for new feature.
    --------------------------------------------------------------------------------------*/
    //-> START OF DEFINISTION
    FEATURE_STA_AAADDDD34,                                    /*  3 */
    FEATURE_STA_AAADDDD35,                                    /*  4 */
    FEATURE_STA_AAADDDD36,                                    /*  5 */
    FEATURE_STA_AAADDDD37,                                    /*  6 */

    // <- END OF DEFINITION : DEF_MAX SHOULD BE UNDER 90
    WIFI_FEATURE_MAX
} WifiFeature;
#endif

#endif /* BUILD_MSM_MODEM */
#endif /* #ifndef TARGAAAAANAZA_H */
#endif /* #ifndef CUSTAAAAANAZA_H */
#endif /* #ifndef DAL_BOOT_IMAGE_SBL2 */
#endif /* #ifndef DAL_BOOT_IMAGE_SBL1 */
#endif /* #ifndef _ARM_ASM_ */
#endif /* #ifndef __ASSEMBLER__ */
#endif /* #ifndef __ASSEMBLY__ */

/**************************************************************/
/**************** DOMESTIC FEATURE (Value : 1 ~ 49)****************/
#define FEATURE_PS_WIFI_DOMESTIC 1
/**************************************************************/
/* check poor internet connection */
#define FEATURE_PS_WIFI_STA_ADDON_POOR_NETWORK FEATURE_PS_WIFI_DOMESTIC+1

#define FEATURE_PS_WIFI_MHS_ADDON_ADVANCED_SETTING FEATURE_PS_WIFI_DOMESTIC+2

#define FEATURE_PS_WIFI_STA_AUTH_EAPAKA_MANAGE_EAP_FAILURE FEATURE_PS_WIFI_DOMESTIC+3

/* REDUCE_ACTION_DEVICE_IDLE_TIME */
#define FEATURE_PS_WIFI_STA_PERF_REDUCE_ACTION_DEVICE_IDLE_TIME FEATURE_PS_WIFI_DOMESTIC+4

#define FEATURE_PS_WIFI_STA_ADDON_EAP_STEP_DEBUG_MSG FEATURE_PS_WIFI_DOMESTIC+5

#define FEATURE_PS_WIFI_COM_SYS_OS_GROUP_ADD_RADIO FEATURE_PS_WIFI_DOMESTIC+6

/*Blackbox Debugging*/
#define FEATURE_PS_WIFI_COM_PREF_BLACKBOX FEATURE_PS_WIFI_DOMESTIC+7

/* ADD_EAP_METHODS */
#define FEATURE_PS_WIFI_STA_AUTH_ADD_EAP_METHODS FEATURE_PS_WIFI_DOMESTIC+8

#define FEATURE_PS_WIFI_STA_TEST_WLAN_CONFIG FEATURE_PS_WIFI_DOMESTIC+9

#define FEATURE_PS_WIFI_STA_CONNECTED_TOAST FEATURE_PS_WIFI_DOMESTIC+10

#define FEATURE_PS_WIFI_STA_AUTH_ADD_EAP_METHODS_FAST FEATURE_PS_WIFI_DOMESTIC+11

#define FEATURE_PS_WIFI_STA_BUGFIX_TURN_ON_WIFI_BUTTON_IN_SCANONLYMODE FEATURE_PS_WIFI_DOMESTIC+12

#define FEATURE_PS_WIFI_COM_WIFI_CONNECTED_CHECK FEATURE_PS_WIFI_DOMESTIC+13

#define FEATURE_PS_WIFI_STA_ADDON_MDM_POLICY_WHITE_LIST FEATURE_PS_WIFI_DOMESTIC+14

/* bss_expiration_scan_count : 2->1 */
#define FEATURE_PS_WIFI_STA_PERF_BSS_EXPIRATION_SCAN_COUNT_CHANGE FEATURE_PS_WIFI_DOMESTIC+15

/* The scan result of Empty SSID was not received in framework */
#define FEATURE_PS_WIFI_STA_BUGFIX_GET_SCAN_RESULT_NO_EMPTY_SSID FEATURE_PS_WIFI_DOMESTIC+16

#define FEATURE_PS_WIFI_COM_SYS_SIM_CHANGED FEATURE_PS_WIFI_DOMESTIC+17

/* restart supplicant when changing to SCAN_ONLY_WITH_WIFI_OFF_MODE from CONNECT_MODE */
#define FEATURE_PS_WIFI_STA_PERF_RESTART_SUPPLICANT_WHEN_CHANGE_TO_SCANONLYMODE FEATURE_PS_WIFI_DOMESTIC+18

/* when entered incorrect WEP key, it will reduce the retry count of dhcp fail */
#define FEATURE_PS_WIFI_STA_ADDON_WEP_AUTH_FAIL_REDUCE_RETRY_COUNT FEATURE_PS_WIFI_DOMESTIC+19

/* when entered incorrect WPA/WPA2 key, it will show the password pop-up */
#define FEATURE_PS_WIFI_STA_ADDON_WPA_PSK_AUTH_FAIL_POPUP FEATURE_PS_WIFI_DOMESTIC+20

/* P2P-DEVICE-FOUND - if device name has euc-kr, we convert to utf-8 */
#define FEATURE_PS_WIFI_P2P_ADDON_PEER_DEVICE_NAME_ENCODING_UTF8 FEATURE_PS_WIFI_DOMESTIC+21

/* NFC WIFI TAG - if ssid has euc-kr, we convert to utf-8 */
#define FEATURE_PS_WIFI_STA_ADDON_NFC_TAG_SSID_ENCODING_UTF8 FEATURE_PS_WIFI_DOMESTIC+22

/* SKT_KT ANQP GET & INTERWORKING CONNECT FOR PASSPOINT*/
#define FEATURE_PS_WIFI_STA_REQ_SKT_KT_PASSPOINT FEATURE_PS_WIFI_DOMESTIC+23

/* SKT_KT DUALBAND */
#define FEATURE_PS_WIFI_STA_REQ_SKT_KT_DUALBAND FEATURE_PS_WIFI_DOMESTIC+24

/* FIX MEMRORY LEAK */
#define FEATURE_PS_WIFI_STA_BUGFIX_MEMORY_LEAK FEATURE_PS_WIFI_DOMESTIC + 25

#define FEATURE_PS_WIFI_STA_FIX_EAP_FAIL_DUE_TO_LOST_NETWORK FEATURE_PS_WIFI_DOMESTIC + 26

#define FEATURE_PS_WIFI_STA_ADDON_HS20_TEMPORARY_ITEM FEATURE_PS_WIFI_DOMESTIC + 27

#define FEATURE_PS_WIFI_STA_BUGFIX_REMOVE_DUP_WPS_NETWORK FEATURE_PS_WIFI_DOMESTIC+ 28

#define FEATURE_PS_WIFI_STA_ADDON_IGNORE_AUTOJOIN_WRONG_KEY_SSID FEATURE_PS_WIFI_DOMESTIC + 29

#define FEATURE_PS_WIFI_STA_PERF_ENABLE_TIMED_OUT_AP FEATURE_PS_WIFI_DOMESTIC + 30


/***************************************************************/
/****************** SKT FEATURE (Value : 50 ~ 99)******************/
#define FEATURE_PS_WIFI_SKT 50
/***************************************************************/
#define FEATURE_PS_WIFI_STA_PERF_SKT_PASSPOINT FEATURE_PS_WIFI_SKT+1

#define FEATURE_PS_WIFI_STA_REQ_SKT_HS20_BSS_STATUS FEATURE_PS_WIFI_SKT +2

#define FEATURE_PS_WIFI_STA_SKT_PASSPOINT_FOR_TEMP_NETWORK FEATURE_PS_WIFI_SKT+3

#define FEATURE_PS_WIFI_STA_SKT_PASSPOINT_CALCULATION_CAPACITY FEATURE_PS_WIFI_SKT+4

#define FEATURE_PS_WIFI_STA_SKT_PASSPOINT_CHECK_VENDOR_SPECIFIC FEATURE_PS_WIFI_SKT+5

#define FEATURE_PS_WIFI_STA_REQ_SKT_PASSPOINT_REQUIREMENT FEATURE_PS_WIFI_SKT+6

#define FEATURE_PS_WIFI_STA_PERF_SKT_CRED_INFO_CHANGE FEATURE_PS_WIFI_SKT+7

#define FEATURE_PS_WIFI_STA_REQ_SKT_TSTART_SCAN FEATURE_PS_WIFI_SKT+8


/***************************************************************/
/****************** KT FEATURE (Value : 100 ~ 149)******************/
#define FEATURE_PS_WIFI_KT 100
/***************************************************************/
#define FEATURE_PS_WIFI_STA_REQ_KT_5GHZ_PRIORITY_CONNECTION FEATURE_PS_WIFI_KT+1

#define FEATURE_PS_WIFI_STA_REQ_KT_ADD_DHCP_OPTION FEATURE_PS_WIFI_KT+2

#define FEATURE_PS_WIFI_STA_REQ_KT_MANUAL_CONNECTION FEATURE_PS_WIFI_KT+3

#define FEATURE_PS_WIFI_STA_REQ_KT_GET_SCAN_RESULT_FOR_KTCM FEATURE_PS_WIFI_KT+4

#define FEATURE_PS_WIFI_STA_REQ_KT_DISCONNECTION_PROPRITY FEATURE_PS_WIFI_KT+5

/*  EAP-AKA AT_NOTIFICATION GENERAL FAILURE AFTER AUTH for sending to the WifiMonitor */
#define FEATURE_PS_WIFI_STA_REQ_KT_EAPAKA_AT_NOTIFICATION_EAP_SIM_GENERAL_FAILURE_AFTER_AUTH FEATURE_PS_WIFI_KT+6

/*  EAP-AKA AT_NOTIFICATION GENERAL FAILURE BEFORE AUTH for sending to the WifiMonitor */
#define FEATURE_PS_WIFI_STA_REQ_KT_EAPAKA_AT_NOTIFICATION_EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH FEATURE_PS_WIFI_KT+7

/* EAP-AKA UMTS AUTH FAILED AUTN INCORRECT MAC for sending to the WifiMonitor */
#define FEATURE_PS_WIFI_STA_REQ_KT_EAPAKA_UMTS_AUTHENTICATION_FAILED_AUTN_INCORRECT_MAC FEATURE_PS_WIFI_KT+8

#define FEATURE_PS_WIFI_STA_REQ_KT_EAPAKA_ALGORITHM_MISMATCH FEATURE_PS_WIFI_KT+9

#define FEATURE_PS_WIFI_STA_REQ_KT_EAPAKA_AT_CHECK_CODE_AT_RESULT_IND FEATURE_PS_WIFI_KT+10

#define FEATURE_PS_WIFI_STA_REQ_KT_EAPAKA_UMTS_AUTHENTICATION_FAILED_CM_ERROR_MEMORY_PROBLEM FEATURE_PS_WIFI_KT+11

#define FEATURE_PS_WIFI_STA_REQ_KT_CHECK_KTCM_IS_RUNNING FEATURE_PS_WIFI_KT+12

#define FEATURE_PS_WIFI_STA_ADDON_KT_RSSI_THRESHOLD FEATURE_PS_WIFI_KT+13

#define FEATURE_PS_WIFI_STA_REQ_KT_CHECK_GIGA_AP FEATURE_PS_WIFI_KT+14

/* EAP-AKA UMTS AUTH AT_NOTIFICATION EAP_SIM_SUCCESS for sending to the WifiMonitor */
#define FEATURE_PS_WIFI_STA_KT_AUTH_EAPAKA_NOTIFICATION_EAP_SIM_SUCCESS FEATURE_PS_WIFI_KT+15

#define FEATURE_PS_WIFI_STA_REQ_KT_CAPTIVE_PORTAL FEATURE_PS_WIFI_KT+16

#define FEATURE_PS_WIFI_STA_REQ_KT_KTCM_AUTO_SCAN FEATURE_PS_WIFI_KT+17

#define FEATURE_PS_WIFI_STA_REQ_KT_POOR_INTERNET FEATURE_PS_WIFI_KT+18

#define  FEATURE_PS_WIFI_STA_REQ_KT_OEM_NOTIFICATION FEATURE_PS_WIFI_KT + 19

/***************************************************************/
/***************** LGU FEATURE (Value : 150 ~ 199)*****************/
#define FEATURE_PS_WIFI_LGU 150
/***************************************************************/
#define FEATURE_PS_WIFI_STA_REQ_LGU_EAPAKA_IDENTITY_INITIALIZE FEATURE_PS_WIFI_LGU+1

/* LGU+ toast msg */
#define FEATURE_PS_WIFI_STA_REQ_LGU_TOAST_MESSAGE FEATURE_PS_WIFI_LGU+2

/*Store that the history of WiFi connection in the DB (success or fail) */
#define FEATURE_PS_WIFI_STA_REQ_LGU_DB FEATURE_PS_WIFI_LGU+3

/* EAP-AKA Authentication Fail Notification by Unregistered USIM */
#define FEATURE_PS_WIFI_STA_REQ_LGU_EAPAKA_FAIL_NOTIFICATION FEATURE_PS_WIFI_LGU+4

/*LGU+ CONNECTION LOG To describe reason of connection fail */
#define FEATURE_PS_WIFI_STA_REQ_LGU_CONNECTION_FAIL_LOG FEATURE_PS_WIFI_LGU+5


/***************************************************************/
/**************** OTHERS FEATURE (Value : 200 ~ 255)****************/
#define FEATURE_PS_WIFI_OTHERS 200
/***************************************************************/


/***************************************************************/
/******************** FEATURE MAX (Value : 256)********************/
#define FEATURE_PS_WIFI_MAX  256
/***************************************************************/
#define WIFI_FEATURE_MAX  FEATURE_PS_WIFI_MAX

/*--------------------------------------------------------------------------------------
  BELOWS ARE ** ALWAYS DEFINED FEATURES **.
  SO, THEY ARE ALL TRUE FOR CONDITIONAL STATEMENTS.
--------------------------------------------------------------------------------------*/
/* Prepare the way for native code operation by external APIs  */
#define FIXED_FEATURE_PS_WIFI_COM_ADDON_NATIVE_INTERFACE  1
/* Detect EUC-KR & convert to UTF-8 automatically */
#define FIXED_FEATURE_PS_WIFI_STA_ADDON_AUTO_CHARSET_ENCODING  1
/* Find hidden ap without taking care of Korean charset */
#define FIXED_FEATURE_PS_WIFI_STA_ADDON_HIDDEN_SSID_IN_KOREAN  1
/* EAP-AKA Prevent to ruin UTF-8 Format about EAP-Notification Message */
#define FIXED_FEATURE_PS_WIFI_STA_AUTH_EAPAKA_BUGFIX_PREVENT_UTF8_FORMAT	1
/* EAP-AKA Not use reauthentication but use Full authentication  */
#define FIXED_FEATURE_PS_WIFI_STA_AUTH_EAPAAKA_SPEC_NOUSE_REAUTHENTICATION  1
/* When config file is written and reboot soon, the file is gone. we must do sync()  */
#define FIXED_FEATURE_PS_WIFI_COM_SYS_CONFIG_FILE_SYNC    1
/* Against invalid operation, we have to support config files initiation */
#define FIXED_FEATURE_PS_WIFI_COM_SYS_CONFIG_FILE_INITIALIZE 1
/* Add-on function that excludes paticular selected APs */
#define FIXED_FEATURE_PS_WIFI_STA_ADDON_SCAN_EXCEPTION_LIST 1
/* Maximize buffer size to contain all scan result as much as the device driver can */
#define FIXED_FEATURE_PS_WIFI_STA_PERF_INCREASE_MAX_SCAN_RESULTS 1
/* Prevent exceptions (including Null Pointer Exception) */
#define FIXED_FEATURE_PS_WIFI_COM_BUGFIX_UNEXPECTED_ERRORS 1
/* Add extra EAP methods(SIM, AKA, FAST, LEAP) */
#define FIXED_FEATURE_PS_WIFI_STA_AUTH_EAP_ADD_EXTRA_METHODS 1
/* Add vedor's default profiles using EAP-AKA method */
#define FIXED_FEATURE_PS_WIFI_STA_AUTH_EAP_ADD_VENDOR_PROFILE 1
/* A feature for debug screen implementation */
#define FIXED_FEATURE_PS_WIFI_STA_TEST_DEBUG_SCREEN 1
/* Expiration time for fast association extended by 10 secs */
#define FIXED_FEATURE_PS_WIFI_STA_PERF_FAST_ASSOCIATION 1
/* Set & Switch REALM for each vendors */
#define FIXED_FEATURE_PS_WIFI_STA_AUTH_SWITCH_EAPAKA_REALM 1

#define FIXED_FEATURE_PS_WIFI_STA_ADDON_CHECK_USIM_BEFORE_AKA_CONN 1

#define FIXED_FEATURE_PS_WIFI_P2P_ADDON_DISCOVER_AFTER_DISCONN 1

#define FIXED_FEATURE_PS_WIFI_STA_PERF_STOP_SCAN_WHEN_SCREEN_OFF 1

#define FIXED_EATURE_PS_WIFI_STA_BUGFIX_CLEAR_PSEUDONYM_IDENEITY 1

#endif/* FEATURE_PS_WIFI */

#endif/* CUST_PANTECH_WIFI_H */

