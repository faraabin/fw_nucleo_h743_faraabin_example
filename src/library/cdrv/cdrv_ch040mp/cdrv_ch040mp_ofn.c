/**
******************************************************************************
* @file           : cdrv_ch040mp_ofn.c
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2024 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2024 FaraabinCo.
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
#include "cdrv_ch040mp_ofn.h"
#include "cdrv_ch040mp.h"

#include <string.h>

/* Private typedef -----------------------------------------------------------*/
FARAABIN_FUNCTION_GROUP_TYPE_DEF_(sCdrvCh040mp);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Exported Functions #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, REBOOT, "Resets module.") {

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, SERIAL_CONFIG, "Saves all user configurations.") {

  uint8_t comport;
  int baudrate;

  FARAABIN_Function_GetParam_(2, "%su %d", &comport, &baudrate);

  fCdrvCh040mp_SerialConfig(me, (eCdrvCh040mp_Com)comport, (eCdrvCh040mp_SerialBaudrate)baudrate);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, CONFIG_6DOF, "Configs module for 6DOF mode.") {

  fCdrvCh040mp_Config(me, eCH040MP_CONFIG_6DOF, 0);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, CONFIG_AHRS, "Configs module for AHRS mode.") {

  fCdrvCh040mp_Config(me, eCH040MP_CONFIG_AHRS, 0);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, CONFIG_SET_CALIB, "Sets current pitch/roll to 0.") {

  fCdrvCh040mp_Config(me, eCH040MP_CONFIG_SET_ROLL_PITCH_ZERO, 0);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, CONFIG_RESET_CALIB, "Clears roll/pitch angle calibration.") {

  fCdrvCh040mp_Config(me, eCH040MP_CONFIG_RESET_ROLL_PITCH_CALIBRATION, 0);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, RESET_YAW, "Resets the yaw angle to zero.") {

  fCdrvCh040mp_Config(me, eCH040MP_CONFIG_RESET_SET_YAW_ZERO, 0);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, SET_STATIC_DETECTION_THR, "help") {

  float val = 0.0f;

  FARAABIN_Function_GetParam_(1, "%f", &val);

  fCdrvCh040mp_Config(me, eCH040MP_CONFIG_SET_IMU_THRESHOLD, val);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, SET_ACCL_BW, "Sets accelerometer bandwidth") {

  float val = 0.0f;

  FARAABIN_Function_GetParam_(1, "%f", &val);

  fCdrvCh040mp_Config(me, eCH040MP_CONFIG_SET_IMU_BANDWIDTH, val);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, SET_ACCL_RANGE, "Sets accelerometer range") {

  float val = 0.0f;

  FARAABIN_Function_GetParam_(1, "%f", &val);

  fCdrvCh040mp_Config(me, eCH040MP_CONFIG_SET_IMU_RANGE, val);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, SET_GYRO_BW, "Sets gyro bandwidth") {

  float val = 0.0f;

  FARAABIN_Function_GetParam_(1, "%f", &val);

  fCdrvCh040mp_Config(me, eCH040MP_CONFIG_SET_GYRO_BANDWIDTH, val);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, SET_GYRO_RANGE, "Sets gyro range") {

  float val = 0.0f;

  FARAABIN_Function_GetParam_(1, "%f", &val);

  fCdrvCh040mp_Config(me, eCH040MP_CONFIG_SET_GYRO_RANGE, val);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, SET_COORDINATE_ROTATION, "Sets coordinate system rotation") {

  int8_t c00 = 0;
  int8_t c01 = 0;
  int8_t c02 = 0;
  int8_t c10 = 0;
  int8_t c11 = 0;
  int8_t c12 = 0;
  int8_t c20 = 0;
  int8_t c21 = 0;
  int8_t c22 = 0;

  FARAABIN_Function_GetParam_(9, "%si%si%si%si%si%si%si%si%si", &c00, &c01, &c02, &c10, &c11, &c12, &c20, &c21, &c22);

  fCdrvCh040mp_ConfigCoordinateSystem(me, c00, c01, c02, c10, c11, c12, c20, c21, c22);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, SET_INCL_RANGE, "Sets inclinometer range") {

  float val = 0.0f;

  FARAABIN_Function_GetParam_(1, "%f", &val);

  fCdrvCh040mp_Config(me, eCH040MP_CONFIG_SET_INCLINOMETER_RANGE, val);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  fCdrvCh040mp_Reboot(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, ENABLE_LOG, "help") {

  fCdrvCh040mp_EnableLogs(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, DISABLE_LOG, "help") {

  fCdrvCh040mp_DisableLogs(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, LOG_VERSION, "help") {

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, LOG_USER_CONFIG, "help") {

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, LOG_COM_CONFIG, "help") {

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, CONFIG_OUT_MSG, "help") {

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, UNLOGALL, "Disables all data output.") {

  fCdrvCh040mp_UnlogAll(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, SAVE_CONFIG, "Saves all user configurations.") {

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(CdrvCh040mp, RESET_FACTORY, "Restor factory default settings.") {

  fCdrvCh040mp_SaveConfig(me);

  meSerial_Send_(me->_uartIntf, me->TxBuffer, me->TxFrameSize, 1000);

  FARAABIN_FUNCTION_END_();
}

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Private Functions #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_GROUP_(CdrvCh040mp, "CH040MP Command function group.") {

  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, REBOOT);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, SERIAL_CONFIG);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, CONFIG_6DOF);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, CONFIG_AHRS);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, CONFIG_SET_CALIB);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, CONFIG_RESET_CALIB);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, RESET_YAW);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, SET_STATIC_DETECTION_THR);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, SET_ACCL_BW);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, SET_ACCL_RANGE);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, SET_GYRO_BW);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, SET_GYRO_RANGE);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, SET_COORDINATE_ROTATION);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, SET_INCL_RANGE);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, ENABLE_LOG);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, DISABLE_LOG);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, LOG_USER_CONFIG);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, LOG_COM_CONFIG);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, CONFIG_OUT_MSG);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, UNLOGALL);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, SAVE_CONFIG);
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvCh040mp, RESET_FACTORY);

}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
