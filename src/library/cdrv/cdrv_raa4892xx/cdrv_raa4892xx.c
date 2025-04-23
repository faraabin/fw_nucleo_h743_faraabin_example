/**
******************************************************************************
* @file           : cdrv_raa4892xx.c
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

/* Includes ------------------------------------------------------------------*/
#include "cdrv_raa4892xx.h"

#include "bfe\r_bfe_raa489206.h"
#include "bfe\r_bfe_raa489206_cfg.h"

#include "faraabin.h"

#include <math.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define ASSERT_NOT_NULL_(obj_) \
do {\
  if(obj_ == NULL)\
  {\
    return 1;\
  }\
}while(0)

/* Private variables ---------------------------------------------------------*/
/*Reset registers values*/
static const u_raa489206_productionid_reg_t g_reset_dieinformation_register = {.value = 0x50};
static const raa489206_iotw_th_t g_reset_iotw_th_register = 0x51;
static const raa489206_iotf_th_t g_reset_iotf_th_register = 0x45;
static const u_raa489206_vregop_register_t g_reset_vregop_register = {.value = 0xF0};
static const u_raa489206_otherfault_reg_t g_reset_other_faults = {.value = 0x00};
static const u_raa489206_globalop_reg_t g_reset_globalop_register = {.value = 0x00};
static const u_raa489206_vcellop_reg_t g_reset_vcellop_register = {.value = 0x80};
static const u_raa489206_ipackop_reg_t g_reset_ipackop_register = {.value = 0x80};
static const u_raa489206_cells_select_t g_reset_cells_select_register = {.value = 0xFFFF};
static const u_raa489206_vcell_voltage_t g_reset_vcell_voltage = {.value = 0x0000};
static const u_raa489206_vcell_max_delta_t g_reset_vcell_max_delta = {.value = 0x0000};
static const u_raa489206_ipack_voltage_t g_reset_ipack_voltage = {.value = 0x0000};
static const u_raa489206_ipack_timer_t g_reset_ipack_timer_register = {.value = 0x00000000};
static const raa489206_vcell_ov_th_t g_reset_vcell_ov_th_register = 0xFF;
static const raa489206_vcell_uv_th_t g_reset_vcell_uv_th_register = 0x00;
static const raa489206_vcell_max_delta_th_t g_reset_vcell_max_delta_th = 0xFF;
static const u_raa489206_vcell_fault_delay_t g_reset_fault_delay_register = {.value = 0x00};
static const raa489206_dsc_threshold_t g_reset_dsc_threshold_register = 0x0F;
static const raa489206_doc_th_register_t g_reset_doc_threshold_register = 0xFF;
static const raa489206_dsc_delay_register_t g_reset_dsc_delay_register = 0x00;
static const u_raa489206_scanop_register_t g_reset_scanop_register = {.value = 0x1B};
static const u_raa489206_pwr_fet_op_t g_reset_pwr_fet_op_register = {.value = 0x5C};
static const raa489206_coc_th_register_t g_reset_coc_threshold_register = 0xFF;
static const raa489206_vbat1_ov_th_t g_reset_vbat1_ov_th_register = 0xFF;
static const raa489206_vbat1_uv_th_t g_reset_vbat1_uv_th_register = 0x00;
static const u_raa489206_vbatop_register_t g_reset_vbatop_register = {.value = 0xC2};
static const u_raa489206_vbat1_register_t g_reset_vbat_register = {.value = 0x0000};
static const raa489206_internal_temperature_t g_reset_internal_temp_register = 0x00;
static const u_raa489206_prifault_register_t g_reset_priority_faults = {.value = 0x00};
static const u_raa489206_prifault_masks_t g_reset_priority_masks = {.value = 0xFF};
static const u_raa489206_etauxfault_reg_t g_reset_etaux_faults = {.value = 0x00};
static const u_raa489206_etauxfault_masks_t g_reset_etaux_masks = {.value = 0xFF};
static const u_raa489206_otherfault_masks_t g_reset_other_masks = {.value = 0xFF};
static const u_raa489206_cbstatus_reg_t g_reset_cb_status = {.value = 0x00};
static const u_raa489206_cbstatus_masks_t g_reset_cb_masks = {.value = 0xFF};
static const u_raa489206_status_reg_t g_reset_status = {.value = 0x00};
static const u_raa489206_status_masks_t g_reset_status_masks = {0xFF};
static const u_raa489206_owstatus_reg_t g_reset_ow_status = {.value = 0x0000};
static const u_raa489206_ow_masks_t g_reset_ow_masks = {.value = 0xFFFF};
static const u_raa489206_oc_delay_t g_reset_oc_delay = {.value = 0x00};
static const u_raa489206_load_charge_oper_t g_reset_load_charge_oper = {.value = 0xB4};
static const u_raa489206_etauxop_register_t g_reset_etaux_oper = {.value = 0xC0};
static const u_raa489206_gpio_alrt_op_reg_t g_reset_gpio_alrt_op = {.value = 0x10};/*1F*/
static const raa489206_xt0_aux0_voltage_t g_reset_xt0_aux0_voltage = {.value = 0x0000};
static const raa489206_xt1_aux1_voltage_t g_reset_xt1_aux1_voltage = {.value = 0x0000};
static const raa489206_dut0_threshold_t g_reset_dut0_th = 0xFF;
static const raa489206_dot0_threshold_t g_reset_dot0_th = 0x00;
static const raa489206_cut0_threshold_t g_reset_cut0_th = 0xFF;
static const raa489206_cot0_threshold_t g_reset_cot0_th = 0x00;
static const raa489206_dut1_threshold_t g_reset_dut1_th = 0xFF;
static const raa489206_dot1_threshold_t g_reset_dot1_th = 0x00;
static const raa489206_cut1_threshold_t g_reset_cut1_th = 0xFF;
static const raa489206_cot1_threshold_t g_reset_cot1_th = 0x00;
static const raa489206_vcc_min_th_t g_reset_vcc_min_th = 0x00;
static const raa489206_ireg_oc1_th_t g_reset_ireg_oc1_th = 0xFF;
static const raa489206_ireg_oc2_th_t g_reset_ireg_oc2_th = 0xFF;
static const raa489206_vtemp_voltage_t g_reset_vtemp_voltage = 0x00;
static const raa489206_vcc_voltage_t g_reset_vcc_voltage = 0x00;
static const raa489206_ireg_voltage_t g_reset_ireg_voltage = {.value = 0x0000};
static const u_raa489206_cb_op_register_t g_reset_cb_operation = {.value = 0x01};
static const u_raa489206_cb_cell_state_t g_reset_cb_cell_state = {.value = 0x0000};
static const u_raa489206_cbon_timer_t g_reset_cbon_timer = {.value = 0x00};
static const u_raa489206_cboff_timer_t g_reset_cboff_timer = {.value = 0x00};
static const raa489206_cb_min_delta_th_t g_reset_cb_min_delta_th = 0x00;
static const raa489206_cb_max_th_t g_reset_cb_max_th = 0xFF;
static const raa489206_cb_min_delta_th_t g_reset_cb_min_th = 0x00;
static const raa489206_veoc_th_t g_reset_veoc_th = 0xFF;
static const raa489206_ieoc_th_t g_reset_ieoc_th = 0x00;

/*Device registers which are linked to the registers bank contained in the control entity*/
static u_raa489206_productionid_reg_t g_dieinformation_register;
static u_raa489206_globalop_reg_t g_globalop_register;
static u_raa489206_vcellop_reg_t g_vcellop_register;
static u_raa489206_ipackop_reg_t g_ipackop_register;
static u_raa489206_cells_select_t g_cells_select_register;
static u_raa489206_vcell_voltage_t g_vcell1_voltage;
static u_raa489206_vcell_voltage_t g_vcell2_voltage;
static u_raa489206_vcell_voltage_t g_vcell3_voltage;
static u_raa489206_vcell_voltage_t g_vcell4_voltage;
static u_raa489206_vcell_voltage_t g_vcell5_voltage;
static u_raa489206_vcell_voltage_t g_vcell6_voltage;
static u_raa489206_vcell_voltage_t g_vcell7_voltage;
static u_raa489206_vcell_voltage_t g_vcell8_voltage;
static u_raa489206_vcell_voltage_t g_vcell9_voltage;
static u_raa489206_vcell_voltage_t g_vcell10_voltage;
static u_raa489206_vcell_voltage_t g_vcell11_voltage;
static u_raa489206_vcell_voltage_t g_vcell12_voltage;
static u_raa489206_vcell_voltage_t g_vcell13_voltage;
static u_raa489206_vcell_voltage_t g_vcell14_voltage;
static u_raa489206_vcell_voltage_t g_vcell15_voltage;
static u_raa489206_vcell_voltage_t g_vcell16_voltage;
static u_raa489206_vcell_max_delta_t g_vcell_max_delta;
static u_raa489206_ipack_voltage_t g_ipack_voltage;
static u_raa489206_ipack_timer_t g_ipack_timer_register;
static raa489206_vcell_ov_th_t g_vcell_ov_th_register;
static raa489206_vcell_uv_th_t g_vcell_uv_th_register;
static raa489206_vcell_max_delta_th_t g_vcell_max_delta_th;
static u_raa489206_vcell_fault_delay_t g_fault_delay_register;
static raa489206_dsc_threshold_t g_dsc_threshold_register;
static raa489206_doc_th_register_t g_doc_threshold_register;
static raa489206_dsc_delay_register_t g_dsc_delay_register;
static u_raa489206_scanop_register_t g_scanop_register;
static raa489206_coc_th_register_t g_coc_threshold_register;
static raa489206_vbat1_ov_th_t g_vbat1_ov_th_register;
static raa489206_vbat1_uv_th_t g_vbat1_uv_th_register;
static raa489206_iotw_th_t g_iotw_th_register;
static raa489206_iotf_th_t g_iotf_th_register;
static u_raa489206_vregop_register_t g_vregop_register;
static u_raa489206_vbatop_register_t g_vbatop_register;
static u_raa489206_vbat1_register_t g_vbat_register;
static raa489206_internal_temperature_t g_internal_temp_register;
static u_raa489206_prifault_register_t g_priority_faults;
static u_raa489206_prifault_masks_t g_priority_masks;
static u_raa489206_etauxfault_reg_t g_etaux_faults;
static u_raa489206_etauxfault_masks_t g_etaux_masks;
static u_raa489206_otherfault_reg_t g_other_faults;
static u_raa489206_otherfault_masks_t g_other_masks;
static u_raa489206_cbstatus_reg_t g_cb_status;
static u_raa489206_cbstatus_masks_t g_cb_masks;
static u_raa489206_status_reg_t g_status;
static u_raa489206_status_masks_t g_status_masks;
static u_raa489206_owstatus_reg_t g_ow_status;
static u_raa489206_ow_masks_t g_ow_masks;
static u_raa489206_oc_delay_t g_oc_delay;
static u_raa489206_load_charge_oper_t g_load_charge_oper;
static u_raa489206_etauxop_register_t g_etaux_oper;
static u_raa489206_gpio_alrt_op_reg_t g_gpio_alrt_op;
static raa489206_xt0_aux0_voltage_t g_xt0_aux0_voltage;
static raa489206_xt1_aux1_voltage_t g_xt1_aux1_voltage;
static raa489206_dut0_threshold_t g_dut0_th;
static raa489206_dot0_threshold_t g_dot0_th;
static raa489206_cut0_threshold_t g_cut0_th;
static raa489206_cot0_threshold_t g_cot0_th;
static raa489206_dut1_threshold_t g_dut1_th;
static raa489206_dot1_threshold_t g_dot1_th;
static raa489206_cut1_threshold_t g_cut1_th;
static raa489206_cot1_threshold_t g_cot1_th;
static raa489206_vcc_min_th_t g_vcc_min_th;
static raa489206_ireg_oc1_th_t g_ireg_oc1_th;
static raa489206_ireg_oc2_th_t g_ireg_oc2_th;
static raa489206_vtemp_voltage_t g_vtemp_voltage;
static raa489206_vcc_voltage_t g_vcc_voltage;
static raa489206_ireg_voltage_t g_ireg_voltage;
static u_raa489206_pwr_fet_op_t g_pwr_fet_op_register;
static u_raa489206_cb_op_register_t g_cb_operation;
static u_raa489206_cb_cell_state_t g_cb_cell_state;
static u_raa489206_cbon_timer_t g_cbon_timer;
static u_raa489206_cboff_timer_t g_cboff_timer;
static raa489206_cb_min_delta_th_t g_cb_min_delta_th;
static raa489206_cb_max_th_t g_cb_max_th;
static raa489206_cb_min_delta_th_t g_cb_min_th;
static raa489206_veoc_th_t g_veoc_th;
static raa489206_ieoc_th_t g_ieoc_th;

