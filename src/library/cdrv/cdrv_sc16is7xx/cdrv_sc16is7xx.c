/**
******************************************************************************
* @file           : cdrv_sc16is7xx.c
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
#include "cdrv_sc16is7xx.h"

#include <stdlib.h>
#include <string.h>

#include "faraabin.h"

/* Private define ------------------------------------------------------------*/
#define OPTIONS_8N1       0b000011
#define OPTIONS_8E1       0b011011
#define OPTIONS_8O1       0b001011

#define OPTIONS_8N2       0b000111
#define OPTIONS_8E2       0b011111
#define OPTIONS_8O2       0b001111

#define OPTIONS_7N1       0b000010
#define OPTIONS_7E1       0b011010
#define OPTIONS_7O1       0b001010

#define OPTIONS_7N2       0b000110
#define OPTIONS_7E2       0b011110
#define OPTIONS_7O2       0b001110

// Genral register block
#define RHR_THR_REG       0x00
#define IER_REG           0x01
#define FCR_IIR_REG       0x02
#define LCR_REG           0x03
#define MCR_REG           0x04
#define LSR_REG           0x05
#define MSR_REG           0x06
#define SPR_REG           0x07
#define TXLVL_REG         0x08
#define RXLVL_REG         0x09
#define IODIR_REG         0x0a
#define IOSTATE_REG       0x0b
#define IOINTENA_REG      0x0c
#define IOCONTROL_REG     0x0e
#define EFCR_REG          0x0f

// Special register block
#define LCR_SPECIAL_START 0x80
#define LCR_SPECIAL_END   0xbf
#define DLL_REG           0x00
#define DLH_REG           0x01

// Enhanced register set
#define EFR_REG           0x02
#define XON1_REG          0x04
#define XON2_REG          0x05
#define XOFF1_REG         0x06
#define XOFF2_REG         0x07

// Interrupt flags
#define IIR_NONE          0x01
#define IIR_RX_ERROR      0x06
#define IIR_RX_IDLE       0x0C
#define IIR_RX_NOT_EMPTY  0x04
#define IIR_TX_EMPTY      0x02
#define IIR_MODEM         0x00
#define IIR_IO_PINS       0x30
#define IIR_XOFF          0x10
#define IIR_CTS_RTS       0x20

/* Private macro -------------------------------------------------------------*/
#define GetInterruptFlags_(obj_)    \
do {\
  (obj_)->_iirState = ReadRegister(obj_, FCR_IIR_REG);\
  (obj_)->_iirState = (obj_)->_iirState & 0x3F;\
}while(0)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t Open(TysSerial_Obj * const me);
static uint8_t Close(TysSerial_Obj * const me);

static uint8_t Send(TysSerial_Obj * const me, uint8_t *data, uint16_t size, uint32_t timeout_ms);
static uint8_t Send_nb(TysSerial_Obj * const me, uint8_t *data, uint16_t size);

static uint8_t Receive(TysSerial_Obj * const me, uint8_t *data, uint16_t size, uint32_t timeout_ms);
static uint8_t Receive_nb(TysSerial_Obj * const me, uint8_t *data, uint16_t size);

static uint16_t Receive_buffer_qty(TysSerial_Obj * const me);
static uint8_t Receive_buffer_clear(TysSerial_Obj * const me);

static uint8_t Event_send_end(TysSerial_Obj * const me, void(*func)(void));
static uint8_t Event_receive_byte(TysSerial_Obj * const me, void(*func)(uint8_t data));
static uint8_t Event_idle_detection(TysSerial_Obj * const me, uint32_t bit_qty, void(*func)(void));
static uint8_t Event_error(TysSerial_Obj * const me, void(*func)(void *handle, uint32_t error_code));
static uint8_t Event_receive_buffer_ovf(TysSerial_Obj * const me, void(*func)(uint8_t *data, uint16_t size));

static void Serial_ctor(TysSerial_Obj * me, void * const private_);

