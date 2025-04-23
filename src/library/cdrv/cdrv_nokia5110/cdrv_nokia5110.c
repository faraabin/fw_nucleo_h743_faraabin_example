/**
******************************************************************************
* @file           : cdrv_nokia5110.c
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
#include "cdrv_nokia5110.h"

#include "pcd8544\pe_map.h"

#include <string.h>

/* Private define ------------------------------------------------------------*/
//PCD8544 driver library
#define PCD8544_WIDTH								84
#define PCD8544_HEIGHT							48

#define LCD_C												0
#define LCD_D												1
#define LCD_CMD											0

#define LCD_X												PCD8544_WIDTH
#define LCD_Y												PCD8544_HEIGHT

#define PCD8544_BUFFER_SIZE					((PCD8544_WIDTH * PCD8544_HEIGHT) / 8)

#define PCD8544_POWERDOWN						0x04
#define PCD8544_ENTRYMODE						0x02
#define PCD8544_EXTENDEDINSTRUCTION	0x01
#define PCD8544_DISPLAYBLANK				0x00
#define PCD8544_DISPLAYNORMAL				0x04
#define PCD8544_DISPLAYALLON				0x01
#define PCD8544_DISPLAYINVERTED			0x05
// Normal instruction set
#define PCD8544_FUNCTIONSET					0x20
#define PCD8544_DISPLAYCONTROL			0x08
#define PCD8544_SETYADDR						0x40
#define PCD8544_SETXADDR						0x80
// Extended instruction set
#define PCD8544_SETTEMP							0x04
#define PCD8544_SETBIAS							0x10
#define PCD8544_SETVOP							0x80
// Display presets
#define PCD8544_LCD_BIAS						0x03	// Range: 0-7 (0x00-0x07)
#define PCD8544_LCD_TEMP						0x02	// Range: 0-3 (0x00-0x03)
#define PCD8544_LCD_CONTRAST				0x46	// Range: 0-127 (0x00-0x7F)
#define LCD_CONTRAST								0XBE //0X00 - 0XFF

//Font library
#define FONT_HEADER_SIZE						7
#define STYLE_NONE									0
#define STYLE_NO_ZERO   						1
#define STYLE_NO_SPACE  						2

#define ALINE_LEFT									0
#define ALINE_CENTER								1
#define ALINE_RIGHT									2
#define ALINE_MARK									(ALINE_LEFT | ALINE_CENTER | ALINE_RIGHT)

#define BORDER_NONE									0x00
#define BORDER_RECT									0x04
#define BORDER_FILL									0x08
#define BORDER_BEVEL								0xF0	// bevel radius 0x00(rectangle), 0x10-0xF0(radius size)
#define BORDER_MASK									(BORDER_FILL | BORDER_RECT)

#define GetLetter() 								peLETTER

#define GetCursorX() 								cursorX
#define GetCursorY() 								cursorY
#define SetCursorX(x) 							(cursorX = x)
#define SetCursorY(y) 							(cursorY = y)
#define SetCursor(x,y) 							{cursorX = x; cursorY = y;}

#define LcdRot(n)										(rot = n)
#define LcdReverse(n)								(Reverse = n)
#define LcdHorizontal(n)						(Horizontal = n)

#define LcdFontFixed(n)							(FontFixed = n)
#define LcdNonTransparence(n)				(NonTransparence = n)

#define SetFgColor(c)								(FgColor = c)
#define SetBkColor(c)								(BkColor = c)
#define GetFgColor()								FgColor
#define GetBkColor()								BkColor

#define LcdFontXScale(n)						(FontXScale = n)
#define LcdFontYScale(n)						(FontYScale = n)
#define LcdFontSpaceX(n)						(FontSpaceX = n)
#define LcdFontSpaceY(n)						(FontSpaceY = n)

#define LcdFontWidth() 	 						FontWidth
#define LcdFontHeight()							FontHeight

/* Private macro -------------------------------------------------------------*/
#define ASSERT_NOT_NULL_RET_(obj_)	\
if(obj_ == NULL) {\
	return 1;\
}

#define GpioInitAsOutput_(obj_)	\
do {\
	obj_->Direction = eGPIO_DIR_OUTPUT;\
	obj_->OutType = eGPIO_PUSH_PULL;\
	if(fGpio_Init_(obj_) != 0) {\
		return 1;\
	}\
}while(0)

#define PutPixel(x, y, clr)	fCdrvNokia5110_PCD8544_DrawPixel(x, y, clr)

#define GetMaxX()	((unsigned char)LCD_X-1)
#define GetMaxY()	((unsigned char)LCD_Y-1)
	
#define DrawStringAt(l,c,s,fk,bk)	{fCdrvNokia5110_SetLine(l,c); SetFgColor(fk); SetBkColor(bk); fCdrvNokia5110_Puts(s);}

/* Private typedef -----------------------------------------------------------*/
typedef enum {
	PCD8544_COMMAND = 0,
	PCD8544_DATA = !PCD8544_COMMAND
}PCD8544_WriteType_t;

typedef enum {
	PCD8544_State_Low = 0,
	PCD8544_State_High = !PCD8544_State_Low
}PCD8544_State_t;

typedef enum {
	PCD8544_Pixel_Clear = 0,
	PCD8544_Pixel_Set = !PCD8544_Pixel_Clear
}PCD8544_Pixel_t;

/* Private variables ---------------------------------------------------------*/
//static Invert_Mode Inverted = NON_INVERTED;
unsigned char PCD8544_Buffer[PCD8544_BUFFER_SIZE];
unsigned char PCD8544_UpdateXmin = 0, PCD8544_UpdateXmax = 0, PCD8544_UpdateYmin = 0, PCD8544_UpdateYmax = 0;

