
#include "cg_EventList_1_Event.h"
#include "cg_EventList_1_ExtFuncion.h"

sSignals Signals = {
{
  .pValue = &(ParametersSmartData.Param_1.Value),
  .Max = 0,
  .pfMax = NULL,//&(ParametersSmartData.Param_3.Value),
  .Min = 0,
  .pfMin = NULL,
  .Hysteresis = 3,
  .pfHysteresis = NULL,
 },
{
  .pValue = &(ParametersSmartData.Param_2.Value),
  .Max = 9,
  .pfMax = NULL,
  .Min = 0,
  .pfMin = NULL,//&(ParametersSmartData.Param_4.Value),
  .Hysteresis = 4,
  .pfHysteresis = NULL,
 }
};
sEvent EventList_1_Events[3] = {
{
  .Name = "eEVENT_EventList_1_Param_1_Signal",
  .Id = 1,
  .Enable = true,
  .pfExternalEnableFunction = feEVENT_EventList_1_Param_1_Signal_ExternalEnableFunction,
  .Type = eEVENT_TYPE_SIGNAL,
  .SignalDataType = ePRIMITIVE_DATA_TYPE_FLOAT32,
  .pSignal = &(Signals.eEVENT_EventList_1_Param_1_Signal),
  .SignalMode = eEVENT_SIGNAL_MODE_GREATHER,
  .pfUserFunction = NULL,
  .DebounceEnable = true,
  .DebounceSetTimeMs = 0,
  .pfDebounceSetTimeMs = NULL,//(uint32_t*)&(ParametersSmartData.Param_1.Value),
  .DebounceResetTimeMs = 8,
  .pfDebounceResetTimeMs = NULL,
  .CounterEnable = true,
  .CounterThreshold = 56,
  .pfCounterThreshold = NULL,
  .pDescription = "ewew\
ewrew\
ewr",
  .pGroups = &(Events_EventList_1_GroupData.eEVENT_EventList_1_Param_1_Signal),
  .StateFlags = (1 << State1) | (1 << State2) | (1 << State3),
  .ResetSourceFlags = (1 << S1),
 },
{
  .Name = "eEVENT_EventList_1_Param_2_Signal",
  .Id = 2,
  .Enable = true,
  .pfExternalEnableFunction = NULL,
  .Type = eEVENT_TYPE_SIGNAL,
  .SignalDataType = ePRIMITIVE_DATA_TYPE_FLOAT32,
  .pSignal = &(Signals.eEVENT_EventList_1_Param_2_Signal),
  .SignalMode = eEVENT_SIGNAL_MODE_SMALLER,
  .pfUserFunction = NULL,
  .DebounceEnable = true,
  .DebounceSetTimeMs = 7,
  .pfDebounceSetTimeMs = NULL,
  .DebounceResetTimeMs = 0,
  .pfDebounceResetTimeMs = NULL,//(uint32_t*)&(ParametersSmartData.Param_2.Value),
  .CounterEnable = false,
  .CounterThreshold = 6,
  .pfCounterThreshold = NULL,
  .pDescription = "ff",
  .pGroups = &(Events_EventList_1_GroupData.eEVENT_EventList_1_Param_2_Signal),
  .StateFlags = (1 << State2),
  .ResetSourceFlags = (1 << S1),
 },
{
  .Name = "eEVENT_EventList_1_Param_3_UserCode",
  .Id = 3,
  .Enable = true,
  .pfExternalEnableFunction = feEVENT_EventList_1_Param_3_UserCode_ExternalEnableFunction,
  .Type = eEVENT_TYPE_USERCODE,
  .SignalDataType = ePRIMITIVE_DATA_TYPE_BOOL,
  .pSignal = NULL,
  .SignalMode = eEVENT_SIGNAL_MODE_BETWEEN,
  .pfUserFunction = feEVENT_EventList_1_Param_3_UserCode_UserCodeFunction,
  .DebounceEnable = false,
  .DebounceSetTimeMs = 6,
  .pfDebounceSetTimeMs = NULL,
  .DebounceResetTimeMs = 7,
  .pfDebounceResetTimeMs = NULL,
  .CounterEnable = false,
  .CounterThreshold = 6,
  .pfCounterThreshold = NULL,
  .pDescription = "ff",
  .pGroups = &(Events_EventList_1_GroupData.eEVENT_EventList_1_Param_3_UserCode),
  .StateFlags = 0,
  .ResetSourceFlags = (1 << S1),
 }
};

sEvents_EventList_1_GroupData Events_EventList_1_GroupData = {
{
  .VarType_1_Value = Member_2,
  .VarType_2_Value = Member_4,
},
{
  .VarType_1_Value = Member_1,
  .VarType_2_Value = Member_5,
},
{
  .VarType_1_Value = Member_3,
  .VarType_2_Value = Member_6,
}
};
uint16_t Events_EventList_1_Qty = 3;
