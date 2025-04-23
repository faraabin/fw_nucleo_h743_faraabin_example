
#ifndef __cg_ParameterList_1_UserVarTypes_H
#define __cg_ParameterList_1_UserVarTypes_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
 eVAR_TYPE_bool = 0,
 eVAR_TYPE_uint8_t = 1,
 eVAR_TYPE_int8_t = 2,
 eVAR_TYPE_uint16_t = 3,
 eVAR_TYPE_int16_t = 4,
 eVAR_TYPE_uint32_t = 5,
 eVAR_TYPE_int32_t = 6,
 eVAR_TYPE_uint64_t = 7,
 eVAR_TYPE_int64_t = 8,
 eVAR_TYPE_float32_t = 9,
 eVAR_TYPE_float64_t = 10,
} eParameterVarTypes;

#ifdef __cplusplus
}
#endif

#endif
