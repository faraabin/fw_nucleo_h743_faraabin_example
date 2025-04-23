#ifndef ADIS16470_H_
#define ADIS16470_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "library\type\me_type.h"
#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "hal\phal\intf\me_hal_spi_intf.h"

//#include "bsp_type.h"

// USER REGISTER MEMORY MAP
#define DIAG_STAT   	0x02  //Output, system error flags 
#define X_GYRO_LOW  	0x04  //Output, x-axis gyroscope, low word 
#define X_GYRO_OUT  	0x06  //Output, x-axis gyroscope, high word 
#define Y_GYRO_LOW  	0x08  //Output, y-axis gyroscope, low word 
#define Y_GYRO_OUT  	0x0A  //Output, y-axis gyroscope, high word 
#define Z_GYRO_LOW  	0x0C  //Output, z-axis gyroscope, low word 
#define Z_GYRO_OUT  	0x0E  //Output, z-axis gyroscope, high word 
#define X_ACCL_LOW  	0x10  //Output, x-axis accelerometer, low word 
#define X_ACCL_OUT  	0x12  //Output, x-axis accelerometer, high word 
#define Y_ACCL_LOW  	0x14  //Output, y-axis accelerometer, low word 
#define Y_ACCL_OUT  	0x16  //Output, y-axis accelerometer, high word 
#define Z_ACCL_LOW  	0x18  //Output, z-axis accelerometer, low word 
#define Z_ACCL_OUT  	0x1A  //Output, z-axis accelerometer, high word 
#define TEMP_OUT    	0x1C  //Output, temperature 
#define TIME_STAMP  	0x1E  //Output, time stamp
#define DATA_CNTR     0x22  //New data counter 
#define X_DELTANG_LOW	0x24  //Output, x-axis delta angle, low word 
#define X_DELTANG_OUT	0x26  //Output, x-axis delta angle, high word 
#define Y_DELTANG_LOW	0x28  //Output, y-axis delta angle, low word 
#define Y_DELTANG_OUT	0x2A  //Output, y-axis delta angle, high word 
#define Z_DELTANG_LOW	0x2C  //Output, z-axis delta angle, low word 
#define Z_DELTANG_OUT	0x2E  //Output, z-axis delta angle, high word 
#define X_DELTVEL_LOW	0x30  //Output, x-axis delta velocity, low word 
#define X_DELTVEL_OUT	0x32  //Output, x-axis delta velocity, high word 
#define Y_DELTVEL_LOW	0x34  //Output, y-axis delta velocity, low word 
#define Y_DELTVEL_OUT	0x36  //Output, y-axis delta velocity, high word 
#define Z_DELTVEL_LOW	0x38  //Output, z-axis delta velocity, low word 
#define Z_DELTVEL_OUT	0x3A  //Output, z-axis delta velocity, high word 
#define XG_BIAS_LOW		0x40  //Calibration, offset, gyroscope, x-axis, low word 
#define XG_BIAS_HIGH	0x42  //Calibration, offset, gyroscope, x-axis, high word 
#define YG_BIAS_LOW		0x44  //Calibration, offset, gyroscope, y-axis, low word 
#define YG_BIAS_HIGH	0x46  //Calibration, offset, gyroscope, y-axis, high word 
#define ZG_BIAS_LOW		0x48  //Calibration, offset, gyroscope, z-axis, low word
#define ZG_BIAS_HIGH	0x4A  //Calibration, offset, gyroscope, z-axis, high word 
#define XA_BIAS_LOW		0x4C  //Calibration, offset, accelerometer, x-axis, low word 
#define XA_BIAS_HIGH	0x4E  //Calibration, offset, accelerometer, x-axis, high word 
#define YA_BIAS_LOW		0x50  //Calibration, offset, accelerometer, y-axis, low word 
#define YA_BIAS_HIGH	0x52  //Calibration, offset, accelerometer, y-axis, high word 
#define ZA_BIAS_LOW		0x54  //Calibration, offset, accelerometer, z-axis, low word 
#define ZA_BIAS_HIGH	0x56  //Calibration, offset, accelerometer, z-axis, high word 
#define FILT_CTRL    	0x5C  //Control, Bartlett window FIR filter  Reserved 
#define MSC_CTRL    	0x60  //Control, input/output and other miscellaneous options 
#define UP_SCALE    	0x62  //Control, scale factor for input clock, pulse per second (PPS) mode 
#define DEC_RATE    	0x64  //Control, decimation filter (output data rate) 
#define NULL_CFG    	0x66  //Control, bias estimation period 
#define GLOB_CMD    	0x68  //Control, global commands 
#define FIRM_REV    	0x6C  //Identification, firmware revision 
#define FIRM_DM    		0x6E  //Identification, date code, day and month 
#define FIRM_Y    		0x70  //Identification, date code, year 
#define PROD_ID    		0x72  //Identification, part number  
#define SERIAL_NUM    0x74  //Identification, serial number 
#define USER_SCR1    	0x76  //User scratch register 1 
#define USER_SCR2    	0x78  //User scratch register 2 
#define USER_SCR3    	0x7A  //User scratch register 3 
#define FLSHCNT_LOW   0x7C  //Output, flash memory write cycle counter, lower word 
#define FLSHCNT_HIGH  0x7E  //Output, flash memory write cycle counter, upper word 

typedef struct {
	
	TysGpio_Obj *cs;
	
	TysSpi_Obj *spi;
	
	struct {
		float x;
		float y;
		float z;
	} accel;
	
	struct {
		float x;
		float y;
		float z;
	} gyro;
	
	float temp;
	
	uint8_t burstByte[21];
	
	uint16_t burstWord[21];
	
}sAdis16470_Obj;

uint8_t fAdis16470_Init(sAdis16470_Obj *me);
uint8_t fAdis16470_Update(sAdis16470_Obj *me);

#ifdef __cplusplus
}
#endif

#endif
