/**
******************************************************************************
* @file           : bsp_config.h
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2023 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2023 FaraabinCo.
* All rights reserved.</center></h2>
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
* @verbatim
* @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __bsp_config_H
#define __bsp_config_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported defines ----------------------------------------------------------*/
#define EXTERNAL_CLOCK_ENABLE

#define FARAABIN_LINK_SERIAL
//#define FARAABIN_LINK_ETHERNET

#if defined(FARAABIN_LINK_SERIAL) && defined(FARAABIN_LINK_ETHERNET)
#error "Select either FARAABIN_LINK_SERIAL or FARAABIN_LINK_ETHERNET"
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BSP_CONFIG_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
