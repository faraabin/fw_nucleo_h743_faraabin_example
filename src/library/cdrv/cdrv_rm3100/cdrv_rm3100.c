/**
******************************************************************************
* @file           : cdrv_rm3100.c
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
#include "cdrv_rm3100.h"

#include <math.h>

/* Private define ------------------------------------------------------------*/
//internal register values without the R/W bit
#define RM3100_REVID_REG 0x36 // Hexadecimal address for the Revid internal register
#define RM3100_POLL_REG 0x00 // Hexadecimal address for the Poll internal register
#define RM3100_CMM_REG 0x01 // Hexadecimal address for the Continuous Measurement Mode internal register
#define RM3100_STATUS_REG 0x34 // Hexadecimal address for the Status internal register
#define RM3100_CCX1_REG 0x04 // Hexadecimal address for the Cycle Count X1 internal register
#define RM3100_CCX0_REG 0x05 // Hexadecimal address for the Cycle Count X0 internal register

//options
#define initialCC 200 // Set the cycle count
#define singleMode 0 //0 = use continuous measurement mode; 1 = use single measurement mode
#define useDRDYPin 1 //0 = not using DRDYPin ; 1 = using DRDYPin to wait for data

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
// Sensor Commands
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t readReg(sCdrvRm3100_Obj * const me, uint8_t addr);
static void writeReg(sCdrvRm3100_Obj * const me, uint8_t addr, uint8_t data);
static void changeCycleCount(sCdrvRm3100_Obj * const me, uint16_t newCC);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                  ##### cdrv_sdp3x.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @param i2cAddr 
 * @return uint8_t 
 */
uint8_t fCdrvRm3100_Init(sCdrvRm3100_Obj * const me) {
	
	me->revid = readReg(me, RM3100_REVID_REG);
  
  changeCycleCount(me, initialCC); //change the cycle count; default = 200 (lower cycle count = higher data rates but lower resolution)

  me->cycleCount = readReg(me, RM3100_CCX1_REG);
  me->cycleCount = (me->cycleCount << 8) | readReg(me, RM3100_CCX0_REG);

  me->gain = (0.3671f * (float)me->cycleCount) + 1.5f; //linear equation to calculate the gain from cycle count

  if (singleMode) {
    //set up single measurement mode
    writeReg(me, RM3100_CMM_REG, 0);
    writeReg(me, RM3100_POLL_REG, 0x70);
  }
  else{
    // Enable transmission to take continuous measurement with Alarm functions off
    writeReg(me, RM3100_CMM_REG, 0x79);
  }
	
	return 0;
}

uint8_t fCdrvRm3100_Update(sCdrvRm3100_Obj * const me) {
	
	uint8_t dataTx;
	
	uint8_t x2,x1,x0,y2,y1,y0,z2,z1,z0;

  //read measurements
  meGpio_Reset_(me->u_cs);
	meDelay_ms_(100);
	
	dataTx = 0xA4;
	meSpi_Transmit_(me->u_spi, &dataTx, 1, 1000);
  
	dataTx = 0xA5;
	meSpi_TransmitReceive_(me->u_spi, &dataTx, &x2, 1, 1000);
	
	dataTx = 0xA6;
	meSpi_TransmitReceive_(me->u_spi, &dataTx, &x1, 1, 1000);
	
	dataTx = 0xA7;
	meSpi_TransmitReceive_(me->u_spi, &dataTx, &x0, 1, 1000);
  
	dataTx = 0xA8;
	meSpi_TransmitReceive_(me->u_spi, &dataTx, &y2, 1, 1000);
	
	dataTx = 0xA9;
	meSpi_TransmitReceive_(me->u_spi, &dataTx, &y1, 1, 1000);
	
	dataTx = 0xAA;
	meSpi_TransmitReceive_(me->u_spi, &dataTx, &y0, 1, 1000);
  
	dataTx = 0xAB;
	meSpi_TransmitReceive_(me->u_spi, &dataTx, &z2, 1, 1000);
	
	dataTx = 0xAC;
	meSpi_TransmitReceive_(me->u_spi, &dataTx, &z1, 1, 1000);
	
	dataTx = 0x00;
	meSpi_TransmitReceive_(me->u_spi, &dataTx, &z0, 1, 1000);
 
  meGpio_Set_(me->u_cs);

  //special bit manipulation since there is not a 24 bit signed int data type
  if (x2 & 0x80){
      me->x_Count = 0xFF;
  }
  if (y2 & 0x80){
      me->y_Count = 0xFF;
  }
  if (z2 & 0x80){
      me->z_Count = 0xFF;
  }

  //format results into single 32 bit signed value
  me->x_Count = (me->x_Count * 256 * 256 * 256) | (int32_t)(x2) * 256 * 256 | (uint16_t)(x1) * 256 | x0;
  me->y_Count = (me->y_Count * 256 * 256 * 256) | (int32_t)(y2) * 256 * 256 | (uint16_t)(y1) * 256 | y0;
  me->z_Count = (me->z_Count * 256 * 256 * 256) | (int32_t)(z2) * 256 * 256 | (uint16_t)(z1) * 256 | z0;

  //calculate magnitude of results
  me->uT = sqrt(pow(((float)(me->x_Count)/me->gain),2) + pow(((float)(me->y_Count)/me->gain),2)+ pow(((float)(me->z_Count)/me->gain),2));

	me->x_uT = (float)(me->x_Count)/me->gain;
	me->y_uT = (float)(me->y_Count)/me->gain;
	me->z_uT = (float)(me->z_Count)/me->gain;

	return 0;
}

