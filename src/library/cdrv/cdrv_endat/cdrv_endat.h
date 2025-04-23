/**
******************************************************************************
* @file           : cdrv_endat.h
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2024 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2024 FaraabinCo.
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
#ifndef __cdrv_endat_H
#define __cdrv_endat_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\Core\me_type.h"
#include "library\driver\intf\me_hal_spi_intf.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 * @brief 
 * 
 */
typedef enum {
  eENDAT_VERSION_2p1,
  eENDAT_VERSION_2p2
}TyeEnDat_Version;

/**
 * @brief 
 * 
 */
#pragma push
#pragma pack(8)
typedef struct {
  
  bool init; /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TyeEnDat_Version u_version;   /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysSpi_Obj *u_spi;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint8_t u_resolution;         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint8_t u_mac_cycle_timeout;  /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  void(*u_data_dir_output)(void); /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  void(*u_data_dir_input)(void); /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint32_t u_value_raw;         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  bool u_alarm;                 /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  float u_value_degree;         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
	
	uint8_t u_crc;								/*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
	
	bool u_data_valid;						/*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  float coef;                   /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
}TysCdrvEnDat_Obj;
#pragma pop

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvEnDat_Init(TysCdrvEnDat_Obj * const me);
uint8_t fCdrvEnDat_Update(TysCdrvEnDat_Obj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_ENDAT_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
