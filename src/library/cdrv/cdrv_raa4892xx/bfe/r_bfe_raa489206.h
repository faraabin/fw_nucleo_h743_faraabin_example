/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : raa489206.h
 * Version      : 1.1
 * Description  : Macros, exported functions and type definitions of the RAA489206 BFE
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 24.08.2021 1.00    Internal Release
 *         : 05.11.2021 1.10    Release
 *         : 24.01.2023 2.0     SOC application and CB commands
 *********************************************************************************************************************/
#ifndef R_BFE_RAA489206_H
#define R_BFE_RAA489206_H
/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_bfe_api.h"
#include "common_utils.h"
#include "..\cdrv_raa4892xx.h"
//#include "r_spi_api.h"
//#include "r_i2c_master_api.h"
//#include "r_external_irq_api.h"
//#include "r_ioport_api.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/* RAA489206 Register Address */
#define RAA489206_REGISTER_SYS_INFO        (0x00)
#define RAA489206_REGISTER_GLOBAL_OP       (0x01)
#define RAA489206_REGISTER_VCELL_OP        (0x02)
#define RAA489206_REGISTER_IPACK_OP        (0x03)
#define RAA489206_REGISTER_CELL_SEL        (0x04)
#define RAA489206_REGISTER_VCELL_OV_TH     (0x06)
#define RAA489206_REGISTER_VCELL_UV_TH     (0x07)
#define RAA489206_REGISTER_VCELL_MAX_D_TH  (0x08)
#define RAA489206_REGISTER_FAULT_DELAY     (0x09)
#define RAA489206_REGISTER_DSC_TH          (0x0A)
#define RAA489206_REGISTER_DOC_TH          (0x0B)
#define RAA489206_REGISTER_DSC_DELAY       (0x0C)
#define RAA489206_REGISTER_OC_DELAY        (0x0D)
#define RAA489206_REGISTER_LD_CHR_OP       (0x0E)
#define RAA489206_REGISTER_COC_TH          (0x0F)
#define RAA489206_REGISTER_IEOC_TH         (0x10)
#define RAA489206_REGISTER_ETAUX_OP        (0x11)
#define RAA489206_REGISTER_GPIO_ALERT_OP   (0x12)
#define RAA489206_REGISTER_DUT0_LIMIT      (0x13)
#define RAA489206_REGISTER_DOT0_LIMIT      (0x14)
#define RAA489206_REGISTER_CUT0_LIMIT      (0x15)
#define RAA489206_REGISTER_COT0_LIMIT      (0x16)
#define RAA489206_REGISTER_DUT1_LIMIT      (0x17)
#define RAA489206_REGISTER_DOT1_LIMIT      (0x18)
#define RAA489206_REGISTER_CUT1_LIMIT      (0x19)
#define RAA489206_REGISTER_COT1_LIMIT      (0x1A)
#define RAA489206_REGISTER_VREG_OP         (0x1B)
#define RAA489206_REGISTER_VVCC_MIN        (0x1C)
#define RAA489206_REGISTER_IREGOC1         (0x1D)
#define RAA489206_REGISTER_IREGOC2         (0x1E)
#define RAA489206_REGISTER_VBAT1_OP        (0x1F)
#define RAA489206_REGISTER_OVBAT1_TH       (0x20)
#define RAA489206_REGISTER_UVBAT1_TH       (0x21)
#define RAA489206_REGISTER_IOTW_TH         (0x22)
#define RAA489206_REGISTER_IOTF_TH         (0x23)
#define RAA489206_REGISTER_PWR_FET_OP      (0x24)
#define RAA489206_REGISTER_CB_OP           (0x25)
#define RAA489206_REGISTER_CB_CELL_STA     (0x26)
#define RAA489206_REGISTER_CB_ON_TIME      (0x28)
#define RAA489206_REGISTER_CB_OFF_TIME     (0x29)
#define RAA489206_REGISTER_CB_MIN_D_TH     (0x2A)
#define RAA489206_REGISTER_CB_MAX_TH       (0x2B)
#define RAA489206_REGISTER_CB_MIN_TH       (0x2C)
#define RAA489206_REGISTER_VEOC_TH         (0x2D)
#define RAA489206_REGISTER_SCAN_OP         (0x2E)
#define RAA489206_REGISTER_VCELL_1         (0x30)
#define RAA489206_REGISTER_VCELL_2         (0x32)
#define RAA489206_REGISTER_VCELL_3         (0x34)
#define RAA489206_REGISTER_VCELL_4         (0x36)
#define RAA489206_REGISTER_VCELL_5         (0x38)
#define RAA489206_REGISTER_VCELL_6         (0x3A)
#define RAA489206_REGISTER_VCELL_7         (0x3C)
#define RAA489206_REGISTER_VCELL_8         (0x3E)
#define RAA489206_REGISTER_VCELL_9         (0x40)
#define RAA489206_REGISTER_VCELL_10        (0x42)
#define RAA489206_REGISTER_VCELL_11        (0x44)
#define RAA489206_REGISTER_VCELL_12        (0x46)
#define RAA489206_REGISTER_VCELL_13        (0x48)
#define RAA489206_REGISTER_VCELL_14        (0x4A)
#define RAA489206_REGISTER_VCELL_15        (0x4C)
#define RAA489206_REGISTER_VCELL_16        (0x4E)
#define RAA489206_REGISTER_VCELL_MAX_DELTA (0x50)
#define RAA489206_REGISTER_IPACK           (0x52)
#define RAA489206_REGISTER_IPACK_TIMER     (0x54)
#define RAA489206_REGISTER_ETAUX_0_V       (0x58)
#define RAA489206_REGISTER_ETAUX_1_V       (0x5A)
#define RAA489206_REGISTER_VBAT1           (0x5C)
#define RAA489206_REGISTER_INTER_TEMP      (0x5E)
#define RAA489206_REGISTER_VTEMP           (0x5F)
#define RAA489206_REGISTER_VCC_V           (0x60)
#define RAA489206_REGISTER_IREG_V          (0x61)
#define RAA489206_REGISTER_PRIORITY_FAULTS (0x63)
#define RAA489206_REGISTER_ETAUX_FAULTS    (0x64)
#define RAA489206_REGISTER_OTHER_FAULTS    (0x65)
#define RAA489206_REGISTER_CB_STATUS       (0x66)
#define RAA489206_REGISTER_STATUS          (0x67)
#define RAA489206_REGISTER_OW_STATUS       (0x68)
#define RAA489206_REGISTER_PRIOR_FAULT_M   (0x83)
#define RAA489206_REGISTER_ETAUX_FAULT_M   (0x84)
#define RAA489206_REGISTER_OTHER_FAULT_M   (0x85)
#define RAA489206_REGISTER_CB_STATUS_M     (0x86)
#define RAA489206_REGISTER_STATUS_M        (0x87)
#define RAA489206_REGISTER_OW_M            (0x88)

/*RAA489206 number of registers*/
#define RAA489206_REGISTER_NUMBER_OF_REGISTERS            (138U)

/*RAA489206 number of vcell registers*/
#define RAA489206_REGISTER_NUMBER_OF_VCELL_REGISTERS            (34U)

/*RAA489206 interface addresses:*/
#define RAA489206_I2C_SLAVE_ADDRESS                        (0x1A) //I2C 7-bit address
#define RAA489206_SPI_SLAVE_CRC_DISABLED_ADDRESS           (0x14) //SPI CRC disabled 7-bit address
#define RAA489206_SPI_SLAVE_CRC_ENABLED_ADDRESS            (0x9C) //SPI CRC disabled 7-bit address

/*startup delay*/
#define RAA489206_STARTUP_DELAY_MS              (20U)

/*Voltages stabilization delay*/
#define RAA489206_VSTABLE_DELAY_MS                (10U)

/*reset delay*/
#define RAA489206_RESET_DELAY_MS                (50U)

/*Charge pump delay time*/
#define BFE_RAA489206_CHARGE_PUMP_WAIT_TIME_MS (10U)

/* Peripherals buffer length */
#define BUFF_LEN                                (256U)

/*CRC Read Command codes*/
#define RAA489206_CRC_COMMAND_ALL_REGISTERS       (0x9A)
#define RAA489206_CRC_COMMAND_MEASUREMENT         (0x9B)
#define RAA489206_CRC_COMMAND_VCELL               (0x9C)
#define RAA489206_CRC_COMMAND_IPACK               (0x9D)
#define RAA489206_CRC_COMMAND_OTHER               (0x9E)
#define RAA489206_CRC_COMMAND_FAULTS               (0x9F)

/*Ipack timer step*/
#define BFE_IPACK_TIMER_STEP_S     (0.015f)

/*System mode*/
#define RAA489206_SYSTEM_MODE_IDLE       (0x00)
#define RAA489206_SYSTEM_MODE_SCAN       (0x01)
#define RAA489206_SYSTEM_MODE_LPM        (0x02)
#define RAA489206_SYSTEM_MODE_SHIP       (0x03)

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/*Scan delay*/
typedef enum e_raa489206_scan_delay
{
   RAA489206_SCAN_DELAY_0_MS     = 0x00,
   RAA489206_SCAN_DELAY_64_MS    = 0x01,
   RAA489206_SCAN_DELAY_128_MS   = 0x02,
   RAA489206_SCAN_DELAY_256_MS   = 0x03,
   RAA489206_SCAN_DELAY_512_MS   = 0x04,
   RAA489206_SCAN_DELAY_1024_MS  = 0x05,
   RAA489206_SCAN_DELAY_2048_MS  = 0x06,
   RAA489206_SCAN_DELAY_4096_MS  = 0x07,
} e_raa489206_scan_delay_t;

/*low power mode timer*/
typedef enum e_raa489206_lpm_timer
{
   RAA489206_LPM_TIMER_0_SCANS      = 0x00,
   RAA489206_LPM_TIMER_512_SCANS    = 0x01,
   RAA489206_LPM_TIMER_1024_SCANS   = 0x02,
   RAA489206_LPM_TIMER_2048_SCANS   = 0x03,
   RAA489206_LPM_TIMER_4096_SCANS   = 0x04,
   RAA489206_LPM_TIMER_8192_SCANS   = 0x05,
   RAA489206_LPM_TIMER_16384_SCANS  = 0x06,
   RAA489206_LPM_TIMER_32768_SCANS  = 0x07,
} e_raa489206_lpm_timer_t;

/*Low power mode regulator*/
typedef enum e_raa489206_lpm_regulator
{
    RAA489206_LPM_WEAK_REG           = 0,
    RAA489206_LPM_STRONG_REG         = 1,
}e_raa489206_lpm_regulator_t;

/*Low power mode regulator*/
typedef enum e_raa489206_comm_timeout_en
{
    RAA489206_COMM_TIMEOUT_OFF           = 0,
    RAA489206_COMM_TIMEOUT_ON          = 1,
}e_raa489206_commtimeout_enable_t;

/* Communication timer to transition to LPM*/
typedef enum e_raa489206_comm_timeout
{
    RAA489206_COMM_TIMEOUT_128MS     = 0x00,
    RAA489206_COMM_TIMEOUT_512MS     = 0x01,
    RAA489206_COMM_TIMEOUT_2048MS    = 0x02,
    RAA489206_COMM_TIMEOUT_4096MS    = 0x03,
}e_raa489206_comm_timeout_t;

/*Vcell averages*/
typedef enum e_raa489206_vcell_avg
{
    RAA489206_VCELL_AVG_1_SAMPLE          = 0x00,
    RAA489206_VCELL_AVG_2_SAMPLES         = 0x01,
    RAA489206_VCELL_AVG_4_SAMPLES         = 0x02,
    RAA489206_VCELL_AVG_8_SAMPLES         = 0x03,
    RAA489206_VCELL_AVG_16_SAMPLES        = 0x04,
    RAA489206_VCELL_AVG_32_SAMPLES        = 0x05,
    RAA489206_VCELL_AVG_64_SAMPLES        = 0x06,
    RAA489206_VCELL_AVG_128_SAMPLES       = 0x07,
} e_raa489206_vcell_avg_t;