const unsigned char *FontPointer;						// Font	Pointer
unsigned char rot 						= 0;					// Rot 0=0°, 1=90°
unsigned char Reverse					= 0;					// Reverse text direction on the display
unsigned char Horizontal			=	1;					// 1: Portrait - 240x320 ,   2: Landscape - 320x240

unsigned  char c1=0;  // Last character buffer

unsigned short FgColor 				= BLACK;			// Text fg color, 5-6-5 RGB
unsigned short BkColor 				= WHITE;			// Text bk color, 5-6-5 RGB
unsigned char FontFixed				= 0;					// Text type 0=Proportional , 1=Fixed
unsigned char NonTransparence = 1;					// Transparent 0=No, 1=Yes

unsigned short fontSize;										// size of current font
unsigned char firstchar;										// first character noumber of current font
unsigned char lastchar;											// last character noumber of current font
unsigned char charwidth;										// current character width register

unsigned char FontWidth;										// max width of font
unsigned char FontHeight;										// max height of font
unsigned char FontXScale 			= 1;					// X size of font
unsigned char FontYScale 			= 1;					// Y size of font

unsigned char FontSpaceX 			= 0;					// space between char
unsigned char FontSpaceY			= 0;					// space between lines

unsigned int cursorX 				= 0;						// x position
unsigned int cursorY 				= 0;						// y position


Lt_Mode peLETTER = E_LETTER;		// English or Persian letter

unsigned char prevLet 				= 0xFF;				// previous persian character register
unsigned char nextLet 				= 0xFF; 			// next persian character register

/* Private function prototypes -----------------------------------------------*/
static uint8_t LcdWrite(sCdrvNokia5110 * const me, unsigned char dc, unsigned data);

static void PutCharEN(unsigned char c);
static void PutCharPE(unsigned char c);
static unsigned int CalcTextWidthEN(char *str);
static unsigned int CalcTextWidthPE(char *str);
//static unsigned int CalcTextWidth(char *Text);
//static unsigned int CalcTextHeight(void);
static char  utf8ascii(char ascii);
static void PutsPE(char *str0);
//static void SetLineX(unsigned char line,unsigned char x);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
              ##### cdrv_nokia5110.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvNokia5110_Init(sCdrvNokia5110 * const me) {
  me->_init = false;
	
	ASSERT_NOT_NULL_RET_(me->CsPin);
	GpioInitAsOutput_(me->CsPin);
	fGpio_Set_(me->CsPin);
	
	ASSERT_NOT_NULL_RET_(me->DataCommandPin);
	GpioInitAsOutput_(me->DataCommandPin);
	fGpio_Set_(me->DataCommandPin);
	
	ASSERT_NOT_NULL_RET_(me->ResetPin);
	GpioInitAsOutput_(me->ResetPin);
	fGpio_Set_(me->ResetPin);
	
	if(me->Spi != NULL) {
		me->Spi->BitOrder = eSPI_FIRSTBIT_MSB;
		me->Spi->DataSize = 8;
		me->Spi->Mode = eSPI_MODE_0;
		me->Spi->Role = eSPI_ROLE_MASTER;
		if(fSpi_Init_(me->Spi) != 0) {
			return 1;
		}
		me->_ctrlMode = eCTRL_MODE_SPI;
	} else {
		if((me->Clock == NULL) || (me->DataIn == NULL)) {
			return 1;
		}
		
		GpioInitAsOutput_(me->Clock);
		fGpio_Reset_(me->Clock);
		GpioInitAsOutput_(me->DataIn);
		fGpio_Set_(me->DataIn);
		
		me->_ctrlMode = eCTRL_MODE_GPIO;
	}
	
	fGpio_Reset_(me->ResetPin);
	fChrono_DelayMs(10);
	fGpio_Set_(me->ResetPin);
	fChrono_DelayMs(10);
	
	LcdWrite(me, LCD_C, 0x21);					// LCD Extended Commands.
	LcdWrite(me, LCD_C, LCD_CONTRAST);	// Set LCD Vop (Contrast).
	LcdWrite(me, LCD_C, 0x04);					// Set Temp coeffiCEEnt. //0x04
	LcdWrite(me, LCD_C, 0x14);					// LCD bias mode 1:48. //0x13
	LcdWrite(me, LCD_C, 0x20);					// LCD Basic Commands
	LcdWrite(me, LCD_C, 0x0C);					// LCD in normal mode.0x0D
	fCdrvNokia5110_LcdClear(me);
	
  me->_init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvNokia5110_LcdClear(sCdrvNokia5110 * const me)
{
	for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
	{
		LcdWrite(me, LCD_D, 0x00);
	}
	for (int index = 0; index < PCD8544_BUFFER_SIZE; index++)
	{
		PCD8544_Buffer[index]=0;
	}
}

/**
 * @brief 
 * 
 * @param me 
 * @param x 
 * @param y 
 */
void fCdrvNokia5110_gotoXY(sCdrvNokia5110 * const me, int x, int y)
{
	LcdWrite(me, 0, 0x80 | x);  // Column.
	LcdWrite(me, 0, 0x40 | y);  // Row.  
}

/**
 * @brief 
 * 
 * @param xMin 
 * @param yMin 
 * @param xMax 
 * @param yMax 
 */
void fCdrvNokia5110_PCD8544_UpdateArea(unsigned char xMin, unsigned char yMin, unsigned char xMax, unsigned char yMax) {
	if (xMin < PCD8544_UpdateXmin) {
		PCD8544_UpdateXmin = xMin;
	}
	if (xMax > PCD8544_UpdateXmax) {
		PCD8544_UpdateXmax = xMax;
	}
	if (yMin < PCD8544_UpdateYmin) {
		PCD8544_UpdateYmin = yMin;
	}
	if (yMax > PCD8544_UpdateYmax) {
		PCD8544_UpdateYmax = yMax;
	}
}

