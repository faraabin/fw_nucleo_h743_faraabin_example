/**
******************************************************************************
* @file           : cdrv_ch040mp.c
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
#include "cdrv_ch040mp.h"
#include "library\utility\chrono\chrono.h"

#include <stdlib.h>
#include <string.h>

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
#pragma pack(1)
typedef struct {

  uint8_t FrameHeader;
  uint8_t FrameType;

  uint16_t DataLength;
  uint16_t Crc;

  uint8_t PackectTag;
  uint8_t DeviceId;
  uint16_t Resv;

  uint8_t DataField[509];

}sCh040mp_Frame;
#pragma pack(8)

typedef union {
  
  uint8_t Byte[2];
  uint16_t U16;
  int16_t I16;

}uData2Byte;

typedef union {
  
  uint8_t Byte[4];
  uint16_t U16[2];
  int16_t I16[2];
  uint32_t U32;
  int32_t I32;
  float32_t F32;

}uDat4Byte;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint16_t fCalcCrc(uint8_t *data, uint16_t size, uint16_t initVal);

/* Variables -----------------------------------------------------------------*/

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Exported Functions #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 * @param me 
 * @param uartIntf 
 * @param txBuffer 
 * @param txBufferSize 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_Init(sCdrvCh040mp * const me, TysSerial_Obj* uartIntf, uint8_t *txBuffer, uint16_t txBufferSize) {

  me->_init = false;
  
  if(uartIntf == NULL) {
    return CH040MP_NULL_UART_ERROR;
  }
  
  me->_uartIntf = uartIntf;
  
  if((txBuffer == NULL) || (txBufferSize == 0)) {
    return CH040MP_TX_BUFFER_ERROR;
  }
  
  me->TxBuffer = txBuffer;
  me->TxBufferSize = txBufferSize;
  
  // Reset all data
  uint8_t *tmp = (uint8_t*)&(me->Data);
  for(int i = 0; i < sizeof(sCdrvCh040mp_Data); i++) {
    tmp[i] = 0x00;
  }

  if(me->_Sin != NULL) {

    me->_Sin->u_dir = eGPIO_DIR_INPUT;
    me->_Sin->u_in_type = eGPIO_PULL_NONE;
    me->_Sin->u_invert = false;
    if(meGpio_Init_(me->_Sin) != 0) {
      return CH040MP_GPIO_ERROR;
    }
  }

  if(me->_Sout != NULL) {

    me->_Sout->u_dir = eGPIO_DIR_OUTPUT;
    me->_Sout->u_out_type = eGPIO_PUSH_PULL;
    if(meGpio_Init_(me->_Sout) != 0) {
      return CH040MP_GPIO_ERROR;
    }

    meGpio_Set_(me->_Sout);
  }

  me->_init = true;
  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @param data 
 * @param size 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_Interpret(sCdrvCh040mp * const me, uint8_t *data, uint16_t size) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  if(size == 0) {
    return CH040MP_DATA_LENGTH_ERROR;
  }
  if(size < 7) {
    return CH040MP_DATA_LENGTH_ERROR;
  }

  sCh040mp_Frame *frame = (sCh040mp_Frame*)data;

  me->_newDataAvailable = false;

  if((size - 6) != frame->DataLength) {
    return CH040MP_DATA_LENGTH_ERROR;
  }

  if(frame->FrameHeader != 0x5A) {
    return CH040MP_HEADER_ERROR;
  }

  if(frame->FrameType != 0xA5) {
    return CH040MP_HEADER_ERROR;
  }

  // CRC is separated from start of frame until byte 4 and from byt 6 until end of frame!
  uint16_t crc = fCalcCrc(&data[6], frame->DataLength, fCalcCrc(data, 4, 0));

  if(crc != frame->Crc) {
    return CH040MP_CRC_ERROR;
  }
  
  me->DevId = frame->DeviceId;

  switch(frame->PackectTag) {

    case 0x91: {
      
      uDat4Byte tmp;
      
      tmp.Byte[0] = frame->DataField[0];
      tmp.Byte[1] = frame->DataField[1];
      tmp.Byte[2] = frame->DataField[2];
      tmp.Byte[3] = frame->DataField[3];
      me->Data.Pressure_Pa = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[4];
      tmp.Byte[1] = frame->DataField[5];
      tmp.Byte[2] = frame->DataField[6];
      tmp.Byte[3] = frame->DataField[7];
      me->Data.TimeStamp_MilliS = tmp.U32;
      
      tmp.Byte[0] = frame->DataField[8];
      tmp.Byte[1] = frame->DataField[9];
      tmp.Byte[2] = frame->DataField[10];
      tmp.Byte[3] = frame->DataField[11];
      me->Data.Acceleration_MilliG.X = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[12];
      tmp.Byte[1] = frame->DataField[13];
      tmp.Byte[2] = frame->DataField[14];
      tmp.Byte[3] = frame->DataField[15];
      me->Data.Acceleration_MilliG.Y = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[16];
      tmp.Byte[1] = frame->DataField[17];
      tmp.Byte[2] = frame->DataField[18];
      tmp.Byte[3] = frame->DataField[19];
      me->Data.Acceleration_MilliG.Z = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[20];
      tmp.Byte[1] = frame->DataField[21];
      tmp.Byte[2] = frame->DataField[22];
      tmp.Byte[3] = frame->DataField[23];
      me->Data.AngularVelocity_DegPerS.X = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[24];
      tmp.Byte[1] = frame->DataField[25];
      tmp.Byte[2] = frame->DataField[26];
      tmp.Byte[3] = frame->DataField[27];
      me->Data.AngularVelocity_DegPerS.Y = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[28];
      tmp.Byte[1] = frame->DataField[29];
      tmp.Byte[2] = frame->DataField[30];
      tmp.Byte[3] = frame->DataField[31];
      me->Data.AngularVelocity_DegPerS.Z = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[32];
      tmp.Byte[1] = frame->DataField[33];
      tmp.Byte[2] = frame->DataField[34];
      tmp.Byte[3] = frame->DataField[35];
      me->Data.MagenticIntensity_MicroT.X = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[36];
      tmp.Byte[1] = frame->DataField[37];
      tmp.Byte[2] = frame->DataField[38];
      tmp.Byte[3] = frame->DataField[39];
      me->Data.MagenticIntensity_MicroT.Y = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[40];
      tmp.Byte[1] = frame->DataField[41];
      tmp.Byte[2] = frame->DataField[42];
      tmp.Byte[3] = frame->DataField[43];
      me->Data.MagenticIntensity_MicroT.Z = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[44];
      tmp.Byte[1] = frame->DataField[45];
      tmp.Byte[2] = frame->DataField[46];
      tmp.Byte[3] = frame->DataField[47];
      me->Data.EulerAngles_Deg.Roll = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[48];
      tmp.Byte[1] = frame->DataField[49];
      tmp.Byte[2] = frame->DataField[50];
      tmp.Byte[3] = frame->DataField[51];
      me->Data.EulerAngles_Deg.Pitch = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[52];
      tmp.Byte[1] = frame->DataField[53];
      tmp.Byte[2] = frame->DataField[54];
      tmp.Byte[3] = frame->DataField[55];
      me->Data.EulerAngles_Deg.Yaw = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[56];
      tmp.Byte[1] = frame->DataField[57];
      tmp.Byte[2] = frame->DataField[58];
      tmp.Byte[3] = frame->DataField[59];
      me->Data.NodeQuaternion.W = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[60];
      tmp.Byte[1] = frame->DataField[61];
      tmp.Byte[2] = frame->DataField[62];
      tmp.Byte[3] = frame->DataField[63];
      me->Data.NodeQuaternion.X = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[64];
      tmp.Byte[1] = frame->DataField[65];
      tmp.Byte[2] = frame->DataField[66];
      tmp.Byte[3] = frame->DataField[67];
      me->Data.NodeQuaternion.Y = tmp.F32;
      
      tmp.Byte[0] = frame->DataField[68];
      tmp.Byte[1] = frame->DataField[69];
      tmp.Byte[2] = frame->DataField[70];
      tmp.Byte[3] = frame->DataField[71];
      me->Data.NodeQuaternion.Z = tmp.F32;

      me->Data.Temperature_C = (int8_t)frame->DataField[72];

      me->_newDataAvailable = true;

      break;
    }

    default: {
      return CH040MP_DATA_TAG_ERROR;
    }
  }

  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @param timeout_ms 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_IsDataReady(sCdrvCh040mp * const me, uint32_t timeout_ms) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  if(me->_Sin == NULL) {

    if(me->_newDataAvailable) {
      return CH040MP_OK;
    } else {
      return CH040MP_DATA_NOT_READY_ERROR;
    }
  }

  sChrono timeout = {0x00};

  fChrono_StartTimeoutMs(&timeout, timeout_ms);

  while(true) {

    if(fChrono_IsTimeout(&timeout)) {
      return CH040MP_TIMEOUT_ERROR;
    }

    uint8_t tmp = 0;
    meGpio_Read_(me->_Sin, &tmp);
    if(tmp == 1) {
      return CH040MP_OK;
    }
  }
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_Reboot(sCdrvCh040mp * const me) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "REBOOT\r\n");

  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_SaveConfig(sCdrvCh040mp * const me) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "SAVECONFIG\r\n");

  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @param config 
 * @param configValue 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_Config(sCdrvCh040mp * const me, eCdrvCh040mp_ConfigMode config, float configValue) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  switch(config) {

    case eCH040MP_CONFIG_6DOF: {

      me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG ATT MODE 0\r\n");

      break;
    }

    case eCH040MP_CONFIG_AHRS: {

      me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG ATT MODE 1\r\n");

      break;
    }

    case eCH040MP_CONFIG_SET_ROLL_PITCH_ZERO: {

      me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG ATT RST 2\r\n");

      break;
    }

    case eCH040MP_CONFIG_RESET_ROLL_PITCH_CALIBRATION: {

      me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG ATT RST 3\r\n");

      break;
    }

    case eCH040MP_CONFIG_RESET_SET_YAW_ZERO: {

      me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG ATT RST 4\r\n");

      break;
    }

    case eCH040MP_CONFIG_SET_IMU_THRESHOLD: {

      if((configValue > 0.0f) && (configValue < 1.0f)) {

        me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG IMU ZARU %04.2f\r\n", configValue);

      } else {

        me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG IMU ZARU %d\r\n", (uint8_t)configValue);

      }

      break;
    }

    case eCH040MP_CONFIG_SET_IMU_BANDWIDTH: {

      if((uint8_t)configValue > 6) {
        return CH040MP_CONFIG_ERROR;
      }

      me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG IMU ABW %d\r\n", (uint8_t)configValue);

      break;
    }

    case eCH040MP_CONFIG_SET_IMU_RANGE: {

      if((uint8_t)configValue > 3) {
        return CH040MP_CONFIG_ERROR;
      }

      me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG IMU ARG %d\r\n", (uint8_t)configValue);

      break;
    }

    case eCH040MP_CONFIG_SET_GYRO_BANDWIDTH: {

      if((uint8_t)configValue > 6) {
        return CH040MP_CONFIG_ERROR;
      }

      me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG IMU GBW %d\r\n", (uint8_t)configValue);

      break;
    }

    case eCH040MP_CONFIG_SET_GYRO_RANGE: {

      if((uint8_t)configValue > 3) {
        return CH040MP_CONFIG_ERROR;
      }

      me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG IMU GRG %d\r\n", (uint8_t)configValue);

      break;
    }

    case eCH040MP_CONFIG_SET_INCLINOMETER_RANGE: {

      if((uint8_t)configValue > 1) {
        return CH040MP_CONFIG_ERROR;
      }

      me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG IMU INC_FMT %d\r\n", (uint8_t)configValue);

      break;
    }

    case eCH040MP_CONFIG_SET_SYSTEM_ROTATION_COORDINATE:
    default: {
      return CH040MP_CONFIG_ERROR;
    }
  }

  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @param c00 
 * @param c01 
 * @param c02 
 * @param c10 
 * @param c11 
 * @param c12 
 * @param c20 
 * @param c21 
 * @param c22 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_ConfigCoordinateSystem(sCdrvCh040mp * const me, int8_t c00, int8_t c01, int8_t c02, int8_t c10, int8_t c11, int8_t c12, int8_t c20, int8_t c21, int8_t c22) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "CONFIG IMU URFR %i,%i,%i,%i,%i,%i,%i,%i,%i\r\n", c00, c01, c02, c10, c11, c12, c20, c21, c22);

  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_EnableLogs(sCdrvCh040mp * const me) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "LOG ENABLE\r\n");

  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_DisableLogs(sCdrvCh040mp * const me) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "LOG DISABLE\r\n");

  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_PrintComPortsInfo(sCdrvCh040mp * const me) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "LOG COMCONFIG\r\n");

  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_PrintFirmwareVersion(sCdrvCh040mp * const me) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "LOG VERSION\r\n");

  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_PrintUserConfigs(sCdrvCh040mp * const me) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "LOG USRCONFIG\r\n");

  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @param freq 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_PrintDataOnTime(sCdrvCh040mp * const me, eCdrvCh040mp_Frequency freq) {

  return CH040MP_INIT_ERROR;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_PrintDataOnMark(sCdrvCh040mp * const me) {

  return CH040MP_INIT_ERROR;
}

/**
 * @brief 
 * 
 * @param me 
 * @param com 
 * @param baudrate 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_SerialConfig(sCdrvCh040mp * const me, eCdrvCh040mp_Com com, eCdrvCh040mp_SerialBaudrate baudrate) {
  
  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "SERIALCONFIG COM%u %d\r\n", com, baudrate);

  return CH040MP_OK;
}


uint8_t fCdrvCh040mp_FactoryReset(sCdrvCh040mp * const me) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "FRESET\r\n");

  return CH040MP_OK;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCh040mp_UnlogAll(sCdrvCh040mp * const me) {

  if(!me->_init) {
    return CH040MP_INIT_ERROR;
  }

  me->TxFrameSize = snprintf((char*)me->TxBuffer, me->TxBufferSize, "UNLOGALL\r\n");

  return CH040MP_OK;
}

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Private Functions #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/

/**
 * @brief 
 * 
 * @param data 
 * @param size 
 * @param initVal 
 * @return uint16_t 
 */
static uint16_t fCalcCrc(uint8_t *data, uint16_t size, uint16_t initVal) {

  uint32_t crc = initVal;

  for(int i = 0; i < size; i++) {
    
    uint32_t byte = data[i];

    crc ^= byte << 8;

    for(int j = 0; j < 8; j++) {

      uint32_t tmp = crc << 1;

      if(crc & 0x8000) {
        tmp ^= 0x1021;
      }

      crc = tmp;
    }
  }

  return crc;
}


/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