typedef enum e_raa489206_ipack_avg
{
    RAA489206_IPACK_AVG_1_SAMPLE          = 0x00,
    RAA489206_IPACK_AVG_2_SAMPLES         = 0x01,
    RAA489206_IPACK_AVG_4_SAMPLES         = 0x02,
    RAA489206_IPACK_AVG_8_SAMPLES         = 0x03,
    RAA489206_IPACK_AVG_16_SAMPLES        = 0x04,
    RAA489206_IPACK_AVG_32_SAMPLES        = 0x05,
    RAA489206_IPACK_AVG_64_SAMPLES        = 0x06,
    RAA489206_IPACK_AVG_128_SAMPLES       = 0x07,
}e_raa489206_ipack_avg_t;

typedef enum e_raa489206_ow_period
{
    RAA489206_OW_PERIOD_256_SCANS         = 0x00,
    RAA489206_OW_PERIOD_512_SCANS         = 0x01,
    RAA489206_OW_PERIOD_1024_SCANS        = 0x02,
    RAA489206_OW_PERIOD_2048_SCANS        = 0x03,
}e_raa489206_ow_period_t;

typedef enum e_raa489206_other_avg
{
    RAA489206_OTHER_AVG_1_SAMPLE          = 0x00,
    RAA489206_OTHER_AVG_2_SAMPLES         = 0x01,
    RAA489206_OTHER_AVG_4_SAMPLES         = 0x02,
    RAA489206_OTHER_AVG_8_SAMPLES         = 0x03,
    RAA489206_OTHER_AVG_16_SAMPLES        = 0x04,
    RAA489206_OTHER_AVG_32_SAMPLES        = 0x05,
    RAA489206_OTHER_AVG_64_SAMPLES        = 0x06,
    RAA489206_OTHER_AVG_128_SAMPLES       = 0x07,
}e_raa489206_other_avg_t;

typedef enum e_raa489206_other_update_period
{
    RAA489206_OTHER_PERIOD_1_SCANS         = 0x00,
    RAA489206_OTHER_PERIOD_8_SCANS         = 0x01,
    RAA489206_OTHER_PERIOD_16_SCANS        = 0x02,
    RAA489206_OTHER_PERIOD_64_SCANS        = 0x03,
} e_raa489206_otherupdate_period_t;

/* Vcell fault delay: number of scan delays given by number in decimal + 1*/
typedef enum e_raa489206_vcell_fault_delay
{
    RAA489206_VCELL_FAULT_DELAY_1_SCAN    = 0x00,
    RAA489206_VCELL_FAULT_DELAY_2_SCAN    = 0x01,
    RAA489206_VCELL_FAULT_DELAY_3_SCAN    = 0x02,
    RAA489206_VCELL_FAULT_DELAY_4_SCAN    = 0x03,
    RAA489206_VCELL_FAULT_DELAY_5_SCAN    = 0x04,
    RAA489206_VCELL_FAULT_DELAY_6_SCAN    = 0x05,
    RAA489206_VCELL_FAULT_DELAY_7_SCAN    = 0x06,
    RAA489206_VCELL_FAULT_DELAY_8_SCAN    = 0x07,
    RAA489206_VCELL_FAULT_DELAY_9_SCAN    = 0x08,
    RAA489206_VCELL_FAULT_DELAY_10_SCAN   = 0x09,
    RAA489206_VCELL_FAULT_DELAY_11_SCAN   = 0x0A,
    RAA489206_VCELL_FAULT_DELAY_12_SCAN   = 0x0B,
    RAA489206_VCELL_FAULT_DELAY_13_SCAN   = 0x0C,
    RAA489206_VCELL_FAULT_DELAY_14_SCAN   = 0x0D,
    RAA489206_VCELL_FAULT_DELAY_15_SCAN   = 0x0E,
    RAA489206_VCELL_FAULT_DELAY_16_SCAN   = 0x0F,
} e_raa489206_vcell_fault_delay_t;

/* over current delay: number of scan delays given by number in decimal. 0 indicates no delay*/
typedef enum e_raa489206_os_fault_delay
{
    RAA489206_OC_FAULT_DELAY_0_SCAN    = 0x00,
    RAA489206_OC_FAULT_DELAY_1_SCAN    = 0x01,
    RAA489206_OC_FAULT_DELAY_2_SCAN    = 0x02,
    RAA489206_OC_FAULT_DELAY_3_SCAN    = 0x03,
    RAA489206_OC_FAULT_DELAY_4_SCAN    = 0x04,
    RAA489206_OC_FAULT_DELAY_5_SCAN    = 0x05,
    RAA489206_OC_FAULT_DELAY_6_SCAN    = 0x06,
    RAA489206_OC_FAULT_DELAY_7_SCAN    = 0x07,
    RAA489206_OC_FAULT_DELAY_8_SCAN    = 0x08,
    RAA489206_OC_FAULT_DELAY_9_SCAN   = 0x09,
    RAA489206_OC_FAULT_DELAY_10_SCAN   = 0x0A,
    RAA489206_OC_FAULT_DELAY_11_SCAN   = 0x0B,
    RAA489206_OC_FAULT_DELAY_12_SCAN   = 0x0C,
    RAA489206_OC_FAULT_DELAY_13_SCAN   = 0x0D,
    RAA489206_OC_FAULT_DELAY_14_SCAN   = 0x0E,
    RAA489206_OC_FAULT_DELAY_15_SCAN   = 0x0F,
} e_raa489206_coc_doc_fault_delay_t;

/*Load detection options*/
typedef enum e_raa489206_ld_options
{
    RAA489206_LOAD_DETECTION_DISABLED        = 0x00,
    RAA489206_LOAD_DETECTION_ENABLED_1MOHM   = 0x01,
    RAA489206_LOAD_DETECTION_ENABLED_10KOHM  = 0x02,
    RAA489206_LOAD_DETECTION_RSV             = 0x03,
} e_raa489206_ld_options_t;

/*Load detection delay*/
typedef enum e_raa489206_ld_delay
{
    RAA489206_LOAD_DETECTION_DELAY_025_S           = 0x00,
    RAA489206_LOAD_DETECTION_DELAY_1_S             = 0x01,
    RAA489206_LOAD_DETECTION_DELAY_2_S             = 0x02,
    RAA489206_LOAD_DETECTION_DELAY_4_S             = 0x03,
} e_raa489206_ld_delay_t;

/*Number of samples averaged per measurement before reporting ETAUX results*/
typedef enum e_raa489206_etaux_avg
{
    RAA489206_ETAUX_1_SAMPLE         = 0x00,
    RAA489206_ETAUX_2_SAMPLES         = 0x01,
    RAA489206_ETAUX_4_SAMPLES         = 0x02,
    RAA489206_ETAUX_8_SAMPLES         = 0x03,
    RAA489206_ETAUX_16_SAMPLES        = 0x04,
    RAA489206_ETAUX_32_SAMPLES        = 0x05,
    RAA489206_ETAUX_64_SAMPLES        = 0x06,
    RAA489206_ETAUX_128_SAMPLES       = 0x07,
} e_raa489206_etaux_avg_t;

typedef enum e_raa489206_etaux_enable
{
    RAA489206_ETAUX_OFF               = 0x00,
    RAA489206_ETAUX_XT0               = 0x01,
    RAA489206_ETAUX_XT1               = 0x02,
    RAA489206_ETAUX_BOTH              = 0x03,
} e_raa489206_etaux_enable_t;

/*GPIO configuration bits*/
typedef enum e_raa489206_gpio_config
{
    RAA489206_GPIO_DIGITAL_INPUTS                  = 0x00,
    RAA489206_GPIO_DIGITAL_OUTPUTS                 = 0x01,
    RAA489206_GPIO_DRIVE_LED                       = 0x02,
    RAA489206_GPIO_PWR_FETS_GATE_DRIVE_OUT         = 0x03,
} e_raa489206_gpio_config_t;

/*2 bytes union with access to least significant byte*/
union u_two_byte_lsb
{
    uint16_t value;
    uint8_t lsb_value;

    struct
    {
        uint16_t lsb                    : 8;
        uint16_t msb                    : 8;
    } lsb_msb;
};

/*4 bytes union with access to least significant byte*/
union u_four_byte_lsb
{
    uint32_t value;
    uint8_t lsb;
};

/*Cells selection*/

typedef enum e_raa489206_cells_select
{
    RAA489206_CELLS_SELECT_16_CELLS                  = 0x0000FFFF,
    RAA489206_CELLS_SELECT_15_CELLS                  = 0x0000FEFF,
    RAA489206_CELLS_SELECT_14_CELLS                  = 0x0000FE7F,
    RAA489206_CELLS_SELECT_13_CELLS                  = 0x0000FC7F,
    RAA489206_CELLS_SELECT_12_CELLS                  = 0x0000FC3F,
    RAA489206_CELLS_SELECT_11_CELLS                  = 0x0000F83F,
    RAA489206_CELLS_SELECT_10_CELLS                  = 0x0000F81F,
    RAA489206_CELLS_SELECT_9_CELLS                   = 0x0000F01F,
    RAA489206_CELLS_SELECT_8_CELLS                   = 0x0000F00F,
    RAA489206_CELLS_SELECT_7_CELLS                   = 0x0000E00F,
    RAA489206_CELLS_SELECT_6_CELLS                   = 0x0000E007,
    RAA489206_CELLS_SELECT_5_CELLS                   = 0x0000C007,
    RAA489206_CELLS_SELECT_4_CELLS                   = 0x0000C003,
} e_raa489206_cells_select_t;

/**********************************************************************************************************************
 RAA489206 SYSTEM REGISTERS
***********************************************************************************************************************/

/**********************************************************************************************************************
 IC Device Details
***********************************************************************************************************************/

/* 0x00 Device product ID register*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t RSV                     : 1;    /*0x00.0 REserved*/
        uint8_t REVISION                : 3;    /*0x00.1...0x00.3 Product revision*/
        uint8_t ID                      : 4;    /*0x00.4...0x00.7 Last two digits of the part ID minus one*/

    } value_b;

} u_raa489206_productionid_reg_t;

/**********************************************************************************************************************
 Global IC Control
 ********************************************************************************************************************/

/* 0x01 Global operation register*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t SYS_SCAN_TRIGGER        : 1;    /*0x01.0 Initiate a system scan*/
        uint8_t SCAN_SEL                : 1;    /*0x01.1 Type os system scan*/
        uint8_t BUSY                    : 1;    /*0x01.2 Busy bit indicationg device status*/
        uint8_t RCAL                    : 1;    /*0x01.3 Recalibrate before another system scan*/
        uint8_t RCAL_LPM_EN             : 1;    /*0x01.4 Recalibrate in Low Power Mode*/
        uint8_t RCAL_VOS_TRIGGER        : 1;    /*0x01.5 Recalibrate Low voltage offset*/
        uint8_t RESET2IDLE              : 1;    /*0x01.6 Reset to idle*/
        uint8_t SFT_RST                 : 1;    /*0x01.7 Soft reset*/

    } value_b;

} u_raa489206_globalop_reg_t;

/**********************************************************************************************************************
 Vcell and Ipack Measurement
 **********************************************************************************************************************/

