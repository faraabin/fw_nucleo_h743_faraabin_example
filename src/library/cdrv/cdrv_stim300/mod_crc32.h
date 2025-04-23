/**
 ******************************************************************************
 *  @file       mod_crc32.h
 *  @brief       
 *  @details     
 *  @author     Adel Ghaderan
 *  @version    4.0.0
 *  @date       1396/05/02
 *  @pre         
 *  @bug         
 *  @warning     
 *  @copyright   GNU Public License.
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 @verbatim
 @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __mod_crc32_H
#define __mod_crc32_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint32_t ModCrc32_InitValue(uint32_t start);
uint32_t ModCrc32_FastCalculate(uint32_t sum, uint8_t *p, uint32_t len);
uint32_t ModCrc32_SlowCalculate(uint32_t sum, uint8_t *p, uint32_t len);

uint32_t ModCrc32_NewCalc(uint8_t *data, uint32_t lenght);

/* Extern functions ----------------------------------------------------------*/ 
/**End of Group_Name
  * @}
  */ 

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/********************************* END OF FILE ********************************/
