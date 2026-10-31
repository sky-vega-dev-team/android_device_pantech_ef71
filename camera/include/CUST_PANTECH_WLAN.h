#ifndef CUST_PANTECH_WLAN_H
#define CUST_PANTECH_WLAN_H

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====

               CUST_PANTECH_WLAN.h

DESCRIPTION

Copyright (c) 2014 by  Pantech All Rights Reserved.

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*======================================================================
                        EDIT HISTORY FOR MODULE

   when           who                          what,where,why
------------  ---------------     -------------------------------------------------
2014-4-25      choi.junwan[LS4]              Create for WLAN Defines
========================================================================*/


/*******************************************************************************
**  TEST_MENU & FACTORY_COMMAND (WLAN Common Feature) [WCN36x0/QCA6174]
*******************************************************************************/
#define FEATURE_PANTECH_WLAN_PROCESS_CMD
#define FEATURE_PANTECH_WLAN_FTM_TX_OFFSET    // 20131104, Target power control for KCP(FTM) test on regulartory mode <-QCA6174 Don't use this FEATURE
#define FEATURE_PANTECH_WLAN_TESTMENU // For WIFI Test Menu (WCN36X0), #8378522# TestMenu

#if 1 //20160421,  EF71S/K 2.4G SCPC, 5G CPLC fixed. defined(T_EF63S)|| defined(T_EF63K)|| defined(T_EF63L)|| defined(T_EF65S)  // This feature  isn't use at EF71 series || defined(T_EF71S)|| defined(T_EF71IE) 
#define FEATURE_PANTECH_WLAN_SCPC_2G_CLPC_5G // For 2.4G SCPC, 5G CLPC
#endif
/*******************************************************************************
**  Pantech Mac Address (WLAN Common Feature) [WCN36x0/QCA6174]
*******************************************************************************/
#define FEATURE_PANTECH_WLAN_RAWDATA_ACCESS // For Mac Address backup Rawdata
#define FEATURE_PANTECH_WLAN_FOUR_MAC_ADDRESS // LS4_WIFI Warfs 20140410 For APQ8084&QCA6174 change Define Name,  for pantech_wifi_mac_backup.h
#define FEATURE_PANTECH_WLAN_MAC_ADDR_BACKUP // LS4_WIFI Warfs 20140410 For APQ8084&QCA6174 change Define Name, used in skytest_thread.c

/*******************************************************************************
**  TRP&TIS Test MENU [WCN36x0/QCA6174]
*******************************************************************************/
#define FEATURE_PANTECH_WLAN_TRP_TIS // 2012-04-09, Pantech only, ymlee_p11019, to config & test TRP TIS

/*******************************************************************************
**  WIFI Framework logging [WCN36x0/QCA6174]
*******************************************************************************/
//#define FEATURE_PANTECH_WLAN_DEBUG_LEVEL_FRAMEWORK  // 20121031 thkim_wifi add for wifi logging

/*******************************************************************************
**  Prima/QCACLD Host Driver FEATURE [WCN36x0/QCA6174]
**  [move to Kbuild file in vendor\qcom\opensource\qcacld-2.0] - QCA6174
**	[move to Kbuild file in vendor\qcom\opensource\prima] - WCN36X0
*******************************************************************************/
#define FEATURE_PANTECH_WLAN
#define FEATURE_PANTECH_WLAN_QCOM_PATCH // used CR Fixs
//#define FEATURE_PANTECH_WLAN_DEBUG_LEVEL //20140508 LS4_WiFi Warfs APQ8064_JB -> MSM8974AB_KK -> APQ8084_KK
//#define FEATURE_PANTECH_WLAN_SCAN

/*******************************************************************************
**  Kernel Driver FEATURE(Kconfig) [WCN36x0/QCA6174]
**	[Defined Kconfig file in \kernel\arch\arm\mach-msm\cust\Kconfig]
*******************************************************************************/
//#define CONFIG_PANTECH_WLAN_DEBUG
//#define CONFIG_PANTECH_WLAN_PATCH

/*******************************************************************************
**  WIFI Throughput Performance FEATURE [WCN36x0/QCA6174]
*******************************************************************************/
//#define FEATURE_PANTECH_WLAN_PERF_CPU_FREQ //LS4_WIFI Warfs 20140728 For Performance, CPU Min Freq set case by case [OS version upper JB MR2(4.3)]
											 //\frameworks\base\services\java\com\android\server\wifi\WifiTrafficPoller.java

/*******************************************************************************
**  QCA6174 FEATURE  [QCA6174]
*******************************************************************************/
//#define FEATURE_PANTECH_WLAN_CHIPSET_QCA_CLD // QCA CHIPSET Used

#ifdef FEATURE_PANTECH_WLAN_CHIPSET_QCA_CLD
#define FEATURE_PANTECH_WLAN_QCA_CHAIN_CONTROL //LS4_WIFI Warfs, 20140421 CR#630874 Add ini variables to select TX or RX chain0/chain1

#ifdef FEATURE_PANTECH_WLAN_TESTMENU
#define FEATURE_PANTECH_WLAN_QCA_FTM_TESTMENU //LS4_WIFI Warfs, 20140424 Create for APQ8084-QCA6174 WIFI FTM TestMenu
#endif //FEATURE_PANTECH_WLAN_TESTMENU

#ifdef FEATURE_PANTECH_WLAN_PROCESS_CMD
#define FEATURE_PANTECH_WLAN_QCA_PROCESS_CMD //LS4_WIFI Warfs, 20140512 Create for APQ8084-QCA6174 WIFI Process CMD
#ifdef FEATURE_PANTECH_WLAN_QCA_PROCESS_CMD
#define FEATURE_PANTECH_WLAN_QCA_FTM_TX_OFFSET //LS4_WIFI Warfs, 20140523 Target power control for KCP(FTM) test on regulartory mode for QCA6174
#endif //FEATURE_PANTECH_WLAN_QCA_PROCESS_CMD
#endif //FEATURE_PANTECH_WLAN_PROCESS_CMD

#endif //FEATURE_PANTECH_WLAN_CHIPSET_QCA_CLD

#endif //CUST_PANTECH_WLAN_H
