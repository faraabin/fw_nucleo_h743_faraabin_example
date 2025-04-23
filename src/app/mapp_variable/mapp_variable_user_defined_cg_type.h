/**
 ******************************************************************************
 *  @file         mapp_fb_type.h
 *  @brief        Mobin INV module
 *  @author       ...
 *  @version      0.0.0.1
 *  @date         yyyy/mm/dd
 *  @copyright    COPYRIGHT(c) 2018 MicroEmbeds
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
#if(!defined(__mapp_fb_type_H) || defined(TYPE_DICT))

/* Includes ------------------------------------------------------------------*/
#include "faraabin.h"
#include "faraabin_fobject_vartype_cg.h"

typedef_struct_(sCgTestStruct) {
  
  sm_(bool_t, CgB);
  sma_(bool_t, CgBa, 10);
  sm_(uint8_t, CgU8);
  sma_(uint8_t, CgU8a, 10);
  sm_(uint16_t, CgU16);
  sma_(uint16_t, CgU16a, 10);
  sm_(uint32_t, CgU32);
  sma_(uint32_t, CgU32a, 10);
  sm_(uint64_t, CgU64);
  sma_(uint64_t, CgU64a, 10);
  sm_(int8_t, CgI8);
  sma_(int8_t, CgI8a, 10);
  sm_(int16_t, CgI16);
  sma_(int16_t, CgI16a, 10);
  sm_(int32_t, CgI32);
  sma_(int32_t, CgI32a, 10);
  sm_(int64_t, CgI64);
  sma_(int64_t, CgI64a, 10);  
  sm_(float32_t, CgF32);
  sma_(float32_t, CgF32a, 10);
  sm_(float64_t, CgF64);
  sma_(float64_t, CgF64a, 10);
  
}typedef_struct_end_(sCgTestStruct);

typedef_enum_(eCgTestEnum) {
  
  em_(Cg)
  emv_(CgValue, 10)
  
}typedef_enum_end_(eCgTestEnum);

#if(!defined(TYPE_DICT))
  #define __mapp_fb_type_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Extern functions ----------------------------------------------------------*/
/* Extern Object or Variable -------------------------------------------------*/

/**End of Group_Name
  * @}
  */

#ifdef __cplusplus
} // extern "C"
#endif

#endif
#endif

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/
