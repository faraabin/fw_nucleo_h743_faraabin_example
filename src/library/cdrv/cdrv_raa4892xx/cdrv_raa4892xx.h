/**
******************************************************************************
* @file           : cdrv_raa4892xx.h
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2023 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2023 FaraabinCo.
* All rights reserved.</center></h2>
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
* @verbatim
* @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_raa4892xx_H
#define __cdrv_raa4892xx_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "hal\phal\intf\me_hal_spi_intf.h"

#include "bfe\r_bfe_api.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/** 
  * @brief
  */
struct TysCdrvRaa489206Vtbl;

/** 
  * @brief
  */
typedef struct {
  bool init;
  
	st_bfe_ctrl_t *u_bfe_control;
  const st_bfe_cfg_t *u_bfe_cfg;
	struct TysCdrvRaa489206Vtbl const *vptr;

	TysSpi_Obj *u_spi;
	TysGpio_Obj *u_cs;

  TysGpio_Obj *u_reset;
  TysGpio_Obj *u_wakeup;
  TysGpio_Obj *u_alert;

  TysGpio_Obj *u_gpio0;
  TysGpio_Obj *u_gpio1;
  TysGpio_Obj *u_gpio2;
  TysGpio_Obj *u_gpio3;
}TysCdrvRaa4892xx_Obj;

