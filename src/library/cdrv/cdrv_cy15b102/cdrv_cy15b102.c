/**
******************************************************************************
* @file           : cdrv_cy15b102.c
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
#include "cdrv_cy15b102.h"

#include <stdlib.h>

/* Private define ------------------------------------------------------------*/
#define CY15B102_OPCODE_WREN  0x06
#define CY15B102_OPCODE_WRDI  0x04
#define CY15B102_OPCODE_RDSR  0x05
#define CY15B102_OPCODE_WRSR  0x01
#define CY15B102_OPCODE_READ  0x03
#define CY15B102_OPCODE_WRITE 0x02
#define CY15B102_OPCODE_SLEEP 0xB9
#define CY15B102_OPCODE_WAKE  0xAB
#define CY15B102_OPCODE_RDID  0x9F

#define CY15B102_STATUS_WEL   (1 << 1)
#define CY15B102_STATUS_BP0   (1 << 2)
#define CY15B102_STATUS_BP1   (1 << 3)
#define CY15B102_STATUS_WPEN  (1 << 7)

#define CY15B102_SIZE         0x3FFFFUL

/* Private macro -------------------------------------------------------------*/
#define AssertEquality_(exp_, val_) (exp_ == val_)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t Init(TysMemory_Obj * const me);
static uint8_t Erase(TysMemory_Obj * const me, uint32_t address, uint32_t size);
static uint8_t Erase_all(TysMemory_Obj * const me);
static uint8_t Read(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data);
static uint8_t Write(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data);
static uint8_t Verify(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data);

static void SetWriteEnableLatch(sCdrvCy15b102Obj * const me);
static void ResetWriteEnableLatch(sCdrvCy15b102Obj * const me);
static uint8_t ReadStatusRegister(sCdrvCy15b102Obj * const me);
static uint8_t WriteStatusRegister(sCdrvCy15b102Obj * const me, uint8_t data);
static uint8_t WriteBytes(sCdrvCy15b102Obj * const me, uint8_t *data, uint16_t size);
static uint8_t ReadBytes(sCdrvCy15b102Obj * const me, uint8_t *data, uint16_t size);

static uint8_t WriteRegister(sCdrvCy15b102Obj * const me, uint8_t *data, uint16_t size);
static uint8_t ReadRegister(sCdrvCy15b102Obj * const me, uint8_t *data, uint16_t size);
static uint8_t WriteReadRegister(sCdrvCy15b102Obj * const me, uint8_t *wData, uint8_t *rData, uint16_t size);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                  ##### cdrv_cy15b102.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCy15b102_Init(sCdrvCy15b102Obj * const me) {
  me->_init = false;

  if(AssertEquality_(me->Cs , NULL)) {
    return 1;
  } else {
    me->Cs->u_dir = eGPIO_DIR_OUTPUT;
    me->Cs->u_out_type = eGPIO_PUSH_PULL;
    if(meGpio_Init_(me->Cs) != 0) {
      return 1;
    }
  }
  meGpio_Set_(me->Cs);

  if(AssertEquality_(me->Spi, NULL)) {
    return 1;
  } else {
    me->Spi->u_bit_order = eSPI_FIRSTBIT_MSB;
    me->Spi->u_data_size = 8;
    me->Spi->u_mode = eSPI_MODE_0;
    me->Spi->u_role = eSPI_ROLE_MASTER;
    if(meSpi_Init_(me->Spi) != 0) {
      return 1;
    }
  }

  if(!AssertEquality_(me->Wp, NULL)) {
    me->Wp->u_dir = eGPIO_DIR_OUTPUT;
    me->Wp->u_out_type = eGPIO_PUSH_PULL;
    if(meGpio_Init_(me->Wp) != 0) {
      return 1;
    }
  }

  SetWriteEnableLatch(me);
  if(WriteStatusRegister(me, 0x82) != 0) {
    return 1;
  }

  me->_init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param start_addr 
 * @param size 
 * @return TysMemory_Obj* 
 */
