/**
 ******************************************************************************
 *  @file         prtl_gcode_compiler.c
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
#include "prtl_gcode_compiler.h"

#include "field\app_field.h"

#include <math.h>
#include <stdlib.h>

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define GCSTATUS_OK												0
#define GCSTATUS_BAD_NUMBER_FORMAT				1
#define GCSTATUS_EXPECTED_COMMAND_LETTER 	2
#define GCSTATUS_UNSUPPORTED_STATEMENT		3
#define GCSTATUS_FLOATING_POINT_ERROR			4
#define GCSTATUS_UNSUPPORTED_PARAM				5
#define GCSTATUS_UNSOPORTED_FEEDRATE			6
#define GCSTATUS_TABLE_SIZE_OVER_X				7 
#define GCSTATUS_TABLE_SIZE_OVER_Y				8 
#define GCSTATUS_TABLE_SIZE_OVER_Z				9 
#define GCSTATUS_CANCELED									101

#define NEXT_ACTION_DEFAULT 				0
#define NEXT_ACTION_DWELL_G4 				1
#define NEXT_ACTION_GO_HOME_G28 		2
#define NEXT_ACTION_RESET_XYZ_G92 	3
#define NEXT_ACTION_STOP 						4
#define NEXT_ACTION_SEEK_G0 				5 // G0 
#define NEXT_ACTION_LINEAR_G1 			6 // G1
#define NEXT_ACTION_EXTRUDER_STOP 	7
#define NEXT_ACTION_EXTRUDER_ON 		8
#define NEXT_ACTION_EXTRUDER_FAST_T 9
#define NEXT_ACTION_EXTRUDER_WAIT_T 10
#define NEXT_ACTION_CW_ARC 					11
#define NEXT_ACTION_CCW_ARC 				12

#define MM_PER_INCH (25.4)

#define SM_TOO_SHORT_SEGMENT_MM	0.015

#define SM_DEFAULT_FEED_RATE 50		// G1
#define SM_DEFAULT_SEEK_RATE 1500	// G0 millimeters per minute

#define SM_X_MAX_STEPS_PER_SEC (SM_X_MAX_FEEDRATE * SM_X_STEPS_PER_MM / 60)
#define SM_Y_MAX_STEPS_PER_SEC (SM_Y_MAX_FEEDRATE * SM_Y_STEPS_PER_MM / 60)
#define SM_Z_MAX_STEPS_PER_SEC (SM_Z_MAX_FEEDRATE * SM_Z_STEPS_PER_MM / 60)
#define SM_R_MAX_STEPS_PER_SEC (SM_R_MAX_FEEDRATE * SM_R_STEPS_PER_MM / 60)

#define SM_X_STEPS_PER_MM	(SM_X_STEPS_PER_360 / AXIS_X_MM_PER_360)
#define SM_Y_STEPS_PER_MM	(SM_Y_STEPS_PER_360 / AXIS_Y_MM_PER_360)
#define SM_Z_STEPS_PER_MM	(SM_Y_STEPS_PER_360 / AXIS_Y_MM_PER_360)
#define SM_R_STEPS_PER_MM	(SM_R_STEPS_PER_360 / AXIS_R_MM_PER_360)

#define K_FRQ 10

#define AXIS_X_MAX_FEED_RATE (SM_X_MAX_STEPS_PER_SEC * K_FRQ)
#define AXIS_Y_MAX_FEED_RATE (SM_Y_MAX_STEPS_PER_SEC * K_FRQ)
#define AXIS_Z_MAX_FEED_RATE (SM_Z_MAX_STEPS_PER_SEC * K_FRQ)
#define AXIS_R_MAX_FEED_RATE (SM_R_MAX_STEPS_PER_SEC * K_FRQ)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static int next_statement(char *letter, double *double_ptr, char *line, int *char_counter);
static int read_double(char *line, int *char_counter, double *double_ptr);
static double strtod_M(const char *str, char **endptr);
static double to_millimeters(double value);
	
/* Variables -----------------------------------------------------------------*/
sPrtlGcodeStatus gc;

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
uint8_t PrtlGcode_Init(double position[4], int32_t stepFromStart[4]) {
	
	memset(&gc, 0, sizeof(gc));
	gc._feedRate = SM_DEFAULT_FEED_RATE;
	gc._seekRate = SM_DEFAULT_SEEK_RATE;
	gc._nextAction = NEXT_ACTION_DEFAULT;
	gc._inchedMode = false;
	gc._absoluteMode = true;
	
	gc._position[0] = position[0];
	gc._position[1] = position[1];
	gc._position[2] = position[2];
	gc._position[3] = position[3];
	
	gc._stepsFromStartX = stepFromStart[0];
	gc._stepsFromStartY = stepFromStart[1];
	gc._stepsFromStartZ = stepFromStart[2];
	gc._stepsFromStartR = stepFromStart[3];
	
	return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t PrtlGcode_Compile(char *line, sPrtlGcodeCmd *cmd) {
		
	double oldPosition[4];
	double feedRate;
	int charCounter = 0;
	char letter;
	double value, dx, dy, dz, dr, moveLength;//, offset[4];
	//int pauseValue = 0;
	
	cmd->IsX = false;
	cmd->IsY = false;
	cmd->IsZ = false;
	cmd->IsR = false;
				
	gc._statusCode = GCSTATUS_OK;
  
  if(
		line[0] == ';' ||
		line[0] == '(' ||
		line[0] == '%') {
			
		return 0;
	}

	// Pass 1: Commands
	while (next_statement(&letter, &value, line, &charCounter)) {
		
		int int_value = (int)value;
		
		switch (letter) {
			
			case 'N':{
				break;
			}
			
			case 'G': {
				
				switch (int_value) {
					
					case 0: {gc._nextAction = NEXT_ACTION_SEEK_G0; break;}
					case 1: {gc._nextAction = NEXT_ACTION_LINEAR_G1; break;}
					case 2: {gc._nextAction = NEXT_ACTION_CW_ARC; break;}
					case 3: {gc._nextAction = NEXT_ACTION_CCW_ARC; break;}
					case 4: {gc._nextAction = NEXT_ACTION_DWELL_G4; break;}
					case 20: {gc._inchedMode = true; break;}
					case 21: {gc._inchedMode = false; break;}
					
					case 30:
					case 28: {
						gc._nextAction = NEXT_ACTION_GO_HOME_G28;
						break;
					}
					
					case 90: {gc._absoluteMode = true; break;}
					case 91: {gc._absoluteMode = false; break;}
					case 92: {gc._nextAction = NEXT_ACTION_RESET_XYZ_G92; break;}
					
					case 64:
					case 40:
					case 17:	
					case 94:	// Feedrate per minute
					case 98:	// Feedrate per minute (group type A)
					case 97:	// Constant spindle speed M T Takes an S address integer, which is interpreted as rev/min (rpm). The default speed mode per system parameter if no mode is programmed. 
					case 49:	// Tool length offset compensation cancel
					case 80: {	// Cancel canned cycle {
						break;
					}
					
					default: { 
						gc._statusCode = GCSTATUS_UNSUPPORTED_STATEMENT;
						return gc._statusCode;
					}
				}
				break;
			}
		
			case 'M': {
				
				switch (int_value) {
					
					case 112: // Emergency Stop 
					case 0:
					case 1:
					case 2:
					case 30:
					case 60: {
						gc._nextAction = NEXT_ACTION_STOP;
						break;
					}
					
					case 23: // Thread gradual pullout ON
					case 24: // Thread gradual pullout OFF
					case 52: // Unload Last tool from spindle
					case 49: // Feedrate override NOT allowed
					case 48: // Feedrate override allowed
					case 8:  // Coolant on
					case 9:  // Coolant off
					case 105: // M105: Get Extruder Temperature Example: M105 Request the temperature of the current extruder and the build base in degrees Celsius. The temperatures are returned to the host computer. For example, the line sent to the host in response to this command looks like 
					case 106: // M106: Fan On Example: M106 S127 Turn on the cooling fan at half speed. Optional parameter 'S' declares the PWM value (0-255) 
					case 107: // Fan Off 
					case 108: // M108: Set Extruder Speed  Sets speed of extruder motor. (Deprecated in current firmware, see M113) 
					case 110: // Set Current Line Number 
					case 113: // Set Extruder PWM 
					case 140: // Bed Temperature (Fast) Example: M140 S55 Set the temperature of the build bed to 55oC 
					case 141: //Chamber Temperature (Fast) Example: M141 S30 Set the temperature of the chamber to 30oC
					case 142: // Holding Pressure Example: M142 S1 Set the holding pressure of the bed to 1 bar. 
					case 6: {
						return gc._statusCode;
					}
					
					default: {
						gc._statusCode = GCSTATUS_UNSUPPORTED_STATEMENT;
						return gc._statusCode;
					}
				}
				break;
			}
		}
		
		if(gc._statusCode != GCSTATUS_OK) {
			return(gc._statusCode);
		}
	}
	
	if (gc._statusCode != GCSTATUS_OK) {
		return(gc._statusCode);
	}

	charCounter = 0;
	oldPosition[AXIS_X] = gc._position[AXIS_X];
	oldPosition[AXIS_Y] = gc._position[AXIS_Y];
	oldPosition[AXIS_Z] = gc._position[AXIS_Z];
	oldPosition[AXIS_R] = gc._position[AXIS_R];
	//offset[0] = offset[1] = offset[2] = offset[3] = 0;

	// Pass 2: Parameters
	while(next_statement(&letter, &value, line, &charCounter)) {
		
		double unit_millimeters_value = to_millimeters(value);
		
		switch (letter) {
			
			case 'F': {
				if (gc._nextAction == NEXT_ACTION_SEEK_G0) {
					gc._seekRate = unit_millimeters_value;
				} else {
					gc._feedRate = unit_millimeters_value; // millimeters pr min
				}
				break;
			}
			
			case 'P': {/*pauseValue = (int)value;*/ break;}
			
			case 'X': {	
				if(gc._absoluteMode) {
					gc._position[letter - 'X'] = unit_millimeters_value;
				} else {
					gc._position[letter - 'X'] += unit_millimeters_value;
				}
				cmd->IsX = true;
				break;
			}
			
			case 'Y': {	
				if(gc._absoluteMode) {
					gc._position[letter - 'X'] = unit_millimeters_value;
				} else {
					gc._position[letter - 'X'] += unit_millimeters_value;
				}
				cmd->IsY = true;
				break;
			}
			
			case 'Z': {	
				if(gc._absoluteMode) {
					gc._position[letter - 'X'] = unit_millimeters_value;
				} else {
					gc._position[letter - 'X'] += unit_millimeters_value;
				}
				cmd->IsZ = true;
				break;
			}
				
			case 'A':
			case 'B': {
				if(gc._absoluteMode) {
					gc._position[AXIS_R] = unit_millimeters_value;
				} else {
					gc._position[AXIS_R] += unit_millimeters_value;
				}
				cmd->IsR = true;
				break;
			}
				
			case 'I':
			case 'J':
			case 'K': {
				//offset[letter - 'I'] = unit_millimeters_value;
				break;
			}
			
//			case 'R': {
//				radius = unit_millimeters_value;
//				radius_mode = true;
//				break;
//			}
			
			case 'G':
			case 'N':
			case 'M': {
				break;
			}
			
			default: {
				gc._statusCode = GCSTATUS_UNSUPPORTED_PARAM;
				return gc._statusCode;
			}
		}
	}
  
	if (gc._statusCode != GCSTATUS_OK) {
		return gc._statusCode;
	}
	
	if(gc._nextAction == NEXT_ACTION_GO_HOME_G28) {
		gc._position[0] = 0;
		gc._position[1] = 0;
		gc._position[2] = 0;
		gc._position[3] = 0;
	}
	
	dx = gc._position[AXIS_X] - oldPosition[AXIS_X];
	dy = gc._position[AXIS_Y] - oldPosition[AXIS_Y];
	dz = gc._position[AXIS_Z] - oldPosition[AXIS_Z];
  dr = gc._position[AXIS_R] - oldPosition[AXIS_R];

	if (fabs(dx) < SM_TOO_SHORT_SEGMENT_MM) { dx = 0.0; gc._position[AXIS_X] = oldPosition[AXIS_X]; }
	if (fabs(dy) < SM_TOO_SHORT_SEGMENT_MM) { dy = 0.0; gc._position[AXIS_Y] = oldPosition[AXIS_Y]; }
	if (fabs(dz) < SM_TOO_SHORT_SEGMENT_MM) { dz = 0.0; gc._position[AXIS_Z] = oldPosition[AXIS_Z]; }
  if (fabs(dr) < SM_TOO_SHORT_SEGMENT_MM) { dr = 0.0; gc._position[AXIS_R] = oldPosition[AXIS_R]; }

	moveLength = sqrt(dx * dx + dy * dy + dz * dz + dr * dr);
  feedRate = (gc._nextAction == NEXT_ACTION_SEEK_G0) ? gc._seekRate : gc._feedRate;
	
	if (
		(gc._nextAction == NEXT_ACTION_SEEK_G0 ||
		gc._nextAction == NEXT_ACTION_LINEAR_G1 ||
		gc._nextAction == NEXT_ACTION_CW_ARC ||
		gc._nextAction == NEXT_ACTION_CCW_ARC) && 
		(moveLength < SM_TOO_SHORT_SEGMENT_MM)) {
			
		// too short move.. Ignore
		gc._position[AXIS_X] = oldPosition[AXIS_X];
		gc._position[AXIS_Y] = oldPosition[AXIS_Y];
		gc._position[AXIS_Z] = oldPosition[AXIS_Z];
    gc._position[AXIS_R] = oldPosition[AXIS_R];
			
		cmd->Position[AXIS_X] = gc._position[AXIS_X];
		cmd->Position[AXIS_Y] = gc._position[AXIS_Y];
		cmd->Position[AXIS_Z] = gc._position[AXIS_Z];
		cmd->Position[AXIS_R] = gc._position[AXIS_R];
		cmd->FeedRate = feedRate;
		cmd->MoveLength = moveLength;
			
		return(gc._statusCode);
	}

	// Perform any physical actions
	switch (gc._nextAction) {
		
		case NEXT_ACTION_RESET_XYZ_G92: {
			gc._position[0] = gc._position[1] = gc._position[2] = 0;
			break;
		}
		
		case NEXT_ACTION_STOP: {
			//cnc_end();
			break;
		}
		
		case NEXT_ACTION_GO_HOME_G28:
		case NEXT_ACTION_SEEK_G0:
		case NEXT_ACTION_LINEAR_G1: {
			
//			cmd->Position[AXIS_X] = gc._position[AXIS_X];
//			cmd->Position[AXIS_Y] = gc._position[AXIS_Y];
//			cmd->Position[AXIS_Z] = gc._position[AXIS_Z];
//			cmd->Position[AXIS_R] = gc._position[AXIS_R];
//			cmd->FeedRate = feedRate;
//			cmd->MoveLength = moveLength;
			
			break;
		}		
	}
	
	cmd->Position[AXIS_X] = gc._position[AXIS_X];
	cmd->Position[AXIS_Y] = gc._position[AXIS_Y];
	cmd->Position[AXIS_Z] = gc._position[AXIS_Z];
	cmd->Position[AXIS_R] = gc._position[AXIS_R];
	cmd->FeedRate = feedRate;
	cmd->MoveLength = moveLength;
	
	return(gc._statusCode);
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t PrtlGcode_CreateMove(sPrtlGcodeCmd *cmd, sPrtlGcodeMove *move) {
	
	int32_t newX = lround(cmd->Position[AXIS_X] * SM_X_STEPS_PER_360 / AXIS_X_MM_PER_360);
	int32_t newY = lround(cmd->Position[AXIS_Y] * SM_Y_STEPS_PER_360 / AXIS_Y_MM_PER_360);
	int32_t newZ = lround(cmd->Position[AXIS_Z] * SM_Z_STEPS_PER_360 / AXIS_Z_MM_PER_360);
    //int32_t newR = lround(r * SM_R_STEPS_PER_360 / AXIS_R_MM_PER_360);
	int32_t newR = lround(cmd->Position[AXIS_R] * 18.0f * 200.0f / 360.0f);
  
	int32_t dx = newX - gc._stepsFromStartX;
	int32_t dy = newY - gc._stepsFromStartY;
	int32_t dz = newZ - gc._stepsFromStartZ;
  int32_t dr = newR - gc._stepsFromStartR;

	gc._stepsFromStartX = newX;
	gc._stepsFromStartY = newY;
	gc._stepsFromStartZ = newZ;
  gc._stepsFromStartR = newR;

	uint32_t timeMs = (uint32_t)(cmd->MoveLength * (60000.0 / cmd->FeedRate));

	if ((dx != 0 || dy != 0 || dz != 0 || dr != 0) && timeMs == 0) {
		timeMs = 1;
	}
	
	move->D[AXIS_X] = dx;
	move->D[AXIS_Y] = dy;
	move->D[AXIS_Z] = dz;
	move->D[AXIS_R] = dr;
	move->TimeMs = timeMs;
	move->MoveLength = cmd->MoveLength;
	move->FeedRate = cmd->FeedRate;
	
	move->IsPen = cmd->IsZ;
	move->Pen = (cmd->Position[AXIS_Z] < 0.5f);
	
	move->IsX = cmd->IsX;
	move->IsY = cmd->IsY;
	
	uint32_t freq[4];
	
	while (timeMs > 0) {
		
		freq[AXIS_R] = (labs(move->D[AXIS_R])) * 1000L * K_FRQ / timeMs;
		if(freq[AXIS_R] > AXIS_R_MAX_FEED_RATE) {
			timeMs = (uint64_t)labs(move->D[AXIS_R]) * (1000L * K_FRQ) / (AXIS_R_MAX_FEED_RATE + 1);
			continue;
		}
		
		freq[AXIS_Z] = (labs(move->D[AXIS_Z])) * 1000L * K_FRQ / timeMs;
		if(freq[AXIS_Z] > AXIS_Z_MAX_FEED_RATE) {
			timeMs = (uint64_t)labs(move->D[AXIS_Z]) * (1000L * K_FRQ) / (AXIS_Z_MAX_FEED_RATE + 1);
			continue;
		}
		
		freq[AXIS_Y] = (labs(move->D[AXIS_Y])) * 1000L * K_FRQ / timeMs;
		if(freq[AXIS_Y] > AXIS_Y_MAX_FEED_RATE) {
			timeMs = (uint64_t)labs(move->D[AXIS_Y]) * (1000L * K_FRQ) / (AXIS_Y_MAX_FEED_RATE + 1);
			continue;
		}
		
		freq[AXIS_X] = (labs(move->D[AXIS_X])) * 1000L * K_FRQ / timeMs;
		if(freq[AXIS_X] > AXIS_X_MAX_FEED_RATE) {
			timeMs = (uint64_t)labs(move->D[AXIS_X]) * (1000L * K_FRQ) / (AXIS_X_MAX_FEED_RATE + 1);
			continue;
		}
    
		break;
	}
	
  uint32_t f = 0;
	uint32_t i, n = 0;

	for(i = 0; i < 4; i++) {
		if(freq[i] > f) {
			f = freq[i];
			n = i;
		}
	}
	
	if(labs(move->D[n]) > 10) {
		for(i = 0; i < 4; i++)
			if(i != n) {
				freq[i] = (uint32_t)(((uint64_t)f * (uint64_t)labs(move->D[i])) / labs(move->D[n])) + 1; //+1 for debug
			}
	}
	
	move->Freq[AXIS_X] = freq[AXIS_X];
	move->Freq[AXIS_Y] = freq[AXIS_Y];
	move->Freq[AXIS_Z] = freq[AXIS_Z];
	move->Freq[AXIS_R] = freq[AXIS_R];
	
	move->IsBusy = true;
	
	return 0;
}

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
static int next_statement(char *letter, double *double_ptr, char *line, int *char_counter) {
	
	while(line[*char_counter] == ' ') {
		(*char_counter)++;
	}

	if(
		line[*char_counter] == 0 ||
		line[*char_counter] == ';' ||
		line[*char_counter] == '\n' ||
		line[*char_counter] == '\r') {
			return false;
	}
		
	*letter = line[*char_counter];
	if ((*letter < 'A') || (*letter > 'Z')) {
		gc._statusCode = GCSTATUS_EXPECTED_COMMAND_LETTER;
		return false;
	}
	
	(*char_counter)++;
	return read_double(line, char_counter, double_ptr);
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static int read_double(char *line, int *char_counter, double *double_ptr) {
	
	char *start = line + *char_counter;
	char *end;

	*double_ptr = strtod_M(start, &end);
	if (end == start) {
		gc._statusCode = GCSTATUS_BAD_NUMBER_FORMAT;
		return false;
	}
	
	*char_counter = (int)(end - line);
	return true;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static double strtod_M(const char *str, char **endptr) {
	
	double number = 0.0;
	double div = 0.0;
	bool negative = false;
	bool plus = false;
	bool skip = true;
	char c;
	while ((c = *str) != 0)
	{
		if (c == '+')
		{
			if (skip && !plus)
			{
				plus = true;
				skip = false;
			}
			else
			{
				break;
			}
		}
		else if (skip && !negative && c == '-')
		{
			if (skip && !negative)
			{
				negative = true;
				skip = false;
			}
			else
			{
				break;
			}
		}
		else if (c == '.')
		{
			if (div == 0.0)
				div = 1.0;
			else
			{
				break;
			}
		}
		else if (c >= '0' && c <= '9')
		{
			skip = false;
			if (div == 0.0)
			{
				number = number * 10.0 + (double)(c - '0');
			}
			else
			{
				div *= 10.0;
				number += ((double)(c - '0') / div);
			}
		}
		else if (!skip)
		{
			break;
		}
		str++;
	}

	if (negative) 
	{
		number = -number;
	}
	
	if(endptr != NULL) {
		*endptr = (char *)str;
	}
	
	return number;
}

static double to_millimeters(double value) {
	
	return (gc._inchedMode ? (value * MM_PER_INCH) : value);
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/
