/**
 ******************************************************************************
 *  @file         prtl_gcode_compiler_cmd.c
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
 * DESCRIPTION:
 *
 ******************************************************************************
 * HOW TO USE:
 *
 ******************************************************************************
 @verbatim
 @endverbatim
*/

/* Includes ------------------------------------------------------------------*/
#include "prtl_gcode_compiler_cmd.h"

#include "prtl_gcode_compiler.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(void);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/*
===============================================================================
                       ##### Private Functios #####
===============================================================================*/
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(prtl_gcode_compiler, Init,
"type cmd help here") {
	
	double initPosition[4] = {0, 0, 0, 0};
	int32_t stepFromStart[4] = {0, 0, 0, 0};
	PrtlGcode_Init(initPosition, stepFromStart);
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(prtl_gcode_compiler, Compile,
"type cmd help here") {
	
	char line[200];
	sPrtlGcodeCmd cmd;
	sPrtlGcodeMove move;
	uint8_t res;
	
	meCONSOLE_GET_PAR_(1, "%s", line);
	for(int i=0; i<strlen(line); i++) {
		if(line[i] == '^') {
			line[i] = ' ';
		}
	}
	
	res = PrtlGcode_Compile(line, &cmd);
	if(res != 0) {
		
		mePRINTF_("\r\nCompile Error : %u", &res);
		
	} else {
		
		mePRINTF_("\r\v\r\nCMD");
		mePRINTF_("\r\nX:%f, Y:%f, Z:%f, R:%f",
			cmd.Position[AXIS_X], cmd.Position[AXIS_Y], cmd.Position[AXIS_R], cmd.Position[AXIS_Z]);
		mePRINTF_("\r\nFeedRate:%f, MoveLengthY:%f",
			cmd.FeedRate, cmd.MoveLength);
		
		res = PrtlGcode_CreateMove(&cmd, &move);
		if(res != 0) {
			
			mePRINTF_("\r\nConvert Error : %u", &res);

		} else {
			
			mePRINTF_("\r\v\r\nMOVE");
			mePRINTF_("\r\ndX:%i, dY:%i, dZ:%i, dR:%i",
				move.D[AXIS_X], move.D[AXIS_Y], move.D[AXIS_R], move.D[AXIS_Z]);
			mePRINTF_("\r\nfX:%u, fY:%u, fZ:%u, fR:%u",
				move.Freq[AXIS_X], move.Freq[AXIS_Y], move.Freq[AXIS_R], move.Freq[AXIS_Z]);
			mePRINTF_("\r\nTime(ms):%u", move.TimeMs);
			mePRINTF_("\r\nPen:%u", move.Pen);
			
		}
	}
	
	meCONSOLE_END_;
}

/*
===============================================================================
                       ##### Exported Function #####
===============================================================================*/
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_GROUP_(prtl_gcode_compiler,
"type cmd help here") {

	meCONSOLE_ADD_CMD_(prtl_gcode_compiler, Init, 0);
	meCONSOLE_ADD_CMD_(prtl_gcode_compiler, Compile, 0);
	
  meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/