/**
 * @brief 
 * 
 * @param me 
 * @param invert 
 */
void fCdrvNokia5110_PCD8544_Invert(sCdrvNokia5110 * const me, Invert_Mode invert) {
	if (invert != NON_INVERTED) {
		LcdWrite(me, PCD8544_COMMAND, PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYINVERTED);
	} else {
		LcdWrite(me, PCD8544_COMMAND, PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
	}
}

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param clr 
 */
void fCdrvNokia5110_PCD8544_DrawPixel(unsigned char x, unsigned char y, char clr) {
	if (x >= PCD8544_WIDTH) {
		return;
	}
	if (y >= PCD8544_HEIGHT) {
		return;
	}

	if (clr != PCD8544_Pixel_Clear) {
		PCD8544_Buffer[x + (y / 8) * PCD8544_WIDTH] |= 1 << (y % 8);
	} else {
		PCD8544_Buffer[x + (y / 8) * PCD8544_WIDTH] &= ~(1 << (y % 8));
	}
	fCdrvNokia5110_PCD8544_UpdateArea(x, y, x, y);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvNokia5110_PCD8544_Home(sCdrvNokia5110 * const me) {
	LcdWrite(me, PCD8544_COMMAND, PCD8544_SETXADDR | 0);
	LcdWrite(me, PCD8544_COMMAND, PCD8544_SETYADDR | 0);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvNokia5110_PCD8544_Refresh(sCdrvNokia5110 * const me) {
	unsigned char i, j;
	for (i = 0; i < 6; i++) {
		//Not in range yet
		if (PCD8544_UpdateYmin > ((i + 1) * 8)) {
			continue;
		}
		//Over range, stop
		if ((i * 8) > PCD8544_UpdateYmax) {
			break;
		}

		LcdWrite(me, PCD8544_COMMAND, PCD8544_SETYADDR | i);
		LcdWrite(me, PCD8544_COMMAND, PCD8544_SETXADDR | PCD8544_UpdateXmin);

		for (j = PCD8544_UpdateXmin; j <= PCD8544_UpdateXmax; j++) {
			LcdWrite(me, PCD8544_DATA, PCD8544_Buffer[(i * PCD8544_WIDTH) + j]);
		}
	}

	PCD8544_UpdateXmin = PCD8544_WIDTH - 1;
	PCD8544_UpdateXmax = 0;
	PCD8544_UpdateYmin = PCD8544_HEIGHT - 1;
	PCD8544_UpdateYmax = 0;
}

/**
 * @brief 
 * 
 * @param x0 
 * @param y0 
 * @param x1 
 * @param y1 
 * @param color 
 */
void fCdrvNokia5110_PCD8544_DrawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color) {
	short dx, dy;
	short temp;

	if (x0 > x1) {
		temp = x1;
		x1 = x0;
		x0 = temp;
	}
	if (y0 > y1) {
		temp = y1;
		y1 = y0;
		y0 = temp;
	}

	dx = x1 - x0;
	dy = y1 - y0;

	if (dx == 0) {
		do {
			fCdrvNokia5110_PCD8544_DrawPixel(x0, y0, color);
			y0++;
		} while (y1 >= y0);
		return;
	}
	if (dy == 0) {
		do {
			fCdrvNokia5110_PCD8544_DrawPixel(x0, y0, color);
			x0++;
		} while (x1 >= x0);
		return;
	}

	/* Based on Bresenham's line algorithm  */
	if (dx > dy) {
		temp = 2 * dy - dx;
		while (x0 != x1) {
			fCdrvNokia5110_PCD8544_DrawPixel(x0, y0, color);
			x0++;
			if (temp > 0) {
				y0++;
				temp += 2 * dy - 2 * dx;
			} else {
				temp += 2 * dy;
			}
		}
		fCdrvNokia5110_PCD8544_DrawPixel(x0, y0, color);
	} else {
		temp = 2 * dx - dy;
		while (y0 != y1) {
			fCdrvNokia5110_PCD8544_DrawPixel(x0, y0, color);
			y0++;
			if (temp > 0) {
				x0++;
				temp += 2 * dy - 2 * dx;
			} else {
				temp += 2 * dy;
			}
		}
		fCdrvNokia5110_PCD8544_DrawPixel(x0, y0, color);
	}
}

/**
 * @brief 
 * 
 * @param x0 
 * @param y0 
 * @param x1 
 * @param y1 
 * @param color 
 */
void fCdrvNokia5110_PCD8544_DrawRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color) {
	fCdrvNokia5110_PCD8544_DrawLine(x0, y0, x1, y0, color); 	//Top
	fCdrvNokia5110_PCD8544_DrawLine(x0, y0, x0, y1, color);	//Left
	fCdrvNokia5110_PCD8544_DrawLine(x1, y0, x1, y1, color);	//Right
	fCdrvNokia5110_PCD8544_DrawLine(x0, y1, x1, y1, color);	//Bottom
}

/**
 * @brief 
 * 
 * @param x0 
 * @param y0 
 * @param x1 
 * @param y1 
 * @param color 
 */
void fCdrvNokia5110_PCD8544_DrawFilledRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color) {
	for (; y0 < y1; y0++) {
		fCdrvNokia5110_PCD8544_DrawLine(x0, y0, x1, y0, color);
	}
}

/**
 * @brief 
 * 
 * @param x0 
 * @param y0 
 * @param r 
 * @param color 
 */
