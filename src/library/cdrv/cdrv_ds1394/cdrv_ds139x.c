/**
******************************************************************************
* @file           : cdrv_ds139x.c
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
#include "cdrv_ds139x.h"

/* Private define ------------------------------------------------------------*/
#define DS139X_REG_100THS		            0x00
#define DS139X_REG_SECONDS		          0x01
#define DS139X_REG_MINUTES		          0x02
#define DS139X_REG_HOURS		            0x03
#define DS139X_REG_DAY			            0x04
#define DS139X_REG_DATE			            0x05
#define DS139X_REG_MONTH_CENT           0x06
#define DS139X_REG_YEAR			            0x07

#define DS139X_REG_ALARM_100THS		      0x08
#define DS139X_REG_ALARM_SECONDS	      0x09
#define DS139X_REG_ALARM_MINUTES	      0x0A
#define DS139X_REG_ALARM_HOURS		      0x0B
#define DS139X_REG_ALARM_DAY_DATE       0x0C

#define DS139X_REG_CONTROL              0x0D
#define DS139X_REG_STATUS               0x0E
#define DS139X_REG_TRICKLE              0x0F

#define DS139X_TRICKLE_CHARGER_ENABLE   0xA0
#define DS139X_TRICKLE_CHARGER_250_OHM  0x01
#define DS139X_TRICKLE_CHARGER_2K_OHM   0x02
#define DS139X_TRICKLE_CHARGER_4K_OHM   0x03
#define DS139X_TRICKLE_CHARGER_NO_DIODE 0x04
#define DS139X_TRICKLE_CHARGER_DIODE    0x08

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint8_t Init(TysRtc_Obj * const me);
TysDT_DateTime GetDateTime(TysRtc_Obj * const me);
uint8_t SetDateTime(TysRtc_Obj * const me, TysDT_DateTime dt);
static void Rtc_ctor(TysRtc_Obj * me, void * const private_);

static uint8_t ReadRegister(sCdrvDs139x_Obj * const me, uint8_t addr, uint8_t *data, uint8_t size);
static uint8_t WriteRegister(sCdrvDs139x_Obj * const me, uint8_t addr, uint8_t *data, uint8_t size);
static uint8_t RTC_ByteToBcd2(uint8_t Value);
static uint8_t RTC_Bcd2ToByte(uint8_t Value);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                ##### cdrv_ds139x.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvDs139x_Init(sCdrvDs139x_Obj * const me) {
  me->init = false;

  if((me->Spi == NULL) || (me->Cs == NULL)) {
    return 1;
  }
  me->Cs->u_dir = eGPIO_DIR_OUTPUT;
  me->Cs->u_out_type = eGPIO_PUSH_PULL;
  if(meGpio_Init_(me->Cs) != 0) {
    return 1;
  }
  meGpio_Set_(me->Cs);

  me->Spi->u_bit_order = eSPI_FIRSTBIT_MSB;
  me->Spi->u_data_size = 8;
  me->Spi->u_mode = eSPI_MODE_0;
  me->Spi->u_role = eSPI_ROLE_MASTER;
  if(meSpi_Init_(me->Spi) != 0) {
    return 1;
  }

  Rtc_ctor(&me->Rtc, (void*)me);

  me->init = true;
  return 0;
}

/*
===============================================================================
                ##### cdrv_ds139x.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t Init(TysRtc_Obj * const me) {
//  sCdrvDs139x_Obj *rtcParent = (sCdrvDs139x_Obj*)me->private_;

  me->init = true;
  return 0;
}

/**
 * @brief Get the Date Time object
 * 
 * @param me 
 * @return TysDT_DateTime 
 */
TysDT_DateTime GetDateTime(TysRtc_Obj * const me) {
  sCdrvDs139x_Obj *rtcParent = (sCdrvDs139x_Obj*)me->private_;
  TysDT_DateTime dt = {
    dt.u_time.u_second = 0,
    dt.u_time.u_minute = 0,
    dt.u_time.u_hour = 0,
    dt.u_date.u_week_day = 0,
    dt.u_date.u_day = 0,
    dt.u_date.u_month = 0,
  };
  uint8_t tmpData[7];

  if(!me->init) {
    return dt;
  }

  if(ReadRegister(rtcParent, DS139X_REG_SECONDS, tmpData, sizeof(tmpData)) != 0) {
    return dt;
  }

  dt.u_time.u_second = RTC_Bcd2ToByte(tmpData[0]);
  dt.u_time.u_minute = RTC_Bcd2ToByte(tmpData[1]);
  dt.u_time.u_hour = RTC_Bcd2ToByte(tmpData[2] & 0x3F);
  dt.u_date.u_week_day = RTC_Bcd2ToByte(tmpData[3]);
  dt.u_date.u_day = RTC_Bcd2ToByte(tmpData[4]);
  dt.u_date.u_month = RTC_Bcd2ToByte(tmpData[5] & 0x7F);
  if(meEdge(&rtcParent->_centuryEvent, tmpData[5] & 0x80) == eEDGE_CHANGE) {
    rtcParent->StartDate += 100;
  }
  dt.u_date.u_year = RTC_Bcd2ToByte(tmpData[6]) + rtcParent->StartDate;
  
  return dt;
}

