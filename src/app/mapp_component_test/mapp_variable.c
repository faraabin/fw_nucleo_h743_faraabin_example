/**
******************************************************************************
* @file           : mapp_variable.c
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
#include "mapp_variable.h"

#include <limits.h>
#include "faraabin.h"

/* Private define ------------------------------------------------------------*/
#define ARRAY_SIZE	10

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct {
	float f32a[ARRAY_SIZE];
	float f32;
}sFlatStruct;

typedef struct {
	
	sFlatStruct elmFsa[ARRAY_SIZE];
	sFlatStruct elmFs;
	uint8_t elmU8;
	uint8_t elmU8a[ARRAY_SIZE];
	
}sNestedStruct;

typedef enum {
	eENUM1B_TEST0 = 0,
	eENUM1B_TEST1 = 10,
	eENUM1B_TEST2 = 20,
	eENUM1B_TEST3 = 30,
	eENUM1B_TEST4 = 40,
	eENUM1B_TEST5 = 50,
	eENUM1B_TEST6 = 60,
	eENUM1B_TEST7 = 70,
	eENUM1B_TEST8 = 80
}eEnum1Byte;

typedef enum {
	eENUM2B_TEST0 = -1000,
	eENUM2B_TEST1 = -100,
	eENUM2B_TEST2 = -10,
	eENUM2B_TEST3 = -1,
	eENUM2B_TEST4 = 0,
	eENUM2B_TEST5 = 1,
	eENUM2B_TEST6 = 10,
	eENUM2B_TEST7 = 100,
	eENUM2B_TEST8 = 1000
}eEnum2Byte;

typedef enum {
	eENUM4B_TEST0 = -65536,
	eENUM4B_TEST1 = -100,
	eENUM4B_TEST2 = -10,
	eENUM4B_TEST3 = -1,
	eENUM4B_TEST4 = 0,
	eENUM4B_TEST5 = 1,
	eENUM4B_TEST6 = 10,
	eENUM4B_TEST7 = 100,
	eENUM4B_TEST8 = 65536
}eEnum4Byte;

/* Private variables ---------------------------------------------------------*/
static bool test_var_b8;
static bool test_var_b8_copy;
static bool test_var_ba8[ARRAY_SIZE];
//static bool *test_var_b8p;
static uint8_t test_var_u8;
static uint8_t test_var_u8_copy;
static uint8_t test_var_ua8[ARRAY_SIZE];
//static uint8_t *test_var_u8p;
static uint16_t test_var_u16;
static uint16_t test_var_u16_copy;
static uint16_t test_var_ua16[ARRAY_SIZE];
//static uint16_t *test_var_u16p;
static uint32_t test_var_u32;
static uint32_t test_var_u32_copy;
static uint32_t test_var_ua32[ARRAY_SIZE];
//static uint32_t *test_var_u32p;
static uint64_t test_var_u64;
static uint64_t test_var_u64_copy;
static uint64_t test_var_ua64[ARRAY_SIZE];
//static uint64_t *test_var_u64p;
static int8_t test_var_i8;
static int8_t test_var_i8_copy;
static int8_t test_var_ia8[ARRAY_SIZE];
//static int8_t *test_var_i8p;
static int16_t test_var_i16;
static int16_t test_var_i16_copy;
static int16_t test_var_ia16[ARRAY_SIZE];
//static int16_t *test_var_i16p;
static int32_t test_var_i32;
static int32_t test_var_i32_copy;
static int32_t test_var_ia32[ARRAY_SIZE];
//static int32_t *test_var_i32p;
static int64_t test_var_i64;
static int64_t test_var_i64_copy;
static int64_t test_var_ia64[ARRAY_SIZE];
//static int64_t *test_var_i64p;
static float test_var_f32;
static float test_var_f32_copy;
static float test_var_fa32[ARRAY_SIZE];
//static float *test_var_f32p;
static double test_var_f64;
static double test_var_f64_copy;
static double test_var_fa64[ARRAY_SIZE];
//static double *test_var_f64p;
//static double *test_var_fa64p[ARRAY_SIZE];
static sNestedStruct test_var_struct;
static sNestedStruct test_var_struct_copy;
static sNestedStruct test_var_structa[ARRAY_SIZE];
//static sNestedStruct *test_var_structp;
//static float test_var_external[ARRAY_SIZE];
//static float test_var_external_copy[ARRAY_SIZE];
static eEnum1Byte test_var_enum1b;
static eEnum1Byte test_var_enum1b_copy;
static eEnum1Byte test_var_enum1ba[ARRAY_SIZE];
//static eEnum1Byte *test_var_enum1bp;
static eEnum2Byte test_var_enum2b;
static eEnum2Byte test_var_enum2b_copy;
static eEnum2Byte test_var_enum2ba[ARRAY_SIZE];
//static eEnum2Byte *test_var_enum2bp;
static eEnum4Byte test_var_enum4b;
static eEnum4Byte test_var_enum4b_copy;
static eEnum4Byte test_var_enum4ba[ARRAY_SIZE];
//static eEnum4Byte *test_var_enum4bp;

