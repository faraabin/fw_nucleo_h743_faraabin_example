
#ifndef __cg_VarType_3_types_H
#define __cg_VarType_3_types_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
 State1 = 1,
 State2 = 2,
 State3 = 3,
} VarType_3;

typedef struct {
 uint8_t Type;
 VarType_3 Value;
 VarType_3 ShodowValue;
 VarType_3 Max;
 VarType_3 *pMax;
 VarType_3 Min;
 VarType_3 *pMin;
} sSmartData_VarType_3;

bool fSmartData_IsValidate_VarType_3(sSmartData_VarType_3 *data, VarType_3 *value);
bool fSmartData_Write_VarType_3(sSmartData_VarType_3 *data, VarType_3 *value);
bool fSmartData_Read_VarType_3(sSmartData_VarType_3 *data, VarType_3 *value);

#ifdef __cplusplus
}
#endif

#endif