struct TysCdrvRaa489206Vtbl {
  e_bfe_err_t(*Init)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*Reset)(TysCdrvRaa4892xx_Obj * const me, e_bfe_reset_type_t reset_type);
  e_bfe_err_t(*StartSystemScan)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*StartContinuousScan)(TysCdrvRaa4892xx_Obj * const me, const bfe_cs_configuration_t * const st_cs_config);
  e_bfe_err_t(*StopContinuousScan)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*IsBusy)(TysCdrvRaa4892xx_Obj * const me, bool * p_is_busy);
  e_bfe_err_t(*ReadStatus)(TysCdrvRaa4892xx_Obj * const me, bfe_status_t * const p_bfe_status);
  e_bfe_err_t(*ClearAllFaults)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*ClearFault)(TysCdrvRaa4892xx_Obj * const me, const bfe_fault_type_t * const p_bfe_fault_type);
  e_bfe_err_t(*ReadMode)(TysCdrvRaa4892xx_Obj * const me, e_bfe_mode_t * const p_value);
  e_bfe_err_t(*ReadVpack)(TysCdrvRaa4892xx_Obj * const me, float * const p_value, bool trigger);
  e_bfe_err_t(*ReadIpack)(TysCdrvRaa4892xx_Obj * const me, float * const p_value, bool trigger);
  e_bfe_err_t(*ReadVcells)(TysCdrvRaa4892xx_Obj * const me, bfe_vcell_measurements_t * const p_values, bool trigger);
  e_bfe_err_t(*ReadOther)(TysCdrvRaa4892xx_Obj * const me, bfe_other_measurements_t * const p_values, bool trigger);
  e_bfe_err_t(*ReadAuxExt)(TysCdrvRaa4892xx_Obj * const me, bfe_auxext_measurements_t * const p_values, bool trigger);
  e_bfe_err_t(*ReadTemperature)(TysCdrvRaa4892xx_Obj * const me, bfe_auxext_measurements_t * const p_value, bool trigger);
  e_bfe_err_t(*TurnChargePumpOn)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*TurnChargePumpOff)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*TurnDFetOn)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*TurnDFetOff)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*TurnCFetOn)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*TurnCFetOff)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*TurnDFetOnCFetOn)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*TurnDFetOffCFetOn)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*TurnDFetOnCFetOff)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*TurnDFetOffCFetOff)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*SetAlerts)(TysCdrvRaa4892xx_Obj * const me, const bfe_alerts_masks_t * const p_alert_events);
  e_bfe_err_t(*SetDOC)(TysCdrvRaa4892xx_Obj * const me, float current_ma);
  e_bfe_err_t(*SetCOC)(TysCdrvRaa4892xx_Obj * const me, float current_mv);
  e_bfe_err_t(*SetDSC)(TysCdrvRaa4892xx_Obj * const me, float current_mv);
  e_bfe_err_t(*SetCellUndevoltage)(TysCdrvRaa4892xx_Obj * const me, float cells_uv_th_mv);
  e_bfe_err_t(*SetMaxVcellDeltaVoltage)(TysCdrvRaa4892xx_Obj * const me, float cells_maxd_th_mv);
  e_bfe_err_t(*SetVpackUndervoltage)(TysCdrvRaa4892xx_Obj * const me, float vpack_uv_th_mv);
  e_bfe_err_t(*SetCellOvervoltage)(TysCdrvRaa4892xx_Obj * const me, float cells_ov_th_mv);
  e_bfe_err_t(*SetVpackOvervoltage)(TysCdrvRaa4892xx_Obj * const me, float vpack_ov_th_mv);
  e_bfe_err_t(*SetInternalOTWarning)(TysCdrvRaa4892xx_Obj * const me, float temperature);
  e_bfe_err_t(*SetVoltageEndOfCharge)(TysCdrvRaa4892xx_Obj * const me, float veoc_mv);
  e_bfe_err_t(*SetCurrentEndOfCharge)(TysCdrvRaa4892xx_Obj * const me, float ieoc_ma);
  e_bfe_err_t(*SetInternalOTFault)(TysCdrvRaa4892xx_Obj * const me, float temperature);
  e_bfe_err_t(*SetMode)(TysCdrvRaa4892xx_Obj * const me, e_bfe_mode_t bfe_mode);
  e_bfe_err_t(*ReadAlerts)(TysCdrvRaa4892xx_Obj * const me, bfe_alerts_masks_t * const p_alert_events);
  e_bfe_err_t(*ReadDOC)(TysCdrvRaa4892xx_Obj * const me, float * current_ma);
  e_bfe_err_t(*ReadCOC)(TysCdrvRaa4892xx_Obj * const me, float * current_mv);
  e_bfe_err_t(*ReadDSC)(TysCdrvRaa4892xx_Obj * const me, float * current_mv);
  e_bfe_err_t(*ReadCellUndevoltage)(TysCdrvRaa4892xx_Obj * const me, float * cells_uv_th_mv);
  e_bfe_err_t(*ReadMaxVcellDeltaVoltage)(TysCdrvRaa4892xx_Obj * const me, float * cells_maxd_th_mv);
  e_bfe_err_t(*ReadVpackUndervoltage)(TysCdrvRaa4892xx_Obj * const me, float * vpack_uv_th_mv);
  e_bfe_err_t(*ReadCellOvervoltage)(TysCdrvRaa4892xx_Obj * const me, float * cells_ov_th_mv);
  e_bfe_err_t(*ReadVpackOvervoltage)(TysCdrvRaa4892xx_Obj * const me, float * vpack_ov_th_mv);
  e_bfe_err_t(*ReadInternalOTWarning)(TysCdrvRaa4892xx_Obj * const me, float * temperature);
  e_bfe_err_t(*ReadInternalOTFault)(TysCdrvRaa4892xx_Obj * const me, float * temperature);
  e_bfe_err_t(*ReadVoltageEndOfCharge)(TysCdrvRaa4892xx_Obj * const me, float * veoc_mv);
  e_bfe_err_t(*ReadCurrentEndOfCharge)(TysCdrvRaa4892xx_Obj * const me, float * ieoc_ma);
  e_bfe_err_t(*ConfigLowPowerMode)(TysCdrvRaa4892xx_Obj * const me, bfe_lpm_cfg_t * const p_lpm_options);
  e_bfe_err_t(*StartLowPowerMode)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*GetDieInformation)(TysCdrvRaa4892xx_Obj * const me, st_bfe_information_t * p_information);
  e_bfe_err_t(*ReadRegister)(TysCdrvRaa4892xx_Obj * const me, st_bfe_register_t * const p_bfe_register);
  e_bfe_err_t(*ReadAllRegisters)(TysCdrvRaa4892xx_Obj * const me);
  e_bfe_err_t(*WriteRegister)(TysCdrvRaa4892xx_Obj * const me, const st_bfe_register_t * const bfe_register);
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
//Helper functions to access Bfe functions easier
#define meBfe_Init_(obj_)                                        obj_->vptr->Init(obj_)
#define meBfe_Reset_(obj_, reset_type_)                          obj_->vptr->Reset(obj_, (reset_type_))
#define meBfe_StartSystemScan_(obj_)                             obj_->vptr->StartSystemScan(obj_)
#define meBfe_StartContinuousScan_(obj_, cs_config_)             obj_->vptr->StartContinuousScan(obj_, (cs_config_))
#define meBfe_StopContinuousScan_(obj_)                          obj_->vptr->StopContinuousScan(obj_)
#define meBfe_IsBusy_(obj_, is_busy_)                            obj_->vptr->IsBusy(obj_, (is_busy_))
#define meBfe_ReadStatus_(obj_, bfe_status_)                     obj_->vptr->ReadStatus(obj_, (bfe_status_))
#define meBfe_ClearAllFaults_(obj_)                              obj_->vptr->ClearAllFaults(obj_)
#define meBfe_ClearFault_(obj_, fault_type_)                     obj_->vptr->ClearFault(obj_, (fault_type_))
#define meBfe_ReadMode_(obj_, value_)                            obj_->vptr->ReadMode(obj_, (value_))
#define meBfe_ReadVpack_(obj_, value_, trigger_)                 obj_->vptr->ReadVpack(obj_, (value_), (trigger_))
#define meBfe_ReadIpack_(obj_, value_, trigger_)                 obj_->vptr->ReadIpack(obj_, (value_), (trigger_))
#define meBfe_ReadVcells_(obj_, values_, trigger_)               obj_->vptr->ReadVcells(obj_, (values_), (trigger_))
#define meBfe_ReadOther_(obj_, values_, trigger_)                obj_->vptr->ReadOther(obj_, (values_), (trigger_))
#define meBfe_ReadAuxExt_(obj_, values_, trigger_)               obj_->vptr->ReadAuxExt(obj_, (values_), (trigger_))
#define meBfe_ReadTemperature_(obj_, value_, trigger_)           obj_->vptr->ReadTemperature(obj_, (value_), (trigger_))
#define meBfe_TurnChargePumpOn_(obj_)                            obj_->vptr->TurnChargePumpOn(obj_)
#define meBfe_TurnChargePumpOff_(obj_)                           obj_->vptr->TurnChargePumpOff(obj_)
#define meBfe_TurnDFetOn_(obj_)                                  obj_->vptr->TurnDFetOn(obj_)
#define meBfe_TurnDFetOff_(obj_)                                 obj_->vptr->TurnDFetOff(obj_)
#define meBfe_TurnCFetOn_(obj_)                                  obj_->vptr->TurnCFetOn(obj_)
#define meBfe_TurnCFetOff_(obj_)                                 obj_->vptr->TurnCFetOff(obj_)
#define meBfe_TurnDFetOnCFetOn_(obj_)                            obj_->vptr->TurnDFetOnCFetOn(obj_)
#define meBfe_TurnDFetOffCFetOn_(obj_)                           obj_->vptr->TurnDFetOffCFetOn(obj_)
#define meBfe_TurnDFetOnCFetOff_(obj_)                           obj_->vptr->TurnDFetOnCFetOff(obj_)
#define meBfe_TurnDFetOffCFetOff_(obj_)                          obj_->vptr->TurnDFetOffCFetOff(obj_)
#define meBfe_SetAlerts_(obj_, alert_events_)                    obj_->vptr->SetAlerts(obj_, (alert_events_))
#define meBfe_SetDOC_(obj_, current_ma_)                         obj_->vptr->SetDOC(obj_, (current_ma_))
#define meBfe_SetCOC_(obj_, current_mv_)                         obj_->vptr->SetCOC(obj_, (current_mv_))
#define meBfe_SetDSC_(obj_, current_mv_)                         obj_->vptr->SetDSC(obj_, (current_mv_))
#define meBfe_SetCellUndevoltage_(obj_, cells_uv_th_mv_)         obj_->vptr->SetCellUndevoltage(obj_, (cells_uv_th_mv_))
#define meBfe_SetMaxVcellDeltaVoltage_(obj_, cells_maxd_th_mv_)  obj_->vptr->SetMaxVcellDeltaVoltage(obj_, (cells_maxd_th_mv_))
#define meBfe_SetVpackUndervoltage_(obj_, vpack_uv_th_mv_)       obj_->vptr->SetVpackUndervoltage(obj_, (vpack_uv_th_mv_))
#define meBfe_SetCellOvervoltage_(obj_, cells_ov_th_mv_)         obj_->vptr->SetCellOvervoltage(obj_, (cells_ov_th_mv_))
#define meBfe_SetVpackOvervoltage_(obj_,  vpack_ov_th_mv_)       obj_->vptr->SetVpackOvervoltage(obj_,  (vpack_ov_th_mv_))
#define meBfe_SetInternalOTWarning_(obj_, temperature_)          obj_->vptr->SetInternalOTWarning(obj_, (temperature_))
#define meBfe_SetVoltageEndOfCharge_(obj_, veoc_mv_)             obj_->vptr->SetVoltageEndOfCharge(obj_, (veoc_mv_))
#define meBfe_SetCurrentEndOfCharge_(obj_, ieoc_ma_)             obj_->vptr->SetCurrentEndOfCharge(obj_, (ieoc_ma_))
#define meBfe_SetInternalOTFault_(obj_, temperature_)            obj_->vptr->SetInternalOTFault(obj_, (temperature_))
#define meBfe_SetMode_(obj_, bfe_mode_)                          obj_->vptr->SetMode(obj_, (bfe_mode_))
#define meBfe_ReadAlerts_(obj_, alert_events_)                   obj_->vptr->ReadAlerts(obj_, (alert_events_))
#define meBfe_ReadDOC_(obj_, current_ma_)                        obj_->vptr->ReadDOC(obj_, (current_ma_))
#define meBfe_ReadCOC_(obj_, current_mv_)                        obj_->vptr->ReadCOC(obj_, (current_mv_))
#define meBfe_ReadDSC_(obj_, current_mv_)                        obj_->vptr->ReadDSC(obj_, (current_mv_))
#define meBfe_ReadCellUndevoltage_(obj_, cells_uv_th_mv_)        obj_->vptr->ReadCellUndevoltage(obj_, (cells_uv_th_mv_))
#define meBfe_ReadMaxVcellDeltaVoltage_(obj_, cells_maxd_th_mv_) obj_->vptr->ReadMaxVcellDeltaVoltage(obj_, (cells_maxd_th_mv_))
#define meBfe_ReadVpackUndervoltage_(obj_, vpack_uv_th_mv_)      obj_->vptr->ReadVpackUndervoltage(obj_, (vpack_uv_th_mv_))
#define meBfe_ReadCellOvervoltage_(obj_, cells_ov_th_mv_)        obj_->vptr->ReadCellOvervoltage(obj_, (cells_ov_th_mv_))
#define meBfe_ReadVpackOvervoltage_(obj_, vpack_ov_th_mv_)       obj_->vptr->ReadVpackOvervoltage(obj_, (vpack_ov_th_mv_))
#define meBfe_ReadInternalOTWarning_(obj_, temperature_)         obj_->vptr->ReadInternalOTWarning(obj_, (temperature_))
#define meBfe_ReadInternalOTFault_(obj_, temperature_)           obj_->vptr->ReadInternalOTFault(obj_, (temperature_))
#define meBfe_ReadVoltageEndOfCharge_(obj_, veoc_mv_)            obj_->vptr->ReadVoltageEndOfCharge(obj_, (veoc_mv_))
#define meBfe_ReadCurrentEndOfCharge_(obj_, ieoc_ma_)            obj_->vptr->ReadCurrentEndOfCharge(obj_, (ieoc_ma_))
#define meBfe_ConfigLowPowerMode_(obj_, lpm_options_)            obj_->vptr->ConfigLowPowerMode(obj_, (lpm_options_))
#define meBfe_StartLowPowerMode_(obj_)                           obj_->vptr->StartLowPowerMode(obj_)
#define meBfe_GetDieInformation_(obj_, information_)             obj_->vptr->GetDieInformation(obj_, (information_))
#define meBfe_ReadRegister_(obj_, bfe_register_)                 obj_->vptr->ReadRegister(obj_, (bfe_register_))
#define meBfe_ReadAllRegisters_(obj_)                            obj_->vptr->ReadAllRegisters(obj_)
#define meBfe_WriteRegister_(obj_, bfe_register_)                obj_->vptr->WriteRegister(obj_, (bfe_register_))

/* Exported functions prototypes ---------------------------------------------*/
uint8_t CdrvRaa4892xx_Init(TysCdrvRaa4892xx_Obj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_RAA4892XX_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