static uint8_t ReadRegister(sCdrvSc16is7xx_Obj *me, uint8_t address);
static uint8_t BurstReadRxFifo(sCdrvSc16is7xx_Obj *me, uint8_t *data, uint8_t size);
static uint8_t WriteRegister(sCdrvSc16is7xx_Obj *me, uint8_t address, uint8_t data);
static uint8_t BurstWriteTxFifo(sCdrvSc16is7xx_Obj *me, uint8_t *data, uint8_t size);
static uint8_t CheckRegisterResetState(sCdrvSc16is7xx_Obj *me);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                ##### cdrv_sc16is7xx.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvSc16is7xx_Init(sCdrvSc16is7xx_Obj * const me) {
  me->init = false;

  if((me->Spi == NULL) || (me->SpiCs == NULL) || (me->Irq == NULL)) {
    return 1;
  }

  me->SpiCs->u_dir = eGPIO_DIR_OUTPUT;
  me->SpiCs->u_out_type = eGPIO_PUSH_PULL;
  if(meGpio_Init_(me->SpiCs) != 0) {
    return 1;
  }
  meGpio_Set_(me->SpiCs);

  me->Spi->u_bit_order = eSPI_FIRSTBIT_MSB;
  me->Spi->u_data_size = 8;
  me->Spi->u_mode = eSPI_MODE_0;
  me->Spi->u_role = eSPI_ROLE_MASTER;
  if(meSpi_Init_(me->Spi) != 0) {
    return 1;
  }

  me->Irq->u_dir = eGPIO_DIR_INPUT;
  me->Irq->u_in_type = eGPIO_PULL_NONE;
  if(meGpio_Init_(me->Irq) != 0) {
    return 1;
  }

  if(me->Reset != NULL) {
    me->Reset->u_dir = eGPIO_DIR_OUTPUT;
    me->Reset->u_out_type = eGPIO_PUSH_PULL;
    if(meGpio_Init_(me->Reset) != 0) {
      return 1;
    }
    meGpio_Set_(me->Reset);
  }

  Serial_ctor(&me->Uart, (void*)me);

  me->init = true;
  me->Uart.init = true;
  return 0;
}

/**
 * @brief
 *
 * @param me
 * @return uint8_t
 */
uint8_t fCdrvSc16is7xx_Reset(sCdrvSc16is7xx_Obj * const me) {
  meGpio_Reset_(me->Reset);
  meDelay_ms_(10);
  meGpio_Set_(me->Reset);

  return 0;
}

/**
 * @brief
 *
 */
void fCdrvSc16is7xx_IrqHandler(sCdrvSc16is7xx_Obj *me) {
  GetInterruptFlags_(me);

  if(me->_iirState == IIR_NONE) {
    return;
  }

  if(me->_iirState == IIR_RX_ERROR) {
    mePRINTF_TRACE_("IIR_RX_ERROR");
    uint8_t lsr = ReadRegister(me, LSR_REG);
    if(me->fpEventError != NULL) {
      //LSR[7] = FIFO data error
      //LSR[6] = THR and TSR empty
      //LSR[5] = THR empty
      //LSR[4] = break interrupt
      //LSR[3] = framing error
      //LSR[2] = parity error
      //LSR[1] = overrun error
      //LSR[0] = receiver data error
      me->fpEventError(me, lsr);
    }
    GetInterruptFlags_(me);
  }

  if(me->_iirState == IIR_RX_IDLE) {
      mePRINTF_TRACE_("IIR_RX_IDLE");
    uint8_t sizeToRead = ReadRegister(me, RXLVL_REG);
    BurstReadRxFifo(me, &me->Uart.u_receive_buffer[me->_receiveQty], sizeToRead);
    me->_receiveQty = me->_receiveQty + sizeToRead;
    me->_rxRemainSize = me->_rxRemainSize - sizeToRead;
    meChrono_Stop(&me->_swIdleDetectionChrono);
    if(me->fpEventIdleDetection != NULL) {
      me->fpEventIdleDetection();
    }

    GetInterruptFlags_(me);
  }

  if(me->_iirState == IIR_RX_NOT_EMPTY) {
      mePRINTF_TRACE_("IIR_RX_NOT_EMPTY");
    uint8_t sizeToRead = ReadRegister(me, RXLVL_REG);
    meChrono_StartTimeout_(&me->_swIdleDetectionChrono, me->_swIdleDetectionTimeout_us);
    BurstReadRxFifo(me, &me->Uart.u_receive_buffer[me->_receiveQty], sizeToRead);
    me->_receiveQty = me->_receiveQty + sizeToRead;
    me->_rxRemainSize = me->_rxRemainSize - sizeToRead;

    if(me->_rxRemainSize == 0) {
      meChrono_Stop(&me->_swIdleDetectionChrono);
      if(me->fpEventIdleDetection != NULL) {
        me->fpEventIdleDetection();
      }
    }

    GetInterruptFlags_(me);
  }

  if(me->_iirState == IIR_TX_EMPTY) {
      mePRINTF_TRACE_("IIR_TX_EMPTY");
    if(!me->_txIsBlocking) {
      me->_txRemainSize = me->_txRemainSize - me->_txLastSentSize;
      me->_txSentIndex = me->_txSentIndex + me->_txLastSentSize;
      if(me->_txRemainSize > 0) {
        if(me->_txRemainSize  > 64) {
            me->_txLastSentSize = 64;
        } else {
            me->_txLastSentSize = me->_txRemainSize;
        }

        BurstWriteTxFifo(me, &me->_txDataPtr[me->_txSentIndex], me->_txLastSentSize);
        mePRINTF_TRACE_("Sent %d bytes", me->_txLastSentSize);
      } else {
        me->Uart.u_is_sending = false;
        if(me->fpEventSendEnd != NULL) {
          me->fpEventSendEnd();
        }
      }
    }

    GetInterruptFlags_(me);
  }

  if(me->_iirState == IIR_MODEM) {
    //TODO: Handle modem status interrupt
    GetInterruptFlags_(me);
  }

  if(me->_iirState == IIR_IO_PINS) {
    //TODO: Handle IP Pins interrupt
    GetInterruptFlags_(me);
  }

  if(me->_iirState == IIR_XOFF) {
    //TODO: Handle XOff interrupt
    GetInterruptFlags_(me);
  }

  if(me->_iirState == IIR_CTS_RTS) {
    //TODO: Handle CTS RTS Change of state interrupt
    GetInterruptFlags_(me);
  }
}

