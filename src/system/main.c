/**
******************************************************************************
* @file           : main.c
* @brief          : Program entry point and main run-time
* @note           :
* @copyright      : COPYRIGHT� 2023 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright� 2023 FaraabinCo.
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
#include "app\app_integrator\app_integrator.h"
#include "app\resources\resources.h"
#include "bsp.h"

#include "faraabin.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                    ##### main.c Exported Functions #####
===============================================================================*/
/**
 * @brief main function
 * 
 * @return int 
 */
int main (void) {
  
  fBsp_Init();
  fResource_Init();
  fAppIntegrator_Init();
  
  fFaraabin_PasswordSet("123");
//  fFaraabin_PasswordEnable();
  
  while(true) {
    
    fBsp_Run();
    fAppIntegrator_Run();
    
  }
}

/**
 * @brief main function
 * 
 * @parameter file
 * @parameter line
 */
void assert_failed(uint8_t *file, uint32_t line) {
  FARAABIN_PrintfError_("MHAL ASSERTION FAILED in file %s, line %d", file, line);
}

/*
===============================================================================
                  ##### main.c Private Functions #####
===============================================================================*/


/************************ � COPYRIGHT FaraabinCo *****END OF FILE****/
