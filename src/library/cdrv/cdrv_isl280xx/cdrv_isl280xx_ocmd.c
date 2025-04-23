/**
******************************************************************************
* @file           : cdrv_isl280xx_ocmd.c
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
#include "cdrv_isl280xx_ocmd.h"
#include "cdrv_isl280xx.h"

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(TysCdrvIsl280xx_Obj);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                        ##### cdrv_isl280xx_ocmd.c Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 */
meCONSOLE_CMD_(cdrv_isl280xx, RESET,
"type cmd help here") {
  CdrvIsl280xx_Reset(me);
  meCONSOLE_END_;
}

/**
 * @brief 
 * 
 */
meCONSOLE_CMD_(cdrv_isl280xx, UPDATE_CONFIG,
"type cmd help here") {
  if(CdrvIsl280xx_UpdateConfigRegister(me) != 0)
		mePRINTF_ERROR_("Config Register Update ERROR");
  meCONSOLE_END_;
}

/**
 * @brief 
 * 
 */
meCONSOLE_CMD_(cdrv_isl280xx, UPDATE_CALIBRATION,
"type cmd help here") {
	float shunt_res;
	meCONSOLE_GET_PAR_(1, "%f", &shunt_res);
	me->u_shunt_resistor = shunt_res;
	
	CdrvIsl280xx_SetCalibrationRegister(me);
	
  meCONSOLE_END_;
}

/**
 * @brief 
 * 
 */
meCONSOLE_CMD_(cdrv_isl280xx, READ_SHUNT_VOLTAGE,
"type cmd help here") {
	mePRINTF_("Shunt voltage: %f volts", CdrvIsl280xx_ReadShuntVoltage(me));
	
  meCONSOLE_END_;
}

/**
 * @brief 
 * 
 */
meCONSOLE_CMD_(cdrv_isl280xx, READ_BUS_VOLTAGE,
"type cmd help here") {
	mePRINTF_("Bus voltage: %f volts", CdrvIsl280xx_ReadBusVoltage(me));
	
  meCONSOLE_END_;
}

/**
 * @brief 
 * 
 */
meCONSOLE_CMD_(cdrv_isl280xx, READ_CURRENT,
"type cmd help here") {
	mePRINTF_("Current: %f amps", CdrvIsl280xx_ReadCurrent(me));
	
  meCONSOLE_END_;
}

/**
 * @brief 
 * 
 */
meCONSOLE_CMD_(cdrv_isl280xx, READ_POWER,
"type cmd help here") {
	mePRINTF_("Power: %f watts", CdrvIsl280xx_ReadPower(me));
	
  meCONSOLE_END_;
}

/**
 * @brief 
 * 
 */
meCONSOLE_CMD_(cdrv_isl280xx, SET_BUS_VOLTAGE_THR,
"type cmd help here") {
	float lower_thr, upper_thr;
	
	meCONSOLE_GET_PAR_(2, "%f %f", &lower_thr, &upper_thr);
	
	if(CdrvIsl280xx_SetBusVoltageThreshold(me, lower_thr, upper_thr) != 0)
		mePRINTF_ERROR_("ERROR setting threshold.");
	
  meCONSOLE_END_;
}

/**
 * @brief 
 * 
 */
meCONSOLE_CMD_(cdrv_isl280xx, SET_SHUNT_VOLTAGE_THR,
"type cmd help here") {
	float lower_thr, upper_thr;
	
	meCONSOLE_GET_PAR_(2, "%f %f", &lower_thr, &upper_thr);
	
	if(CdrvIsl280xx_SetShuntVoltageThreshold(me, lower_thr, upper_thr) != 0)
		mePRINTF_ERROR_("ERROR setting threshold.");
	
  meCONSOLE_END_;
}

/**
 * @brief 
 * 
 */