/**
 * @brief
 *
 */
void fCdrvSc16is7xx_SoftwareIdleDetection_Run(sCdrvSc16is7xx_Obj *me) {
  if(meChrono_us_IsTimedOut(&me->_swIdleDetectionChrono)) {
    if(me->fpEventIdleDetection != NULL) {
      meChrono_Stop(&me->_swIdleDetectionChrono);
      me->fpEventIdleDetection();
    }
  }
}

/*
===============================================================================
                ##### cdrv_sc16is7xx.c Private Functions #####
===============================================================================*/
/**
 * @brief
 *
 * @param me
 * @return uint8_t
 */
static uint8_t Open(TysSerial_Obj * const me) {
  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;

  if(CheckRegisterResetState(uart_parent) != 0) {
    return 1;
  }

  if(me->u_receive_buffer_size == 0) {
    return 1;
  }
  if(me->u_receive_buffer == NULL) {
    me->u_receive_buffer = malloc(me->u_receive_buffer_size * sizeof(uint8_t));
    if(me->u_receive_buffer == NULL) {
      return 1;
    }
  }

  int divBaudrate = (uart_parent->OscillatorClockMhz) / (16.0f * me->u_baud_rate);
  WriteRegister(uart_parent, LCR_REG, LCR_SPECIAL_START);
  WriteRegister(uart_parent, DLL_REG, divBaudrate & 0xFF);
  WriteRegister(uart_parent, DLH_REG, divBaudrate >> 8);
  WriteRegister(uart_parent, LCR_REG, LCR_SPECIAL_END);
  WriteRegister(uart_parent, EFR_REG, ReadRegister(uart_parent, EFR_REG) | 0x10);

  uint8_t options = 0;
  if(me->u_parity == eSERIAL_PARITY_NONE) {
      switch(me->u_stop_bit) {
        case eSERIAL_STOP_BIT_1:
          options = OPTIONS_8N1;
          break;

        case eSERIAL_STOP_BIT_2:
          options = OPTIONS_8N2;
          break;

        default:
          return 1;
      }
  }
  if(me->u_parity == eSERIAL_PARITY_EVEN) {
      switch(me->u_stop_bit) {
        case eSERIAL_STOP_BIT_1:
          options = OPTIONS_8E1;
          break;

        case eSERIAL_STOP_BIT_2:
          options = OPTIONS_8E2;
          break;

        default:
          return 1;
      }
  }
  if(me->u_parity == eSERIAL_PARITY_ODD) {
      switch(me->u_stop_bit) {
        case eSERIAL_STOP_BIT_1:
          options = OPTIONS_8O1;
          break;

        case eSERIAL_STOP_BIT_2:
          options = OPTIONS_8O2;
          break;

        default:
          return 1;
      }
  }

  WriteRegister(uart_parent, LCR_REG, options & 0x3F);
  WriteRegister(uart_parent, MCR_REG, ReadRegister(uart_parent, MCR_REG) | (1 << 2));
  if(uart_parent->RxFifoTrigLevel > 60) {
    return 1;
  }
  WriteRegister(uart_parent, SPR_REG, ((uart_parent->RxFifoTrigLevel / 4) << 4));
  WriteRegister(uart_parent, FCR_IIR_REG, 0x07 | (0x00 << 6) | (0x00 << 4));
  meDelay_ms_(10);
  WriteRegister(uart_parent, IER_REG, 0x07);
  WriteRegister(uart_parent, EFCR_REG, 0x30);

  me->u_enable = true;
  return 0;
}