//addr is the 7 bit value of the register's address (without the R/W bit)
static uint8_t readReg(sCdrvRm3100_Obj * const me, uint8_t addr) {
	
  uint8_t dataTx = 0;
	uint8_t dataRx = 0;
	
	meGpio_Reset_(me->u_cs);
	meDelay_ms_(100);
  
	dataTx = addr | 0x80; //OR with 0x80 to make first bit(read/write bit) high for read
	meSpi_Transmit_(me->u_spi, &dataTx, 1, 1000);
	meSpi_Receive_(me->u_spi, &dataRx, 1, 1000);

  meGpio_Set_(me->u_cs);
	
  return dataRx;
}

//addr is the 7 bit (No r/w bit) value of the internal register's address, data is 8 bit data being written
static void writeReg(sCdrvRm3100_Obj * const me, uint8_t addr, uint8_t data){
	
	uint8_t dataTx = 0;
	
  meGpio_Reset_(me->u_cs);
	meDelay_ms_(100);
  
	dataTx = addr & 0x7F; //AND with 0x7F to make first bit(read/write bit) low for write
	meSpi_Transmit_(me->u_spi, &dataTx, 1, 1000);
	
	dataTx = data;
	meSpi_Transmit_(me->u_spi, &dataTx, 1, 1000);
	
  meGpio_Set_(me->u_cs);
}

//newCC is the new cycle count value (16 bits) to change the data acquisition
static void changeCycleCount(sCdrvRm3100_Obj * const me, uint16_t newCC){
	
	uint8_t dataTx = 0;
	
  uint8_t CCMSB = (newCC & 0xFF00) >> 8; //get the most significant byte
  uint8_t CCLSB = newCC & 0xFF; //get the least significant byte
    
  meGpio_Reset_(me->u_cs);
  meDelay_ms_(100);
	
	dataTx = RM3100_CCX1_REG & 0x7F; //AND with 0x7F to make first bit(read/write bit) low for write
	meSpi_Transmit_(me->u_spi, &dataTx, 1, 1000);
  
	meSpi_Transmit_(me->u_spi, &CCMSB, 1, 1000);  //write new cycle count to ccx1
	meSpi_Transmit_(me->u_spi, &CCLSB, 1, 1000);  //write new cycle count to ccx0
	
	meSpi_Transmit_(me->u_spi, &CCMSB, 1, 1000);  //write new cycle count to ccy1
	meSpi_Transmit_(me->u_spi, &CCLSB, 1, 1000);  //write new cycle count to ccy0
	
	meSpi_Transmit_(me->u_spi, &CCMSB, 1, 1000);  //write new cycle count to ccz1
	meSpi_Transmit_(me->u_spi, &CCLSB, 1, 1000);  //write new cycle count to ccz0
	
	meGpio_Set_(me->u_cs);
}


/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