FARAABIN_DICT_GROUP_DEF_(mappVariableDictGroup);
FARAABIN_VAR_TYPE_DEF_(sFlatStruct);
FARAABIN_VAR_TYPE_DEF_(sNestedStruct);
FARAABIN_VAR_TYPE_DEF_(eEnum1Byte);
FARAABIN_VAR_TYPE_DEF_(eEnum2Byte);
FARAABIN_VAR_TYPE_DEF_(eEnum4Byte);

/**
 * @brief 
 * 
 */
static FARAABIN_VAR_TYPE_STRUCT_FUNC_(sFlatStruct)
{
	FARAABIN_VAR_TYPE_STRUCT_FUNC_START_(sFlatStruct);
	
	FARAABIN_VAR_TYPE_STRUCT_MEMBER_(float32_t, f32a, ARRAY_SIZE);
	FARAABIN_VAR_TYPE_STRUCT_MEMBER_(float32_t, f32, 1);
	
	FARAABIN_VAR_TYPE_STRUCT_FUNC_END_(sFlatStruct);
}

/**
 * @brief 
 * 
 */
static FARAABIN_VAR_TYPE_STRUCT_FUNC_(sNestedStruct)
{
	FARAABIN_VAR_TYPE_STRUCT_FUNC_START_(sNestedStruct);
	
	FARAABIN_VAR_TYPE_STRUCT_MEMBER_(sFlatStruct, elmFsa, ARRAY_SIZE);
	FARAABIN_VAR_TYPE_STRUCT_MEMBER_(sFlatStruct, elmFs, 1);
	FARAABIN_VAR_TYPE_STRUCT_MEMBER_(uint8_t, elmU8a, ARRAY_SIZE);
	FARAABIN_VAR_TYPE_STRUCT_MEMBER_(uint8_t, elmU8, 1);
	
	FARAABIN_VAR_TYPE_STRUCT_FUNC_END_(sNestedStruct);
}

/**
 * @brief 
 * 
 */
static FARAABIN_VAR_TYPE_ENUM_FUNC_(eEnum1Byte) {
	
	FARAABIN_VAR_TYPE_ENUM_FUNC_START_(eEnum1Byte);
	
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM1B_TEST0);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM1B_TEST1);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM1B_TEST2);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM1B_TEST3);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM1B_TEST4);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM1B_TEST5);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM1B_TEST6);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM1B_TEST7);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM1B_TEST8);
	
	FARAABIN_VAR_TYPE_ENUM_FUNC_END_(eEnum1Byte);
}

/**
 * @brief 
 * 
 */
static FARAABIN_VAR_TYPE_ENUM_FUNC_(eEnum2Byte) {
	
	FARAABIN_VAR_TYPE_ENUM_FUNC_START_(eEnum2Byte);
	
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM2B_TEST0);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM2B_TEST1);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM2B_TEST2);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM2B_TEST3);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM2B_TEST4);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM2B_TEST5);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM2B_TEST6);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM2B_TEST7);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM2B_TEST8);
	
	FARAABIN_VAR_TYPE_ENUM_FUNC_END_(eEnum2Byte);
}

/**
 * @brief 
 * 
 */
static FARAABIN_VAR_TYPE_ENUM_FUNC_(eEnum4Byte) {
	
	FARAABIN_VAR_TYPE_ENUM_FUNC_START_(eEnum4Byte);
	
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM4B_TEST0);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM4B_TEST1);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM4B_TEST2);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM4B_TEST3);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM4B_TEST4);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM4B_TEST5);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM4B_TEST6);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM4B_TEST7);
	FARAABIN_VAR_TYPE_ENUM_MEMBER_(eENUM4B_TEST8);
	
	FARAABIN_VAR_TYPE_ENUM_FUNC_END_(eEnum4Byte);
}