/**
 * @brief
 *
 * @param me
 * @return uint8_t
 */
static uint8_t Close(TysSerial_Obj * const me) {
    sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;

    meCHECK_INIT_(eME_RESULT_ERROR_INIT);
    meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);

    WriteRegister(uart_parent, EFCR_REG, 0x36);

    return 0;
}

/**
 * @brief
 *
 * @param me
 * @param data
 * @param size
 * @param timeout_ms
 * @return uint8_t
 */
static uint8_t Send(TysSerial_Obj * const me, uint8_t *data, uint16_t size, uint32_t timeout_ms) {
  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;
  int i = 0;
  static TysChrono_Obj timeoutChrono;

  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);

  uint8_t ier = ReadRegister(uart_parent, IER_REG); //Disabling transmit interrupt
  ier &= ~(1 << 1);
  WriteRegister(uart_parent, IER_REG, ier);

  if(me->u_is_sending == true) {
    return 1;
  }

  uart_parent->_txIsBlocking = true;
  meChrono_StartTimeout_(&timeoutChrono, timeout_ms);
  me->u_is_sending = true;
  for(i = 0; i < (size / 64); i++) {
    while(ReadRegister(uart_parent, TXLVL_REG) < (size > 64 ? 64 : size)) {
      if(meChrono_ms_IsTimedOut(&timeoutChrono)) {
        return 1;
      }
    }
    BurstWriteTxFifo(uart_parent, &data[64 * i], 64);
  }

  while(ReadRegister(uart_parent, TXLVL_REG) < (size > 64 ? 64 : size)) {
    if(meChrono_ms_IsTimedOut(&timeoutChrono)) {
      return 1;
    }
  }
  BurstWriteTxFifo(uart_parent, &data[64 * i], size % 64);
  me->u_is_sending = false;

  return 0;
}

/**
 * @brief
 *
 * @param me
 * @param data
 * @param size
 * @return uint8_t
 */
static uint8_t Send_nb(TysSerial_Obj * const me, uint8_t *data, uint16_t size) {
  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;

  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);

  uint8_t ier = ReadRegister(uart_parent, IER_REG); //Enabling transmit interrupt
  ier |= (1 << 1);
  WriteRegister(uart_parent, IER_REG, ier);

  if(me->u_is_sending == true) {
    return 1;
  }

  uart_parent->_txDataPtr = data;
  uart_parent->_txRemainSize = size;
  uart_parent->_txSentIndex = 0;

  uart_parent->_txIsBlocking = false;
  me->u_is_sending = true;
  if(uart_parent->_txRemainSize  > 64) {
    uart_parent->_txLastSentSize = 64;
  } else {
    uart_parent->_txLastSentSize = uart_parent->_txRemainSize;
  }

  BurstWriteTxFifo(uart_parent, &uart_parent->_txDataPtr[uart_parent->_txSentIndex], uart_parent->_txLastSentSize);
  mePRINTF_TRACE_("Sent %d bytes", uart_parent->_txLastSentSize);

  return 0;
}

