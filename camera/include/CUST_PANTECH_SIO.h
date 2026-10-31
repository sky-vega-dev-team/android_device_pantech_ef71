#ifndef CUST_PANTECH_SIO_H
#define CUST_PANTECH_SIO_H

/****************************************************************************** 
 ************************** featureing rule ***********************************
 * FEATURE_PANTECH_[USB|UART|TESTMENU|FACTORY_COMMAND|SIO|STABILITY]_SUBFUNC  *
*******************************************************************************/

// move to kernel config
//#define FEATURE_PANTECH_SIO_TEMP  //temporary feature for development 
//#define FEATURE_PANTECH_SIO_BUG_FIX // debug feature for qualcomm bugs.

#define FEATURE_PANTECH_USB_PST_MODE_CHANGE
#if defined(T_EF59K) || defined(T_EF61K) || defined(T_EF63K) || defined(T_EF69K) || defined(T_EF71K)
#define FEATURE_PANTECH_USB_SMART_DM_CONTROL
#endif
//#if defined(T_EF59L) || defined(T_EF62L) || defined(T_EF63L)
//#define FEATURE_PANTECH_USB_LGT_PC_MODE
//#endif

/*******************************************************************************
** UART CONSOLE (for SBL1 and LK)
** Please refer Kconfig for kernel function
*******************************************************************************/
#define FEATURE_PANTECH_UART_SERIAL 

#if defined(FEATURE_PANTECH_UART_SERIAL)
#if ((defined(T_EF56S) || defined(T_EF57K) || defined(T_EF58L)) \
		&& (CONFIG_BOARD_VER < CONFIG_TP10)) || (defined(T_NAMI) && (CONFIG_BOARD_VER < CONFIG_PT20))
#define FEATURE_PANTECH_CONSOLE_UART1
#else
#define FEATURE_PANTECH_CONSOLE_UART10
#endif
#endif

/*******************************************************************************
**  TEST_MENU & FACTORY_COMMAND
*******************************************************************************/
#define FEATURE_PANTECH_TESTMENU_USB
#define FEATURE_PANTECH_FACTORY_COMMAND
#if defined(T_EF71IE) || defined(T_EF71S) || defined(T_EF71K)
#define FEATURE_PANTECH_TESTMENU_USB_PCDT_ONOFF
#endif
#define FEATURE_PANTECH_FACTORY_GET_USB_ISERIAL


#if defined(T_EF71S) || defined(T_EF71K)
// Be careful that this feature should be enabled after second IOT.
// Because telecommunication(SKT/KT/LGT) company can not access the testmenu.(ref. USB checklist ver1.6)
#define FEATURE_PANTECH_TESTMENU_NO_ENTERING 
#endif


/*******************************************************************************
** USB 
*******************************************************************************/
/*******************************************************************************
 * COMMON FEATURE (for SBL1 and LK and Android)
 * ***************************************************************************/
#define FEATURE_PANTECH_USB
#define FEATURE_PANTECH_USB_DEBUG // Same feature defined in kernel Kconfig 
#ifdef FEATURE_PANTECH_USB_DEBUG
#define FEATURE_PANTECH_USB_STATE_DEBUG // Same feature defined in kernel Kconfig
#endif

//#define FEATURE_PANTECH_USB_TUNE_SIGNALING_PARAM // Same feature defined in kernel Kconfig
#define FEATURE_PANTECH_USB_QXDM_ONOFF // Same feature defined in kernel Kconfig

/* adb security */
#define FEATURE_PANTECH_USB_ADB_SECURE
/*******************************************************************************
 * DEPENDANT ON MODEL (for SBL1 and LK and Android)
 * ***************************************************************************/
//#define FEATURE_PANTECH_USB_CDFREE // Same feature defined in kernel Kconfig
#define FEATURE_PANTECH_USB_BLOCKING_MDMSTATE
/* Same featire defined in kernel Kconfig
#if ((defined(T_EF59S) || defined(T_EF59K) || defined(T_EF59L)) \
		&& (CONFIG_BOARD_VER > CONFIG_TP10))
#define FEATURE_PANTECH_USB_VER_SWITCH 
#endif
*/

#endif/* CUST_PANTECH_SIO_H */

