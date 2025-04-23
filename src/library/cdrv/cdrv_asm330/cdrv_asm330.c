/**
******************************************************************************
* @file           : cdrv_asm330.c
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
#include "cdrv_asm330.h"

#include <string.h>

/* Private define ------------------------------------------------------------*/
#define SENSOR_BOOT_TIME_ms     10
#define SENSOR_RESET_TIMEOUT_ms 1000

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint8_t SensorInit(sCdrvAsm330Obj * const me);
int32_t PlatformWriteRegister(void * me, uint8_t reg, const uint8_t *data, uint16_t length);
int32_t PlatformReadRegister(void * me, uint8_t reg, uint8_t *data, uint16_t length);
void PlatformDelay_ms(uint32_t millisec);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                  ##### cdrv_asm330.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @param operationConfig 
 * @return uint8_t 
 */
uint8_t fCdrvAsm330_Init(sCdrvAsm330Obj * const me) {
  me->_init = false;

  if((me->Spi == NULL) || (me->Cs == NULL)) {
    return 1;
  }
  
  me->Spi->u_bit_order = eSPI_FIRSTBIT_MSB;
  me->Spi->u_data_size = 8;
  me->Spi->u_mode = eSPI_MODE_0;
  me->Spi->u_role = eSPI_ROLE_MASTER;
  if(meSpi_Init_(me->Spi) != 0) {
    return 1;
  }

  me->Cs->u_dir = eGPIO_DIR_OUTPUT;
  me->Cs->u_out_type = eGPIO_PUSH_PULL;
  if(meGpio_Init_(me->Cs) != 0) {
    return 1;
  }
  meGpio_Set_(me->Cs);

  if(me->Int1 != NULL) {
    me->Int1->u_dir = eGPIO_DIR_INPUT;
    me->Int1->u_in_type = eGPIO_PULL_NONE;
    if(meGpio_Init_(me->Int1) != 0) {
      return 1;
    }
    meGpio_Event_Edge_Config_(me->Int1, eEDGE_FALLING, me->fpInt1Event);
    meGpio_Event_Edge_Enable_(me->Int1);
  }
  if(me->Int2 != NULL) {
    me->Int2->u_dir = eGPIO_DIR_INPUT;
    me->Int2->u_in_type = eGPIO_PULL_NONE;
    if(meGpio_Init_(me->Int2) != 0) {
      return 1;
    }
    meGpio_Event_Edge_Config_(me->Int2, eEDGE_FALLING, me->fpInt2Event);
    meGpio_Event_Edge_Enable_(me->Int2);
  }

  me->_sensorCtx.handle = (void*)me;
  me->_sensorCtx.mdelay = PlatformDelay_ms;
  me->_sensorCtx.read_reg = PlatformReadRegister;
  me->_sensorCtx.write_reg = PlatformWriteRegister;

  meDelay_ms_(SENSOR_BOOT_TIME_ms);

  if(SensorInit(me) != 0) {
    return 1;
  }

  me->_init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 */
uint8_t fCdrvAsm330_UpdateAccel(sCdrvAsm330Obj * const me) {
  int16_t acclRawData[3];

  asm330lhh_xl_flag_data_ready_get(&me->_sensorCtx, &me->_isDataReady);

  if(!me->_isDataReady) {
    return 1;
  }

  memset(acclRawData, 0x00, 3 * sizeof(int16_t));
  asm330lhh_acceleration_raw_get(&me->_sensorCtx, acclRawData);
  me->Acceleration_mg.X = asm330lhh_from_fs2g_to_mg(acclRawData[0]);
  me->Acceleration_mg.Y = asm330lhh_from_fs2g_to_mg(acclRawData[1]);
  me->Acceleration_mg.Z = asm330lhh_from_fs2g_to_mg(acclRawData[2]);

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 */
uint8_t fCdrvAsm330_UpdateGyro(sCdrvAsm330Obj * const me) {
  int16_t angRateRawData[3];

  asm330lhh_gy_flag_data_ready_get(&me->_sensorCtx, &me->_isDataReady);

  if(!me->_isDataReady) {
    return 1;
  }

  memset(angRateRawData, 0x00, 3 * sizeof(int16_t));
  asm330lhh_angular_rate_raw_get(&me->_sensorCtx, angRateRawData);
  me->AngularRate_mdps.X = asm330lhh_from_fs2000dps_to_mdps(angRateRawData[0]);
  me->AngularRate_mdps.Y = asm330lhh_from_fs2000dps_to_mdps(angRateRawData[1]);
  me->AngularRate_mdps.Z = asm330lhh_from_fs2000dps_to_mdps(angRateRawData[2]);

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 */
uint8_t fCdrvAsm330_UpdateTemp(sCdrvAsm330Obj * const me) {
  int16_t tempRawData;

  asm330lhh_temp_flag_data_ready_get(&me->_sensorCtx, &me->_isDataReady);

  if(!me->_isDataReady) {
    return 1;
  }

  memset(&tempRawData, 0x00, sizeof(int16_t));
  asm330lhh_temperature_raw_get(&me->_sensorCtx, &tempRawData);
  me->Temperature_degC = asm330lhh_from_lsb_to_celsius(tempRawData);
  
  return 0;
}

/*
===============================================================================
                  ##### cdrv_asm330.c Private Functions #####
===============================================================================*/
/**
 * @brief Use example link below for more info
 * https://github.com/STMicroelectronics/STMems_Standard_C_drivers/blob/master/asm330lhh_STdC/examples
 * @param me 
 * @return uint8_t 
 */
uint8_t SensorInit(sCdrvAsm330Obj * const me) {

  asm330lhh_i2c_interface_set(&me->_sensorCtx, ASM330LHH_I2C_DISABLE);
  asm330lhh_spi_mode_set(&me->_sensorCtx, ASM330LHH_SPI_4_WIRE);

  asm330lhh_device_id_get(&me->_sensorCtx, &me->_whoAmI);
  if(me->_whoAmI != ASM330LHH_ID) {
    return 1;
  }

  asm330lhh_reset_set(&me->_sensorCtx, PROPERTY_ENABLE);

  meChrono_StartTimeout_(&me->_timer, SENSOR_RESET_TIMEOUT_ms);
  do {
    if(meChrono_ms_IsTimedOut(&me->_timer)) {
      return 1;
    }
    asm330lhh_reset_get(&me->_sensorCtx, &me->_reset);
  } while (me->_reset);

  asm330lhh_device_conf_set(&me->_sensorCtx, PROPERTY_ENABLE);
  asm330lhh_block_data_update_set(&me->_sensorCtx, PROPERTY_ENABLE);
  asm330lhh_xl_data_rate_set(&me->_sensorCtx, me->AccelOutputDataRate);
  asm330lhh_gy_data_rate_set(&me->_sensorCtx, me->GyroOutputDataRate);
  asm330lhh_xl_full_scale_set(&me->_sensorCtx, me->AccelFullScale);
  asm330lhh_gy_full_scale_set(&me->_sensorCtx, me->GyroFullScale);
  asm330lhh_xl_hp_path_on_out_set(&me->_sensorCtx, ASM330LHH_LP_ODR_DIV_100);
  asm330lhh_xl_filter_lp2_set(&me->_sensorCtx, PROPERTY_ENABLE);

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param reg 
 * @param data 
 * @param size 
 * @return int32_t 
 */
int32_t PlatformWriteRegister(void * me, uint8_t reg, const uint8_t *data, uint16_t length) {
  sCdrvAsm330Obj *device = (sCdrvAsm330Obj*)me;
  uint8_t regAddr = reg;

  meGpio_Reset_(device->Cs);

  if(meSpi_Transmit_(device->Spi, &regAddr, 1, device->SpiTimeout) != 0) {
    meGpio_Set_(device->Cs);
    return 1;
  }
  if(meSpi_Transmit_(device->Spi, (uint8_t*)data, length, device->SpiTimeout) != 0) {
    meGpio_Set_(device->Cs);
    return 1;
  }

  meGpio_Set_(device->Cs);

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param reg 
 * @param data 
 * @param size 
 * @return int32_t 
 */
int32_t PlatformReadRegister(void * me, uint8_t reg, uint8_t *data, uint16_t length) {
  sCdrvAsm330Obj *device = (sCdrvAsm330Obj*)me;
  uint8_t regAddr = reg | 0x80;

  meGpio_Reset_(device->Cs);

  if(meSpi_Transmit_(device->Spi, &regAddr, 1, device->SpiTimeout) != 0) {
    meGpio_Set_(device->Cs);
    return 1;
  }
  if(meSpi_Receive_(device->Spi, data, length, device->SpiTimeout) != 0) {
    meGpio_Set_(device->Cs);
    return 1;
  }

  meGpio_Set_(device->Cs);

  return 0;
}

/**
 * @brief
 *
 */
void PlatformDelay_ms(uint32_t millisec) {
  meDelay_ms_(millisec);
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
