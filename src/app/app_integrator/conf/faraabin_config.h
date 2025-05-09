/**
 ******************************************************************************
 * @file           : faraabin_config.h
 * @brief          : Faraabin configuration header file.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 FaraabinCo.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 *
 * https://faraabinco.ir/
 * https://github.com/FaraabinCo
 *
 ******************************************************************************
 * @verbatim
 * 
 * Faraabin configuration is done by modifying this file.
 * In order to use this file:
 * 1- Copy this file to your project and add its location to your include paths.
 * 2- Modify faraabin features and configuration as you require them in your project.
 * 
 * @endverbatim
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FARAABIN_CONFIG_H
#define FARAABIN_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported defines ----------------------------------------------------------*/
/** @defgroup FARAABIN_CONFIG
  * @brief
  * @{
  */
#define FARAABIN_ENABLE /*!< Enables Faraabin throughout user application. */

/** @defgroup FB_FEATURE_FLAG
  * @brief Faraabin features.
  * 
  * @note To disable a feature, simply comment corresponding FB_FEATURE_FLAG.
  *       To enable a feature, uncomment corresponding FB_FEATURE_FLAG.
  * @{
  */
#define FB_FEATURE_FLAG_DEFAULT_DATABUS         /*!< This feature creates a default databus for faraabin. */
#define FB_FEATURE_FLAG_DEFAULT_EVENT_GROUP     /*!< This feature creates a default event group for faraabin. */

/** @} */ //End of FB_FEATURE_FLAG

/** @defgroup FB_FEATURE_FLAG
  * @brief Faraabin features can be Enabled/Disabled using these comments.
  * 
  * @note To disable a feature, simply comment corresponding FB_FEATURE_FLAG.
  *       To enable a feature, uncomment corresponding FB_FEATURE_FLAG.
  * @{
  */
#define FB_FEATURE_FLAG_MCU_CLI                /*!< This feature ebables you to create FunctionGroups and run your functions in faraabin UI. */
#define FB_FEATURE_FLAG_BUFFER_OVF             /*!< This features enables the buffer overflow notification. Activating this feature can be time consuming. */
//#define FB_FEATURE_FLAG_ALLOW_SEND_DICT_BLOCKING /*!< This features enables that dictionary send by blocking fFaraabin_Run() function. */

/** @} */ //End of FB_FEATURE_FLAG

/** @defgroup FB_FEATURE_FLAG_ADD_ON
  * @brief Faraabin addons.
  * 
  * @note To disable an addon, simply comment corresponding FB_FEATURE_FLAG.
  *       To enable an addon, uncomment corresponding FB_FEATURE_FLAG.
  * @{
  */
#define FB_ADD_ON_FEATURE_FLAG_UNITY           /*!< This feature enables unity port in faraabin & creates UnityReport event group to show reports of unity in it's TerminalWd. */
#define FB_ADD_ON_FEATURE_FLAG_CPU_PROFILER   /*!< This feature enables you to instantiate cpu_profiler module to measure process timing in your app. */
#define FB_ADD_ON_FEATURE_FLAG_STATE_MACHINE  /*!< This feature connects faraabin to your state machine (generated by faraabin state machine library) and gives more control and visualization of your SM. */

/** @} */ //End of FB_FEATURE_FLAG_ADD_ON

/**
 * @brief Interval of the default databus in milliseconds.
 * 
 */
#define FB_DEFAULT_DATABUS_CYCLE_MS     (100U)

/**
 * @brief Number of channels of the faraabin default databus.
 * 
 */
#define FB_DEFAULT_DATABUS_CHANNEL_QTY  (20U)

/**
 * @brief Number of items to dequeue from databus capture buffer when databus is sending.
 * 
 */
#define FB_DATABUS_CAPTURE_SEND_ITEMS   (20U)

/**
 * @brief Timeout for sending each byte via faraabin link in milliseconds.
 * 
 */
#define FB_BYTE_SENDING_TIME_MS         (10U)

/**
 * @brief Live timeout in milliseconds.
 * 
 */
#define FB_LIVE_TIMEOUT_MS              (2000U)

/**
 * @brief Maximum number of allowable fobjects to add to dictionary.
 * 
 */
#define FB_MAX_FOBJECT_QTY              (100U)

/**
 * @brief Determines maximum number of concurrent functions that faraabin engine can run.
 * 
 */
#define FB_MAX_CONCURRENT_FUNCTION      (2U)

/**
 * @brief Determines the buffer size dedicated to each function to save their parameters.
 * 
 */
#define FB_FUNCTION_PARAM_BUFFER_SIZE   (200U)

/**
 * @brief Buffer size allocated to the text events in Faraabin.
 * 
 */
#define TEXT_EVENT_BUFFER_SIZE          (200U)

/**
 * @brief Maximum number of times that higher priority text events can interrup lower ones.
 * 
 */
#define TEXT_EVENT_MAX_REENTRANCE       (10U)

/** @} */ //End of FARAABIN_CONFIG

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* FARAABIN_CONFIG_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
