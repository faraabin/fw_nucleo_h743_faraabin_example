/**
******************************************************************************
* @file           : mapp_variable_user_defined.c
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
#include "mapp_variable_user_defined.h"

#include "faraabin.h"

#include <limits.h>

/* Private define ------------------------------------------------------------*/
#define ARRAY_SIZE  10

#define DEFAULT_FMIN    (-1234.4321f)
#define DEFAULT_FMAX    (1234.4321f)
#define DEFAULT_DMIN    (-1234.43211234)
#define DEFAULT_DMAX    (1234.43211234)

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/**
 * @brief 
 * 
 */
typedef struct {

  float TestFieldFa32[ARRAY_SIZE];
  float TestFieldF32;

}sTestStruct1;

/**
 * @brief 
 * 
 */
typedef struct {
  
  sTestStruct1 TestFieldTSa1[ARRAY_SIZE];
  sTestStruct1 TestFieldTS1;
  uint8_t TestFieldU8;
  uint8_t TestFieldUa8[ARRAY_SIZE];
  
}sTestStruct2;

/**
 * @brief 
 * 
 */
typedef enum {

  eTE1_TEST1 = 10,
  eTE1_TEST2 = 20,
  eTE1_TEST3 = 30,
  eTE1_TEST4 = 40,
  eTE1_TEST5 = 50,
  eTE1_TEST6 = 60,
  eTE1_TEST7 = 70,
  eTE1_TEST8 = 80

}eTestEnum1;

/**
 * @brief 
 * 
 */
typedef enum {

  eTE2_TEST1 = -20,
  eTE2_TEST2 = -10,
  eTE2_TEST3 = -1,
  eTE2_TEST4 = 0,
  eTE2_TEST5 = 1,
  eTE2_TEST6 = 10,
  eTE2_TEST7 = 20,
  eTE2_TEST8 = 30

}eTestEnum2;

/**
 * @brief 
 * 
 */
typedef enum {

 eTE3_TEST1 = -65535,
 eTE3_TEST2 = -10,
 eTE3_TEST3 = -1,
 eTE3_TEST4 = 0,
 eTE3_TEST5 = 1,
 eTE3_TEST6 = 10,
 eTE3_TEST7 = 100,
 eTE3_TEST8 = 65535

}eTestEnum3;

/* Private variables ---------------------------------------------------------*/
static sTestStruct1 TestVarTS1;
static sTestStruct1 TestVarTS1Clone;
static sTestStruct1 TestVarTSa1[ARRAY_SIZE];

static sTestStruct2 TestVarTS2;
static sTestStruct2 TestVarTS2Clone;
static sTestStruct2 TestVarTSa2[ARRAY_SIZE];

static eTestEnum1 TestVarTE1;
static eTestEnum1 TestVarTE1Clone;
static eTestEnum1 TestVarTEa1[ARRAY_SIZE];
static eTestEnum2 TestVarTE2;
static eTestEnum2 TestVarTE2Clone;
static eTestEnum2 TestVarTEa2[ARRAY_SIZE];
static eTestEnum3 TestVarTE3;
static eTestEnum3 TestVarTE3Clone;
static eTestEnum3 TestVarTEa3[ARRAY_SIZE];

FARAABIN_CONTAINER_DEF_(MappVariableUserDefinedContainer);
FARAABIN_VAR_TYPE_DEF_STATIC_(sTestStruct1);
FARAABIN_VAR_TYPE_DEF_STATIC_(sTestStruct2);
FARAABIN_VAR_TYPE_DEF_STATIC_(eTestEnum1);
FARAABIN_VAR_TYPE_DEF_STATIC_(eTestEnum2);
FARAABIN_VAR_TYPE_DEF_STATIC_(eTestEnum3);

/**
 * @brief 
 * 
 */
static FARAABIN_VAR_TYPE_STRUCT_FUNC_(sTestStruct1)
{
  FARAABIN_VAR_TYPE_STRUCT_FUNC_START_(sTestStruct1);
  
  FARAABIN_VAR_TYPE_STRUCT_MEMBER_(float32_t, TestFieldFa32, ARRAY_SIZE);
  FARAABIN_VAR_TYPE_STRUCT_MEMBER_(float32_t, TestFieldF32, 1);
  
  FARAABIN_VAR_TYPE_STRUCT_FUNC_END_(sTestStruct1);
}

/**
 * @brief 
 * 
 */
