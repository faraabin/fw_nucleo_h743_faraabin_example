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
 * File Name    : r_bfe_raa489206_cfg.h
 * Version      : 1.1
 * Description  : Macros to select the BFE module settings to be set at compilation time.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 24.08.2021 1.00    Internal Release
 *         : 05.11.2021 1.10    Release
 *         : 24.01.2023 2.0     SOC application and CB commands
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef BFE_R_BFE_RAA489206_CFG_H_
#define BFE_R_BFE_RAA489206_CFG_H_

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/
/*Select either SPI (1) or I2C (0) communication interface*/
#define COMM_SPI (1)
/*Enable CRC SPI feature. Only valid for SPI communication interface*/
#define SPI_EN_CRC (1)
/*Default shunt resistor value in Ohms*/
#define DEFAULT_SHUNT_RES (0.005f)
/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

#endif /* BFE_R_BFE_RAA489206_CFG_H_ */
