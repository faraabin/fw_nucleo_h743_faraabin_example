
//Include required file's
#include "cg_ParameterList_1_Param.h"

//Create & initialize parameter array
sParameter Parameters[10] = {
{
  //Param_1
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_1",
  .Id = 1,
  .Unit = "u",
  .Symbol = "s",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "d",
  .Data = &(ParametersSmartData.Param_1),
  .Groups = &(ParametersGroupData.Param_1),
},
{
  //Param_2
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_2",
  .Id = 2,
  .Unit = "u",
  .Symbol = "s",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "d",
  .Data = &(ParametersSmartData.Param_2),
  .Groups = &(ParametersGroupData.Param_2),
},
{
  //Param_3
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_3",
  .Id = 3,
  .Unit = "u",
  .Symbol = "s",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "d",
  .Data = &(ParametersSmartData.Param_3),
  .Groups = &(ParametersGroupData.Param_3),
},
{
  //Param_4
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_4",
  .Id = 4,
  .Unit = "u",
  .Symbol = "s",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "d",
  .Data = &(ParametersSmartData.Param_4),
  .Groups = &(ParametersGroupData.Param_4),
},
{
  //Param_5
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_5",
  .Id = 5,
  .Unit = "u",
  .Symbol = "s",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "d",
  .Data = &(ParametersSmartData.Param_5),
  .Groups = &(ParametersGroupData.Param_5),
},
{
  //Param_6
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_6",
  .Id = 6,
  .Unit = "u",
  .Symbol = "s",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "d",
  .Data = &(ParametersSmartData.Param_6),
  .Groups = &(ParametersGroupData.Param_6),
},
{
  //Param_7
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_7",
  .Id = 7,
  .Unit = "u",
  .Symbol = "s",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "d",
  .Data = &(ParametersSmartData.Param_7),
  .Groups = &(ParametersGroupData.Param_7),
},
{
  //Param_8
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_8",
  .Id = 8,
  .Unit = "u",
  .Symbol = "s",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "d",
  .Data = &(ParametersSmartData.Param_8),
  .Groups = &(ParametersGroupData.Param_8),
},
{
  //Param_9
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_9",
  .Id = 9,
  .Unit = "u",
  .Symbol = "s",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "d",
  .Data = &(ParametersSmartData.Param_9),
  .Groups = &(ParametersGroupData.Param_9),
},
{
  //Param_10
  .Type = (uint8_t)ePARAMETER_TYPE_MEASURE,
  .Name = "Param_10",
  .Id = 10,
  .Unit = "u",
  .Symbol = "s",
  .DataType = (uint8_t)eVAR_TYPE_float32_t,
  .Description = "d",
  .Data = &(ParametersSmartData.Param_10),
  .Groups = &(ParametersGroupData.Param_10),
}
};

//Create & initialize parameter's smart data
sParameters_SmartData ParametersSmartData = {
{
  //Param_1
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 9,
  .pfMax = NULL,
  .Min = 0,
  .pfMin = NULL,
},
{
  //Param_2
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 0,
  .pfMax = NULL,//(float32_t*)&(ParametersSmartData.Param_4.Value),
  .Min = 0,
  .pfMin = NULL,//(float32_t*)&(ParametersSmartData.Param_5.Value),
},
{
  //Param_3
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 9,
  .pfMax = NULL,
  .Min = 0,
  .pfMin = NULL,//(float32_t*)&(ParametersSmartData.Param_8.Value),
},
{
  //Param_4
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 0,
  .pfMax = NULL,//(float32_t*)&(ParametersSmartData.Param_1.Value),
  .Min = 1,
  .pfMin = NULL,
},
{
  //Param_5
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 10,
  .pfMax = NULL,
  .Min = 2,
  .pfMin = NULL,
},
{
  //Param_6
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 11,
  .pfMax = NULL,
  .Min = 3,
  .pfMin = NULL,
},
{
  //Param_7
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 12,
  .pfMax = NULL,
  .Min = 4,
  .pfMin = NULL,
},
{
  //Param_8
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 13,
  .pfMax = NULL,
  .Min = 5,
  .pfMin = NULL,
},
{
  //Param_9
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 14,
  .pfMax = NULL,
  .Min = 6,
  .pfMin = NULL,
},
{
  //Param_10
  .Type = (uint8_t)eVAR_TYPE_float32_t,
  .Value = 0,
  .ShodowValue = 0,
  .Max = 15,
  .pfMax = NULL,
  .Min = 7,
  .pfMin = NULL,
}
};

//Create & initialize parameter's group data
sParameters_GroupData ParametersGroupData = {
{
  .VarType_1_Value = Member_1,
  .VarType_2_Value = Member_4,
},
{
  .VarType_1_Value = Member_2,
  .VarType_2_Value = Member_5,
},
{
  .VarType_1_Value = Member_3,
  .VarType_2_Value = Member_6,
},
{
  .VarType_1_Value = Member_1,
  .VarType_2_Value = Member_4,
},
{
  .VarType_1_Value = Member_2,
  .VarType_2_Value = Member_5,
},
{
  .VarType_1_Value = Member_3,
  .VarType_2_Value = Member_6,
},
{
  .VarType_1_Value = Member_1,
  .VarType_2_Value = Member_4,
},
{
  .VarType_1_Value = Member_2,
  .VarType_2_Value = Member_5,
},
{
  .VarType_1_Value = Member_3,
  .VarType_2_Value = Member_6,
},
{
  .VarType_1_Value = Member_1,
  .VarType_2_Value = Member_4,
}
};
uint16_t ParametersQty = 10;