static FARAABIN_VAR_TYPE_STRUCT_FUNC_(sTestStruct2)
{
  FARAABIN_VAR_TYPE_STRUCT_FUNC_START_(sTestStruct2);
  
  FARAABIN_VAR_TYPE_STRUCT_MEMBER_(sTestStruct1, TestFieldTSa1, ARRAY_SIZE);
  FARAABIN_VAR_TYPE_STRUCT_MEMBER_(sTestStruct1, TestFieldTS1, 1);
  FARAABIN_VAR_TYPE_STRUCT_MEMBER_(uint8_t, TestFieldUa8, ARRAY_SIZE);
  FARAABIN_VAR_TYPE_STRUCT_MEMBER_(uint8_t, TestFieldU8, 1);
  
  FARAABIN_VAR_TYPE_STRUCT_FUNC_END_(sTestStruct2);
}

/**
 * @brief 
 * 
 */
static FARAABIN_VAR_TYPE_ENUM_FUNC_(eTestEnum1) {
  
  FARAABIN_VAR_TYPE_ENUM_FUNC_START_(eTestEnum1);
  
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE1_TEST1);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE1_TEST2);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE1_TEST3);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE1_TEST4);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE1_TEST5);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE1_TEST6);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE1_TEST7);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE1_TEST8);
  
  FARAABIN_VAR_TYPE_ENUM_FUNC_END_(eTestEnum1);
}

/**
 * @brief 
 * 
 */
static FARAABIN_VAR_TYPE_ENUM_FUNC_(eTestEnum2) {
  
  FARAABIN_VAR_TYPE_ENUM_FUNC_START_(eTestEnum2);
  
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE2_TEST1);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE2_TEST2);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE2_TEST3);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE2_TEST4);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE2_TEST5);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE2_TEST6);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE2_TEST7);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE2_TEST8);
  
  FARAABIN_VAR_TYPE_ENUM_FUNC_END_(eTestEnum2);
}

/**
 * @brief 
 * 
 */
static FARAABIN_VAR_TYPE_ENUM_FUNC_(eTestEnum3) {
 
 FARAABIN_VAR_TYPE_ENUM_FUNC_START_(eTestEnum3);
 
 FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE3_TEST1);
 FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE3_TEST2);
 FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE3_TEST3);
 FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE3_TEST4);
 FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE3_TEST5);
 FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE3_TEST6);
 FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE3_TEST7);
 FARAABIN_VAR_TYPE_ENUM_MEMBER_(eTE3_TEST8);
 
 FARAABIN_VAR_TYPE_ENUM_FUNC_END_(eTestEnum3);
}

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappVariableUserDefined = {
  .Name = "MappVariableUserDefined",
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
  
  TestVarTS1.TestFieldF32 = DEFAULT_FMAX;
  TestVarTS2.TestFieldTS1.TestFieldF32 = DEFAULT_FMAX;
  TestVarTS2.TestFieldU8 = CHAR_MAX;
  
  for(uint8_t i = 0; i < ARRAY_SIZE; i = i + 2) {
    
    TestVarTS1.TestFieldFa32[i] = DEFAULT_FMIN;
    TestVarTS1.TestFieldFa32[i + 1] = DEFAULT_FMAX;
    
    TestVarTS2.TestFieldTS1.TestFieldFa32[i] = DEFAULT_FMIN;
    TestVarTS2.TestFieldTS1.TestFieldFa32[i + 1] = DEFAULT_FMAX;
    TestVarTS2.TestFieldUa8[i] = CHAR_MAX;
    TestVarTS2.TestFieldUa8[i + 1] = CHAR_MIN;
    
  }
  
  for(uint8_t i = 0; i < ARRAY_SIZE; i++) {
    
    for(uint8_t j = 0; j < ARRAY_SIZE; j = j + 2) {
    
      TestVarTSa1[i].TestFieldF32 = DEFAULT_FMAX;
      TestVarTSa1[i].TestFieldFa32[j] = DEFAULT_FMIN;
      TestVarTSa1[i].TestFieldFa32[j + 1] = DEFAULT_FMAX;
      
      TestVarTSa2[i].TestFieldTS1.TestFieldF32 = DEFAULT_FMAX;
      TestVarTSa2[i].TestFieldTS1.TestFieldFa32[j] = DEFAULT_FMIN;
      TestVarTSa2[i].TestFieldTS1.TestFieldFa32[j + 1] = DEFAULT_FMAX;
      
      TestVarTSa2[i].TestFieldTSa1[i].TestFieldF32 = DEFAULT_FMAX;
      TestVarTSa2[i].TestFieldTSa1[i].TestFieldFa32[j] = DEFAULT_FMIN;
      TestVarTSa2[i].TestFieldTSa1[i].TestFieldFa32[j + 1] = DEFAULT_FMAX;
      
      TestVarTSa2[i].TestFieldU8 = CHAR_MAX;
      TestVarTSa2[i].TestFieldUa8[j] = CHAR_MAX;
      TestVarTSa2[i].TestFieldUa8[j + 1] = CHAR_MIN;
      
    }
  }

  return 0;
}