/*Registers bank*/
static st_raa489206_system_registers_t g_raa489206_registers =
{
 .die_information = {.address = RAA489206_REGISTER_SYS_INFO, .p_value = &(g_dieinformation_register.value),
                        .p_reset_value = (&g_reset_dieinformation_register.value), .type = READ, .size = (sizeof(g_dieinformation_register.value))/(sizeof(uint8_t))},
 .global_operation = {.address = RAA489206_REGISTER_GLOBAL_OP, .p_value = &(g_globalop_register.value),
                      .p_reset_value = (&g_reset_globalop_register.value), .type = READ_WRITE, .size = (sizeof(g_globalop_register.value))/(sizeof(uint8_t))},
 .vcell_operation = {.address = RAA489206_REGISTER_VCELL_OP, .p_value = &(g_vcellop_register.value),
                     .p_reset_value = (&g_reset_vcellop_register.value), .type = READ_WRITE, .size = (sizeof(g_vcellop_register.value))/(sizeof(uint8_t))},
 .ipack_operation = {.address = RAA489206_REGISTER_IPACK_OP, .p_value = &(g_ipackop_register.value),
                     .p_reset_value = (&g_reset_ipackop_register.value), .type = READ_WRITE, .size = (sizeof(g_ipackop_register.value))/(sizeof(uint8_t))},
 .cell_select = {.address = RAA489206_REGISTER_CELL_SEL, .p_value = &(g_cells_select_register.lsb_value),
                 .p_reset_value = (&g_reset_cells_select_register.lsb_value), .type = READ_WRITE, .size = (sizeof(g_cells_select_register.value))/(sizeof(uint8_t))},
 .vcell_1 = {.address = RAA489206_REGISTER_VCELL_1, .p_value = &(g_vcell1_voltage.lsb_value),
             .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell1_voltage.value))/(sizeof(uint8_t))},
 .vcell_2 = {.address = RAA489206_REGISTER_VCELL_2, .p_value = &(g_vcell2_voltage.lsb_value),
             .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell2_voltage.value))/(sizeof(uint8_t))},
 .vcell_3 = {.address = RAA489206_REGISTER_VCELL_3, .p_value = &(g_vcell3_voltage.lsb_value),
             .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell3_voltage.value))/(sizeof(uint8_t))},
 .vcell_4 = {.address = RAA489206_REGISTER_VCELL_4, .p_value = &(g_vcell4_voltage.lsb_value),
             .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell4_voltage.value))/(sizeof(uint8_t))},
 .vcell_5 = {.address = RAA489206_REGISTER_VCELL_5, .p_value = &(g_vcell5_voltage.lsb_value),
             .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell5_voltage.value))/(sizeof(uint8_t))},
 .vcell_6 = {.address = RAA489206_REGISTER_VCELL_6, .p_value = &(g_vcell6_voltage.lsb_value),
             .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell6_voltage.value))/(sizeof(uint8_t))},
 .vcell_7 = {.address = RAA489206_REGISTER_VCELL_7, .p_value = &(g_vcell7_voltage.lsb_value),
             .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell7_voltage.value))/(sizeof(uint8_t))},
 .vcell_8 = {.address = RAA489206_REGISTER_VCELL_8, .p_value = &(g_vcell8_voltage.lsb_value),
             .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell8_voltage.value))/(sizeof(uint8_t))},
 .vcell_9 = {.address = RAA489206_REGISTER_VCELL_9, .p_value = &(g_vcell9_voltage.lsb_value),
             .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell9_voltage.value))/(sizeof(uint8_t))},
 .vcell_10 = {.address = RAA489206_REGISTER_VCELL_10, .p_value = &(g_vcell10_voltage.lsb_value),
              .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell10_voltage.value))/(sizeof(uint8_t))},
 .vcell_11 = {.address = RAA489206_REGISTER_VCELL_11, .p_value = &(g_vcell11_voltage.lsb_value),
              .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell11_voltage.value))/(sizeof(uint8_t))},
 .vcell_12 = {.address = RAA489206_REGISTER_VCELL_12, .p_value = &(g_vcell12_voltage.lsb_value),
              .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell12_voltage.value))/(sizeof(uint8_t))},
 .vcell_13 = {.address = RAA489206_REGISTER_VCELL_13, .p_value = &(g_vcell13_voltage.lsb_value),
              .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell13_voltage.value))/(sizeof(uint8_t))},
 .vcell_14 = {.address = RAA489206_REGISTER_VCELL_14, .p_value = &(g_vcell14_voltage.lsb_value),
              .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell14_voltage.value))/(sizeof(uint8_t))},
 .vcell_15 = {.address = RAA489206_REGISTER_VCELL_15, .p_value = &(g_vcell15_voltage.lsb_value),
              .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell15_voltage.value))/(sizeof(uint8_t))},
 .vcell_16 = {.address = RAA489206_REGISTER_VCELL_16, .p_value = &(g_vcell16_voltage.lsb_value),
              .p_reset_value = (&g_reset_vcell_voltage.lsb_value), .type = READ, .size = (sizeof(g_vcell16_voltage.value))/(sizeof(uint8_t))},
 .vcell_max_delta_voltage = {.address = RAA489206_REGISTER_VCELL_MAX_DELTA, .p_value = &(g_vcell_max_delta.lsb_value),
                             .p_reset_value = (&g_reset_vcell_max_delta.lsb_value), .type = READ, .size = (sizeof(g_vcell_max_delta.value))/(sizeof(uint8_t))},
 .ipack_voltage = {.address = RAA489206_REGISTER_IPACK, .p_value = &(g_ipack_voltage.lsb_value),
                   .p_reset_value = (&g_reset_ipack_voltage.lsb_value), .type = READ, .size = (sizeof(g_ipack_voltage.value))/(sizeof(uint8_t))},
 .ipack_timer ={.address = RAA489206_REGISTER_IPACK_TIMER, .p_value = &(g_ipack_timer_register.lsb_value),
                .p_reset_value = (&g_reset_ipack_timer_register.lsb_value), .type = READ, .size = (sizeof(g_ipack_timer_register.value))/(sizeof(uint8_t))},
 .vcell_overvoltage_th = {.address = RAA489206_REGISTER_VCELL_OV_TH, .p_value = &g_vcell_ov_th_register,
                          .p_reset_value = (&g_reset_vcell_ov_th_register), .type = READ_WRITE, .size = (sizeof(g_vcell_ov_th_register))/(sizeof(uint8_t))},
 .vcell_undervoltage_th = {.address = RAA489206_REGISTER_VCELL_UV_TH, .p_value = &g_vcell_uv_th_register,
                           .p_reset_value = (&g_reset_vcell_uv_th_register), .type = READ_WRITE, .size = (sizeof(g_vcell_uv_th_register))/(sizeof(uint8_t))},
 .vcell_max_delta_th = {.address = RAA489206_REGISTER_VCELL_MAX_D_TH, .p_value = &g_vcell_max_delta_th,
                        .p_reset_value = (&g_reset_vcell_max_delta_th), .type = READ_WRITE, .size = (sizeof(g_vcell_max_delta_th))/(sizeof(uint8_t))},
 .fault_delay = {.address = RAA489206_REGISTER_FAULT_DELAY, .p_value = &(g_fault_delay_register.value),
                 .p_reset_value = (&g_reset_fault_delay_register.value), .type = READ_WRITE, .size = (sizeof(g_fault_delay_register.value))/(sizeof(uint8_t))},
 .discharge_short_current_th = {.address = RAA489206_REGISTER_DSC_TH , .p_value = &g_dsc_threshold_register,
                                .p_reset_value = (&g_reset_dsc_threshold_register), .type = READ_WRITE, .size = (sizeof(g_dsc_delay_register))/(sizeof(uint8_t))},
 .discharge_overcurrent_th = {.address = RAA489206_REGISTER_DOC_TH , .p_value = &g_doc_threshold_register,
                              .p_reset_value = (&g_reset_doc_threshold_register), .type = READ_WRITE, .size = (sizeof(g_doc_threshold_register))/(sizeof(uint8_t))},
 .dsc_delay = {.address = RAA489206_REGISTER_DSC_DELAY, .p_value = &g_dsc_delay_register,
               .p_reset_value = (&g_reset_dsc_delay_register), .type = READ_WRITE, .size = (sizeof(g_dsc_delay_register))/(sizeof(uint8_t))},
 .scan_operation = {.address = RAA489206_REGISTER_SCAN_OP, .p_value = &(g_scanop_register.value),
                    .p_reset_value = (&g_reset_scanop_register.value), .type = READ_WRITE, .size = (sizeof(g_scanop_register.value))/(sizeof(uint8_t))},
 .charge_overcurrent_th = {.address = RAA489206_REGISTER_COC_TH, .p_value = &g_coc_threshold_register,
                           .p_reset_value = (&g_reset_coc_threshold_register), .type = READ_WRITE, .size = (sizeof(g_coc_threshold_register))/(sizeof(uint8_t))},
 .vbat1_ov_th = {.address = RAA489206_REGISTER_OVBAT1_TH, .p_value = &g_vbat1_ov_th_register,
                 .p_reset_value = (&g_reset_vbat1_ov_th_register), .type = READ_WRITE, .size = (sizeof(g_vbat1_ov_th_register))/(sizeof(uint8_t))},
 .vbat1_uv_th = {.address = RAA489206_REGISTER_UVBAT1_TH, .p_value = &g_vbat1_uv_th_register,
                 .p_reset_value = (&g_reset_vbat1_uv_th_register), .type = READ_WRITE, .size = (sizeof(g_vbat1_uv_th_register))/(sizeof(uint8_t))},
 .overtemperature_warning_th = {.address = RAA489206_REGISTER_IOTW_TH, .p_value = &g_iotw_th_register,
                                .p_reset_value = (&g_reset_iotw_th_register), .type = READ_WRITE, .size = (sizeof(g_iotw_th_register))/(sizeof(uint8_t))},
 .overtemperature_fault_th = {.address = RAA489206_REGISTER_IOTF_TH, .p_value = &g_iotf_th_register,
                              .p_reset_value = (&g_reset_iotf_th_register), .type = READ_WRITE, .size = (sizeof(g_iotf_th_register))/(sizeof(uint8_t))},
 .vreg_operation = {.address = RAA489206_REGISTER_VREG_OP, .p_value = &(g_vregop_register.value),
                    .p_reset_value = (&g_reset_vregop_register.value), .type = READ_WRITE, .size = (sizeof(g_vregop_register.value))/(sizeof(uint8_t))},
 .vbat1_operation = {.address = RAA489206_REGISTER_VBAT1_OP, .p_value = &(g_vbatop_register.value),
                     .p_reset_value = (&g_reset_vbatop_register.value), .type = READ_WRITE, .size = (sizeof(g_vbatop_register.value))/(sizeof(uint8_t))},
 .vbat1 = {.address = RAA489206_REGISTER_VBAT1, .p_value = &(g_vbat_register.lsb_value),
           .p_reset_value = (&g_reset_vbat_register.lsb_value), .type = READ, .size = (sizeof(g_vbat_register.value))/(sizeof(uint8_t))},
 .internal_temperature = {.address = RAA489206_REGISTER_INTER_TEMP, .p_value = &g_internal_temp_register,
                          .p_reset_value = (&g_reset_internal_temp_register), .type = READ, .size = (sizeof(g_internal_temp_register))/(sizeof(uint8_t))},
 .priority_faults = {.address = RAA489206_REGISTER_PRIORITY_FAULTS, .p_value = &(g_priority_faults.value),
                     .p_reset_value = (&g_reset_priority_faults.value), .type = READ_WRITE, .size = (sizeof(g_priority_faults.value))/(sizeof(uint8_t))},
 .etaux_faults = {.address = RAA489206_REGISTER_ETAUX_FAULTS, .p_value = &(g_etaux_faults.value),
                  .p_reset_value = (&g_reset_etaux_faults.value), .type = READ_WRITE, .size = (sizeof(g_etaux_faults.value))/(sizeof(uint8_t))},
 .other_faults = {.address = RAA489206_REGISTER_OTHER_FAULTS, .p_value = &(g_other_faults.value),
                  .p_reset_value = (&g_reset_other_faults.value), .type = READ_WRITE, .size = (sizeof(g_other_faults.value))/(sizeof(uint8_t))},
 .cb_status = {.address = RAA489206_REGISTER_CB_STATUS, .p_value = &(g_cb_status.value),
               .p_reset_value = (&g_reset_cb_status.value), .type = READ_WRITE, .size = (sizeof(g_cb_status.value))/(sizeof(uint8_t))},
 .status = {.address = RAA489206_REGISTER_STATUS, .p_value = &(g_status.value),
            .p_reset_value = (&g_reset_status.value), .type = READ_WRITE, .size = (sizeof(g_status.value))/(sizeof(uint8_t))},
 .open_wire_status = {.address = RAA489206_REGISTER_OW_STATUS, .p_value = &(g_ow_status.lsb_value),
                      .p_reset_value = (&g_reset_ow_status.lsb_value), .type = READ_WRITE, .size = (sizeof(g_ow_status.value))/(sizeof(uint8_t))},
.priority_faults_mask = {.address = RAA489206_REGISTER_PRIOR_FAULT_M, .p_value = &(g_priority_masks.value),
                         .p_reset_value = (&g_reset_priority_masks.value), .type = READ_WRITE, .size = (sizeof(g_priority_masks.value))/(sizeof(uint8_t))},
.etaux_faults_mask = {.address = RAA489206_REGISTER_ETAUX_FAULT_M, .p_value = &(g_etaux_masks.value),
                      .p_reset_value = (&g_reset_etaux_masks.value), .type = READ_WRITE, .size = (sizeof(g_etaux_masks.value))/(sizeof(uint8_t))},
.other_faults_mask = {.address = RAA489206_REGISTER_OTHER_FAULT_M, .p_value = &(g_other_masks.value),
                      .p_reset_value = (&g_reset_other_masks.value), .type = READ_WRITE, .size = (sizeof(g_other_masks.value))/(sizeof(uint8_t))},
.cb_status_masks = {.address = RAA489206_REGISTER_CB_STATUS_M, .p_value = &(g_cb_masks.value),
                    .p_reset_value = (&g_reset_cb_masks.value), .type = READ_WRITE, .size = (sizeof(g_cb_masks.value))/(sizeof(uint8_t))},
.status_masks = {.address = RAA489206_REGISTER_STATUS_M, .p_value = &(g_status_masks.value),
                 .p_reset_value = (&g_reset_status_masks.value), .type = READ_WRITE, .size = (sizeof(g_status_masks.value))/(sizeof(uint8_t))},
.open_wire_mask = {.address = RAA489206_REGISTER_OW_M, .p_value = &(g_ow_masks.lsb_value),
                   .p_reset_value = (&g_reset_ow_masks.lsb_value), .type = READ_WRITE, .size = (sizeof(g_ow_masks.value))/(sizeof(uint8_t))},

 .oc_delay = {.address = RAA489206_REGISTER_OC_DELAY, .p_value = &(g_oc_delay.value),
              .p_reset_value = (&g_reset_oc_delay.value), .type = READ_WRITE, .size = (sizeof(g_oc_delay.value))/(sizeof(uint8_t))},
 .load_charge_operation = {.address = RAA489206_REGISTER_LD_CHR_OP, .p_value = &(g_load_charge_oper.value),
                           .p_reset_value = (&g_reset_load_charge_oper.value), .type = READ_WRITE, .size = (sizeof(g_load_charge_oper.value))/(sizeof(uint8_t))},
 .etaux_operation = {.address = RAA489206_REGISTER_ETAUX_OP, .p_value = &(g_etaux_oper.value),
                     .p_reset_value = (&g_reset_etaux_oper.value), .type = READ_WRITE, .size = (sizeof(g_etaux_oper.value))/(sizeof(uint8_t))},
 .gpio_alrt_operation = {.address = RAA489206_REGISTER_GPIO_ALERT_OP, .p_value = &(g_gpio_alrt_op.value),
                         .p_reset_value = (&g_reset_gpio_alrt_op.value), .type = READ_WRITE, .size = (sizeof(g_gpio_alrt_op.value))/(sizeof(uint8_t))},
 .etaux0_voltage = {.address = RAA489206_REGISTER_ETAUX_0_V, .p_value = &(g_xt0_aux0_voltage.lsb_value),
                    .p_reset_value = (&g_reset_xt0_aux0_voltage.lsb_value), .type = READ_WRITE, .size = (sizeof(g_xt0_aux0_voltage.value))/(sizeof(uint8_t))},
 .etaux1_voltage = {.address = RAA489206_REGISTER_ETAUX_1_V, .p_value = &(g_xt1_aux1_voltage.lsb_value),
                    .p_reset_value = (&g_reset_xt1_aux1_voltage.lsb_value), .type = READ_WRITE, .size = (sizeof(g_xt1_aux1_voltage.value))/(sizeof(uint8_t))},
 .dut0_limit = {.address = RAA489206_REGISTER_DUT0_LIMIT, .p_value = &(g_dut0_th),
                .p_reset_value = (&g_reset_dut0_th), .type = READ_WRITE, .size = (sizeof(g_dut0_th))/(sizeof(uint8_t))},
 .dot0_limit = {.address = RAA489206_REGISTER_DOT0_LIMIT, .p_value = &(g_dot0_th),
                .p_reset_value = (&g_reset_dot0_th), .type = READ_WRITE, .size = (sizeof(g_dot0_th))/(sizeof(uint8_t))},
 .cut0_limit = {.address = RAA489206_REGISTER_CUT0_LIMIT, .p_value = &(g_cut0_th),
                .p_reset_value = (&g_reset_cut0_th), .type = READ_WRITE, .size = (sizeof(g_cut0_th))/(sizeof(uint8_t))},
 .cot0_limit = {.address = RAA489206_REGISTER_COT0_LIMIT, .p_value = &(g_cot0_th),
                .p_reset_value = (&g_reset_cot0_th), .type = READ_WRITE, .size = (sizeof(g_cot0_th))/(sizeof(uint8_t))},
 .dut1_limit = {.address = RAA489206_REGISTER_DUT1_LIMIT, .p_value = &(g_dut1_th),
                .p_reset_value = (&g_reset_dut1_th), .type = READ_WRITE, .size = (sizeof(g_dut1_th))/(sizeof(uint8_t))},
 .dot1_limit = {.address = RAA489206_REGISTER_DOT1_LIMIT, .p_value = &(g_dot1_th),
                .p_reset_value = (&g_reset_dot1_th), .type = READ_WRITE, .size = (sizeof(g_dot1_th))/(sizeof(uint8_t))},
 .cut1_limit = {.address = RAA489206_REGISTER_CUT1_LIMIT, .p_value = &(g_cut1_th),
                .p_reset_value = (&g_reset_cut1_th), .type = READ_WRITE, .size = (sizeof(g_cut1_th))/(sizeof(uint8_t))},
 .cot1_limit = {.address = RAA489206_REGISTER_COT1_LIMIT, .p_value = &(g_cot1_th),
                .p_reset_value = (&g_reset_cot1_th), .type = READ_WRITE, .size = (sizeof(g_cot1_th))/(sizeof(uint8_t))},
 .vcc_minimum_th = {.address = RAA489206_REGISTER_VVCC_MIN, .p_value = &(g_vcc_min_th),
                    .p_reset_value = (&g_reset_vcc_min_th), .type = READ_WRITE, .size = (sizeof(g_vcc_min_th))/(sizeof(uint8_t))},
 .ireg_overcurrent1_th = {.address = RAA489206_REGISTER_IREGOC1, .p_value = &(g_ireg_oc1_th),
                          .p_reset_value = (&g_reset_ireg_oc1_th), .type = READ_WRITE, .size = (sizeof(g_ireg_oc1_th))/(sizeof(uint8_t))},
 .ireg_overcurrent2_th = {.address = RAA489206_REGISTER_IREGOC2, .p_value = &(g_ireg_oc2_th),
                          .p_reset_value = (&g_reset_ireg_oc2_th), .type = READ_WRITE, .size = (sizeof(g_ireg_oc2_th))/(sizeof(uint8_t))},
 .vtemp_voltage = {.address = RAA489206_REGISTER_VTEMP, .p_value = &(g_vtemp_voltage),
                   .p_reset_value = (&g_reset_vtemp_voltage), .type = READ, .size = (sizeof(g_vtemp_voltage))/(sizeof(uint8_t))},
 .vcc_voltage = {.address = RAA489206_REGISTER_VCC_V, .p_value = &(g_vcc_voltage),
                 .p_reset_value = (&g_reset_vcc_voltage), .type = READ, .size = (sizeof(g_vcc_voltage))/(sizeof(uint8_t))},
 .ireg_voltage = {.address = RAA489206_REGISTER_IREG_V, .p_value = &(g_ireg_voltage.lsb_value),
                  .p_reset_value = (&g_reset_ireg_voltage.lsb_value), .type = READ, .size = (sizeof(g_ireg_voltage.value))/(sizeof(uint8_t))},
 .power_fet_operation = {.address = RAA489206_REGISTER_PWR_FET_OP, .p_value = &(g_pwr_fet_op_register.value),
                  .p_reset_value = (&g_reset_pwr_fet_op_register.value), .type = READ_WRITE, .size = (sizeof(g_pwr_fet_op_register.value))/(sizeof(uint8_t))},
 .cb_operation = {.address = RAA489206_REGISTER_CB_OP, .p_value = &(g_cb_operation.value),
                  .p_reset_value = (&g_reset_cb_operation.value), .type = READ_WRITE, .size = (sizeof(g_cb_operation.value))/(sizeof(uint8_t))},
 .cb_cell_state = {.address = RAA489206_REGISTER_CB_CELL_STA, .p_value = &(g_cb_cell_state.lsb_value),
                   .p_reset_value = (&g_reset_cb_cell_state.lsb_value), .type = READ_WRITE, .size = (sizeof(g_cb_cell_state.value))/(sizeof(uint8_t))},
 .cb_on_time = {.address = RAA489206_REGISTER_CB_ON_TIME, .p_value = &(g_cbon_timer.value),
                .p_reset_value = (&g_reset_cbon_timer.value), .type = READ_WRITE, .size = (sizeof(g_cbon_timer.value))/(sizeof(uint8_t))},
 .cb_off_time = {.address = RAA489206_REGISTER_CB_OFF_TIME, .p_value = &(g_cboff_timer.value),
                 .p_reset_value = (&g_reset_cboff_timer.value), .type = READ_WRITE, .size = (sizeof(g_cboff_timer.value))/(sizeof(uint8_t))},
 .cb_min_delta_th = {.address = RAA489206_REGISTER_CB_MIN_D_TH, .p_value = &(g_cb_min_delta_th),
                     .p_reset_value = (&g_reset_cb_min_delta_th), .type = READ_WRITE, .size = (sizeof(g_cb_min_delta_th))/(sizeof(uint8_t))},
 .cb_max_th = {.address = RAA489206_REGISTER_CB_MAX_TH, .p_value = &(g_cb_max_th),
               .p_reset_value = (&g_reset_cb_max_th), .type = READ_WRITE, .size = (sizeof(g_cb_max_th))/(sizeof(uint8_t))},
 .cb_min_th = {.address = RAA489206_REGISTER_CB_MIN_TH, .p_value = &(g_cb_min_th),
               .p_reset_value = (&g_reset_cb_min_th), .type = READ_WRITE, .size = (sizeof(g_cb_min_th))/(sizeof(uint8_t))},
 .eoc_voltage_th = {.address = RAA489206_REGISTER_VEOC_TH, .p_value = &(g_veoc_th),
                    .p_reset_value = (&g_reset_veoc_th), .type = READ_WRITE, .size = (sizeof(g_veoc_th))/(sizeof(uint8_t))},
 .eoc_current_th = {.address = RAA489206_REGISTER_IEOC_TH, .p_value = &(g_ieoc_th),
                    .p_reset_value = (&g_reset_ieoc_th), .type = READ_WRITE, .size = (sizeof(g_ieoc_th))/(sizeof(uint8_t))},

};

