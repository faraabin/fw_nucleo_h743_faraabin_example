/**
******************************************************************************
* @file           : cdrv_nokia5110.h
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
#ifndef __cdrv_nokia5110_H
#define __cdrv_nokia5110_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\i_driver\i_gpio.h"
#include "library\i_driver\i_spi.h"

#include <stdint.h>
#include <stdbool.h>

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
  E_LETTER,
  P_LETTER
}Lt_Mode;

typedef enum {
  WHITE    = 0x00,
  BLACK    = 0xFF
}PCD8544_Color;

typedef enum {
  NON_INVERTED = 0,
  INVERTED = 1
}Invert_Mode;

typedef enum {
  eANTENNA0 = 0xa3,
  eANTENNA1 = 0x99,
  eANTENNA2 = 0xa4,
  eANTENNA3 = 0xa8,
  eANTENNA4 = 0xaa,
  eBAT0 = 0xac,
  eBAT1 = 0xad,
  eBAT2 = 0xaf,
  eBAT3 = 0xb2,
  eLIKE = 0x88,
  eUNLIKE = 0x89,
  eALARM = 0x8b,
  eSPEAKER = 0x8f,
  eMUSIC = 0x91,
  ePLUGIN = 0x92,
  eTEMP = 0x93,
  eHUM = 0x94,
  eLOCK = 0xa6,
  eUNLOCK = 0xa7,
}eNOKIA5110_SPECIAL_CAHR;

typedef enum {
  
  eCTRL_MODE_SPI = 0,
  eCTRL_MODE_GPIO,
  
}eCdrvNokia5110ControlMode;

typedef struct {
  bool _init;
  eCdrvNokia5110ControlMode _ctrlMode;

  sGpio *CsPin;
  sSpi *Spi;
  sGpio *ResetPin;
  sGpio *DataCommandPin;
  sGpio *Clock;
  sGpio *DataIn;

}sCdrvNokia5110;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvNokia5110_Init(sCdrvNokia5110 * const me);

void fCdrvNokia5110_LcdClear(sCdrvNokia5110 * const me);
void fCdrvNokia5110_gotoXY(sCdrvNokia5110 * const me, int x, int y);
void fCdrvNokia5110_PCD8544_UpdateArea(unsigned char xMin, unsigned char yMin, unsigned char xMax, unsigned char yMax);
void fCdrvNokia5110_PCD8544_Invert(sCdrvNokia5110 * const me, Invert_Mode invert);
void fCdrvNokia5110_PCD8544_DrawPixel(unsigned char x, unsigned char y, char clr);
void fCdrvNokia5110_PCD8544_Home(sCdrvNokia5110 * const me);
void fCdrvNokia5110_PCD8544_Refresh(sCdrvNokia5110 * const me);
void fCdrvNokia5110_PCD8544_DrawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color);
void fCdrvNokia5110_PCD8544_DrawRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color);
void fCdrvNokia5110_PCD8544_DrawFilledRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color);
void fCdrvNokia5110_PCD8544_DrawCircle(char x0, char y0, char r, char color);
void fCdrvNokia5110_PCD8544_DrawFilledCircle(char x0, char y0, char r, char color);
void fCdrvNokia5110_PCD8544_DrawBitmap(sCdrvNokia5110 * const me, const unsigned char *bitmap, unsigned char x, unsigned char y);

void fCdrvNokia5110_LcdFont(const unsigned char *pointer);
void fCdrvNokia5110_SetLetter(Lt_Mode L);
void fCdrvNokia5110_SetLine(unsigned char line,unsigned char column);
void fCdrvNokia5110_PutChar(unsigned char c);
void fCdrvNokia5110_Puts(char *Text);
unsigned char fCdrvNokia5110_Bit_Is_Set(unsigned char ,unsigned char);

unsigned int CalcTextWidth(char *Text);
unsigned int CalcTextHeight(void);
void SetLineX(unsigned char line,unsigned char x);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_NOKIA5110_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
