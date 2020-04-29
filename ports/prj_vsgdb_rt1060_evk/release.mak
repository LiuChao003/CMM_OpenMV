#Generated by VisualGDB (http://visualgdb.com)
#DO NOT EDIT THIS FILE MANUALLY UNLESS YOU ABSOLUTELY NEED TO
#USE VISUALGDB PROJECT PROPERTIES DIALOG INSTEAD

BINARYDIR := Release

#Additional flags
PREPROCESSOR_MACROS := NDEBUG=1 RELEASE=1 __FPU_PRESENT=1 USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE=1 ARM_MATH_CM7 N_THUMB NDEBUG CPU_MIMXRT1052DVL6A MCU_SERIES_RT105 MCU_SERIES_RT106 USB_STACK_BM __BYTE_ORDER__=__ORDER_LITTLE_ENDIAN__ MICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool MICROPY_MODULE_FROZEN_MPY FFCONF_H='\\"oofatfs/ffconf.h\\"' HARD_FP FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 XIP_EXTERNAL_FLASH M_PI=3.141592654f M_PI_2=1.570796327f
INCLUDE_DIRS := ..\.. ..\..\py ..\..\extmod ..\..\lib ..\..\lib\cmsis\inc ..\nxp_rt1050_60 ..\nxp_rt1050_60\boards\imxrtevk105x ..\nxp_rt1050_60\mcusdk ..\nxp_rt1050_60\mcusdk\drivers ..\nxp_rt1050_60\mcusdk\utilities ..\nxp_rt1050_60\cmsis ..\nxp_rt1050_60\build-imxrtevk105x ..\nxp_rt1050_60\usb_cdc_msc ..\nxp_rt1050_60\mcusdk\middleware\sdkusb\include ..\nxp_rt1050_60\mcusdk\middleware\sdkusb\osa ..\nxp_rt1050_60\mcusdk\middleware\sdkusb\device ..\nxp_rt1050_60\mcusdk\middleware\sdkusb\phy ..\nxp_rt1050_60\sdmmc ..\nxp_rt1050_60\omv ..\nxp_rt1050_60\omv\py ..\nxp_rt1050_60\omv\img ..\nxp_rt1050_60\omv\nn ..\..\lib\oofatfs ..\..\lib\mp-readline ..\..\extmod\rt_thread ..\..\extmod\rt_thread\include\libc ..\..\extmod\rt_thread\include ..\..\drivers\m8266\lib_new ..\..\drivers\m8266 ..\nxp_rt1050_60\mcusdk\utilities\io ..\nxp_rt1050_60\mcusdk\utilities\log ..\nxp_rt1050_60\mcusdk\utilities\str ..\nxp_rt1050_60\flegftl ..\nxp_rt1050_60\sdmmc
LIBRARY_DIRS := 
LIBRARY_NAMES := 
ADDITIONAL_LINKER_INPUTS := 
MACOS_FRAMEWORKS := 
LINUX_PACKAGES := 

CFLAGS := -g  -O3
CXXFLAGS := -g    -O3
ASFLAGS := 
LDFLAGS := 
COMMONFLAGS := 
LINKER_SCRIPT := C:\d\gitrepos\mpyrt_omv\ports\prj_keil_rt1060_evk\sdram.sct

START_GROUP := 
END_GROUP := 

#Additional options detected from testing the toolchain
USE_DEL_TO_CLEAN := 1
CP_NOT_AVAILABLE := 1

ADDITIONAL_MAKE_FILES := mcu.mak
GENERATE_BIN_FILE := 0
GENERATE_IHEX_FILE := 1