const float s_vdoc_step_mv = -1.345f;
const float s_vdoc_offset_mv = -0.00525f;
const float s_vcoc_step_mv = 1.345f;
const float s_vcoc_offset_mv = 0.00525f;
const float s_vdsc_step_mv = -20.083f;
const float s_vdsc_offset_mv = -20.083f;
const float s_vcell_max_delta_step_mv = 18.83f;
const float s_vcell_max_delta_offset_mv = 18.79f;
const float s_vcell_ov_vthstep_mv = 18.83f;
const float s_vcell_uv_vthstep_mv = 18.83f;
const float s_vcell_ov_offset_mv = 18.79f;
const float s_vcell_uv_offset_mv = 0.03677f;
const float s_vbat1_ov_step_mv = 301.25f;
const float s_vbat1_uv_step_mv = 301.25f;
const float s_vbat1_ov_offset_mv = 300.66f;
const float s_vbat1_uv_offset_mv = 300.66f;
const float s_vbat1_step_mv = 1.177f;
const float s_vcell_step_mv = 0.07355f;
const float s_vcc_step_mv = 25.104f;
const float s_etaux_step_mv = 0.02452f;
const float s_ireg_step_mv = 0.010507f;
const float s_vtemp_step_mv = 3.138f;
const float s_vtemp_offset_mv = 804.908f;
const float s_ipack_lsb_mv= 0.01051f;
const float s_veoc_step_mv = 18.828f;
const float s_veoc_offset_mv = 18.791f;
const float s_ieoc_step_mv = 1.345f;
const float s_ieoc_offset_mv = 0.005253f;
const float s_cb_min_delta_step_mv = 4.707f;
const float s_cb_min_delta_offset_mv = 4.67f;
const float s_cb_max_step_mv = 18.828f;
const float s_cb_max_offset_mv = 18.791f;
const float s_cb_min_step_mv = 18.828f;
const float s_cb_min_offset_mv = 0.03677f;
const uint8_t s_cb_timer_step = 8;

volatile e_bfe_err_t s_spi_event_flag = BFE_SUCCESS;     // SPI Transfer Event completion flag

static uint8_t s_raw_buff[BUFF_LEN]; /*Read-After_Write Buffer*/
static uint8_t s_tx_buff[BUFF_LEN];   /*Transmit Buffer*/
static uint8_t s_rx_buff[BUFF_LEN];   /*Receive Buffer*/

/* Wait counter for operations monitoring */
static volatile const uint32_t s_max_wait_count = 0x0000FFFF;
static volatile const uint32_t s_min_wait_count = 0x00000000;
static volatile const uint32_t s_max_wait_busy_ms = 2000U;
static volatile uint32_t s_wait_count = 0x0000FFFF;
static volatile uint8_t s_read_busy_period = 20U; /*How often the busy bit is read to determine device availability*/

static u_raa489206_spi_address_t s_spi_add_crc;
static u_raa489206_spi_address_t s_spi_add_no_crc;
static st_raa489206_instance_ctrl_t * sp_raa489206_ctrl;

static bool s_device_busy;
static e_bfe_mode_t s_mode;

