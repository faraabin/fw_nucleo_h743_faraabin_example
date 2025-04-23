/**
 ******************************************************************************
 * @file           : cdrv_m95xxx.c
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

/* Includes ------------------------------------------------------------------*/
#include "cdrv_m95xxx.h"

#include "memory_test\memory_test.h"

#include <stdlib.h>

/* Private define ------------------------------------------------------------*/
#define MIN_TRIALS              1
#define LOCKID                  0x02   /* Byte to be send to lock ID page*/    
#define ADDRLID_16              0x0400
  
#define ADDRLID_SPI             0x0480    
#define LOCKDATA_SPI            0x02
    
#define BITCOUNT                0x01  /* Initial count value */
#define IDMASK                  0x04  /* Mask fith bit of I2C mem pDevice address */
    
#define EEPROMEX_WREN           0x06  /*!< Write enable instruction */
#define EEPROMEX_WRDI           0x04  /*!< Write disable instruction */
#define EEPROMEX_RDSR           0x05  /*!< Read Status Register instruction  */
#define EEPROMEX_WRSR           0x01  /*!< Write Status Register instruction */
#define EEPROMEX_WRITE          0x02  /*!< Lower Half Write to Memory instruction */
#define EEPROMEX_UPWRITE        0x0A  /*!< Upper Half Write to Memory instruction */
#define EEPROMEX_READ           0x03  /*!< Lower Half Read from Memory instruction */
#define EEPROMEX_UPREAD         0x0B  /*!< Upper Half Read from Memory instruction */
#define EEPROMEX_RDID           0x83  /*!< Read identifiction instruction */
#define EEPROMEX_WRID           0x82  /*!< Write identifiction instruction */
#define EEPROMEX_RDLS           0x83  /*!< Read ID page lock status instruction */
#define EEPROMEX_LID            0x82  /*!< Lock ID page in read only mode instruction */
#define EEPROMEX_FullProtect    0x0C  /*!< Whole memory protect from write - Write BP1 BP2 bits as 11 in status register */
#define EEPROMEX_UHalfProtect   0x08  /*!< Upper Half Protect from write - Write BP1 BP2 bits as 10 in status register */
#define EEPROMEX_UQuarterProtect 0x04  /*!< Upper Quarter Protect from write - Write BP1 BP2 bits as 01 in status register */
#define EEPROMEX_UnProtect      0x00  /*!< Un Protect from read only mode - Write BP1 BP2 bits as 10 in status register */

#define EEPROMEX_SPI_WIPFLAG  0x01U

#define FORMAT_VALUE 0xFF

#define READY_TIMEOUT_ms  100

/* Private macro -------------------------------------------------------------*/
/**
 * @brief 
 * 
 */
#define CHECK_INIT_(ret_)\
if(!me->_init) {\
  return (ret_);\
}

/**
 * @brief 
 * 
 */
#define CHECK_ENABLE_(ret_)\
if(!me->Enable) {\
  return (ret_);\
}

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t Init(sMemory * const me);
static uint8_t Erase(sMemory * const me, uint32_t address, uint32_t size);
static uint8_t Erase_all(sMemory * const me);
static uint8_t Read(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data);
static uint8_t Write(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data);
static uint8_t Verify(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data);

static uint8_t WriteMemory(sCdrvM95xxx * const me, uint32_t addr, uint16_t size, uint8_t *data, uint8_t inst);
static uint8_t WriteCmd(sCdrvM95xxx * const me, uint8_t data);
static uint8_t WriteAddr(sCdrvM95xxx * const me, uint32_t addr);
static bool IsDeviceReady(sCdrvM95xxx * const me, uint32_t trials);

/* Variables -----------------------------------------------------------------*/

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Exported Functions #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 * @param me 
 * @param chip 
 * @return uint8_t 
 */
