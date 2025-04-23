/**
******************************************************************************
* @file           : mapp_variable_primitive.c
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

/* Includes ------------------------------------------------------------------*/
#include "mapp_variable_primitive.h"

#include "runtime_scaler.h"

#include <limits.h>

/* Private define ------------------------------------------------------------*/
#define ARRAY_SIZE  10

#define DEFAULT_FMIN    (-1234.4321f)
#define DEFAULT_FMAX    (1234.4321f)
#define DEFAULT_DMIN    (-1234.43211234)
#define DEFAULT_DMAX    (1234.43211234)

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
static bool TestVarB8 = true;
static bool TestVarB8Clone;
static bool TestVarBa8[ARRAY_SIZE] = {true, false, true, false, true, false, true, false, true, false};

static uint8_t TestVarU8 = CHAR_MAX;
static uint8_t TestVarU8Clone;
static uint8_t TestVarUa8[ARRAY_SIZE] = {CHAR_MAX, CHAR_MIN, CHAR_MAX, CHAR_MIN, CHAR_MAX, CHAR_MIN, CHAR_MAX, CHAR_MIN, CHAR_MAX, CHAR_MIN};

static uint16_t TestVarU16 = USHRT_MAX;
static uint16_t TestVarU16Clone;
static uint16_t TestVarUa16[ARRAY_SIZE] = {USHRT_MAX, CHAR_MIN, USHRT_MAX, CHAR_MIN, USHRT_MAX, CHAR_MIN, USHRT_MAX, CHAR_MIN, USHRT_MAX, CHAR_MIN};

static uint32_t TestVarU32 = UINT_MAX;
static uint32_t TestVarU32Clone;
static uint32_t TestVarUa32[ARRAY_SIZE] = {UINT_MAX, CHAR_MIN, UINT_MAX, CHAR_MIN, UINT_MAX, CHAR_MIN, UINT_MAX, CHAR_MIN, UINT_MAX, CHAR_MIN};

static uint64_t TestVarU64 = ULLONG_MAX;
static uint64_t TestVarU64Clone;
static uint64_t TestVarUa64[ARRAY_SIZE] = {ULLONG_MAX, CHAR_MIN, ULLONG_MAX, CHAR_MIN, ULLONG_MAX, CHAR_MIN, ULLONG_MAX, CHAR_MIN, ULLONG_MAX, CHAR_MIN};

static int8_t TestVarI8 = SCHAR_MIN;
static int8_t TestVarI8Clone;
static int8_t TestVarIa8[ARRAY_SIZE] = {SCHAR_MAX, SCHAR_MIN, SCHAR_MAX, SCHAR_MIN, SCHAR_MAX, SCHAR_MIN, SCHAR_MAX, SCHAR_MIN, SCHAR_MAX, SCHAR_MIN};

static int16_t TestVarI16 = SHRT_MIN;
static int16_t TestVarI16Clone;
static int16_t TestVarIa16[ARRAY_SIZE] = {SHRT_MAX, SHRT_MIN, SHRT_MAX, SHRT_MIN, SHRT_MAX, SHRT_MIN, SHRT_MAX, SHRT_MIN, SHRT_MAX, SHRT_MIN};

static int32_t TestVarI32 = INT_MIN;
static int32_t TestVarI32Clone;
static int32_t TestVarIa32[ARRAY_SIZE] = {INT_MAX, INT_MIN, INT_MAX, INT_MIN, INT_MAX, INT_MIN, INT_MAX, INT_MIN, INT_MAX, INT_MIN};

static int64_t TestVarI64 = LLONG_MIN;
static int64_t TestVarI64Clone;
static int64_t TestVarIa64[ARRAY_SIZE] = {LLONG_MAX, LLONG_MIN, LLONG_MAX, LLONG_MIN, LLONG_MAX, LLONG_MIN, LLONG_MAX, LLONG_MIN, LLONG_MAX, LLONG_MIN};

static float TestVarF32 = DEFAULT_FMAX;
static float TestVarF32Clone;
static float TestVarFa32[ARRAY_SIZE] = {DEFAULT_FMIN, DEFAULT_FMAX, DEFAULT_FMIN, DEFAULT_FMAX, DEFAULT_FMIN, DEFAULT_FMAX, DEFAULT_FMIN, DEFAULT_FMAX, DEFAULT_FMIN, DEFAULT_FMAX};

static double TestVarF64 = DEFAULT_DMAX;
static double TestVarF64Clone;
static double TestVarFa64[ARRAY_SIZE] = {DEFAULT_DMIN, DEFAULT_DMAX, DEFAULT_DMIN, DEFAULT_DMAX, DEFAULT_DMIN, DEFAULT_DMAX, DEFAULT_DMIN, DEFAULT_DMAX, DEFAULT_DMIN, DEFAULT_DMAX};

static uint32_t TestVarExternalUa32[ARRAY_SIZE];

FARAABIN_CONTAINER_DEF_(MappVariablePrimitiveContainer);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

/**
 * @brief 
 * 
 * @param accessType 
 * @param varPtr 
 * @param data 
 * @param size 
 * @return uint8_t 
 */