/**
 * @brief
 *
 * @param me
 * @param data
 * @param size
 * @param timeout_ms
 * @return uint8_t
 */
static uint8_t Receive(TysSerial_Obj * const me, uint8_t *data, uint16_t size, uint32_t timeout_ms) {
  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;
  static TysChrono_Obj timeoutChrono;

  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);

  uart_parent->_receiveQty = 0;
  uint8_t ier = ReadRegister(uart_parent, IER_REG); //Disabling receive interrupt
  ier &= ~(1 << 0);
  WriteRegister(uart_parent, IER_REG, ier);

  meChrono_StartTimeout_(&timeoutChrono, timeout_ms);
  while(uart_parent->_receiveQty < size) {
    if(meChrono_ms_IsTimedOut(&timeoutChrono)) {
      return 1;
    }

    uint8_t sizeToRead = ReadRegister(uart_parent, RXLVL_REG);
    if(sizeToRead > 0) {
      BurstReadRxFifo(uart_parent, &me->u_receive_buffer[uart_parent->_receiveQty], sizeToRead);
      uart_parent->_receiveQty = uart_parent->_receiveQty + sizeToRead;
    }
  }

  return 0;
}

/**
 * @brief
 *
 * @param me
 * @param data
 * @param size
 * @return uint8_t
 */
static uint8_t Receive_nb(TysSerial_Obj * const me, uint8_t *data, uint16_t size) {
  //TODO: Need fixing. Becomes unstable!
  return 1;
//  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;

//  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
//  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);

//  uart_parent->_receiveQty = 0;
//  uart_parent->_rxRemainSize = size;
//  uint8_t ier = ReadRegister(uart_parent, IER_REG); //Enabling receive interrupt
//  ier |= (1 << 0);
//  WriteRegister(uart_parent, IER_REG, ier);
//  WriteRegister(uart_parent, IER_REG, 0x07);

//  return 1;
}

/**
 * @brief
 *
 * @param me
 * @return uint16_t
 */
static uint16_t Receive_buffer_qty(TysSerial_Obj * const me) {
  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;

  return uart_parent->_receiveQty;
}

/**
 * @brief
 *
 * @param me
 * @return uint8_t
 */
static uint8_t Receive_buffer_clear(TysSerial_Obj * const me) {
  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;

  WriteRegister(uart_parent, FCR_IIR_REG, 0x03);
  for(int i = 0; i < me->u_receive_buffer_size; i++) {
      me->u_receive_buffer[i] = 0x00;
  }
  return 0;
}

/**
 * @brief
 *
 * @param me
 * @param func
 * @return uint8_t
 */
static uint8_t Event_send_end(TysSerial_Obj * const me, void(*func)(void)) {
  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;

  if(func != NULL) {
    uart_parent->fpEventSendEnd = func;
  }

  return 0;
}

/**
 * @brief
 *
 * @param me
 * @param func
 * @return uint8_t
 */
static uint8_t Event_receive_byte(TysSerial_Obj * const me, void(*func)(uint8_t data)) {
  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;

  if(func != NULL) {
    uart_parent->fpEventReceiveByte = func;
  }

  return 0;
}

/**
 * @brief
 *
 * @param me
 * @param bit_qty
 * @param func
 * @return uint8_t
 */
static uint8_t Event_idle_detection(TysSerial_Obj * const me, uint32_t bit_qty, void(*func)(void)) {
  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;

  if(func != NULL) {
    uart_parent->fpEventIdleDetection = func;
  }
  uart_parent->_swIdleDetectionTimeout_us = bit_qty * (1.0f / (float)(me->u_baud_rate)) * 1000000.0f;

  return 0;
}

/**
 * @brief
 *
 * @param me
 * @param func
 * @return uint8_t
 */
static uint8_t Event_error(TysSerial_Obj * const me, void(*func)(void *handle, uint32_t error_code)) {
  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;

  if(func != NULL) {
    uart_parent->fpEventError = func;
  }

  return 0;
}

/**
 * @brief
 *
 * @param me
 * @param func
 * @return uint8_t
 */
static uint8_t Event_receive_buffer_ovf(TysSerial_Obj * const me, void(*func)(uint8_t *data, uint16_t size)) {
  sCdrvSc16is7xx_Obj *uart_parent = (sCdrvSc16is7xx_Obj*)me->private_;

  if(func != NULL) {
    uart_parent->fpEventReceiveBufferOvf = func;
  }

  return 0;
}