uint8_t fCdrvM95xxx_Init(sCdrvM95xxx * const me, eCdrvM95xxxChip chip) {
  
  me->_init = false;
  
  if((me->Spi == NULL) || (me->Cs == NULL)) {
    return 1;
  }
  
  me->_chip = chip;
  
  switch(me->_chip) {

    case eDEVICE_M95080: {
      
      me->_pageSize = 32;
      me->_addrByteQty = 2;
      me->_tmpBuffer = (uint8_t*)malloc(me->_pageSize);
      if(me->_tmpBuffer == NULL) {
        return 1;
      }
      
      break;
    }
    
    case eDEVICE_M95640: {
      
      me->_pageSize = 32;
      me->_addrByteQty = 2;
      me->_tmpBuffer = (uint8_t*)malloc(me->_pageSize);
      if(me->_tmpBuffer == NULL) {
        return 1;
      }
      
      break;
    }
    
    case eDEVICE_M95M01: {
      
      me->_pageSize = 256;
      me->_addrByteQty = 3;
      me->_tmpBuffer = (uint8_t*)malloc(me->_pageSize);
      if(me->_tmpBuffer == NULL) {
        return 1;
      }
      
      break;
    }
    
    default: {
      return 1;
    }
  }
  
  me->_init = true;
  me->Enable = true;
  
  fCdrvM95xxx_WpDisable(me);
  
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param start_addr 
 * @param size 
 * @return sMemory* 
 */
sMemory* fCdrvM95xxx_CreatePartirion(sCdrvM95xxx * const me, uint32_t start_addr, uint32_t size) {

  CHECK_INIT_(NULL);
  CHECK_ENABLE_(NULL);
  
  static struct sMemoryVtbl const vtbl = {
    Init,
    Erase,
    Erase_all,
    Read,
    Write,
    Verify,
  };
  
  if((start_addr + size) > fCdrvM95xxx_GetSize(me)) {
    return NULL;
  }
  
  sMemory *partition = (sMemory*)malloc(sizeof(sMemory));
  if(partition == NULL) {
    return NULL;
  }
  
  partition->_init = false;
  partition->Enable = false;
  partition->_vtbl = &vtbl;
  partition->StartAddress = start_addr;
  partition->Size = size;
  partition->pDevice = me;

  return partition;  
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvM95xxx_WpDisable(sCdrvM95xxx * const me) {

  CHECK_INIT_(NULL);
  CHECK_ENABLE_(NULL);
  
  if(me->Wp != NULL) {
    fGpio_Write_(me->Wp, 0);
  }
  
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvM95xxx_WpEnable(sCdrvM95xxx * const me) {

  CHECK_INIT_(NULL);
  CHECK_ENABLE_(NULL);
  
  if(me->Wp != NULL) {
    fGpio_Write_(me->Wp, 1);
  }
  
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint32_t 
 */
uint32_t fCdrvM95xxx_GetSize (sCdrvM95xxx * const me) {

  CHECK_INIT_(NULL);
  CHECK_ENABLE_(NULL);
  
  switch(me->_chip) {
    
    case eDEVICE_M95080: {
      return 1024;
    }
    
    case eDEVICE_M95640: {
      return 8192;
    }
    
    case eDEVICE_M95M01: {
      return 131072;
    }
    
    default: {
      return 0;
    }
  }
}

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Private Functions #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t Init(sMemory * const me) {

  me->_init = true;
  me->Enable = true;
  
  if(fMemoryTest_8Bit_NonDestructive_Connection(me) != 0) {
    return 1;
  }
  
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
static uint8_t Erase(sMemory * const me, uint32_t address, uint32_t size) {
  
  CHECK_INIT_(1);
  CHECK_ENABLE_(1);
  
  sCdrvM95xxx *dev = (sCdrvM95xxx*)me->pDevice;
  
  if(size  == 0) {
    return 1;
  }
  
  if((address + size) > (me->StartAddress + me->Size)) {
    return 1;
  }
  
  address += me->StartAddress;
  
  for(uint16_t i = 0; i<dev->_pageSize; i++) {
    dev->_tmpBuffer[i] = FORMAT_VALUE;
  }
  
  uint16_t i;
  uint16_t first_page_byte_size, last_page_byte_size, complete_page_qty;
  uint32_t tmp_addr;
  
  first_page_byte_size = dev->_pageSize - (address % dev->_pageSize);

  if(size <= first_page_byte_size) {
    first_page_byte_size = size;
    last_page_byte_size = 0;
    complete_page_qty = 0;
  } else {
    last_page_byte_size = (address + size) % dev->_pageSize;
    complete_page_qty= (size - (first_page_byte_size + last_page_byte_size)) / dev->_pageSize;
  }
  
  tmp_addr = address;
  
  if(WriteMemory(dev, tmp_addr, first_page_byte_size, dev->_tmpBuffer, EEPROMEX_WRITE) != 0) {
    return 1;
  }
  
  if(IsDeviceReady(dev, MIN_TRIALS) == false) {
    return 1;
  }
    
  if(complete_page_qty > 0) {
    for(i=0; i<complete_page_qty; i++) {
      tmp_addr = address + first_page_byte_size + (i * dev->_pageSize);
      
      if(WriteMemory(dev, tmp_addr, dev->_pageSize, dev->_tmpBuffer, EEPROMEX_WRITE) != 0) {
        return 1;
      }
      
      if(IsDeviceReady(dev, MIN_TRIALS) == false) {
        return 1;
      }
    }
  }
  
  if(last_page_byte_size > 0) {
    tmp_addr = address + first_page_byte_size + (complete_page_qty * dev->_pageSize);
    
    if(WriteMemory(dev, tmp_addr, last_page_byte_size, dev->_tmpBuffer, EEPROMEX_WRITE) != 0) {
      return 1;
    }
    
    if(IsDeviceReady(dev, MIN_TRIALS) == false) {
      return 1;
    }
  }
  
  return(0);
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t Erase_all(sMemory * const me) {
  
  CHECK_INIT_(1);
  CHECK_ENABLE_(1);

  return Erase(me, 0, me->Size);
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
static uint8_t Read(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data) {

  CHECK_INIT_(1);
  CHECK_ENABLE_(1);
  
  sCdrvM95xxx *dev = (sCdrvM95xxx*)me->pDevice;
  
  if(size  == 0) {
    return 1;
  }
  
  if((address + size) > (me->StartAddress + me->Size)) {
    return 1;
  }
  
  address += me->StartAddress;
  
  if(IsDeviceReady(dev, MIN_TRIALS) == false) {
    return 1;
  }
  
  fGpio_Write_(dev->Cs, 0);
  
  uint8_t inst = EEPROMEX_READ;
  if(fSpi_Transmit_(dev->Spi, &inst, 1, dev->SpiTimeoutMs) != 0) {
    return 1;
  }
  
  if(WriteAddr(dev, address) != 0) { 
    return 1;
  }
  
  if(fSpi_Receive_(dev->Spi, data, size, dev->SpiTimeoutMs) != 0) {
    return 1;
  }
  
  fGpio_Write_(dev->Cs, 1);
  
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
static uint8_t Write(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data) {

  CHECK_INIT_(1);
  CHECK_ENABLE_(1);
  
  sCdrvM95xxx *dev = (sCdrvM95xxx*)me->pDevice;
  
  if(size  == 0) {
    return 1;
  }
  
  if((address + size) > (me->StartAddress + me->Size)) {
    return 1;
  }
  
  address += me->StartAddress;
  
  uint16_t i;
  uint16_t first_page_byte_size, last_page_byte_size, complete_page_qty;
  uint8_t *ptr;
  uint32_t tmp_addr;
  
  first_page_byte_size = dev->_pageSize - (address % dev->_pageSize);

  if(size <= first_page_byte_size) {
    first_page_byte_size = size;
    last_page_byte_size = 0;
    complete_page_qty = 0;
  } else {
    last_page_byte_size = (address + size) % dev->_pageSize;
    complete_page_qty = (size - (first_page_byte_size + last_page_byte_size)) / dev->_pageSize;
  }
  
  ptr = data;
  tmp_addr = address;

  if(WriteMemory(dev, tmp_addr, first_page_byte_size, ptr, EEPROMEX_WRITE) != 0) {
    return 1;
  }
  
  if(IsDeviceReady(dev, MIN_TRIALS) == false) {
    return 1;
  }
    
  if(complete_page_qty > 0) {
    for(i=0; i<complete_page_qty; i++) {
      ptr = data + first_page_byte_size + (i * dev->_pageSize);
      tmp_addr = address + first_page_byte_size + (i * dev->_pageSize);

      if(WriteMemory(dev, tmp_addr, dev->_pageSize, ptr, EEPROMEX_WRITE) != 0) {
        return 1;
      }
      
      if(IsDeviceReady(dev, MIN_TRIALS) == false) {
        return 1;
      }
    }
  }
  
  if(last_page_byte_size > 0) {
    ptr = data + first_page_byte_size + (complete_page_qty * dev->_pageSize);
    tmp_addr = address + first_page_byte_size + (complete_page_qty * dev->_pageSize);

    if(WriteMemory(dev, tmp_addr, last_page_byte_size, ptr, EEPROMEX_WRITE) != 0) {
      return 1;
    }
    
    if(IsDeviceReady(dev, MIN_TRIALS) == false) {
      return 1;
    }
  }
  
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
static uint8_t Verify(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data) {

  CHECK_INIT_(1);
  CHECK_ENABLE_(1);
  
  uint8_t tmp = 0;
  
  for(uint32_t i=0; i<size; i++) {
    if(Read(me, address + i, 1, &tmp) != 0) {
      return 1;
    }
    
    if(tmp != data[i]) {
      return 1;
    }
  }
  
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param addr 
 * @param size 
 * @param data 
 * @param inst 
 * @return uint8_t 
 */
static uint8_t WriteMemory(sCdrvM95xxx * const me, uint32_t addr, uint16_t size, uint8_t *data, uint8_t inst) {

  if(WriteCmd(me, EEPROMEX_WREN) != 0) {
    return 1; 
  }
  
  fGpio_Write_(me->Cs, 0);
  
  if(fSpi_Transmit_(me->Spi, &inst, 1, me->SpiTimeoutMs) != 0) {
    return 1;
  }
  
  if(WriteAddr(me, addr) != 0) {
    return 1;
  }
  
  if(fSpi_Transmit_(me->Spi, data, size, me->SpiTimeoutMs)!= 0) {
     return 1;
  }
  
  fGpio_Write_(me->Cs, 1);
  
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param cmd 
 * @return uint8_t 
 */
static uint8_t WriteCmd(sCdrvM95xxx * const me, uint8_t cmd) {

  uint8_t status; 
  
  fGpio_Write_(me->Cs, 0);
  
  status = fSpi_Transmit_(me->Spi, &cmd, 1, me->SpiTimeoutMs);
  
  fGpio_Write_(me->Cs, 1);
  
  return status;
}

/**
 * @brief 
 * 
 * @param me 
 * @param addr 
 * @return uint8_t 
 */
static uint8_t WriteAddr(sCdrvM95xxx * const me, uint32_t addr) {

  static uint8_t Addr[3];
  uint32_t addrpacket = addr;
  
  if(me->_addrByteQty == 2) {
    
    Addr[1] = (uint8_t)(addrpacket & 0xFF);
    addrpacket = addrpacket >> 8;
    Addr[0] = (uint8_t)(addrpacket & 0xFF);
    
  } else {
    
    Addr[2] = (uint8_t)(addrpacket & 0xFF);
    addrpacket = addrpacket >> 8;
    Addr[1] = (uint8_t)(addrpacket & 0xFF);
    addrpacket = addrpacket >> 8;
    Addr[0] = (uint8_t)(addrpacket & 0xFF);
    
  }
  
  return  fSpi_Transmit_(me->Spi, Addr, me->_addrByteQty, me->SpiTimeoutMs);
}

/**
 * @brief 
 * 
 * @param me 
 * @param trials 
 * @return true 
 * @return false 
 */
static bool IsDeviceReady(sCdrvM95xxx * const me, uint32_t trials) {

  uint8_t status = 0;
  
  fGpio_Write_(me->Cs, 0);

  uint8_t tmp = EEPROMEX_RDSR;
  if(fSpi_Transmit_(me->Spi, &tmp, 1, me->SpiTimeoutMs) != 0) {
    fGpio_Write_(me->Cs, 1);
    return false;
  }
  
  fChrono_StartTimeoutMs(&me->_timer, READY_TIMEOUT_ms);
  
  do {
    fSpi_Receive_(me->Spi, &status, 1, me->SpiTimeoutMs);
    
    if(fChrono_IsTimeout(&me->_timer) == true) {
      fGpio_Write_(me->Cs, 1);
      return false;
    }
    
  }while((status & EEPROMEX_SPI_WIPFLAG) == 1);
  
  fGpio_Write_(me->Cs, 1);
  
  return true;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
