#ifndef CUST_PANTECH_FS_H
#define CUST_PANTECH_FS_H

/******************************************************************************
* 2014-11-11 p10255 : Created
******************************************************************************/

/*TEST_MENU & FACTORY_COMMAND*/
 /*****************************************************
* owner  : unknown          
* date    : unknown
* PLM    : 
* Case  :       
* Description : factory cmd
* kernel : none
* user    : used
******************************************************/
#define FEATURE_PANTECH_FS_FACTORY_CMD

#ifdef FEATURE_PANTECH_FS_FACTORY_CMD
#define FEATURE_PANTECH_FS_FACTORY_CMD_APP_CHECK
#define FEATURE_PANTECH_FS_FACTORY_CMD_EFS_ERASE
#define FEATURE_PANTECH_FS_FACTORY_CMD_INIT_ALL
#define FEATURE_PANTECH_FS_FACTORY_CMD_EMMC_FW_VER
#define FEATURE_PANTECH_FS_FACTORY_CMD_SDCARD_CHECK
#define FEATURE_PANTECH_FS_FACTORY_CMD_USER_APP_CHECK
#define FEATURE_PANTECH_FS_FACTORY_CMD_SECURE_ERASE
#define FEATURE_PANTECH_FS_FACTORY_CMD_EMMC_CID_REGISTER

#define FEATURE_PANTECH_FS_FACTORY_CMD_CHECKSUM_READ
#define FEATURE_PANTECH_FS_FACTORY_CMD_PRELOAD_CHECKSUM
#define FEATURE_PANTECH_FS_FACTORY_CMD_MOVIENAND_FORMAT
#endif

/*******************************************************************************
** FS 
*******************************************************************************/

 /*****************************************************
* owner  : unknown          
* date    : unknown
* PLM    : 
* Case  :       
* Description : sdcard detect & internal storage detect
* kernel : none
* user    : used
******************************************************/
#define PANTECH_STORAGE_INTERNAL_EMUL

 /*****************************************************
* owner  : unknown          
* date    : unknown
* PLM    : 
* Case  :       
* Description : exfat
* kernel : used (CONFIG_PANTECH_SDXC_EXFAT)
* user    : used (FEATURE_PANTECH_SDXC_EXFAT)
* build script : used (PANTECH_SDXC_EXFAT_FS,PANTECH_SDXC_EXFAT_BUILD)
******************************************************/
#define FEATURE_PANTECH_SDXC_EXFAT

/*	FS Repair		*/
 /*****************************************************
* owner  : unknown          
* date    : unknown
* PLM    : 
* Case  :       
* Description : recovery manual repair
* kernel : none
* user    : used
******************************************************/
#define FEATURE_PANTECH_MANUAL_REPAIR

 /*****************************************************
* owner  : unknown          
* date    : unknown
* PLM    : 
* Case  :       
* Description : auto repair for broken storage 
* kernel : used (CONFIG_PANTECH_FS_AUTO_REPAIR)
* user    : used
* bootloader    : used
******************************************************/
#define FEATURE_PANTECH_AUTO_REPAIR

 /*****************************************************
* owner  : unknown          
* date    : unknown
* PLM    : 
* Case  :       
* Description : fs test
* user    : used
* bootloader    : used
******************************************************/
#define FEATURE_PANTECH_FS_TEST

/*	Recovery mode		*/
 /*****************************************************
* owner  : unknown          
* date    : unknown
* PLM    : 
* Case  :       
* Description : recovery mode
* user    : used
******************************************************/
#define FEATURE_RECOVERY_HIDDEN_MENU
#define FEATURE_CS_USERDATA_BACKUP

/*	CUTUS			*/
 /*****************************************************
* owner  : unknown          
* date    : unknown
* PLM    : 
* Case  :       
* Description : sky station
* user    : used
******************************************************/
#define FEATURE_PANTECH_CERTUS

/*	Encryption		*/
 /*****************************************************
* owner  : unknown          
* date    : unknown
* PLM    : 
* Case  :       
* Description : ENCRYPTION
* user    : used
******************************************************/
#define FEATURE_SKY_DATA_ENCRYPTION
#define FAST_ENCRYPTION

/*	Image Verify		*/
 /*****************************************************
* owner  : unknown          
* date    : unknown
* PLM    : 
* Case  :       
* Description : user & other image verify
* user    : used
******************************************************/
#define FEATURE_SKY_MD5_VERIFY

  /*****************************************************
* owner  : unknown          
* date    : unknown
* PLM    : 
* Case  :       
* Description : for mmc utils
* user    : used
******************************************************/
#define FEATURE_SKY_USER_DATA_VER
#define FEATURE_SKY_FAT16_FOR_SBL3

  /*****************************************************
* owner  : jiseungwha         
* date    : 2016 01 28
* PLM    : 
* Case  :       
* Description : mmcblk_utils has to be unounted for dm-verify.
* user    : used
******************************************************/
#define FEATURE_PANTECH_MMCBLKUTILS_UNMOUNT
  /*****************************************************
* owner  : jiseungwha          
* date    : 2016 02 19
* PLM    : 
* Case  :       
* Description : key was changed because of EF71 for hidden menu ,it's only used in EF71 MODEL
* user    : used
******************************************************/
#define FEATURE_RECOVERY_HIDDEN_MENU_ONLY_EF71
  /*****************************************************
* owner  : jiseungwha          
* date    : 2016 05 10
* PLM    : 
* Case  :       
* Description : for userdata reserve
* user    : used
******************************************************/
#define FEATURE_PANTECH_USERDATA_RESERVE_10MB
  /*****************************************************
* owner  : jiseungwha          
* date    : 2016 06 2
* PLM    : 
* Case  :       
* Description :mountservice label error
* user    : used
******************************************************/
#define FEATURE_PANTECH_MOUNTSEVICE_LABEL_ERROR


/*	rentlock			*/
 /*****************************************************
* owner  : cafe2020          
* date    : 2016 07 07
* PLM    : 
* Case  :       
* Description : sky station
* user    : used
******************************************************/
#define FEATURE_SKY_RENTLOCK


#endif
