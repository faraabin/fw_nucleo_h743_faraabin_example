/**
******************************************************************************
* @file           : cdrv_hd44780.h
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
#ifndef __cdrv_hd44780_H
#define __cdrv_hd44780_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

#include "hal\phal\intf\me_hal_gpio_intf.h"

/* Exported defines ----------------------------------------------------------*/
#define BIT7 0x80
#define BIT6 0x40
#define BIT5 0x20
#define BIT4 0x10
#define BIT3 0x08
#define BIT2 0x04
#define BIT1 0x02
#define BIT0 0x01

#define HD44780_BUSY_FLAG       HD44780_DATA7
#define HD44780_INIT_SEQ        0x30
#define HD44780_DISP_CLEAR      0x01
#define HD44780_DISP_OFF        0x08
#define HD44780_DISP_ON         0x0C
#define HD44780_CURSOR_ON       0x0E
#define HD44780_CURSOR_OFF      0x0C
#define HD44780_CURSOR_BLINK    0x0F
#define HD44780_RETURN_HOME     0x02 
#define HD44780_ENTRY_MODE      0x06
#define HD44780_4BIT_MODE       0x20
#define HD44780_8BIT_MODE       0x30
#define HD44780_2_ROWS          0x08
#define HD44780_FONT_5x8        0x00
#define HD44780_FONT_5x10       0x04
#define HD44780_POSITION        0x80

#define HD44780_SHIFT           0x10
#define HD44780_CURSOR          0x00
#define HD44780_DISPLAY         0x08
#define HD44780_LEFT            0x00
#define HD44780_RIGHT           0x04

#define HD44780_ROWS            2
#define HD44780_COLS            16

#define HD44780_ROW1_START      0x00
#define HD44780_ROW1_END        HD44780_COLS
#define HD44780_ROW2_START      0x40
#define HD44780_ROW2_END        HD44780_COLS

// **********************************************
//                      !!!
//      MODE DEFINITION - CORRECTLY DEFINED
//
// ----------------------------------------------
//
//  HD44780_4BIT_MODE - 4 bit mode / 4 data wires 
//  HD44780_8BIT_MODE - 8 bit mode / 8 data wires    
//
// **********************************************
#define HD44780_MODE            HD44780_4BIT_MODE

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {
  bool init;
	
	TysGpio_Obj *EnPin;
  TysGpio_Obj *RsPin;
  TysGpio_Obj *RwPin;
  TysGpio_Obj *Db7Pin;
  TysGpio_Obj *Db6Pin;
  TysGpio_Obj *Db5Pin;
  TysGpio_Obj *Db4Pin;
	TysGpio_Obj *Db3Pin;
  TysGpio_Obj *Db2Pin;
  TysGpio_Obj *Db1Pin;
  TysGpio_Obj *Db0Pin;
}sCdrvHd44780Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvHD44780_Init(sCdrvHd44780Obj * const me);

void fCdrvHD44780_DisplayClear(sCdrvHd44780Obj * const me);
void fCdrvHD44780_DisplayOn(sCdrvHd44780Obj * const me);
void fCdrvHD44780_CursorOn(sCdrvHd44780Obj * const me);
void fCdrvHD44780_CursorOff(sCdrvHd44780Obj * const me);
void fCdrvHD44780_CursorBlink(sCdrvHd44780Obj * const me);
void fCdrvHD44780_DrawChar(sCdrvHd44780Obj * const me, char character);
void fCdrvHD44780_DrawString(sCdrvHd44780Obj * const me, char *str);
char fCdrvHD44780_PositionXY(sCdrvHd44780Obj * const me, char x, char y);
char fCdrvHD44780_Shift(sCdrvHd44780Obj * const me, char item, char direction);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_HD44780_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
