/*
 * =================================================================
 * EDIT HISTORY FOR MODULE

 * This section contains comments describing changes made to the module.
 * Notice that changes are listed in reverse chronological order. Please use ISO format for dates.

 *   $DateTime: 03/13/13 16:04:37 $

 * when       who    what, where, wh
  ---------- --- ---------------------------------------------------
  2016-01-11 sgh start
  2016-01-14 sgh daemon late start,,, not modifed init script

 * =================================================================
 */

#ifndef _CUST_PANTECH_SNS_H_
#define _CUST_PANTECH_SNS_H_

/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_DAEMON_LATE_START
* -----------------------------------------------------------------
*   .Brif          : to start daemon more earlier. (system server often can't get sensor list, because daemon is not ready.)
*   .Applied Block : sensordaemon / init script
*   .Applied Files : android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/src/sns_main.c
*                    android/device/qcom/common/rootdir/etc/init.qcom.rc <--- more lookup
*                    android/device/qcom/common/rootdir/etc/init.qcom.sh <--- more lookup
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_DAEMON_LATE_START

/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_ENCRYPTION
* -----------------------------------------------------------------
*   .Brif          : to prevent Encryption fail issue.
*   .Applied Block : sensordaemon / init script
*   .Applied Files : android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/src/sns_main.c
*                    android/device/qcom/common/rootdir/etc/init.qcom.rc <== more lookup
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_ENCRYPTION


/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_APDS99xx_SUNLIGHT_CANCELATION
* -----------------------------------------------------------------
*   .Brif          : APDS99xx sunlight cancelation
*   .Applied Block : ADSP(DD)
*   .Applied Files : adsp_proc/Sensors/dd/qcom/src/Sns_dd_apds99xx.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_APDS99XX_SUNLIGHT_CANCELATION


/* -----------------------------------------------------------------
   * CONFIG_PANTECH_SNSUTILS
   * -----------------------------------------------------------------
   *   .Brif          : use snsutils
   *   .Applied Block : HAL & pantech_server
   *   .Applied Files : 
   *                  vendor/qcom/proprietary/sensors/dsps/libhalsensors/Android.mk
   *                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/inc/Utility.h
   *                  vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/Proximity.cpp
   *                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/SensorsContext.cpp   
   *                  vendor/pantech/frameworks/pantechserver/server/cmds/pantech_factory/callback_func_sensor.c
   * ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNSUTILS
#ifdef CONFIG_PANTECH_SNSUTILS
#define CONFIG_PANTECH_ADSP_SUPPORTED_PROPERTY "sys.sns.supported"
#endif  // CONFIG_PANTECH_SNSUTILS

/* -----------------------------------------------------------------
   * CONFIG_PANTECH_GES_PRX_3AXES
   * -----------------------------------------------------------------
   *   .Brif          : Pixart gesture and proximity sensor 3axes data streaming
   *   .Applied Block : HAL & property_service
   *   .Applied Files :                                             
   *                  msm/adsp_proc/Sensors/dd/qcom/src/sns_dd_apds99xx_priv.h                                                    
   *                  msm/adsp_proc/Sensors/smgr/src/sns_smgr_init.c 
   *                  android/system/core/init/property_service.c   
   *                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/inc/Utility.h
   *                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/Light.cpp
   *                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/Proximity.cpp   
   *                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/SMGRSensor.cpp   
   *                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/SensorsContext.cpp
   *                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/Utility.cpp
   * ---------------------------------------------------------------*/
#ifdef CONFIG_PANTECH_SNSUTILS                                                                                   
#define CONFIG_PANTECH_GES_PRX_ALS_3AXES
#endif
#ifdef CONFIG_PANTECH_GES_PRX_ALS_3AXES
#define CONFIG_PANTECH_GES_PRX_ALS_3AXES_PROPERTY "sys.sns.debug"
#endif

/* -----------------------------------------------------------------
* CONFIG_PANTECH_FACTORY_PROCESS_CMD                                                                             
* -----------------------------------------------------------------
*   .Brif          : the codes about pantech factory process cmd
*   .Applied Block : pantech_server
*   .Applied Files :                                                                                              
*                  vendor\pantech\frameworks\pantechserver\include\server\cmd\pantech_factory\pantech_factory_cmd.h
*                  android/vendor/pantech/frameworks/pantechserver/server/cmds/pantech_factory/callback_func_sensor.c
*                  vendor\pantech\frameworks\pantechserver\server\Android.mk
*                  vendor\pantech\frameworks\pantechserver\server\cmds\pantech_factory\callback_func_usbpart.c
* 
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_FACTORY_PROCESS_CMD

/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_ADD_VALID_GROUP_RADIO
* -----------------------------------------------------------------
*   .Brif          : For issue gyro selftest(SkyTest menu) failed after applied 1025 patch. 
*   .Applied Block : sensordaemon
*   .Applied Files : 
*                  android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/inc/sns_main.h
*                  android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/src/sns_main.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_ADD_VALID_GROUP_RADIO

/* -----------------------------------------------------------------
* CONFIG_PANTECH_ADSP_LOGGING
* -----------------------------------------------------------------
*   .Brif          : to print the logs we add or to prevent repeating same logs
*   .Applied Block : HAL
*   .Applied Files : vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_hal.cpp
*                    vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/Thresh.cpp
*                    vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/SensorsContext.cpp   
*                    vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/src/sns_main.c
*                    vendor/qcom/proprietary/sensors/dsps/sensordaemon/apps/common/sns_debug/src/sns_debug_main.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_ADSP_LOGGING

/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_CHECK_DEVICE_VERSION
* -----------------------------------------------------------------
*   .Brif          : check device version is over 1 (because of CTS test)
*   .Applied Block : HAL
*   .Applied Files :
*                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/Sensor.cpp
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_CHECK_DEVICE_VERSION


/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_FIX_WTIME
* -----------------------------------------------------------------
*   .Brif          : fix wtime to 27.3ms
*   .Applied Block : ADSP
*   .Applied Files :  msm8974_v22/adsp_proc/Sensors/dd/qcom/src/sns_dd_apds99xx.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_FIX_WTIME

/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_WAKE_LOCK_PROXIMITY
 * -----------------------------------------------------------------
 *   .Brif          : acqurie wake lock when proximity data is arrived
 *   .Applied Block : sensordaemon
 *   .Applied Files : vendor/qcom/proprietary/sensors/dsps/sensordamon/apps/common/acm/src/sns_acm_mr.c
 * ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_WAKE_LOCK_PROXIMITY

/* ----------------------------------------------------------------- 
* CONFIG_PANTECH_SNS_LIST
* -----------------------------------------------------------------
*   .Brif          : Enable sensor within Google
*   .Applied Block : HAL
*   .Applied Files : android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/SensorsContext.cpp   
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_LIST

/* ----------------------------------------------------------------- 
* CONFIG_PANTECH_SNS_CTS
* -----------------------------------------------------------------
*   .Brif          : Gyro min freq set to 2 from 1 temporarilly cause of CTS.
*   .Brif          : Gyro, GyroUncalibrate sensor fastest batching CTS
*   .Applied Block : HAL
*   .Applied Files : 
*                    vendor/qcom/proprietary/sensors/dsps/libhalsensors/inc/sensors_hal.h
*                   vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_hal.cpp
*                    vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/Sensor.cpp
*                    vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/MagneticUncalibrated.cpp
*                   vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/Gyroscope.cpp
*                    vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/GyroscopeUncalibrated.cpp
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_CTS

#endif // _CUST_PANTECH_SNS_H_
