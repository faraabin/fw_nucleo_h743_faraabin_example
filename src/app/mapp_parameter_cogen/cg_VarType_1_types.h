
#ifndef __cg_VarType_1_types_H
#define __cg_VarType_1_types_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
 Member_1 = 1,
 Member_2 = 2,
 Member_3 = 3,
} VarType_1;

typedef struct {
 uint8_t Type;
 VarType_1 Value;
 VarType_1 ShodowValue;
 VarType_1 Max;
 VarType_1 *pMax;
 VarType_1 Min;
 VarType_1 *pMin;
} sSmartData_VarType_1;

bool fSmartData_IsValidate_VarType_1(sSmartData_VarType_1 *data, VarType_1 *value);
bool fSmartData_Write_VarType_1(sSmartData_VarType_1 *data, VarType_1 *value);
bool fSmartData_Read_VarType_1(sSmartData_VarType_1 *data, VarType_1 *value);

#ifdef __cplusplus
}
#endif

#endif
