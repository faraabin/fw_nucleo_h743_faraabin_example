/**
 ******************************************************************************
 * @file           : stm32h7xx_phal_config.h
 * @brief          :
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 FaraabinCo.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component
 * 
 * https://faraabinco.ir/
 * https://github.com/FaraabinCo
 *
 ******************************************************************************
 * @verbatim
 * @endverbatim
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef stm32h7xx_phal_config_H
#define stm32h7xx_phal_config_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Exported defines ----------------------------------------------------------*/
/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Phal Watchdog Parameter #####                     ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define PHAL_WD_ENABLE

/**
 * @brief 
 * 
 */
#define meHAL_IWDG_PRESCALER  128  //4-8-16-32-64-128-256

/**
 * @brief 
 * 
 */
#define meHAL_IWDG_CLOCK         32000

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Phal UART Parameter #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define UART1_ENABLE
//#define UART2_ENABLE
#define UART3_ENABLE
//#define UART4_ENABLE
//#define UART5_ENABLE
//#define UART6_ENABLE
//#define UART7_ENABLE
//#define UART8_ENABLE

/**
 * @brief 
 * 
 */
#define UART1_TX_PORT_PIN  AUX_PA9    //PA9-PB6-PB14
#define UART1_RX_PORT_PIN  AUX_PA10   //PA10-PB7-PB15

/**
 * @brief 
 * 
 */
//#define UART1_DE_ENABLE
#define UART1_DE_PORT_PIN  AUX_PA12  //PA12
#define UART1_DE_POLARITY_HIGH  true //true-false
#define UART1_DE_ASSERTION_TIME 31  //0~31
#define UART1_DE_DEASSERTION_TIME 31  //0~31

/**
 * @brief 
 * 
 */
//#define UART1_TX_DMA_CFG   DMA1_STREAM0
//#define UART1_RX_DMA_CFG   DMA1_STREAM1

#define UART1_TX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR
#define UART1_RX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR

/**
 * @brief 
 * 
 */
#define UART1_TX_DMA_IRQ_PreemptPriority  2
#define UART1_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART1_RX_DMA_IRQ_PreemptPriority  2
#define UART1_RX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART1_IRQ_PreemptPriority  2
#define UART1_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART1_OVERSAMPLING  UART_OVERSAMPLING_16 //UART_OVERSAMPLING_16-UART_OVERSAMPLING_8

/**
 * @brief 
 * 
 */
#define UART1_TXINVERT_ENABLE            false  //true-false
#define UART1_RXINVERT_ENABLE            false  //true-false
#define UART1_DATA_BINARY_INVERT_ENABLE  false  //true-false
#define UART1_PIN_SWAP_ENABLE            false  //true-false
  
/**
 * @brief 
 * 
 */
#define UART2_TX_PORT_PIN  AUX_PD5   //PA2-PD5
#define UART2_RX_PORT_PIN  AUX_PD6   //PA3-PD6

/**
 * @brief 
 * 
 */
//#define UART2_DE_ENABLE
#define UART2_DE_PORT_PIN  AUX_PD4  //PA1-PD4
#define UART2_DE_POLARITY_HIGH  true //true-false
#define UART2_DE_ASSERTION_TIME 31  //0~31
#define UART2_DE_DEASSERTION_TIME 31  //0~31

/**
 * @brief 
 * 
 */
#define UART2_TX_DMA_CFG   DMA1_STREAM0
#define UART2_RX_DMA_CFG   DMA1_STREAM1

#define UART2_TX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR
#define UART2_RX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR

/**
 * @brief 
 * 
 */
#define UART2_TX_DMA_IRQ_PreemptPriority  2
#define UART2_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART2_RX_DMA_IRQ_PreemptPriority  2
#define UART2_RX_DMA_IRQ_SubPriority      2

/** 
  * @brief
  */
#define UART2_IRQ_PreemptPriority  2
#define UART2_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART2_OVERSAMPLING  UART_OVERSAMPLING_16 //UART_OVERSAMPLING_16-UART_OVERSAMPLING_8

/**
 * @brief 
 * 
 */
#define UART2_TXINVERT_ENABLE            false  //true-false
#define UART2_RXINVERT_ENABLE            false  //true-false
#define UART2_DATA_BINARY_INVERT_ENABLE  false  //true-false
#define UART2_PIN_SWAP_ENABLE            false  //true-false

/**
 * @brief 
 * 
 */
#define UART3_TX_PORT_PIN  AUX_PD8  //PC10-PD8-PB10
#define UART3_RX_PORT_PIN  AUX_PD9  //PC11-PD9-PB11

/**
 * @brief 
 * 
 */
//#define UART3_DE_ENABLE
#define UART3_DE_PORT_PIN  AUX_PB14  //PB14-PD12
#define UART3_DE_POLARITY_HIGH  true //true-false
#define UART3_DE_ASSERTION_TIME 31  //0~31
#define UART3_DE_DEASSERTION_TIME 31  //0~31

/**
 * @brief 
 * 
 */
#define UART3_TX_DMA_CFG   DMA1_STREAM2
#define UART3_RX_DMA_CFG   DMA1_STREAM3

#define UART3_TX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR
#define UART3_RX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR

/** 
  * @brief
  */
#define UART3_TX_DMA_IRQ_PreemptPriority  2
#define UART3_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART3_RX_DMA_IRQ_PreemptPriority  0
#define UART3_RX_DMA_IRQ_SubPriority      0

/**
 * @brief 
 * 
 */
#define UART3_IRQ_PreemptPriority  2
#define UART3_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART3_OVERSAMPLING  UART_OVERSAMPLING_16 //UART_OVERSAMPLING_16-UART_OVERSAMPLING_8

/**
 * @brief 
 * 
 */
#define UART3_TXINVERT_ENABLE            false  //true-false
#define UART3_RXINVERT_ENABLE            false  //true-false
#define UART3_DATA_BINARY_INVERT_ENABLE  false  //true-false
#define UART3_PIN_SWAP_ENABLE            false  //true-false

/**
 * @brief 
 * 
 */
#define UART4_TX_PORT_PIN  AUX_PD1  //PA0-PC10-PA12-PH13-PD1
#define UART4_RX_PORT_PIN  AUX_PD0  //PA1-PC11-PI9-PA11-PH14-PD0

/**
 * @brief 
 * 
 */
//#define UART4_DE_ENABLE
#define UART4_DE_PORT_PIN  AUX_PB14  //PB14-PA15
#define UART4_DE_POLARITY_HIGH  true //true-false
#define UART4_DE_ASSERTION_TIME 31  //0~31
#define UART4_DE_DEASSERTION_TIME 31  //0~31

/**
 * @brief 
 * 
 */
// #define UART4_TX_DMA_CFG   DMA1_STREAM4
// #define UART4_RX_DMA_CFG   DMA1_STREAM5

#define UART4_TX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR
#define UART4_RX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR

/**
 * @brief 
 * 
 */
#define UART4_TX_DMA_IRQ_PreemptPriority  1
#define UART4_TX_DMA_IRQ_SubPriority      1

/**
 * @brief 
 * 
 */
#define UART4_RX_DMA_IRQ_PreemptPriority  1
#define UART4_RX_DMA_IRQ_SubPriority      1

/**
 * @brief 
 * 
 */
#define UART4_IRQ_PreemptPriority  1
#define UART4_IRQ_SubPriority      1

/**
 * @brief 
 * 
 */
#define UART4_OVERSAMPLING  UART_OVERSAMPLING_16 //UART_OVERSAMPLING_16-UART_OVERSAMPLING_8

/**
 * @brief 
 * 
 */
#define UART4_TXINVERT_ENABLE            false  //true-false
#define UART4_RXINVERT_ENABLE            false  //true-false
#define UART4_DATA_BINARY_INVERT_ENABLE  false  //true-false
#define UART4_PIN_SWAP_ENABLE            false  //true-false

/**
 * @brief 
 * 
 */
#define UART5_TX_PORT_PIN  AUX_PC12  //PC12-PB13-PB6-PB9
#define UART5_RX_PORT_PIN  AUX_PD2   //PD2-PB12-PB5-PB8

/**
 * @brief 
 * 
 */
//#define UART5_DE_ENABLE
#define UART5_DE_PORT_PIN  AUX_PC8  //PC8
#define UART5_DE_POLARITY_HIGH  true //true-false
#define UART5_DE_ASSERTION_TIME 31  //0~31
#define UART5_DE_DEASSERTION_TIME 31  //0~31

/**
 * @brief 
 * 
 */
//#define UART5_TX_DMA_CFG   DMA2_STREAM0
//#define UART5_RX_DMA_CFG   DMA2_STREAM1

#define UART5_TX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR
#define UART5_RX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR

/**
 * @brief 
 * 
 */