void fCdrvNokia5110_PCD8544_DrawCircle(char x0, char y0, char r, char color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	fCdrvNokia5110_PCD8544_DrawPixel(x0, y0 + r, color);
	fCdrvNokia5110_PCD8544_DrawPixel(x0, y0 - r, color);
	fCdrvNokia5110_PCD8544_DrawPixel(x0 + r, y0, color);
	fCdrvNokia5110_PCD8544_DrawPixel(x0 - r, y0, color);

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		fCdrvNokia5110_PCD8544_DrawPixel(x0 + x, y0 + y, color);
		fCdrvNokia5110_PCD8544_DrawPixel(x0 - x, y0 + y, color);
		fCdrvNokia5110_PCD8544_DrawPixel(x0 + x, y0 - y, color);
		fCdrvNokia5110_PCD8544_DrawPixel(x0 - x, y0 - y, color);

		fCdrvNokia5110_PCD8544_DrawPixel(x0 + y, y0 + x, color);
		fCdrvNokia5110_PCD8544_DrawPixel(x0 - y, y0 + x, color);
		fCdrvNokia5110_PCD8544_DrawPixel(x0 + y, y0 - x, color);
		fCdrvNokia5110_PCD8544_DrawPixel(x0 - y, y0 - x, color);
	}
}

/**
 * @brief 
 * 
 * @param x0 
 * @param y0 
 * @param r 
 * @param color 
 */
void fCdrvNokia5110_PCD8544_DrawFilledCircle(char x0, char y0, char r, char color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	fCdrvNokia5110_PCD8544_DrawPixel(x0, y0 + r, color);
	fCdrvNokia5110_PCD8544_DrawPixel(x0, y0 - r, color);
	fCdrvNokia5110_PCD8544_DrawPixel(x0 + r, y0, color);
	fCdrvNokia5110_PCD8544_DrawPixel(x0 - r, y0, color);
	fCdrvNokia5110_PCD8544_DrawLine(x0 - r, y0, x0 + r, y0, color);

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		fCdrvNokia5110_PCD8544_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
		fCdrvNokia5110_PCD8544_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, color);

		fCdrvNokia5110_PCD8544_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, color);
		fCdrvNokia5110_PCD8544_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, color);
	}
}

/**
 * @brief 
 * 
 * @param me 
 * @param bitmap 
 * @param x 
 * @param y 
 */
void fCdrvNokia5110_PCD8544_DrawBitmap(sCdrvNokia5110 * const me, const unsigned char *bitmap, unsigned char x, unsigned char y)
{
	unsigned char 			width, height, header;
	unsigned char 			displayData;

	unsigned char 			xx, yy, yyy;
	unsigned char				hh, ww;

	unsigned char				endShift;
	unsigned int				xy;

  header = (bitmap[0]);
  width  = (bitmap[1]);
  height = (bitmap[2]);

	// Drawing position calculation
	ww = width;
	hh = height;

	if((x+ww) > PCD8544_WIDTH)		ww = PCD8544_WIDTH  -x;
	if((y+hh) > PCD8544_HEIGHT) 	hh = PCD8544_HEIGHT -y;

	if(hh%8)			hh = hh/8+1;
	else					hh = hh/8;

	endShift = 0;

	// Draw my BMP!
//	if(mode != INVERS)		PCD8544_DrawFilledRectangle(x, y, width-1, height-1, WHITE);		//no transparent

	for(yy=0; yy<hh; yy++)
	{
		yyy = y + (yy * 8);

		if(yyy > (PCD8544_HEIGHT-8))
		{
		 	endShift = y % 8;
			yyy = PCD8544_HEIGHT -8;
		}

		fCdrvNokia5110_gotoXY(me, x, yyy);
		xy = (unsigned int)(yy)*width +header;

		for(xx=0; xx<ww; xx++)
		{
			displayData = (bitmap[xy++]);

			if(endShift)	LcdWrite(me, LCD_D,(displayData << endShift));
			else					LcdWrite(me, LCD_D,displayData);
	 	}
  }

//	if(mode == INVERS)			PCD8544_Invert(x, y, width-1, height-1);			//invers color
}

void fCdrvNokia5110_LcdFont(const unsigned char *pointer)
{
	FontPointer 			= pointer;

	FontWidth 				= (FontPointer[2]);
	FontHeight				= (FontPointer[3]);

	//fontSize				=	_pgm_read_word(FontPointer[0]);
	fontSize					=	(unsigned short)((FontPointer[1])) << 8;
	fontSize				 += (FontPointer[0]);
	firstchar 				=	(FontPointer[5]);
	lastchar 					=	(FontPointer[6]);
}

void fCdrvNokia5110_SetLetter(Lt_Mode L)
{
	peLETTER = L;
	
	if(L == P_LETTER)
		cursorX = GetMaxX();
	else
		cursorX = 0;
}

void fCdrvNokia5110_SetLine(unsigned char line,unsigned char column)
{
	if(peLETTER == P_LETTER)
		cursorX =GetMaxX() - (unsigned int)FontWidth  * FontXScale * column;
	else
		cursorX =(unsigned int)FontWidth  * FontXScale * column;

	cursorY =(unsigned int)(FontHeight +FontSpaceY)* FontYScale * line;
}

void fCdrvNokia5110_PutChar(unsigned char c)
{
  if(peLETTER == P_LETTER)
		PutCharPE(c);
	else
			PutCharEN(c);
}

void fCdrvNokia5110_Puts(char *Text)
{	
	unsigned int		i = 0;
	
  if(peLETTER == P_LETTER)
  {
		PutsPE(Text);
	}
	else
	{

		while(Text[i]) PutCharEN(Text[i++]);

	}
}

