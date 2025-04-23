/**
 ******************************************************************************
 * @file           : mapp_code_block.c
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
#include "mapp_code_block.h"

#include "resources\resources.h"

#include "faraabin.h"
#include "runtime_scaler.h"
#include "cpu_profiler_wrapper.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CPU_PROFILER_CODEBLOCK_DEF_(TestCodeBlock);
CPU_PROFILER_SECTION_DEF_(TestSection1);
CPU_PROFILER_SECTION_DEF_(TestSection2);
CPU_PROFILER_SECTION_DEF_(TestSection3);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappCodeBlock = {
  .Name = "MappCodeBlock",
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

	fCpuProfiler_CodeBlockInit_WithPath_(&TestCodeBlock, 3, "TEST");
  
	fCpuProfiler_CodeBlockAddSection_(&TestCodeBlock, &TestSection1);
	fCpuProfiler_CodeBlockAddSection_(&TestCodeBlock, &TestSection2);
	fCpuProfiler_CodeBlockAddSection_(&TestCodeBlock, &TestSection3);

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {

  RUN_EVERY_US_(CodeBlockRt, 150) {

    fCpuProfiler_CodeBlockBegin_(&TestCodeBlock) {
      
			fCpuProfiler_SectionBegin_(&TestSection3);
			
      fChrono_DelayUs(10); // This resembles the user code that takes time to execute.
			
			fCpuProfiler_SectionEnd_(&TestSection3);

      fCpuProfiler_SectionBegin_(&TestSection2);

      fChrono_DelayUs(20); // This resembles the user code that takes time to execute.

      fCpuProfiler_SectionEnd_(&TestSection2);
			
			fCpuProfiler_SectionBegin_(&TestSection1);

      fChrono_DelayUs(30); // This resembles the user code that takes time to execute.

      fCpuProfiler_SectionEnd_(&TestSection1);

      fChrono_DelayUs(40); // This resembles the user code that takes time to execute.

      fCpuProfiler_CodeBlockEnd_(&TestCodeBlock);
    }

    RUN_END_;
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

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