/* 0x02 Cell voltage operation*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t VCELL_TRIGGER           : 1;    /*0x02.0 1 initiates Vcell measurement*/
        uint8_t CLR_FAULTS_STATUS       : 1;    /*0x02.1 1 clears faults and status*/
        uint8_t VCELL_AVG               : 3;    /*0x01.2...0x04 Number of samples averaged */
        uint8_t CHRWUV                  : 1;    /*0x02.5 1 disables Vcell UV*/
        uint8_t DCHRWOV                : 1;    /*0x02.6 1 disables Vcell OV*/
        uint8_t VCELL_EN                : 1;    /*0x02.7 1 Enables Vcells scan within system scans*/
    } value_b;

} u_raa489206_vcellop_reg_t;

/* 0x03 Ipack operation*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t IPACK_TRIGGER           : 1;    /*0x03.0 initiates an Ipack measurement*/
        uint8_t IDIR_DELAY              : 1;    /*0x03.1 number of measurements to determine charge/discharge: 0=1, 1=3 readings*/
        uint8_t IPACK_AVG               : 3;    /*0x03.2...0x03.4 number of samples averaged before writing the result*/
        uint8_t OW_UPDATE               : 2;    /*0x03.5...0x03.6 Control how often the open-wire test is executed*/
        uint8_t IPACK_EN                : 1;    /*0x03.7 Set to 1 to enable Ipack measurements*/
    } value_b;

} u_raa489206_ipackop_reg_t;

/* 0x04-0x05 Cell select register*/
typedef union
{
    uint16_t value;
    uint8_t lsb_value;

    struct
    {
        uint16_t lsb                    : 8;
        uint16_t msb                    : 8;
    } lsb_msb;

    struct
    {
        uint16_t CELLS_1_8               : 8;
        uint16_t CELLS_9_16              : 8;
    } cells_group;

    struct
    {
        uint16_t CELL1                   : 1;    /*0x04.0 Cell 1*/
        uint16_t CELL2                   : 1;    /*0x04.1 Cell 2*/
        uint16_t CELL3                   : 1;    /*0x04.2 Cell 3*/
        uint16_t CELL4                   : 1;    /*0x04.3 Cell 4*/
        uint16_t CELL5                   : 1;    /*0x04.4 Cell 5*/
        uint16_t CELL6                   : 1;    /*0x04.5 Cell 6*/
        uint16_t CELL7                   : 1;    /*0x04.6 Cell 7*/
        uint16_t CELL8                   : 1;    /*0x04.7 Cell 8*/
        uint16_t CELL9                   : 1;    /*0x05.0 Cell 9*/
        uint16_t CELL10                  : 1;    /*0x05.1 Cell 10*/
        uint16_t CELL11                  : 1;    /*0x05.2 Cell 11*/
        uint16_t CELL12                  : 1;    /*0x05.3 Cell 12*/
        uint16_t CELL13                  : 1;    /*0x05.4 Cell 13*/
        uint16_t CELL14                  : 1;    /*0x05.5 Cell 14*/
        uint16_t CELL15                  : 1;    /*0x05.6 Cell 15*/
        uint16_t CELL16                  : 1;    /*0x05.7 Cell 16*/

    } cells;

} u_raa489206_cells_select_t;

/* 0x30-0x4F V cell voltage 2-byte registers: VCell = (regVal)x(VCELLStep) + (0.5)x(VCELLStep); VCELLStep = 73.54792uV.*/
typedef union u_two_byte_lsb u_raa489206_vcell_voltage_t;

/* 0x50-0x51V cell max delta voltage 2byte-registers: VCell = (regVal)x(VCELLStep); VCELLStep = 73.54792uV.*/
typedef union u_two_byte_lsb u_raa489206_vcell_max_delta_t;

/* 0x52-0x53 Ipack voltage register*/
typedef union u_two_byte_lsb u_raa489206_ipack_voltage_t;

/* 0x54-0x57 Ipack timer register*/
typedef union
{
    uint32_t value;
    uint8_t lsb_value;

    struct
    {
        uint32_t byte1              : 8;
        uint32_t byte2              : 8;
        uint32_t byte3              : 8;
        uint32_t byte4              : 8;
    } bytes_values;
} u_raa489206_ipack_timer_t;

/**********************************************************************************************************************
 Vcell fault detectors
***********************************************************************************************************************/
/* 0x06 Vcell over-voltage register*/
typedef uint8_t raa489206_vcell_ov_th_t;

/* 0x07 Vcell under-voltage register*/
typedef uint8_t raa489206_vcell_uv_th_t;

/* 0x08 Max Delta Threshold register*/
typedef uint8_t raa489206_vcell_max_delta_th_t;

/* 0x09 Fault Delay register*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t VCELL_FAULT_DELAY        : 4; /*0x09.1...0x09.3 enables scans delay for Vcell OV and UV faults */
        uint8_t ETAUX_FAULT              : 1; /*0x09.4 enables 3-scan delay for ETAUX voltage threshold*/
        uint8_t OTHER_FAULT_DELAY        : 1; /*0x09.5 enables 3-scans delay for Vcc,Vtmpf,Ireg1,Ireg2,Vbovf,Vbuvf,IOTF,IOTW faults*/
        uint8_t DELTA_VCELL_FAULT_DELAY  : 1; /*0x09.6 enables 3-scans delay for delta vcell fault*/
        uint8_t AUX_XTN_PULLUP           : 1; /*0x09.7 when set to t, internal resistors are connected bwtween AUX0/1 and Vcc*/
    } value_b;
} u_raa489206_vcell_fault_delay_t;

/**********************************************************************************************************************
 Ipack fault detectors
***********************************************************************************************************************/

/* 0x0A Discharge Short-Circuit Threshold*/
typedef uint8_t raa489206_dsc_threshold_t;

/* 0x0B Discharge over-current threshold*/
typedef uint8_t raa489206_doc_th_register_t;

/* 0x0C Discharge Short-Circuit Delay register. TODO: Check reserve bit implications*/
typedef uint8_t raa489206_dsc_delay_register_t;

/* 0x0D Over-current delay*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t COCD                    : 4; /*0x0D.0-0x0D.3 Discharge overcurrent delay*/
        uint8_t DOCD                    : 4; /*0x0D.4-0x0D.7 Charge overcurrent delay*/
    } value_b;
} u_raa489206_oc_delay_t;

/*0x0E Load/Charge Operations*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t RSV                    : 1; /*0x0E.0 Reserved bit*/
        uint8_t LDLP                   : 1; /*0x0E.1 Load detect while in power mode*/
        uint8_t FCDC                   : 1; /*0x0E.2 FET charge driver connect*/
        uint8_t CPWR                   : 1; /*0x0E.3 Configure power FET*/
        uint8_t ELR                    : 1; /*0x0E.4 Enable load recovery*/
        uint8_t ELD                    : 2; /*0x0E.5...0x0E.6 Enable load detection*/
        uint8_t CFD                    : 1; /*0x0E.7 Connect for discharge fault*/
    } value_b;
} u_raa489206_load_charge_oper_t;

/*0x0F Charge over-current threshold*/
typedef uint8_t raa489206_coc_th_register_t;

/**********************************************************************************************************************
 External Temperature / Auxiliary (ETAUX)
***********************************************************************************************************************/
/*0x11 Etaux Operation*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t ETAUX_TRIGGER                   : 1; /*0x11.0 Trigger setting to 1 triggers an ETAUX measurement*/
        uint8_t ETAUX_RSV1                      : 1; /*0x11.1 Reserve bit*/
        uint8_t ETAUX_AVG                       : 3; /*0x11.2...0x11.4 ETAUX averages*/
        uint8_t ETAUX_RSV5                      : 1; /*0x11.5 Reserve bit*/
        uint8_t ETAUX_ENABLE                    : 2; /*0x11.6...0x11.7 ETAUX enable. enables including ETAUX measurement in scan mode*/
    }value_b;

}u_raa489206_etauxop_register_t;

/**********************************************************************************************************************
 Alert and GPIO
***********************************************************************************************************************/
/*0x12 Alert and General purpose I/O*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t GPIO_STATUS                     : 4; /*0x12.0...0x12.3 Status of each GPIO pin*/
        uint8_t GPIO_CONFIG                     : 2; /*0x12.4...0x12.5 Configuration of GPIO pins*/
        uint8_t ALRT_PULSE_EN                   : 1; /*0x12.6 Alert pulse enable*/
        uint8_t ALRT_ASSERT                     : 1; /*0x12.7 Alert pin assertion*/
    }value_b;

}u_raa489206_gpio_alrt_op_reg_t;

/**********************************************************************************************************************
 ETAUX Detectors
***********************************************************************************************************************/
/* 0x13...0x1A Under-temperature and over-temperature ETAUX thresholds*/
typedef uint8_t raa489206_cut0_threshold_t;
typedef uint8_t raa489206_cut1_threshold_t;
typedef uint8_t raa489206_dut0_threshold_t;
typedef uint8_t raa489206_dut1_threshold_t;
typedef uint8_t raa489206_cot0_threshold_t;
typedef uint8_t raa489206_cot1_threshold_t;
typedef uint8_t raa489206_dot0_threshold_t;
typedef uint8_t raa489206_dot1_threshold_t;

/* 0x58 2-bytes ETAUX0 Voltage*/
typedef union u_two_byte_lsb raa489206_xt0_aux0_voltage_t;
/* 0x5A 2-bytes ETAUX1 Voltage*/
typedef union u_two_byte_lsb raa489206_xt1_aux1_voltage_t;
typedef uint8_t raa489206_cut1_threshold_t;
typedef uint8_t raa489206_dut0_threshold_t;
typedef uint8_t raa489206_dut1_threshold_t;
typedef uint8_t raa489206_cot0_threshold_t;
typedef uint8_t raa489206_cot1_threshold_t;
typedef uint8_t raa489206_dot0_threshold_t;
typedef uint8_t raa489206_dot1_threshold_t;

/**********************************************************************************************************************
 Internal temperature
***********************************************************************************************************************/
/*0x22 Internal over temperature warning register*/
typedef uint8_t raa489206_iotw_th_t;

/*0x23 Internal over temperature fault register*/
typedef uint8_t raa489206_iotf_th_t;

/*Internal temperature register 0x5E*/
typedef uint8_t raa489206_internal_temperature_t;

/**********************************************************************************************************************
 Regulator Measurements and Detectors
***********************************************************************************************************************/
/*0x1B Vreg Operation register*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t VREG_TRIGGER            : 1; /* 0x1B.0 setting to 1 starts measurement of Vcc, Vvtem and Ireg*/
        uint8_t LP_REG                  : 1; /* 0x1B.1 selects the regulator that is on during LPM. 1 = strong, 0=weak*/
        uint8_t LD_DELAY                : 2; /* 0x1B.2...0x1B.3 Load Detect time delay (in s) before testing for load*/
        uint8_t UPDATE_OTHER            : 2; /* 0x1B.4...0x1B.5 Number of scans before ETAUX, Vbat1, Vcc, Ireg, Vtemp
                                                and IT are measured*/
        uint8_t COMM_TIMEOUT            : 2; /* 0x1B.6...0x1B.7 timeout period (in ms) to transition to LPM when no
                                                communication is receiveD*/
    }value_b;
} u_raa489206_vregop_register_t;

/*0x1C Vcc minimuim threshold register*/
typedef uint8_t raa489206_vcc_min_th_t;

/*0x1D IREGoc1 threshold - Limit compare to while the device is in SCAN or IDLE mode*/
typedef uint8_t raa489206_ireg_oc1_th_t;

/*0x1E IREGoc2 threshold - Limit compare to while the device is in Low Power Mode*/
typedef uint8_t raa489206_ireg_oc2_th_t;

/*0x5F Vvtemo Voltage: result from the measurement of the Vtemp pin voltage*/
typedef uint8_t raa489206_vtemp_voltage_t;

/*0x60 Vcc voltage*/
typedef uint8_t raa489206_vcc_voltage_t;

/*0x60-0x62 2-byte Ireg voltage*/
typedef union u_two_byte_lsb raa489206_ireg_voltage_t;