/* Private function prototypes -----------------------------------------------*/
static e_bfe_err_t Raa489206Init(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206Reset(TysCdrvRaa4892xx_Obj * const me, e_bfe_reset_type_t reset_type);
static e_bfe_err_t Raa489206StartSystemScan(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206StartContinuousScan(TysCdrvRaa4892xx_Obj * const me, const bfe_cs_configuration_t * const st_cs_config);
static e_bfe_err_t Raa489206StopContinuousScan(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206IsBusy(TysCdrvRaa4892xx_Obj * const me, bool * p_is_busy);
static e_bfe_err_t Raa489206ReadStatus(TysCdrvRaa4892xx_Obj * const me, bfe_status_t * const p_bfe_status);
static e_bfe_err_t Raa489206ClearAllFaults(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206ClearFault(TysCdrvRaa4892xx_Obj * const me, const bfe_fault_type_t * const p_bfe_fault_type);
static e_bfe_err_t Raa489206ReadMode(TysCdrvRaa4892xx_Obj * const me, e_bfe_mode_t * const p_value);
static e_bfe_err_t Raa489206ReadVpack(TysCdrvRaa4892xx_Obj * const me, float * const p_value, bool trigger);
static e_bfe_err_t Raa489206ReadIpack(TysCdrvRaa4892xx_Obj * const me, float * const p_value, bool trigger);
static e_bfe_err_t Raa489206ReadVcells(TysCdrvRaa4892xx_Obj * const me, bfe_vcell_measurements_t * const p_values, bool trigger);
static e_bfe_err_t Raa489206ReadOther(TysCdrvRaa4892xx_Obj * const me, bfe_other_measurements_t * const p_values, bool trigger);
static e_bfe_err_t Raa489206ReadAuxExt(TysCdrvRaa4892xx_Obj * const me, bfe_auxext_measurements_t * const p_values, bool trigger);
static e_bfe_err_t Raa489206ReadTemperature(TysCdrvRaa4892xx_Obj * const me, bfe_auxext_measurements_t * const p_value, bool trigger);
static e_bfe_err_t Raa489206TurnChargePumpOn(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206TurnChargePumpOff(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206TurnDFetOn(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206TurnDFetOff(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206TurnCFetOn(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206TurnCFetOff(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206TurnDFetOnCFetOn(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206TurnDFetOffCFetOn(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206TurnDFetOnCFetOff(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206TurnDFetOffCFetOff(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206SetAlerts(TysCdrvRaa4892xx_Obj * const me, const bfe_alerts_masks_t * const p_alert_events);
static e_bfe_err_t Raa489206SetDOC(TysCdrvRaa4892xx_Obj * const me, float current_ma);
static e_bfe_err_t Raa489206SetCOC(TysCdrvRaa4892xx_Obj * const me, float current_mv);
static e_bfe_err_t Raa489206SetDSC(TysCdrvRaa4892xx_Obj * const me, float current_mv);
static e_bfe_err_t Raa489206SetCellUndevoltage(TysCdrvRaa4892xx_Obj * const me, float cells_uv_th_mv);
static e_bfe_err_t Raa489206SetMaxVcellDeltaVoltage(TysCdrvRaa4892xx_Obj * const me, float cells_maxd_th_mv);
static e_bfe_err_t Raa489206SetVpackUndervoltage(TysCdrvRaa4892xx_Obj * const me, float vpack_uv_th_mv);
static e_bfe_err_t Raa489206SetCellOvervoltage(TysCdrvRaa4892xx_Obj * const me, float cells_ov_th_mv);
static e_bfe_err_t Raa489206SetVpackOvervoltage(TysCdrvRaa4892xx_Obj * const me, float vpack_ov_th_mv);
static e_bfe_err_t Raa489206SetInternalOTWarning(TysCdrvRaa4892xx_Obj * const me, float temperature);
static e_bfe_err_t Raa489206SetVoltageEndOfCharge(TysCdrvRaa4892xx_Obj * const me, float veoc_mv);
static e_bfe_err_t Raa489206SetCurrentEndOfCharge(TysCdrvRaa4892xx_Obj * const me, float ieoc_ma);
static e_bfe_err_t Raa489206SetInternalOTFault(TysCdrvRaa4892xx_Obj * const me, float temperature);
static e_bfe_err_t Raa489206SetMode(TysCdrvRaa4892xx_Obj * const me, e_bfe_mode_t bfe_mode);
static e_bfe_err_t Raa489206ReadAlerts(TysCdrvRaa4892xx_Obj * const me, bfe_alerts_masks_t * const p_alert_events);
static e_bfe_err_t Raa489206ReadDOC(TysCdrvRaa4892xx_Obj * const me, float * current_ma);
static e_bfe_err_t Raa489206ReadCOC(TysCdrvRaa4892xx_Obj * const me, float * current_mv);
static e_bfe_err_t Raa489206ReadDSC(TysCdrvRaa4892xx_Obj * const me, float * current_mv);
static e_bfe_err_t Raa489206ReadCellUndevoltage(TysCdrvRaa4892xx_Obj * const me, float * cells_uv_th_mv);
static e_bfe_err_t Raa489206ReadMaxVcellDeltaVoltage(TysCdrvRaa4892xx_Obj * const me, float * cells_maxd_th_mv);
static e_bfe_err_t Raa489206ReadVpackUndervoltage(TysCdrvRaa4892xx_Obj * const me, float * vpack_uv_th_mv);
static e_bfe_err_t Raa489206ReadCellOvervoltage(TysCdrvRaa4892xx_Obj * const me, float * cells_ov_th_mv);
static e_bfe_err_t Raa489206ReadVpackOvervoltage(TysCdrvRaa4892xx_Obj * const me, float * vpack_ov_th_mv);
static e_bfe_err_t Raa489206ReadInternalOTWarning(TysCdrvRaa4892xx_Obj * const me, float * temperature);
static e_bfe_err_t Raa489206ReadInternalOTFault(TysCdrvRaa4892xx_Obj * const me, float * temperature);
static e_bfe_err_t Raa489206ReadVoltageEndOfCharge(TysCdrvRaa4892xx_Obj * const me, float * veoc_mv);
static e_bfe_err_t Raa489206ReadCurrentEndOfCharge(TysCdrvRaa4892xx_Obj * const me, float * ieoc_ma);
static e_bfe_err_t Raa489206ConfigLowPowerMode(TysCdrvRaa4892xx_Obj * const me, bfe_lpm_cfg_t * const p_lpm_options);
static e_bfe_err_t Raa489206StartLowPowerMode(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206GetDieInformation(TysCdrvRaa4892xx_Obj * const me, st_bfe_information_t * p_information);
static e_bfe_err_t Raa489206ReadRegister(TysCdrvRaa4892xx_Obj * const me, st_bfe_register_t * const p_bfe_register);
static e_bfe_err_t Raa489206ReadAllRegisters(TysCdrvRaa4892xx_Obj * const me);
static e_bfe_err_t Raa489206WriteRegister(TysCdrvRaa4892xx_Obj * const me, const st_bfe_register_t * const bfe_register);

static void SpiCallback(void);
//static void I2cCallback(void);
static uint8_t VoltageToRegister(float voltage_mv, const float step, const float offset);
static float RegisterToVoltage(uint16_t reg_val, const float step, const float offset);
static uint8_t TemperatureToRegister(float deg_val);
static float RegisterToTemperature(uint8_t reg_val);

static e_bfe_err_t WriteSpi(TysCdrvRaa4892xx_Obj * const me, uint8_t address, uint8_t const * p_values, uint16_t num_values, bool use_crc);
static e_bfe_err_t ReadSpi(TysCdrvRaa4892xx_Obj * const me, uint8_t address, uint8_t * p_values, uint16_t num_values, bool use_crc);
static e_bfe_err_t ReadSpiAllRegistersNoCrc(TysCdrvRaa4892xx_Obj * const me, uint8_t * p_values);
//static e_bfe_err_t WriteI2c(uint8_t address, uint8_t const * p_values, uint16_t num_values, bool use_crc);
//static e_bfe_err_t ReadI2c(uint8_t address, uint8_t * p_values, uint16_t num_values, bool use_crc);
//static e_bfe_err_t ValidateI2cEvent(void);
static e_bfe_err_t ReadSpiCrcCommand(TysCdrvRaa4892xx_Obj * const me, uint8_t crc_command, uint8_t * p_values, uint16_t num_values);
static e_bfe_err_t ExecuteStartupSequence(TysCdrvRaa4892xx_Obj * const me, st_raa489206_instance_ctrl_t *p_raa489206_ctrl);
static e_bfe_err_t ExecuteBasicInit(TysCdrvRaa4892xx_Obj * const me, st_raa489206_instance_ctrl_t *p_raa489206_ctrl);
static e_bfe_err_t CompareResetValues(st_raa489206_system_registers_t *p_regs);
static inline void WaitUntilFree(TysCdrvRaa4892xx_Obj * const me, st_raa489206_instance_ctrl_t *p_raa489206_ctrl, bool *p_is_busy);
static uint16_t CalculateCrc(uint16_t numbytes, const uint8_t * const input_buf);
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                        ##### cdrv_raa4892xx.c Exported Functions #####
===============================================================================*/
uint8_t CdrvRaa4892xx_Init(TysCdrvRaa4892xx_Obj * const me) {
	me->init = false;
  ASSERT_NOT_NULL_(me->u_cs);
  ASSERT_NOT_NULL_(me->u_reset);
  ASSERT_NOT_NULL_(me->u_alert);
  ASSERT_NOT_NULL_(me->u_spi);
  meUNIT_INIT_START_();

  //Init BFE GPIOs
  me->u_cs->u_dir = eGPIO_DIR_OUTPUT;
  me->u_cs->u_out_type = eGPIO_PUSH_PULL;
  meUNIT_INIT_(meGpio_Init_(me->u_cs));
  meUNIT_INIT_(meGpio_Set_(me->u_cs));

  me->u_reset->u_dir = eGPIO_DIR_OUTPUT;
  me->u_reset->u_out_type = eGPIO_PUSH_PULL;
  meUNIT_INIT_(meGpio_Init_(me->u_reset));
  meUNIT_INIT_(meGpio_Reset_(me->u_reset)); //Release reset pin so that BFE can work.

  me->u_alert->u_dir = eGPIO_DIR_INPUT;
  me->u_alert->u_in_type = eGPIO_PULL_NONE;
  meUNIT_INIT_(meGpio_Init_(me->u_alert));

  if(me->u_wakeup != NULL) {
    me->u_wakeup->u_dir = eGPIO_DIR_OUTPUT;
    me->u_wakeup->u_out_type = eGPIO_PUSH_PULL;
    meUNIT_INIT_(meGpio_Init_(me->u_wakeup));
		meGpio_Set_(me->u_wakeup);
  }

  //TODO: Do something for the GPIOx pins of the BFE

  //Init BFE SPI
  me->u_spi->u_bit_order = eSPI_FIRSTBIT_MSB;
	me->u_spi->u_data_size = 8;
	me->u_spi->u_mode = eSPI_MODE_0;
	me->u_spi->u_role = eSPI_ROLE_MASTER;
	meUNIT_INIT_(meSpi_Init_(me->u_spi));
  meUNIT_INIT_(meSpi_Event_TransmitEnd_(me->u_spi, SpiCallback));
  meUNIT_INIT_(meSpi_Event_TransmitReceiveEnd_(me->u_spi, SpiCallback));

	static struct TysCdrvRaa489206Vtbl const vtbl = {
    Raa489206Init,
    Raa489206Reset,
    Raa489206StartSystemScan,
    Raa489206StartContinuousScan,
    Raa489206StopContinuousScan,
    Raa489206IsBusy,
    Raa489206ReadStatus,
    Raa489206ClearAllFaults,
    Raa489206ClearFault,
    Raa489206ReadMode,
    Raa489206ReadVpack,
    Raa489206ReadIpack,
    Raa489206ReadVcells,
    Raa489206ReadOther,
    Raa489206ReadAuxExt,
    Raa489206ReadTemperature,
    Raa489206TurnChargePumpOn,
    Raa489206TurnChargePumpOff,
    Raa489206TurnDFetOn,
    Raa489206TurnDFetOff,
    Raa489206TurnCFetOn,
    Raa489206TurnCFetOff,
    Raa489206TurnDFetOnCFetOn,
    Raa489206TurnDFetOffCFetOn,
    Raa489206TurnDFetOnCFetOff,
    Raa489206TurnDFetOffCFetOff,
    Raa489206SetAlerts,
    Raa489206SetDOC,
    Raa489206SetCOC,
    Raa489206SetDSC,
    Raa489206SetCellUndevoltage,
    Raa489206SetMaxVcellDeltaVoltage,
    Raa489206SetVpackUndervoltage,
    Raa489206SetCellOvervoltage,
    Raa489206SetVpackOvervoltage,
    Raa489206SetInternalOTWarning,
    Raa489206SetVoltageEndOfCharge,
    Raa489206SetCurrentEndOfCharge,
    Raa489206SetInternalOTFault,
    Raa489206SetMode,
    Raa489206ReadAlerts,
    Raa489206ReadDOC,
    Raa489206ReadCOC,
    Raa489206ReadDSC,
    Raa489206ReadCellUndevoltage,
    Raa489206ReadMaxVcellDeltaVoltage,
    Raa489206ReadVpackUndervoltage,
    Raa489206ReadCellOvervoltage,
    Raa489206ReadVpackOvervoltage,
    Raa489206ReadInternalOTWarning,
    Raa489206ReadInternalOTFault,
    Raa489206ReadVoltageEndOfCharge,
    Raa489206ReadCurrentEndOfCharge,
    Raa489206ConfigLowPowerMode,
    Raa489206StartLowPowerMode,
    Raa489206GetDieInformation,
    Raa489206ReadRegister,
    Raa489206ReadAllRegisters,
    Raa489206WriteRegister,
  };
	
	me->vptr = &vtbl;

  if(meUNIT_INIT_RESULT_() == 0) {
    me->init = true;
  }
  return meUNIT_INIT_RESULT_();
}


/*
===============================================================================
                    ##### cdrv_raa4892xx.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206Init(TysCdrvRaa4892xx_Obj * const me) {
	/*Error status*/
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	//fsp_err_t fsp_error = FSP_SUCCESS;

	/*Initialize the control entity according to the configuration settings contained in the configuration entity*/
	sp_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;
	st_raa489206_extended_cfg_t * p_ext_cfg = (st_raa489206_extended_cfg_t *) (me->u_bfe_cfg->p_extend);

	BFE_ERROR_RETURN(sp_raa489206_ctrl != NULL, BFE_ERR_NULL_CTRL_POINTER);
	BFE_ERROR_RETURN(p_ext_cfg != NULL, BFE_ERR_NULL_CFG_POINTER);

	sp_raa489206_ctrl->p_cfg = me->u_bfe_cfg;
	/*Set use of CRC*/
	sp_raa489206_ctrl->use_crc = p_ext_cfg->use_crc;
	/*Set cells present in the BMS*/
	sp_raa489206_ctrl->cells_select.value = (uint16_t) (0x0000FFFF & me->u_bfe_cfg->cell_select);
	/*set pointer to device registers*/
	sp_raa489206_ctrl->p_regs = &g_raa489206_registers;
	/*set the option to check writing operation by reading the value back after writing a register*/
	sp_raa489206_ctrl->read_after_write = me->u_bfe_cfg->read_after_write;

	/*initialization of the i/o pins */
//	fsp_error = p_ext_cfg->p_ioport->p_api->open(p_ext_cfg->p_ioport->p_ctrl, p_ext_cfg->p_ioport->p_cfg);

//	BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

//	sp_raa489206_ctrl->p_ioport = p_ext_cfg->p_ioport;
//	sp_raa489206_ctrl->reset_pin = p_ext_cfg->reset_pin;
//	sp_raa489206_ctrl->cms0_pin = p_ext_cfg->cms0_pin;
//	sp_raa489206_ctrl->i2c_add_sel_pin = p_ext_cfg->i2c_add_sel_pin;
//	sp_raa489206_ctrl->alert_pin = p_ext_cfg->alert_pin;
//	sp_raa489206_ctrl->wakeup_pin = p_ext_cfg->wakeup_pin;
	/*Set reset pin to ensure its initial high state*/
//	fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, sp_raa489206_ctrl->reset_pin, BSP_IO_LEVEL_HIGH);

	/*Set the wakeup pin*/
	//fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, sp_raa489206_ctrl->wakeup_pin, BSP_IO_LEVEL_HIGH);

//	BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

	/*Initialize communication interface with the device: I2C or SPI*/
	switch (sp_raa489206_ctrl->p_cfg->peripheral_type)
	{
			case BFE_COMMUNICATION_INTERFACE_SPI:

					/*Set read and write spi functions*/
					sp_raa489206_ctrl->p_readRegisterValues = ReadSpi;
					sp_raa489206_ctrl->p_writeRegisterValues = WriteSpi;

					/*Initialize SPI interface*/
//					fsp_error = p_ext_cfg->p_spi->p_api->open(p_ext_cfg->p_spi->p_ctrl, p_ext_cfg->p_spi->p_cfg);
//					fsp_error = p_ext_cfg->p_spi->p_api->callbackSet (p_ext_cfg->p_spi->p_ctrl, spi_callback, NULL, NULL);

//					BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

//					sp_raa489206_ctrl->p_spi = p_ext_cfg->p_spi;
//					sp_spi = p_ext_cfg->p_spi;
					/*select spi setting the CMS0 pin to 1*/
//					fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, sp_raa489206_ctrl->cms0_pin, BSP_IO_LEVEL_HIGH);

//					BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

					/*Set SPI addressses (with and without CRC)*/
					s_spi_add_crc.address_byte = p_ext_cfg->device_spi_add_with_crc;
					s_spi_add_no_crc.address_byte = p_ext_cfg->device_spi_add_no_crc;
//					s_ss_pin = p_ext_cfg->ss_pin;
					break;

			case BFE_COMMUNICATION_INTERFACE_I2C:

					/*Set read and write i2c functions*/
//					sp_raa489206_ctrl->p_readRegisterValues = ReadI2c;
//					sp_raa489206_ctrl->p_writeRegisterValues = WriteI2c;

					/*Initialize I2C interface*/
//					fsp_error = p_ext_cfg->p_i2c->p_api->open(p_ext_cfg->p_i2c->p_ctrl, p_ext_cfg->p_i2c->p_cfg);
//					fsp_error = p_ext_cfg->p_i2c->p_api->slaveAddressSet(p_ext_cfg->p_i2c->p_ctrl, p_ext_cfg->device_i2c_add, I2C_MASTER_ADDR_MODE_7BIT);
//					fsp_error = p_ext_cfg->p_i2c->p_api->callbackSet(p_ext_cfg->p_i2c->p_ctrl, i2c_callback, NULL, NULL);

//					BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

//					sp_raa489206_ctrl->p_i2c = p_ext_cfg->p_i2c;
//					sp_i2c = p_ext_cfg->p_i2c;
					/*select i2c clearing  CMS0*/
//					fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, sp_raa489206_ctrl->cms0_pin, BSP_IO_LEVEL_LOW);
//					fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, sp_raa489206_ctrl->i2c_add_sel_pin, BSP_IO_LEVEL_HIGH);

//					BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

					break;

			default:

					return BFE_ERR_COMM_NONSUPPORTED_INTERFACE;
	}

//	BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

	sp_raa489206_ctrl->init = true;
	/*Execution of the device startup sequence*/
	bfe_error = ExecuteStartupSequence(me, sp_raa489206_ctrl);

	BFE_ERROR_RETURN((bfe_error == BFE_SUCCESS || bfe_error == BFE_ERR_REGISTER_RESET_UNMATCHED), bfe_error);

	bfe_error = ExecuteBasicInit(me, sp_raa489206_ctrl);

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param reset_type 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206Reset(TysCdrvRaa4892xx_Obj * const me, e_bfe_reset_type_t reset_type) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
//	fsp_err_t fsp_error = FSP_SUCCESS;

	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	switch (reset_type)
	{
			case BFE_RESET_TYPE_SOFT:

					/*Read register before writing*/
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					g_globalop_register.value_b.SFT_RST = 1;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					break;

			case BFE_RESET_TYPE_TOIDLE:

					/*Read register before writing*/
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					g_globalop_register.value_b.RESET2IDLE = 1;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					break;

			case BFE_RESET_TYPE_HARD:

					bfe_error = (e_bfe_err_t)meGpio_Set_(me->u_reset);
					meDelay_ms_(RAA489206_RESET_DELAY_MS);
					bfe_error = (e_bfe_err_t)meGpio_Reset_(me->u_reset);
//					fsp_error = p_raa489206_ctrl->p_ioport->p_api->pinWrite(p_raa489206_ctrl->p_ioport->p_ctrl, p_raa489206_ctrl->reset_pin, BSP_IO_LEVEL_LOW);
//					R_BSP_SoftwareDelay(RAA489206_RESET_DELAY_MS, BSP_DELAY_UNITS_MILLISECONDS);
//					fsp_error = p_raa489206_ctrl->p_ioport->p_api->pinWrite(p_raa489206_ctrl->p_ioport->p_ctrl, p_raa489206_ctrl->reset_pin, BSP_IO_LEVEL_HIGH);
						
						BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
//					BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

					break;

			default:

					return BFE_ERR_INVALID_ARGUMENT;
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206StartSystemScan(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED );

	/*Ensure the device is in SCAN mode*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	g_scanop_register.value_b.SYS_MODE = RAA489206_SYSTEM_MODE_SCAN;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Clear the trigger bit of the Global operation register to ensure 0-1 transition*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	g_globalop_register.value_b.SYS_SCAN_TRIGGER = 0;
	g_globalop_register.value_b.SCAN_SEL = 1;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Trigger a system scan event to start scanning*/
	g_globalop_register.value_b.SYS_SCAN_TRIGGER = 1;
	/*disable read after write option since scan trigger bit is cleared after being written*/
	bool copy_raw = p_raa489206_ctrl->read_after_write;
	p_raa489206_ctrl->read_after_write = false;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));
	p_raa489206_ctrl->read_after_write = copy_raw;
	/*Verify success of scan */
	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param st_cs_config 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206StartContinuousScan(TysCdrvRaa4892xx_Obj * const me, const bfe_cs_configuration_t * const st_cs_config) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_cs_config_t * p_cont_scan_cfg = (st_raa489206_cs_config_t *) st_cs_config;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED );

	/*Stop continuous scan operation*/
	bfe_error = meBfe_StopContinuousScan_(me);

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Wait until the device is available, i.e., busy bit is 0*/

	WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

	BFE_ERROR_RETURN(s_device_busy == 0, BFE_ERR_DEVICE_BUSY);

	/*Clear all faults to clear fault counters and ensure a clean start*/

	meBfe_ClearAllFaults_(me);

	//BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	if (p_cont_scan_cfg != NULL)
	{
			/*Set the scan delay based on the selected enum value*/

			/*1. Read the  device scan operation register*/
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*2. Set the specified scan delay in the scan operation register*/
			g_scanop_register.value_b.SCAN_DELAY = p_cont_scan_cfg->scan_delay;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*3. Configure measurements to be made during scan according to settings specified by p_cont_scan_cfg */

			/*3.1. Vcell*/
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			g_vcellop_register.value_b.VCELL_EN = p_cont_scan_cfg->vcell_cfg.VCELL_EN;
			g_vcellop_register.value_b.VCELL_AVG = p_cont_scan_cfg->vcell_cfg.VCELL_AVG;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*3.2. ipack*/
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			g_ipackop_register.value_b.IPACK_EN = p_cont_scan_cfg->ipack_cfg.IPACK_EN;
			g_ipackop_register.value_b.IPACK_AVG = p_cont_scan_cfg->ipack_cfg.IPACK_AVG;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*3.3. Open-wire*/
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			g_pwr_fet_op_register.value_b.OW_EN = p_cont_scan_cfg->ow_cfg.OW_EN;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			g_ipackop_register.value_b.OW_UPDATE = p_cont_scan_cfg->ow_cfg.OW_UPDATE;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*3.4. Other*/
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			g_vbatop_register.value_b.OTHER_AVG = p_cont_scan_cfg->other_cfg.OTHER_AVG;
			g_vbatop_register.value_b.VBAT_ENABLE = p_cont_scan_cfg->other_cfg.VBAT_EN;
			g_vbatop_register.value_b.ITEMP_ENABLE = p_cont_scan_cfg->other_cfg.ITEMP_EN;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vreg_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			g_vregop_register.value_b.UPDATE_OTHER = p_cont_scan_cfg->other_cfg.OTHER_UPDATE;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vreg_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*3.5. Etaux*/
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->etaux_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			g_etaux_oper.value_b.ETAUX_AVG = p_cont_scan_cfg->etaux_cfg.ETAUX_AVG;
			g_etaux_oper.value_b.ETAUX_ENABLE = p_cont_scan_cfg->etaux_cfg.ETAUX_EN;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->etaux_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
	}

	/*4. Set the device to SCAN mode*/

	bfe_error = meBfe_SetMode_(me, BFE_MODE_SCAN);

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*5. Clear the trigger bit of the Global operation register to ensure 0-1 transition and set the continuous selection bit to 0*/

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	g_globalop_register.value_b.SYS_SCAN_TRIGGER = 0;
	g_globalop_register.value_b.SCAN_SEL = 0;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Trigger a system scan event to start continuous scan operation*/
	g_globalop_register.value_b.SYS_SCAN_TRIGGER = 1;
	/*disable read after write option since scan trigger bit is cleared after being written*/
	bool copy_raw = p_raa489206_ctrl->read_after_write;
	p_raa489206_ctrl->read_after_write = false;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));
	p_raa489206_ctrl->read_after_write = copy_raw;

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206StopContinuousScan(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	static e_bfe_mode_t mode;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED );

	/*set the Scan Select bit and clear the trigger bit of the Global operation register to stop any scan operation*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	bfe_error = meBfe_ReadMode_(me, &mode);

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	if ((g_globalop_register.value_b.SCAN_SEL == 1) || (mode != BFE_MODE_SCAN))
	{
			return BFE_SUCCESS;
	}

	/*set the Scan Select bit and clear the trigger bit of the Global operation register to stop any scan operation*/

	g_globalop_register.value_b.SCAN_SEL = 1;
	g_globalop_register.value_b.SYS_SCAN_TRIGGER = 0;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	uint16_t wait_delay = 0;

	switch (g_scanop_register.value_b.SCAN_DELAY)
	{
			case RAA489206_SCAN_DELAY_0_MS:

					wait_delay = 10;
					break;

			case RAA489206_SCAN_DELAY_64_MS:

					wait_delay = 80;
					break;

			case RAA489206_SCAN_DELAY_128_MS:

					wait_delay = 140;
					break;

			case RAA489206_SCAN_DELAY_256_MS:

					wait_delay = 270;
					break;

			case RAA489206_SCAN_DELAY_512_MS:

					wait_delay = 525;
					break;

			case RAA489206_SCAN_DELAY_1024_MS:

					wait_delay = 1040;
					break;

			case RAA489206_SCAN_DELAY_2048_MS:

					wait_delay = 2060;
					break;

			case RAA489206_SCAN_DELAY_4096_MS:

					wait_delay = 5010;
					break;
	}

	meDelay_ms_(wait_delay);
//	R_BSP_SoftwareDelay(wait_delay, BSP_DELAY_UNITS_MILLISECONDS);

	WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

	BFE_ERROR_RETURN(s_device_busy == false, BFE_ERR_DEVICE_BUSY);

	/*Clear all faults to clear fault counters and ensure a clean end*/

	bfe_error = meBfe_ClearAllFaults_(me);

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);


	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_is_busy 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206IsBusy(TysCdrvRaa4892xx_Obj * const me, bool * p_is_busy) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;

	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	*p_is_busy = g_globalop_register.value_b.BUSY;

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_bfe_status 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadStatus(TysCdrvRaa4892xx_Obj * const me, bfe_status_t * const p_bfe_status) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_status_t * p_raa489206_status = (st_raa489206_status_t *) p_bfe_status;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

	/*Read the priority faults register*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->priority_faults));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_status->priority_status.value = g_priority_faults.value;

	/*Read etaux faults register*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->etaux_faults));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_status->etaux_status.value = g_etaux_faults.value;

	/*Read the other faults register*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->other_faults));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_status->other_status.value = g_other_faults.value;

	/*Read the cell balancing status register*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->cb_status));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_status->cb_status.value = g_cb_status.value;

	/*Read the status register*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->status));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_status->general_status.value = g_status.value;

	/*Read the open-wire status register*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->open_wire_status));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_status->ow_status.value = g_ow_status.value;

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ClearAllFaults(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;

	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	/*Read device register before writing*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Set the Clear faults and Status bit of the Vcell operation register*/
	g_vcellop_register.value_b.CLR_FAULTS_STATUS = 1;
	/*Write device register to clear faults*/
	bool copy_raw = p_raa489206_ctrl->read_after_write;
	p_raa489206_ctrl->read_after_write = false;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_operation));
	p_raa489206_ctrl->read_after_write = copy_raw;

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	for (uint8_t i = 0; i < 10; i++ )
	{
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_operation));
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->priority_faults));
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->etaux_faults));
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->other_faults));
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->cb_status));
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->status));
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->open_wire_status));

			if ((g_vcellop_register.value_b.CLR_FAULTS_STATUS == 0)
							&& (g_priority_faults.value == 0)
							&& (g_etaux_faults.value == 0)
							&& (g_other_faults.value == 0)
							&& (g_cb_status.value == 0)
							&& ((g_status.value & 0x0F) == 0)
							&& (g_ow_status.value == 0))
			{
					return BFE_SUCCESS;
			}

				meDelay_ms_(1);