unsigned char fCdrvNokia5110_Bit_Is_Set(unsigned char Byte ,unsigned char Mask)
{
	if(Byte&(0x01<<Mask))
		return 1;
	else 
		return 0;
}

/*
===============================================================================
              ##### cdrv_nokia5110.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @param dc 
 * @param data 
 * @return uint8_t 
 */
static uint8_t LcdWrite(sCdrvNokia5110 * const me, unsigned char dc, unsigned data) {
	if(dc == 0) {
		fGpio_Reset_(me->DataCommandPin);
	}
	if(dc == 1) {
		fGpio_Set_(me->DataCommandPin);
	}
	
	fGpio_Reset_(me->CsPin);
	
	if(me->_ctrlMode == eCTRL_MODE_SPI) {
		uint8_t spiBuffer = data;
		
		if(fSpi_Transmit_(me->Spi, &spiBuffer, 1, 100) != 0) {
			return 1;
		}
	}
	
	if(me->_ctrlMode == eCTRL_MODE_GPIO) {
		uint8_t cnt = 8;
		
//		for(int i = 0; i < 8; i++) {
//			
//			fGpio_Write_(me->DataIn, !!(data & (1 << (7 - i))));
//			fGpio_Set_(me->Clock);
//			fGpio_Reset_(me->Clock);
//		}
		
		while(cnt--) {
			
			if(data & 0x80) {
				fGpio_Set_(me->DataIn);
			} else {
				fGpio_Reset_(me->DataIn);
			}
			
			fGpio_Set_(me->Clock);
			data = data << 1;
			fGpio_Reset_(me->Clock);
		}
    
    fGpio_Set_(me->DataIn);
    fGpio_Reset_(me->Clock);
	}
	
	fGpio_Set_(me->CsPin);
	
	return 0;
}

static void PutCharEN(unsigned char c)
{
	unsigned char 			byte 					= 0;
	unsigned char 			bitoffset 				= 0;
	unsigned char 			maske 					= 0;
	unsigned short 			bcounter 				= 0;
	unsigned short 			bitsbischar 			= 0;
	unsigned short 			bytesbischar			= 0;
	unsigned short 			xPos,yPos;
	
	unsigned char 			Ccounter 				= 0;
	unsigned char 			xc						= 0;
	unsigned char 			yc						= 0;
	unsigned char 			sx 						= 0;
	unsigned char 			sy 						= 0;

   // get current character width
	charwidth	= (FontPointer[(unsigned int)(c)+FONT_HEADER_SIZE-firstchar]);
	
	
	if(c == '\n')
	{
		cursorX = 0;
		cursorY = cursorY + (unsigned int)FontHeight * FontYScale; 
		
		return;
	}

	// character out of range.
  if( (c < firstchar) || (c > lastchar) || (fontSize == 0)) 
  {
	  return;
  };
	// character is not in list.
	if (charwidth == 0)
	{
		return;
	};
	// sara thai font. line remain at last position
	if(FontFixed)
	{
		charwidth = FontWidth;
	}
	else
	{
		//english special fonts!
		if (((c >= 0xd4) && (c <= 0xda)) || 
	  	  ((c >= 0xe7) && (c <= 0xec)) ||
				 (c == 0xd1))
		{
			cursorX = cursorX - (unsigned int)charwidth * FontXScale;
		}
	}

	// fixed width for digit
 	if((c >= '0') && (c <= '9'))		// english : 0 to 9
		charwidth = (FontPointer[(unsigned int)(FONT_HEADER_SIZE)+'0'-firstchar]);		//width reference = ZERO
	
	// line adjust
	if(((int)cursorX + charwidth * FontXScale) > GetMaxX())
	{
		cursorY = cursorY + (unsigned int)FontHeight * FontYScale; 
		cursorX = 0;
	}

	// calculate current character position on the table
	for(Ccounter = 0; Ccounter < c-firstchar; Ccounter++)
		bitsbischar += ((FontPointer[(unsigned int)(Ccounter)+FONT_HEADER_SIZE]));	//c0_width +...+ cn_width
    
    
	bitsbischar 		*= FontHeight;																										//c_widths * FH
	bitsbischar 		+= (((unsigned short)(lastchar)-firstchar)+FONT_HEADER_SIZE)*8;		//plus font headers
	bytesbischar 		 = bitsbischar/8;																//
	bitoffset 			 = bitsbischar % 8;															//
	maske						 = bitoffset % 8;																//

	// draw character
	for(xc = 0; xc < charwidth; xc++)
	{
		for(yc = 0; yc < FontHeight; yc++)
		{
			if(maske > 7)
			{
				maske = 0;
				bcounter += 1;
			}
			byte = (FontPointer[bytesbischar + bcounter + 1]);

			xPos = (unsigned short)xc*FontXScale + cursorX;
			
			if(Horizontal)	//128x64
			{
				if(Reverse)
					yPos = (((unsigned short)FontHeight-yc)*FontYScale + cursorY);
				else
					yPos = (((unsigned short)yc)*FontYScale + cursorY);     
			}
			else						//64x128
			{
				if(Reverse)
					yPos = (((unsigned short)FontHeight-yc)*FontYScale + cursorY);
				else
					yPos = (((unsigned short)yc)*FontYScale + cursorY);
				
			}	//Horizontal

			for(sx = 0; sx < FontXScale; sx++)
			{
				for(sy = 0; sy < FontYScale; sy++)
				{
					if(fCdrvNokia5110_Bit_Is_Set(byte, maske))
					{
						if(rot)		PutPixel(yPos+sy, xPos+sx, FgColor);
						else			PutPixel(xPos+sx, yPos+sy, FgColor);
					}
					else
					{
						if(NonTransparence)
						{
							if(rot)		PutPixel(yPos+sy, xPos+sx, BkColor);
							else			PutPixel(xPos+sx, yPos+sy, BkColor);
						}
					}
				};//for sy
			};//for sx
			
			maske++;
		};//for yc
	};//for xc
	
	// adjust cursor to next position - english
	//cursorX	+= (unsigned int)charwidth * FontXScale + FontSpace;
	cursorX	+= (unsigned int)charwidth * FontXScale + FontSpaceX;
}

