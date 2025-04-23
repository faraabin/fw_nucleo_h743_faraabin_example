
#ifndef __cg_ParameterList_1_Param_H
#define __cg_ParameterList_1_Param_H

#ifdef __cplusplus
extern "C" {
#endif

//Include required file's
#include "parameter.h"
#include "smart_data.h"

#include "cg_ParameterList_1_UserVarTypes.h"

#include "cg_VarType_1_types.h"
#include "cg_VarType_2_types.h"
#include "cg_VarType_3_types.h"
#include "cg_VarType_4_types.h"

//Define types
typedef enum {
 ePARAMETER_ID_Param_1 = 0,
 ePARAMETER_ID_Param_2 = 1,
 ePARAMETER_ID_Param_3 = 2,
 ePARAMETER_ID_Param_4 = 3,
 ePARAMETER_ID_Param_5 = 4,
 ePARAMETER_ID_Param_6 = 5,
 ePARAMETER_ID_Param_7 = 6,
 ePARAMETER_ID_Param_8 = 7,
 ePARAMETER_ID_Param_9 = 8,
 ePARAMETER_ID_Param_10 = 9,
} eParametersId;

typedef struct {
 sSmartData_Float32 Param_1;
 sSmartData_Float32 Param_2;
 sSmartData_Float32 Param_3;
 sSmartData_Float32 Param_4;
 sSmartData_Float32 Param_5;
 sSmartData_Float32 Param_6;
 sSmartData_Float32 Param_7;
 sSmartData_Float32 Param_8;
 sSmartData_Float32 Param_9;
 sSmartData_Float32 Param_10;
} sParameters_SmartData;

typedef struct {
 VarType_1 VarType_1_Value;
 VarType_2 VarType_2_Value;
} sParameterGroups;

typedef struct {
 sParameterGroups Param_1;
 sParameterGroups Param_2;
 sParameterGroups Param_3;
 sParameterGroups Param_4;
 sParameterGroups Param_5;
 sParameterGroups Param_6;
 sParameterGroups Param_7;
 sParameterGroups Param_8;
 sParameterGroups Param_9;
 sParameterGroups Param_10;
} sParameters_GroupData;

//Extern created variables
extern sParameter Parameters[10];
extern sParameters_SmartData ParametersSmartData;
extern sParameters_GroupData ParametersGroupData;
extern uint16_t ParametersQty;

#ifdef __cplusplus
}
#endif

#endif