#define UART5_TX_DMA_IRQ_PreemptPriority  2
#define UART5_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART5_RX_DMA_IRQ_PreemptPriority  2
#define UART5_RX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART5_IRQ_PreemptPriority  2
#define UART5_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART5_OVERSAMPLING  UART_OVERSAMPLING_16 //UART_OVERSAMPLING_16-UART_OVERSAMPLING_8

/**
 * @brief 
 * 
 */
#define UART5_TXINVERT_ENABLE            false  //true-false
#define UART5_RXINVERT_ENABLE            false  //true-false
#define UART5_DATA_BINARY_INVERT_ENABLE  false  //true-false
#define UART5_PIN_SWAP_ENABLE            false  //true-false

/**
 * @brief 
 * 
 */
#define UART6_TX_PORT_PIN AUX_PG14  //PC6-PG14
#define UART6_RX_PORT_PIN AUX_PG9  //PC7-PG9

/**
 * @brief 
 * 
 */
//#define UART6_DE_ENABLE
#define UART6_DE_PORT_PIN  AUX_PG12  //PG8-PG12
#define UART6_DE_POLARITY_HIGH  true //true-false
#define UART6_DE_ASSERTION_TIME 31  //0~31
#define UART6_DE_DEASSERTION_TIME 31  //0~31

/**
 * @brief 
 * 
 */
#define UART6_TX_DMA_CFG   DMA1_STREAM4
#define UART6_RX_DMA_CFG   DMA1_STREAM5

#define UART6_TX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR
#define UART6_RX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR

/**
 * @brief 
 * 
 */
#define UART6_TX_DMA_IRQ_PreemptPriority  2
#define UART6_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART6_RX_DMA_IRQ_PreemptPriority  2
#define UART6_RX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART6_IRQ_PreemptPriority  2
#define UART6_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART6_OVERSAMPLING  UART_OVERSAMPLING_16 //UART_OVERSAMPLING_16-UART_OVERSAMPLING_8

/**
 * @brief 
 * 
 */
#define UART6_TXINVERT_ENABLE            false  //true-false
#define UART6_RXINVERT_ENABLE            false  //true-false
#define UART6_DATA_BINARY_INVERT_ENABLE  false  //true-false
#define UART6_PIN_SWAP_ENABLE            false  //true-false

/**
 * @brief 
 * 
 */
#define UART7_TX_PORT_PIN AUX_PE8  //PF7-PE8-PA15-PB4
#define UART7_RX_PORT_PIN AUX_PE7  //PF6-PE7-PA8-PB3

/**
 * @brief 
 * 
 */
//#define UART7_DE_ENABLE
#define UART7_DE_PORT_PIN  AUX_PE9  //PF8-PE9
#define UART7_DE_POLARITY_HIGH  true //true-false
#define UART7_DE_ASSERTION_TIME 31  //0~31
#define UART7_DE_DEASSERTION_TIME 31  //0~31

/**
 * @brief 
 * 
 */
// #define UART7_TX_DMA_CFG   DMA1_STREAM6
// #define UART7_RX_DMA_CFG   DMA1_STREAM7

#define UART7_TX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR
#define UART7_RX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR

/**
 * @brief 
 * 
 */
#define UART7_TX_DMA_IRQ_PreemptPriority  2
#define UART7_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART7_RX_DMA_IRQ_PreemptPriority  2
#define UART7_RX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART7_IRQ_PreemptPriority  2
#define UART7_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART7_OVERSAMPLING  UART_OVERSAMPLING_16 //UART_OVERSAMPLING_16-UART_OVERSAMPLING_8

/**
 * @brief 
 * 
 */
#define UART7_TXINVERT_ENABLE            false  //true-false
#define UART7_RXINVERT_ENABLE            false  //true-false
#define UART7_DATA_BINARY_INVERT_ENABLE  false  //true-false
#define UART7_PIN_SWAP_ENABLE            false  //true-false

/**
 * @brief 
 * 
 */
#define UART8_TX_PORT_PIN AUX_PE1  //PE1
#define UART8_RX_PORT_PIN AUX_PE0  //PE0

/**
 * @brief 
 * 
 */
//#define UART8_DE_ENABLE
#define UART8_DE_PORT_PIN  AUX_PD15  //PD15
#define UART8_DE_POLARITY_HIGH  true //true-false
#define UART8_DE_ASSERTION_TIME 31  //0~31
#define UART8_DE_DEASSERTION_TIME 31  //0~31

/**
 * @brief 
 * 
 */
#define UART8_TX_DMA_CFG   DMA1_STREAM6
#define UART8_RX_DMA_CFG   DMA1_STREAM7

#define UART8_TX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR
#define UART8_RX_DMA_MODE   DMA_NORMAL //DMA_NORMAL-DMA_CIRCULAR

/**
 * @brief 
 * 
 */
#define UART8_TX_DMA_IRQ_PreemptPriority  2
#define UART8_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART8_RX_DMA_IRQ_PreemptPriority  2
#define UART8_RX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART8_IRQ_PreemptPriority  2
#define UART8_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define UART8_OVERSAMPLING  UART_OVERSAMPLING_16 //UART_OVERSAMPLING_16-UART_OVERSAMPLING_8

/**
 * @brief 
 * 
 */
#define UART8_TXINVERT_ENABLE            false  //true-false
#define UART8_RXINVERT_ENABLE            false  //true-false
#define UART8_DATA_BINARY_INVERT_ENABLE  false  //true-false
#define UART8_PIN_SWAP_ENABLE            false  //true-false

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                       ##### Phal USBD_FS_VCP Parameter #####                     ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define USBD_FS_VCP_ENABLE

#define USBD_FS_VCP_IRQ_PreemptPriority    2
#define USBD_FS_VCP_IRQ_SubPriority        2

/** @defgroup USBD_DESC_Private_Defines USBD_DESC_Private_Defines
  * @brief Private defines.
  * @{
  */

#define USBD_VID                      1155
#define USBD_LANGID_STRING            1033
#define USBD_MANUFACTURER_STRING      "STMicroelectronics"
#define USBD_PID_FS                    22336
#define USBD_PRODUCT_STRING_FS        "Virtual ComPort"
#define USBD_CONFIGURATION_STRING_FS  "CDC Config"
#define USBD_INTERFACE_STRING_FS      "CDC Interface"

#define USB_SIZ_BOS_DESC              0x0C

/**
  * @}
  */

/** @defgroup USBD_DESC_Exported_Constants USBD_DESC_Exported_Constants
  * @brief Constants.
  * @{
  */
#define DEVICE_ID1            (UID_BASE)
#define DEVICE_ID2            (UID_BASE + 0x4)
#define DEVICE_ID3            (UID_BASE + 0x8)