/**********************************************************************************************************************
 Vbat
***********************************************************************************************************************/
/*0x1F Vbat operation register */
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t  VBAT_TRIGGER           : 1; /*0x1F.0 setting to 1 triggers a Vbat measurement*/
        uint8_t  COM_TIMEOUT_EN         : 1; /*0x1F.1 Communication timeout enable*/
        uint8_t  OTHER_AVG              : 3; /*0x1F.2..0x1F.4 Number of samples to be averages before passing results*/
        uint8_t  ITEMP_TRIGGER          : 1; /*0x1F.5 setting to 1 starts an Itemp measurement*/
        uint8_t  ITEMP_ENABLE           : 1; /*0x1F.6 setting to 1 includes Itemp measurement during scans*/
        uint8_t  VBAT_ENABLE            : 1; /*0x1F.7 setting to 1 includes Vbat1 measurement during scans*/
    } value_b;
} u_raa489206_vbatop_register_t;


/*0x20 Vbat1 over-voltage register*/
typedef uint8_t raa489206_vbat1_ov_th_t;

/*0x21 Vbat1 under-voltage register*/
typedef uint8_t raa489206_vbat1_uv_th_t;

/*Vbat voltage 0x5C - 0x5D*/
typedef union u_two_byte_lsb u_raa489206_vbat1_register_t;

/**********************************************************************************************************************
 Power FET Controls and Open-Wire
***********************************************************************************************************************/
/*Power FET Operation 0x24*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t CFET_EN                         : 1; /*0x24.0 Charge FET enable. 1 activates CFET unless prevented by a related fault*/
        uint8_t DFET_EN                         : 1; /*0x24.1 Discharge FET enable. 1 activates CFET unless prevented by a related fault*/
        uint8_t ETA_CON                         : 1; /*0x24.2 External temperature and auxiliary port connect*/
        uint8_t VBAT1_CON                       : 1; /*0x24.3 VBAT connect bit*/
        uint8_t CELL_CON                        : 1; /*0x24.4 Vcell connect bit*/
        uint8_t OW_TRIGGER                      : 1; /*0x24.5 setting to 1 Initiates an open-wire test sequence*/
        uint8_t OW_EN                           : 1; /*0x24.6 set to 1 to include an OW test sequence during scans*/
        uint8_t CPMP_EN                         : 1; /*0x24.7 enables the charge pump in idle or scan modes if set to 1*/
    } value_b;

} u_raa489206_pwr_fet_op_t;

/**********************************************************************************************************************
 Cell Balancing
***********************************************************************************************************************/
/*0x25 Cell balancing operation*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t CB_CHRG             : 1; /*0x25.0 Cell balancing charge*/
        uint8_t CB_EOC              : 1; /*0x25.1 Cell balancing end of charge*/
        uint8_t CB_MASK             : 1; /*0x25.2 Cell balancing mask. Prevents adjacent cells from balancing at the same time*/
        uint8_t IEOC_EN             : 1; /*0x25.3 Current end of charge*/
        uint8_t CB_TRIGGER          : 1; /*0x25.4 CEll balancing trigger. When set triggers one cell balancing cycle*/
        uint8_t CB_CONFIG           : 1; /*0x25.5 Cell balancing configuration */
        uint8_t AUTO_CB_EN          : 1; /*0x25.6 Auto balancing enable*/
        uint8_t CB_EN               : 1; /*0x25.7 setting this bit enables cell balancing*/
    } value_b;
} u_raa489206_cb_op_register_t;

/*0x26-0x27 Cell balancing Cell state*/
typedef union u_two_byte_lsb u_raa489206_cb_cell_state_t;

/*0x2A Minimum delta threshold*/
typedef uint8_t raa489206_cb_min_delta_th_t;

/*0x2B Cell balancing maximum threshold*/
typedef uint8_t raa489206_cb_max_th_t;

/*0x2D Voltage end of charge threshold*/
typedef uint8_t raa489206_veoc_th_t;

/*0x10 Current end of charge threshold*/
typedef uint8_t raa489206_ieoc_th_t;

/*Cell balancing timers*/
union u_raa489206_cb_timer
{
    uint8_t value;

    struct
    {
        uint8_t UNIT            : 1; /*timer unit: 0: ms (default), 1: s*/
        uint8_t CB_TIMER        : 7; /*Cell balancing unit*/
    }value_b;
} ;

typedef enum e_raa489206_cb_fets_drive_config
{
    RAA489206_CB_FETS_DRIVE_INT  =   0x00, //Drive internal FETs
    RAA489206_CB_FETS_DRIVE_EXT  =   0x01, //Drive external FETs
} e_raa489206_cb_fets_drive_config;

/*0x28 Cell balancing ON timer*/
typedef union u_raa489206_cb_timer u_raa489206_cbon_timer_t;

/*0x28 Cell balancing OFF timer*/
typedef union u_raa489206_cb_timer u_raa489206_cboff_timer_t;

/**********************************************************************************************************************
 System Faults and Status
***********************************************************************************************************************/

/* 0x63 Priority fault: Failures related to the battery pack */
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t OVF                     : 1; /*0x63.0 (Any) Vcell over-voltage fault*/
        uint8_t UVF                     : 1; /*0x63.1 (Any) Vcell under-voltage fault*/
        uint8_t DSCF                    : 1; /*0x63.2 Discharge short current fault*/
        uint8_t DOCF                    : 1; /*0x63.3 Discharge over-temperature fault*/
        uint8_t COCF                    : 1; /*0x63.4 Charge overcurrent fault*/
        uint8_t IOTF                    : 1; /*0x63.5 Internal over-temperature fault */
        uint8_t OWF                     : 1; /*0x63.6 Open-wire fault (ORs Vbat, Vss, xT0 and xT1 OW tests)*/
        uint8_t VCCF                    : 1; /*0x63.7 Under-voltage event at the Vcc pin */
    } value_b;
} u_raa489206_prifault_register_t;

/* 0x83 Priority fault masks: it enable/disable the propagation of faults to the Alert pin.*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t OVFM                     : 1; /*0x83.0 (Any) Vcell over-voltage fault mask*/
        uint8_t UVFM                     : 1; /*0x83.1 (Any) Vcell under-voltage fault mask*/
        uint8_t DSCFM                    : 1; /*0x83.2 Discharge short current fault mask*/
        uint8_t DOCFM                    : 1; /*0x83.3 Discharge over-temperature fault mask*/
        uint8_t COCFM                    : 1; /*0x83.4 Charge overcurrent fault mask*/
        uint8_t IOTFM                    : 1; /*0x83.5 Internal over-temperature fault mask*/
        uint8_t OWFM                     : 1; /*0x83.6 Open-wire fault (ORs Vbat, Vss, xT0 and xT1 OW tests) mask*/
        uint8_t VCCFM                    : 1; /*0x83.7 Under-voltage event at the Vcc pin mask*/
    } value_b;
} u_raa489206_prifault_masks_t;

/*  0x64 ETAUX faults: Failures related to measured voltages at the xT0 and xT1 pins.*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t DUT0                     : 1; /*0x64.0 DUT fault when xT0 Voltage is below DUT0 th*/
        uint8_t DOT0                     : 1; /*0x64.1 DOT fault when xT0 Voltage is below DOT0 th*/
        uint8_t CUT0                     : 1; /*0x64.2 CUT fault when xT0 Voltage is below CUT0 th*/
        uint8_t COT0                     : 1; /*0x64.3 COT fault when xT0 Voltage is below COT0 th*/
        uint8_t DUT1                     : 1; /*0x64.4 DUT fault when xT1 Voltage is below DUT1 th*/
        uint8_t DOT1                     : 1; /*0x64.5 DOT fault when xT1 Voltage is below DOT1 th*/
        uint8_t CUT1                     : 1; /*0x64.6 CUT fault when xT1 Voltage is below CUT1 th*/
        uint8_t COT1                     : 1; /*0x64.7 COT fault when xT1 Voltage is below COT1 th*/
    } value_b;
} u_raa489206_etauxfault_reg_t;

/*  0x84 ETAUX faults masks: Enables/disables propagation of faults to the alert pin.*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t DUT0M                     : 1; /*0x84.0 DUT0 mask*/
        uint8_t DOT0M                     : 1; /*0x84.1 DOT0 mask*/
        uint8_t CUT0M                     : 1; /*0x84.2 CUT0 mask*/
        uint8_t COT0M                     : 1; /*0x84.3 COT0 mask*/
        uint8_t DUT1M                     : 1; /*0x84.4 DUT1 mask*/
        uint8_t DOT1M                     : 1; /*0x84.5 DOT1 mask*/
        uint8_t CUT1M                     : 1; /*0x84.6 CUT1 mask*/
        uint8_t COT1M                     : 1; /*0x84.7 COT1 mask*/
    } value_b;
} u_raa489206_etauxfault_masks_t;

/* 0x65 Other fault register*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t CRCF                    : 1; /*0x65.0 CRC sent by the MCU does not match the internal value */
        uint8_t OWVSS                   : 1; /*0x65.1 Open-wire fault on Vss pin*/
        uint8_t OWBVBAT                 : 1; /*0x65.2 Open-wire fault on Vbat pin*/
        uint8_t OW0                     : 1; /*0x65.3 Open-wire fault on pin xT0*/
        uint8_t OW1                     : 1; /*0x65.4 Open-wire fault on pin xT1*/
        uint8_t CPMP_NRDY               : 1; /*0x65.5 Charge pump not ready because of low Vcpmp voltage*/
        uint8_t VBUVF                   : 1; /*0x65.6 Vbat1 under-voltage fault*/
        uint8_t VBOVF                   : 1; /*0x65.7 Vbat1 over-voltage fault*/
    } value_b;
}u_raa489206_otherfault_reg_t;

/*  0x85 Other fault masks: enables/disables propagation of faults to the alert pin.*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t BUSYM                    : 1; /*0x85.0 Device busy mask */
        uint8_t RSV1                     : 1; /*0x85.1 reserved bit*/
        uint8_t RSV2                     : 1; /*0x85.2 reserved bit*/
        uint8_t RSV3                     : 1; /*0x85.3 reserved bit*/
        uint8_t RSV4                     : 1; /*0x85.4 reserved bit*/
        uint8_t CPMP_NRDYM               : 1; /*0x85.5 charge pump not ready mask*/
        uint8_t VBUVFM                   : 1; /*0x85.6 Vbat1 under-voltage fault*/
        uint8_t VBOVFM                   : 1; /*0x85.7 Vbat1 over-voltage fault*/
    } value_b;
}u_raa489206_otherfault_masks_t;

/*  0x66 Cell balancing and charging status register*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t NEEDCB                    : 1; /*0x66.0 need cell balancing */
        uint8_t TLOTCB                    : 1; /*0x66.1 Too low to perform cell balancing*/
        uint8_t THITCB                    : 1; /*0x66.2 Too high to perform cell balancing*/
        uint8_t DVCF                      : 1; /*0x66.3 Vcell max delta fault*/
        uint8_t VEOC                      : 1; /*0x66.4 Voltage end of charge achieved*/
        uint8_t IEOC                      : 1; /*0x66.5 Current end of charge achieved*/
        uint8_t IOTW                      : 1; /*0x66.6 Internal overtemperature warning*/
        uint8_t BATFULL                   : 1; /*0x66.7 Charging and aouto cell balancing has completed*/
    } value_b;
}u_raa489206_cbstatus_reg_t;

