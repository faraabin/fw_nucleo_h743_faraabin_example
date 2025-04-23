/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_bfe.h
 * Version      : 1.1
 * Description  : This file defines the Application Program Interface (API) that shall be implemented by Battery Front
 *                Ends (BFEs) implementations to provide Battery Management Systems (BMSs) with common services and
 *                functions required to execute theirs tasks.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 24.08.2021 1.00    Internal Release
 *         : 05.11.2021 1.10    Release
 *         : 24.01.2023 2.0     SOC application and CB commands
 *********************************************************************************************************************/

#ifndef R_BFE_API_H
#define R_BFE_API_H

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

#define BFE_API_VERSION_MAJOR   (1U)
#define BFE_API_VERSION_MINOR   (0U)

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/** Driver configuration: high or low side driver**/
typedef enum e_bfe_driver_configuration
{
    BFE_DRIVER_HIGH_SIDE,
    BFE_DRIVER_LOW_SIDE,
} e_bfe_driver_configuration_t;

/** Power configuration: series or parallel**/
typedef enum e_bfe_fet_configuration
{
    BFE_FET_CONFIG_SERIES,   //either charger or load can be connected
    BFE_FET_CONFIG_PARALLEL, // Load and charger are allowed at the same
} e_bfe_fet_configuration_t;

/** Communication peripheral to read/write operations on the BFE. */
typedef enum e_bfe_communication_peripheral
{
    BFE_COMMUNICATION_INTERFACE_SPI, // Serial Peripheral Interface
    BFE_COMMUNICATION_INTERFACE_I2C, // Inter-Chip Communication
    BFE_COMMUNICATION_SINGLE_WIRE,   // Single wire
    BFE_COMMUNICATION_INTERFACE_SCI, // Serial Communication Interface
    BFE_COMMUNICATION_INTERFACE_BT,  // Bluetooth
} e_bfe_comm_peripheral_t;

/** Die nickname*/
typedef enum e_bfe_nickname
{
    BFE_NICKNAME_RAA206,
    BFE_NICKNAME_RAA489206,
    BFE_NICKNAME_GUPPY,
    BFE_NICKNAME_ISL208,
} e_bfe_nickname_t;

/** Common Die information structure */
typedef struct st_bfe_information
{
    uint8_t die_revision;       ///< Die revision
    uint8_t manufacturing_id;   ///< Manufacturing ID
    uint8_t device_id;          ///< API minor version
    e_bfe_nickname_t nickname;    ///< Device nickname
} st_bfe_information_t;

/** Register type/rights to verify whether a register may be written or read */
typedef enum e_register_type{
    READ = 0,
    READ_WRITE
} e_register_type_t;

/** Generic BFE register: address= register address, type=R/R_W, p_value pointer to the value(s), size=number of bytes,
 * p_reset_value= pointer to the default value (used for self-diagnosis after reset)*/
typedef struct st_bfe_register{

    uint8_t address;
    e_register_type_t type;
    uint8_t * const p_value;
    const uint8_t * const p_reset_value;
    uint8_t size;
} st_bfe_register_t;

/** Features supported by the BFE*/
typedef union u_bfe_features{

    uint32_t bfe_features_bits;

    uint8_t v_cells        : 1;        ///> Cells voltage
    uint8_t v_pack         : 1;        ///> Battery pack voltage
    uint8_t i_pack         : 1;        ///> Battery pack current
    uint8_t v_bat          : 1;        ///> Vbat voltage, which powers the device
    uint8_t v_cc           : 1;        ///> Regulated voltage, e.g., 3.3/5.5 V
    uint8_t low_side       : 1;        ///> Low-side FETs drivers configuration
    uint8_t high_side      : 1;        ///> High-side FETs drivers configuration
    uint8_t int_temp       : 1;        ///> internal temperature
    uint8_t ext_temp       : 2;        ///> Number of external temperature inputs 2-bit binary
    uint8_t crc            : 1;        ///> CRC
    uint8_t gpios          : 2;        ///> Number General Purpose I/O pins
    uint8_t low_power_mode : 1;        ///> Low power mode LPM
    uint8_t weak_regulator : 1;        ///> Weak regulator in LPM that provides low current
    uint8_t adc            : 1;        ///> Analog-To-Digital Converter
    uint8_t i2c            : 1;        ///> Inter-Chip Communication interface
    uint8_t spi            : 1;        ///> Serial Peripheral Interface
    uint8_t s_wire         : 1;        ///> One wire communication interface
    uint8_t blow_fuse      : 1;        ///> Pin to blow external fuse
    uint8_t cell_balancing : 1;        ///> Cell balancing capability
    uint8_t ch_detector    : 1;        ///> Charge detection circuit
    uint8_t load_detector  : 1;        ///> Load detection circuit
    uint8_t i_integrator   : 1;        ///> current integrator
    uint8_t scc_detection  : 1;        ///> short circuit detection
    uint8_t coc_detection  : 1;        ///> charge over-current detection
    uint8_t dco_detection  : 1;        ///> discharge over-current detection
    uint8_t mosfet_control : 1;        ///> FETs driver
    uint8_t rtc_function   : 1;        ///> Real Time Clock support
    uint8_t calibration    : 1;        ///> calibration procedure
    uint8_t ow_aux         : 2;        ///> open wire test function for pins

} u_bfe_features_t;

