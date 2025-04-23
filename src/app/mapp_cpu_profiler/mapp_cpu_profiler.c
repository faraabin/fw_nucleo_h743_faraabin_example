/**
 ******************************************************************************
 * @file           : mapp_cpu_profiler.c
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
#include "mapp_cpu_profiler.h"

#include "resources\resources.h"

#include "runtime_scaler.h"
#include "cpu_profiler_wrapper.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CPU_PROFILER_PROCESS_DEF_(TestProcess1);
CPU_PROFILER_PROCESS_DEF_(TestProcess2);
CPU_PROFILER_PROCESS_DEF_(TestProcess3);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappCpuProfiler = {
  .Name = "MappCpuProfiler",
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

	fCpuProfiler_ProcessInit_(&TestProcess1, 0);
	TestProcess1.Priority = 2;
	
	fCpuProfiler_ProcessInit_(&TestProcess2, 0);
	TestProcess2.Priority = 1;
	
	fCpuProfiler_ProcessInit_(&TestProcess3, 0);
	TestProcess3.Priority = 0;

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {

  RUN_EVERY_MS_(Rt, 100) {

		fCpuProfiler_ProcessBegin_(&TestProcess1) {
			
			fChrono_DelayMs(10);
			
			fCpuProfiler_ProcessBegin_(&TestProcess2) {
		
				fChrono_DelayMs(10);	
				
				fCpuProfiler_ProcessBegin_(&TestProcess3) {
				
					fChrono_DelayMs(10);	
				
				fCpuProfiler_ProcessEnd_(&TestProcess3);
				}
				
				fChrono_DelayMs(10);	
			
			fCpuProfiler_ProcessEnd_(&TestProcess2);
			}
				
			fChrono_DelayMs(10);
			
		fCpuProfiler_ProcessEnd_(&TestProcess1);
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
