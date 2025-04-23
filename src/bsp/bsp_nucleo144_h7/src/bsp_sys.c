/**
******************************************************************************
* @file           : bsp_sys.c
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

/* Includes ------------------------------------------------------------------*/
#include "bsp_sys.h"

#include "bsp_config.h"

#include "stm32h7xx_phal.h"
#include "stm32h7xx_hal.h"

#include "chrono.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                        ##### bsp_sys.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t fBspSys_Init(void) {
  
	fPhal_Init();
  fTick_Init_(Phal.Tick->Tick);
  fTick_Reset_(Phal.Tick->Tick);
  fChrono_Init(Phal.Tick->Tick->Value);
  
	HAL_Init();

  MX_GPIO_Init();
  if(SystemClock_Config() != 0) {
    return 1;
  }
  
  fPhal_Tick_Init();
	fTick_Init_(Phal.Tick->Tick); 
  fChrono_Init(Phal.Tick->Tick->Value);  
  
	return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t fBspSys_KernelTimer_Init(void) {
  /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
  
  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t fBspSys_ResetCpu(void) {
	HAL_NVIC_SystemReset();
	
	return 0;
}

/*
===============================================================================
                    ##### bsp_sys.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 */
static uint8_t SystemClock_Config(void) {
#ifdef EXTERNAL_CLOCK_ENABLE
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 120;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    return 1;
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    return 1;
  }
  
  return 0;
#else
	return 1;
#endif
}

/**
 * @brief 
 * 
 */
static void MX_GPIO_Init(void) {
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();

}

/**
 * @brief 
 * 
 * @param TickPriority 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority) {
  //this function is defined here to prevent enable systick timer
  return HAL_OK;
}

/**
 * @brief 
 * 
 */
void HAL_SuspendTick(void) {
  /* Disable tick counting */
  fTick_Stop_(Phal.Tick->Tick);
}

/**
 * @brief 
 * 
 */
void HAL_ResumeTick(void) {
  /* Enable tick counting */
  fTick_Resume_(Phal.Tick->Tick);
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