#define USB_SIZ_STRING_SERIAL  0x1A

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Defines USBD_CDC_IF_Exported_Defines
  * @brief Defines.
  * @{
  */
/* Define size for the receive and transmit buffer over CDC */
//#define APP_RX_DATA_SIZE  2048
#define APP_TX_DATA_SIZE  2048
/**
  * @}
  */

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                       ##### Phal USBD_HS_VCP Parameter #####                     ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define USBD_HS_VCP_ENABLE

#define USBD_HS_VCP_IRQ_PreemptPriority    2
#define USBD_HS_VCP_IRQ_SubPriority        2

/** @defgroup USBD_DESC_Private_Defines USBD_DESC_Private_Defines
  * @brief Private defines.
  * @{
  */

#define USBD_VID                      1155
#define USBD_LANGID_STRING            1033
#define USBD_MANUFACTURER_STRING      "STMicroelectronics"
#define USBD_PID_HS                   22336
#define USBD_PRODUCT_STRING_HS        "STM32 Virtual ComPort"
#define USBD_CONFIGURATION_STRING_HS  "CDC Config"
#define USBD_INTERFACE_STRING_HS      "CDC Interface"

#define USB_SIZ_BOS_DESC              0x0C

/**
  * @}
  */

/** @defgroup USBD_DESC_Exported_Constants USBD_DESC_Exported_Constants
  * @brief Constants.
  * @{
  */
#define DEVICE_ID1            (UID_BASE)
#define DEVICE_ID2            (UID_BASE + 0x4)
#define DEVICE_ID3            (UID_BASE + 0x8)

#define USB_SIZ_STRING_SERIAL  0x1A

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Defines USBD_CDC_IF_Exported_Defines
  * @brief Defines.
  * @{
  */
/* Define size for the receive and transmit buffer over CDC */
//#define APP_RX_DATA_SIZE  2048
#define APP_TX_DATA_SIZE  2048
/**
  * @}
  */

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Phal CAN Parameter #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define CAN1_ENABLE
//#define CAN2_ENABLE

/**
 * @brief 
 * 
 */
#define CAN1_TX_PORT_PIN  AUX_PH13   //PA12-PH13-PD1-PB9
#define CAN1_RX_PORT_PIN  AUX_PH14   //PA11-PH14-PD0-PB8-PI9

/**
 * @brief 
 * 
 */
#define CAN1_TX_FIFO_ELEMNT_QTY 10

/**
 * @brief 
 * 
 */
#define CAN1_IT0_IRQ_PreemptPriority  0
#define CAN1_IT0_IRQ_SubPriority      0

/**
 * @brief 
 * 
 */
#define CAN1_IT1_IRQ_PreemptPriority  2
#define CAN1_IT1_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define CAN2_TX_PORT_PIN  AUX_PB13   //PB13-PB6
#define CAN2_RX_PORT_PIN  AUX_PB12   //PB12-PB5

/**
 * @brief 
 * 
 */
#define CAN2_TX_FIFO_ELEMNT_QTY 10

/**
 * @brief 
 * 
 */
#define CAN2_IT0_IRQ_PreemptPriority  2
#define CAN2_IT0_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define CAN2_IT1_IRQ_PreemptPriority  2
#define CAN2_IT1_IRQ_SubPriority      2

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Phal RTC Parameter #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define RTC_ENABLE

/**
 * @brief 
 * 
 */
#define RTC_CLOCK_SOURCE_EXTERNAL //EXTERNAL-INTERNAL

/**
 * @brief 
 * 
 */
#define START_DATE 2000

/**
 * @brief 
 * 
 */
#define RTC_DAYLIGHTSAVING RTC_DAYLIGHTSAVING_NONE //NONE-SUB1H-ADD1H

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Phal SPI Parameter #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
#define SPI1_ENABLE
//#define SPI2_ENABLE
//#define SPI3_ENABLE
//#define SPI4_ENABLE
//#define SPI5_ENABLE
//#define SPI6_ENABLE

/**
 * @brief 
 * 
 */
#define SPI1_NSS_PORT_PIN  AUX_PA4    //PA4-PA15
#define SPI1_SCK_PORT_PIN  AUX_PA5   //PA5-PG11-PB3
#define SPI1_MISO_PORT_PIN  AUX_PA6   //PA6-PG9-PB4
#define SPI1_MOSI_PORT_PIN  AUX_PA7   //PA7-PD7-PB5

#define SPI1_NSS_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI1_NSS_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI1_SCK_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI1_SCK_PIN_PULL  GPIO_PULLUP //NOPULL-PULLUP-PULLDOWN

#define SPI1_MISO_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI1_MISO_PIN_PULL  GPIO_PULLUP //NOPULL-PULLUP-PULLDOWN

#define SPI1_MOSI_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI1_MOSI_PIN_PULL  GPIO_PULLUP //NOPULL-PULLUP-PULLDOWN

/**
 * @brief 
 * 
 */
#define SPI1_DIRECTION  SPI_DIRECTION_2LINES  // SPI_DIRECTION_2LINES-SPI_DIRECTION_2LINES_RXONLY-SPI_DIRECTION_1LINE
#define SPI1_NSS        SPI_NSS_SOFT          // SPI_NSS_SOFT-SPI_NSS_HARD_INPUT-SPI_NSS_HARD_OUTPUT
#define SPI1_FIRSTBIT   SPI_FIRSTBIT_MSB      // SPI_FIRSTBIT_MSB-SPI_FIRSTBIT_LSB
#define SPI1_DMA_MODE   DMA_NORMAL          // DMA_CIRCULAR-DMA_NORMAL

/**
 * @brief 
 * 
 */
#define SPI1_BAUD SPI_BAUDRATEPRESCALER_256 //2-4-8-15-32-64-128

/**
 * @brief 
 * 
 */
#define SPI1_TX_DMA_CFG   DMA1_STREAM6
#define SPI1_RX_DMA_CFG   DMA1_STREAM7

/**
 * @brief 
 * 
 */
#define SPI1_TX_DMA_IRQ_PreemptPriority  2
#define SPI1_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define SPI1_RX_DMA_IRQ_PreemptPriority  2
#define SPI1_RX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define SPI2_NSS_PORT_PIN  AUX_PB9    //PB9-PB12-PI0
#define SPI2_SCK_PORT_PIN  AUX_PB13   //PB10-PB13-PI1-PA9-PA12-PD3
#define SPI2_MISO_PORT_PIN  AUX_PB14   //PC2-PB14-PI2
#define SPI2_MOSI_PORT_PIN  AUX_PB15   //PC1-PC3-PB13-PI3-PB15

#define SPI2_NSS_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI2_NSS_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI2_SCK_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI2_SCK_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI2_MISO_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI2_MISO_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI2_MOSI_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI2_MOSI_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

/**
 * @brief 
 * 
 */
#define SPI2_DIRECTION  SPI_DIRECTION_2LINES  // SPI_DIRECTION_2LINES-SPI_DIRECTION_2LINES_RXONLY-SPI_DIRECTION_1LINE
#define SPI2_NSS        SPI_NSS_SOFT          // SPI_NSS_SOFT-SPI_NSS_HARD_INPUT-SPI_NSS_HARD_OUTPUT
#define SPI2_FIRSTBIT   SPI_FIRSTBIT_MSB      // SPI_FIRSTBIT_MSB-SPI_FIRSTBIT_LSB
#define SPI2_DMA_MODE   DMA_NORMAL            // DMA_CIRCULAR-DMA_NORMAL

/**
 * @brief 
 * 
 */
#define SPI2_BAUD SPI_BAUDRATEPRESCALER_128 //2-4-8-15-32-64-128

/**
 * @brief 
 * 
 */
//#define SPI2_TX_DMA_CFG   DMA1_STREAM2
//#define SPI2_RX_DMA_CFG   DMA1_STREAM2

/**
 * @brief 
 * 
 */
#define SPI2_TX_DMA_IRQ_PreemptPriority  2
#define SPI2_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define SPI2_RX_DMA_IRQ_PreemptPriority  2
#define SPI2_RX_DMA_IRQ_SubPriority      2
  
/**
 * @brief 
 * 
 */
#define SPI3_NSS_PORT_PIN  AUX_PA4    //PA4-PA15
#define SPI3_SCK_PORT_PIN  AUX_PC10   //PC10-PB3
#define SPI3_MISO_PORT_PIN  AUX_PC11   //PC11-PB4
#define SPI3_MOSI_PORT_PIN  AUX_PC12   //PC12-PD6-PB5

#define SPI3_NSS_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI3_NSS_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI3_SCK_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI3_SCK_PIN_PULL  GPIO_PULLUP //NOPULL-PULLUP-PULLDOWN

#define SPI3_MISO_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI3_MISO_PIN_PULL  GPIO_PULLUP //NOPULL-PULLUP-PULLDOWN

#define SPI3_MOSI_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI3_MOSI_PIN_PULL  GPIO_PULLUP //NOPULL-PULLUP-PULLDOWN

/**
 * @brief 
 * 
 */
#define SPI3_DIRECTION  SPI_DIRECTION_2LINES  // SPI_DIRECTION_2LINES-SPI_DIRECTION_2LINES_RXONLY-SPI_DIRECTION_1LINE
#define SPI3_NSS        SPI_NSS_SOFT          // SPI_NSS_SOFT-SPI_NSS_HARD_INPUT-SPI_NSS_HARD_OUTPUT
#define SPI3_FIRSTBIT   SPI_FIRSTBIT_MSB      // SPI_FIRSTBIT_MSB-SPI_FIRSTBIT_LSB
#define SPI3_DMA_MODE   DMA_NORMAL            // DMA_CIRCULAR-DMA_NORMAL

/**
 * @brief 
 * 
 */
#define SPI3_BAUD SPI_BAUDRATEPRESCALER_32 //2-4-8-15-32-64-128

/**
 * @brief 
 * 
 */
//#define SPI3_TX_DMA_CFG   DMA1_STREAM2
//#define SPI3_RX_DMA_CFG   DMA1_STREAM2

/**
 * @brief 
 * 
 */
#define SPI3_TX_DMA_IRQ_PreemptPriority  2
#define SPI3_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define SPI3_RX_DMA_IRQ_PreemptPriority  2
#define SPI3_RX_DMA_IRQ_SubPriority      2
  
/**
 * @brief 
 * 
 */
#define SPI4_NSS_PORT_PIN  AUX_PE4     //PE4-PE11
#define SPI4_SCK_PORT_PIN  AUX_PE2     //PE2-PE12
#define SPI4_MISO_PORT_PIN  AUX_PE5   //PE5-PE13
#define SPI4_MOSI_PORT_PIN  AUX_PE6   //PE6-PE14

#define SPI4_NSS_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI4_NSS_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI4_SCK_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI4_SCK_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI4_MISO_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI4_MISO_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI4_MOSI_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI4_MOSI_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

/**
 * @brief 
 * 
 */
#define SPI4_DIRECTION  SPI_DIRECTION_2LINES  // SPI_DIRECTION_2LINES-SPI_DIRECTION_2LINES_RXONLY-SPI_DIRECTION_1LINE
#define SPI4_NSS        SPI_NSS_SOFT          // SPI_NSS_SOFT-SPI_NSS_HARD_INPUT-SPI_NSS_HARD_OUTPUT
#define SPI4_FIRSTBIT   SPI_FIRSTBIT_MSB      // SPI_FIRSTBIT_MSB-SPI_FIRSTBIT_LSB
#define SPI4_DMA_MODE   DMA_NORMAL          // DMA_CIRCULAR-DMA_NORMAL

/**
 * @brief 
 * 
 */
#define SPI4_BAUD SPI_BAUDRATEPRESCALER_128 //2-4-8-15-32-64-128

/**
 * @brief 
 * 
 */
//#define SPI4_TX_DMA_CFG   DMA1_STREAM2
//#define SPI4_RX_DMA_CFG   DMA1_STREAM2

/**
 * @brief 
 * 
 */
#define SPI4_TX_DMA_IRQ_PreemptPriority  2
#define SPI4_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define SPI4_RX_DMA_IRQ_PreemptPriority  2
#define SPI4_RX_DMA_IRQ_SubPriority      2
  
/**
 * @brief 
 * 
 */
#define SPI5_NSS_PORT_PIN   AUX_PF6   //PF6-PH5
#define SPI5_SCK_PORT_PIN   AUX_PF7   //PF7-PH6
#define SPI5_MISO_PORT_PIN  AUX_PF8   //PF8-PH7
#define SPI5_MOSI_PORT_PIN  AUX_PF9   //PF9-PF11

#define SPI5_NSS_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI5_NSS_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI5_SCK_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI5_SCK_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI5_MISO_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI5_MISO_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI5_MOSI_PIN_MODE  GPIO_MODE_AF_PP //OD-PP
#define SPI5_MOSI_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

/**
 * @brief 
 * 
 */
#define SPI5_DIRECTION  SPI_DIRECTION_2LINES  // SPI_DIRECTION_2LINES-SPI_DIRECTION_2LINES_RXONLY-SPI_DIRECTION_1LINE
#define SPI5_NSS        SPI_NSS_SOFT          // SPI_NSS_SOFT-SPI_NSS_HARD_INPUT-SPI_NSS_HARD_OUTPUT
#define SPI5_FIRSTBIT   SPI_FIRSTBIT_MSB      // SPI_FIRSTBIT_MSB-SPI_FIRSTBIT_LSB
#define SPI5_DMA_MODE   DMA_NORMAL          // DMA_CIRCULAR-DMA_NORMAL

/**
 * @brief 
 * 
 */
#define SPI5_BAUD SPI_BAUDRATEPRESCALER_128 //2-4-8-15-32-64-128

/**
 * @brief 
 * 
 */
//#define SPI5_TX_DMA_CFG   DMA1_STREAM2
//#define SPI5_RX_DMA_CFG   DMA1_STREAM2

/**
 * @brief 
 * 
 */
#define SPI5_TX_DMA_IRQ_PreemptPriority  2
#define SPI5_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define SPI5_RX_DMA_IRQ_PreemptPriority  2
#define SPI5_RX_DMA_IRQ_SubPriority      2
  
/**
 * @brief 
 * 
 */
#define SPI6_NSS_PORT_PIN  AUX_PG8    //PG8
#define SPI6_SCK_PORT_PIN  AUX_PG13   //PG13
#define SPI6_MISO_PORT_PIN  AUX_PG12   //PG12
#define SPI6_MOSI_PORT_PIN  AUX_PG14   //PG14

#define SPI6_NSS_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define SPI6_NSS_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI6_SCK_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define SPI6_SCK_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI6_MISO_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define SPI6_MISO_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define SPI6_MOSI_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define SPI6_MOSI_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

/**
 * @brief 
 * 
 */
#define SPI6_DIRECTION  SPI_DIRECTION_2LINES  // SPI_DIRECTION_2LINES-SPI_DIRECTION_2LINES_RXONLY-SPI_DIRECTION_1LINE
#define SPI6_NSS        SPI_NSS_SOFT          // SPI_NSS_SOFT-SPI_NSS_HARD_INPUT-SPI_NSS_HARD_OUTPUT
#define SPI6_FIRSTBIT   SPI_FIRSTBIT_MSB      // SPI_FIRSTBIT_MSB-SPI_FIRSTBIT_LSB
#define SPI6_DMA_MODE   DMA_CIRCULAR          // DMA_CIRCULAR-DMA_NORMAL

/**
 * @brief 
 * 
 */
#define SPI6_BAUD SPI_BAUDRATEPRESCALER_2 //2-4-8-15-32-64-128

/**
 * @brief 
 * 
 */
//#define SPI6_TX_DMA_CFG   DMA1_STREAM2
//#define SPI6_RX_DMA_CFG   DMA1_STREAM2

/**
 * @brief 
 * 
 */
#define SPI6_TX_DMA_IRQ_PreemptPriority  2
#define SPI6_TX_DMA_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define SPI6_RX_DMA_IRQ_PreemptPriority  2
#define SPI6_RX_DMA_IRQ_SubPriority      2

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Phal I2C Parameter #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define I2C1_ENABLE
//#define I2C2_ENABLE
//#define I2C3_ENABLE
//#define I2C4_ENABLE

/**
 * @brief 
 * 
 */
#define I2C1_SCL_PORT_PIN  AUX_PB6    //PB6-PB8
#define I2C1_SDA_PORT_PIN  AUX_PB7   //PB7-PB9

#define I2C1_SCL_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define I2C1_SCL_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define I2C1_SDA_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define I2C1_SDA_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

/**
 * @brief 
 * 
 */
#define I2C1_TIMING                 0x307075B1
#define I2C1_ADDRESSINGMODE          I2C_ADDRESSINGMODE_7BIT   //I2C_ADDRESSINGMODE_7BIT-I2C_ADDRESSINGMODE_10BIT
#define I2C1_DUALADDRESS             I2C_DUALADDRESS_DISABLED  //I2C_DUALADDRESS_DISABLED-I2C_DUALADDRESS_ENABLED
#define I2C1_GENERALCALL             I2C_GENERALCALL_DISABLED  //I2C_GENERALCALL_DISABLED-I2C_GENERALCALL_ENABLED

/**
 * @brief 
 * 
 */
#define I2C1_ER_IRQ_PreemptPriority  2
#define I2C1_ER_IRQ_SubPriority      2
  
/**
 * @brief 
 * 
 */
#define I2C2_SCL_PORT_PIN  AUX_PF1    //PF1-PH4-PB10
#define I2C2_SDA_PORT_PIN  AUX_PF0   //PF0-PH5-PB11

#define I2C2_SCL_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define I2C2_SCL_PIN_PULL  GPIO_PULLUP //NOPULL-PULLUP-PULLDOWN

#define I2C2_SDA_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define I2C2_SDA_PIN_PULL  GPIO_PULLUP //NOPULL-PULLUP-PULLDOWN

/**
 * @brief 
 * 
 */
#define I2C2_TIMING                 0x307075B1
#define I2C2_ADDRESSINGMODE          I2C_ADDRESSINGMODE_7BIT   //I2C_ADDRESSINGMODE_7BIT-I2C_ADDRESSINGMODE_10BIT
#define I2C2_DUALADDRESS             I2C_DUALADDRESS_DISABLED  //I2C_DUALADDRESS_DISABLED-I2C_DUALADDRESS_ENABLED
#define I2C2_GENERALCALL             I2C_GENERALCALL_DISABLED  //I2C_GENERALCALL_DISABLED-I2C_GENERALCALL_ENABLED

/**
 * @brief 
 * 
 */
#define I2C2_ER_IRQ_PreemptPriority  2
#define I2C2_ER_IRQ_SubPriority      2
  
/**
 * @brief 
 * 
 */
#define I2C3_SCL_PORT_PIN  AUX_PA8    //PA8-PH7
#define I2C3_SDA_PORT_PIN  AUX_PC9   //PC9-PH8

#define I2C3_SCL_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define I2C3_SCL_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

#define I2C3_SDA_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define I2C3_SDA_PIN_PULL  GPIO_NOPULL //NOPULL-PULLUP-PULLDOWN

/**
 * @brief 
 * 
 */
#define I2C3_TIMING                 0x307075B1
#define I2C3_ADDRESSINGMODE          I2C_ADDRESSINGMODE_7BIT   //I2C_ADDRESSINGMODE_7BIT-I2C_ADDRESSINGMODE_10BIT
#define I2C3_DUALADDRESS             I2C_DUALADDRESS_DISABLED  //I2C_DUALADDRESS_DISABLED-I2C_DUALADDRESS_ENABLED
#define I2C3_GENERALCALL             I2C_GENERALCALL_DISABLED  //I2C_GENERALCALL_DISABLED-I2C_GENERALCALL_ENABLED

/**
 * @brief 
 * 
 */
#define I2C3_ER_IRQ_PreemptPriority  2
#define I2C3_ER_IRQ_SubPriority      2
  
/**
 * @brief 
 * 
 */
#define I2C4_SCL_PORT_PIN  AUX_PF14    //PF14-PH11-PD12-PB6-PB8
#define I2C4_SDA_PORT_PIN  AUX_PF15   //PF15-PH12-PD13-PB7-PB9

#define I2C4_SCL_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define I2C4_SCL_PIN_PULL  GPIO_PULLUP //NOPULL-PULLUP-PULLDOWN

#define I2C4_SDA_PIN_MODE  GPIO_MODE_AF_OD //OD-PP
#define I2C4_SDA_PIN_PULL  GPIO_PULLUP //NOPULL-PULLUP-PULLDOWN

/**
 * @brief 
 * 
 */
#define I2C4_TIMING                 0x307075B1
#define I2C4_ADDRESSINGMODE          I2C_ADDRESSINGMODE_7BIT   //I2C_ADDRESSINGMODE_7BIT-I2C_ADDRESSINGMODE_10BIT
#define I2C4_DUALADDRESS             I2C_DUALADDRESS_DISABLED  //I2C_DUALADDRESS_DISABLED-I2C_DUALADDRESS_ENABLED
#define I2C4_GENERALCALL             I2C_GENERALCALL_DISABLED  //I2C_GENERALCALL_DISABLED-I2C_GENERALCALL_ENABLED

/**
 * @brief 
 * 
 */
#define I2C4_ER_IRQ_PreemptPriority  2
#define I2C4_ER_IRQ_SubPriority      2
  
/**
 * @brief 
 * 
 */
#define I2C_STRETCH_MAX_CLOCK 30

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Phal TICK Parameter #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
#define PHAL_TICK_ENABLE

/**
 * @brief 
 * 
 */
#define HAL_TICK TICK_TIM2 //TIM2-TIM5

/**
 * @brief 
 * 
 */
#define HAL_TICK_ns  1000

/**
 * @brief 
 * 
 */
#define HAL_TICK_TOP_VALUE  0xFFFFFFFF

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                         ##### Phal TIMER Parameter #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define TIMER_CH1_ENABLE                      // This Channel use TIM1 
//#define TIMER_CH2_ENABLE                      // This Channel use TIM2 
//#define TIMER_CH3_ENABLE                      // This Channel use TIM3
//#define TIMER_CH4_ENABLE                      // This Channel use TIM4 
//#define TIMER_CH5_ENABLE                      // This Channel use TIM5 
#define TIMER_CH6_ENABLE                      // This Channel use TIM6 
#define TIMER_CH7_ENABLE                      // This Channel use TIM7 
//#define TIMER_CH8_ENABLE                      // This Channel use TIM8 
  
/**
 * @brief 
 * 
 */
#define TIMER_CH1_IRQ_PreemptPriority  2
#define TIMER_CH1_IRQ_SubPriority      2
  
/**
 * @brief 
 * 
 */
#define TIMER_CH2_IRQ_PreemptPriority  2
#define TIMER_CH2_IRQ_SubPriority      2
 
/**
 * @brief 
 * 
 */
#define TIMER_CH3_IRQ_PreemptPriority  2
#define TIMER_CH3_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define TIMER_CH4_IRQ_PreemptPriority  2
#define TIMER_CH4_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define TIMER_CH5_IRQ_PreemptPriority  2
#define TIMER_CH5_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define TIMER_CH6_IRQ_PreemptPriority  2
#define TIMER_CH6_IRQ_SubPriority      2

/** 
  * @brief
  */
#define TIMER_CH7_IRQ_PreemptPriority  2
#define TIMER_CH7_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define TIMER_CH8_IRQ_PreemptPriority  2
#define TIMER_CH8_IRQ_SubPriority      2

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Phal PWM Parameter #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
//Help :  CENTERALIGNED3 : Event on both top & zero counter value.
//        CENTERALIGNED2 : Event on top  counter value.
//        CENTERALIGNED1 : Event on zero counter value.

/**
 * @brief 
 * 
 */
//#define TIM1_PWM_CH1_ENABLE
//#define TIM1_PWM_CH2_ENABLE
//#define TIM1_PWM_CH3_ENABLE
//#define TIM1_PWM_CH4_ENABLE

/**
 * @brief 
 * 
 */
#define TIM1_PWM_IRQ_PreemptPriority  0
#define TIM1_PWM_IRQ_SubPriority      0

/**
 * @brief 
 * 
 */
#define TIM1_PWM_MODE TIM_COUNTERMODE_CENTERALIGNED3 //UP-DOWN-CENTERALIGNED1-CENTERALIGNED2-CENTERALIGNED3
#define TIM1_PWM_CLOCK_DIVISION 0
#define TIM1_PWM_PRESCALER 0
#define TIM1_REPETITION_COUNTER 1
#define TIM1_UPDATE_OVF true

/**
 * @brief 
 * 
 */
#define TIM1_SYNC_MASTER_ENABLE
#define TIM1_SYNC_MASTER_MODE TIM_TRGO_UPDATE

//#define TIM1_SYNC_SLAVE_ENABLE
#define TIM1_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM1_SYNC_SLAVE_TRIGGER   TIM_TS_ITR3

/**
 * @brief 
 * 
 */
#define TIM1_PWM_CH1_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define TIM1_PWM_CH1_PORT_PIN  AUX_PE9 //PE9-PA8

#define TIM1_PWM_CH2_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define TIM1_PWM_CH2_PORT_PIN  AUX_PE11 //PE11-PA9

#define TIM1_PWM_CH3_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define TIM1_PWM_CH3_PORT_PIN  AUX_PE13 //PE13-PA10

#define TIM1_PWM_CH4_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define TIM1_PWM_CH4_PORT_PIN  AUX_PE14 //PE14-PA11

/**
 * @brief 
 * 
 */
//#define TIM2_PWM_CH1_ENABLE
//#define TIM2_PWM_CH2_ENABLE
//#define TIM2_PWM_CH3_ENABLE
//#define TIM2_PWM_CH4_ENABLE

/**
 * @brief 
 * 
 */
#define TIM2_PWM_IRQ_PreemptPriority  2
#define TIM2_PWM_IRQ_SubPriority      2
 
/**
 * @brief 
 * 
 */
#define TIM2_PWM_MODE TIM_COUNTERMODE_CENTERALIGNED3 //UP-DOWN-CENTERALIGNED1-CENTERALIGNED2-CENTERALIGNED3
#define TIM2_PWM_CLOCK_DIVISION 0
#define TIM2_PWM_PRESCALER 0
#define TIM2_REPETITION_COUNTER 0

/**
 * @brief 
 * 
 */
//#define TIM2_SYNC_MASTER_ENABLE
#define TIM2_SYNC_MASTER_MODE TIM_TRGO_UPDATE

//#define TIM2_SYNC_SLAVE_ENABLE
#define TIM2_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM2_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0

/**
 * @brief 
 * 
 */
#define TIM2_PWM_CH1_PORT_PIN  AUX_PA0 //PA0-PA5-PA15
#define TIM2_PWM_CH2_PORT_PIN  AUX_PA1 //PA1-PB3
#define TIM2_PWM_CH3_PORT_PIN  AUX_PB10 //PA2-PB10
#define TIM2_PWM_CH4_PORT_PIN  AUX_PB11 //PA3-PB11

/**
 * @brief 
 * 
 */
//#define TIM3_PWM_CH1_ENABLE
//#define TIM3_PWM_CH2_ENABLE
//#define TIM3_PWM_CH3_ENABLE
//#define TIM3_PWM_CH4_ENABLE

/**
 * @brief 
 * 
 */
#define TIM3_PWM_IRQ_PreemptPriority  2
#define TIM3_PWM_IRQ_SubPriority      2
 
/**
 * @brief 
 * 
 */
#define TIM3_PWM_MODE TIM_COUNTERMODE_CENTERALIGNED3 //UP-DOWN-CENTERALIGNED1-CENTERALIGNED2-CENTERALIGNED3
#define TIM3_PWM_CLOCK_DIVISION 0
#define TIM3_PWM_PRESCALER 0
#define TIM3_REPETITION_COUNTER 0

/**
 * @brief 
 * 
 */
//#define TIM3_SYNC_MASTER_ENABLE
#define TIM3_SYNC_MASTER_MODE TIM_TRGO_UPDATE

//#define TIM3_SYNC_SLAVE_ENABLE
#define TIM3_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM3_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0

/**
 * @brief 
 * 
 */
#define TIM3_PWM_CH1_PORT_PIN  AUX_PC6 //PA6-PC6-PB4
#define TIM3_PWM_CH2_PORT_PIN  AUX_PC7 //PA7-PC7-PB5
#define TIM3_PWM_CH3_PORT_PIN  AUX_PC8 //PB0-PC8
#define TIM3_PWM_CH4_PORT_PIN  AUX_PC9 //PB1-PC9

/**
 * @brief 
 * 
 */
//#define TIM4_PWM_CH1_ENABLE
//#define TIM4_PWM_CH2_ENABLE
//#define TIM4_PWM_CH3_ENABLE
//#define TIM4_PWM_CH4_ENABLE

/**
 * @brief 
 * 
 */
#define TIM4_PWM_IRQ_PreemptPriority  2
#define TIM4_PWM_IRQ_SubPriority      2
 
/**
 * @brief 
 * 
 */
#define TIM4_PWM_MODE TIM_COUNTERMODE_CENTERALIGNED3 //UP-DOWN-CENTERALIGNED1-CENTERALIGNED2-CENTERALIGNED3
#define TIM4_PWM_CLOCK_DIVISION 0
#define TIM4_PWM_PRESCALER 0
#define TIM4_REPETITION_COUNTER 0

/**
 * @brief 
 * 
 */
//#define TIM4_SYNC_MASTER_ENABLE
#define TIM4_SYNC_MASTER_MODE TIM_TRGO_UPDATE

//#define TIM4_SYNC_SLAVE_ENABLE
#define TIM4_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM4_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0

/**
 * @brief 
 * 
 */
#define TIM4_PWM_CH1_PORT_PIN  AUX_PD12 //PD12-PB6
#define TIM4_PWM_CH2_PORT_PIN  AUX_PD13 //PD13-PB7
#define TIM4_PWM_CH3_PORT_PIN  AUX_PD14 //PD14-PB8
#define TIM4_PWM_CH4_PORT_PIN  AUX_PB9 //PD15-PB9

/**
 * @brief 
 * 
 */
//#define TIM5_PWM_CH1_ENABLE
//#define TIM5_PWM_CH2_ENABLE
//#define TIM5_PWM_CH3_ENABLE
//#define TIM5_PWM_CH4_ENABLE

/**
 * @brief 
 * 
 */
#define TIM5_PWM_IRQ_PreemptPriority  2
#define TIM5_PWM_IRQ_SubPriority      2
 
/**
 * @brief 
 * 
 */
#define TIM5_PWM_MODE TIM_COUNTERMODE_CENTERALIGNED3 //UP-DOWN-CENTERALIGNED1-CENTERALIGNED2-CENTERALIGNED3
#define TIM5_PWM_CLOCK_DIVISION 0
#define TIM5_PWM_PRESCALER 0
#define TIM5_REPETITION_COUNTER 0

/**
 * @brief 
 * 
 */
//#define TIM5_SYNC_MASTER_ENABLE
#define TIM5_SYNC_MASTER_MODE TIM_TRGO_UPDATE

//#define TIM5_SYNC_SLAVE_ENABLE
#define TIM5_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM5_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0

/**
 * @brief 
 * 
 */
#define TIM5_PWM_CH1_PORT_PIN  AUX_PA0 //PH10-PA0
#define TIM5_PWM_CH2_PORT_PIN  AUX_PA1 //PH11-PA1
#define TIM5_PWM_CH3_PORT_PIN  AUX_PA2 //PH12-PA2
#define TIM5_PWM_CH4_PORT_PIN  AUX_PA3 //PI0-PA3

/**
 * @brief 
 * 
 */
//#define TIM8_PWM_CH1_ENABLE
//#define TIM8_PWM_CH2_ENABLE
//#define TIM8_PWM_CH3_ENABLE
//#define TIM8_PWM_CH4_ENABLE

/**
 * @brief 
 * 
 */
#define TIM8_PWM_IRQ_PreemptPriority  2
#define TIM8_PWM_IRQ_SubPriority      2
 
/**
 * @brief 
 * 
 */
#define TIM8_PWM_MODE TIM_COUNTERMODE_CENTERALIGNED3 //UP-DOWN-CENTERALIGNED1-CENTERALIGNED2-CENTERALIGNED3
#define TIM8_PWM_CLOCK_DIVISION 0
#define TIM8_PWM_PRESCALER 0
#define TIM8_REPETITION_COUNTER 1
#define TIM8_UPDATE_OVF true

/**
 * @brief 
 * 
 */
//#define TIM8_SYNC_MASTER_ENABLE
#define TIM8_SYNC_MASTER_MODE TIM_TRGO_UPDATE

#define TIM8_SYNC_SLAVE_ENABLE
#define TIM8_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM8_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0 //TIM_TS_ITR2

/**
 * @brief 
 * 
 */
#define TIM8_PWM_CH1_POLARITY  TIM_OCPOLARITY_LOW //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define TIM8_PWM_CH1_PORT_PIN  AUX_PC6 //PC6-PI5

#define TIM8_PWM_CH2_POLARITY  TIM_OCPOLARITY_LOW //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define TIM8_PWM_CH2_PORT_PIN  AUX_PC7 //PC7-PI6

#define TIM8_PWM_CH3_POLARITY  TIM_OCPOLARITY_LOW //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define TIM8_PWM_CH3_PORT_PIN  AUX_PC8 //PC8-PI7

#define TIM8_PWM_CH4_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define TIM8_PWM_CH4_PORT_PIN  AUX_PC9 //PC9-PI2

/**
 * @brief 
 * 
 */
//#define TIM9_PWM_CH1_ENABLE
//#define TIM9_PWM_CH2_ENABLE

/**
 * @brief 
 * 
 */
#define TIM9_PWM_IRQ_PreemptPriority  2
#define TIM9_PWM_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define TIM9_PWM_CLOCK_DIVISION 0
#define TIM9_PWM_PRESCALER 0
#define TIM9_REPETITION_COUNTER 0

/**
 * @brief 
 * 
 */
//#define TIM9_SYNC_MASTER_ENABLE
#define TIM9_SYNC_MASTER_MODE TIM_TRGO_UPDATE

//#define TIM9_SYNC_SLAVE_ENABLE
#define TIM9_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM9_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0
 
/**
 * @brief 
 * 
 */
#define TIM9_PWM_CH1_PORT_PIN  AUX_PA2 //PE5-PA2
#define TIM9_PWM_CH2_PORT_PIN  AUX_PA3 //PA3

/**
 * @brief 
 * 
 */
//#define TIM10_PWM_CH1_ENABLE

/**
 * @brief 
 * 
 */
#define TIM10_PWM_CLOCK_DIVISION 0
#define TIM10_PWM_PRESCALER 0
#define TIM10_REPETITION_COUNTER 0

/**
 * @brief 
 * 
 */
//#define TIM10_SYNC_MASTER_ENABLE
#define TIM10_SYNC_MASTER_MODE TIM_TRGO_UPDATE

//#define TIM10_SYNC_SLAVE_ENABLE
#define TIM10_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM10_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0

/**
 * @brief 
 * 
 */
#define TIM10_PWM_CH1_PORT_PIN  AUX_PB8 //PF6-PB8

/**
 * @brief 
 * 
 */
//#define TIM11_PWM_CH1_ENABLE

/**
 * @brief 
 * 
 */
#define TIM11_PWM_CLOCK_DIVISION 0
#define TIM11_PWM_PRESCALER 0
#define TIM11_REPETITION_COUNTER 0

/**
 * @brief 
 * 
 */
//#define TIM11_SYNC_MASTER_ENABLE
#define TIM11_SYNC_MASTER_MODE TIM_TRGO_UPDATE

//#define TIM11_SYNC_SLAVE_ENABLE
#define TIM11_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM11_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0

/**
 * @brief 
 * 
 */
#define TIM11_PWM_CH1_PORT_PIN  AUX_PB9 //PF7-PB9

/**
 * @brief 
 * 
 */
//#define TIM12_PWM_CH1_ENABLE
//#define TIM12_PWM_CH2_ENABLE

/**
 * @brief 
 * 
 */
#define TIM12_PWM_CLOCK_DIVISION 0
#define TIM12_PWM_PRESCALER 0
#define TIM12_REPETITION_COUNTER 0

/**
 * @brief 
 * 
 */
//#define TIM12_SYNC_MASTER_ENABLE
#define TIM12_SYNC_MASTER_MODE TIM_TRGO_UPDATE

//#define TIM12_SYNC_SLAVE_ENABLE
#define TIM12_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM12_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0

/**
 * @brief 
 * 
 */
#define TIM12_PWM_CH1_PORT_PIN  AUX_PB14 //PH6-PB14
#define TIM12_PWM_CH2_PORT_PIN  AUX_PB15 //PH9-PB15

/**
 * @brief 
 * 
 */
//#define TIM13_PWM_CH1_ENABLE

/**
 * @brief 
 * 
 */
#define TIM13_PWM_CLOCK_DIVISION 0
#define TIM13_PWM_PRESCALER 0
#define TIM13_REPETITION_COUNTER 0

/**
 * @brief 
 * 
 */
//#define TIM13_SYNC_MASTER_ENABLE
#define TIM13_SYNC_MASTER_MODE TIM_TRGO_UPDATE

//#define TIM13_SYNC_SLAVE_ENABLE
#define TIM13_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM13_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0

/**
 * @brief 
 * 
 */
#define TIM13_PWM_CH1_PORT_PIN  AUX_PF8 //PF8-PA6

/**
 * @brief 
 * 
 */
//#define TIM14_PWM_CH1_ENABLE

/**
 * @brief 
 * 
 */
#define TIM14_PWM_CLOCK_DIVISION 0
#define TIM14_PWM_PRESCALER 0
#define TIM14_REPETITION_COUNTER 0

/**
 * @brief 
 * 
 */
//#define TIM14_SYNC_MASTER_ENABLE
#define TIM14_SYNC_MASTER_MODE TIM_TRGO_UPDATE

//#define TIM14_SYNC_SLAVE_ENABLE
#define TIM14_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
#define TIM14_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0

/**
 * @brief 
 * 
 */
#define TIM14_PWM_CH1_PORT_PIN  AUX_PF9 //PF9-PA7

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                       ##### Phal HRTIM PWM Parameter #####                       ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define HRTIM1_PWM_CHA1_ENABLE
//#define HRTIM1_PWM_CHA2_ENABLE
//#define HRTIM1_PWM_CHB1_ENABLE
//#define HRTIM1_PWM_CHB2_ENABLE
//#define HRTIM1_PWM_CHC1_ENABLE
//#define HRTIM1_PWM_CHC2_ENABLE
//#define HRTIM1_PWM_CHD1_ENABLE
//#define HRTIM1_PWM_CHD2_ENABLE
//#define HRTIM1_PWM_CHE1_ENABLE
//#define HRTIM1_PWM_CHE2_ENABLE

/**
 * @brief 
 * 
 */
//#define TIM1_PWM_IRQ_PreemptPriority  2
//#define TIM1_PWM_IRQ_SubPriority      2
 
/**
 * @brief 
 * 
 */
//#define TIM1_PWM_MODE TIM_COUNTERMODE_UP //UP-DOWN-CENTERALIGNED1-CENTERALIGNED2-CENTERALIGNED3
#define HRTIM1_PWM_CLOCK_DIVISION 0
#define HRTIM1_PWM_PRESCALER HRTIM_PRESCALERRATIO_DIV1 //HRTIM_PRESCALERRATIO_DIV1,2,4

/**
 * @brief 
 * 
 */
//#define TIM1_SYNC_MASTER_ENABLE
//#define TIM1_SYNC_SLAVE_ENABLE
//#define TIM1_SYNC_SLAVE_MODE      TIM_SLAVEMODE_RESET
//#define TIM1_SYNC_SLAVE_TRIGGER   TIM_TS_ITR0

/**
 * @brief 
 * 
 */
//#define HRTIM1_PWM_CHA1_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define HRTIM1_PWM_CHA1_PORT_PIN  AUX_PC6 //PC6

//#define HRTIM1_PWM_CHA2_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define HRTIM1_PWM_CHA2_PORT_PIN  AUX_PC7 //PC7

//#define HRTIM1_PWM_CHB1_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define HRTIM1_PWM_CHB1_PORT_PIN  AUX_PC8 //PC8

//#define HRTIM1_PWM_CHB2_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define HRTIM1_PWM_CHB2_PORT_PIN  AUX_PA8 //PA8

//#define HRTIM1_PWM_CHC1_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define HRTIM1_PWM_CHC1_PORT_PIN  AUX_PA9 //PA9

//#define HRTIM1_PWM_CHC2_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define HRTIM1_PWM_CHC2_PORT_PIN  AUX_PA10 //PA10

//#define HRTIM1_PWM_CHD1_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define HRTIM1_PWM_CHD1_PORT_PIN  AUX_PA11 //PA11

//#define HRTIM1_PWM_CHD2_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define HRTIM1_PWM_CHD2_PORT_PIN  AUX_PA12 //PA12

//#define HRTIM1_PWM_CHE1_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define HRTIM1_PWM_CHE1_PORT_PIN  AUX_PG6 //PG6

//#define HRTIM1_PWM_CHE2_POLARITY  TIM_OCPOLARITY_HIGH //TIM_OCPOLARITY_HIGH-TIM_OCPOLARITY_LOW
#define HRTIM1_PWM_CHE2_PORT_PIN  AUX_PG7 //PG7

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                 ##### Phal Incremental Encoder Parameter #####                   ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define TIM1_INC_ENCODER_ENABLE
//#define TIM2_INC_ENCODER_ENABLE
//#define TIM3_INC_ENCODER_ENABLE
//#define TIM4_INC_ENCODER_ENABLE
//#define TIM5_INC_ENCODER_ENABLE
//#define TIM8_INC_ENCODER_ENABLE

/**
 * @brief 
 * 
 */
#define TIM1_TI1_PORT_PIN  AUX_PA8 //PE9-PA8
#define TIM1_TI2_PORT_PIN  AUX_PA9 //PE11-PA9

/**
 * @brief 
 * 
 */
#define TIM2_TI1_PORT_PIN  AUX_PA0 //PA0-PA5-PA15
#define TIM2_TI2_PORT_PIN  AUX_PA1 //PA1-PB3

/**
 * @brief 
 * 
 */
#define TIM3_TI1_PORT_PIN  AUX_PA6 //PA6-PC6-PB4
#define TIM3_TI2_PORT_PIN  AUX_PA7 //PA7-PC7-PB5

/**
 * @brief 
 * 
 */
#define TIM4_TI1_PORT_PIN  AUX_PB6 //PD12-PB6
#define TIM4_TI2_PORT_PIN  AUX_PB7 //PD13-PB7

/**
 * @brief 
 * 
 */
#define TIM5_TI1_PORT_PIN  AUX_PA0 //PH10-PA0
#define TIM5_TI2_PORT_PIN  AUX_PA1 //PH11-PA1

/**
 * @brief 
 * 
 */
#define TIM8_TI1_PORT_PIN  AUX_PC6 //PC6-PI5
#define TIM8_TI2_PORT_PIN  AUX_PC7 //PC7-PI6

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Phal GPIO Parameter #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define GPIO_PA0
//#define GPIO_PA1
//#define GPIO_PA2
//#define GPIO_PA3
//#define GPIO_PA4
//#define GPIO_PA5
//#define GPIO_PA6
//#define GPIO_PA7
//#define GPIO_PA8
//#define GPIO_PA9
//#define GPIO_PA10
#define GPIO_PA11
//#define GPIO_PA12
//#define GPIO_PA13
//#define GPIO_PA14
//#define GPIO_PA15

/**
 * @brief 
 * 
 */
#define GPIO_PB0
//#define GPIO_PB1
//#define GPIO_PB2
//#define GPIO_PB3
//#define GPIO_PB4
//#define GPIO_PB5
//#define GPIO_PB6
#define GPIO_PB7
//#define GPIO_PB8
//#define GPIO_PB9
//#define GPIO_PB10
//#define GPIO_PB11
//#define GPIO_PB12
//#define GPIO_PB13
#define GPIO_PB14
//#define GPIO_PB15

/**
 * @brief 
 * 
 */
//#define GPIO_PC0
//#define GPIO_PC1
//#define GPIO_PC2
//#define GPIO_PC3
//#define GPIO_PC4
//#define GPIO_PC5
//#define GPIO_PC6
//#define GPIO_PC7
//#define GPIO_PC8
//#define GPIO_PC9
//#define GPIO_PC10
//#define GPIO_PC11
//#define GPIO_PC12
#define GPIO_PC13
//#define GPIO_PC14
//#define GPIO_PC15

/**
 * @brief 
 * 
 */
//#define GPIO_PD0
//#define GPIO_PD1
//#define GPIO_PD2
//#define GPIO_PD3
//#define GPIO_PD4
//#define GPIO_PD5
//#define GPIO_PD6
//#define GPIO_PD7
//#define GPIO_PD8
//#define GPIO_PD9
//#define GPIO_PD10
//#define GPIO_PD11
//#define GPIO_PD12
//#define GPIO_PD13
//#define GPIO_PD14
//#define GPIO_PD15

/**
 * @brief 
 * 
 */
//#define GPIO_PE0
//#define GPIO_PE1
//#define GPIO_PE2
//#define GPIO_PE3
//#define GPIO_PE4
//#define GPIO_PE5
//#define GPIO_PE6
//#define GPIO_PE7
//#define GPIO_PE8
//#define GPIO_PE9
//#define GPIO_PE10
//#define GPIO_PE11
//#define GPIO_PE12
//#define GPIO_PE13
//#define GPIO_PE14
//#define GPIO_PE15

/**
 * @brief 
 * 
 */
//#define GPIO_PF0
//#define GPIO_PF1
//#define GPIO_PF2
//#define GPIO_PF3
//#define GPIO_PF4
//#define GPIO_PF5
//#define GPIO_PF6
//#define GPIO_PF7
//#define GPIO_PF8
//#define GPIO_PF9
//#define GPIO_PF10
//#define GPIO_PF11
//#define GPIO_PF12
//#define GPIO_PF13
//#define GPIO_PF14
//#define GPIO_PF15

/**
 * @brief 
 * 
 */
//#define GPIO_PG0
//#define GPIO_PG1
//#define GPIO_PG2
//#define GPIO_PG3
//#define GPIO_PG4
//#define GPIO_PG5
//#define GPIO_PG6
//#define GPIO_PG7
//#define GPIO_PG8
//#define GPIO_PG9
//#define GPIO_PG10
//#define GPIO_PG11
//#define GPIO_PG12
//#define GPIO_PG13
//#define GPIO_PG14
//#define GPIO_PG15

/**
 * @brief 
 * 
 */
//#define GPIO_PH0
//#define GPIO_PH1
//#define GPIO_PH2
//#define GPIO_PH3
//#define GPIO_PH4
//#define GPIO_PH5
//#define GPIO_PH6
//#define GPIO_PH7
//#define GPIO_PH8
//#define GPIO_PH9
//#define GPIO_PH10
//#define GPIO_PH11
//#define GPIO_PH12
//#define GPIO_PH13
//#define GPIO_PH14
//#define GPIO_PH15

/**
 * @brief 
 * 
 */
//#define GPIO_PI0
//#define GPIO_PI1
//#define GPIO_PI2
//#define GPIO_PI3
//#define GPIO_PI4
//#define GPIO_PI5
//#define GPIO_PI6
//#define GPIO_PI7
//#define GPIO_PI8
//#define GPIO_PI9
//#define GPIO_PI10
//#define GPIO_PI11
//#define GPIO_PI12
//#define GPIO_PI13
//#define GPIO_PI14
//#define GPIO_PI15

/**
 * @brief 
 * 
 */
//#define GPIO_PJ0
//#define GPIO_PJ1
//#define GPIO_PJ2
//#define GPIO_PJ3
//#define GPIO_PJ4
//#define GPIO_PJ5
//#define GPIO_PJ6
//#define GPIO_PJ7
//#define GPIO_PJ8
//#define GPIO_PJ9
//#define GPIO_PJ10
//#define GPIO_PJ11
//#define GPIO_PJ12
//#define GPIO_PJ13
//#define GPIO_PJ14
//#define GPIO_PJ15

/**
 * @brief 
 * 
 */
//#define GPIO_PK0
//#define GPIO_PK1
//#define GPIO_PK2
//#define GPIO_PK3
//#define GPIO_PK4
//#define GPIO_PK5
//#define GPIO_PK6
//#define GPIO_PK7
//#define GPIO_PK8
//#define GPIO_PK9
//#define GPIO_PK10
//#define GPIO_PK11
//#define GPIO_PK12
//#define GPIO_PK13
//#define GPIO_PK14
//#define GPIO_PK15

/**
 * @brief 
 * 
 */
//#define EXTI0_PORT  GPIOA
//#define EXTI1_PORT  GPIOA
//#define EXTI2_PORT  GPIOA
//#define EXTI3_PORT  GPIOA
//#define EXTI4_PORT  GPIOA
//#define EXTI5_PORT  GPIOA
//#define EXTI6_PORT  GPIOA
//#define EXTI7_PORT  GPIOA
//#define EXTI8_PORT  GPIOB
//#define EXTI9_PORT  GPIOA
//#define EXTI10_PORT GPIOA
//#define EXTI11_PORT GPIOA
//#define EXTI12_PORT GPIOA
//#define EXTI13_PORT GPIOA
//#define EXTI14_PORT GPIOA
//#define EXTI15_PORT GPIOA

/**
 * @brief 
 * 
 */
#define EXTI_CH0_IRQ_PreemptPriority  2
#define EXTI_CH0_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define EXTI_CH1_IRQ_PreemptPriority  2
#define EXTI_CH1_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define EXTI_CH2_IRQ_PreemptPriority  2
#define EXTI_CH2_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define EXTI_CH3_IRQ_PreemptPriority  2
#define EXTI_CH3_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define EXTI_CH4_IRQ_PreemptPriority  2
#define EXTI_CH4_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define EXTI_CH9_5_IRQ_PreemptPriority  2
#define EXTI_CH9_5_IRQ_SubPriority      2

/**
 * @brief 
 * 
 */
#define EXTI_CH15_10_IRQ_PreemptPriority  2
#define EXTI_CH15_10_IRQ_SubPriority      2

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Phal ADC Parameter #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
//#define ADC1_CH0_ENABLE
//#define ADC1_CH1_ENABLE
//#define ADC1_CH2_ENABLE
//#define ADC1_CH3_ENABLE
//#define ADC1_CH4_ENABLE
//#define ADC1_CH5_ENABLE
//#define ADC1_CH6_ENABLE
//#define ADC1_CH7_ENABLE
//#define ADC1_CH8_ENABLE
//#define ADC1_CH9_ENABLE
//#define ADC1_CH10_ENABLE
//#define ADC1_CH11_ENABLE
//#define ADC1_CH12_ENABLE
//#define ADC1_CH13_ENABLE
//#define ADC1_CH14_ENABLE
//#define ADC1_CH15_ENABLE
//#define ADC1_CH16_ENABLE
//#define ADC1_CH17_ENABLE
//#define ADC1_CH18_ENABLE
//#define ADC1_CH19_ENABLE

/**
 * @brief 
 * 
 */
#define ADC1_SAMPLETIME       ADC_SAMPLETIME_32CYCLES_5
#define ADC1_FREE_RUN_ENABLE  false
#define ADC1_EXT_TRIG         ADC_EXTERNALTRIG_T1_TRGO

/**
 * @brief 
 * 
 */
#define ADC1_DMA_CFG   DMA2_STREAM0

/**
 * @brief 
 * 
 */
//#define ADC2_CH0_ENABLE
//#define ADC2_CH1_ENABLE
//#define ADC2_CH2_ENABLE
//#define ADC2_CH3_ENABLE
//#define ADC2_CH4_ENABLE
//#define ADC2_CH5_ENABLE
//#define ADC2_CH6_ENABLE
//#define ADC2_CH7_ENABLE
//#define ADC2_CH8_ENABLE
//#define ADC2_CH9_ENABLE
//#define ADC2_CH10_ENABLE
//#define ADC2_CH11_ENABLE
//#define ADC2_CH12_ENABLE
//#define ADC2_CH13_ENABLE
//#define ADC2_CH14_ENABLE
//#define ADC2_CH15_ENABLE
//#define ADC2_CH18_ENABLE
//#define ADC2_CH19_ENABLE

/**
 * @brief 
 * 
 */
#define ADC2_SAMPLETIME       ADC_SAMPLETIME_8CYCLES_5
#define ADC2_FREE_RUN_ENABLE  false
#define ADC2_EXT_TRIG         ADC_EXTERNALTRIG_T8_TRGO

/**
 * @brief 
 * 
 */
#define ADC2_DMA_CFG   DMA2_STREAM4

/**
 * @brief 
 * 
 */
//#define ADC3_CH0_ENABLE
//#define ADC3_CH1_ENABLE
//#define ADC3_CH2_ENABLE
//#define ADC3_CH3_ENABLE
//#define ADC3_CH4_ENABLE
//#define ADC3_CH5_ENABLE
//#define ADC3_CH6_ENABLE
//#define ADC3_CH7_ENABLE
//#define ADC3_CH8_ENABLE
//#define ADC3_CH9_ENABLE
//#define ADC3_CH10_ENABLE
//#define ADC3_CH11_ENABLE
//#define ADC3_CH12_ENABLE
//#define ADC3_CH13_ENABLE
//#define ADC3_CH14_ENABLE
//#define ADC3_CH15_ENABLE
//#define ADC3_TEMPERATURE_ENABLE

/**
 * @brief 
 * 
 */
#define ADC3_SAMPLETIME       ADC_SAMPLETIME_32CYCLES_5
#define ADC3_FREE_RUN_ENABLE  false
#define ADC3_EXT_TRIG         ADC_EXTERNALTRIG_T1_TRGO

/**
 * @brief 
 * 
 */
#define ADC3_DMA_CFG DMA2_STREAM1

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

#include "stm32h7xx_phal_internal.h"

#ifdef __cplusplus
}
#endif

#endif /* STM32H7XX_PHAL_CONFIG_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