static void PutCharPE(unsigned char c)
{
	unsigned char 			byte 					= 0;
	unsigned char 			bitoffset 		= 0;
	unsigned char 			maske 				= 0;
	unsigned short 			bcounter 			= 0;
	unsigned short 			bitsbischar 	= 0;
	unsigned short 			bytesbischar	= 0;
	unsigned short 			xPos,yPos;

	unsigned char 			Ccounter 			= 0;
	unsigned char 			xc 						= 0;
	unsigned char 			yc 						= 0;
	unsigned char 			sx 						= 0;
	unsigned char 			sy 						= 0;
	
	// get current character width
	charwidth	= (FontPointer[(unsigned int)(c)+FONT_HEADER_SIZE-firstchar]);
	

	// line feed, goto next line
	if(c == '\n')
	{
		cursorX = GetMaxX();
		cursorY += (unsigned int)(FontHeight +FontSpaceY)* FontYScale;
		
		return;
	}

	// character out of range.
  if( (c < firstchar) || (c > lastchar) || (fontSize == 0)) 
  {
  	return;
  };
	// character is not in list.
	if (charwidth == 0)
	{
		return;
	};
	// sara thai font. line remain at last position
	if(FontFixed)
	{
		charwidth = FontWidth;
	};
	// line adjust
	if(((int)cursorX - charwidth * FontXScale) < 0)
  {
		cursorY = cursorY   + (unsigned int)FontHeight * FontYScale; 
		cursorX = GetMaxX() - (unsigned int)charwidth * FontXScale;
	}

	// adjust cursor to current position - persian
	cursorX	-= (unsigned int)charwidth * FontXScale + FontSpaceX;

	// calculate current character position on the table
	for(Ccounter = 0; Ccounter < c-firstchar; Ccounter++)
		bitsbischar += ((FontPointer[(unsigned int)(Ccounter)+FONT_HEADER_SIZE]));	//c0_width +...+ cn_width


	bitsbischar 		*= FontHeight;																										//c_widths * FH
	bitsbischar 		+= (((unsigned short)(lastchar)-firstchar)+FONT_HEADER_SIZE)*8;		//plus font headers
	bytesbischar 		 = bitsbischar/8;									//
	bitoffset 			 = bitsbischar % 8;								//
	maske						 = bitoffset % 8;									//

	// draw character
	for(xc = 0; xc < charwidth; xc++)
	{
		for(yc = 0; yc < FontHeight; yc++)
		{
			if(maske > 7)
			{
				maske = 0;
				bcounter+=1;
			}
			byte = (FontPointer[bytesbischar + bcounter + 1]);

			xPos = (unsigned short)xc*FontXScale + cursorX;
			
			if(Horizontal)	//128x64
			{
				if(Reverse)
					yPos = (((unsigned short)FontHeight-yc)*FontYScale + cursorY);
				else
					yPos = (((unsigned short)yc)*FontYScale + cursorY);     
			}
			else						//64x128
			{
				if(Reverse)
					yPos = (((unsigned short)FontHeight-yc)*FontYScale + cursorY);
				else
					yPos = (((unsigned short)yc)*FontYScale + cursorY);
				
			}	//Horizontal

			for(sx = 0; sx < FontXScale; sx++)
			{
				for(sy = 0; sy < FontYScale; sy++)
				{
					if(fCdrvNokia5110_Bit_Is_Set(byte, maske))
					{
						if(rot)		PutPixel(yPos+sy, xPos+sx, FgColor);
						else			PutPixel(xPos+sx, yPos+sy, FgColor);
					}
					else
					{
						if(NonTransparence)
						{
							if(rot)		PutPixel(yPos+sy, xPos+sx, BkColor);
							else			PutPixel(xPos+sx, yPos+sy, BkColor);
						}
					}
				};//for sy
			};//for sx
			
			maske++;
		}//for yc
	}//for xc	
}

static unsigned int CalcTextWidthEN(char *str)
{
	unsigned int 		strSize = 0;
	unsigned char 	c;
	unsigned int 		i = 0;	

	while(str[i])
	{
		c = str[i++];
		
		if(c == '\n')			continue;
		
		if(FontFixed)
			strSize += (unsigned int)(FontWidth) * FontXScale;
		else
		{
		  if((c < firstchar) || (c > lastchar)) 
				charwidth = FontWidth;
			else
			{
				charwidth = (FontPointer[(unsigned int)(c)+FONT_HEADER_SIZE-firstchar]);

				//english spesial fonts!
				if (((c >= 0xd4) && (c <= 0xda)) || 
		    		((c >= 0xe7) && (c <= 0xec)) ||
				  	 (c == 0xd1))

					charwidth = 0;
			}
			
			strSize += (unsigned int)(charwidth) * FontXScale;
		}
		
		strSize += FontSpaceX;
	}//while
	
	return(strSize);
}

