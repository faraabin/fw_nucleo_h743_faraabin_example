
#include "cg_ParameterList_1_Param.h"

sParameter Parameters[6] = {
{
  //Param_1
  .Type = (uint8_t)ePARAMETER_TYPE_SETTING,
  .Name = "Param_1",
  .Id = 1,
  .Unit = "v",
  .Symbol = "s1",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "",
  .Data = &(ParametersData.Param_1),
},
{
  //Param_2
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_2",
  .Id = 2,
  .Unit = "i",
  .Symbol = "s2",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "",
  .Data = &(ParametersData.Param_2),
},
{
  //Param_3
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_3",
  .Id = 3,
  .Unit = "u",
  .Symbol = "s3",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "",
  .Data = &(ParametersData.Param_3),
},
{
  //Param_4
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_4",
  .Id = 4,
  .Unit = "u",
  .Symbol = "s4",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "",
  .Data = &(ParametersData.Param_4),
},
{
  //Param_5
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_5",
  .Id = 5,
  .Unit = "u",
  .Symbol = "s5",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "",
  .Data = &(ParametersData.Param_5),
},
{
  //Param_6
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_6",
  .Id = 6,
  .Unit = "u",
  .Symbol = "s6",
  .DataType = (uint8_t)eVAR_TYPE_uint16_t,
  .Description = "",
  .Data = &(ParametersData.Param_6),
}
};

sParameters_SmartData ParametersData = {
{
  //Param_1
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 100,
  .Min = -100,
},
{
  //Param_2
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 1,
  .ShodowValue = 1,
  .Max = 50,
  .Min = -50,
},
{
  //Param_3
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 100,
  .Min = 0,
},
{
  //Param_4
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 100,
  .Min = 0,
},
{
  //Param_5
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 100,
  .Min = 0,
},
{
  //Param_6
  .Type = (uint8_t)eVAR_TYPE_uint16_t,
  .Value = 34,
  .ShodowValue = 34,
  .Max = 100,
  .Min = 0,
}
};