/** BFE error codes */
typedef enum e_bfe_err
{
    BFE_SUCCESS = 0,

    BFE_ERR_ASSERTION             = 1,                      ///< A critical assertion has failed
    BFE_ERR_INVALID_POINTER       = 2,                      ///< Pointer points to invalid memory location
    BFE_ERR_INVALID_ARGUMENT      = 3,                      ///< Invalid input parameter
    BFE_ERR_INVALID_NUMARGUMENTS  = 4,                      ///< Invalid number of arguments
    BFE_ERR_INVALID_REGISTER      = 5,                      ///< Register does not exist
    BFE_ERR_READ_ONLY_REGISTER    = 6,                      ///< read-only register cannot be written
    BFE_ERR_INVALID_STATE         = 7,                      ///< state is invalid
    BFE_ERR_UNMATCHED_REGISTERS   = 8,                      ///< MCU and device regoisters do not match
    BFE_ERR_UNSUPPORTED_FEATURE   = 9,                      ///< Feature or function is not supported by the BFE
    BFE_ERR_DEVICE_BUSY           = 10,                      ///< Device is currently busy
    BFE_ERR_DEVICE_NOT_INITIALIZED = 11,                    ///< Device has not been initialized
    BFE_ERR_NOT_ENOUGH_MEMORY      = 12,                     ///< The caller has not assigned enough
    BFE_ERR_REGISTER_RESET_UNMATCHED = 13,                  ///< The expected reset value does not match the actual register value
    BFE_ERR_INV_REG_SIZE         = 14,                      ///< Unsupported register size
    BFE_ERR_NONSUPPORTED_MODE = 15,                    ///< Selected device mode is not supported
    BFE_ERR_INVALID_CONTSCAN  = 16,                     ///< Operation not allowed during continuous scan
    BFE_ERR_INVALID_CELL      = 17,                     ///< Invalid cell number

    /* Communication errors */
    BFE_COMM_SUCCESS                    = 100,

    BFE_ERR_COMM_NO_COMMUNICATION      = 101,                    ///< Communication with the device could not be established
    BFE_ERR_COMM_WRONG_CRC             = 102,                    ///< Wrong CRC received
    BFE_ERR_COMM_OPEN_FAILED           = 103,                    ///< error while opening communication interface
    BFE_ERR_COMM_NONSUPPORTED_INTERFACE = 104,                   ///< Selected interface is not supported
    BFE_ERR_COM_READ_AFTER_WRITE_FAILED  = 105,                    ///< Read-after-write operation for verification failed
    BFE_ERR_COMM_TIMEOUT                 = 106,
    BFE_ERR_COMM_FAULT              = 107,

    /*Parameter related errors*/
    BFE_PARAM_OK                      = 200,

    BFE_ERR_RETURN_VALUES_DONOT_MATCH = 201,                 ///< the number of values that are expected by the caller is incorrect
    BFE_ERR_NULL_CTRL_POINTER         = 202,                 ///< ctrl instance has been casted to null pointer. check parameter
    BFE_ERR_NULL_CFG_POINTER          = 203,                 ///< cfg instance has been casted to a null pointer
    BFE_ERR_MUSTBE_POSITIVE_VALUE     = 204,                 ///< Parameter value must be >0
    BFE_ERR_MUSTBE_NEGATIVE_VALUE     = 205,                 ///< Parameter value must be <0
    BFE_ERR_MUSTBE_NONZERO_VALUE     = 206,                 ///< Parameter value must be !=0
    BFE_ERR_UNSUPPORTED_CELL_COUNT   = 207,                 ///< Number of selected cells is not supported
    BFE_ERR_UNSUPPORTED_DELAY       = 208,                 ///< Delay time is not supported
    BFE_ERR_OUT_OF_RANGE_VALUE      = 209,                 ///< Value is out of the valid range
    /*FSP error*/
    BFE_FSP_SUCESS                  = 300,

    BFE_ERR_FSP_ERROR               = 301,                   ///< the FSP layer has reported an error

    BFE_WARN_BUSY                    = 900,                  ///< Warning to indicate a register has been reading while the device is busy
    BFE_WARN_REGISTER_RESET_UNMATCHED = 901,                  ///< Warning: The expected reset value does not match the actual register value

} e_bfe_err_t;

