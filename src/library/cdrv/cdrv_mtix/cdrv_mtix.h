/**
******************************************************************************
* @file           : cdrv_mti7.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_mti7_H
#define __cdrv_mti7_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\chrono\me_chrono.h"

#include "xbus\mtssp.h"

#include "hal\phal\intf\me_hal_spi_intf.h"
#include "hal\phal\intf\me_hal_serial_intf.h"
#include "hal\phal\intf\me_hal_gpio_intf.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum
{
	eOP_ProtocolInfo = 0x01,
	eOP_ConfigureProtocol = 0x02,
	eOP_ControlPipe = 0x03,
	eOP_PipeStatus = 0x04,
	eOP_NotificationPipe = 0x05,
	eOP_MeasurementPipe = 0x06
}eMTi1_SpiOpcode;

typedef enum
{
	eEC_PERIOD_INVALID = 0x03,
	eEC_MESSAGE_INVALID = 0x04,
	eEC_TIMER_OVERFLOW = 0x1E,
	eEC_BAUDRATE_NOT_VALID = 0x20,
	eEC_PARAM_INVALID = 0x21,
	eEC_DEVICE_ERROR = 0x28,
	eEC_DATA_OVERFLOW = 0x29,
	eEC_BUFFER_OVERFLOW = 0x2A
}eMTix_ErrorCode;

typedef struct {
	
	uint16_t accX			: 1;
	uint16_t accY			: 1;
	uint16_t accZ			: 1;
	uint16_t gyrX			: 1;
	uint16_t gyrY			: 1;
	uint16_t gyrZ			: 1;
	uint16_t magX			: 1;
	uint16_t magY			: 1;
	uint16_t magZ			: 1;
	uint16_t baro			: 1;
	uint16_t gnss			: 1;
	uint16_t battery	: 1;
	uint16_t flash		: 1;
	uint16_t button		: 1;
	uint16_t sync			: 1;
	uint16_t reserved : 1;
	
}sMTix_SelfTestDataObj;

typedef struct
{
	float X;
	float Y;
	float Z;
}sMTi1_XYZObj;

typedef struct
{
	uint8_t MeasurementSize;
	
	float Temperature;
	
	struct _utc{
		uint32_t ns;
		uint16_t Year;
		uint8_t Month;
		uint8_t Day;
		uint8_t Hour;
		uint8_t Minute;
		uint8_t Second;
		uint8_t Flags;
	}UtcTime;
	
	uint16_t PacketCounter;
	
	uint32_t SampleTimeFine;
	uint32_t SampleTimeCoarse;
	
	struct _quaternion {
		float Q0;
		float Q1;
		float Q2;
		float Q3;
	}Quaternion;
	
	struct _euler {
		float Roll;
		float Pitch;
		float Yaw;
	}Euler;
	
	struct _rotMat {
		float a;
		float b;
		float c;
		float d;
		float e;
		float f;
		float g;
		float h;
		float i;
	}RotationMatrix;
	
	uint32_t Pressure;
	
	sMTi1_XYZObj DeltaV;
	struct _deltaQ {
		float Q0;
		float Q1;
		float Q2;
		float Q3;
	}DeltaQ;
	sMTi1_XYZObj Acceleration;
	sMTi1_XYZObj FreeAcceleration;
	sMTi1_XYZObj AccelerationHR;
	
	sMTi1_XYZObj RateOfTurn;
	sMTi1_XYZObj RateOfTurnHR;
	
	//TODO: Gnss is not written yet
//	struct _gnss_pvt {
//		uint32_t itow;
//		uint16_t year;
//		uint8_t month;
//		uint8_t day;
//		uint8_t hour;
//		uint8_t min;
//		uint8_t sec;
//		uint8_t valid;
//		uint32_t tAcc;
//		int nano;
//		uint8_t fixType;
//		uint8_t flags;
//		uint8_t numSV;
//		uint8_t reserved1;
//		int lon;
//		int lat;
//		int hMSL;
//		uint32_t hAcc;
//		uint32_t vAcc;
//		int velN;
//		int velD;
//		int gSpeed;
//		int headMot;
//		uint32_t sAcc;
//		uint32_t headAcc;
//		int headVeh;
//		uint16_t gdop;
//		uint16_t pdop;
//		uint16_t tdop;
//		uint16_t vdop;
//		uint16_t hdop;
//		uint16_t ndop;
//		uint16_t edop;
//	}GnssPvt;
	
	//TODO: Complete gnss sat info
//	struct _gnss_sat_info {
//		uint32_t itow;
//		uint8_t numSvs;
//		uint8_t res1;
//		uint8_t res2;
//		uint8_t res3;
//		
//	}
	
	uint32_t GnssPvtPulse;
	
	//TODO: Raw data is not needed
//	struct _rawAccGyrMagTemp {
//		uint16_t accX;
//		uint16_t accY;
//		uint16_t accZ;
//		uint16_t gyrX;
//		uint16_t gyrY;
//		uint16_t gyrZ;
//		uint16_t magX;
//		uint16_t magY;
//		uint16_t magZ;
//		uint16_t Temp;
//	}RawAccGyrMagTemp;
	
	sMTi1_XYZObj MagneticField;
	
	uint8_t StatusByte;
	
	struct _stat{
		uint32_t SelfTest : 1;
		uint32_t FilterValid : 1;
		uint32_t GnssFix : 1;
		uint32_t NoRotUpdate : 2;
		uint32_t RepMo : 1;
		uint32_t ClockSync : 1;
		uint32_t Reserved1 : 1;
		uint32_t ClipFlagAccX : 1;
		uint32_t ClipFlagAccY : 1;
		uint32_t ClipFlagAccZ : 1;
		uint32_t ClipFlagGyrX : 1;
		uint32_t ClipFlagGyrY : 1;
		uint32_t ClipFlagGyrZ : 1;
		uint32_t ClipFlagMagX : 1;
		uint32_t ClipFlagMagY : 1;
		uint32_t ClipFlagMagZ : 1;
		uint32_t Reserved2 : 2;
		uint32_t SyncInMarker : 1;
		uint32_t SyncOutMarker : 1;
		uint32_t FilterMode : 3;
		uint32_t HaveGnssTimePulse : 1;
		uint32_t RtkStatus : 2;
		uint32_t Reserved3 : 3;
	}StatusWord;
	
	uint64_t DevId;
	
	uint16_t LocId;
	
	sMTi1_XYZObj PositionEcef;
	
	struct _latLon{
		float lat;
		float lon;
	}LatLon;
	
	float AltEllipsoid;
	
	sMTi1_XYZObj Velocity;
	
}sMTi1DataObj;

typedef struct
{
	bool _init;
	uint8_t _txData[256];
	uint8_t _rxData[256];
	TysChrono_Obj _timer;
	sMtsspIntf _mtssp;
	
	sMTi1DataObj Data;
	uint16_t SelfTestResult;
	
	TysSpi_Obj *Spi;
	uint32_t SpiTimeout_ms;
	TysGpio_Obj *Cs;
	TysGpio_Obj *Drdy;
	TysGpio_Obj *Reset;
	
	void(*reqDevIdCallback)(uint64_t devId);
	void(*reqPrdIdCallback)(uint8_t *prdId, uint8_t size);
	void(*reqHwVersionCallback)(uint8_t verMajor, uint8_t verMinor);
	void(*reqFwRevisionCallback)(uint8_t *fwRev, uint8_t size);
	void(*selfTestCallback)(sMTix_SelfTestDataObj result);
	void(*errorCallback)(uint8_t errorCode);
	void(*wakeupCallback)(void);
	void(*reqOptionFlagsCallback)(uint8_t flags);
	void(*reqConfigCallback)(uint8_t *configs, uint8_t size);
	void(*reqOutputConfigCallback)(uint8_t *configs, uint8_t size);
	void(*statusByteCallback)(uint8_t status);
	void(*statusWordCallback)(uint32_t status);
	void(*iccCommandAckCallback)(uint8_t *data, uint8_t size);
	
}sMTix_Object;

typedef struct {
	bool ActivateTemperature;
	uint16_t TemperatureUpdateRate;
	bool ActivateUtcTime;
	bool ActivatePacketCounter;
	bool ActivateSampleTimeFine;
	bool ActivateSampleTimeCoarse;
	bool ActivateOrientationQuaternion;
	bool ActivateOrientationRotationMatrix;
	bool ActivateOrientationEulerAngles;
	uint16_t OrientationUpdateRate;
	bool ActivateBaroPressure;
	uint16_t PressureUpdateRate;
	bool ActivateDeltaV;
	bool ActivateAcceleration;
	bool ActivateFreeAcceleration;
	bool ActivateAccelerationHR;
	uint16_t AccelerationUpdateRate;
	bool ActivateAltitudeEllipsoid;
	bool ActivatePositionEcef;
	bool ActivateLatLon;
	uint16_t PositionUpdateRate;
	bool ActivateGnssPvtData;
	bool ActivateGnssSatInfo;
	bool ActivateGnssPvtPulse;
	uint16_t GnssUpdateRate;
	bool ActivateRateOfTurn;
	bool ActivateDeltaQ;
	bool ActivateRateOfTurnHR;
	uint16_t AngularVelocityUpdateRate;
	bool ActivateRawAccGyrMagTemp;
	bool ActivateRawGyroTemp;
	uint16_t RawSensorUpdateRate;
	bool ActivateMagneticField;
	uint16_t MagneticFieldUpdateRate;
	bool ActivateVelocityXYZ;
	uint16_t VelocityUpdateRate;
	bool ActivateStatusByte;
	bool ActivateStatusWord;
	bool ActivateDeviceId;
	bool ActivateLocationId;
	
}sMTixOutputConfigObj;

typedef enum {
	DisableAutoStore = 0x00000001,
	DisableAutoMeasurement = 0x00000002,
	EnableBeidou = 0x00000004,
	Reserved = 0x00000008,
	EnableAhs = 0x00000010,
	EnableOrientationSmoother = 0x00000020,
	EnableConfigurableBusId = 0x00000040,
	EnableInRunCompassCalibration = 0x00000080,
	EnableConfigMessageAtStartup = 0x00000200,
	EnablePositionVelocitySmoother = 0x00000800,
	EnableContinuousZRU = 0x00001000,
	
}eMTixOptionFlagsObj;

typedef enum {
	eMTIx_RESET_SOFTWARE = 0,
	eMTIx_RESET_HARDWARE,
}eMTixResetType;

typedef struct {
	uint8_t pol : 1;
	uint8_t otype : 1;
	uint8_t nevent : 1;
	uint8_t mevent : 1;
	uint8_t reserved : 4;
}sMTixDataReadyConfig;

typedef enum {
	eMTIx_IRCC_START_REP_MOTION = 0,
	eMTIx_IRCC_STOP_REP_MOTION = 1,
	eMTIx_IRCC_STORE_ICC_PARAM = 2,
	eMTIx_IRCC_GET_REP_MOTION_STAT = 3
}eMTixInRunCompassCalibration;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvMtix_Init(sMTix_Object * const me, sMTixDataReadyConfig dataReadyConfig);
uint8_t fCdrvMtix_Reset(sMTix_Object * const me, eMTixResetType resetType);
uint8_t fCdrvMtix_IsDataReady(sMTix_Object * const me);
void fCdrvMtix_GoToConfig(sMTix_Object * const me);
void fCdrvMtix_GoToMeasurement(sMTix_Object * const me);
void fCdrvMtix_RequestDeviceId(sMTix_Object * const me);
void fCdrvMtix_RequestProductCode(sMTix_Object * const me);
void fCdrvMtix_RequestHardwareVersion(sMTix_Object * const me);
void fCdrvMtix_RequestFirmwareRevision(sMTix_Object * const me);
void fCdrvMtix_RunSelfTest(sMTix_Object * const me);
void fCdrvMtix_RequestOptionFlags(sMTix_Object * const me);
void fCdrvMtix_SetOptionFlags(sMTix_Object * const me, eMTixOptionFlagsObj setFlags, eMTixOptionFlagsObj clearFlags);
void fCdrvMtix_RestoreFactory(sMTix_Object * const me);
void fCdrvMtix_RequestConfig(sMTix_Object * const me);
void fCdrvMtix_RequestOutputConfig(sMTix_Object * const me);
void fCdrvMtix_SetOutputConfig(sMTix_Object * const me, sMTixOutputConfigObj config);
void fCdrvMtix_SetNoRotation(sMTix_Object * const me, uint16_t delay_s);
void fCdrvMtix_InRunCompassCalibration(sMTix_Object * const me, eMTixInRunCompassCalibration cmd);

void fCdrvMtix_ReadFromDevice(sMTix_Object * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_MTI7_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
