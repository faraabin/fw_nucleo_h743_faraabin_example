/**
******************************************************************************
* @file           : faraabin_port.c
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2022 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2022 FaraabinCo.
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
#include "faraabin_port.h"

#if defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )
#include <arm_compat.h>
#endif

#if defined ( __ICCARM__ )
#include "intrinsics.h"
#endif

#include "bsp_sys.h"
#include "bsp.h"

#include "chrono.h"

/* Private define ------------------------------------------------------------*/
/**
 * @brief Definition of the inline function for the corresponding compiler.
 * 
 * @note Depending on your target and compiler, define the 'INLINE_' macro to ensure that 
 *       the compiler treats 'fFaraabin_CriticalSectionExit()' as an inline function.
 */
#ifndef INLINE__

#if defined ( __CC_ARM )
#define INLINE__  __forceinline
#endif

#elif defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )
#define INLINE__  __attribute__((always_inline))

#elif defined ( __GNUC__ )

#define INLINE__  __forceinline

#elif defined ( __ICCARM__ )

#define INLINE__  __forceinline

#elif defined ( __TI_ARM__ )

#define INLINE__

#elif defined ( __CSMC__ )

#define INLINE__

#elif defined ( __TASKING__ )

#define INLINE__

#else
  #error Unknown compiler
#endif  //INLINE__

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static char fwName[] = "FW_NUCLEO144_H7";
static uint8_t fbTxBuffer[3000];
static uint8_t fbRxBuffer[1000];

/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                ##### faraabin_port.c Exported Functions #####
===============================================================================*/
/**
 * @brief Returns Firmware name of your project to faraabin as string.
 * 
 * @return fwName Firmware name.
 */
char* fFaraabin_GetFirmwareName(void) {
  return fwName;
}

/**
 * @brief Returns additional info from your project to faraabin as a string.
 * 
 * @return fwInfo Firmware info. 
 */
char* fFaraabin_GetFirmwareInfo(void) {
	
	//return "{\"Clock\":\"100MHz\",\"key2\":\"value2\"}";
	return "info";
}

/**
 * @brief Returns address of the faraabin TX Buffer.
 * 
 * @note This buffer has to be of type uint8_t with proper size.
 * 
 * @return pTxBuffer Pointer to Faraabin buffer created by user.
 */
uint8_t* fFaraabin_GetTxBufferPointer(void) {
  return fbTxBuffer;
}

/**
 * @brief Returns size of the faraabin TX Buffer.
 * 
 * @return size Size of Faraabin buffer created by user.
 */
uint32_t fFaraabin_GetTxBufferSize(void) {
  return sizeof(fbTxBuffer);
}

/**
 * @brief Returns address of the faraabin RX Buffer.
 * 
 * @note This buffer has to be of type uint8_t with proper size.
 * 
 * @return pRxBuffer Pointer to Faraabin buffer created by user.
 */
uint8_t* fFaraabin_GetRxBufferPointer(void) {
  return fbRxBuffer;
}

/**
 * @brief Returns size of the faraabin RX Buffer.
 * 
 * @return size Size of Faraabin buffer created by user.
 */
uint32_t fFaraabin_GetRxBufferSize(void) {
  return sizeof(fbRxBuffer);
}

/**
 * @brief This functions sends faraabin data via user's link to PC.
 * 
 * @return sendStatus '0' if sending data is failed, '1' otherwise.
 */
uint8_t fFaraabin_Send(uint8_t *data, uint16_t size) {
  return fBsp_SerialSend(data, size);
}

/**
 * @brief This function returns the sending status of the faraabin link.
 * 
 * @return isSending 'true' if the link is busy sending data, 'false' if the link is free to send new data.
 */
bool fFaraabin_IsSending(void) {
  return fBsp_SerialIsSending();
}

/**
 * @brief This function is designed to initiate a software reset via the Faraabin UI.
 * 
 * @note If your microcontroller supports a software reset, implement the function body
 *       to trigger the reset. In Faraabin, you can right-click on your MCU fobject and 
 *       select "Reset MCU" to invoke this function whenever necessary.
 * 
 */
void fFaraabin_ResetMcu(void) {
  fBspSys_ResetCpu();
}

/**
 * @brief This function is used when Faraabin needs to enter a critical section.
 * 
 * @note To overcome mixing of the faraabin data that is being generated in different processes(IRQ or Task), faraabin often needs 
 *       to disable all interrupts and reenable them after generating the frame.
 * 
 */
INLINE__ void fFaraabin_CriticalSectionEnter(void) {

#if defined ( __CC_ARM )

  __disable_irq();

#elif defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )

  __disable_irq();

#elif defined ( __GNUC__ )

  __disable_irq();

#elif defined ( __ICCARM__ )

  __disable_interrupt();

#elif defined ( __TI_ARM__ )

  // Implement the critical section enter code for TI ARM compiler;

#elif defined ( __CSMC__ )

  // Implement the critical section enter code for CSMC compiler;

#elif defined ( __TASKING__ )

  // Implement the critical section enter code for TASKING compiler;

#else
  #error Unknown compiler
#endif
  
}
  
/**
 * @brief This function is used when Faraabin needs to exit from a critical section.
 * 
 * @note To overcome mixing of the faraabin data that is being generated in different processes(IRQ or Task), faraabin often needs 
 *       to disable all interrupts and reenable them after generating the frame.
 * 
 */
INLINE__ void fFaraabin_CriticalSectionExit(void) {

#if defined ( __CC_ARM )

  __enable_irq();

#elif defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )

  __enable_irq();

#elif defined ( __GNUC__ )

  __enable_irq();

#elif defined ( __ICCARM__ )

  __enable_interrupt();

#elif defined ( __TI_ARM__ )

  // Implement the critical section enter code for TI ARM compiler;

#elif defined ( __CSMC__ )

  // Implement the critical section enter code for CSMC compiler;

#elif defined ( __TASKING__ )

  // Implement the critical section enter code for TASKING compiler;

#else
  #error Unknown compiler
#endif

}

/*
===============================================================================
                  ##### faraabin_port.c Private Functions #####
===============================================================================*/

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