/** BFE events that shall be reported to the application */
typedef enum e_bfe_event
{
    BFE_EVENT_RESET = 1,                        ///< BFE has been reset
    BFE_EVENT_FIXED_CHECKSUM_FAILED,            ///< Fixed data checksum does not match
    BFE_EVENT_COMMUNICATION_TIME_OUT,           ///< No communication has been detected/generated during a given time
    BFE_EVENT_NO_RESPONSE,                      ///< BFE does not respond
    BFE_EVENT_SHORT_DETECTED,                   ///> short current has been detected
    BFE_EVENT_LOAD_DETECTED,                    ///> Load has been detected
    BFE_EVENT_POWER_FAULT,                      ///> Fault in internal and external regulators has been detected
    BFE_EVENT_INTERNAL_FAULT,                   ///> an internal fault has been detected, e.g., internal clock
    BFE_EVENT_VBOV_FAULT,                       ///> VBAT over-voltage Fault
    BFE_EVENT_VBUV_FAULT,                       ///> VBAT under-voltage Fault
    BFE_EVENT_CPMP_NRDY,                        ///> Charge pump is not ready
    BFE_EVENT_OW_AUX,                           ///> open wire has occurred on auxiliary pins
    BFE_EVENT_OW_VBAT,                          ///> Top cell voltage is higher that device powering voltage VBAT
    BFE_EVENT_OW_VSS,                           ///> VSS voltage is significantly higher than VC0
    BFE_EVENT_CRC_MASTER_FAULT,                 ///> CRC value sent by the master does not match internal CRC value
} e_bfe_event_t;

/**BFE states*/
typedef enum e_bfe_mode
{
    BFE_MODE_RESET,                            ///> Initial state when all circuits and oscillators are off
    BFE_MODE_IDLE,                             ///> The device is ready waiting for a task to be executed
    BFE_MODE_POWER_DOWN,                       ///> BFE shut down state
    BFE_MODE_POWER_UP,                         ///> BFE power-up state
    BFE_MODE_SHIP,                             ///> Lowest power consumption
    BFE_MODE_LOW_POWER_MODE,                   ///> The BFE is currently in low power mode
    BFE_MODE_SCAN,                             ///> Continuous and periodic execution of measurements
} e_bfe_mode_t;

/**BFE types of resets*/
typedef enum e_bfe_reset_type
{
    BFE_RESET_TYPE_SOFT,
    BFE_RESET_TYPE_HARD,
    BFE_RESET_TYPE_TOIDLE,
} e_bfe_reset_type_t;

/** Common callback parameter definition */
typedef struct st_bfe_callback_args
{
    e_bfe_event_t  event;                ///< Event code
    void const * p_context;            ///< Context provided to user during callback
} st_bfe_callback_args_t;

/** BFE interface configuration */
typedef struct st_bfe_cfg
{
    float *                         const p_shunt_resistor;         ///< Shunt resistor value in [Ohms] to meaasure Ipack
    uint8_t                         max_cells;              ///< Maximum number of cells
    uint8_t                         min_cells;              ///< Minimum number of cells
    uint32_t                        cell_select;            ///< indicates which cells exists in the BMS
    e_bfe_comm_peripheral_t         peripheral_type;        ///< peripheral used to communicate with the BFE
    bool                            read_after_write;       ///< if true, a read operation follows register write to verify correctness
    uint8_t                         num_read_after_write;   ///< Number of read after write operations to generate error in case verification fails
    e_bfe_driver_configuration_t    driver_conf;            ///< Configuration of the FET drivers
    e_bfe_fet_configuration_t       power_conf;             ///< configuration of FET drivers to provide load and/or charger connection
    void const                      * p_extend;             ///< Extended BFE hardware dependent configuration
} st_bfe_cfg_t;

