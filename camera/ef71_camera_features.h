/*
 * The stock ef71 framework had OEM camera metadata tags (flip mode, flash
 * needed, VT mode) for the Pantech camera app. The Q framework does not, so
 * leave out the HAL features that only feed those tags.
 */
#undef F_PANTECH_CAMERA_OEM_FLIP_MODE
#undef F_PANTECH_CAMERA_FLASH_NEEDED

/*
 * The mm-camera libraries in vendor/pantech/ef71 were rebuilt without the
 * Pantech VT tuning ("ef71: Drop pantech vt tuning"), so their parameter list
 * has no CAM_INTF_PARM_IS_VT. Leave it out here too, or every parameter after
 * it is off by one and the daemon never sets up the sensor and ISP.
 */
#undef F_PANTECH_CAMERA_CUST_VT_TUNING