static char* mappVariablePath = "APP\\MAPP_VARIABLE";
static char* mappVariableEmptyPath = "";
static char* mappVariableNullPath = NULL;

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

static uint8_t AppHardwareInit(void);
static uint8_t AppBehaviourInit(void);

//static uint8_t ExternalVariableInterface(bool isWrite, uint32_t varPtr, uint8_t *data, uint16_t size);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock mappVariable = {
  .Name = "mappVariable",
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

  AppHardwareInit();
  AppBehaviourInit();

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {
	
	test_var_b8_copy = test_var_b8;
	test_var_u8_copy = test_var_u8;
	test_var_u16_copy = test_var_u16;
	test_var_u32_copy = test_var_u32;
	test_var_u64_copy = test_var_u64;
	test_var_i8_copy = test_var_i8;
	test_var_i16_copy = test_var_i16;
	test_var_i32_copy = test_var_i32;
	test_var_i64_copy = test_var_i64;
	test_var_f32_copy = test_var_f32;
	test_var_f64_copy = test_var_f64;
  test_var_struct_copy.elmFs.f32 = test_var_struct.elmFs.f32;
  for(int i = 0; i < ARRAY_SIZE; i++) {
    test_var_struct_copy.elmFs.f32a[i] = test_var_struct.elmFs.f32a[i];
    test_var_struct_copy.elmU8a[i] = test_var_struct.elmU8a[i];
    test_var_struct_copy.elmFsa[i].f32 = test_var_struct.elmFsa[i].f32;
    for(int j = 0; j < ARRAY_SIZE; j++) {
      test_var_struct_copy.elmFsa[j].f32a[i] = test_var_struct.elmFsa[j].f32a[i];
    }
  }
  test_var_enum1b_copy = test_var_enum1b;
  test_var_enum2b_copy = test_var_enum2b;
  test_var_enum4b_copy = test_var_enum4b;
//  for(int i =0; i < ARRAY_SIZE; i++) {
//    test_var_external_copy[i] = test_var_external[i];
//  }
  
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
 * @return uint8_t 
 */
static uint8_t AppHardwareInit(void) {

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
static uint8_t AppBehaviourInit(void) {
	
	FARAABIN_DictGroup_Init_(&mappVariableDictGroup);
	FARAABIN_VAR_TYPE_STRUCT_INIT_WP_(sFlatStruct, mappVariablePath);
	FARAABIN_VAR_TYPE_STRUCT_INIT_WP_(sNestedStruct, mappVariablePath);
	FARAABIN_VAR_TYPE_ENUM_INIT_WP_(eEnum1Byte, mappVariablePath);
	FARAABIN_VAR_TYPE_ENUM_INIT_WP_(eEnum2Byte, mappVariablePath);
	FARAABIN_VAR_TYPE_ENUM_INIT_WP_(eEnum4Byte, mappVariablePath);

  test_var_b8 = true;
  test_var_b8_copy = test_var_b8;
  for(int i = 0; i < sizeof(test_var_ba8); i++) {
		
		test_var_ba8[i] = ((i % 2) == 0);
		
	}
//	test_var_b8p = &test_var_b8;
	
  test_var_u8 = UINT8_MAX;
  test_var_u8_copy = test_var_u8;
  for(int i = 0; i < ARRAY_SIZE; i++) {
		
		if((i % 2) == 0) {
			test_var_ua8[i] = UINT8_MAX;
		} else {
			test_var_ua8[i] = 0;
		}
	}
//	test_var_u8p = &test_var_u8;
	
	test_var_u16 = UINT16_MAX;
  test_var_u16_copy = test_var_u16;
  for(int i = 0; i < ARRAY_SIZE; i++) {
		
		if((i % 2) == 0) {
			test_var_ua16[i] = UINT16_MAX;
		} else {
			test_var_ua16[i] = 0;
		}
	}
//	test_var_u16p = &test_var_u16;
	
	test_var_u32 = UINT32_MAX;
  test_var_u32_copy = test_var_u32;
  for(int i = 0; i < ARRAY_SIZE; i++) {
		
		if((i % 2) == 0) {
			test_var_ua32[i] = UINT32_MAX;
		} else {
			test_var_ua32[i] = 0;
		}
	}
//	test_var_u32p = &test_var_u32;
	
	test_var_u64 = 0xFFFFFFFFFFFFFFFF;
  test_var_u64_copy = test_var_u64;
  for(int i = 0; i < ARRAY_SIZE; i++) {
		
		if((i % 2) == 0) {
			test_var_ua64[i] = 0xFFFFFFFFFFFFFFFF;
		} else {
			test_var_ua64[i] = 0;
		}
	}
//	test_var_u64p = &test_var_u64;
	
  test_var_i8 = INT8_MIN;
  test_var_i8_copy = test_var_i8;
  for(int i = 0; i < ARRAY_SIZE; i++) {
		
		if((i % 2) == 0) {
			test_var_ia8[i] = INT8_MAX;
		} else {
			test_var_ia8[i] = INT8_MIN;
		}
	}
//	test_var_i8p = &test_var_i8;
	
  test_var_i16 = INT16_MIN;
  test_var_i16_copy = test_var_i16;
  for(int i = 0; i < ARRAY_SIZE; i++) {
		
		if((i % 2) == 0) {
			test_var_ia16[i] = INT16_MAX;
		} else {
			test_var_ia16[i] = INT16_MIN;
		}
	}
//	test_var_i16p = &test_var_i16;
	
  test_var_i32 = INT32_MIN;
  test_var_i32_copy = test_var_i32;
  for(int i = 0; i < ARRAY_SIZE; i++) {
		
		if((i % 2) == 0) {
			test_var_ia32[i] = INT32_MAX;
		} else {
			test_var_ia32[i] = INT32_MIN;
		}
	}
//	test_var_i32p = &test_var_i32;
	
  test_var_i64 = 0x8000000000000000;
  test_var_i64_copy = test_var_i64;
  for(int i = 0; i < ARRAY_SIZE; i++) {
		
		if((i % 2) == 0) {
			test_var_ia64[i] = 0x7FFFFFFFFFFFFFFF;
		} else {
			test_var_ia64[i] = 0x8000000000000000;
		}
	}
//	test_var_i64p = &test_var_i64;
	
	test_var_f32 = 1234.4321f;
	test_var_f32_copy = test_var_f32;
	for(int i = 0; i < ARRAY_SIZE; i++) {
		
		if((i % 2) == 0) {
			test_var_fa32[i] = 1234.4321f;
//      test_var_external[i] = 1234.4321f;
		} else {
			test_var_fa32[i] = -1234.4321f;
//      test_var_external[i] = -1234.4321f;
		}
	}
//	test_var_f32p = &test_var_f32;
	
	test_var_f64 = 1234.43211234;
	test_var_f64_copy = test_var_f64;
	for(int i = 0; i < ARRAY_SIZE; i++) {
		
		if((i % 2) == 0) {
			test_var_fa64[i] = 1234.43211234;
		} else {
			test_var_fa64[i] = -1234.43211234;
		}
	}
//	test_var_f64p = &test_var_f64;
//	for(int i = 0; i < ARRAY_SIZE; i++) {
//		test_var_fa64p[i] = &test_var_fa64[i];
//	}
	
	test_var_struct.elmFs.f32 = 1234.4321f;
	test_var_struct.elmU8 = UINT8_MAX;
  for(int i = 0; i < ARRAY_SIZE; i++) {
		
		test_var_struct.elmFsa[i].f32 = 1234.4321f;
		
		if((i % 2) == 0) {
			test_var_struct.elmU8a[i] = UINT8_MAX;
			test_var_struct.elmFs.f32a[i] = 1234.4321f;
			test_var_structa[i].elmU8 = UINT8_MAX;
			test_var_struct.elmFsa[i].f32a[i] = 1234.4321f;
		} else {
			test_var_struct.elmU8a[i] = 0;
			test_var_struct.elmFs.f32a[i] = -1234.4321f;
			test_var_structa[i].elmU8 = 0;
			test_var_struct.elmFsa[i].f32a[i] = -1234.4321f;
		}
	}
//	test_var_structp = &test_var_struct;

  test_var_enum1b = eENUM1B_TEST0;
  test_var_enum2b = eENUM2B_TEST0;
  test_var_enum4b = eENUM4B_TEST0;
//  test_var_enum1bp = &test_var_enum1b;
//  test_var_enum2bp = &test_var_enum2b;
//  test_var_enum4bp = &test_var_enum4b;
  for(int i = 0; i < ARRAY_SIZE; i++) {
    test_var_enum1ba[i] = eENUM1B_TEST0;
    test_var_enum2ba[i] = eENUM2B_TEST0;
    test_var_enum4ba[i] = eENUM4B_TEST0;
  }

  return 0;
}

/**
 * @brief 
 * 
 * @param cmd 
 * @param varPtr 
 * @param data 
 * @param size 
 * @return uint8_t 
 */
//static uint8_t ExternalVariableInterface(bool isWrite, uint32_t varPtr, uint8_t *data, uint16_t size) {
//	
//	uint32_t offset = varPtr - (uint32_t)&test_var_external;
//  if((offset % sizeof(test_var_external[0])) != 0) {
//    return 1;
//  }
//  offset = offset / sizeof(test_var_external[0]);
//  
//  if(offset > (sizeof(test_var_external) / sizeof(test_var_external[0]))) {
//    return 1;
//  }
//  
//  if((size % sizeof(test_var_external[0])) != 0) {
//    return 1;
//  }
//	
//	switch(access) {
//		case eVAR_ACCESS_TYPE_READ: {
//			
//			data = (uint8_t*)&test_var_external[offset];
//			
//			break;
//		}
//		case eVAR_ACCESS_TYPE_WRITE: {
//      
//      memcpy(&test_var_external[offset], data, size);
//			
//			break;
//		}
//		default: {
//			
//			return 1;
//		}
//	}
//	
//	return 0;
//}

/**
 * @brief 
 * 
 */
FARAABIN_DICT_GROUP_FUNC_(mappVariableDictGroup) {
  
  FARAABIN_SET_PATH_(mappVariablePath);
	
	FARAABIN_VAR_BOOL_DICT_(test_var_b8);
	FARAABIN_VAR_BOOL_DICT_(test_var_b8_copy);
	FARAABIN_VAR_BOOL_ARRAY_DICT_(test_var_ba8);
//	FARAABIN_VAR_BOOL_POINTER_(test_var_b8p);
  
  FARAABIN_SET_PATH_(mappVariableEmptyPath);
	
	FARAABIN_VAR_U8_DICT_(test_var_u8);
	FARAABIN_VAR_U8_DICT_(test_var_u8_copy);
	FARAABIN_VAR_U8_ARRAY_DICT_(test_var_ua8);
//	FARAABIN_VAR_U8_POINTER_(test_var_u8p);
  
  FARAABIN_SET_PATH_(mappVariableNullPath);
	
	FARAABIN_VAR_U16_DICT_(test_var_u16);
	FARAABIN_VAR_U16_DICT_(test_var_u16_copy);
	FARAABIN_VAR_U16_ARRAY_DICT_(test_var_ua16);
//	FARAABIN_VAR_U16_POINTER_(test_var_u16p);
	
	FARAABIN_VAR_U32_DICT_WP_(test_var_u32, mappVariablePath);
	FARAABIN_VAR_U32_DICT_WP_(test_var_u32_copy, mappVariablePath);
	FARAABIN_VAR_U32_ARRAY_DICT_WP_(test_var_ua32, mappVariablePath);
//	FARAABIN_VAR_U32_POINTER_(test_var_u32p, mappVariablePath);
	
	FARAABIN_VAR_U64_DICT_WP_(test_var_u64, mappVariablePath);
	FARAABIN_VAR_U64_DICT_WP_(test_var_u64_copy, mappVariablePath);
	FARAABIN_VAR_U64_ARRAY_DICT_WP_(test_var_ua64, mappVariablePath);
//	FARAABIN_VAR_U64_POINTER_(test_var_u64p, mappVariablePath);
	
  FARAABIN_VAR_I8_DICT_WP_(test_var_i8, mappVariablePath);
	FARAABIN_VAR_I8_DICT_WP_(test_var_i8_copy, mappVariablePath);
	FARAABIN_VAR_I8_ARRAY_DICT_WP_(test_var_ia8, mappVariablePath);
//	FARAABIN_VAR_I8_POINTER_(test_var_i8p, mappVariablePath);
	
	FARAABIN_VAR_I16_DICT_WP_(test_var_i16, mappVariablePath);
	FARAABIN_VAR_I16_DICT_WP_(test_var_i16_copy, mappVariablePath);
	FARAABIN_VAR_I16_ARRAY_DICT_WP_(test_var_ia16, mappVariablePath);
//	FARAABIN_VAR_I16_POINTER_(test_var_i16p, mappVariablePath);
	
	FARAABIN_VAR_I32_DICT_WP_(test_var_i32, mappVariablePath);
	FARAABIN_VAR_I32_DICT_WP_(test_var_i32_copy, mappVariablePath);
	FARAABIN_VAR_I32_ARRAY_DICT_WP_(test_var_ia32, mappVariablePath);
//	FARAABIN_VAR_I32_POINTER_(test_var_i32p, mappVariablePath);
	
	FARAABIN_VAR_I64_DICT_WP_(test_var_i64, mappVariablePath);
	FARAABIN_VAR_I64_DICT_WP_(test_var_i64_copy, mappVariablePath);
	FARAABIN_VAR_I64_ARRAY_DICT_WP_(test_var_ia64, mappVariablePath);
//	FARAABIN_VAR_I64_POINTER_(test_var_i64p, mappVariablePath);
	
  FARAABIN_VAR_F32_DICT_WP_(test_var_f32, mappVariablePath);
	FARAABIN_VAR_F32_DICT_WP_(test_var_f32_copy, mappVariablePath);
	FARAABIN_VAR_F32_ARRAY_DICT_WP_(test_var_fa32, mappVariablePath);
//	FARAABIN_VAR_F32_POINTER_(test_var_f32p, mappVariablePath);
	
	FARAABIN_VAR_F64_DICT_WP_(test_var_f64, mappVariablePath);
	FARAABIN_VAR_F64_DICT_WP_(test_var_f64_copy, mappVariablePath);
	FARAABIN_VAR_F64_ARRAY_DICT_WP_(test_var_fa64, mappVariablePath);
//	FARAABIN_VAR_F64_POINTER_(test_var_f64p, mappVariablePath);
	
	FARAABIN_VAR_STRUCT_DICT_WP_(test_var_struct, sNestedStruct, mappVariablePath);
	FARAABIN_VAR_STRUCT_DICT_WP_(test_var_struct_copy, sNestedStruct, mappVariablePath);
	FARAABIN_VAR_STRUCT_ARRAY_DICT_WP_(test_var_structa, sNestedStruct, mappVariablePath);
//	FARAABIN_VAR_STRUCT_POINTER_(test_var_structp, sNestedStruct, mappVariablePath);
  
  FARAABIN_VAR_STRUCT_DICT_WP_(test_var_struct.elmFs, sFlatStruct, mappVariablePath);
  FARAABIN_VAR_STRUCT_ARRAY_DICT_WP_(test_var_struct.elmFsa, sFlatStruct, mappVariablePath);
  FARAABIN_VAR_U8_DICT_WP_(test_var_struct.elmU8, mappVariablePath);
  FARAABIN_VAR_U8_ARRAY_DICT_WP_(test_var_struct.elmU8a, mappVariablePath);
	
	FARAABIN_VAR_ENUM_DICT_WP_(test_var_enum1b, eEnum1Byte, mappVariablePath);
	FARAABIN_VAR_ENUM_DICT_WP_(test_var_enum1b_copy, eEnum1Byte, mappVariablePath);
	FARAABIN_VAR_ENUM_ARRAY_DICT_WP_(test_var_enum1ba, eEnum1Byte, mappVariablePath);
//	FARAABIN_VAR_ENUM_POINTER_(test_var_enum1bp, eEnum1Byte, mappVariablePath);
	
	FARAABIN_VAR_ENUM_DICT_WP_(test_var_enum2b, eEnum2Byte, mappVariablePath);
	FARAABIN_VAR_ENUM_DICT_WP_(test_var_enum2b_copy, eEnum2Byte, mappVariablePath);
	FARAABIN_VAR_ENUM_ARRAY_DICT_WP_(test_var_enum2ba, eEnum2Byte, mappVariablePath);
//	FARAABIN_VAR_ENUM_POINTER_(test_var_enum2bp, eEnum2Byte, mappVariablePath);
	
	FARAABIN_VAR_ENUM_DICT_WP_(test_var_enum4b, eEnum4Byte, mappVariablePath);
	FARAABIN_VAR_ENUM_DICT_WP_(test_var_enum4b_copy, eEnum4Byte, mappVariablePath);
	FARAABIN_VAR_ENUM_ARRAY_DICT_WP_(test_var_enum4ba, eEnum4Byte, mappVariablePath);
//	FARAABIN_VAR_ENUM_POINTER_(test_var_enum4bp, eEnum4Byte, mappVariablePath);
	
//	FARAABIN_VAR_EXTERNAL_(test_var_external, float32_t, ARRAY_SIZE, ExternalVariableInterface, mappVariablePath);

  FARAABIN_DICT_GROUP_FUNC_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