static uint8_t TestVarExternalAccessCallback(bool isWrite, uint32_t varPtr, uint8_t *data, uint16_t size) {
  
  if(varPtr > (uint32_t)&TestVarExternalUa32[ARRAY_SIZE - 1]) {
    return 1;
  }
  
  if((varPtr % (uint32_t)TestVarExternalUa32) != 0) {
    return 1;
  }
  
  if((size % 4) != 0) {
    return 1;
  }

  if(isWrite) {
    memcpy((void*)varPtr, data, size);
  }

  if(!isWrite) {
    data = (uint8_t*)varPtr;
  }

  return 0;
}

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappVariablePrimitive = {
  .Name = "MappVariablePrimitive",
  .Init = AppInit,
  .Start = AppStart,
  .Run = AppRun,
  .Terminate = AppTerminate
};

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Exported Functions #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/


/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Private Functions #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
* @brief 
* 
* @return uint8_t 
*/
uint8_t AppInit(void) {

  return 0;
}

/**
 * @brief 
 * 
 * @param param 
 * @return uint8_t 
 */
uint8_t AppStart(void* param) {

  FARAABIN_Container_Init_(&MappVariablePrimitiveContainer);

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {
  
  TestVarB8Clone = TestVarB8;
  TestVarU8Clone = TestVarU8;
  TestVarU16Clone = TestVarU16;
  TestVarU32Clone = TestVarU32;
  TestVarU64Clone = TestVarU64;
  TestVarI8Clone = TestVarI8;
  TestVarI16Clone = TestVarI16;
  TestVarI32Clone = TestVarI32;
  TestVarI64Clone = TestVarI64;
  TestVarF32Clone = TestVarF32;
  TestVarF64Clone = TestVarF64;
  
  for(uint8_t i = 0; i < ARRAY_SIZE;) {
    
    TestVarBa8[i + 1] = TestVarBa8[i];
    TestVarUa8[i + 1] = TestVarUa8[i];
    TestVarUa16[i + 1] = TestVarUa16[i];
    TestVarUa32[i + 1] = TestVarUa32[i];
    TestVarUa64[i + 1] = TestVarUa64[i];
    TestVarIa8[i + 1] = TestVarIa8[i];
    TestVarIa16[i + 1] = TestVarIa16[i];
    TestVarIa32[i + 1] = TestVarIa32[i];
    TestVarIa64[i + 1] = TestVarIa64[i];
    TestVarFa32[i + 1] = TestVarFa32[i];
    TestVarFa64[i + 1] = TestVarFa64[i];
    TestVarExternalUa32[i + 1] = TestVarExternalUa32[i];
    
    i = i + 2;
    
  }
  
  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppTerminate(void) {

  return 0;
}

/**
 * @brief 
 * 
 */
FARAABIN_CONTAINER_FUNC_(MappVariablePrimitiveContainer) {
  
  FARAABIN_SET_PATH_("TEST_UNSIGNED");
  
  FARAABIN_VAR_BOOL_(TestVarB8);
  FARAABIN_VAR_BOOL_(TestVarB8Clone);
  FARAABIN_VAR_BOOL_ARRAY_(TestVarBa8);
  
  FARAABIN_VAR_U8_(TestVarU8);
  FARAABIN_VAR_U8_(TestVarU8Clone);
  FARAABIN_VAR_U8_ARRAY_(TestVarUa8);
  
  FARAABIN_VAR_U16_(TestVarU16);
  FARAABIN_VAR_U16_(TestVarU16Clone);
  FARAABIN_VAR_U16_ARRAY_(TestVarUa16);

  FARAABIN_VAR_U32_(TestVarU32);
  FARAABIN_VAR_U32_(TestVarU32Clone);
  FARAABIN_VAR_U32_ARRAY_(TestVarUa32);

  FARAABIN_VAR_U64_(TestVarU64);
  FARAABIN_VAR_U64_(TestVarU64Clone);
  FARAABIN_VAR_U64_ARRAY_(TestVarUa64);

  FARAABIN_SET_PATH_("TEST_SIGNED");
  
  FARAABIN_VAR_I8_(TestVarI8);
  FARAABIN_VAR_I8_(TestVarI8Clone);
  FARAABIN_VAR_I8_ARRAY_(TestVarIa8);
  
  FARAABIN_VAR_I16_(TestVarI16);
  FARAABIN_VAR_I16_(TestVarI16Clone);
  FARAABIN_VAR_I16_ARRAY_(TestVarIa16);

  FARAABIN_VAR_I32_(TestVarI32);
  FARAABIN_VAR_I32_(TestVarI32Clone);
  FARAABIN_VAR_I32_ARRAY_(TestVarIa32);

  FARAABIN_VAR_I64_(TestVarI64);
  FARAABIN_VAR_I64_(TestVarI64Clone);
  FARAABIN_VAR_I64_ARRAY_(TestVarIa64);

  FARAABIN_SET_PATH_("TEST_FLOAT");

  FARAABIN_VAR_F32_(TestVarF32);
  FARAABIN_VAR_F32_(TestVarF32Clone);
  FARAABIN_VAR_F32_ARRAY_(TestVarFa32);
  
  FARAABIN_VAR_F64_(TestVarF64);
  FARAABIN_VAR_F64_(TestVarF64Clone);
  FARAABIN_VAR_F64_ARRAY_(TestVarFa64);
  
  FARAABIN_SET_PATH_("TEST_EXTERNAL");
  
  FARAABIN_VAR_U32_ARRAY_CB_(TestVarExternalUa32, TestVarExternalAccessCallback);

  FARAABIN_CONTAINER_FUNC_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