//			R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MILLISECONDS);
	}

	return BFE_ERR_DEVICE_BUSY;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_bfe_status 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ClearFault(TysCdrvRaa4892xx_Obj * const me, const bfe_fault_type_t * const p_bfe_fault_type) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;

	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;
	e_raa489206_fault_type_t * p_raa489206_fault_type = (e_raa489206_fault_type_t *) p_bfe_fault_type;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	/*Deactivate the RAW feature to avoid possible error when fault persists*/
	bool copy_raw = p_raa489206_ctrl->read_after_write;
	p_raa489206_ctrl->read_after_write = false;

	switch (*p_raa489206_fault_type)
	{
			case  RAA489206_FAULT_TYPE_PRIORITY:

			/*Clear priority faults bits*/
			g_priority_faults.value = 0x00;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->priority_faults));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->priority_faults));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			break;

			case RAA489206_FAULT_TYPE_ETAUX:

			/*clear  etaux faults bits*/
			g_etaux_faults.value = 0x00;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->etaux_faults));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->etaux_faults));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			break;

			case RAA489206_FAULT_TYPE_OTHER:

			 /*clear  other faults bits*/
			g_other_faults.value = 0x00;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->other_faults));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->other_faults));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			break;

			case RAA489206_FAULT_TYPE_CB:

			/*clear cell balancing faults bits*/
			g_cb_status.value = 0x00;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->cb_status));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->cb_status));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			break;

			case RAA489206_FAULT_TYPE_OW:

			/*clear open-wire faults bits*/
			g_ow_status.value = 0x00;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->open_wire_status));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->open_wire_status));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			break;

			case RAA489206_FAULT_TYPE_GENERAL:

			/*clear general status bits*/
			g_status.value = 0x00;

			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->status));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->status));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
	}

	p_raa489206_ctrl->read_after_write = copy_raw;

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_value 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadMode(TysCdrvRaa4892xx_Obj * const me, e_bfe_mode_t * const p_value) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;

	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	switch(g_scanop_register.value_b.SYS_MODE)
	{
			case RAA489206_SYSTEM_MODE_IDLE:

					*p_value = BFE_MODE_IDLE;

					break;

			case RAA489206_SYSTEM_MODE_LPM:

					*p_value = BFE_MODE_LOW_POWER_MODE;

					break;

			case RAA489206_SYSTEM_MODE_SHIP:

					*p_value = BFE_MODE_SHIP;

					break;

			case RAA489206_SYSTEM_MODE_SCAN:

					*p_value = BFE_MODE_SCAN;

					break;

			default:

					return BFE_ERR_NONSUPPORTED_MODE;
	}



	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_value 
 * @param trigger 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadVpack(TysCdrvRaa4892xx_Obj * const me, float * const p_value, bool trigger) {
	BFE_ERROR_RETURN(p_value != NULL, BFE_ERR_INVALID_POINTER);

	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bool restore_cont_scan = false;

	if (trigger == true)
	{
			/*1. Check whether the system is configured in continuous system scan*/
			bfe_error = meBfe_ReadMode_(me, &s_mode);

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			if (g_globalop_register.value_b.SCAN_SEL == 0 && s_mode == BFE_MODE_SCAN)
			{
					/*Stop continuous system scan to perform a trigger*/
					restore_cont_scan = true;
					g_globalop_register.value_b.SCAN_SEL = 1;
					g_globalop_register.value_b.SYS_SCAN_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*2. Trigger Vpack measurement*/
			/*Read register containing the Vpack measurement trigger*/
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*Check whether the trigger bit is set. If it is, clear it before triggering*/
			if (g_vbatop_register.value_b.VBAT_TRIGGER == 1)
			{
					g_vbatop_register.value_b.VBAT_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*3. Set the Vpack trigger bit to start measurement*/
			g_vbatop_register.value_b.VBAT_TRIGGER = 1;

			WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

			BFE_ERROR_RETURN(s_device_busy == false, BFE_ERR_DEVICE_BUSY);

			/*Write the register (with the read-after-write function disabled) to start a measurement*/
			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_operation));
			p_raa489206_ctrl->read_after_write = aux_raw;

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
	}

	/*4. Wait for until the device finishes measuring*/
	WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

	/*5. Read measurement*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	*p_value = RegisterToVoltage(g_vbat_register.value, s_vbat1_step_mv, 0.5f*s_vbat1_step_mv);

	/*6. Restore the device to continuous operation if it had been deactivated*/
	if (restore_cont_scan == true)
	{
			g_globalop_register.value_b.SCAN_SEL = 0;
			g_globalop_register.value_b.SYS_SCAN_TRIGGER = 1;
			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));
			p_raa489206_ctrl->read_after_write = aux_raw;

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
	}

	if (s_device_busy == true)
	{
			return BFE_WARN_BUSY;
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_value 
 * @param trigger 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadIpack(TysCdrvRaa4892xx_Obj * const me, float * const p_value, bool trigger) {
	BFE_ERROR_RETURN(p_value != NULL, BFE_ERR_INVALID_POINTER);

	e_bfe_err_t bfe_error = BFE_SUCCESS;

	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bool restore_cont_scan = false;

	if (trigger == true)
	{
			/*1. Check whether the system is configured in continuous system scan*/
			bfe_error = meBfe_ReadMode_(me, &s_mode);

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			if (g_globalop_register.value_b.SCAN_SEL == 0 && s_mode == BFE_MODE_SCAN)
			{
					/*Stop continuous system scan to perform a trigger*/
					restore_cont_scan = true;
					g_globalop_register.value_b.SCAN_SEL = 1;
					g_globalop_register.value_b.SYS_SCAN_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*2. Trigger Ipack measurement*/
			/*Read register containing the Ipack measurement trigger*/
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*Check whether the trigger bit is set. If it is, clear it before triggering*/
			if (g_reset_ipackop_register.value_b.IPACK_TRIGGER == 1)
			{
					g_ipackop_register.value_b.IPACK_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*3. Set the IPack trigger bit to start an Ipack measurement*/
			g_ipackop_register.value_b.IPACK_TRIGGER = 1;

			WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

			/*Write (with the read-after-write function disabled) the register to start a measurement*/

			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_operation));
			p_raa489206_ctrl->read_after_write =aux_raw;

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	}

	/*4. Wait for until the device finishes measuring*/
	WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

	BFE_ERROR_RETURN(s_device_busy == false, BFE_ERR_DEVICE_BUSY);

	/*5. Read Ipack voltage register which contains the value of the recent measurement*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_voltage));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	float v_ipack_mv = 0;

	if (g_ipack_voltage.value & 0x8000)
	{
			v_ipack_mv = ((float)(g_ipack_voltage.value - 65536.0f) * s_ipack_lsb_mv) + (0.5f * s_ipack_lsb_mv);
	}

	else
	{
			v_ipack_mv = (g_ipack_voltage.value * s_ipack_lsb_mv) + (0.5f * s_ipack_lsb_mv);
	}

	*p_value = v_ipack_mv / (*(p_raa489206_ctrl->p_cfg->p_shunt_resistor));

	/*6. Restore the device to continuous operation if it had been deactivated*/
	if (restore_cont_scan == true)
	{
			g_globalop_register.value_b.SCAN_SEL = 0;
			g_globalop_register.value_b.SYS_SCAN_TRIGGER = 1;
			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));
			p_raa489206_ctrl->read_after_write = aux_raw;

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
	}

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_timer));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	if (s_device_busy == true)
	{
			return BFE_WARN_BUSY;
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_values 
 * @param trigger 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadVcells(TysCdrvRaa4892xx_Obj * const me, bfe_vcell_measurements_t * const p_values, bool trigger) {
	BFE_ERROR_RETURN(p_values != NULL, BFE_ERR_INVALID_POINTER);

	e_bfe_err_t bfe_error = BFE_SUCCESS;

	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	u_raa489206_vcell_measurements_t * p_vcells = (u_raa489206_vcell_measurements_t *) p_values;

	uint8_t count = 0;

	uint8_t num_measurements = sizeof(p_vcells->vector) / sizeof(p_vcells->vector[0]);

	/*Initialization of Vcell values. Cells not selected will return -1 as value*/
	for (float *p_i = p_vcells->vector; count < num_measurements; p_i++)
	{
			*p_i =  (-1.0f);
			count++;
	}

	bool restore_cont_scan = false;

	if (trigger == true)
	{
			/*1. Check whether the system is configured in continuous system scan*/
			bfe_error = meBfe_ReadMode_(me, &s_mode);

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			if (g_globalop_register.value_b.SCAN_SEL == 0 && s_mode == BFE_MODE_SCAN)
			{
					/*Stop continuous system scan to perform a trigger*/
					restore_cont_scan = true;
					g_globalop_register.value_b.SCAN_SEL = 1;
					g_globalop_register.value_b.SYS_SCAN_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*2. Trigger measurement of the selected cells*/
			/*Read the Vcell operation register*/
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*Check whether the trigger bit is set. If it is, clear it before triggering*/
			if (g_vcellop_register.value_b.VCELL_TRIGGER == 1)
			{
					g_vcellop_register.value_b.VCELL_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*3. Set its Vcell trigger bit and write the device register with raw function disabled*/
			g_vcellop_register.value_b.VCELL_TRIGGER = 1;

			WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

			BFE_ERROR_RETURN(s_device_busy == false, BFE_ERR_DEVICE_BUSY);

			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_operation));
			p_raa489206_ctrl->read_after_write = aux_raw;
	}

	/*4. Wait for until the device finishes measuring*/
	WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

	/*5. Read measurements*/

//    if (p_raa489206_ctrl->use_crc)
//    {
//        static uint8_t s_vcells_array[RAA489206_REGISTER_NUMBER_OF_VCELL_REGISTERS];
//
//        bfe_error = read_spi_crc_command(RAA489206_CRC_COMMAND_VCELL, &(s_vcells_array[0]), RAA489206_REGISTER_NUMBER_OF_VCELL_REGISTERS);
//
//        BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
//
//        uint8_t cell_num = 0;
//
//        for (uint8_t i = 0; i < (RAA489206_REGISTER_NUMBER_OF_VCELL_REGISTERS - 2) ; i++ )
//        {
//
//            if (READ_BIT(p_raa489206_ctrl->cells_select.value,cell_num))
//            {
//                u_raa489206_vcell_voltage_t vcell_v = {.value = 0x00};
//                vcell_v.lsb_msb.msb = s_vcells_array[i];
//                vcell_v.lsb_msb.lsb = s_vcells_array[i + 1];
//                p_vcells->vector[cell_num] = register_to_voltage(vcell_v.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
//            }
//
//            i++;
//            cell_num++;
//        }
//
//        u_raa489206_vcell_voltage_t vdelta_v = {.value = 0x00};
//        vdelta_v.lsb_msb.msb = s_vcells_array[RAA489206_REGISTER_NUMBER_OF_VCELL_REGISTERS - 2];
//        vdelta_v.lsb_msb.lsb = s_vcells_array[RAA489206_REGISTER_NUMBER_OF_VCELL_REGISTERS - 1];
//
//        p_vcells->measurements.vcell_max_delta = register_to_voltage(vdelta_v.value, s_vcell_step_mv, 0);
//    }
//
//    else
//    {

			if (p_raa489206_ctrl->cells_select.cells.CELL1)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_1));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell1 = RegisterToVoltage(g_vcell1_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL2)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_2));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell2 = RegisterToVoltage(g_vcell2_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}
			if (p_raa489206_ctrl->cells_select.cells.CELL3)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_3));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell3 = RegisterToVoltage(g_vcell3_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL4)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_4));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell4 = RegisterToVoltage(g_vcell4_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL5)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_5));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell5 = RegisterToVoltage(g_vcell5_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL6)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_6));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell6 = RegisterToVoltage(g_vcell6_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL7)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_7));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell7 = RegisterToVoltage(g_vcell7_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL8)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_8));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell8 = RegisterToVoltage(g_vcell8_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL9)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_9));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell9 = RegisterToVoltage(g_vcell9_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL10)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_10));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell10 = RegisterToVoltage(g_vcell10_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL11)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_11));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell11 = RegisterToVoltage(g_vcell11_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL12)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_12));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell12 = RegisterToVoltage(g_vcell12_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL13)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_13));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell13 = RegisterToVoltage(g_vcell13_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL14)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_14));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell14 = RegisterToVoltage(g_vcell14_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL15)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_15));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell15 = RegisterToVoltage(g_vcell15_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			if (p_raa489206_ctrl->cells_select.cells.CELL16)
			{
					bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_16));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					p_vcells->measurements.cell16 = RegisterToVoltage(g_vcell16_voltage.value, s_vcell_step_mv, 0.5f*s_vcell_step_mv);
			}

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_max_delta_voltage));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			p_vcells->measurements.vcell_max_delta = RegisterToVoltage(g_vcell_max_delta.value,s_vcell_step_mv, 0);
//    }

	/*6. Restore the device to continuous operation if it had been deactivated*/
	if (restore_cont_scan)
	{
			g_globalop_register.value_b.SCAN_SEL = 0;
			g_globalop_register.value_b.SYS_SCAN_TRIGGER = 1;
			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));
			p_raa489206_ctrl->read_after_write = aux_raw;

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
	}

	if (s_device_busy == true)
	{
			return BFE_WARN_BUSY;
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_values 
 * @param trigger 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadOther(TysCdrvRaa4892xx_Obj * const me, bfe_other_measurements_t * const p_values, bool trigger) {
	BFE_ERROR_RETURN(p_values != NULL, BFE_ERR_INVALID_POINTER);

	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	u_raa489206_other_measurements_t * p_other_measurements = (u_raa489206_other_measurements_t *) p_values;

	bool restore_cont_scan = false;

	if (trigger == true)
	{
			/*1. Check whether the system is configured in continuous system scan*/
			bfe_error = meBfe_ReadMode_(me, &s_mode);

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			if (g_globalop_register.value_b.SCAN_SEL == 0 && s_mode == BFE_MODE_SCAN)
			{
					/*Stop continuous system scan to perform a trigger*/
					restore_cont_scan = true;
					g_globalop_register.value_b.SCAN_SEL = 1;
					g_globalop_register.value_b.SYS_SCAN_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*2. Trigger Regulator measurements*/
			/*Read Vreg operation register*/
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vreg_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*Check whether trigger bit is set, and clear it if it is.*/
			if (g_vregop_register.value_b.VREG_TRIGGER == 1)
			{
					g_vregop_register.value_b.VREG_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vreg_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*3. Set its Vreg trigger bit and write the device register (with raw function disabled)*/
			g_vregop_register.value_b.VREG_TRIGGER = 1;

			WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

			BFE_ERROR_RETURN(s_device_busy == false, BFE_ERR_DEVICE_BUSY);

			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vreg_operation));
			p_raa489206_ctrl->read_after_write = aux_raw;

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	}

	/*4. Wait until the device finishes measuring*/
	WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

	/*5. Read other measurements*/
	/*Vcc*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcc_voltage));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	uint16_t aux_cast = (uint16_t)g_vcc_voltage;
	p_other_measurements->measurements.vcc = RegisterToVoltage(aux_cast, s_vcc_step_mv, 0.5f*s_vcc_step_mv);

	/*Ireg*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->ireg_voltage));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	st_raa489206_extended_cfg_t * p_cfg = (st_raa489206_extended_cfg_t *) p_raa489206_ctrl->p_cfg->p_extend;

	p_other_measurements->measurements.ireg = RegisterToVoltage(g_ireg_voltage.value, s_ireg_step_mv, 0.5f*s_ireg_step_mv) / p_cfg->reg_resistor;

	/*Vtemp*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vtemp_voltage));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_other_measurements->measurements.vtemp = RegisterToVoltage(g_vtemp_voltage, s_vtemp_step_mv, s_vtemp_offset_mv);

	/*6. Restore the device to continuous operation if it had been deactivated*/
	if (restore_cont_scan)
	{
			g_globalop_register.value_b.SCAN_SEL = 0;
			g_globalop_register.value_b.SYS_SCAN_TRIGGER = 1;
			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));
			p_raa489206_ctrl->read_after_write = aux_raw;

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
	}

	if (s_device_busy == true)
	{
			return BFE_WARN_BUSY;
	}

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_values 
 * @param trigger 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadAuxExt(TysCdrvRaa4892xx_Obj * const me, bfe_auxext_measurements_t * const p_values, bool trigger) {
	BFE_ERROR_RETURN(p_values != NULL, BFE_ERR_INVALID_POINTER);

	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	u_raa489206_etaux_measurements_t * p_other_measurements = (u_raa489206_etaux_measurements_t *) p_values;

	bool restore_cont_scan = false;

	if (trigger == true)
	{
			/*1. Check whether the system is configured in continuous system scan*/
			bfe_error = meBfe_ReadMode_(me, &s_mode);

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			if (g_globalop_register.value_b.SCAN_SEL == 0 && s_mode == BFE_MODE_SCAN)
			{
					/*Stop continuous system scan to perform a trigger*/
					restore_cont_scan = true;
					g_globalop_register.value_b.SCAN_SEL = 1;
					g_globalop_register.value_b.SYS_SCAN_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*2. Trigger ETAUX measurements*/
			/*Read ETAUX operation register*/

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->etaux_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*Check whether trigger bit is set, and clear it if it is.*/
			if (g_etaux_oper.value_b.ETAUX_TRIGGER == 1)
			{
					g_etaux_oper.value_b.ETAUX_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->etaux_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*3. Set its Vcell trigger bit and write the device register (with raw function disabled)*/
			g_etaux_oper.value_b.ETAUX_TRIGGER = 1;

			WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

			BFE_ERROR_RETURN(s_device_busy == false, BFE_ERR_DEVICE_BUSY);

			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->etaux_operation));
			p_raa489206_ctrl->read_after_write = aux_raw;

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	}

	/*4. Wait until the device finishes measuring*/
	WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

	/*5. Read ETAUX measurements*/
	/*xT0/Aux0*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->etaux0_voltage));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_other_measurements->measurements.xt0_aux0 = RegisterToVoltage(g_xt0_aux0_voltage.value, s_etaux_step_mv, 0.5f*s_etaux_step_mv);

	/*xT0/Aux0*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->etaux1_voltage));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_other_measurements->measurements.xt1_aux1 = RegisterToVoltage(g_xt1_aux1_voltage.value, s_etaux_step_mv, 0.5f*s_etaux_step_mv); //Bug found

	/*6. Restore the device to continuous operation if it had been deactivated*/
	if (restore_cont_scan)
	{
			g_globalop_register.value_b.SCAN_SEL = 0;
			g_globalop_register.value_b.SYS_SCAN_TRIGGER = 1;
			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));
			p_raa489206_ctrl->read_after_write = aux_raw;

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
	}

	if (s_device_busy == true)
	{
			return BFE_WARN_BUSY;
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_value 
 * @param trigger 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadTemperature(TysCdrvRaa4892xx_Obj * const me, bfe_auxext_measurements_t * const p_value, bool trigger) {
	BFE_ERROR_RETURN(p_value != NULL, BFE_ERR_INVALID_POINTER);

	e_bfe_err_t bfe_error = BFE_SUCCESS;

	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	st_raa489206_temperature_measurements_t * p_itemperature = (st_raa489206_temperature_measurements_t *) p_value;

	bool restore_cont_scan = false;

	if (trigger == true)
	{
			/*1. Check whether the system is configured in continuous system scan*/
			bfe_error = meBfe_ReadMode_(me, &s_mode);

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			if (g_globalop_register.value_b.SCAN_SEL == 0 && s_mode == BFE_MODE_SCAN)
			{
					/*Stop continuous system scan to perform a trigger*/
					restore_cont_scan = true;
					g_globalop_register.value_b.SCAN_SEL = 1;
					g_globalop_register.value_b.SYS_SCAN_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*2. Trigger Internal temperature measurement*/
			/*Read Vbat operation register, which contains the Internal temperature trigger*/

			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			/*Check whether trigger bit is set, and clear it if it is.*/
			if (g_reset_vbatop_register.value_b.ITEMP_TRIGGER == 1)
			{
					g_vbatop_register.value_b.ITEMP_TRIGGER = 0;
					bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_operation));

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
			}

			/*3. Set its Vcell trigger bit and write the device register (with raw function disabled)*/
			g_vbatop_register.value_b.ITEMP_TRIGGER = 1;

			WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

			BFE_ERROR_RETURN(s_device_busy == false, BFE_ERR_DEVICE_BUSY);

			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_operation));
			p_raa489206_ctrl->read_after_write = aux_raw;

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	}

	/*4. Wait until the device finishes measuring*/
	WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

	/*5. Read internal temperature measurement*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->internal_temperature));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	*p_itemperature = RegisterToTemperature(g_internal_temp_register);

	/*6. Restore the device to continuous operation if it had been deactivated*/
	if (restore_cont_scan)
	{
			g_globalop_register.value_b.SCAN_SEL = 0;
			g_globalop_register.value_b.SYS_SCAN_TRIGGER = 1;
			bool aux_raw = p_raa489206_ctrl->read_after_write;
			p_raa489206_ctrl->read_after_write = false;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));
			p_raa489206_ctrl->read_after_write = aux_raw;

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
	}

	if (s_device_busy == true)
	{
			return BFE_WARN_BUSY;
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206TurnChargePumpOn(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Turn the charge pump on*/
	g_pwr_fet_op_register.value_b.CPMP_EN = 1;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
	/*Wait 10ms to ensure its output voltage rises*/
	meDelay_ms_(BFE_RAA489206_CHARGE_PUMP_WAIT_TIME_MS);
//	R_BSP_SoftwareDelay(BFE_RAA489206_CHARGE_PUMP_WAIT_TIME_MS, BSP_DELAY_UNITS_MILLISECONDS);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206TurnChargePumpOff(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Turn the charge pump off*/
	g_pwr_fet_op_register.value_b.CPMP_EN = 0;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206TurnDFetOn(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	g_pwr_fet_op_register.value_b.DFET_EN = 1;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206TurnDFetOff(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*turn Discharge FET off*/
	g_pwr_fet_op_register.value_b.DFET_EN = 0;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206TurnCFetOn(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Turn charge FET on*/
	g_pwr_fet_op_register.value_b.CFET_EN = 1;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206TurnCFetOff(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Turn charge FET off*/
	g_pwr_fet_op_register.value_b.CFET_EN = 0;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206TurnDFetOnCFetOn(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*turn FETs on*/
	g_pwr_fet_op_register.value_b.DFET_EN = 1;
	g_pwr_fet_op_register.value_b.CFET_EN = 1;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206TurnDFetOffCFetOn(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*turn DFET off and CFET on*/
	g_pwr_fet_op_register.value_b.DFET_EN = 0;
	g_pwr_fet_op_register.value_b.CFET_EN = 1;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206TurnDFetOnCFetOff(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*turn DFET off and CFET on*/
	g_pwr_fet_op_register.value_b.DFET_EN = 1;
	g_pwr_fet_op_register.value_b.CFET_EN = 0;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206TurnDFetOffCFetOff(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*turn DFET and CFET off*/
	g_pwr_fet_op_register.value_b.DFET_EN = 0;
	g_pwr_fet_op_register.value_b.CFET_EN = 0;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_alert_events 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetAlerts(TysCdrvRaa4892xx_Obj * const me, const bfe_alerts_masks_t * const p_alert_events) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;
	st_raa489206_events_masks_t *p_raa489206_masks = (st_raa489206_events_masks_t *) p_alert_events;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	/*Set the specified delays*/
	/*Fault delays*/
	g_fault_delay_register = p_raa489206_masks->fault_delays;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->fault_delay));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Discharge short current delay*/
	g_dsc_delay_register = p_raa489206_masks->dsc_delay;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->dsc_delay));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Overcurrent delays: Discharge and charge over-current*/
	g_oc_delay = p_raa489206_masks->oc_delay;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->oc_delay));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Load detect delay*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vreg_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	g_vregop_register.value_b.LD_DELAY = p_raa489206_masks->ld_delay;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vreg_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Current direction delay*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	g_ipackop_register.value_b.IDIR_DELAY = p_raa489206_masks->idir_delay;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Priority alerts*/
	g_priority_masks.value = p_raa489206_masks->priority_masks.value;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->priority_faults_mask));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*ETAUX alerts*/
	g_etaux_masks.value = p_raa489206_masks->etaux_masks.value;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->etaux_faults_mask));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Other alerts*/
	g_other_masks.value =  p_raa489206_masks->other_masks.value;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->other_faults_mask));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Balancing and charging alerts*/
	g_cb_masks.value = p_raa489206_masks->cb_masks.value;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->cb_status_masks));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*General status alerts*/
	g_status_masks.value = p_raa489206_masks->status_masks.value;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->status_masks));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Open-wire status alerts*/
	g_ow_masks.value = p_raa489206_masks->ow_masks.value;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->open_wire_mask));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);


	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param current_ma 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetDOC(TysCdrvRaa4892xx_Obj * const me, float current_ma) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	float current_mv = (current_ma) * (*(p_raa489206_ctrl->p_cfg->p_shunt_resistor));
	g_doc_threshold_register = VoltageToRegister(current_mv, s_vdoc_step_mv, s_vdoc_offset_mv);
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->discharge_overcurrent_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param current_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetCOC(TysCdrvRaa4892xx_Obj * const me, float current_ma) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	float current_mv = (current_ma) * (*(p_raa489206_ctrl->p_cfg->p_shunt_resistor));
	g_coc_threshold_register = VoltageToRegister(current_mv, s_vcoc_step_mv,  s_vcoc_offset_mv);
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->charge_overcurrent_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param current_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetDSC(TysCdrvRaa4892xx_Obj * const me, float current_ma) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	float current_mv = (current_ma) * (*(p_raa489206_ctrl->p_cfg->p_shunt_resistor));
	/*the 4-MSB are reserved*/
	g_dsc_threshold_register = (VoltageToRegister(current_mv, s_vdsc_step_mv,  s_vdsc_offset_mv)) & 0x0F;

	/*Minimum threshold is 0x01 = -40,167 mV. Section 5.5.1*/
	if (g_dsc_threshold_register == 0x00)
	{
			g_dsc_threshold_register = 0x01;
	}
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->discharge_short_current_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param cells_uv_th_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetCellUndevoltage(TysCdrvRaa4892xx_Obj * const me, float cells_uv_th_mv) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	g_vcell_uv_th_register = VoltageToRegister(cells_uv_th_mv, s_vcell_uv_vthstep_mv, s_vcell_uv_offset_mv);
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_undervoltage_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param cells_maxd_th_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetMaxVcellDeltaVoltage(TysCdrvRaa4892xx_Obj * const me, float cells_maxd_th_mv) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	g_vcell_max_delta_th = VoltageToRegister(cells_maxd_th_mv, s_vcell_max_delta_step_mv, s_vcell_max_delta_offset_mv);
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_max_delta_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param vpack_uv_th_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetVpackUndervoltage(TysCdrvRaa4892xx_Obj * const me, float vpack_uv_th_mv) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	g_vbat1_uv_th_register = VoltageToRegister(vpack_uv_th_mv, s_vbat1_uv_step_mv, s_vbat1_uv_offset_mv);
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_uv_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param cells_ov_th_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetCellOvervoltage(TysCdrvRaa4892xx_Obj * const me, float v_cells_ov_th_mv) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	g_vcell_ov_th_register = VoltageToRegister(v_cells_ov_th_mv, s_vcell_ov_vthstep_mv, s_vcell_ov_offset_mv);
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_overvoltage_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param vpack_ov_th_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetVpackOvervoltage(TysCdrvRaa4892xx_Obj * const me, float vpack_ov_th_mv) {
    e_bfe_err_t bfe_error = BFE_SUCCESS;
    st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

    BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

    g_vbat1_ov_th_register = VoltageToRegister(vpack_ov_th_mv, s_vbat1_ov_step_mv, s_vbat1_ov_offset_mv);
    bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_ov_th));

    BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

    return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param temperature 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetInternalOTWarning(TysCdrvRaa4892xx_Obj * const me, float war_temperature) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	g_iotw_th_register = TemperatureToRegister(war_temperature);
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->overtemperature_warning_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param veoc_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetVoltageEndOfCharge(TysCdrvRaa4892xx_Obj * const me, float veoc) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	g_veoc_th = VoltageToRegister(veoc, s_veoc_step_mv, s_veoc_offset_mv);

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->eoc_voltage_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param ieoc_ma 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetCurrentEndOfCharge(TysCdrvRaa4892xx_Obj * const me, float current_ma) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	float current_mv = (current_ma) * (*(p_raa489206_ctrl->p_cfg->p_shunt_resistor));

	g_ieoc_th = VoltageToRegister(current_mv, s_ieoc_step_mv, s_ieoc_offset_mv);

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->eoc_current_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param temperature 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetInternalOTFault(TysCdrvRaa4892xx_Obj * const me, float fault_temperature) {
    e_bfe_err_t bfe_error = BFE_SUCCESS;
    st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

    BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

    g_iotf_th_register = TemperatureToRegister(fault_temperature);
    bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->overtemperature_fault_th));

    BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

    return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param bfe_mode 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206SetMode(TysCdrvRaa4892xx_Obj * const me, e_bfe_mode_t bfe_mode) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	switch(bfe_mode)
	{
			case BFE_MODE_IDLE:

					g_scanop_register.value_b.SYS_MODE = RAA489206_SYSTEM_MODE_IDLE;

					break;

			case BFE_MODE_SCAN:

					g_scanop_register.value_b.SYS_MODE = RAA489206_SYSTEM_MODE_SCAN;

					break;

			case BFE_MODE_LOW_POWER_MODE:

					g_scanop_register.value_b.SYS_MODE = RAA489206_SYSTEM_MODE_LPM;

					break;

			case BFE_MODE_SHIP:

					g_scanop_register.value_b.SYS_MODE = RAA489206_SYSTEM_MODE_SHIP;

					break;

			default:

					return BFE_ERR_NONSUPPORTED_MODE;
	}

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_alert_events 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadAlerts(TysCdrvRaa4892xx_Obj * const me, bfe_alerts_masks_t * const p_alert_events) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;
	st_raa489206_events_masks_t *p_raa489206_masks = (st_raa489206_events_masks_t *) p_alert_events;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	/*Read the specified delays*/
	/*Fault delays*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->fault_delay));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_masks->fault_delays = g_fault_delay_register;

	/*Discharge short current delay*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->dsc_delay));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_masks->dsc_delay = g_dsc_delay_register;

	/*Overcurrent delays: Discharge and charge over-current*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->oc_delay));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_masks->oc_delay = g_oc_delay;

	/*Load detect delay*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vreg_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_masks->ld_delay = (e_raa489206_ld_delay_t)g_vregop_register.value_b.LD_DELAY;

	 /*Current direction delay*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->ipack_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_masks->idir_delay = g_ipackop_register.value_b.IDIR_DELAY;

	/*Priority alerts*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->priority_faults_mask));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_masks->priority_masks.value = g_priority_masks.value;

	/*ETAUX alerts*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->etaux_faults_mask));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_masks->etaux_masks.value = g_etaux_masks.value;

	/*Other alerts*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->other_faults_mask));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_masks->other_masks.value = g_other_masks.value ;

	/*Balancing and charging alerts*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->cb_status_masks));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_masks->cb_masks.value = g_cb_masks.value;

	/*General status alerts*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->status_masks));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_masks->status_masks.value = g_status_masks.value;

	/*Open-wire status alerts*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->open_wire_mask));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_raa489206_masks->ow_masks.value = g_ow_masks.value;

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param current_ma 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadDOC(TysCdrvRaa4892xx_Obj * const me, float * p_current_ma) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->discharge_overcurrent_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	float current_mv = RegisterToVoltage(g_doc_threshold_register, s_vdoc_step_mv, s_vdoc_offset_mv);

	*p_current_ma = (current_mv) / (*(p_raa489206_ctrl->p_cfg->p_shunt_resistor));

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param current_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadCOC(TysCdrvRaa4892xx_Obj * const me, float * p_current_ma) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->charge_overcurrent_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	float current_mv = RegisterToVoltage(g_coc_threshold_register, s_vcoc_step_mv, s_vcoc_offset_mv);

	*p_current_ma = (current_mv) / (*(p_raa489206_ctrl->p_cfg->p_shunt_resistor));

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param current_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadDSC(TysCdrvRaa4892xx_Obj * const me, float * p_current_ma) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->discharge_short_current_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	float current_mv = RegisterToVoltage(g_dsc_threshold_register, s_vdsc_step_mv, s_vdsc_offset_mv);

	*p_current_ma = (current_mv) / (*(p_raa489206_ctrl->p_cfg->p_shunt_resistor));

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param cells_uv_th_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadCellUndevoltage(TysCdrvRaa4892xx_Obj * const me, float * p_cells_uv_th_mv) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_undervoltage_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	*p_cells_uv_th_mv = RegisterToVoltage(g_vcell_uv_th_register, s_vcell_uv_vthstep_mv, s_vcell_uv_offset_mv);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param cells_maxd_th_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadMaxVcellDeltaVoltage(TysCdrvRaa4892xx_Obj * const me, float * p_cells_maxd_th_mv) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_max_delta_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	*p_cells_maxd_th_mv = RegisterToVoltage(g_vcell_max_delta_th, s_vcell_max_delta_step_mv, s_vcell_max_delta_offset_mv);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param vpack_uv_th_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadVpackUndervoltage(TysCdrvRaa4892xx_Obj * const me, float * p_vpack_uv_th_mv) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_uv_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	*p_vpack_uv_th_mv = RegisterToVoltage(g_vbat1_uv_th_register, s_vbat1_uv_step_mv, s_vbat1_uv_offset_mv);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param cells_ov_th_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadCellOvervoltage(TysCdrvRaa4892xx_Obj * const me, float * p_v_cells_ov_th_mv) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vcell_overvoltage_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	*p_v_cells_ov_th_mv = RegisterToVoltage(g_vcell_ov_th_register, s_vcell_ov_vthstep_mv, s_vcell_ov_offset_mv);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param vpack_ov_th_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadVpackOvervoltage(TysCdrvRaa4892xx_Obj * const me, float * p_vpack_ov_th_mv) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_ov_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	*p_vpack_ov_th_mv = RegisterToVoltage(g_vbat1_ov_th_register, s_vbat1_ov_step_mv, s_vbat1_ov_offset_mv);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param temperature 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadInternalOTWarning(TysCdrvRaa4892xx_Obj * const me, float * p_war_temperature) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->overtemperature_warning_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	*p_war_temperature = RegisterToTemperature(g_iotw_th_register);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param temperature 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadInternalOTFault(TysCdrvRaa4892xx_Obj * const me, float * p_fault_temperature) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->overtemperature_fault_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	*p_fault_temperature = RegisterToTemperature(g_iotf_th_register);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param veoc_mv 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadVoltageEndOfCharge(TysCdrvRaa4892xx_Obj * const me, float * p_veoc) {
    e_bfe_err_t bfe_error = BFE_SUCCESS;
    st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

    BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

    bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->eoc_voltage_th));

    BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

    *p_veoc = RegisterToVoltage(g_veoc_th, s_veoc_step_mv, s_veoc_offset_mv   );

    return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param ieoc_ma 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadCurrentEndOfCharge(TysCdrvRaa4892xx_Obj * const me, float * p_current_ma) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->eoc_current_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	float current_mv = RegisterToVoltage(g_ieoc_th, s_ieoc_step_mv, s_ieoc_offset_mv   );

	*p_current_ma = (current_mv) / (*(p_raa489206_ctrl->p_cfg->p_shunt_resistor));

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_lpm_options 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ConfigLowPowerMode(TysCdrvRaa4892xx_Obj * const me, bfe_lpm_cfg_t * const p_lpm_options) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t *) me->u_bfe_control;
	st_raa489206_lpm_cfg_t *p_raa4892206_lpm_cfg = (st_raa489206_lpm_cfg_t*) p_lpm_options;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	/*Set low power timer*/
	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	g_scanop_register.value_b.LPT = p_raa4892206_lpm_cfg->LPM_TIMER;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Set low power regulator*/

	meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vreg_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	g_vregop_register.value_b.LP_REG = p_raa4892206_lpm_cfg->REG_TYPE;
	g_vregop_register.value_b.COMM_TIMEOUT = (uint8_t) (p_raa4892206_lpm_cfg->COM_TO);

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vreg_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*set communication time-out*/

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	g_vbatop_register.value_b.COM_TIMEOUT_EN = p_raa4892206_lpm_cfg->COMTO_EN;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*set load detection in low power mode*/

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->load_charge_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	g_load_charge_oper.value_b.LDLP = p_raa4892206_lpm_cfg->LDLP;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->load_charge_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206StartLowPowerMode(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t*) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	g_scanop_register.value_b.SYS_MODE = RAA489206_SYSTEM_MODE_LPM;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));;

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_information 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206GetDieInformation(TysCdrvRaa4892xx_Obj * const me, st_bfe_information_t * p_information) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t*) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->die_information));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	p_information->device_id = g_dieinformation_register.value_b.ID;
	p_information->die_revision = g_dieinformation_register.value_b.REVISION;
	p_information->manufacturing_id = 0x00;
	p_information->nickname = BFE_NICKNAME_RAA206;

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param p_bfe_register 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadRegister(TysCdrvRaa4892xx_Obj * const me, st_bfe_register_t * const p_bfe_register) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t*) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	if (p_bfe_register->p_value == NULL)
	{
			return BFE_ERR_INVALID_POINTER;
	}

	bfe_error = p_raa489206_ctrl->p_readRegisterValues(me, p_bfe_register->address, p_bfe_register->p_value, p_bfe_register->size, p_raa489206_ctrl->use_crc);

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param me 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206ReadAllRegisters(TysCdrvRaa4892xx_Obj * const me) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t*) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	uint8_t register_bank_size = sizeof( *(p_raa489206_ctrl->p_regs)) / sizeof(st_bfe_register_t);
	uint8_t reg_count = 0;

	static uint8_t s_registers_array[RAA489206_REGISTER_NUMBER_OF_REGISTERS];

	WaitUntilFree(me, p_raa489206_ctrl, &s_device_busy);