/*  0x86 Cell balancing and charging status masks.*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t NEEDCBM                    : 1; /*0x86.0 need cell balancing mask*/
        uint8_t TLOTCBM                    : 1; /*0x86.1 Too low to perform cell balancing mask*/
        uint8_t THITCBM                    : 1; /*0x86.2 Too high to perform cell balancing mask*/
        uint8_t DVCFM                      : 1; /*0x86.3 Vcell max delta fault mask*/
        uint8_t VEOCM                      : 1; /*0x86.4 Voltage end of charge achieved mask*/
        uint8_t IEOCM                      : 1; /*0x86.5 Current end of charge achieved mask*/
        uint8_t IOTWM                      : 1; /*0x86.6 Internal overtemperature warning mask*/
        uint8_t BATFULLM                   : 1; /*0x86.7 full charge mask*/
    } value_b;
}u_raa489206_cbstatus_masks_t;

/* 0x67 Status register: general status of the RAA489206 */
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t VTMPF                    : 1; /*0x67.0 Undervoltage of the Vtemp pin voltage*/
        uint8_t IREG2                    : 1; /*0x67.1 Regulator over-current while in LPM */
        uint8_t IREG1                    : 1; /*0x67.2 Regulator over-current while in IDLE or SCAN modes*/
        uint8_t OTHERF                   : 1; /*0x67.3 Other faults, i.e., communication time out and oscillator*/
        uint8_t LDPRESI                  : 1; /*0x67.4 Load present indicator*/
        uint8_t CHPRES                   : 1; /*0x67.5 Charger present*/
        uint8_t CHRGI                    : 1; /*0x67.6 Charge current indicator*/
        uint8_t DCHRGI                   : 1; /*0x67.7 Discharge current indicator*/
    } value_b;
}u_raa489206_status_reg_t;

/* 0x87 Status register masks*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t VTMPFM                    : 1; /*0x87.0 Vtemp under-voltage mask*/
        uint8_t IREG2M                    : 1; /*0x87.1 Regulator over-current while in LPM mask*/
        uint8_t IREG1M                    : 1; /*0x87.2 Regulator over-current while in IDLE or SCAN modes mask*/
        uint8_t OTHERFM                   : 1; /*0x87.3 Other faults, i.e., communication time out and oscillator, mask*/
        uint8_t LDPRESIM                  : 1; /*0x87.4 Load present indicator mask*/
        uint8_t CHPRESM                   : 1; /*0x87.5 Charger present mask*/
        uint8_t CHRGIM                    : 1; /*0x87.6 Charge current mask*/
        uint8_t DCHRGIM                   : 1; /*0x87.7 Discharge current mask*/
    } value_b;
}u_raa489206_status_masks_t;

/*  0x68-69 Open-wire Status register*/
typedef union
{
    uint16_t value;
    uint8_t lsb_value;

    struct
    {
        uint16_t lsb                        : 8;
        uint16_t msb                        : 8;
    } lsb_msb;

    struct
    {
        uint16_t OWCELL1                    : 1; /*0x68.0 Indicator of open wire in cell 1*/
        uint16_t OWCELL2                    : 1; /*0x68.1 Indicator of open wire in cell 2*/
        uint16_t OWCELL3                    : 1; /*0x68.2 Indicator of open wire in cell 3*/
        uint16_t OWCELL4                    : 1; /*0x68.3 Indicator of open wire in cell 4*/
        uint16_t OWCELL5                    : 1; /*0x68.4 Indicator of open wire in cell 5*/
        uint16_t OWCELL6                    : 1; /*0x68.5 Indicator of open wire in cell 6*/
        uint16_t OWCELL7                    : 1; /*0x68.6 Indicator of open wire in cell 7*/
        uint16_t OWCELL8                    : 1; /*0x68.7 Indicator of open wire in cell 8*/
        uint16_t OWCELL9                    : 1; /*0x69.0 Indicator of open wire in cell 9*/
        uint16_t OWCELL10                   : 1; /*0x69.1 Indicator of open wire in cell 10*/
        uint16_t OWCELL11                   : 1; /*0x69.2 Indicator of open wire in cell 11*/
        uint16_t OWCELL12                   : 1; /*0x69.3 Indicator of open wire in cell 12*/
        uint16_t OWCELL13                   : 1; /*0x69.4 Indicator of open wire in cell 13*/
        uint16_t OWCELL14                   : 1; /*0x69.5 Indicator of open wire in cell 14*/
        uint16_t OWCELL15                   : 1; /*0x69.6 Indicator of open wire in cell 15*/
        uint16_t OWCELL16                   : 1; /*0x69.7 Indicator of open wire in cell 16*/
    } value_b;
}u_raa489206_owstatus_reg_t;

/*  0x88-99 Open-wire Status masks*/
typedef union
{
    uint16_t value;
    uint8_t lsb_value;

    struct
    {
        uint16_t lsb                        : 8;
        uint16_t msb                        : 8;
    } lsb_msb;

    struct
    {
        uint16_t OWCELL1M                    : 1; /*0x88.0 OW cell1 mask*/
        uint16_t OWCELL2M                    : 1; /*0x88.1 OW cell2 mask*/
        uint16_t OWCELL3M                    : 1; /*0x88.2 OW cell3 mask*/
        uint16_t OWCELL4M                    : 1; /*0x88.3 OW cell4 mask*/
        uint16_t OWCELL5M                    : 1; /*0x88.4 OW cell5 mask*/
        uint16_t OWCELL6M                    : 1; /*0x88.5 OW cell6 mask*/
        uint16_t OWCELL7M                    : 1; /*0x88.6 OW cell7 mask*/
        uint16_t OWCELL8M                    : 1; /*0x88.7 OW cell8 mask*/
        uint16_t OWCELL9M                    : 1; /*0x89.0 OW cell9 mask*/
        uint16_t OWCELL10M                   : 1; /*0x89.1 OW cell10 mask*/
        uint16_t OWCELL11M                   : 1; /*0x89.2 OW cell11 mask*/
        uint16_t OWCELL12M                   : 1; /*0x89.3 OW cell12 mask*/
        uint16_t OWCELL13M                   : 1; /*0x89.4 OW cell13 mask*/
        uint16_t OWCELL14M                   : 1; /*0x89.5 OW cell14 mask*/
        uint16_t OWCELL15M                   : 1; /*0x89.6 OW cell15 mask*/
        uint16_t OWCELL16M                   : 1; /*0x89.7 OW cell16 mask*/
    } value_b;
}u_raa489206_ow_masks_t;

/**********************************************************************************************************************
 System Operation
***********************************************************************************************************************/

/*0x2E Scan operation register*/
typedef union
{
    uint8_t value;

    struct
    {
        uint8_t SCAN_DELAY                      : 3; /*Scan delay*/
        uint8_t LPT                             : 3; /*Low power timer*/
        uint8_t SYS_MODE                        : 2; /*System mode*/
    }value_b;
} u_raa489206_scanop_register_t;

/**********************************************************************************************************************
 END OF RAA489206 SYSTEM REGISTERS TYPES DEFINITIONS
***********************************************************************************************************************/

/*2byte CRC*/
typedef union
{
     uint16_t crc_word;

     struct
     {
         uint8_t lsb            : 8; /*LSB CRC*/
         uint8_t msb            : 8; /*MSB CRC*/
     }crc_b;
} u_crc_t;

/*SPI address*/
typedef union
{
    uint8_t address_byte;

    struct
    {
        uint8_t rw                      : 1; /*Read/write bit*/
        uint8_t dev_add                 : 7; /*7-bit device address */
    }rw_bits;
} u_raa489206_spi_address_t;

/** Definition of RAA489206 system registers */
typedef struct st_raa489206_system_registers
{
    //Device details
    st_bfe_register_t die_information;
    //Global IC Controls
    st_bfe_register_t global_operation;
    //Vcell and Ipack Controls
    st_bfe_register_t vcell_operation;
    st_bfe_register_t ipack_operation;
    st_bfe_register_t cell_select;
    st_bfe_register_t vcell_1;
    st_bfe_register_t vcell_2;
    st_bfe_register_t vcell_3;
    st_bfe_register_t vcell_4;
    st_bfe_register_t vcell_5;
    st_bfe_register_t vcell_6;
    st_bfe_register_t vcell_7;
    st_bfe_register_t vcell_8;
    st_bfe_register_t vcell_9;
    st_bfe_register_t vcell_10;
    st_bfe_register_t vcell_11;
    st_bfe_register_t vcell_12;
    st_bfe_register_t vcell_13;
    st_bfe_register_t vcell_14;
    st_bfe_register_t vcell_15;
    st_bfe_register_t vcell_16;
    st_bfe_register_t vcell_max_delta_voltage;
    st_bfe_register_t ipack_voltage;
    st_bfe_register_t ipack_timer;
    //Vcell Detectors
    st_bfe_register_t vcell_overvoltage_th;
    st_bfe_register_t vcell_undervoltage_th;
    st_bfe_register_t vcell_max_delta_th;
    st_bfe_register_t fault_delay;
    //Ipack detectors
    st_bfe_register_t discharge_short_current_th;
    st_bfe_register_t discharge_overcurrent_th;
    st_bfe_register_t dsc_delay;
    st_bfe_register_t oc_delay;
    st_bfe_register_t load_charge_operation;
    st_bfe_register_t charge_overcurrent_th;
    // External temperature/Auxiliary port (ETAUX) Controls
    st_bfe_register_t etaux_operation;
    st_bfe_register_t gpio_alrt_operation;
    st_bfe_register_t etaux0_voltage;
    st_bfe_register_t etaux1_voltage;
    // External temperature/Auxiliary port (ETAUX) Detectors
    st_bfe_register_t dut0_limit;
    st_bfe_register_t dot0_limit;
    st_bfe_register_t cut0_limit;
    st_bfe_register_t cot0_limit;

    st_bfe_register_t dut1_limit;
    st_bfe_register_t dot1_limit;
    st_bfe_register_t cut1_limit;
    st_bfe_register_t cot1_limit;
    //Internal Temperature
    st_bfe_register_t overtemperature_warning_th;
    st_bfe_register_t overtemperature_fault_th;
    st_bfe_register_t internal_temperature;
    //Voltage Regulator
    st_bfe_register_t vreg_operation;
    st_bfe_register_t vcc_minimum_th;
    st_bfe_register_t ireg_overcurrent1_th;
    st_bfe_register_t ireg_overcurrent2_th;
    st_bfe_register_t vtemp_voltage;
    st_bfe_register_t vcc_voltage;
    st_bfe_register_t ireg_voltage;
    //Vbat1 controls
    st_bfe_register_t vbat1_operation;
    st_bfe_register_t vbat1_ov_th;
    st_bfe_register_t vbat1_uv_th;
    st_bfe_register_t vbat1;
    //Power FET Controls and Open-Wire
    st_bfe_register_t power_fet_operation;
    //Cell balancing controls
    st_bfe_register_t cb_operation;
    st_bfe_register_t cb_cell_state;
    st_bfe_register_t cb_on_time;
    st_bfe_register_t cb_off_time;
    //Cell balancing detectors
    st_bfe_register_t cb_min_delta_th;
    st_bfe_register_t cb_max_th;
    st_bfe_register_t cb_min_th;
    st_bfe_register_t eoc_voltage_th;
    st_bfe_register_t eoc_current_th;
    //System faults and indicators
    st_bfe_register_t priority_faults;
    st_bfe_register_t etaux_faults;
    st_bfe_register_t other_faults;
    st_bfe_register_t cb_status;
    st_bfe_register_t status;
    st_bfe_register_t open_wire_status;
    st_bfe_register_t priority_faults_mask;
    st_bfe_register_t etaux_faults_mask;
    st_bfe_register_t other_faults_mask;
    st_bfe_register_t cb_status_masks;
    st_bfe_register_t status_masks;
    st_bfe_register_t open_wire_mask;
    //System Operation
    st_bfe_register_t scan_operation;
} st_raa489206_system_registers_t;