/**
 * @brief 
 * 
 * @param param 
 * @return uint8_t 
 */
uint8_t AppStart(void* param) {

  FARAABIN_Container_Init_(&MappVariableUserDefinedContainer);
  FARAABIN_VAR_TYPE_STRUCT_INIT_WP_(sTestStruct1, "TEST");
  FARAABIN_VAR_TYPE_STRUCT_INIT_WP_(sTestStruct2, "TEST");
  FARAABIN_VAR_TYPE_ENUM_INIT_WP_(eTestEnum1, "TEST");
  FARAABIN_VAR_TYPE_ENUM_INIT_WP_(eTestEnum2, "TEST");
  FARAABIN_VAR_TYPE_ENUM_INIT_WP_(eTestEnum3, "TEST");

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {

  TestVarTS1Clone = TestVarTS1;
  TestVarTS2Clone = TestVarTS2;
  TestVarTE1Clone = TestVarTE1;
  TestVarTE2Clone = TestVarTE2;
  TestVarTE3Clone = TestVarTE3;

  for(uint8_t i = 0; i < ARRAY_SIZE; i+=2) {

    TestVarTS1.TestFieldFa32[i + 1] = TestVarTS1.TestFieldFa32[i];
    TestVarTS2.TestFieldUa8[i + 1] = TestVarTS2.TestFieldUa8[i];
    TestVarTS2.TestFieldTS1.TestFieldFa32[i + 1] = TestVarTS2.TestFieldTS1.TestFieldFa32[i];

    TestVarTEa1[i + 1] = TestVarTEa1[i];
    TestVarTEa2[i + 1] = TestVarTEa2[i];
    TestVarTEa3[i + 1] = TestVarTEa3[i];

  }

  for(uint8_t i = 0; i < ARRAY_SIZE; i++) {

    for(uint8_t j = 0; j < ARRAY_SIZE; j+=2) {
      
      TestVarTS2.TestFieldTSa1[i].TestFieldFa32[j + 1] = TestVarTS2.TestFieldTSa1[i].TestFieldFa32[j];
      TestVarTSa1[i].TestFieldFa32[j + 1] = TestVarTSa1[i].TestFieldFa32[j];
      TestVarTSa2[i].TestFieldUa8[j + 1] = TestVarTSa2[i].TestFieldUa8[j];
      TestVarTSa2[i].TestFieldTS1.TestFieldFa32[j + 1] = TestVarTSa2[i].TestFieldTS1.TestFieldFa32[j];

    }
  }

  for(uint8_t i = 0; i < ARRAY_SIZE; i++) {

    for(uint8_t j = 0; j < ARRAY_SIZE; j++) {

      for(uint8_t k = 0; k < ARRAY_SIZE; k+=2) {

        TestVarTSa2[i].TestFieldTSa1[j].TestFieldFa32[k + 1] = TestVarTSa2[i].TestFieldTSa1[j].TestFieldFa32[k];

      }
    }
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
FARAABIN_CONTAINER_FUNC_(MappVariableUserDefinedContainer) {
  
  FARAABIN_SET_PATH_("TEST_STRUCTURE");
  
  FARAABIN_VAR_STRUCT_(TestVarTS1, sTestStruct1);
  FARAABIN_VAR_STRUCT_(TestVarTS1Clone, sTestStruct1);
  FARAABIN_VAR_STRUCT_ARRAY_(TestVarTSa1, sTestStruct1);
  FARAABIN_VAR_STRUCT_(TestVarTS2, sTestStruct2);
  FARAABIN_VAR_STRUCT_(TestVarTS2Clone, sTestStruct2);
  FARAABIN_VAR_STRUCT_ARRAY_(TestVarTSa2, sTestStruct2);
  
  FARAABIN_SET_PATH_("TEST_ENUM");

  FARAABIN_VAR_ENUM_(TestVarTE1, eTestEnum1);
  FARAABIN_VAR_ENUM_(TestVarTE1Clone, eTestEnum1);
  FARAABIN_VAR_ENUM_ARRAY_(TestVarTEa1, eTestEnum1);
  FARAABIN_VAR_ENUM_(TestVarTE2, eTestEnum2);
  FARAABIN_VAR_ENUM_(TestVarTE2Clone, eTestEnum2);
  FARAABIN_VAR_ENUM_ARRAY_(TestVarTEa2, eTestEnum2);
  FARAABIN_VAR_ENUM_(TestVarTE3, eTestEnum3);
  FARAABIN_VAR_ENUM_(TestVarTE3Clone, eTestEnum3);
  FARAABIN_VAR_ENUM_ARRAY_(TestVarTEa3, eTestEnum3);
  
  FARAABIN_CONTAINER_FUNC_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
