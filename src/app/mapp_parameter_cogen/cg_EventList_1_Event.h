
#ifndef __cg_EventList_1_Event_H
#define __cg_EventList_1_Event_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cg_ParameterList_1_Param.h"
#include "event.h"


typedef enum {
 eEVENT_EventList_1_Param_1_Signal = 1,
 eEVENT_EventList_1_Param_2_Signal = 2,
 eEVENT_EventList_1_Param_3_UserCode = 3,
} eEventList_1_Event;

typedef struct {
 sEventSignal_Float32 eEVENT_EventList_1_Param_1_Signal;
 sEventSignal_Float32 eEVENT_EventList_1_Param_2_Signal;
} sSignals;

typedef struct {
 VarType_1 VarType_1_Value;
 VarType_2 VarType_2_Value;
} sEvents_EventList_1_Groups;

typedef struct {
 sEvents_EventList_1_Groups eEVENT_EventList_1_Param_1_Signal;
 sEvents_EventList_1_Groups eEVENT_EventList_1_Param_2_Signal;
 sEvents_EventList_1_Groups eEVENT_EventList_1_Param_3_UserCode;
} sEvents_EventList_1_GroupData;

extern sEvent EventList_1_Events[3];
extern sEvents_EventList_1_GroupData Events_EventList_1_GroupData;
extern uint16_t Events_EventList_1_Qty;

#ifdef __cplusplus
}
#endif

#endif