/*Device states*/
typedef enum e_raa489206_state
{
    RAA489206_STATE_INIT,                             ///> Just after reset/ Power on
    RAA489206_STATE_AWAKE,                            ///> Initial state on state transition
    RAA489206_STATE_DISCHARGING,                      ///> During discharging
    RAA489206_STATE_END_OF_CHARGE,                    ///> Cells are fully charged
    RAA489206_STATE_END_OF_DISCHARGE,                 ///> Cells are fully discharged
    RAA489206_STATE_LOW_POWER_MODE,                   ///> The BFE is in Low Power Mode (LPM)
    RAA489206_STATE_CHARGE_TEMPERATURE_FAULT,         ///> temperature fault while charging
    RAA489206_STATE_DISCHARGE_TEMPERATURE_FAULT,      ///> temperature fault while discharging
    RAA489206_STATE_SHORT_CURRENT,                    ///> Short current detected
    RAA489206_STATE_EXTRA_TEMP_FAULT,                 ///> abnormal temperature detected by an additional sensor
    RAA489206_STATE_POWER_DOWN,                       ///> BFE is powered down
    RAA489206_STATE_INITIAL_CALIBRATION,              ///> BFE is waiting for AD calibration
    RAA489206_STATE_CRITICAL_FAULT_OVER_VOLTAGE,      ///> Over voltage has been detected
    RAA489206_STATE_CRITICAL_FAULT_UNDER_VOLTAGE,     ///> Under voltage has been detected
    RAA489206_STATE_CRITICAL_FAULT_DELTA_VPACK,       ///> high difference between pack voltage and the cell sum
    RAA489206_STATE_CRITICAL_FAULT_DELTA_VCELL,       ///> high Vmax - Vmin
    RAA489206_STATE_WRONG_FIXED_DATA,                 ///> parameter setting error

} e_raa489206_state_t;

/*Extended configuration entity*/
typedef struct st_raa489206_extended_cfg
{
    float                           reg_resistor;               ///< Sense resistor between emitter and Vdd pins used to measure Ireg
    bool                            use_crc;                    ///< Use cyclic redundacy check
    bool                            enable_fuse_blow;           ///< enable fuse blow option
    bool                            enable_chr_pump_init;       ///< indicates whether the charge pump shall be enable during initialization
//    const spi_instance_t            * p_spi;                    ///< spi instance
//    const i2c_master_instance_t     * p_i2c;                    ///< i2c instance
//    const ioport_instance_t         * p_ioport;                 ///< ioport instance
//    bsp_io_port_pin_t               reset_pin;                  ///< reset pin port
//    bsp_io_port_pin_t               cms0_pin;                   ///< CMS0 pin port
//    bsp_io_port_pin_t               ss_pin;                     ///< Slave Selection pin
//    bsp_io_port_pin_t               i2c_add_sel_pin;            ///< I2C address selector pin
//    bsp_io_port_pin_t               alert_pin;                  ///< alert pin
//    bsp_io_port_pin_t               wakeup_pin;                 ///< Wakeup pin port
    uint8_t                         device_spi_add_no_crc;      ///< SPI slave address to read data
    uint8_t                         device_spi_add_with_crc;    ///< SPI slave address to read data using crc
    uint8_t                         device_i2c_add;             ///< I2C slave address

} st_raa489206_extended_cfg_t;

/* BFE RAA489206 control block. DO NOT INITIALIZE.  Initialization occurs when @ref bfe_api_t::init is called. */
typedef struct st_raa489206_instance_ctrl
{
    u_raa489206_cells_select_t                  cells_select;
//    const spi_instance_t                      * p_spi;            ///< spi instance
//    const i2c_master_instance_t               * p_i2c;            ///< i2c instance
//    const ioport_instance_t                   * p_ioport;         ///< ioport instance
//    bsp_io_port_pin_t                           reset_pin;        ///< reset pin port
//    bsp_io_port_pin_t                           cms0_pin;         ///< CMS0 pin port
//    bsp_io_port_pin_t                           ss_pin;           ///< Slave Selection pin if needed (SPI on SCI)
//    bsp_io_port_pin_t                           i2c_add_sel_pin;  ///< I2C address selector pin
//    bsp_io_port_pin_t                           alert_pin;        ///< alert pin
//    bsp_io_port_pin_t                           wakeup_pin;       ///< Wakeup pin port
    bool                                        init;             ///< Indicates whether the init() API has been successfully called.
    bool                                        use_crc;          ///< use crc feature and commands
    const st_bfe_cfg_t                        * p_cfg;            ///< Pointer to configuration entity
    st_raa489206_system_registers_t           * p_regs;           ///< raa489206 system registers
    e_bfe_err_t (* p_writeRegisterValues)(TysCdrvRaa4892xx_Obj * const me, uint8_t address, uint8_t const * p_values, uint16_t num_values, bool use_crc); ///< Pointer to  write function
    e_bfe_err_t (* p_readRegisterValues)(TysCdrvRaa4892xx_Obj * const me, uint8_t address, uint8_t * p_values, uint16_t num_values, bool use_crc); ///< pointer to read function
    bool read_after_write;
} st_raa489206_instance_ctrl_t;

/* BFE events masks: specifies which events should propagate to the device alert pin, which may generate an
 * MCU IRQ event. It also specifies delays for events such as short current , load detection, current direction*/
typedef struct
{
    u_raa489206_prifault_masks_t priority_masks;
    u_raa489206_etauxfault_masks_t etaux_masks;
    u_raa489206_otherfault_masks_t other_masks;
    u_raa489206_cbstatus_masks_t cb_masks;
    u_raa489206_status_masks_t status_masks;
    u_raa489206_ow_masks_t ow_masks;
    u_raa489206_vcell_fault_delay_t fault_delays;
    raa489206_dsc_delay_register_t dsc_delay;
    u_raa489206_oc_delay_t oc_delay;
    e_raa489206_ld_delay_t ld_delay;
    bool idir_delay;
} st_raa489206_events_masks_t;

/*type of fault*/
typedef enum
{
    RAA489206_FAULT_TYPE_PRIORITY    = 0x01,
    RAA489206_FAULT_TYPE_ETAUX       = 0x02,
    RAA489206_FAULT_TYPE_OTHER       = 0x03,
    RAA489206_FAULT_TYPE_CB          = 0x04,
    RAA489206_FAULT_TYPE_GENERAL     = 0x05,
    RAA489206_FAULT_TYPE_OW          = 0x06,
} e_raa489206_fault_type_t;

/* BFE status: reports the  status of the BFE*/
typedef struct
{
    u_raa489206_prifault_register_t priority_status;
    u_raa489206_etauxfault_reg_t etaux_status;
    u_raa489206_otherfault_reg_t other_status;
    u_raa489206_cbstatus_reg_t cb_status;
    u_raa489206_status_reg_t general_status;
    u_raa489206_owstatus_reg_t ow_status;
}st_raa489206_status_t;

/*RAA489206 continuous scan configuration*/

typedef struct
{
    uint8_t VCELL_EN                        : 1; /*Vcell measurement*/
    e_raa489206_vcell_avg_t VCELL_AVG        : 3; /*Number of samples to average*/
} st_raa489206_cs_cfg_vcell_t;

typedef struct
{
    uint8_t IPACK_EN                        : 1; /*I pack measurement*/
    e_raa489206_ipack_avg_t IPACK_AVG        : 3; /*Number of samples to average*/
} st_raa489206_cs_cfg_ipack_t;

typedef struct
{
    uint8_t OW_EN                           : 1; /*I pack measurement*/
    e_raa489206_ow_period_t  OW_UPDATE       : 2; /*How often the open-wire test is executed as part of the continuous scans*/
} st_raa489206_cs_cfg_open_wire_t;

typedef struct
{
    uint8_t VBAT_EN                                     : 1; /*enable vpack measurement*/
    uint8_t ITEMP_EN                                     : 1; /*enable internal temperature measurement*/
    e_raa489206_other_avg_t OTHER_AVG                    : 3; /*number of samples to average*/
    e_raa489206_otherupdate_period_t OTHER_UPDATE        : 2; /* number of scans required before ETAUX, Vbat,Vcc, Ireg and int. temp are made*/
} st_raa489206_cs_cfg_other_t;

typedef struct
{
    e_raa489206_etaux_enable_t ETAUX_EN                        : 2; /*External/auxiliar measurements*/
    e_raa489206_etaux_avg_t ETAUX_AVG                       : 3; /*Number of samples to average*/
} st_raa489206_cs_cfg_etaux_t;

typedef struct
{
    st_raa489206_cs_cfg_vcell_t vcell_cfg;
    st_raa489206_cs_cfg_ipack_t ipack_cfg;
    st_raa489206_cs_cfg_open_wire_t ow_cfg;
    st_raa489206_cs_cfg_other_t other_cfg;
    st_raa489206_cs_cfg_etaux_t etaux_cfg;
    e_raa489206_scan_delay_t scan_delay;
} st_raa489206_cs_config_t;

/*cell balancing timer unit*/
typedef enum
{
    RAA489206_CB_TIMER_UNIT_MS       = 0x00,
    RAA489206_CB_TIMER_UNIT_S        = 0x01,
} e_raa489206_cb_timer_unit_t;

typedef struct
{
    float veoc_th;
    float ieoc_th;
    u_raa489206_cb_op_register_t cb_operation;
    float min_delta_th;
    float cbmax_th;
    float cbmin_th;
    e_raa489206_cb_timer_unit_t cb_timer_unit;
    uint8_t cbon_time;
    uint8_t cboff_time;
} st_raa489206_cb_config;

typedef union
{

    float vector[3];

    struct
    {
        float vcc;
        float ireg;
        float vtemp;
    } measurements;
} u_raa489206_other_measurements_t;

typedef union
{
    float vector[17];

    struct{
        float cell1;
        float cell2;
        float cell3;
        float cell4;
        float cell5;
        float cell6;
        float cell7;
        float cell8;
        float cell9;
        float cell10;
        float cell11;
        float cell12;
        float cell13;
        float cell14;
        float cell15;
        float cell16;
        float vcell_max_delta;
    } measurements;
} u_raa489206_vcell_measurements_t;

typedef union
{
    float vector[2];

    struct
    {
        float xt0_aux0;
        float xt1_aux1;
    } measurements;
}u_raa489206_etaux_measurements_t;

typedef float st_raa489206_temperature_measurements_t;

typedef struct
{
    e_raa489206_lpm_timer_t LPM_TIMER       : 3; /*Low power mode timer*/
    e_raa489206_lpm_regulator_t REG_TYPE    : 1; /*Regulator type*/
    uint8_t COMTO_EN                        : 1; /*Enable communication time out*/
    e_raa489206_comm_timeout_t COM_TO       : 2; /*Communication timeout*/
    uint8_t LDLP                            : 1; /*Load detect while in low power mode*/
} st_raa489206_lpm_cfg_t;

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

extern const st_bfe_api_t g_bfe_raa489206_api;

