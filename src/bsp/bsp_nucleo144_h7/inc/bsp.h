/**
******************************************************************************
* @file           : bsp.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __bsp_H
#define __bsp_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stdbool.h"

#include "bsp_config.h"

#include "i_driver\i_gpio.h"
#include "i_driver\i_serial.h"
#include "i_driver\i_timer.h"
#include "io\led.h"
#include "io\pb.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {
	
	struct _dio {
    
		sLed LedGreen;
    sLed LedBlue;
    sLed LedRed;
    
    sPb PbUser;
    
	}Dio;
	
	struct _com {
    
		sSerial *Usb2serial;
    
		sSerial *UsbOtg;
    
	}Com;

  struct _sysRt {
    
    sTimer *Tim6;
    sTimer *Tim7;
    
  }SysRt;
	
}sBspNucleo144;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fBsp_Init(void);
void fBsp_Run(void);

uint8_t fBsp_SerialSend(uint8_t *data, uint16_t size);
bool fBsp_SerialIsSending(void);

/* Exported variables --------------------------------------------------------*/
extern sBspNucleo144 Bsp;

#ifdef __cplusplus
}
#endif

#endif /* __BSP_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