#if (COMM_SPI == 1)
	if (p_raa489206_ctrl->use_crc)
	{

			bfe_error = ReadSpiCrcCommand(me, RAA489206_CRC_COMMAND_ALL_REGISTERS, &(s_registers_array[0]), RAA489206_REGISTER_NUMBER_OF_REGISTERS);

	}

	else
	{
			bfe_error = ReadSpiAllRegistersNoCrc(me, &(s_registers_array[0]));

//        for (st_bfe_register_t *p_reg = (st_bfe_register_t *) p_raa489206_ctrl->p_regs; reg_count < register_bank_size ; p_reg++ )
//        {
//
//            bfe_error = R_RAA489206_ReadRegister(p_raa489206_ctrl, p_reg);
//
//            BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
//
//            reg_count++;
//        }
//
//        BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);
	}
#else
//	bfe_error = ReadI2c(0x00, &(s_registers_array[0]), RAA489206_REGISTER_NUMBER_OF_REGISTERS, true);
#endif

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	for (st_bfe_register_t *p_reg = (st_bfe_register_t *) p_raa489206_ctrl->p_regs; reg_count < register_bank_size ; p_reg++ )
	{

			for (uint8_t i = 0; i < p_reg->size; i++ )
			{
					*(p_reg->p_value + p_reg->size - i - 1) = s_registers_array[p_reg->address + i];
			}

			reg_count++;
	}

	if (s_device_busy == true)
	{
			return BFE_WARN_BUSY;
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param me 
 * @param bfe_register 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t Raa489206WriteRegister(TysCdrvRaa4892xx_Obj * const me, const st_bfe_register_t * const p_bfe_register) {
	if (p_bfe_register->type != READ_WRITE)
	{
			return BFE_ERR_READ_ONLY_REGISTER;
	}

	e_bfe_err_t bfe_error = BFE_SUCCESS;
	st_raa489206_instance_ctrl_t *p_raa489206_ctrl = (st_raa489206_instance_ctrl_t*) me->u_bfe_control;

	BFE_ERROR_RETURN( p_raa489206_ctrl->init == true, BFE_ERR_DEVICE_NOT_INITIALIZED);

	st_raa489206_extended_cfg_t *p_raa489206_cfg = (st_raa489206_extended_cfg_t *) (p_raa489206_ctrl->p_cfg->p_extend);

	bfe_error = p_raa489206_ctrl->p_writeRegisterValues(me, p_bfe_register->address, p_bfe_register->p_value, p_bfe_register->size,
																										 p_raa489206_cfg->use_crc);

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	if (p_raa489206_ctrl->read_after_write)
	{

			uint8_t * p_reg_value = p_bfe_register->p_value;

			for (uint8_t raw_failed = 0; raw_failed < p_raa489206_ctrl->p_cfg->num_read_after_write; raw_failed++ )
			{
					memset(&s_raw_buff[0], 0x00, BUFF_LEN);

					bfe_error = p_raa489206_ctrl->p_readRegisterValues(me, p_bfe_register->address, s_raw_buff, p_bfe_register->size,
																														 p_raa489206_cfg->use_crc);

					BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

					/*Read after write verification: the register value is read and compared with the value that should have been
					 * written to verify its correctness*/

					for (uint8_t i = 0; i < p_bfe_register->size; i++ )
					{
							if ((p_reg_value[i]) != s_raw_buff[i])
							{
									bfe_error = BFE_ERR_COM_READ_AFTER_WRITE_FAILED;

									break;
							}

					}

					if (bfe_error == BFE_SUCCESS)
					{
							return BFE_SUCCESS;
					}
			}
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 */
static void SpiCallback(void) {
	s_spi_event_flag = BFE_COMM_SUCCESS;
	//TODO:
//	if (p_args->event == SPI_EVENT_TRANSFER_COMPLETE)
//	{
//			s_spi_event_flag = BFE_COMM_SUCCESS;
//	}
//	else
//	{
//			s_spi_event_flag = BFE_ERR_COMM_FAULT;
//	}
}

/**
 * @brief 
 * 
 */
//static void I2cCallback(void) {

//}

/**
 * @brief 
 * 
 * @param voltage_mv 
 * @param step 
 * @param offset 
 * @return uint8_t 
 */
static uint8_t VoltageToRegister(float voltage, const float step, const float offset) {
	double reg = floor((voltage - offset) / step);

	if (reg > (double) 0xFF)
	{
			return 0xFF;
	}

	if (reg < 0)
	{
			return 0x00;
	}

	return (uint8_t) reg;
}

/**
 * @brief 
 * 
 * @param reg_val 
 * @param step 
 * @param offset 
 * @return float 
 */
static float RegisterToVoltage(uint16_t reg_val, const float step, const float offset) {
	float voltage = (float) ((reg_val * step) + offset);
	return voltage;
}

/**
 * @brief 
 * 
 * @param deg_val 
 * @return uint8_t 
 */
static uint8_t TemperatureToRegister(float deg_val) {
	double celsius = floor(((-2.95) * 0.0001 * (double)deg_val * (double)deg_val) - (1.15975 * (double)deg_val) + (182.23));

	if (celsius > (double) 0xFF)
	{
			return 0xFF;
	}

	if (celsius < 0)
	{
			return 0x00;
	}

	return (uint8_t)celsius;
}

/**
 * @brief 
 * 
 * @param reg_val 
 * @return float 
 */
static float RegisterToTemperature(uint8_t reg_val) {
	float temperature = (float)(((-1.82) * 0.0001 * reg_val * reg_val) - (0.79605 * reg_val) + 151.11);

	return temperature;
}

/**
 * @brief 
 * 
 * @param address 
 * @param p_values 
 * @param num_values 
 * @param use_crc 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t WriteSpi(TysCdrvRaa4892xx_Obj * const me, uint8_t reg_address, uint8_t const * p_values, uint16_t num_values, bool use_crc) {
//	fsp_err_t fsp_error = FSP_SUCCESS;

	/* Cleaning tx buffer */
	memset(&s_tx_buff[0], 0x00, BUFF_LEN);

	if (use_crc == true)
	{
			s_spi_add_crc.rw_bits.rw = 0;
			s_tx_buff[0] = s_spi_add_crc.address_byte;
	}
	else
	{
			s_spi_add_no_crc.rw_bits.rw = 0;
			s_tx_buff[0] = s_spi_add_no_crc.address_byte;
	}

	uint8_t count = 0;
	uint8_t spi_bytes = 3;

	for (uint8_t const * p_i = p_values + num_values - 1; p_i >= p_values; p_i-- )
	{
			s_tx_buff[1] = reg_address + count;
			s_tx_buff[2] = *p_i;

			if (use_crc == true)
			{

					u_crc_t spi_crc = {.crc_word = 0x0000};
					spi_crc.crc_word = CalculateCrc(3, s_tx_buff);
					s_tx_buff[3] = spi_crc.crc_b.msb;
					s_tx_buff[4] = spi_crc.crc_b.lsb;
					spi_bytes = 5;
			}

			/* Reseting master_event flag before starting SPI transmission*/
			s_spi_event_flag =  BFE_FSP_SUCESS;

#if (SCI_SPI == 1)
			fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, s_ss_pin, BSP_IO_LEVEL_LOW);

			BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);
#endif
			
			meGpio_Reset_(me->u_cs);
			meSpi_Transmit_(me->u_spi, s_tx_buff, spi_bytes, 10);
//			fsp_error = sp_spi->p_api->write(sp_spi->p_ctrl, s_tx_buff, spi_bytes, SPI_BIT_WIDTH_8_BITS);

//			BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

			/* Wait until the SPI transmission completes */
//			s_wait_count = s_max_wait_count;

//			while (s_spi_event_flag != BFE_COMM_SUCCESS)
//			{
//					s_wait_count--;

//					if (s_wait_count == s_min_wait_count)
//					{
//							/* Return time out error if SPI operation fails to complete */

//							return BFE_ERR_COMM_TIMEOUT;
//					}
//					else if (s_spi_event_flag == BFE_ERR_COMM_FAULT)
//					{
//							return BFE_ERR_COMM_FAULT;
//					}
//					else
//					{
//							/* Do nothing */
//					}
//			}

#if (SCI_SPI == 1)
			fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, s_ss_pin, BSP_IO_LEVEL_HIGH);

			BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);
