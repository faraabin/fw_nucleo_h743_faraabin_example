/**
 ******************************************************************************
 * @file           : mapp_unity_tests.c
 * @brief          :
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 FaraabinCo.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component
 * 
 * https://faraabinco.ir/
 * https://github.com/FaraabinCo
 *
 ******************************************************************************
 * @verbatim
 * @endverbatim
 */

/* Includes ------------------------------------------------------------------*/
#include "mapp_unity_tests.h"

#include "unity_fixture.h"

#include <stdbool.h>

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void RunTests(void);

/* Variables -----------------------------------------------------------------*/

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Exported Functions #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief Function that runs all unit tests and returns the result.
 * 
 * @return int 
 */
int fMappUnity_Tests_Run(int argc, const char* argv[]) {
  
  return UnityMain(argc, argv, RunTests);
}

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Private Functions #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/

/**
 * @brief Test group object.
 * 
 */
TEST_GROUP(MAPP_UNITY_TEST_GROUP);

/**
 * @brief Unit test setup.
 * 
 */
TEST_SETUP(MAPP_UNITY_TEST_GROUP) {
  
}

/**
 * @brief Unit test teardown.
 * 
 */
TEST_TEAR_DOWN(MAPP_UNITY_TEST_GROUP) {

}

/**
 * @brief 
 * 
 */
TEST(MAPP_UNITY_TEST_GROUP, ReturnsTest1OkMessage) {
  
  TEST_ASSERT_MESSAGE(true, "Test example with successful assertion.");
}

/**
 * @brief 
 * 
 */
TEST(MAPP_UNITY_TEST_GROUP, ReturnsTest2OkMessage) {
  
  TEST_ASSERT_MESSAGE(true, "Test example with successful assertion.");
}

/**
 * @brief 
 * 
 */
TEST(MAPP_UNITY_TEST_GROUP, ReturnsTest3OkMessage) {
  
  TEST_ASSERT_MESSAGE(true, "Test example with successful assertion.");
}

/**
 * @brief 
 * 
 */
TEST(MAPP_UNITY_TEST_GROUP, ReturnsTest1FailMessage) {
  
  TEST_ASSERT_MESSAGE(false, "Test example with failure assertion.");
}

/**
 * @brief 
 * 
 */
TEST(MAPP_UNITY_TEST_GROUP, ReturnsTest2FailMessage) {
  
  TEST_ASSERT_MESSAGE(false, "Test example with failure assertion.");
}

/**
 * @brief 
 * 
 */
TEST(MAPP_UNITY_TEST_GROUP, ReturnsTest3FailMessage) {
  
  TEST_ASSERT_MESSAGE(false, "Test example with failure assertion.");
}

/**
 * @brief Run all tests in test group.
 * 
 */
static void RunTests(void) {

  RUN_TEST_GROUP(MAPP_UNITY_TEST_GROUP);

}

/**
 * @brief 
 * 
 */
TEST_GROUP_RUNNER(MAPP_UNITY_TEST_GROUP) {

  RUN_TEST_CASE(MAPP_UNITY_TEST_GROUP, ReturnsTest1OkMessage);
  RUN_TEST_CASE(MAPP_UNITY_TEST_GROUP, ReturnsTest2OkMessage);
  RUN_TEST_CASE(MAPP_UNITY_TEST_GROUP, ReturnsTest3OkMessage);
  RUN_TEST_CASE(MAPP_UNITY_TEST_GROUP, ReturnsTest1FailMessage);
  RUN_TEST_CASE(MAPP_UNITY_TEST_GROUP, ReturnsTest2FailMessage);
  RUN_TEST_CASE(MAPP_UNITY_TEST_GROUP, ReturnsTest3FailMessage);

}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