/** BFE control block.  Allocate an instance specific control block to pass into the BFE API calls.
 * @par Implemented as
 * - raa489206_instance_ctrl
 */
typedef void st_bfe_ctrl_t;

/**Configuration settings of the continuous scan operation
 * @par Implemented as
 * - st_raa489206_cs_config_t*/
typedef void bfe_cs_configuration_t;

/**BFE general status and faults of the device
 * @par Implemented as
 * - st_raa489206_status_t*/
typedef void bfe_status_t;

/**BFE fault type
 * @par Implemented as
 * - st_raa489206_fault_type_t*/
typedef void bfe_fault_type_t;

/**Other measurements
 * @par Implemented as
 * - st_raa489206_other_measurements_t*/
typedef void bfe_other_measurements_t;

/**Vcell measurements
 * @par Implemented as
 * - st_raa489206_vcell_measurements_t*/
typedef void bfe_vcell_measurements_t;

/**Auxiliary/External measurements
 * @par Implemented as
 * - st_raa489206_aux_ext_measurements_t*/
typedef void bfe_auxext_measurements_t;

/**Auxiliary/External measurements
 * @par Implemented as
 * - st_raa489206_temperature_measurements_t*/
typedef void bfe_temperature_measurements_t;

/** Events that shall propagate to/assert the alert pin
 * @par Implemented as
 * - st_raa489206_events_masks_t*/
typedef void bfe_alerts_masks_t;

/** Low Power Mode (LPM) configuration settings
 * @par Implemented as
 * - st_raa489206_lpm_cfg_t*/
typedef void bfe_lpm_cfg_t;

