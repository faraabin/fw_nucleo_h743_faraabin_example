/**
******************************************************************************
* @file           : cdrv_isl280xx.c
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
#include "cdrv_isl280xx.h"

/* Private define ------------------------------------------------------------*/
#define REG_ADDR_CONFIGURATION		0x00
#define REG_ADDR_SHUNT_VOLTAGE		0x01
#define REG_ADDR_BUS_VOLTAGE			0x02
#define REG_ADDR_POWER						0x03
#define REG_ADDR_CURRENT					0x04
#define REG_ADDR_CALIBRATION			0x05
#define REG_ADDR_V_SHUNT_THR			0x06
#define REG_ADDR_V_BUS_THR				0x07
#define REG_ADDR_DCS_INTR_STAT		0x08
#define REG_ADDR_AUX_CONTROL			0x09

#define CFG_RST_POS   						15
#define CFG_BRNG_POS  						13
#define CFG_PG_POS    						11
#define CFG_BADC_POS  						7
#define CFG_SADC_POS  						3
#define CFG_MODE_POS  						0

#define SHUNT_VOLTAGE_LSB_uV			10.0f
#define BUS_VOLTAGE_LSB_mV				4.0f
#define SHUNT_VOLTAGE_THR_LSB_mV	2.56f
#define BUS_VOLTAGE_THR_LSB_mV		256.0f

/* Private macro -------------------------------------------------------------*/
#define GetBit_(value_, n_)	((value_ >> n_) & 0x01)

/* Private typedef -----------------------------------------------------------*/
/**
  * @brief
  */
typedef struct {
	uint16_t register_value;
	struct {
		uint8_t mode	: 3;
		uint8_t sadc	: 4;
		uint8_t badc	: 4;
		uint8_t pg 		: 2;
		uint8_t brng	: 2;
		uint8_t rst		: 1;
	}fields;
}TyuCdrvIsl280xx_Config;

/* Private variables ---------------------------------------------------------*/
static float full_scale_bus_voltage[4] = {
	0.04f, 0.08f, 0.16f, 0.32f
};

/* Private function prototypes -----------------------------------------------*/
static uint8_t I2CInit(TysCdrvIsl280xx_Obj * const me);
static void UpdateConfigRegister(TysCdrvIsl280xx_Obj * const me);
static void SetCalibrationRegister(TysCdrvIsl280xx_Obj * const me);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                        ##### cdrv_isl280xx.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @param a0 
 * @param a1 
 * @return uint8_t 
 */
