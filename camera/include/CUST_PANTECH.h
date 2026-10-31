#ifndef CUST_PANTECH_H
#define CUST_PANTECH_H

#define CONFGI_EV10  0
#define CONFIG_PT10  10
#define CONFIG_PT20  12
#define CONFIG_WS10  20
#define CONFIG_WS20  22
#define CONFIG_TP10  30
#define CONFIG_TP20  32

#include "BOARD_VER.h"

/******************************************************************************
 * Conditional ON/OFF Feature                                                 *
 * If you use this feature, you must confirm that build completion,           *
 * when feature was enabled or disabeld.                                      *
 * 1. FEATURE_PANTECH_ERR_CRASH_LOGGING                                       *
 * 2. FEATURE_PANTECH_RAWDATA_ACCESS                                          *
 * 3. FEATURE_PANTECH_QMI_SERVER                                              *
 * 4. FEATURE_PANTECH_TESTMENU_SERVER_VER2                                    *
 * ****************************************************************************/

/*******************************************************************************
 * PANTECH LOG SYSTEM - related Debug System (LS1)
 * ****************************************************************************/
#define FEATURE_PANTECH_ERR_CRASH_LOGGING

/*******************************************************************************
**  SKY_RAW_DATA - related SkyRawData Service (LS1)
*******************************************************************************/
#define FEATURE_PANTECH_RAWDATA_ACCESS

/*******************************************************************************
**  SKY_QMI_SERVICE - related QMI service (LS1)
*******************************************************************************/
#define FEATURE_PANTECH_QMI_SERVER

/*******************************************************************************
**  SKY TEST MENU Socket Service - related pantech_server (LS1)
*******************************************************************************/
#define FEATURE_PANTECH_TESTMENU_SERVER_VER2

/*******************************************************************************
**  FACTORY_COMMAND
*******************************************************************************/
#define PANTECH_DIAG_MSECTOR

#define CONFIG_PANTECH

/*******************************************************************************
**  SNS
*******************************************************************************/
#include "CUST_PANTECH_SENSOR.h"

/*******************************************************************************
**  WLAN
*******************************************************************************/
#include "CUST_PANTECH_WLAN.h"

/*******************************************************************************
**  Bluetooth
*******************************************************************************/
#include "CUST_PANTECH_BLUETOOTH.h" // 141202 p12602: BT features were moved to CUST_PANTECH_BLUETOOTH.h

#include "CUST_PANTECH_SIO.h"

/*******************************************************************************
** RF Feature
*******************************************************************************/
#define F_PANTECH_RF       // pantech rf qxdm message

/*******************************************************************************
**  Display
*******************************************************************************/
#include "CUST_PANTECH_DISPLAY.h"

/*******************************************************************************
**  PDL
*******************************************************************************/
#include "CUST_PANTECH_PDL.h"

/*******************************************************************************
**  GOTA
*******************************************************************************/
#include "CUST_PANTECH_GOTA.h"
#define FEATURE_PANTECH_GOTA_BACKUP_CODE

/*******************************************************************************
**  P12554 Codec
*******************************************************************************/
#include "CUST_PANTECH_MMP.h"
/*******************************************************************************
**  Sound
*******************************************************************************/
#include "CUST_PANTECH_SOUND.h"

/*******************************************************************************
**  Camera
*******************************************************************************/
#include "CUST_PANTECH_CAMERA.h"

/******************************************************************************
**  Touch/HS Feature
******************************************************************************/
#if defined(T_EF71S) || defined(T_EF71IE) || defined(T_EF71K)
#define FEATURE_PAN_WHEEL_VELOCITY // BS2 Touch/HS - For Pantech wheel velocity
//#define FEATURE_DEBUG_PAN_WHEEL_VELOCITY // BS2 Touch/HS - For Pantech wheel velocity debugging
#endif

/*******************************************************************************
**  FS
*******************************************************************************/
#include "CUST_PANTECH_FS.h"

/*******************************************************************************
**  Touch
*******************************************************************************/
#define  FEATURE_PANTECH_FACTORY_CMD_KEYPRESS

/*******************************************************************************
**  PMIC
*******************************************************************************/
#include "CUST_PANTECH_PMIC.h"

/*******************************************************************************
** Android Patternlock Reset
*******************************************************************************/
#define FEATURE_PANTECH_PATTERN_UNLOCK
#if defined(T_EF71IE)
#define FEATURE_PANTECH_PATTERN_MIN
#endif

/* IMEI Erase Factory Command */
#define FEATURE_FACTORY_IMEI_ERASE

/*******************************************************************************
**  DRM - FEATURE_PANTECH_HOPPIN_DRM
*******************************************************************************/
#include "CUST_PANTECH_DRM.h"

/*******************************************************************************
**  UIM
*******************************************************************************/
#define F_PANTECH_UIM_TESTMENU
#define F_PANTECH_UIM_CLK_3_84MHZ

/*******************************************************************************
** PVS VALUE
*******************************************************************************/
#define FEATURE_PANTECH_DDR_DIVICE_INFO

#define FEATURE_PANTECH_SYS_FACTORY_CMD

/*******************************************************************************
 **  PANTECH ROOTING CHECK
*******************************************************************************/
#define F_PANTECH_OEM_ROOTING
#define F_PANTECH_ADB_ROOT
// 130905 LS1-JHM modified :secure boot(F_PANTECH_SECBOOT)
// $$ CAUTION : DO NOT CHANGE BELOW CODES ! THESE ARE CONTROLED BY BUILD SCRIPT
#define F_PANTECH_SECBOOT
//#define FEATURE_PANTECH_DXHDCP_PROVISIONING

/*******************************************************************************
** BS3-CF,FW_VENDOR_FOR_AOT_VIDEO_APP
** API support for AOT 
*******************************************************************************/
#define FEATURE_PANTECH_MMP_SUPPORT_AOT

//P11557@YJLEE
#include "CUST_PANTECH_WIFI.h"

#ifdef T_SKY_MODEL_TARGET_COMMON
#include "cust_sky_cp_linux.h"

#include "cust_sky_ds_linux.h"
#endif/* T_SKY_MODEL_TARGET_COMMON */

#endif/* CUST_PANTECH_H */