#endif
			meGpio_Set_(me->u_cs);
			count++;
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param address 
 * @param p_values 
 * @param num_values 
 * @param use_crc 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t ReadSpi(TysCdrvRaa4892xx_Obj * const me, uint8_t reg_address, uint8_t * p_values, uint16_t num_values, bool use_crc) {
//	fsp_err_t fsp_error = FSP_SUCCESS;
	uint16_t spi_bytes;
	uint8_t rx_offset = 2; /*1-byte slave address + 1-byte command*/

	/* Cleaning buffers */
	memset(&s_tx_buff[0], 0x00 ,BUFF_LEN);
	memset(&s_rx_buff[0], 0x00, BUFF_LEN);

	if (use_crc)
	{
			s_spi_add_crc.rw_bits.rw = 1;
			s_tx_buff[0] = s_spi_add_crc.address_byte;
			spi_bytes = 3;
	}

	else
	{
			s_spi_add_no_crc.rw_bits.rw = 1;
			s_tx_buff[0] = s_spi_add_no_crc.address_byte;
			spi_bytes = 2 + num_values;
	}

	for (uint8_t i = 0; i < num_values; i++ )
	{
			if (use_crc)
			{
					s_tx_buff[1] = reg_address + i;
					u_crc_t mcu_crc = {.crc_word = 0x0000};
					mcu_crc.crc_word = CalculateCrc(2, s_tx_buff);
					s_tx_buff[2] = mcu_crc.crc_b.msb;
					s_tx_buff[3] = mcu_crc.crc_b.lsb;
					rx_offset = 4; /* 2-byte MCU CRC*/
					spi_bytes = 7;/* num_values += 2-byte MCU CRC + 2-byte Device CRC*/
			}

			else
			{
					s_tx_buff[1] = reg_address;
			}

			/* Reseting master_event flag before starting SPI transmission*/
			s_spi_event_flag =  BFE_FSP_SUCESS;

#if (SCI_SPI == 1)
			fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, s_ss_pin, BSP_IO_LEVEL_LOW);

			BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);
