#include "main.h"
#include "pcd8544.h"

Invert_Mode									Inverted 					= NON_INVERTED;
unsigned char PCD8544_Buffer[PCD8544_BUFFER_SIZE];
unsigned char PCD8544_UpdateXmin = 0, PCD8544_UpdateXmax = 0, PCD8544_UpdateYmin = 0, PCD8544_UpdateYmax = 0;





unsigned char spi_soft(unsigned char dat)
{
	unsigned char cnt = 8;
	while (cnt--) {
		if (dat & 0x80)  HAL_GPIO_WritePin(DI_GPIO_Port,DI_Pin,GPIO_PIN_SET);
		else HAL_GPIO_WritePin(DI_GPIO_Port,DI_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_SET);
		dat <<= 1;
		HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_RESET);
	}
	return dat;
}


void LcdWrite (unsigned char dc, unsigned data)
{
	if (dc==0) HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_RESET);
	if (dc==1) HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(CE_GPIO_Port,CE_Pin,GPIO_PIN_RESET);
	spi_soft(data);
	HAL_GPIO_WritePin(CE_GPIO_Port,CE_Pin,GPIO_PIN_SET);
}

void LcdClear(void)
{
	for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
	{
		LcdWrite(LCD_D, 0x00);
	}
	for (int index = 0; index < PCD8544_BUFFER_SIZE; index++)
	{
        PCD8544_Buffer[index]=0;
	}

}
void LcdInitialise(void)
{
	HAL_GPIO_WritePin(RST_GPIO_Port,RST_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RST_GPIO_Port,RST_Pin,GPIO_PIN_SET);
	LcdWrite(LCD_C, 0x21 );  // LCD Extended Commands.
	LcdWrite(LCD_C, LCD_CONTRAST);  // Set LCD Vop (Contrast).
	LcdWrite(LCD_C, 0x014 );  // Set Temp coeffiCEEnt. //0x04
	LcdWrite(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x13
	LcdWrite(LCD_C, 0x20 );  // LCD Basic Commands
	LcdWrite(LCD_C, 0x0C );  // LCD in normal mode.0x0D
}
void gotoXY(int x, int y)
{
  LcdWrite( 0, 0x80 | x);  // Column.
  LcdWrite( 0, 0x40 | y);  // Row.  

}

void PCD8544_DrawPixel(unsigned char x, unsigned char y, char clr) {
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
	PCD8544_UpdateArea(x, y, x, y);
}

void PCD8544_Invert(Invert_Mode invert) {
	if (invert != NON_INVERTED) {
		LcdWrite(PCD8544_COMMAND, PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYINVERTED);
	} else {
		LcdWrite(PCD8544_COMMAND, PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
	}
}

void PCD8544_Home(void) {
	LcdWrite(PCD8544_COMMAND, PCD8544_SETXADDR | 0);
	LcdWrite(PCD8544_COMMAND, PCD8544_SETYADDR | 0);
}

void PCD8544_Refresh(void) {
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

		LcdWrite(PCD8544_COMMAND, PCD8544_SETYADDR | i);
		LcdWrite(PCD8544_COMMAND, PCD8544_SETXADDR | PCD8544_UpdateXmin);

		for (j = PCD8544_UpdateXmin; j <= PCD8544_UpdateXmax; j++) {
			LcdWrite(PCD8544_DATA, PCD8544_Buffer[(i * PCD8544_WIDTH) + j]);
		}
	}

	PCD8544_UpdateXmin = PCD8544_WIDTH - 1;
	PCD8544_UpdateXmax = 0;
	PCD8544_UpdateYmin = PCD8544_HEIGHT - 1;
	PCD8544_UpdateYmax = 0;
}

void PCD8544_UpdateArea(unsigned char xMin, unsigned char yMin, unsigned char xMax, unsigned char yMax) {
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


void PCD8544_DrawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color) {
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
			PCD8544_DrawPixel(x0, y0, color);
			y0++;
		} while (y1 >= y0);
		return;
	}
	if (dy == 0) {
		do {
			PCD8544_DrawPixel(x0, y0, color);
			x0++;
		} while (x1 >= x0);
		return;
	}

	/* Based on Bresenham's line algorithm  */
	if (dx > dy) {
		temp = 2 * dy - dx;
		while (x0 != x1) {
			PCD8544_DrawPixel(x0, y0, color);
			x0++;
			if (temp > 0) {
				y0++;
				temp += 2 * dy - 2 * dx;
			} else {
				temp += 2 * dy;
			}
		}
		PCD8544_DrawPixel(x0, y0, color);
	} else {
		temp = 2 * dx - dy;
		while (y0 != y1) {
			PCD8544_DrawPixel(x0, y0, color);
			y0++;
			if (temp > 0) {
				x0++;
				temp += 2 * dy - 2 * dx;
			} else {
				temp += 2 * dy;
			}
		}
		PCD8544_DrawPixel(x0, y0, color);
	}
}

void PCD8544_DrawRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color) {
	PCD8544_DrawLine(x0, y0, x1, y0, color); 	//Top
	PCD8544_DrawLine(x0, y0, x0, y1, color);	//Left
	PCD8544_DrawLine(x1, y0, x1, y1, color);	//Right
	PCD8544_DrawLine(x0, y1, x1, y1, color);	//Bottom
}

void PCD8544_DrawFilledRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, char color) {
	for (; y0 < y1; y0++) {
		PCD8544_DrawLine(x0, y0, x1, y0, color);
	}
}
        
void PCD8544_DrawCircle(char x0, char y0, char r, char color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    PCD8544_DrawPixel(x0, y0 + r, color);
    PCD8544_DrawPixel(x0, y0 - r, color);
    PCD8544_DrawPixel(x0 + r, y0, color);
    PCD8544_DrawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        PCD8544_DrawPixel(x0 + x, y0 + y, color);
        PCD8544_DrawPixel(x0 - x, y0 + y, color);
        PCD8544_DrawPixel(x0 + x, y0 - y, color);
        PCD8544_DrawPixel(x0 - x, y0 - y, color);

        PCD8544_DrawPixel(x0 + y, y0 + x, color);
        PCD8544_DrawPixel(x0 - y, y0 + x, color);
        PCD8544_DrawPixel(x0 + y, y0 - x, color);
        PCD8544_DrawPixel(x0 - y, y0 - x, color);
    }
}

void PCD8544_DrawFilledCircle(char x0, char y0, char r, char color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    PCD8544_DrawPixel(x0, y0 + r, color);
    PCD8544_DrawPixel(x0, y0 - r, color);
    PCD8544_DrawPixel(x0 + r, y0, color);
    PCD8544_DrawPixel(x0 - r, y0, color);
    PCD8544_DrawLine(x0 - r, y0, x0 + r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        PCD8544_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
        PCD8544_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, color);

        PCD8544_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, color);
        PCD8544_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, color);
    }
}



void PCD8544_DrawBitmap(const unsigned char *bitmap, unsigned char x, unsigned char y)
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

		gotoXY(x, yyy);
		xy = (unsigned int)(yy)*width +header;

		for(xx=0; xx<ww; xx++)
		{
			displayData = (bitmap[xy++]);

			if(endShift)			LcdWrite(LCD_D,(displayData << endShift));
			else					LcdWrite(LCD_D,displayData);
	 	}
  }

//	if(mode == INVERS)			PCD8544_Invert(x, y, width-1, height-1);			//invers color
} //PCD8544_DrawBitmap