static unsigned int CalcTextWidthPE(char *str)
{
	unsigned char 	curnLet, dumyLet;
	unsigned char 	Pstat, stat, Nstat;
	
	unsigned char		backFontSpace =FontSpaceX;
	unsigned int 		strSize = 0;
	unsigned int		i = 0;
	
 	while(str[i])
	{ 		
		curnLet = str[i++];
		if(curnLet == '\n')			continue;
	
		if(FontFixed)
			strSize += (unsigned int)(FontWidth) * FontXScale;
		else
		{
		 	if((curnLet < firstchar) || (curnLet > lastchar)) 
				charwidth = FontWidth;
			else
			{
		 		switch(curnLet)
		 		{	
		 			case 0x81:				//peh
		    		curnLet = 0xEA;
		 				break;
		 			case 0x8D:				//cheh
		    		curnLet = 0xEB;
		 				break;
		 			case 0x8E:				//zheh
		    		curnLet = 0xEE;
		 				break;
		 			case 0x90:				//geh
		    		curnLet = 0xEF;
		 				break;
					case 0x98:				//Ke
		    		curnLet = 0xDF;
		 				break;
		 			case 0xE1:				//laa
		    		nextLet = str[i++];
		    		
		    		if(nextLet == 0xC7)
		    			curnLet = 0xFB;
		    		else
		    		{
		    			i--;
		    			curnLet = 0xE1;
		    		}
		 				break;
		 			case 0x30:				//persian digits 0...9
					case 0x31:
					case 0x32:
					case 0x33:
					case 0x34:
					case 0x35:
					case 0x36:
					case 0x37:
					case 0x38:
					case 0x39:
						curnLet -= 0x20;
		 				break;
		 			case 0x3F:				//persian question mark
		    		curnLet = 0xBF;
		 				break;
		 			case 0x3B:				//persian semicolon
		    		curnLet = 0x1F;
		 				break;
		 			case 0x2C:				//persian comma
		    		curnLet = 0x1D;
		 				break;
		 			case 0x2E:				//persian point
		    		curnLet = 0x1C;
		 				break; 				
				}//switch curnLet
		
				//--------------------------------
		  	nextLet = str[i++];
		  	i--;
		  	
		 		switch(nextLet)
		 		{	
		 			case 0x81:				//peh
		    		nextLet = 0xEA;
		 				break;
		 			case 0x8D:				//cheh
		    		nextLet = 0xEB;
		 				break;
		 			case 0x8E:				//zheh
		    		nextLet = 0xEE;
		 				break;
		 			case 0x90:				//geh
		    		nextLet = 0xEF;
		 				break;
					case 0x98:				//Ke
		    		nextLet = 0xDF;
		 				break;
		 			case 0x30:				//0...9
					case 0x31:
					case 0x32:
					case 0x33:
					case 0x34:
					case 0x35:
					case 0x36:
					case 0x37:
					case 0x38:
					case 0x39:
						nextLet -= 0x20;
		 				break; 			
		 			case 0x3F:				//persian question mark
		    		nextLet = 0xBF;
		 				break;
		 			case 0x3B:				//persian semicolon
		    		nextLet = 0x1F;
		 				break;
		 			case 0x2C:				//persian comma
		    		nextLet = 0x1D;
		 				break;
		 			case 0x2E:				//persian point
		    		nextLet = 0x1C;
		 				break; 				
				}//switch nextLet

				if(curnLet > 0xC0)
				{		
					if(prevLet > 0xC0)
						Pstat = (((PEmap[prevLet-0xC1][5])));
					else
						Pstat = 0;
						
					if(nextLet > 0xC0)
						Nstat = (((PEmap[nextLet-0xC1][4])));
					else
						Nstat = 0;
					
					stat = (Pstat<<1) | Nstat;		
					
					if(stat>1)	FontSpaceX = 0;
					else 				FontSpaceX = backFontSpace;
					////////////////
					dumyLet = ((PEmap[curnLet-0xC1][stat]));
					
					charwidth = (FontPointer[(unsigned int)(dumyLet)+FONT_HEADER_SIZE-firstchar]);
					strSize += (unsigned int)(charwidth) * FontXScale;
					strSize += FontSpaceX;
					////////////////
					FontSpaceX = backFontSpace;
				}
				else
				{
					charwidth = (FontPointer[(unsigned int)(curnLet)+FONT_HEADER_SIZE-firstchar]);
					strSize += (unsigned int)(charwidth) * FontXScale;
					strSize += FontSpaceX;
				}
				
				prevLet = curnLet;
			}
		}
	}//while

 	prevLet = 0xFF;
 	
	return(strSize);
}

unsigned int CalcTextWidth(char *Text)
{
	if(peLETTER == E_LETTER)
		return(CalcTextWidthEN(Text));
	else
		return(CalcTextWidthPE(Text));
}

unsigned int CalcTextHeight(void)
{
	return((unsigned int)(FontHeight) * FontYScale);
}

static char  utf8ascii(char ascii) {

    if ( ascii < (char)128 )   // Standard ASCII-set 0..0x7F handling
    {   
			c1=0;
      return( ascii );
    }

    // get previous input
    char last = c1;   // get last char
    c1=ascii;         // remember actual character

switch (last)     // conversion depending on first UTF8-character
    {
case (char)0xd8:
        if(ascii >= (char)0xa0 && ascii <= (char)0xb6)
        {
        return (ascii + 0x20);  
        }

        if(ascii>=(char)0xb7 && ascii<=(char)0xba)
        {
        	return (ascii + 0x21);
        }
        break;
case (char)0xd9:
        if(ascii>=(char)0x80 && ascii<=(char)0x83)
        {
        	return (ascii + 0x5c); 
        }

        if(ascii==(char)0x84)
        {
        	return (ascii + 0x5d);
        }

        if(ascii>=(char)0x85 && ascii<=(char)0x88)
        {
        	return (ascii + 0x5e);
        }

        if(ascii==(char)0x89 || ascii==(char)0x8a)
        {
        	return (ascii + 0x63); 
        }

        if(ascii==(char)0xbe)
        {
        	return 0x81;
        }
        break;
case (char)0xda:
        if(ascii==(char)0x86)
        {
        	return 0x8d;
        }
        if(ascii==(char)0x98)//zhe
        {
        	return 0x8e;
        }

        if(ascii==(char)0xaf)
        {
        	return 0x90;
        }
        if(ascii==(char)0xa9)//ke
          {
          	return 0xdf;
          }
				break;	
case (char)0xdb:
        if(ascii==(char)0x8c)
        {
        	return 0xed;
        }
        break;
    }

    return  (0);                                     // otherwise: return zero, if character has to be ignored
}