#endif
			meGpio_Reset_(me->u_cs);
			meSpi_TransmitReceive_(me->u_spi, s_tx_buff, s_rx_buff, spi_bytes, 10);
//			fsp_error = sp_spi->p_api->writeRead(sp_spi->p_ctrl, s_tx_buff, s_rx_buff, spi_bytes, SPI_BIT_WIDTH_8_BITS);

//			BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

			/* Wait until the SPI transmission completes */
			s_wait_count = s_max_wait_count;

//			while (s_spi_event_flag != BFE_COMM_SUCCESS)
//			{
//					s_wait_count--;

//					if (s_wait_count == s_min_wait_count)
//					{
//							/* Return time out error if SPI operation fails to complete */

//							return BFE_ERR_COMM_TIMEOUT;
//					}
//					else if (s_spi_event_flag == BFE_ERR_COMM_FAULT)
//					{
//							return BFE_ERR_COMM_FAULT;
//					}
//					else
//					{
//							/* Do nothing */
//					}
//			}

#if (SCI_SPI == 1)
			fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, s_ss_pin, BSP_IO_LEVEL_HIGH);

			BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);
#endif
			meGpio_Set_(me->u_cs);
			
			if (use_crc)
			{
					u_crc_t mcu_crc = {.crc_word = 0x0000};
					mcu_crc.crc_word = CalculateCrc(1, &s_rx_buff[rx_offset]);
					u_crc_t rx_crc = {.crc_word = 0x0000};
					rx_crc.crc_b.msb = s_rx_buff[rx_offset + 1];
					rx_crc.crc_b.lsb = s_rx_buff[rx_offset + 2];

					if (mcu_crc.crc_word != rx_crc.crc_word)
					{
							return BFE_ERR_COMM_WRONG_CRC;
					}

					p_values[num_values - i - 1] = s_rx_buff[rx_offset];
			}

			else
			{
					for (i = 0; i < num_values; i++ )
					{
							p_values[num_values - i - 1] = s_rx_buff[rx_offset + i];
					}

					break;
			}
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param p_values 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t ReadSpiAllRegistersNoCrc(TysCdrvRaa4892xx_Obj * const me, uint8_t * p_values) {
//	fsp_err_t fsp_error = FSP_SUCCESS;
	uint16_t spi_bytes;
	uint8_t rx_offset = 2; /*1-byte slave address + 1-byte command*/

	/* Cleaning buffers */
	memset(&s_tx_buff[0], 0x00 ,BUFF_LEN);
	memset(&s_rx_buff[0], 0x00, BUFF_LEN);


	s_spi_add_no_crc.rw_bits.rw = 1;
	s_tx_buff[0] = s_spi_add_no_crc.address_byte;
	spi_bytes = 2 + RAA489206_REGISTER_NUMBER_OF_REGISTERS;


	s_tx_buff[1] = 0x00;
	/* Reseting master_event flag before starting SPI transmission*/
	s_spi_event_flag =  BFE_FSP_SUCESS;

#if (SCI_SPI == 1)
	fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, s_ss_pin, BSP_IO_LEVEL_LOW);

	BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);
#endif
	meGpio_Reset_(me->u_cs);
	meSpi_TransmitReceive_(me->u_spi, s_tx_buff, s_rx_buff, spi_bytes, 10);
//	fsp_error = sp_spi->p_api->writeRead(sp_spi->p_ctrl, s_tx_buff, s_rx_buff, spi_bytes, SPI_BIT_WIDTH_8_BITS);

//	BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

	/* Wait until the SPI transmission completes */
//	s_wait_count = s_max_wait_count;

//	while (s_spi_event_flag != BFE_COMM_SUCCESS)
//	{
//			s_wait_count--;

//			if (s_wait_count == s_min_wait_count)
//			{
//					/* Return time out error if SPI operation fails to complete */

//					return BFE_ERR_COMM_TIMEOUT;
//			}
//			else if (s_spi_event_flag == BFE_ERR_COMM_FAULT)
//			{
//					return BFE_ERR_COMM_FAULT;
//			}
//			else
//			{
//					/* Do nothing */
//			}
//	}

#if (SCI_SPI == 1)
	fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, s_ss_pin, BSP_IO_LEVEL_HIGH);

	BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);
#endif
	meGpio_Set_(me->u_cs);

	for (uint8_t i = 0; i < RAA489206_REGISTER_NUMBER_OF_REGISTERS; i++ )
	{
			p_values[i] = s_rx_buff[rx_offset + i];
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param address 
 * @param p_values 
 * @param num_values 
 * @param use_crc 
 * @return e_bfe_err_t 
 */
//static e_bfe_err_t WriteI2c(uint8_t address, uint8_t const * p_values, uint16_t num_values, bool use_crc) {
//	return BFE_ERR_FSP_ERROR;
//}

/**
 * @brief 
 * 
 * @param address 
 * @param p_values 
 * @param num_values 
 * @param use_crc 
 * @return e_bfe_err_t 
 */
//static e_bfe_err_t ReadI2c(uint8_t address, uint8_t * p_values, uint16_t num_values, bool use_crc) {
//	return BFE_ERR_FSP_ERROR;
//}

/**
 * @brief 
 * 
 * @return e_bfe_err_t 
 */
//static e_bfe_err_t ValidateI2cEvent(void) {
//	return BFE_ERR_FSP_ERROR;
//}

/**
 * @brief 
 * 
 * @param crc_command 
 * @param p_values 
 * @param num_values 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t ReadSpiCrcCommand(TysCdrvRaa4892xx_Obj * const me, uint8_t crc_command, uint8_t * p_values, uint16_t num_values) {
//	fsp_err_t fsp_error = FSP_SUCCESS;

	/* Cleaning buffers */
	memset(&s_tx_buff[0], 0x00 ,BUFF_LEN);
	memset(&s_rx_buff[0], 0x00, BUFF_LEN);


	s_spi_add_crc.rw_bits.rw = 1;
	s_tx_buff[0] = s_spi_add_crc.address_byte;
	s_tx_buff[1] = crc_command;
	u_crc_t mcu_crc = {.crc_word = 0x0000};
	mcu_crc.crc_word = CalculateCrc(2, s_tx_buff);
	s_tx_buff[2] = mcu_crc.crc_b.msb;
	s_tx_buff[3] = mcu_crc.crc_b.lsb;

	/* Reseting master_event flag before starting SPI transmission*/
	s_spi_event_flag =  BFE_FSP_SUCESS;

#if (SCI_SPI == 1)
			fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, s_ss_pin, BSP_IO_LEVEL_LOW);

			BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);
#endif
	meGpio_Reset_(me->u_cs);
	meSpi_TransmitReceive_(me->u_spi, s_tx_buff, s_rx_buff, num_values + 6, 10);
//	fsp_error = sp_spi->p_api->writeRead(sp_spi->p_ctrl, s_tx_buff, s_rx_buff, num_values + 6, SPI_BIT_WIDTH_8_BITS);

//	BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);

	/* Wait until the SPI transmission completes */
	s_wait_count = s_max_wait_count;

	while (s_spi_event_flag != BFE_COMM_SUCCESS)
	{
			s_wait_count--;

			if (s_wait_count == s_min_wait_count)
			{
					/* Return time out error if SPI operation fails to complete */

					return BFE_ERR_COMM_TIMEOUT;
			}
			else if (s_spi_event_flag == BFE_ERR_COMM_FAULT)
			{
					return BFE_ERR_COMM_FAULT;
			}
			else
			{
					/* Do nothing */
			}
	}

#if (SCI_SPI == 1)
			fsp_error = sp_raa489206_ctrl->p_ioport->p_api->pinWrite(sp_raa489206_ctrl->p_ioport->p_ctrl, s_ss_pin, BSP_IO_LEVEL_HIGH);

			BFE_ERROR_RETURN(fsp_error == FSP_SUCCESS, BFE_ERR_FSP_ERROR);
#endif
	meGpio_Set_(me->u_cs);
	
	mcu_crc.crc_word = 0x0000;
	mcu_crc.crc_word = CalculateCrc(num_values, &s_rx_buff[4]);
	u_crc_t rx_crc = {.crc_word = 0x0000};
	rx_crc.crc_b.msb = s_rx_buff[num_values + 4];
	rx_crc.crc_b.lsb = s_rx_buff[num_values + 5];

	if (rx_crc.crc_word == 0x0000)
	{
			return BFE_ERR_COMM_NO_COMMUNICATION;
	}

	if (mcu_crc.crc_word != rx_crc.crc_word)
	{
			return BFE_ERR_COMM_WRONG_CRC;
	}

	for (uint16_t i = 0; i < num_values; i++ )
	{
			p_values[i] = s_rx_buff[i + 4];
	}

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param p_raa489206_ctrl 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t ExecuteStartupSequence(TysCdrvRaa4892xx_Obj * const me, st_raa489206_instance_ctrl_t *p_raa489206_ctrl) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;


	/*Wait until voltages stabilize*/
	meDelay_ms_(RAA489206_VSTABLE_DELAY_MS);
//	R_BSP_SoftwareDelay(RAA489206_VSTABLE_DELAY_MS, BSP_DELAY_UNITS_MILLISECONDS);

	/*Execute a hard reset by clearing device reset pin for 50ms */
	bfe_error = meBfe_Reset_(me, BFE_RESET_TYPE_HARD);

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Wait for the whole power-up sequence to finish (20ms Max)*/
	meDelay_ms_(RAA489206_STARTUP_DELAY_MS);
//	R_BSP_SoftwareDelay(RAA489206_STARTUP_DELAY_MS, BSP_DELAY_UNITS_MILLISECONDS);

	/*Read all registers*/
	bfe_error = meBfe_ReadAllRegisters_(me);

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*Set GIOP to 0*/
	g_gpio_alrt_op.value_b.GPIO_STATUS = 0x00;

	meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->gpio_alrt_operation));

	/* Compare registers values with reset values*/
	bfe_error = CompareResetValues(p_raa489206_ctrl->p_regs);

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param p_raa489206_ctrl 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t ExecuteBasicInit(TysCdrvRaa4892xx_Obj * const me, st_raa489206_instance_ctrl_t *p_raa489206_ctrl) {
	e_bfe_err_t bfe_error = BFE_SUCCESS;

	/*1. Set Idle mode*/
	g_scanop_register.value_b.SYS_MODE = RAA489206_SYSTEM_MODE_IDLE;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->scan_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*2. Disable communication timer*/
	g_vbatop_register.value_b.COM_TIMEOUT_EN = 0;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vbat1_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*3. Select the strong regulator for low power mode*/
	g_vregop_register.value_b.LP_REG = 1;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->vreg_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*4. Unmask busy bit to assert ALERT pin*/
	g_other_masks.value_b.BUSYM = 0;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->other_faults_mask));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*5. Set the internal over-temperature warning threshold to ~85°C, this corresponds to 0x51 */
	g_iotw_th_register = 0x51;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->overtemperature_warning_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*6. Set the internal over-temperature fault threshold to ~95°C, this corresponds to 0x45 */
	g_iotf_th_register = 0x45;
	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->overtemperature_fault_th));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*7. Select the cells that exist in the BMS*/
	g_cells_select_register = p_raa489206_ctrl->cells_select;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->cell_select));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	/*8. Enable charge pump if the init option has been selected*/

	st_raa489206_extended_cfg_t * p_ext_cfg = (st_raa489206_extended_cfg_t *) p_raa489206_ctrl->p_cfg->p_extend;

	if (p_ext_cfg->enable_chr_pump_init == 1)
	{
			bfe_error = meBfe_ReadRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			g_pwr_fet_op_register.value_b.CPMP_EN = 1;
			bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->power_fet_operation));

			BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

			meDelay_ms_(BFE_RAA489206_CHARGE_PUMP_WAIT_TIME_MS);
//			R_BSP_SoftwareDelay(BFE_RAA489206_CHARGE_PUMP_WAIT_TIME_MS, BSP_DELAY_UNITS_MILLISECONDS);
	}

	/*9. Set Scan select to 1 (single scan mode)*/

	g_globalop_register.value_b.SCAN_SEL = 1;

	bfe_error = meBfe_WriteRegister_(me, &(p_raa489206_ctrl->p_regs->global_operation));

	BFE_ERROR_RETURN(bfe_error == BFE_SUCCESS, bfe_error);

	return BFE_SUCCESS;
}

/**
 * @brief 
 * 
 * @param p_regs 
 * @return e_bfe_err_t 
 */
static e_bfe_err_t CompareResetValues(st_raa489206_system_registers_t *p_raa489206_registers) {
	uint8_t register_bank_size = sizeof( *p_raa489206_registers) / sizeof(st_bfe_register_t);
	uint8_t reg_count = 0;
	e_bfe_err_t bfe_error = BFE_SUCCESS;

	for (st_bfe_register_t *p_reg = (st_bfe_register_t *) p_raa489206_registers; reg_count < register_bank_size; p_reg++ )
	{
			reg_count++;

			if (p_reg->p_reset_value == NULL)
			{
					continue;
			}
			for (uint8_t i = 0; i < p_reg->size; i++ )
			{
					if ((*(p_reg->p_reset_value + i)) != (*(p_reg->p_value + i)))
					{
							bfe_error = BFE_ERR_REGISTER_RESET_UNMATCHED;
					}
			}
	}

	return bfe_error;
}

/**
 * @brief 
 * 
 * @param p_raa489206_ctrl 
 * @param p_is_busy 
 */
static inline void WaitUntilFree(TysCdrvRaa4892xx_Obj * const me, st_raa489206_instance_ctrl_t *p_raa489206_ctrl, bool *p_is_busy) {
	*p_is_busy = true;
	e_bfe_err_t bfe_error = BFE_SUCCESS;

	meDelay_ms_(1);
//	R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MILLISECONDS); /*Give the device some time to assert the pin*/
	bfe_error = meBfe_IsBusy_(me, p_is_busy);

	BFE_ERROR_VOID(bfe_error == BFE_SUCCESS);

	if ((*p_is_busy) == false)
	{
			return;
	}

	/*Pool the Alert pin to determine whether the device is busy. This avoids using requesting too often the device over the communication
	 * interface, which may keep it too busy and increase its power consumption*/
	uint8_t readLevel = 0;
//	bsp_io_level_t readLevel = BSP_IO_LEVEL_LOW;
	uint32_t wait_busy_count = s_max_wait_busy_ms;
	uint8_t read_busy_count = 0;

	while (wait_busy_count != s_min_wait_count)
	{
			wait_busy_count--;
			read_busy_count++;

			meGpio_Read_(me->u_alert, &readLevel);
//			p_raa489206_ctrl->p_ioport->p_api->pinRead(p_raa489206_ctrl->p_ioport->p_ctrl, p_raa489206_ctrl->alert_pin, &readLevel);

			if (readLevel == 1)
			{
					break;
			}

			/*Read BUSY bit every Xms*/
			if (read_busy_count == s_read_busy_period)
			{
					bfe_error = meBfe_IsBusy_(me, p_is_busy);

					BFE_ERROR_VOID(bfe_error == BFE_SUCCESS);

					if ((*p_is_busy) == false)
					{
							return;
					}

					read_busy_count = 0;
			}
			meDelay_ms_(1);
//			R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MILLISECONDS);
	}

	/* Read value of busy bit before returning*/
	meBfe_IsBusy_(me, p_is_busy);
}

/**
 * @brief 
 * 
 * @param numbytes 
 * @param input_buf 
 * @return uint16_t 
 */
static uint16_t CalculateCrc(uint16_t numbytes, const uint8_t * const p_input_buf) {
	uint16_t i;
	uint8_t j;
	bool xor_flag;
	uint16_t crc_val = 0xFFFF;

	for (i = 0; i < numbytes; i++ )
	{
			uint64_t long_value = p_input_buf[i];
			crc_val = (uint16_t)(crc_val ^ long_value);  /*XOR data with CRC lower byte*/

			for (j = 0; j < 8; j++ )  /*shift for each bit & check for XOR*/
			{
					xor_flag = 0;

					if (crc_val & 0x0001) /*get the overflow flag, i.e., CRC LSB*/
					{
							xor_flag = 1;
					}

					crc_val = crc_val >> 1;  /*shift right 1 bit*/

					if (xor_flag)
					{
							crc_val = (crc_val ^ 0x8408);  /*XOR with poly*/
					}
			}
	}

	crc_val = crc_val ^ 0xFFFF;  /*xor the final crc*/

	return (crc_val);
}

 /************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