extern u_raa489206_productionid_reg_t g_dieinformation_register;
extern u_raa489206_globalop_reg_t g_globalop_register;
extern u_raa489206_vcellop_reg_t g_vcellop_register;
extern u_raa489206_ipackop_reg_t g_ipackop_register;
extern u_raa489206_cells_select_t g_cells_select_register;
extern u_raa489206_vcell_voltage_t g_vcell1_voltage;
extern u_raa489206_vcell_voltage_t g_vcell2_voltage;
extern u_raa489206_vcell_voltage_t g_vcell3_voltage;
extern u_raa489206_vcell_voltage_t g_vcell4_voltage;
extern u_raa489206_vcell_voltage_t g_vcell5_voltage;
extern u_raa489206_vcell_voltage_t g_vcell6_voltage;
extern u_raa489206_vcell_voltage_t g_vcell7_voltage;
extern u_raa489206_vcell_voltage_t g_vcell8_voltage;
extern u_raa489206_vcell_voltage_t g_vcell9_voltage;
extern u_raa489206_vcell_voltage_t g_vcell10_voltage;
extern u_raa489206_vcell_voltage_t g_vcell11_voltage;
extern u_raa489206_vcell_voltage_t g_vcell12_voltage;
extern u_raa489206_vcell_voltage_t g_vcell13_voltage;
extern u_raa489206_vcell_voltage_t g_vcell14_voltage;
extern u_raa489206_vcell_voltage_t g_vcell15_voltage;
extern u_raa489206_vcell_voltage_t g_vcell16_voltage;
extern u_raa489206_vcell_max_delta_t g_vcell_max_delta;
extern u_raa489206_ipack_voltage_t g_ipack_voltage;
extern u_raa489206_ipack_timer_t g_ipack_timer_register;
extern raa489206_vcell_ov_th_t g_vcell_ov_th_register;
extern raa489206_vcell_uv_th_t g_vcell_uv_th_register;
extern raa489206_vcell_max_delta_th_t g_vcell_max_delta_th;
extern u_raa489206_vcell_fault_delay_t g_fault_delay_register;
extern raa489206_dsc_threshold_t g_dsc_threshold_register;
extern raa489206_doc_th_register_t g_doc_threshold_register;
extern raa489206_dsc_delay_register_t g_dsc_delay_register;
extern u_raa489206_scanop_register_t g_scanop_register;
extern raa489206_coc_th_register_t g_coc_threshold_register;
extern raa489206_vbat1_ov_th_t g_vbat1_ov_th_register;
extern raa489206_vbat1_uv_th_t g_vbat1_uv_th_register;
extern raa489206_iotw_th_t g_iotw_th_register;
extern raa489206_iotf_th_t g_iotf_th_register;
extern u_raa489206_vregop_register_t g_vregop_register;
extern u_raa489206_vbatop_register_t g_vbatop_register;
extern u_raa489206_vbat1_register_t g_vbat_register;
extern raa489206_internal_temperature_t g_internal_temp_register;
extern u_raa489206_prifault_register_t g_priority_faults;
extern u_raa489206_prifault_masks_t g_priority_masks;
extern u_raa489206_etauxfault_reg_t g_etaux_faults;
extern u_raa489206_etauxfault_masks_t g_etaux_masks;
extern u_raa489206_otherfault_reg_t g_other_faults;
extern u_raa489206_otherfault_masks_t g_other_masks;
extern u_raa489206_cbstatus_reg_t g_cb_status;
extern u_raa489206_cbstatus_masks_t g_cb_masks;
extern u_raa489206_status_reg_t g_status;
extern u_raa489206_status_masks_t g_status_masks;
extern u_raa489206_owstatus_reg_t g_ow_status;
extern u_raa489206_ow_masks_t g_ow_masks;
extern u_raa489206_oc_delay_t g_oc_delay;
extern u_raa489206_load_charge_oper_t g_load_charge_oper;
extern u_raa489206_etauxop_register_t g_etaux_oper;
extern u_raa489206_gpio_alrt_op_reg_t g_gpio_alrt_op;
extern raa489206_xt0_aux0_voltage_t g_xt0_aux0_voltage;
extern raa489206_xt1_aux1_voltage_t g_xt1_aux1_voltage;
extern raa489206_dut0_threshold_t g_dut0_th;
extern raa489206_dot0_threshold_t g_dot0_th;
extern raa489206_cut0_threshold_t g_cut0_th;
extern raa489206_cot0_threshold_t g_cot0_th;
extern raa489206_dut1_threshold_t g_dut1_th;
extern raa489206_dot1_threshold_t g_dot1_th;
extern raa489206_cut1_threshold_t g_cut1_th;
extern raa489206_cot1_threshold_t g_cot1_th;
extern raa489206_vcc_min_th_t g_vcc_min_th;
extern raa489206_ireg_oc1_th_t g_ireg_oc1_th;
extern raa489206_ireg_oc2_th_t g_ireg_oc2_th;
extern raa489206_vtemp_voltage_t g_vtemp_voltage;
extern raa489206_vcc_voltage_t g_vcc_voltage;
extern raa489206_ireg_voltage_t g_ireg_voltage;
extern u_raa489206_pwr_fet_op_t g_pwr_fet_op_register;
extern u_raa489206_cb_op_register_t g_cb_operation;
extern u_raa489206_cb_cell_state_t g_cb_cell_state;
extern u_raa489206_cbon_timer_t g_cbon_timer;
extern u_raa489206_cboff_timer_t g_cboff_timer;
extern raa489206_cb_min_delta_th_t g_cb_min_delta_th;
extern raa489206_cb_max_th_t g_cb_max_th;
extern raa489206_cb_min_delta_th_t g_cb_min_th;
extern raa489206_veoc_th_t g_veoc_th;
extern raa489206_ieoc_th_t g_ieoc_th;

extern const float s_vdoc_step_mv;
extern const float s_vdoc_offset_mv;
extern const float s_vcoc_step_mv;
extern const float s_vcoc_offset_mv;
extern const float s_vdsc_step_mv;
extern const float s_vdsc_offset_mv;
extern const float s_vcell_max_delta_step_mv;
extern const float s_vcell_max_delta_offset_mv;
extern const float s_vcell_ov_vthstep_mv;
extern const float s_vcell_uv_vthstep_mv;
extern const float s_vcell_ov_offset_mv;
extern const float s_vcell_uv_offset_mv;
extern const float s_vbat1_ov_step_mv;
extern const float s_vbat1_uv_step_mv;
extern const float s_vbat1_ov_offset_mv;
extern const float s_vbat1_uv_offset_mv;
extern const float s_vbat1_step_mv;
extern const float s_vcell_step_mv;
extern const float s_vcc_step_mv;
extern const float s_etaux_step_mv;
extern const float s_ireg_step_mv;
extern const float s_vtemp_step_mv;
extern const float s_vtemp_offset_mv;
extern const float s_ipack_lsb_mv;
extern const float s_veoc_step_mv;
extern const float s_veoc_offset_mv;
extern const float s_ieoc_step_mv;
extern const float s_ieoc_offset_mv;
extern const float s_cb_min_delta_step_mv;
extern const float s_cb_min_delta_offset_mv;
extern const float s_cb_max_step_mv;
extern const float s_cb_max_offset_mv;
extern const float s_cb_min_step_mv;
extern const float s_cb_min_offset_mv;
extern const uint8_t s_cb_timer_step;

///***********************************************************************************************************************
// * Public APIs
// **********************************************************************************************************************/

///**********************************************************************************************************************
// * Function Name: R_RAA489206_Init
// * Description  : Initialize device
// * Arguments    : p_ctrl control entity
// *              : p_cfg configuration entity
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_Init (st_bfe_ctrl_t * const p_ctrl, const st_bfe_cfg_t  * const p_cfg );

