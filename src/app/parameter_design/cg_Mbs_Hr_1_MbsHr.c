
#include "cg_Mbs_Hr_1_MbsHr.h"

sMbs_HoldingRegister_Item Mbs_Hr_1_MbsHr[11] = {
{
  .Access = eMBS_ACCESS_RW,
  .Address = 0,
  .DataPtr = ((uint16_t*)&(ParametersData.Param_1.ShodowValue)),
  .Parameter = &(Parameters[ePARAMETER_Param_1]),
 },
{
  .Access = eMBS_ACCESS_RW,
  .Address = 1,
  .DataPtr = ((uint16_t*)&(ParametersData.Param_1.ShodowValue)) + 1,
  .Parameter = &(Parameters[ePARAMETER_Param_1]),
 },
{
  .Access = eMBS_ACCESS_R,
  .Address = 2,
  .DataPtr = ((uint16_t*)&(ParametersData.Param_2.ShodowValue)),
  .Parameter = &(Parameters[ePARAMETER_Param_2]),
 },
{
  .Access = eMBS_ACCESS_R,
  .Address = 3,
  .DataPtr = ((uint16_t*)&(ParametersData.Param_2.ShodowValue)) + 1,
  .Parameter = &(Parameters[ePARAMETER_Param_2]),
 },
{
  .Access = eMBS_ACCESS_R,
  .Address = 4,
  .DataPtr = ((uint16_t*)&(ParametersData.Param_3.ShodowValue)),
  .Parameter = &(Parameters[ePARAMETER_Param_3]),
 },
{
  .Access = eMBS_ACCESS_R,
  .Address = 5,
  .DataPtr = ((uint16_t*)&(ParametersData.Param_3.ShodowValue)) + 1,
  .Parameter = &(Parameters[ePARAMETER_Param_3]),
 },
{
  .Access = eMBS_ACCESS_R,
  .Address = 6,
  .DataPtr = ((uint16_t*)&(ParametersData.Param_4.ShodowValue)),
  .Parameter = &(Parameters[ePARAMETER_Param_4]),
 },
{
  .Access = eMBS_ACCESS_R,
  .Address = 7,
  .DataPtr = ((uint16_t*)&(ParametersData.Param_4.ShodowValue)) + 1,
  .Parameter = &(Parameters[ePARAMETER_Param_4]),
 },
{
  .Access = eMBS_ACCESS_R,
  .Address = 8,
  .DataPtr = ((uint16_t*)&(ParametersData.Param_5.ShodowValue)),
  .Parameter = &(Parameters[ePARAMETER_Param_5]),
 },
{
  .Access = eMBS_ACCESS_R,
  .Address = 9,
  .DataPtr = ((uint16_t*)&(ParametersData.Param_5.ShodowValue)) + 1,
  .Parameter = &(Parameters[ePARAMETER_Param_5]),
 },
{
  .Access = eMBS_ACCESS_R,
  .Address = 10,
  .DataPtr = (uint16_t*)&(ParametersData.Param_6.ShodowValue),
  .Parameter = &(Parameters[ePARAMETER_Param_6]),
 }
};
