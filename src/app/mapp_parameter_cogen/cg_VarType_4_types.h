
#ifndef __cg_VarType_4_types_H
#define __cg_VarType_4_types_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
 S1 = 1,
 S2 = 2,
 S3 = 3,
} VarType_4;

typedef struct {
 uint8_t Type;
 VarType_4 Value;
 VarType_4 ShodowValue;
 VarType_4 Max;
 VarType_4 *pMax;
 VarType_4 Min;
 VarType_4 *pMin;
} sSmartData_VarType_4;

bool fSmartData_IsValidate_VarType_4(sSmartData_VarType_4 *data, VarType_4 *value);
bool fSmartData_Write_VarType_4(sSmartData_VarType_4 *data, VarType_4 *value);
bool fSmartData_Read_VarType_4(sSmartData_VarType_4 *data, VarType_4 *value);

#ifdef __cplusplus
}
#endif

#endif