///**********************************************************************************************************************
// * Function Name: R_RAA489206_Reset
// * Description  : Reset device.
// * Argument     : p_ctrl- control entity
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_Reset (st_bfe_ctrl_t * const p_ctrl, e_bfe_reset_type_t reset_type);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_InitSystemScan
// * Description  : Initiate a scan.
// * Arguments    : p_ctrl control entity
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_StartSystemScan (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_InitContinuousScan
// * Description  : Initiate continuous scan operation.
// * Arguments    : p_ctrl control entity
// *              : st_cs_config continuous scan configuration
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_StartContinuousScan (st_bfe_ctrl_t * const p_ctrl, const bfe_cs_configuration_t * const st_cs_config);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_StopContinuousScan
// * Description  : Stop continuous scan operation.
// * Arguments    : p_ctrl control entity
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_StopContinuousScan (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_IsBusy
// * Description  : Returns device availability.
// * Argument     : p_ctrl control entity
// *              : p_is_busy pointer to boolean that will contain current availability status
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_IsBusy (st_bfe_ctrl_t * const p_ctrl, bool * p_is_busy);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadFaults
// * Description  : Read current device status and faults.
// * Arguments    : p_ctrl control entity
// *              : p_bfe_status pointer to a variable that will contain status and faults registers
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadStatus (st_bfe_ctrl_t * const p_ctrl, bfe_status_t * const p_bfe_status);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ClearFaults
// * Description  : Clear all device faults.
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ClearAllFaults (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ClearFault
// * Description  : Clear specified faults contained in a device-specific variable
// * Arguments    : p_ctrl control entity
// *              : p_bfe_status pointer to the device-specific variable that specifies the faults to be cleared
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ClearFault (st_bfe_ctrl_t * const p_ctrl, const bfe_status_t * const p_bfe_status);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadMode
// * Description  : Read current device mode.
// * Arguments    : p_ctrl control entity
// *              : p_bfe_mode pointer to the variable that will contain the current device mode
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadMode (st_bfe_ctrl_t * const p_ctrl, e_bfe_mode_t * const p_value);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadVpack
// * Description  : Read Vpack voltage.
// * Arguments    : p_ctrl control entity
// *              : p_value pointer to float value that will contain the Vpack voltage in [mV]
// *              : trigger boolean that specifies whether a measurement shall be triggered.
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadVpack (st_bfe_ctrl_t * const p_ctrl, float * const p_value, bool trigger);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadIpack
// * Description  : Read I pack current.
// * Arguments    : p_ctrl control entity
// *              : p_value pointer to a float variable that will contained the Ipack value in [mA]
// *              : trigger boolean that specifies whether a measurement shall be triggered.
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadIpack (st_bfe_ctrl_t * const p_ctrl, float * const p_value, bool trigger);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadVcells
// * Description  : Read Vcell voltages.
// * Arguments    : p_ctrl control
// *              : p_values pointer to device-specific variable that will contain the Vcell voltages in [mV]
// *              : trigger boolean that specifies whether a measurement shall be triggered.
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadVcells (st_bfe_ctrl_t * const p_ctrl, bfe_vcell_measurements_t * const p_values, bool trigger);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadOther
// * Description  : Read other measurements.
// * Arguments    : p_ctrl control entity
// *              : p_values pointer to device-specific variable that will contain other measurements
// *              : trigger boolean that specifies whether a measurement shall be triggered.
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadOther (st_bfe_ctrl_t * const p_ctrl, bfe_other_measurements_t * const p_values, bool trigger);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadAuxExt
// * Description  : Read auxiliary/external measurements.
// * Arguments    : p_ctrl control entity
// *              : p_values pointer to device-specific variable that will contain ETAUX measurements
// *              : trigger boolean that specifies whether a measurement shall be triggered.
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadAuxExt (st_bfe_ctrl_t * const p_ctrl, bfe_auxext_measurements_t * const p_values, bool trigger);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadTemperature
// * Description  : Read current internal temeperature.
// * Arguments    : p_ctrl control entity
// *              : p_value pointer to a device-specific variable that will contained the measured value in [°C]
// *              : trigger boolean that specifies whether a measurement shall be triggered.
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadTemperature (st_bfe_ctrl_t * const p_ctrl, bfe_auxext_measurements_t * const p_value, bool trigger);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_TurnChargePumpOn
// * Description  : Turn charge pump on.
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_TurnChargePumpOn (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_TurnChargePumpOff
// * Description  : Turn charge pump off.
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_TurnChargePumpOff (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_TurnDFetOn
// * Description  : Turn discharge FET on.
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_TurnDFetOn (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_TurnDFetOff
// * Description  : Turn discharge FET off.
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_TurnDFetOff (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_TurnCFetOn
// * Description  : Turn charge FET on.
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_TurnCFetOn (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_TurnCFetOff
// * Description  : Turn charge FET off.
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_TurnCFetOff (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_R_RAA489206_TurnDFetOnCFetOn
// * Description  : Turn discharge and charge FETs on.
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_TurnDFetOnCFetOn (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_TurnDFetOff
// * Description  : Turn discharge FET off and Charge FET on.
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_TurnDFetOffCFetOn (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_TurnDFetOnCFetOff
// * Description  : Turn discharge FET on and charge FET off.
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_TurnDFetOnCFetOff (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_TurnCFetOff
// * Description  : Turn discharge and charge FETs off.
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_TurnDFetOffCFetOff (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetAlerts
// * Description  : Set the events that propagate to the device alert pin.
// * Arguments    : p_alert_events pointer to a device-specific variable that contains the flags of events that shall
// *                assert the alarm pin
// * Return Value : bfe error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetAlerts (st_bfe_ctrl_t * const p_ctrl, const bfe_alerts_masks_t * const p_alert_events);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetDOC
// * Description  : Set Discharge over-current threshold.
// * Arguments    : p_ctrl control entity
// *              : current_ma current threshold in [mA]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetDOC (st_bfe_ctrl_t * const p_ctrl, float current_ma);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetCOC
// * Description  : Set charge over-current threshold.
// * Arguments    : p_ctrl control entity
// *              : current_ma current threshold in [mA]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetCOC (st_bfe_ctrl_t * const p_ctrl, float current_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetDSC
// * Description  : Set short-ciscuit threshold.
// * Arguments    : p_ctrl control entity
// *              : current_ma current threshold in [mA]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetDSC (st_bfe_ctrl_t * const p_ctrl, float current_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetCellUndevoltage
// * Description  : Set Cell under-voltage threshold.
// * Arguments    : p_ctrl control entity
// *              : cells_uv_th_mv under-voltage threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetCellUndevoltage (st_bfe_ctrl_t * const p_ctrl, float cells_uv_th_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetMaxVcellDeltaVoltage
// * Description  : Set the threshold of the maximum difference between cell voltages .
// * Arguments    : p_ctrl control entity
// *              : cells_maxd_th_mv maximum delta threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetMaxVcellDeltaVoltage(st_bfe_ctrl_t * const p_ctrl, float cells_maxd_th_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetVpacUndervoltage
// * Description  : Set Vpack under-voltage threshold.
// * Arguments    : p_ctrl control entity
// *              : vpack_uv_th_mv under-voltage threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetVpackUndervoltage (st_bfe_ctrl_t * const p_ctrl, float vpack_uv_th_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetCellUndevoltage
// * Description  : Set Cell over-voltage threshold.
// * Arguments    : p_ctrl control entity
// *              : cells_ov_th_mv over-voltage threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetCellOvervoltage (st_bfe_ctrl_t * const p_ctrl, float cells_ov_th_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetVpackOvervoltage
// * Description  : Set Vpack over-voltage threshold.
// * Arguments    : p_ctrl control entity
// *              : vpack_ov_th_mv over-voltage threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetVpackOvervoltage (st_bfe_ctrl_t * const p_ctrl, float vpack_ov_th_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetInternalOTWarning
// * Description  : Set internal over-temperature warning threshold.
// * Arguments    : p_ctrl control entity
// *              : temperature temperature in [°C]
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetInternalOTWarning (st_bfe_ctrl_t * const p_ctrl, float temperature);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetVoltageEndOfCharge
// * Description  : Set voltage end of charge threshold.
// * Arguments    : p_ctrl control entity
// *              : veoc_mv voltage end of charge threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetVoltageEndOfCharge (st_bfe_ctrl_t * const p_ctrl, float veoc_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetCurrentEndOfCharge
// * Description  : Set current end of charge threshold.
// * Arguments    : p_ctrl control entity
// *              : ieoc_ma current end of charge threshold in [mA]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetCurrentEndOfCharge (st_bfe_ctrl_t * const p_ctrl, float ieoc_ma);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetInternalOTFault
// * Description  : Set internal over-temperature fault threshold.
// * Arguments    : p_ctrl control entity
// *              : temperature temperature in [°C]
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetInternalOTFault (st_bfe_ctrl_t * const p_ctrl, float temperature);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_SetMode
// * Description  : transfer the device into a given mode
// * Argument     : p_ctrl control entity
// *              : bfe_mode BFE mode to be set
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_SetMode (st_bfe_ctrl_t * const p_ctrl, e_bfe_mode_t bfe_mode);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadAlerts
// * Description  : Read the events that propagate to the device alert pin.
// * Arguments    : p_alert_events pointer to a device-specific variable that contains the flags of events that shall
// *                assert the alarm pin
// * Return Value : bfe error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadAlerts (st_bfe_ctrl_t * const p_ctrl, bfe_alerts_masks_t * const p_alert_events);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadDOC
// * Description  : Read Discharge over-current threshold.
// * Arguments    : p_ctrl control entity
// *              : current_ma current threshold in [mA]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadDOC (st_bfe_ctrl_t * const p_ctrl, float * current_ma);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadCOC
// * Description  : Read charge over-current threshold.
// * Arguments    : p_ctrl control entity
// *              : current_ma current threshold in [mA]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadCOC (st_bfe_ctrl_t * const p_ctrl, float * current_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadDSC
// * Description  : Read short-circuit threshold.
// * Arguments    : p_ctrl control entity
// *              : current_ma current threshold in [mA]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadDSC (st_bfe_ctrl_t * const p_ctrl, float * current_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadCellUndevoltage
// * Description  : Read Cell under-voltage threshold.
// * Arguments    : p_ctrl control entity
// *              : cells_uv_th_mv under-voltage threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadCellUndevoltage (st_bfe_ctrl_t * const p_ctrl, float * cells_uv_th_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadMaxVcellDeltaVoltage
// * Description  : Read the threshold of the maximum difference between cell voltages .
// * Arguments    : p_ctrl control entity
// *              : cells_maxd_th_mv maximum delta threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadMaxVcellDeltaVoltage(st_bfe_ctrl_t * const p_ctrl, float * cells_maxd_th_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadVpacUndervoltage
// * Description  : Read Vpack under-voltage threshold.
// * Arguments    : p_ctrl control entity
// *              : vpack_uv_th_mv under-voltage threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadVpackUndervoltage (st_bfe_ctrl_t * const p_ctrl, float * vpack_uv_th_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadCellUndevoltage
// * Description  : Read Cell over-voltage threshold.
// * Arguments    : p_ctrl control entity
// *              : cells_ov_th_mv over-voltage threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadCellOvervoltage (st_bfe_ctrl_t * const p_ctrl, float * cells_ov_th_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadVpackOvervoltage
// * Description  : Read Vpack over-voltage threshold.
// * Arguments    : p_ctrl control entity
// *              : vpack_ov_th_mv over-voltage threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadVpackOvervoltage (st_bfe_ctrl_t * const p_ctrl, float * vpack_ov_th_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadInternalOTWarning
// * Description  : Read internal over-temperature fault threshold.
// * Arguments    : p_ctrl control entity
// *              : temperature temperature in [°C]
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadInternalOTWarning (st_bfe_ctrl_t * const p_ctrl, float * temperature);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadInternalOTFault
// * Description  : Read internal over-temperature warning threshold.
// * Arguments    : p_ctrl control entity
// *              : temperature temperature in [°C]
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadInternalOTFault (st_bfe_ctrl_t * const p_ctrl, float * temperature);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadVoltageEndOfCharge
// * Description  : Read voltage end of charge threshold.
// * Arguments    : p_ctrl control entity
// *              : p_veoc_mv voltage end of charge threshold in [mV]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadVoltageEndOfCharge (st_bfe_ctrl_t * const p_ctrl, float * veoc_mv);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadCurrentEndOfCharge
// * Description  : Read current end of charge threshold.
// * Arguments    : p_ctrl control entity
// *              : p_ieoc_ma current end of charge threshold in [mA]
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadCurrentEndOfCharge (st_bfe_ctrl_t * const p_ctrl, float * ieoc_ma);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ConfigLowPowerMode
// * Description  : Configuredevice low power mode settings.
// * Argument     : p_ctrl control entity.
// *              : p_lpm_options pointer to a device-defined variable which contains LPM configuration settings
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ConfigLowPowerMode (st_bfe_ctrl_t * const p_ctrl, bfe_lpm_cfg_t * const p_lpm_options);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_StartLowPowerMode
// * Description  : transfer the device into low power mode
// * Argument     : p_ctrl control entity
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_StartLowPowerMode (st_bfe_ctrl_t * const p_ctrl);


///**********************************************************************************************************************
// * Function Name: R_RAA489206_GetDieInformation
// * Description  : obtain die information
// * Argument     : p_ctrl control entity
// *              : p_information pointer to variable that will contain the die inforamtion
// * Return Value : bfe_error BFE error code
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_GetDieInformation (st_bfe_ctrl_t * const p_ctrl, st_bfe_information_t * p_information);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadRegister
// * Description  : read the given register
// * Argument     : p_ctrl control entity
// *              : p_bfe_register pointer to the register that will contain the read value
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadRegister (st_bfe_ctrl_t * const p_ctrl, st_bfe_register_t * const p_bfe_register);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_ReadAllRegisters
// * Description  : Read all registers
// * Arguments    : p_ctrl control entity that also contains a pointer to the register bank
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_ReadAllRegisters (st_bfe_ctrl_t * const p_ctrl);

///**********************************************************************************************************************
// * Function Name: R_RAA489206_WriteRegister
// * Description  : write the given register
// * Argument     : p_ctrl control entity
// *              :  p_bfe_register pointer to the register that contin the data to be written in the device
// * Return Value : bfe_error BFE error code.
// *********************************************************************************************************************/
//e_bfe_err_t R_RAA489206_WriteRegister (st_bfe_ctrl_t * const p_ctrl, const st_bfe_register_t * const bfe_register);


///***********************************************************************************************************************
// * Interruptions callbacks
// **********************************************************************************************************************/

///**********************************************************************************************************************
// * Function Name: spi_callback
// * Description  : Callback called during ISR of the SPI peripheral
// * Argument     : p_args pointer to callback arguments provided by the SPI ISR
// * Return Value : void
// *********************************************************************************************************************/
//void spi_callback (spi_callback_args_t *p_args);

///**********************************************************************************************************************
// * Function Name: i2c_callback
// * Description  : Callback called during ISR of the I2C peripheral
// * Argument     : p_args pointer to callback arguments provided by the SPI ISR
// * Return Value : void
// *********************************************************************************************************************/
//void i2c_callback (i2c_master_callback_args_t *p_args);

///**********************************************************************************************************************
// * Function Name: voltage_to_register
// * Description  : convert voltage to bfe register value
// * Argument     : voltage_mv voltage value in [mV]
// *                step voltage step of the register in [mV]
// *                offset offset of the register in [mV]
// * Return Value : register value
// *********************************************************************************************************************/
//uint8_t voltage_to_register (float voltage_mv, const float step, const float offset);

///**********************************************************************************************************************
// * Function Name: register_to_voltage
// * Description  : convert a register value to voltage in [mV]
// * Argument     : reg_val register value
// *                step voltage step of the register in [mV]
// *                offset offset of the register in [mV]
// * Return Value : voltage in [mV]
// *********************************************************************************************************************/
//float register_to_voltage (uint16_t reg_val, const float step, const float offset);

///**********************************************************************************************************************
// * Function Name: temperature_to_register
// * Description  : convert a temperature to bfe register value
// * Argument     : deg_val temperature value in [C]
// * Return Value : register value
// *********************************************************************************************************************/
//uint8_t temperature_to_register (float deg_val);

///**********************************************************************************************************************
// * Function Name: register_to_temperature
// * Description  : convert a register value to temperature in [C]
// * Argument     : reg_val register value
// * Return Value : temperature in [C]
// *********************************************************************************************************************/
//float register_to_temperature (uint8_t reg_val);

#endif /* APP_LIB_RAA489206_H_ */