/**
 * @brief Set the Date Time object
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t SetDateTime(TysRtc_Obj * const me, TysDT_DateTime dt) {
  sCdrvDs139x_Obj *rtcParent = (sCdrvDs139x_Obj*)me->private_;
  uint8_t tmpData[7];

  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);

  tmpData[0] = RTC_ByteToBcd2(dt.u_time.u_second);
  tmpData[1] = RTC_ByteToBcd2(dt.u_time.u_minute);
  tmpData[2] = RTC_ByteToBcd2(dt.u_time.u_hour);
  tmpData[3] = RTC_ByteToBcd2(dt.u_date.u_week_day);
  tmpData[4] = RTC_ByteToBcd2(dt.u_date.u_day);
  tmpData[5] = RTC_ByteToBcd2(dt.u_date.u_month);
  uint8_t cent;
  meEdge_Force(&rtcParent->_centuryEvent, ReadRegister(rtcParent, DS139X_REG_MONTH_CENT, &cent, 1) & 0x80);
  tmpData[6] = RTC_ByteToBcd2(dt.u_date.u_year - rtcParent->StartDate);

  if(WriteRegister(rtcParent, DS139X_REG_SECONDS, tmpData, sizeof(tmpData)) != 0) {
    return 1;
  }

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param private_ 
 */
static void Rtc_ctor(TysRtc_Obj * me, void * const private) {
  static struct TysRtcVtbl const vtbl = {
    Init,
    GetDateTime,
    SetDateTime,
  };

  if(me == NULL) {
    return;
  }

  uint8_t *tmp = (uint8_t*)me;
  for(uint16_t i=0; i<sizeof(*me); i++) {
    tmp[i] = 0;
  }

  /*Initialize Special param*/
  me->init = false;
  me->u_enable = true;
  me->vptr = &vtbl;
  me->private_ = private;
}

/**
 * @brief 
 * 
 * @param me 
 * @param addr 
 * @return uint8_t 
 */
static uint8_t ReadRegister(sCdrvDs139x_Obj * const me, uint8_t addr, uint8_t *data, uint8_t size) {
  uint8_t txData = addr;

  meGpio_Reset_(me->Cs);
  if(meSpi_Transmit_(me->Spi, &txData, 1, me->SpiTimeout_ms) != 0) {
    return 1;
  }
  if(meSpi_Receive_(me->Spi, data, size, me->SpiTimeout_ms) != 0) {
    return 1;
  }
  meGpio_Set_(me->Cs);

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param addr 
 * @param data 
 * @return uint8_t 
 */
static uint8_t WriteRegister(sCdrvDs139x_Obj * const me, uint8_t addr, uint8_t *data, uint8_t size) {

  uint8_t txData = addr | 0x80;

  meGpio_Reset_(me->Cs);
  meSpi_Transmit_(me->Spi, &txData, 1, me->SpiTimeout_ms);
  meSpi_Transmit_(me->Spi, data, size, me->SpiTimeout_ms);
  meGpio_Set_(me->Cs);

  return 0;
}

/**
  * @brief  Convert a 2 digit decimal to BCD format.
  * @param  Value Byte to be converted
  * @retval Converted byte
  */
static uint8_t RTC_ByteToBcd2(uint8_t Value) {
  uint32_t bcdhigh = 0U;
  uint8_t temp = Value;

  while (temp >= 10U)
  {
    bcdhigh++;
    temp -= 10U;
  }

  return ((uint8_t)(bcdhigh << 4U) | temp);
}

/**
  * @brief  Convert from 2 digit BCD to Binary.
  * @param  Value BCD value to be converted
  * @retval Converted word
  */
static uint8_t RTC_Bcd2ToByte(uint8_t Value) {
  uint8_t tmp;
  tmp = ((Value & 0xF0U) >> 4U) * 10U;
  return (tmp + (Value & 0x0FU));
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
