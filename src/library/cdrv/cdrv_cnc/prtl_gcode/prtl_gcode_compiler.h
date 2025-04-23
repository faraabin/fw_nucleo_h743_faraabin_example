/**
 ******************************************************************************
 *  @file         prtl_gcode_compiler.h
 *  @brief        ...
 *  @author       ...
 *  @version      0.0.0.1
 *  @date         yyyy/mm/dd
 *  @copyright    COPYRIGHT(c) 2018 MicroEmbeds
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 @verbatim
 @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __prtl_gcode_compiler_H
#define __prtl_gcode_compiler_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

#include "library\faraabin\faraabin.h"
  
/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2
#define AXIS_R 3

/* Exported types (enum, struct, union,...)-----------------------------------*/
/**
  * @brief
  */
typedef struct {
	
	double Position[4];
	double MoveLength;
	double FeedRate;
	
	bool IsX;
	bool IsY;
	bool IsZ;
	bool IsR;
	                               
}sPrtlGcodeCmd;

/**
  * @brief
  */
typedef struct {
	
	bool IsBusy;
	
	int32_t D[4];
	
	bool IsPen;
	bool Pen;
	
	bool IsX;
	bool IsY;
	
	uint32_t TimeMs;
	
	double MoveLength;
	double FeedRate;
	
	uint32_t Freq[4];
	                               
}sPrtlGcodeMove;

/**
  * @brief
  */
typedef struct {
	
	double _position[4];
	uint8_t _statusCode;
	uint8_t _nextAction; 		/* The action that will be taken by the parsed line */
	uint8_t _inchedMode;   	/* 0 = millimeter mode, 1 = inches mode {G20, G21} */
	uint8_t _absoluteMode; 	/* 0 = relative motion, 1 = absolute motion {G90, G91} */
	double _feedRate;
	double _seekRate;     	/* Millimeters/second */
	
	int32_t _stepsFromStartX;
	int32_t _stepsFromStartY;
	int32_t _stepsFromStartZ;
	int32_t _stepsFromStartR;
	                               
}sPrtlGcodeStatus;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t PrtlGcode_Init(double position[4], int32_t stepFromStart[4]);
uint8_t PrtlGcode_Compile(char *gcode, sPrtlGcodeCmd *cmd);
uint8_t PrtlGcode_CreateMove(sPrtlGcodeCmd *cmd, sPrtlGcodeMove *move);

/* Extern functions ----------------------------------------------------------*/
/* Extern Object or Variable -------------------------------------------------*/
extern sPrtlGcodeStatus gc;

/**End of Group_Name
  * @}
  */

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/