/** Shared Interface definition for Battery Front Ends */
typedef struct st_bfe_api
{
    /** Initialize a BFE and set control block with necessary configuration.
     * @par Implemented as
     * - @ref RAA489206_Init
     *
     * @param[in, out] p_ctrl Pointer to the BFE control block.
     * @param[in]      p_cfg  Pointer to BFE configuration structure.
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_init)(st_bfe_ctrl_t * p_ctrl, st_bfe_cfg_t const * const p_cfg);

    /** Reset BFE device.
     * @par Implemented as
     * - @ref RAA489206_Reset
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in]  reset_type reset type to be executed
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_reset)(st_bfe_ctrl_t * const p_ctrl, e_bfe_reset_type_t reset_type);

    /** Start a complete system scan.
     * @par Implemented as
     * - @ref RAA489206_StartSystemScan
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_startSystemScan)(st_bfe_ctrl_t * const p_ctrl);

    /** Start continuous scan mode.
     * @par Implemented as
     * - @ref RAA489206_StartContinuousScan
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  st_cs_settings pointer to continuous scan operation settings
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_startContinuousScan)(st_bfe_ctrl_t * const p_ctrl, const bfe_cs_configuration_t * const st_cs_settings);

    /** Stop continuous scan mode.
     * @par Implemented as
     * - @ref RAA489206_StopContinuousScan
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_stopContinuousScan)(st_bfe_ctrl_t * const p_ctrl);

    /** Read curent device status (busy or available)
     * @par Implemented as
     * - @ref RAA489206_IsBusy()
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in/out] p_device_busy pointer to boolean that will store the device availabity (busy=true, available=false)
     *
     * @return bfe error code
     */
    e_bfe_err_t ( * p_isBusy)(st_bfe_ctrl_t * const p_ctrl, bool * p_device_is_busy);

    /** Read BFE Status
     * @par Implemented as
     * - @ref RAA489206_ReadFaults()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out] p_bfe_status pointer to a BFE-defined variable that will store its status and faults indicators
     *
     * @return bfe_err error code.
     */
    e_bfe_err_t ( * p_readStatus)(st_bfe_ctrl_t * p_ctrl, bfe_status_t * const p_bfe_status);

    /** Read BFE Mode
     * @par Implemented as
     * - @ref RAA489206_ReadMode()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out] p_mode pointer to variable that will store device mode
     *
     * @return bfe_err error code.
     */
    e_bfe_err_t ( * p_readMode)(st_bfe_ctrl_t * p_ctrl, e_bfe_mode_t * const p_mode);

    /** Clear all current Faults
     * @par Implemented as
     * - @ref RAA489206_ClearAllFaults()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     *
     * @return bfe_err error code.
     */
    e_bfe_err_t ( * p_clearAllFaults)(st_bfe_ctrl_t * p_ctrl);

    /** Clear a Fault or a group of Faults
     * @par Implemented as
     * - @ref RAA489206_ClearFault()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in]  p_bfe_faults    Pointer to BFE-defined structure that specifies the faults to be cleared.
     *
     * @return bfe_err error code.
     */
    e_bfe_err_t ( * p_clearFault)(st_bfe_ctrl_t * p_ctrl, const bfe_fault_type_t * const p_bfe_faults);

    /** Read Battery Pack voltage
     * @par Implemented as
     * - @ref RAA489206_ReadVpack()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in/out] p_value   Pointer to float variable which will store Vpack value in [mV].
     * @param[in]  trigger boolean indicating whether a Vpack measurement is triggered before reading its value
     *      *
     * @return bfe_err error code.
     */
    e_bfe_err_t ( * p_readVpack)(st_bfe_ctrl_t * const p_ctrl, float * const p_value, bool trigger);

    /** Read cells voltage.
     * @par Implemented as
     * - @ref RAA489206_ReadVcells()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in/out] p_values Pointer to a BFE-defined variable that will store Vcell values in [mV].
     * @param[in]  trigger boolean indicating whether a Vcell measurement should be triggered before reading its value
     *
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readVcells)(st_bfe_ctrl_t * const p_ctrl, bfe_vcell_measurements_t * const p_values, bool trigger);

    /** Read pack current calculated using the shunt resistor value stored in the bfe config entity.
     * @par Implemented as
     * - @ref RAA489206_ReadIpack()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in/out] p_values Pointer to float variable that will store Ipack value in [mA]
     * @param[in]  trigger boolean indicating whether a Ipack measurement is triggered before reading its value

     *
     * @return bfe_err error code
     */
    e_bfe_err_t (* p_readIpack)(st_bfe_ctrl_t * const p_ctrl, float * const p_value, bool trigger);

    /** Read other measurements provided by the BFE, e.g., internal temperature voltage.
     * @par Implemented as
     * - @ref RAA489206_ReadOther()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in/out] p_values Pointer to BFE-defined variable that will contain Other measurements values, e.g., Vdd, Idd, Itemp.
     * @param[in]  trigger boolean indicating whether measurements are triggered before reading its value
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readOther)(st_bfe_ctrl_t * const p_ctrl, bfe_other_measurements_t * const p_values, bool trigger);

    /** Read auxiliary/external measurements provided by the BFE.
     * @par Implemented as
     * - @ref RAA489206_ReadAuxExt()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in/out] p_values Pointer to BFE-defined variable that will store Aux/Ext measurements values
     * @param[in]  trigger boolean indicating whether measurements are triggered before reading its value
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readAuxExt)(st_bfe_ctrl_t * const p_ctrl, bfe_auxext_measurements_t * const p_values, bool trigger);

    /** Read temperature.
      * @par Implemented as
      * - @ref RAA489206_ReadTemperature()
      *
      * @param[in]  p_ctrl    Pointer to BFE control block.
      * @param[in/out] p_values Pointer to BFE-defined variable that will store temperature measurements
      * @param[in]  trigger boolean indicating whether measurements are triggered before reading its value
      *
      * @return bfe_err error code
      */
     e_bfe_err_t ( * p_readTemperature)(st_bfe_ctrl_t * const p_ctrl, bfe_temperature_measurements_t * const p_values, bool trigger);

     /** turn BFE charge pump on.
      * @par Implemented as
      * - @ref RAA489206_TurnChargePumpOn()
      *
      * @param[in]  p_ctrl  Pointer to BFE control block.
      * @return bfe_err error code
      */
     e_bfe_err_t ( * p_turnChargePumpOn)(st_bfe_ctrl_t * const p_ctrl);

     /** turn BFE charge pump off.
      * @par Implemented as
      * - @ref RAA489206_TurnChargePumpOff()
      *
      * @param[in]  p_ctrl    Pointer to BFE control block.
      * @return bfe_err error code
      */
     e_bfe_err_t ( * p_turnChargePumpOff)(st_bfe_ctrl_t * const p_ctrl);

    /** turn BFE discharge FET on.
     * @par Implemented as
     * - @ref RAA489206_TurnDFetOn()
     *
     * @param[in]  p_ctrl  Pointer to BFE control block.
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_turnDfetOn)(st_bfe_ctrl_t * const p_ctrl);

    /** turn BFE discharge FET off.
     * @par Implemented as
     * - @ref RAA489206_TurnDfetOff()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_turnDfetOff)(st_bfe_ctrl_t * const p_ctrl);

    /** turn BFE charge FET on.
     * @par Implemented as
     * - @ref RAA489206_TurnCefOn()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_turnCfetOn)(st_bfe_ctrl_t * const p_ctr);

    /** turn BFE charge FET off.
     * @par Implemented as
     * - @ref RAA489206_TurnCFetOff()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_turnCfetOff)(st_bfe_ctrl_t * const p_ctrl);

    /** turn both BFE discharge and charge FETs on.
     * @par Implemented as
     * - @ref RAA489206_TurnDFetOnCFetOn()
     *
     * @param[in]  p_ctrl  Pointer to BFE control block.
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_turnDfetOnCfetOn)(st_bfe_ctrl_t * const p_ctrl);

    /** turn BFE discharge FET off and charge FET on.
     * @par Implemented as
     * - @ref RAA489206_TurnDFetOffCFetOn()
     *
     * @param[in]  p_ctrl  Pointer to BFE control block.
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_turnDfetOffCfetOn)(st_bfe_ctrl_t * const p_ctrl);

    /** turn BFE discharge FET on and charge FET off.
     * @par Implemented as
     * - @ref RAA489206_TurnDFetOnCfetOff()
     *
     * @param[in]  p_ctrl  Pointer to BFE control block.
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_turnDfetOnCfetOff)(st_bfe_ctrl_t * const p_ctrl);

    /** turn both BFE discharge FET and charge FET off.
     * @par Implemented as
     * - @ref RAA489206_TurnDFetOffCFetOff()
     *
     * @param[in]  p_ctrl  Pointer to BFE control block.
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_turnDfetOffCfetOff)(st_bfe_ctrl_t * const p_ctrl);

    /** Set mode.
     * @par Implemented as
     * - @ref RAA489206_SetMode()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in] bfe_mode   Device mode to be set in the device
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_setMode)(st_bfe_ctrl_t * const p_ctrl, e_bfe_mode_t bfe_mode);

    /** Set alerts.
     * @par Implemented as
     * - @ref RAA489206_SetAlerts()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in/out] alert_events Pointer to BFE-defined variable that specifies which events shall assert the Alert pin
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_setAlerts)(st_bfe_ctrl_t * const p_ctrl, const bfe_alerts_masks_t * const alert_events);

    /** Set discharge over-current (DOC) threshold.
     * @par Implemented as
     * - @ref RAA489206_SetDOC()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in]  current_th   Discharge over-current threshold in [mA]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_setDoc)(st_bfe_ctrl_t * const p_ctrl, float current_ma);

    /** Set charge over-current (COC) threshold.
     * @par Implemented as
     * - @ref RAA489206_SetCOC()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  current_th   Charge over-current threshold in [mA]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_setCoc)(st_bfe_ctrl_t * const p_ctrl, float current_ma);

    /** Set discharge short-circuit  (DSC) threshold.
         * @par Implemented as
         * - @ref RAA489206_SetDSC()
         *
         * @param[in]  p_ctrl    Pointer to the BFE control block.
         * @param[in]  current_th   Short over-current threshold in [mA]
         *
         * @return bfe_err error code
         */
    e_bfe_err_t ( * p_setDsc)(st_bfe_ctrl_t * const p_ctrl, float current_ma);

    /** Set cells under-voltage threshold .
     * @par Implemented as
     * - @ref R_RAA489206_SetCellUndevoltage()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  vcells_delta_th_mv   Cell voltage delta threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_setMaxVCellDelta)(st_bfe_ctrl_t * const p_ctrl, float vcells_delta_th_mv);

    /** Set cells under-voltage threshold .
     * @par Implemented as
     * - @ref RAA489206_SetCellsUndervoltage()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  cells_vcell_delta_th_mv   Cells under-voltage threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_setCellUndervoltage)(st_bfe_ctrl_t * const p_ctrl, float cells_vcell_delta_th_mv);

    /** Set Battery pack under-voltage threshold .
     * @par Implemented as
     * - @ref RAA489206_SetVpackUndervoltage()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  vpack_uv_th  Pack under-voltage threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_setVpackUndervoltage)(st_bfe_ctrl_t * const p_ctrl, float vpack_uv_th_mv);

    /** Set cells over-voltage threshold .
     * @par Implemented as
     * - @ref RAA489206_SetCellsOvervoltage()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  cells_ov_th  Cells over-voltage threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_setCellOvervoltage)(st_bfe_ctrl_t * const p_ctrl, float cells_ov_th_mv);

    /** Set Battery pack over-voltage threshold .
     * @par Implemented as
     * - @ref RAA489206_SetVpackOvervoltage()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  vpack_ov_th   Pack over-voltage threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_setVpackOvervoltage)(st_bfe_ctrl_t * const p_ctrl, float vpack_ov_th_mv);

    /** Set internal over-temperature warning .
     * @par Implemented as
     * - @ref RAA489206_SetInternalOvertemperature()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  temperature   internal over-temperature threshold in [°C]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t (* p_setInternalOvertemperatureWarn)(st_bfe_ctrl_t * const p_ctrl, float temperature);

    /** Set internal over-temperature fault threshold .
     * @par Implemented as
     * - @ref RAA489206_SetInternalOvertemperature()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  temperature   internal over-temperature fault threshold in [°C]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t (* p_setInternalOvertemperatureFault)(st_bfe_ctrl_t * const p_ctrl, float temperature);

    /** Set voltage end of charge threshold .
     * @par Implemented as
     * - @ref R_RAA489206_SetVoltageEndOfCharge()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  veoc_mv   voltage end of charge threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_setVoltageEndOfCharge)(st_bfe_ctrl_t * const p_ctrl, float veoc_mv);

    /** Set current end of charge threshold .
     * @par Implemented as
     * - @ref R_RAA489206_SetCurrentEndOfCharge()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  veoc_mv   current end of charge threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_setCurrentEndOfCharge)(st_bfe_ctrl_t * const p_ctrl, float ieoc_ma);

    /** Read alerts.
     * @par Implemented as
     * - @ref RAA489206_ReadAlerts()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in/out] p_alert_events Pointer to BFE-defined variable to be returned
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readAlerts)(st_bfe_ctrl_t * const p_ctrl, bfe_alerts_masks_t * const p_alert_events);

    /** Read discharge over-current (DOC) threshold.
     * @par Implemented as
     * - @ref RAA489206_ReadDOC()
     *
     * @param[in]  p_ctrl    Pointer to BFE control block.
     * @param[in/out]  current_th   pointer to the variable that will store the DOC threshold in [mA]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readDoc)(st_bfe_ctrl_t * const p_ctrl, float * p_current_ma);

    /** Read charge over-current (COC) threshold.
     * @par Implemented as
     * - @ref RAA489206_ReadCOC()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out]  p_current_th   pointer to the variable that will store the COC threshold in [mA]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readCoc)(st_bfe_ctrl_t * const p_ctrl, float * p_current_ma);

    /** Read discharge short-circuit  (DSC) threshold.
         * @par Implemented as
         * - @ref RAA489206_ReadDSC()
         *
         * @param[in]  p_ctrl    Pointer to the BFE control block.
         * @param[in]  p_current_th   pointer to the variable that will store the DSC threshold in [mA]
         *
         * @return bfe_err error code
         */
    e_bfe_err_t ( * p_readDsc)(st_bfe_ctrl_t * const p_ctrl, float * p_current_ma);

    /** Read Vcells delta  threshold .
     * @par Implemented as
     * - @ref R_RAA489206_ReadCellUndevoltage()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out]  p_vcells_delta_th_mv   pointer to variable that will store the Vcells delta threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readMaxVCellDelta)(st_bfe_ctrl_t * const p_ctrl, float * p_vcells_delta_th_mv);

    /** Read cells under-voltage threshold .
     * @par Implemented as
     * - @ref RAA489206_ReadCellsUndervoltage()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out]  p_vcell_uv_th_mv   pointer to the variable that will store the vcells UV threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readCellUndervoltage)(st_bfe_ctrl_t * const p_ctrl, float * p_vcell_uv_th_mv);

    /** Read Battery pack under-voltage threshold .
     * @par Implemented as
     * - @ref RAA489206_ReadVpackUndervoltage()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out]  p_vpack_uv_th   pointer to the variable that will store the under-voltage threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readVpackUndervoltage)(st_bfe_ctrl_t * const p_ctrl, float * p_vpack_uv_th_mv);

    /** Read cells over-voltage threshold .
     * @par Implemented as
     * - @ref RAA489206_ReadCellsOvervoltage()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out]  p_cells_ov_th   pointer to the variable that will store the over-voltage threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readCellOvervoltage)(st_bfe_ctrl_t * const p_ctrl, float * p_cells_ov_th_mv);

    /** Set Battery pack over-voltage threshold .
     * @par Implemented as
     * - @ref RAA489206_ReadVpackOvervoltage()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out]  p_vpack_ov_th   pointer to the variable that will store the over-voltage threshold in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readVpackOvervoltage)(st_bfe_ctrl_t * const p_ctrl, float * p_vpack_ov_th_mv);

    /** Set internal over-temperature warning .
     * @par Implemented as
     * - @ref RAA489206_ReadInternalOvertemperature()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out]  p_temperature   pointer to variable that will store the internal over-temperature threshold in [°C]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t (* p_readInternalOvertemperatureWarn)(st_bfe_ctrl_t * const p_ctrl, float * p_temperature);

    /** Read internal over-temperature fault threshold .
     * @par Implemented as
     * - @ref RAA489206_ReadInternalOvertemperature()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out]  p_temperature   pointer to variable that will store the internal over-temperature fault threshold in [°C]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t (* p_readInternalOvertemperatureFault)(st_bfe_ctrl_t * const p_ctrl, float * p_temperature);

    /** Read voltage end of charge threshold .
     * @par Implemented as
     * - @ref RAA489206_ReadVoltageendOfCharge()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out]  p_veoc_th   pointer to the variable that will store the voltage en of charge in [mV]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readVoltageEndOfCharge)(st_bfe_ctrl_t * const p_ctrl, float * p_veoc_th);

    /** Read current end of charge threshold.
     * @par Implemented as
     * - @ref RAA489206_ReadCurrentEndOfCharge()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out]  p_veoc_th   pointer to the variable that will store the current end of charge in [mA]
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_readCurrentEndOfCharge)(st_bfe_ctrl_t * const p_ctrl, float * p_ieoc_th);

    /** Configure device low power mode settings.
     * @par Implemented as
     * - @ref RAA489206_ConfigureLowPowerMode()
     *
     * @param[in]  p_ctrl  Pointer to the BFE control block.
     * @param[in]  p_lpm_options    Pointer to structure with low power mode options.
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_configureLowPowerMode)(st_bfe_ctrl_t * const p_ctrl, bfe_lpm_cfg_t * const p_lpm_options);

    /** Set the device to its low power mode.
     * @par Implemented as
     * - @ref RAA489206_StartLowPowerMode()
     *
     * @param[in]  p_ctrl  Pointer to the BFE control block.
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_startLowPowerMode)(st_bfe_ctrl_t * const p_ctrl);

    /** Get die information (e.g. revision).
     * @par Implemented as
     * - @ref RAA489206_GetDieInformation()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in/out]  p_information    Pointer to the structure to be written with the die information.
     *
     * @return bfe_err error code
     */
    e_bfe_err_t ( * p_getDieInformation)(st_bfe_ctrl_t * const p_ctrl, st_bfe_information_t * p_information);

    /** Read device register
     * @par Implemented as
     * - @ref RAA489206_ReadRegister()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  p_bfe_register    Pointer to the bfe register to be read.
     *
     * @return bfe_err error code
     */
    e_bfe_err_t (* p_readRegister)(st_bfe_ctrl_t * const p_ctrl, st_bfe_register_t * const bfe_register);

    /** Write register value in a device register.
     * @par Implemented as
     * - @ref RAA489206_WriteRegister()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     * @param[in]  p_bfe_register    Pointer to the bfe register to be written.
     *
     * @return bfe_err error code
     */
    e_bfe_err_t (* p_writeRegister)(st_bfe_ctrl_t * const p_ctrl, const st_bfe_register_t * const p_bfe_register);

    /** Read all registers
     * @par Implemented as
     * - @ref RAA489206_ReadAllRegisters()
     *
     * @param[in]  p_ctrl    Pointer to the BFE control block.
     *
     * @return bfe_err error code
     */
    e_bfe_err_t (* p_readAllRegisters)(st_bfe_ctrl_t * const p_ctrl);
} st_bfe_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_bfe_instance
{
    st_bfe_ctrl_t       * p_ctrl;          ///< Pointer to the control structure for this instance
    const st_bfe_cfg_t  * p_cfg;           ///< Pointer to the configuration structure for this instance
    const st_bfe_api_t  * p_api;           ///< Pointer to the API structure for this instance
} st_bfe_instance_t;
/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

#endif /* BFE_BFE_H_ */
