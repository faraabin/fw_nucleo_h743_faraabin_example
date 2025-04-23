/**
******************************************************************************
* @file           : cdrv_ch040mp.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_ch040mp_H
#define __cdrv_ch040mp_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

#include "driver\intf\me_hal_serial_intf.h"
#include "driver\intf\me_hal_gpio_intf.h"

/* Exported defines ----------------------------------------------------------*/
#define CH040MP_OK                    (0U)
#define CH040MP_HEADER_ERROR          (1U)
#define CH040MP_CRC_ERROR             (2U)
#define CH040MP_DATA_TAG_ERROR        (3U)
#define CH040MP_DATA_LENGTH_ERROR     (4U)
#define CH040MP_DATA_NOT_READY_ERROR  (5U)
#define CH040MP_CONFIG_ERROR          (6U)
#define CH040MP_INIT_ERROR            (7U)
#define CH040MP_TX_BUFFER_ERROR       (8U)
#define CH040MP_NULL_UART_ERROR       (9U)
#define CH040MP_GPIO_ERROR            (10U)
#define CH040MP_TIMEOUT_ERROR         (11U)

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {

  int8_t Temperature_C;
  
  float Pressure_Pa;
  
  uint32_t TimeStamp_MilliS;

  struct {

    float X;

    float Y;

    float Z;

  }Acceleration_MilliG;

  struct {

    float X;

    float Y;

    float Z;

  }AngularVelocity_DegPerS;

  struct {

    float X;

    float Y;

    float Z;

  }MagenticIntensity_MicroT;

  struct {

    float Roll;

    float Pitch;

    float Yaw;

  }EulerAngles_Deg;

  struct {

    float W;

    float X;

    float Y;

    float Z;

  }NodeQuaternion;

}sCdrvCh040mp_Data;

typedef struct {

  bool _init;

  bool _newDataAvailable;
  
  TysSerial_Obj *_uartIntf;
  TysGpio_Obj *_Sin;
  TysGpio_Obj *_Sout;

  sCdrvCh040mp_Data Data;
  
  uint8_t DevId;

  uint8_t *TxBuffer;
  uint16_t TxBufferSize;
  uint16_t TxFrameSize;

}sCdrvCh040mp;

typedef enum {
  
  eCH040MP_BAURATE_9600 = 9600,
  eCH040MP_BAURATE_115200 = 115200,
  eCH040MP_BAURATE_256000 = 256000,
  eCH040MP_BAURATE_460800 = 460800,
  eCH040MP_BAURATE_921600 = 921600

}eCdrvCh040mp_SerialBaudrate;

typedef enum {

  eCH040MP_CONFIG_6DOF = 0,
  eCH040MP_CONFIG_AHRS,
  eCH040MP_CONFIG_SET_ROLL_PITCH_ZERO,
  eCH040MP_CONFIG_RESET_ROLL_PITCH_CALIBRATION,
  eCH040MP_CONFIG_RESET_SET_YAW_ZERO,
  eCH040MP_CONFIG_SET_IMU_THRESHOLD,
  eCH040MP_CONFIG_SET_IMU_BANDWIDTH,
  eCH040MP_CONFIG_SET_IMU_RANGE,
  eCH040MP_CONFIG_SET_GYRO_BANDWIDTH,
  eCH040MP_CONFIG_SET_GYRO_RANGE,
  eCH040MP_CONFIG_SET_INCLINOMETER_RANGE,
  eCH040MP_CONFIG_SET_SYSTEM_ROTATION_COORDINATE,

}eCdrvCh040mp_ConfigMode;



typedef enum {

  eCH040MP_FREQ_1Hz = 0,
  eCH040MP_FREQ_2Hz,
  eCH040MP_FREQ_50Hz,
  eCH040MP_FREQ_100Hz,
  eCH040MP_FREQ_250Hz,
  eCH040MP_FREQ_500Hz

}eCdrvCh040mp_Frequency;

typedef enum {

  eCH040MP_COM0 = 0,
  eCH040MP_COM1

}eCdrvCh040mp_Com;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvCh040mp_Init(sCdrvCh040mp * const me, TysSerial_Obj* uartIntf, uint8_t *txBuffer, uint16_t txBufferSize);
uint8_t fCdrvCh040mp_Interpret(sCdrvCh040mp * const me, uint8_t *data, uint16_t size);
uint8_t fCdrvCh040mp_IsDataReady(sCdrvCh040mp * const me, uint32_t timeout_ms);

uint8_t fCdrvCh040mp_Reboot(sCdrvCh040mp * const me);
uint8_t fCdrvCh040mp_SaveConfig(sCdrvCh040mp * const me);
uint8_t fCdrvCh040mp_Config(sCdrvCh040mp * const me, eCdrvCh040mp_ConfigMode config, float configValue);
uint8_t fCdrvCh040mp_ConfigCoordinateSystem(sCdrvCh040mp * const me, int8_t c00, int8_t c01, int8_t c02, int8_t c10, int8_t c11, int8_t c12, int8_t c20, int8_t c21, int8_t c22);
uint8_t fCdrvCh040mp_EnableLogs(sCdrvCh040mp * const me);
uint8_t fCdrvCh040mp_DisableLogs(sCdrvCh040mp * const me);
uint8_t fCdrvCh040mp_PrintComPortsInfo(sCdrvCh040mp * const me);
uint8_t fCdrvCh040mp_PrintFirmwareVersion(sCdrvCh040mp * const me);
uint8_t fCdrvCh040mp_PrintUserConfigs(sCdrvCh040mp * const me);
uint8_t fCdrvCh040mp_PrintDataOnTime(sCdrvCh040mp * const me, eCdrvCh040mp_Frequency freq);
uint8_t fCdrvCh040mp_PrintDataOnMark(sCdrvCh040mp * const me);
uint8_t fCdrvCh040mp_SerialConfig(sCdrvCh040mp * const me, eCdrvCh040mp_Com com, eCdrvCh040mp_SerialBaudrate baudrate);
uint8_t fCdrvCh040mp_FactoryReset(sCdrvCh040mp * const me);
uint8_t fCdrvCh040mp_UnlogAll(sCdrvCh040mp * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_CH040MP_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
