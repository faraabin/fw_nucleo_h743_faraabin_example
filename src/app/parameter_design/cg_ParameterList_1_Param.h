
#ifndef __cg_ParameterList_1_Param_H
#define __cg_ParameterList_1_Param_H

#ifdef __cplusplus
extern "C" {
#endif

#include "parameter.h"
#include "smart_data.h"
#include "cg_ParameterList_1_UserVarTypes.h"


typedef enum {
 ePARAMETER_Param_1 = 0,
 ePARAMETER_Param_2 = 1,
 ePARAMETER_Param_3 = 2,
 ePARAMETER_Param_4 = 3,
 ePARAMETER_Param_5 = 4,
 ePARAMETER_Param_6 = 5,
} eParameters;

typedef struct {
 sSmartData_Float32 Param_1;
 sSmartData_Float32 Param_2;
 sSmartData_Float32 Param_3;
 sSmartData_Float32 Param_4;
 sSmartData_Float32 Param_5;
 sSmartData_UInt16 Param_6;
} sParameters_SmartData;

extern sParameter Parameters[6];
extern sParameters_SmartData ParametersData;

#ifdef __cplusplus
}
#endif

#endif