static void PutsPE(char *str0)
{	
	unsigned char 	curnLet;
	unsigned char 	Pstat, stat, Nstat;
	
	unsigned char		backFontSpace = FontSpaceX;
	char 						strTemp[50];
	char 						str[50];
	unsigned char 	i = 0, j = 0,c=0;
	unsigned int		k = 0;

	// ****** UTF8-Decoder: convert UTF8-string to extended ASCII *******
	        for (i=0; i<strlen(str0); i++)
	        {
	                c = utf8ascii(str0[i]);
	                if (c!=0) str[k++]=c;

	        }
	        str[k]=0;
	        i = 0;
	        k=0;

 	while(str[k])
	{ 		
 		curnLet = str[k++];
 		
 		switch(curnLet)
 		{	
 			case 0x81:				//peh
    		curnLet = 0xEA;
 				break;
 			case 0x8D:				//cheh
    		curnLet = 0xEB;
 				break;
 			case 0x8E:				//zheh
    		curnLet = 0xEE;
 				break;
 			case 0x90:				//geh
    		curnLet = 0xEF;
 				break;
			case 0x98:				//Ke
		    curnLet = 0xDF;
		 		break;
 			case 0xE1:				//laa
    		nextLet = str[k++];
    		
    		if(nextLet == 0xC7)
    			curnLet = 0xFB;
    		else
    		{
    			k--;
    			curnLet = 0xE1;
    		}
 				break;
 			case 0x3F:				//persian question mark
    		curnLet = 0xBF;
 				break;
 			case 0x3B:				//persian semicolon
    		curnLet = 0x1F;
 				break;
 			case 0x2C:				//persian comma
    		curnLet = 0x1D;
 				break;
 			case 0x2E:				//persian point
    		curnLet = 0x1C;
 				break; 				
		}//switch curnLet
		
		//--------------------------------
  	nextLet = str[k++];
  	k--;
 	
 		switch(nextLet)
 		{	
 			case 0x81:				//peh
    		nextLet = 0xEA;
 				break;
 			case 0x8D:				//cheh
    		nextLet = 0xEB;
 				break;
 			case 0x8E:				//zheh
    		nextLet = 0xEE;
 				break;
 			case 0x90:				//geh
    		nextLet = 0xEF;
 				break;
			case 0x98:				//Ke
		    nextLet = 0xDF;
		 		break;
 			case 0x3F:				//persian question mark
    		nextLet = 0xBF;
 				break;
 			case 0x3B:				//persian semicolon
    		nextLet = 0x1F;
 				break;
 			case 0x2C:				//persian comma
    		nextLet = 0x1D;
 				break;
 			case 0x2E:				//persian point
    		nextLet = 0x1C;
 				break; 			
		}//switch nextLet

		if(curnLet > 0xC0)
		{		
			if(prevLet > 0xC0)
				Pstat = (((PEmap[prevLet-0xC1][5])));		// 1: prevLet attach to curnLet -- 0: prevLet don't attach to curnLet
			else
				Pstat = 0;
				
			if(nextLet > 0xC0)
				Nstat = (((PEmap[nextLet-0xC1][4])));		// 1: nextLet attach to curnLet -- 0: nextLet don't attach to curnLet
			else
				Nstat = 0;
			
			//			Pstat	|	Nstat	|	stat
			//		 -------+-------+------
			//				0		|		0		|		0				curnLet, don't attach to prevLet and nextLet
			//				0		|		1		|		1				curnLet, don't attach to prevLet and attach to nextLet
			//				1		|		0		|		2				curnLet, attach to prevLet and don't attach to nextLet
			//				1		|		1		|		3				curnLet, attach to prevLet and nextLet
			
			stat = (Pstat<<1) | Nstat;		
			
			if(stat>1)	FontSpaceX = 0;
			else 				FontSpaceX = backFontSpace;
			
			PutCharPE(((PEmap[curnLet-0xC1][stat])));
			FontSpaceX = backFontSpace;
		}
		else	//Original 'curnLet' below 193 without ( � � � � )  -- for digits and symbols!
		{
  		if((curnLet >= '0') && (curnLet <= '9'))		// 0 to 9
  		{
  			i++;
  			strTemp[i] 	 = curnLet;

  			if(!((nextLet >= '0') && (nextLet <= '9')))
				{
					for(j=i; j>0; j--)
						PutCharPE(strTemp[j]-0x20);

					i = 0;
				}
			}		
			else
				PutCharPE(curnLet);
		}
		
		prevLet = curnLet;
	}//while

 	prevLet = 0xFF;
}

void SetLineX(unsigned char line,unsigned char x)
{
		if(peLETTER == P_LETTER)
		{
			cursorX =GetMaxX() - x;
		}
		else{
			cursorX = x;
		}
	cursorY =(unsigned int)(FontHeight +FontSpaceY)* FontYScale * line;
}	

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
