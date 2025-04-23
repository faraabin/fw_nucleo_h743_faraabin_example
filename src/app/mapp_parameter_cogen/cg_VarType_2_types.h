
#ifndef __cg_VarType_2_types_H
#define __cg_VarType_2_types_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
 Member_4 = 1,
 Member_5 = 2,
 Member_6 = 3,
} VarType_2;

typedef struct {
 uint8_t Type;
 VarType_2 Value;
 VarType_2 ShodowValue;
 VarType_2 Max;
 VarType_2 *pMax;
 VarType_2 Min;
 VarType_2 *pMin;
} sSmartData_VarType_2;

bool fSmartData_IsValidate_VarType_2(sSmartData_VarType_2 *data, VarType_2 *value);
bool fSmartData_Write_VarType_2(sSmartData_VarType_2 *data, VarType_2 *value);
bool fSmartData_Read_VarType_2(sSmartData_VarType_2 *data, VarType_2 *value);

#ifdef __cplusplus
}
#endif

#endif