uint8_t CdrvIsl280xx_Init(TysCdrvIsl280xx_Obj * const me, TyeCdrvIsl208xx_AddressPinConnection a0, TyeCdrvIsl208xx_AddressPinConnection a1) {
  me->init = false;

  if(me->u_is_broadcast)
    me->device_address = 0x7E;
  else
  {
    if (a0 == eCONNECT_GND && a1 == eCONNECT_GND)
      me->device_address = 0x80;
    else if (a0 == eCONNECT_VCC && a1 == eCONNECT_GND)
      me->device_address = 0x82;
    else if (a0 == eCONNECT_SDA && a1 == eCONNECT_GND)
      me->device_address = 0x84;
    else if (a0 == eCONNECT_SCL && a1 == eCONNECT_GND)
      me->device_address = 0x86;
    else if (a0 == eCONNECT_GND && a1 == eCONNECT_VCC)
      me->device_address = 0x88;
    else if (a0 == eCONNECT_VCC && a1 == eCONNECT_VCC)
      me->device_address = 0x8A;
    else if (a0 == eCONNECT_SDA && a1 == eCONNECT_VCC)
      me->device_address = 0x8C;
    else if (a0 == eCONNECT_SCL && a1 == eCONNECT_VCC)
      me->device_address = 0x8E;
    else if (a0 == eCONNECT_GND && a1 == eCONNECT_SDA)
      me->device_address = 0x90;
    else if (a0 == eCONNECT_VCC && a1 == eCONNECT_SDA)
      me->device_address = 0x92;
    else if (a0 == eCONNECT_SDA && a1 == eCONNECT_SDA)
      me->device_address = 0x94;
    else if (a0 == eCONNECT_SCL && a1 == eCONNECT_SDA)
      me->device_address = 0x96;
    else if (a0 == eCONNECT_GND && a1 == eCONNECT_SCL)
      me->device_address = 0x98;
    else if (a0 == eCONNECT_VCC && a1 == eCONNECT_SCL)
      me->device_address = 0x9A;
    else if (a0 == eCONNECT_SDA && a1 == eCONNECT_SCL)
      me->device_address = 0x9C;
    else if (a0 == eCONNECT_SCL && a1 == eCONNECT_SCL)
      me->device_address = 0x9E;
  }
	
	if(I2CInit(me) != 0)
		return 1;
	
	UpdateConfigRegister(me);
	if(CdrvIsl280xx_UpdateConfigRegister(me) != 0)
		return 1;

	if(CdrvIsl280xx_SetCalibrationRegister(me) != 0)
		return 1;
	
  me->init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t CdrvIsl280xx_Reset(TysCdrvIsl280xx_Obj * const me) {
	TyuCdrvIsl280xx_Config tmp;
	tmp.register_value = me->config_register;
	tmp.fields.rst = 1;
	me->config_register = tmp.register_value;
	if(CdrvIsl280xx_UpdateConfigRegister(me) != 0)
		return 1;
	meDelay_ms_(10);
	//Read I2c Config reg and update this field
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t CdrvIsl280xx_UpdateConfigRegister(TysCdrvIsl280xx_Obj * const me) {
	
	//if(meI2c_Transmit_(
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 */
void CdrvIsl280xx_ReadConfigRegister(TysCdrvIsl280xx_Obj * const me) {
	//transmit I2C command
	//me->config = 
}

/**
 * @brief 
 * 
 * @param me 
 * @param exti_cb 
 * @return uint8_t 
 */
uint8_t CdrvIsl280xx_InterruptCallbackConfig(TysCdrvIsl280xx_Obj * const me, void(*exti_cb)(TyeEdge_Event ev)) {
  if(exti_cb != NULL)
    me->exti_cb = exti_cb;
  else
    return 1;

  return 0;
}

uint8_t CdrvIsl280xx_SetCalibrationRegister(TysCdrvIsl280xx_Obj * const me) {
	SetCalibrationRegister(me);
	
	//Transmit I2C
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t CdrvIsl280xx_InterruptEnable(TysCdrvIsl280xx_Obj * const me);

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t CdrvIsl280xx_InterruptDisable(TysCdrvIsl280xx_Obj * const me);

/**
 * @brief 
 * 
 * @param me 
 * @return float 
 */
float CdrvIsl280xx_ReadShuntVoltage(TysCdrvIsl280xx_Obj * const me) {
  if(!me->init)
    return 0.0;
	
	uint16_t shunt_value_raw = 0;
	float shunt_value_weighted = 0.0;
	//Read I2C config and check for equality of shunt voltage range and pga
	//Read I2C bus voltage register and check CNVR is 1 in triggered mode
	//Read I2C bus voltage register and check OVF is 0 that no overflow is happened
	//Read I2C shunt voltage value register
	
	switch(me->u_shunt_voltage_range)
	{
		case eSHUNT_RANGE_320mV:
			shunt_value_weighted = (float)((int16_t)(shunt_value_raw));
		break;
		case eSHUNT_RANGE_160mv:
			shunt_value_weighted = (float)((int16_t)((shunt_value_raw) & 0x7FFF) << 1) / 2.0f;
		break;
		case eSHUNT_RANGE_80mV:
			shunt_value_weighted = (float)((int16_t)((shunt_value_raw) & 0x3FFF) << 2) / 4.0f;
		break;
		case eSHUNT_RANGE_40mV:
			shunt_value_weighted = (float)((int16_t)((shunt_value_raw) & 0x1FFF) << 3) / 8.0f;
		break;
		default:
			return 0.0f;
	}
	
	return shunt_value_weighted * SHUNT_VOLTAGE_LSB_uV / 1000000.0f;
}

/**
 * @brief 
 * 
 * @param me 
 * @return float 
 */
float CdrvIsl280xx_ReadBusVoltage(TysCdrvIsl280xx_Obj * const me) {
	if(!me->init)
    return 0.0f;
	
	uint16_t bus_value_raw;
	float bus_value_weighted = 0.0;
	//Read I2C config and check the equlaity of bus voltage range and brng
	//Read I2C bus voltage register and check CNVR is 1 in triggered mode
	//Read I2C bus voltage register and check OVF is 0 that no overflow is happened
	//Read I2C bus voltage value register
	
	switch(me->u_bus_voltage_range)
	{
		case eBUS_RANGE_60V:
			bus_value_weighted = (float)((uint16_t)bus_value_raw >> 2);
		break;
		case eBUS_RANGE_32V:
			bus_value_weighted = (float)((uint16_t)bus_value_raw >> 3);
		break;
		case eBUS_RANGE_16V:
			bus_value_weighted = (float)((uint16_t)(bus_value_raw & 0x7FF8) >> 3);
		break;
		default:
			return 0.0f;
	}
	
	return bus_value_weighted * BUS_VOLTAGE_LSB_mV / 1000.0f;
}

/**
 * @brief 
 * 
 * @param me 
 * @return float 
 */
float CdrvIsl280xx_ReadPower(TysCdrvIsl280xx_Obj * const me) {
	if(!me->init)
    return 0.0;
	
	uint16_t power_value_raw = 0;
	float power_value_weighted = 0.0;
	float range_coef  = 1.0f;
	if(me->u_bus_voltage_range == eBUS_RANGE_60V)
		range_coef = 2.0f;
	//Read I2C config and check the equlaity of bus voltage range and brng
	//Read I2C bus voltage register and check CNVR is 1 in triggered mode
	//Read I2C bus voltage register and check OVF is 0 that no overflow is happened
	//Read I2C bus voltage value register
	power_value_weighted = (float)(power_value_raw);
	
	return power_value_weighted * me->current_lsb * (BUS_VOLTAGE_LSB_mV / 1000.0f) * 5000.0f * range_coef;
}

/**
 * @brief 
 * 
 * @param me 
 * @return float 
 */
float CdrvIsl280xx_ReadCurrent(TysCdrvIsl280xx_Obj * const me) {
	if(!me->init)
    return 0.0;
	
	int16_t current_value_raw = 0;
	float current_value_weighted = 0.0;
	//Read I2C config and check the equlaity of bus voltage range and brng
	//Read I2C bus voltage register and check CNVR is 1 in triggered mode
	//Read I2C bus voltage register and check OVF is 0 that no overflow is happened
	//Read I2C bus voltage value register
	current_value_weighted = (float)(current_value_raw);
	
	return current_value_weighted * me->current_lsb;
}

/**
 * @brief 
 * 
 * @param me 
 * @param threshold 
 * @return uint8_t 
 */
uint8_t CdrvIsl280xx_SetBusVoltageThreshold(TysCdrvIsl280xx_Obj * const me, float lower_thr, float upper_thr) {
	if((upper_thr < 0.0f) || (lower_thr < 0.0f))
		return 1;
	if(upper_thr < lower_thr)
		return 1;
	if((lower_thr > 255 * BUS_VOLTAGE_THR_LSB_mV / 1000.0f) || (upper_thr > 255 * BUS_VOLTAGE_THR_LSB_mV / 1000.0f))
		return 1;
	
	uint8_t bmn = (uint8_t)(lower_thr * 1000.0f / BUS_VOLTAGE_THR_LSB_mV);
	uint8_t bmx = (uint8_t)(upper_thr * 1000.0f / BUS_VOLTAGE_THR_LSB_mV);
	
	uint16_t bus_thr_register = (uint16_t)(bmx << 8) + (uint16_t)(bmn);
	
	//Transmit I2C
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param threshold 
 * @return uint8_t 
 */
uint8_t CdrvIsl280xx_SetShuntVoltageThreshold(TysCdrvIsl280xx_Obj * const me, float lower_thr, float upper_thr) {
	if((upper_thr > 127.0f * SHUNT_VOLTAGE_THR_LSB_mV / 1000.0f) || (upper_thr < -128.0f * SHUNT_VOLTAGE_THR_LSB_mV / 1000.0f))
		return 1;
	if((lower_thr > 127.0f * SHUNT_VOLTAGE_THR_LSB_mV / 1000.0f) || (lower_thr < -128.0f * SHUNT_VOLTAGE_THR_LSB_mV / 1000.0f))
		return 1;
	if(upper_thr < lower_thr)
		return 1;
	
	uint8_t smn = (uint8_t)(lower_thr * 1000.0f / SHUNT_VOLTAGE_THR_LSB_mV);
	uint8_t smx = (uint8_t)(upper_thr * 1000.0f / SHUNT_VOLTAGE_THR_LSB_mV);
	
	uint16_t shunt_thr_register = (uint16_t)(smx << 8) + (uint16_t)(smn);
	
	//Transmit I2C
	
	return 0;
}

/*
===============================================================================
                    ##### cdrv_isl280xx.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @return uint8_t 
 */
static uint8_t I2CInit(TysCdrvIsl280xx_Obj * const me) {
  if(me->u_i2c == NULL)
    return 1;
  if(meI2c_Init_(me->u_i2c) != 0)
    return 1;
  
  if(me->u_exti == NULL)
    return 0;
  else {
    me->u_exti->u_dir = eGPIO_DIR_INPUT;
    me->u_exti->u_in_type = eGPIO_PULL_NONE;
    if(meGpio_Init_(me->u_exti) != 0)
      return 1;
    meGpio_Event_Edge_Config_(me->u_exti, eEDGE_CHANGE, me->exti_cb);
  }

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 */
static void UpdateConfigRegister(TysCdrvIsl280xx_Obj * const me) {
	TyuCdrvIsl280xx_Config tmp;
	
	tmp.fields.brng = me->u_bus_voltage_range;
	tmp.fields.badc = me->u_bus_adc_resolution;
	tmp.fields.mode = me->u_mode;
	tmp.fields.pg = me->u_shunt_voltage_range;
	tmp.fields.sadc = me->u_shunt_adc_resolution;
	tmp.fields.rst = 0;
	
	me->config_register = tmp.register_value;
}

/**
 * @brief Set the Calibration Register object
 * 
 * @param me 
 * @return uint8_t 
 */
static void SetCalibrationRegister(TysCdrvIsl280xx_Obj * const me) {
	float full_scale_current = full_scale_bus_voltage[me->u_shunt_voltage_range] / me->u_shunt_resistor;
	uint16_t adc_res;
	switch(me->u_shunt_adc_resolution) {
		case eADC_RES_12Bit1Sample:
			adc_res = (uint16_t)(1 << 12);
		break;
		case eADC_RES_13bit1Sample:
			adc_res = (uint16_t)(1 << 13);
		break;
		case eADC_RES_14Bit1Sample:
			adc_res = (uint16_t)(1 << 14);
		break;
		case eADC_RES_15Bit1Sample:
		case eADC_RES_15Bit2Samples:
		case eADC_RES_15Bit4Samples:
		case eADC_RES_15Bit8Samples:
		case eADC_RES_15Bit16Samples:
		case eADC_RES_15Bit32Samples:
		case eADC_RES_15Bit64Samples:
		case eADC_RES_15Bit128Samples:
			adc_res = (uint16_t)(1 << 15);
		break;
		default:
			return;
	}
	me->current_lsb = full_scale_current / adc_res;
	me->calibration_register = (uint16_t)((0.04096f)/((me->u_shunt_resistor) * (me->current_lsb)));
	me->calibration_register &= ~(0x0001 << 0);
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
