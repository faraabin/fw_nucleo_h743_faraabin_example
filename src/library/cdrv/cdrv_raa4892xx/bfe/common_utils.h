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
 * File Name    : common_utils.h
 * Version      : 1.1
 * Description  : Common macros and utilities.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 24.08.2021 1.00    Internal Release
 *         : 05.11.2021 1.10    Release
 *         : 24.01.2023 2.0     SOC application and CB commands
 *********************************************************************************************************************/

#ifndef BFE_COMMON_UTILS_H
#define BFE_COMMON_UTILS_H

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdint.h>

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

///*Set register bit*/
//#define SET_BIT(REGISTER,BIT) ((REGISTER) |=  (1<<(BIT)))
///*Clear register bit*/
//#define CLR_BIT(REGISTER,BIT) ((REGISTER) &= ~((0x01)<<(BIT)))
//#define READ_BIT(REGISTER,BIT) ((REGISTER) & (1<<(BIT)))
///*Set mask*/
//#define SET_MASK(REGISTER,MASK) ((REGISTER) |=  (MASK))
///*Clear mask*/
//#define CLEAR_MASK(REGISTER,MASK) ((REGISTER) &=  (~(MASK)))
///*get mask*/
//#define GET_MASK(REGISTER,MASK) ((REGISTER) &  (MASK))

///*Null character definition*/
//#define NULL_CHAR       ('\0')

///*Unused variable*/
//#define UNUSED(x) ((void)(x))

/* All BFE error codes are returned using this macro. Calls returns error- if condition "a" is false. Used
 * to identify runtime errors in BFE implementations. */
#define BFE_ERROR_RETURN(a, err)                       (\
    {                                                   \
        if ((a))                                        \
        {                                               \
            (void) 0;                  /* Do nothing */ \
        }                                               \
        else                                            \
        {                         \
            return (err);                                 \
        }                                               \
    })

#define BFE_ERROR_VOID(a)                       (\
    {                                                   \
        if ((a))                                        \
        {                                               \
            (void) 0;                  /* Do nothing */ \
        }                                               \
        else                                            \
        {                         \
            return;                                 \
        }                                               \
    })

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

#endif /* BFE_COMMON_UTILS_H_ */