meCONSOLE_CMD_(cdrv_isl280xx, DEVICE_INFO,
"type cmd help here") {
  CdrvIsl280xx_ReadConfigRegister(me);
  mePRINTF_("======== Info for %s PM device ========", me->u_name);
	mePRINTF_("Device address: 0x%04X", me->device_address);
	
	switch(me->u_bus_voltage_range)
	{
		case eBUS_RANGE_16V:
			mePRINTF_("Bus voltage range: 16V");
		break;
		case eBUS_RANGE_32V:
			mePRINTF_("Bus voltage range: 32V");
		break;
		case eBUS_RANGE_60V:
			mePRINTF_("Bus voltage range: 60V");
		break;
		default:
			break;
	}
	switch(me->u_bus_adc_resolution)
	{
		case eADC_RES_12Bit1Sample:
			mePRINTF_("Bus voltage ADC resolution: 12 bits with 1 sample");
		break;
		case eADC_RES_13bit1Sample:
			mePRINTF_("Bus voltage ADC resolution: 13 bits with 1 sample");
		break;
		case eADC_RES_14Bit1Sample:
			mePRINTF_("Bus voltage ADC resolution: 14 bits with 1 sample");
		break;
		case eADC_RES_15Bit1Sample:
			mePRINTF_("Bus voltage ADC resolution: 15 bits with 1 sample");
		break;
		case eADC_RES_15Bit2Samples:
			mePRINTF_("Bus voltage ADC resolution: 15 bits with 2 samples");
		break;
		case eADC_RES_15Bit4Samples:
			mePRINTF_("Bus voltage ADC resolution: 15 bits with 4 samples");
		break;
		case eADC_RES_15Bit8Samples:
			mePRINTF_("Bus voltage ADC resolution: 15 bits with 8 samples");
		break;
		case eADC_RES_15Bit16Samples:
			mePRINTF_("Bus voltage ADC resolution: 15 bits with 16 samples");
		break;
		case eADC_RES_15Bit32Samples:
			mePRINTF_("Bus voltage ADC resolution: 15 bits with 32 samples");
		break;
		case eADC_RES_15Bit64Samples:
			mePRINTF_("Bus voltage ADC resolution: 15 bits with 64 samples");
		break;
		case eADC_RES_15Bit128Samples:
			mePRINTF_("Bus voltage ADC resolution: 15 bits with 128 samples");
		break;
		default:
			break;
	}
	
	switch(me->u_shunt_voltage_range)
	{
		case eSHUNT_RANGE_40mV:
			mePRINTF_("Shunt voltage range: 40mV");
		break;
		case eSHUNT_RANGE_80mV:
			mePRINTF_("Shunt voltage range: 80mV");
		break;
		case eSHUNT_RANGE_160mv:
			mePRINTF_("Shunt voltage range: 160mV");
		break;
		case eSHUNT_RANGE_320mV:
			mePRINTF_("Shunt voltage range: 320mV");
		break;
		default:
			break;
	}
	switch(me->u_shunt_adc_resolution)
	{
		case eADC_RES_12Bit1Sample:
			mePRINTF_("Shunt voltage ADC resolution: 12 bits with 1 sample");
		break;
		case eADC_RES_13bit1Sample:
			mePRINTF_("Shunt voltage ADC resolution: 13 bits with 1 sample");
		break;
		case eADC_RES_14Bit1Sample:
			mePRINTF_("Shunt voltage ADC resolution: 14 bits with 1 sample");
		break;
		case eADC_RES_15Bit1Sample:
			mePRINTF_("Shunt voltage ADC resolution: 15 bits with 1 sample");
		break;
		case eADC_RES_15Bit2Samples:
			mePRINTF_("Shunt voltage ADC resolution: 15 bits with 2 samples");
		break;
		case eADC_RES_15Bit4Samples:
			mePRINTF_("Shunt voltage ADC resolution: 15 bits with 4 samples");
		break;
		case eADC_RES_15Bit8Samples:
			mePRINTF_("Shunt voltage ADC resolution: 15 bits with 8 samples");
		break;
		case eADC_RES_15Bit16Samples:
			mePRINTF_("Shunt voltage ADC resolution: 15 bits with 16 samples");
		break;
		case eADC_RES_15Bit32Samples:
			mePRINTF_("Shunt voltage ADC resolution: 15 bits with 32 samples");
		break;
		case eADC_RES_15Bit64Samples:
			mePRINTF_("Shunt voltage ADC resolution: 15 bits with 64 samples");
		break;
		case eADC_RES_15Bit128Samples:
			mePRINTF_("Shunt voltage ADC resolution: 15 bits with 128 samples");
		break;
		default:
			break;
	}
	
	switch(me->u_mode)
	{
		case eMODE_PowerDown:
			mePRINTF_("Device mode is POWER DOWN.");
		break;
		case eMODE_SVTrig:
			mePRINTF_("Device mode is SHUNT VOLTAGE TRIGGERED.");
		break;
		case eMODE_BVTrig:
			mePRINTF_("Device mode is BUS VOLTAGE TRIGGERED.");
		break;
		case eMODE_SVBVTrig:
			mePRINTF_("Device mode is SHUNT and BUS VOLTAGE TRIGGERED.");
		break;
		case eMODE_ADCOff:
			mePRINTF_("Device mode is ADC OFF.");
		break;
		case eMODE_SVCont:
			mePRINTF_("Device mode is SHUNT VOLTAGE CONTINUOUS.");
		break;
		case eMODE_BVCont:
			mePRINTF_("Device mode is BUS VOLTAGE CONTINUOUS.");
		break;
		case eMODE_SVBVCont:
			mePRINTF_("Device mode is SHUNT and BUS VOLTAGE CONTINUOUS.");
		break;
		default:
			break;
	}
	
	mePRINTF_("Calculated current LSB: %f Amps", me->current_lsb);
	mePRINTF_("Calculated power LSB: %f Watts", me->power_lsb);
	mePRINTF_("Device shunt resistor: %f Ohms", me->u_shunt_resistor);
	
	mePRINTF_("======================================");
	
  meCONSOLE_END_;
}

/*
===============================================================================
                    ##### cdrv_isl280xx_ocmd.c Private Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_GROUP_(cdrv_isl280xx,
"type cmd help here") {
  meCONSOLE_ADD_CMD_(cdrv_isl280xx, RESET, 0);
	meCONSOLE_ADD_CMD_(cdrv_isl280xx, UPDATE_CONFIG, 0);
	meCONSOLE_ADD_CMD_(cdrv_isl280xx, UPDATE_CALIBRATION, 0);
	meCONSOLE_ADD_CMD_(cdrv_isl280xx, READ_SHUNT_VOLTAGE, 0);
	meCONSOLE_ADD_CMD_(cdrv_isl280xx, READ_BUS_VOLTAGE, 0);
	meCONSOLE_ADD_CMD_(cdrv_isl280xx, READ_CURRENT, 0);
	meCONSOLE_ADD_CMD_(cdrv_isl280xx, READ_POWER, 0);
	meCONSOLE_ADD_CMD_(cdrv_isl280xx, SET_BUS_VOLTAGE_THR, 0);
	meCONSOLE_ADD_CMD_(cdrv_isl280xx, SET_SHUNT_VOLTAGE_THR, 0);
	meCONSOLE_ADD_CMD_(cdrv_isl280xx, DEVICE_INFO, 0);

  meCONSOLE_END_;
}

 /************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