TysMemory_Obj* fCdrvCy15b102_CreatePartirion(sCdrvCy15b102Obj * const me, uint32_t start_addr, uint32_t size) {
  static struct TysMemoryVtbl const vtbl = {
    Init,
    Erase,
    Erase_all,
    Read,
    Write,
    Verify,
  };
  
  if((start_addr + size) > fCdrvCy15b102_GetSize(me)) {
    return NULL;
  }
  
  TysMemory_Obj *partition = (TysMemory_Obj*)malloc(sizeof(TysMemory_Obj));
  if(partition == NULL) {
    return NULL;
  }
  
  partition->init = false;
  partition->u_enable = false;
  partition->vptr = &vtbl;
  partition->u_start_address = start_addr;
  partition->u_size = size;
  partition->device = me;

  return partition;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCy15b102_WpDisable(sCdrvCy15b102Obj * const me) {

  if(!AssertEquality_(me->Wp, NULL)) {
    return meGpio_Set_(me->Wp);
  }

  return 1;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvCy15b102_WpEnable(sCdrvCy15b102Obj * const me) {

  if(!AssertEquality_(me->Wp, NULL)) {
    return meGpio_Reset_(me->Wp);
  }

  return 1;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint32_t 
 */
uint32_t fCdrvCy15b102_GetSize(sCdrvCy15b102Obj * const me) {
  return CY15B102_SIZE;
}

/*
===============================================================================
                  ##### cdrv_cy15b102.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t Init(TysMemory_Obj * const me) {

  me->init = true;
  me->u_enable = true;

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param address 
 * @param size 
 * @return uint8_t 
 */
static uint8_t Erase(TysMemory_Obj * const me, uint32_t address, uint32_t size) {

  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);

  uint8_t txData[10];
  uint16_t divCount = size / 10;
  uint8_t modCount = size % 10;
  sCdrvCy15b102Obj *device = (sCdrvCy15b102Obj*)me->device;

  address += me->u_start_address;

  if((address + size) > (me->u_start_address + me->u_size)) {
    return 1;
  }

  SetWriteEnableLatch(device);

  txData[0] = CY15B102_OPCODE_WRITE;
  txData[1] = address >> 16;
  txData[2] = address >> 8;
  txData[3] = address;

  meGpio_Reset_(device->Cs);
  if(meSpi_Transmit_(device->Spi, txData, 4, device->SpiTimeout) != 0) {
    meGpio_Set_(device->Cs);
    return 1;
  }

  for(int i = 0; i < 10; i++) {
    txData[i] = 0;
  }

  for(int i = 0; i < divCount; i++) {
    if(meSpi_Transmit_(device->Spi, txData, 10, device->SpiTimeout) != 0) {
      meGpio_Set_(device->Cs);
      return 1;
    }
  }
  if(meSpi_Transmit_(device->Spi, txData, modCount, device->SpiTimeout) != 0) {
    meGpio_Set_(device->Cs);
    return 1;
  }
  meGpio_Set_(device->Cs);

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t Erase_all(TysMemory_Obj * const me) {

  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);

  return Erase(me, 0, me->u_size);
}

/**
 * @brief 
 * 
 * @param me 
 * @param address 
 * @param size 
 * @param data 
 * @return uint8_t 
 */
static uint8_t Read(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data) {

  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);

  uint8_t txData[10];
  sCdrvCy15b102Obj *device = (sCdrvCy15b102Obj*)me->device;

  if(size  == 0) {
    return 1;
  }

  address += me->u_start_address;

  if((address + size) > (me->u_start_address + me->u_size)) {
    return 1;
  }

  txData[0] = CY15B102_OPCODE_READ;
  txData[1] = address >> 16;
  txData[2] = address >> 8;
  txData[3] = address;

  meGpio_Reset_(device->Cs);
  if(meSpi_Transmit_(device->Spi, txData, 4, device->SpiTimeout) != 0) {
    meGpio_Set_(device->Cs);
    return 1;
  }

  if(meSpi_Receive_(device->Spi, data, size, device->SpiTimeout) != 0) {
    meGpio_Set_(device->Cs);
    return 1;
  }

  meGpio_Set_(device->Cs);

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param address 
 * @param size 
 * @param data 
 * @return uint8_t 
 */
static uint8_t Write(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data) {

  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);

  uint8_t txData[10] = {0x00};
  sCdrvCy15b102Obj *device = (sCdrvCy15b102Obj*)me->device;

  if(size  == 0) {
    return 1;
  }

  address += me->u_start_address;

  if((address + size) > (me->u_start_address + me->u_size)) {
    return 1;
  }

  SetWriteEnableLatch(device);

  meGpio_Reset_(device->Cs);

  txData[0] = CY15B102_OPCODE_WRITE;
  txData[1] = address >> 16;
  txData[2] = address >> 8;
  txData[3] = address;

  if(meSpi_Transmit_(device->Spi, txData, 4, device->SpiTimeout) != 0) {
    meGpio_Set_(device->Cs);
    return 1;
  }

  if(meSpi_Transmit_(device->Spi, data, size, device->SpiTimeout) != 0) {
    meGpio_Set_(device->Cs);
    return 1;
  }

  meGpio_Set_(device->Cs);

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param address 
 * @param size 
 * @param data 
 * @return uint8_t 
 */
static uint8_t Verify(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data) {
  //TODO: No need to implement this function.
  return 0;
}

/**
 * @brief Set the Write Enable Latch object
 * 
 * @param me 
 */
static void SetWriteEnableLatch(sCdrvCy15b102Obj * const me) {
  uint8_t txData = CY15B102_OPCODE_WREN;

  WriteRegister(me, &txData, 1);
}

/**
 * @brief 
 * 
 * @param me 
 */
static void ResetWriteEnableLatch(sCdrvCy15b102Obj * const me) {
  uint8_t txData = CY15B102_OPCODE_WREN;

  WriteRegister(me, &txData, 1);
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t ReadStatusRegister(sCdrvCy15b102Obj * const me) {
  uint8_t status[2] = {0x00};
  uint8_t txData[2];
  txData[0] = CY15B102_OPCODE_WRSR;
  txData[1] = 0x00;

  WriteReadRegister(me, txData, status, 2);

  return status[1];
}

/**
 * @brief 
 * 
 * @param me 
 * @param data 
 * @return uint8_t 
 */
static uint8_t WriteStatusRegister(sCdrvCy15b102Obj * const me, uint8_t data) {
  uint8_t txData[2];
  txData[0] = CY15B102_OPCODE_WRSR;
  txData[1] = data;

  return WriteRegister(me, txData, 2);

}

/**
 * @brief 
 * 
 * @param me 
 * @param data 
 * @param size 
 * @return uint8_t 
 */
static uint8_t WriteRegister(sCdrvCy15b102Obj * const me, uint8_t *data, uint16_t size) {
  meGpio_Reset_(me->Cs);
  if(meSpi_Transmit_(me->Spi, data, size, me->SpiTimeout) != 0) {
    meGpio_Set_(me->Cs);
    return 1;
  }
  meGpio_Set_(me->Cs);

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
static uint8_t ReadRegister(sCdrvCy15b102Obj * const me, uint8_t *data, uint16_t size) {
  meGpio_Reset_(me->Cs);
  if(meSpi_Receive_(me->Spi, data, size, me->SpiTimeout) != 0) {
    meGpio_Set_(me->Cs);
    return 1;
  }
  meGpio_Set_(me->Cs);

  return 0;
}

static uint8_t WriteReadRegister(sCdrvCy15b102Obj * const me, uint8_t *wData, uint8_t *rData, uint16_t size) {
  meGpio_Reset_(me->Cs);
  if(meSpi_TransmitReceive_(me->Spi, wData, rData, size, me->SpiTimeout) != 0) {
    meGpio_Set_(me->Cs);
    return 1;
  }
  meGpio_Set_(me->Cs);

  return 0;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
