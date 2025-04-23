//-----------------------------------------------------------------------------
// Copyright:  M3R 
// Author:     
// Remarks:    
// known Problems: 
// Version: 0.01   
// Description:  
//                                 
//-------

#ifndef __PCD8544_H_
#define __PCD8544_H_

#define PCD8544_WIDTH		84
#define PCD8544_HEIGHT	48

#define LCD_X						84
#define LCD_Y						48

#define PutPixel(x, y, clr)		PCD8544_DrawPixel(x, y, clr)

#define GetMaxX() ((unsigned char)LCD_X-1)
#define GetMaxY() ((unsigned char)LCD_Y-1)

	//------------------------


#define PCD8544_POWERDOWN			0x04
#define PCD8544_ENTRYMODE			0x02
#define PCD8544_EXTENDEDINSTRUCTION	0x01
#define PCD8544_DISPLAYBLANK		0x00
#define PCD8544_DISPLAYNORMAL		0x04
#define PCD8544_DISPLAYALLON		0x01
#define PCD8544_DISPLAYINVERTED		0x05
// Normal instruction set
#define PCD8544_FUNCTIONSET			0x20
#define PCD8544_DISPLAYCONTROL		0x08
#define PCD8544_SETYADDR			0x40
#define PCD8544_SETXADDR			0x80
// Extended instruction set
#define PCD8544_SETTEMP				0x04
#define PCD8544_SETBIAS				0x10
#define PCD8544_SETVOP				0x80
// Display presets
#define PCD8544_LCD_BIAS			0x03	// Range: 0-7 (0x00-0x07)
#define PCD8544_LCD_TEMP			0x02	// Range: 0-3 (0x00-0x03)
#define PCD8544_LCD_CONTRAST		0x46	// Range: 0-127 (0x00-0x7F)
	// Colors
	typedef enum {
		WHITE		= 0x00,
		BLACK		= 0xFF

	}  PCD8544_Color;


	// Useful user constants
	typedef enum {
	  NON_INVERTED	= 0,
	  INVERTED		= 1
	} Invert_Mode;

typedef enum {
	PCD8544_COMMAND = 0,
	PCD8544_DATA = !PCD8544_COMMAND
} PCD8544_WriteType_t;

typedef enum {
	PCD8544_State_Low = 0,
	PCD8544_State_High = !PCD8544_State_Low
} PCD8544_State_t;

typedef enum {
	PCD8544_Pin_DC = 1,
	PCD8544_Pin_RST = 2
} PCD8544_Pin_t;


typedef enum {
	PCD8544_Pixel_Clear = 0,
	PCD8544_Pixel_Set = !PCD8544_Pixel_Clear
} PCD8544_Pixel_t;



#define LCD_C     0
#define LCD_D     1
#define LCD_CMD   0



#define PCD8544_BUFFER_SIZE 		PCD8544_WIDTH * PCD8544_HEIGHT / 8

#define LCD_CONTRAST 0XBE //0X00 - 0XFF

void LcdClear(void);
void LcdInitialise(void);
void gotoXY(int x, int y);
void PCD8544_UpdateArea(unsigned char xMin, unsigned char yMin, unsigned char xMax, unsigned char yMax);
void PCD8544_Invert(Invert_Mode invert);
void PCD8544_DrawPixel(unsigned char x, unsigned char y, char clr);
void PCD8544_Home(void);
void PCD8544_Refresh(void);
void PCD8544_DrawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color);
void PCD8544_DrawRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color);
void PCD8544_DrawFilledRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color);
void PCD8544_DrawCircle(char x0, char y0, char r, char color);
void PCD8544_DrawFilledCircle(char x0, char y0, char r, char color);
void PCD8544_DrawBitmap(const unsigned char *bitmap, unsigned char x, unsigned char y);
#endif