/**
 * @brief
 *
 * @param me
 * @param private_
 */
static void Serial_ctor(TysSerial_Obj * me, void * const private_) {
  static struct TysSerialVtbl const vtbl = {
    Open,
    Close,

    Send,
    Send_nb,

    Receive,
    Receive_nb,

    Receive_buffer_qty,
    Receive_buffer_clear,

    Event_send_end,
    Event_receive_byte,
    Event_idle_detection,
    Event_error,
    Event_receive_buffer_ovf
  };

  if(me == NULL) {
    return;
  }

  uint8_t *tmp = (uint8_t*)me;
  for(uint16_t i=0; i<sizeof(*me); i++) {
    tmp[i] = 0;
  }

  /*Initialize Special param*/
  me->init = false;
  me->u_enable = true;
  me->vptr = &vtbl;
  me->private_ = private_;

  me->u_stop_bit = eSERIAL_STOP_BIT_1;
  me->u_parity = eSERIAL_PARITY_NONE;
  me->u_baud_rate = 9600;
}

/**
 * @brief
 *
 * @param me
 * @param address
 * @return uint8_t
 */
static uint8_t ReadRegister(sCdrvSc16is7xx_Obj *me, uint8_t address) {
  uint8_t rxData[2] = {0};
  uint8_t txData[2] = {0};

  txData[0] = 0x80 | (address << 3);
  txData[1] = 0x00;

  meGpio_Reset_(me->SpiCs);
  meSpi_TransmitReceive_(me->Spi, txData, rxData, 2, me->SpiTimeout);
  meGpio_Set_(me->SpiCs);

  return rxData[1];
}

/**
 * @brief
 *
 * @param me
 * @param address
 * @param data
 * @param size
 * @return uint8_t
 */
static uint8_t BurstReadRxFifo(sCdrvSc16is7xx_Obj *me, uint8_t *data, uint8_t size) {
  uint8_t address = 0x80 | (RHR_THR_REG << 3);

  if(size > 64) {
    return 1;
  }

  meGpio_Reset_(me->SpiCs);
  meSpi_Transmit_(me->Spi, &address, 1, me->SpiTimeout);
  meSpi_Receive_(me->Spi, data, size, me->SpiTimeout);
  meGpio_Set_(me->SpiCs);

  return 0;
}

/**
 * @brief
 *
 * @param me
 * @param address
 * @param data
 */
static uint8_t WriteRegister(sCdrvSc16is7xx_Obj *me, uint8_t address, uint8_t data) {
  uint8_t txData[2] = {0};

  txData[0] = address << 3;
  txData[1] = data;

  meGpio_Reset_(me->SpiCs);
  meSpi_Transmit_(me->Spi, txData, 2, me->SpiTimeout);
  meGpio_Set_(me->SpiCs);

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param address 
 * @param data 
 * @param size 
 * @return uint8_t 
 */
static uint8_t BurstWriteTxFifo(sCdrvSc16is7xx_Obj *me, uint8_t *data, uint8_t size) {
  uint8_t address = 0x00;

  address = (RHR_THR_REG << 3);

  meGpio_Reset_(me->SpiCs);
  meSpi_Transmit_(me->Spi, &address, 1, me->SpiTimeout);
  meSpi_Transmit_(me->Spi, data, size, me->SpiTimeout);
  meGpio_Set_(me->SpiCs);

  return 0;
}

static uint8_t CheckRegisterResetState(sCdrvSc16is7xx_Obj *me) {
  uint8_t rxData;

  rxData = ReadRegister(me, IER_REG);
  if(rxData != 0x00) {
    return 1;
  }

  rxData = ReadRegister(me, FCR_IIR_REG);
  if(rxData != 0x01) {
    return 1;
  }

  rxData = ReadRegister(me, LCR_REG);
  if(rxData != 0x1D) {
    return 1;
  }

  rxData = ReadRegister(me, MCR_REG);
  if(rxData != 0x00) {
    return 1;
  }

  rxData = ReadRegister(me, LSR_REG);
  if(rxData != 0x60) {
    return 1;
  }

  return 0;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
