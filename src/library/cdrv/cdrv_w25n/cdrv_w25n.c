/**
 ******************************************************************************
 * @file           : cdrv_w25n.c
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
#include "cdrv_w25n.h"

#include "memory_test\memory_test.h"

#include <stdlib.h>

/* Private define ------------------------------------------------------------*/
#define BUSY_TIMEOUT_ms 15

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
static uint8_t fInit(sMemory * const me);
static uint8_t fErase(sMemory * const me, uint32_t address, uint32_t size);
static uint8_t fEraseAll(sMemory * const me);
static uint8_t fRead(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data);
static uint8_t fWrite(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data);
static uint8_t fVerify(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data);

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
uint8_t fCdrvW25Nxx_Init(sCdrvW25Nxx * const me, eCdrvW25Nxx_Chip chip) {

  me->_init = false;
  
  if((me->Spi == NULL) || (me->Cs == NULL)) {
    return 1;
  }
  
  me->_chip = chip;
  
  me->_pageSize = 2048;
  
  me->_init = true;
  me->Enable = true;
  
  fCdrvW25Nxx_WpDisable(me);
  
  if(w25n_begin(me) != 0) {
    return 1;
  }
  
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
sMemory* fCdrvW25Nxx_CreatePartition(sCdrvW25Nxx * const me, uint32_t start_addr, uint32_t size) {
  
  CHECK_INIT_(NULL);
  CHECK_ENABLE_(NULL);
  
  static struct sMemoryVtbl const vtbl = {
    fInit,
    fErase,
    fEraseAll,
    fRead,
    fWrite,
    fVerify,
  };
  
  if((start_addr + size) > fCdrvW25Nxx_GetSize(me)) {
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
uint8_t fCdrvW25Nxx_WpDisable(sCdrvW25Nxx * const me) {

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
uint8_t fCdrvW25Nxx_WpEnable(sCdrvW25Nxx * const me) {
  
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
uint32_t fCdrvW25Nxx_GetSize(sCdrvW25Nxx * const me) {

  CHECK_INIT_(NULL);
  CHECK_ENABLE_(NULL);

  return w25n_getMaxPage(me) * 2048;
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
/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t fInit(sMemory * const me) {
  
  me->_init = true;
  me->Enable = true;
  
//  if(meMemoryTest_8Bit_NonDestruvtive_Connection(me) != 0) {
//    
//    me->_init = false;
//    me->Enable = false;
//    
//    return 1;
//  }
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t fErase(sMemory * const me, uint32_t address, uint32_t size) {

//  CHECK_INIT_(1);
//  CHECK_ENABLE_(1);
//  
//  sCdrvW25Nxx *dev = (sCdrvW25Nxx*)me->pDevice;
//  
//  if(size  == 0) {
//    return 1;
//  }
//  
//  if((address + size) > (me->StartAddress + me->Size)) {
//    return 1;
//  }
//  
//  address += me->StartAddress;
//  
//  for(uint16_t i = 0; i<dev->_pageSize; i++) {
//    dev->tmp_buffer[i] = FORMAT_VALUE;
//  }
//  
//  uint16_t i;
//  uint16_t first_page_byte_size, last_page_byte_size, complete_page_qty;
//  uint32_t tmp_addr;
//  
//  first_page_byte_size = dev->_pageSize - (address % dev->_pageSize);

//  if(size <= first_page_byte_size) {
//    first_page_byte_size = size;
//    last_page_byte_size = 0;
//    complete_page_qty = 0;
//  } else {
//    last_page_byte_size = (address + size) % dev->_pageSize;
//    complete_page_qty= (size - (first_page_byte_size + last_page_byte_size)) / dev->_pageSize;
//  }
//  
//  tmp_addr = address;
//  
//  if(WriteMemory(dev, tmp_addr, first_page_byte_size, dev->tmp_buffer, EEPROMEX_WRITE) != 0) {
//    return 1;
//  }
//  
//  if(IsDeviceReady(dev, MIN_TRIALS) == false) {
//    return 1;
//  }
//    
//  if(complete_page_qty > 0) {
//    for(i=0; i<complete_page_qty; i++) {
//      tmp_addr = address + first_page_byte_size + (i * dev->_pageSize);
//      
//      if(WriteMemory(dev, tmp_addr, dev->_pageSize, dev->tmp_buffer, EEPROMEX_WRITE) != 0) {
//        return 1;
//      }
//      
//      if(IsDeviceReady(dev, MIN_TRIALS) == false) {
//        return 1;
//      }
//    }
//  }
//  
//  if(last_page_byte_size > 0) {
//    tmp_addr = address + first_page_byte_size + (complete_page_qty * dev->_pageSize);
//    
//    if(WriteMemory(dev, tmp_addr, last_page_byte_size, dev->tmp_buffer, EEPROMEX_WRITE) != 0) {
//      return 1;
//    }
//    
//    if(IsDeviceReady(dev, MIN_TRIALS) == false) {
//      return 1;
//    }
//  }
//  
//  return(0);

  return 1;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t fEraseAll(sMemory * const me) {

  CHECK_INIT_(1);
  CHECK_ENABLE_(2);
  
  sCdrvW25Nxx *dev = (sCdrvW25Nxx*)me->pDevice;
  
  if(w25n_bulkErase(dev) != 0) {
    return 1;
  }
  
  return w25n_block_WIP(dev, 40000);  
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t fRead(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data) {
  
  CHECK_INIT_(1);
  CHECK_ENABLE_(2);
  
  sCdrvW25Nxx *dev = (sCdrvW25Nxx*)me->pDevice;
  
  if(size  == 0) {
    return 1;
  }
  
  address += me->StartAddress;
  
  if((address + size) > (me->StartAddress + me->Size)) {
    return 1;
  }
  
  uint16_t i;
  uint32_t first_page_byte_size, last_page_byte_size, complete_page_qty;
  uint32_t first_page_start_column;
  uint32_t page_index = 0;
  uint8_t *ptr;
  //uint32_t tmp_addr;
  
  first_page_start_column = (address % dev->_pageSize);
  first_page_byte_size = dev->_pageSize - first_page_start_column;
  page_index = (address / dev->_pageSize);
  
  if(size <= first_page_byte_size) {
    first_page_byte_size = size;
    last_page_byte_size = 0;
    complete_page_qty = 0;
  } else {
    last_page_byte_size = (address + size) % dev->_pageSize;
    complete_page_qty = (size - (first_page_byte_size + last_page_byte_size)) / dev->_pageSize;
  }
  
  ptr = data;
  //tmp_addr = address;

  if(w25n_read_page(dev, first_page_start_column, ptr, first_page_byte_size, page_index) != 0) {
    return 1;
  }
  page_index++;
  
  if(complete_page_qty > 0) {
    for(i=0; i<complete_page_qty; i++) {
      ptr = data + first_page_byte_size + (i * dev->_pageSize);
      //tmp_addr = address + first_page_byte_size + (i * dev->_pageSize);

      if(w25n_read_page(dev, 0, ptr, dev->_pageSize, page_index) != 0) {
        return 1;
      }
      page_index++;
    }
  }
  
  if(last_page_byte_size > 0) {
    ptr = data + first_page_byte_size + (complete_page_qty * dev->_pageSize);
    //tmp_addr = address + first_page_byte_size + (complete_page_qty * dev->_pageSize);

    if(w25n_read_page(dev, 0, ptr, last_page_byte_size, page_index) != 0) {
      return 1;
    }    
  }
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t fWrite(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data) {

  CHECK_INIT_(1);
  CHECK_ENABLE_(2);
  
  sCdrvW25Nxx *dev = (sCdrvW25Nxx*)me->pDevice;
  
  if(size  == 0) {
    return 1;
  }
  
  address += me->StartAddress;
  
  if((address + size) > (me->StartAddress + me->Size)) {
    return 1;
  }
  
  uint16_t i;
  uint32_t first_page_byte_size, last_page_byte_size, complete_page_qty;
  uint32_t first_page_start_column;
  uint32_t page_index = 0;
  uint8_t *ptr;
  //uint32_t tmp_addr;
  
  first_page_start_column = (address % dev->_pageSize);
  first_page_byte_size = dev->_pageSize - first_page_start_column;
  page_index = (address / dev->_pageSize);
  
  if(size <= first_page_byte_size) {
    first_page_byte_size = size;
    last_page_byte_size = 0;
    complete_page_qty = 0;
  } else {
    last_page_byte_size = (address + size) % dev->_pageSize;
    complete_page_qty = (size - (first_page_byte_size + last_page_byte_size)) / dev->_pageSize;
  }
  
  ptr = data;
  //tmp_addr = address;

  if(w25n_write_page(dev, first_page_start_column, ptr, first_page_byte_size, page_index) != 0) {
    return 1;
  }
  page_index++;
  
  if(complete_page_qty > 0) {
    for(i=0; i<complete_page_qty; i++) {
      ptr = data + first_page_byte_size + (i * dev->_pageSize);
      //tmp_addr = address + first_page_byte_size + (i * dev->_pageSize);

      if(w25n_write_page(dev, 0, ptr, dev->_pageSize, page_index) != 0) {
        return 1;
      }
      page_index++;
    }
  }
  
  if(last_page_byte_size > 0) {
    ptr = data + first_page_byte_size + (complete_page_qty * dev->_pageSize);
    //tmp_addr = address + first_page_byte_size + (complete_page_qty * dev->_pageSize);

    if(w25n_write_page(dev, 0, ptr, last_page_byte_size, page_index) != 0) {
      return 1;
    }    
  }
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t fVerify(sMemory * const me, uint32_t address, uint32_t size, uint8_t *data) {

  CHECK_INIT_(1);
  CHECK_ENABLE_(2);
  
  sCdrvW25Nxx *dev = (sCdrvW25Nxx*)me->pDevice;
  
  if(size  == 0) {
    return 1;
  }
  
  address += me->StartAddress;
  
  if((address + size) > (me->StartAddress + me->Size)) {
    return 1;
  }
  
  uint16_t i;
  uint32_t first_page_byte_size, last_page_byte_size, complete_page_qty;
  uint32_t first_page_start_column;
  uint32_t page_index = 0;
  uint8_t *ptr;
  //uint32_t tmp_addr;
  
  first_page_start_column = (address % dev->_pageSize);
  first_page_byte_size = dev->_pageSize - first_page_start_column;
  page_index = (address / dev->_pageSize);
  
  if(size <= first_page_byte_size) {
    first_page_byte_size = size;
    last_page_byte_size = 0;
    complete_page_qty = 0;
  } else {
    last_page_byte_size = (address + size) % dev->_pageSize;
    complete_page_qty = (size - (first_page_byte_size + last_page_byte_size)) / dev->_pageSize;
  }
  
  ptr = data;
  //tmp_addr = address;

  if(w25n_verify_page(dev, first_page_start_column, ptr, first_page_byte_size, page_index) != 0) {
    return 1;
  }
  page_index++;
  
  if(complete_page_qty > 0) {
    for(i=0; i<complete_page_qty; i++) {
      ptr = data + first_page_byte_size + (i * dev->_pageSize);
      //tmp_addr = address + first_page_byte_size + (i * dev->_pageSize);

      if(w25n_verify_page(dev, 0, ptr, dev->_pageSize, page_index) != 0) {
        return 1;
      }
      page_index++;
    }
  }
  
  if(last_page_byte_size > 0) {
    ptr = data + first_page_byte_size + (complete_page_qty * dev->_pageSize);
    //tmp_addr = address + first_page_byte_size + (complete_page_qty * dev->_pageSize);

    if(w25n_verify_page(dev, 0, ptr, last_page_byte_size, page_index) != 0) {
      return 1;
    }    
  }
  
  return 0;
}

///////////////////
/* w25n_begin(int cs) -- initialises the flash and checks that the flash is 
     * functioning and is the right model.
     * Output -- 0 if working, 1 if error*/ 
int w25n_begin(sCdrvW25Nxx * const me){
  
  fGpio_Set_(me->Cs);

  w25n_reset(me);

  uint8_t jedec[5] = {W25N_JEDEC_ID, 0x00, 0x00, 0x00, 0x00};
  
  fGpio_Reset_(me->Cs);
  fSpi_TransmitReceive_(me->Spi, jedec, me->_rxBuffer, sizeof(jedec), 1000);
  fGpio_Set_(me->Cs);
  
  if(me->_rxBuffer[2] == WINBOND_MAN_ID){
    
    if((uint16_t)(me->_rxBuffer[3] << 8 | me->_rxBuffer[4]) == W25N01GV_DEV_ID){
      
      w25n_setStatusReg(me, W25N_PROT_REG, 0x00);
      me->_chip = eW25N01GV;
      return 0;
    }
    
    if((uint16_t)(me->_rxBuffer[3] << 8 | me->_rxBuffer[4]) == W25M02GV_DEV_ID){
      
      me->_chip = eW25M02GV;
      w25n_dieSelect(me, 0);
      w25n_setStatusReg(me, W25N_PROT_REG, 0x00);
      w25n_dieSelect(me, 1);
      w25n_setStatusReg(me, W25N_PROT_REG, 0x00);
      w25n_dieSelect(me, 0);
      
      return 0;
    }
  }
  
  return 1;
}

/* w25n_reset() -- resets the pDevice. */
void w25n_reset(sCdrvW25Nxx * const me){
  
  //TODO check WIP in case of reset during write
  uint8_t buf[] = {W25N_RESET};
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, buf, sizeof(buf), 1000);
  fGpio_Set_(me->Cs);
  
  fChrono_DelayUs(600);
}

int w25n_dieSelect(sCdrvW25Nxx * const me, uint8_t die){
  
  //TODO add some type of input validation
  uint8_t buf[2] = {W25M_DIE_SELECT, die};
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, buf, sizeof(buf), 1000);
  fGpio_Set_(me->Cs);
  
  me->_dieSelect = die;
  return 0;
}

/* int w25n_dieSelectOnAdd(uint32_t pageAdd) -- auto changes selected die based on requested address
     * Input - full range (across all dies) page address
     * Output - error output, 0 for success
     */
int w25n_dieSelectOnAdd(sCdrvW25Nxx * const me, uint32_t pageAdd){
  
  if(pageAdd > w25n_getMaxPage(me)) {
    return 1;
  }
  
  return w25n_dieSelect(me, pageAdd / W25N01GV_MAX_PAGE);
}

/* w25n_getStatusReg(char reg) -- gets the char value from one of the registers:
     * W25N_STAT_REG / W25N_CONFIG_REG / W25N_PROT_REG
     * Output -- register byte value
     */
char w25n_getStatusReg(sCdrvW25Nxx * const me, char reg){
  
  uint8_t buf[3] = {W25N_READ_STATUS_REG, reg, 0x00};
  
  fGpio_Reset_(me->Cs);
  fSpi_TransmitReceive_(me->Spi, buf, me->_rxBuffer, sizeof(buf), 1000);
  fGpio_Set_(me->Cs);
  
  return me->_rxBuffer[2];
}

/* w25n_setStatusReg(char reg, char set) -- Sets one of the status registers:
     * W25N_STAT_REG / W25N_CONFIG_REG / W25N_PROT_REG
     * set input -- char input to set the reg to */
void w25n_setStatusReg(sCdrvW25Nxx * const me, char reg, char set){
  
  uint8_t buf[3] = {W25N_WRITE_STATUS_REG, reg, set};
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, buf, sizeof(buf), 1000);
  fGpio_Set_(me->Cs);
}

/* w25n_getMaxPage() Returns the max page for the given chip
     */
uint32_t w25n_getMaxPage(sCdrvW25Nxx * const me){
  
  if (me->_chip == eW25M02GV) {
    return W25M02GV_MAX_PAGE;
  }
  
  if (me->_chip == eW25N01GV) {
    return W25N01GV_MAX_PAGE;
  }
  
  return 0;
}

/* w25n_writeEnable() -- enables write opperations on the chip.
     * Is disabled after a write operation and must be recalled.
     */
void w25n_writeEnable(sCdrvW25Nxx * const me){
  
  uint8_t buf[] = {W25N_WRITE_ENABLE};
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, buf, sizeof(buf), 1000);
  fGpio_Set_(me->Cs);
}

/* w25n_writeDisable() -- disables all write opperations on the chip */
void w25n_writeDisable(sCdrvW25Nxx * const me){
  
  uint8_t buf[] = {W25N_WRITE_DISABLE};
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, buf, sizeof(buf), 1000);
  fGpio_Set_(me->Cs);
}

/* w25n_blockErase(uint32_t pageAdd) -- Erases one block of data on the flash chip. One block is 64 Pages, and any given 
     * page address within the block will erase that block.
     * Rerturns 0 if successful
     * */
int w25n_blockErase(sCdrvW25Nxx * const me, uint32_t pageAdd){
  
  if(pageAdd > w25n_getMaxPage(me)) {
    return 1;
  }
  
  w25n_dieSelectOnAdd(me, pageAdd);
  
  uint8_t pageHigh = (char)((pageAdd & 0xFF00) >> 8);
  uint8_t pageLow = (char)(pageAdd);
  uint8_t buf[4] = {W25N_BLOCK_ERASE, 0x00, pageHigh, pageLow};
  
  if(w25n_block_WIP(me, 1000) != 0) {
    return 1;
  }
    
  w25n_writeEnable(me);
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, buf, sizeof(buf), 1000);
  fGpio_Set_(me->Cs);
  
  return 0;
}

/* w25n_bulkErase() -- Erases the entire chip
     * THIS TAKES A VERY LONG TIME, ~30 SECONDS
     * Returns 0 if successful 
     * */
int w25n_bulkErase(sCdrvW25Nxx * const me) {
  
  int error = 0;
  for(uint32_t i = 0; i < w25n_getMaxPage(me); i+=64){
    
    if((error = w25n_blockErase(me, i)) != 0) {
      return error;
    }
  }
  
  return 0;
}

/* w25n_loadProgData(uint16_t columnAdd, char* buf, uint32_t dataLen) -- Transfers datalen number of bytes from the 
     * given buffer to the internal flash buffer, to be programed once a ProgramExecute command is sent.
     * datalLen cannot be more than the internal buffer size of 2111 bytes, or 2048 if ECC is enabled on chip.
     * When called any data in the internal buffer beforehand will be nullified.
     * WILL ERASE THE DATA IN BUF OF LENGTH DATALEN BYTES
     * */
int w25n_writeToInternalBuffer(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen) {
  
  if(columnAdd > (uint32_t)W25N_MAX_COLUMN) {
    return 1;
  }
  
  if(dataLen > (uint32_t)W25N_MAX_COLUMN - columnAdd) {
    return 1;
  }
  
  uint8_t columnHigh = (columnAdd & 0xFF00) >> 8;
  uint8_t columnLow = columnAdd & 0xff;
  uint8_t cmdbuf[3] = {W25N_PROG_DATA_LOAD, columnHigh, columnLow};
  
  if(w25n_block_WIP(me, BUSY_TIMEOUT_ms) != 0) {
    return 1;
  }
  w25n_writeEnable(me);
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, cmdbuf, sizeof(cmdbuf), 1000);
  fSpi_Transmit_(me->Spi, buf, dataLen, 1000);
  fGpio_Set_(me->Cs);
  
  return 0;
}

//int w25n_loadProgData(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen, uint32_t pageAdd){
//  
//  if(w25n_dieSelectOnAdd(me, pageAdd)) {
//    return 1;
//  }
//  
//  return w25n_loadProgData(me, columnAdd, buf, dataLen);
//}

/* w25n_loadRandProgData(uint16_t columnAdd, char* buf, uint32_t dataLen) -- Transfers datalen number of bytes from the 
     * given buffer to the internal flash buffer, to be programed once a ProgramExecute command is sent.
     * datalLen cannot be more than the internal buffer size of 2111 bytes, or 2048 if ECC is enabled on chip.
     * Unlike the normal loadProgData the loadRandProgData function allows multiple transfers to the internal buffer
     * without the nulling of the currently kept data. 
     * WILL ERASE THE DATA IN BUF OF LENGTH DATALEN BYTES
     */
int w25n_writeRandToInternalBuffer(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen) {
  
  if(columnAdd > (uint32_t)W25N_MAX_COLUMN) {
    return 1;
  }
  
  if(dataLen > (uint32_t)W25N_MAX_COLUMN - columnAdd) {
    return 1;
  }
  
  uint8_t columnHigh = (columnAdd & 0xFF00) >> 8;
  uint8_t columnLow = columnAdd & 0xff;
  uint8_t cmdbuf[3] = {W25N_RAND_PROG_DATA_LOAD, columnHigh, columnLow};
  
  if(w25n_block_WIP(me, BUSY_TIMEOUT_ms) != 0) {
    return 1;
  }
  w25n_writeEnable(me);
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, cmdbuf, sizeof(cmdbuf), 1000);
  fSpi_Transmit_(me->Spi, buf, dataLen, 1000);  
  fGpio_Set_(me->Cs);
  
  return 0;
}

//int w25n_loadRandProgData(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen, uint32_t pageAdd){
//  
//  if(w25n_dieSelectOnAdd(me, pageAdd)) {
//    return 1;
//  }
//  
//  return w25n_loadRandProgData(me, columnAdd, buf, dataLen);
//}

/* w25n_ProgramExecute(uint32_t add) -- Commands the flash to program the internal buffer contents to the addres page
     * given after a loadProgData or loadRandProgData has been called.
     * The selected page needs to be erased prior to use as the falsh chip can only change 1's to 0's
     * This command will put the flash in a busy state for a time, so busy checking is required ater use.  */
int w25n_writeInternalBufferToPage(sCdrvW25Nxx * const me, uint32_t pageAdd) {
  
  if(pageAdd > w25n_getMaxPage(me)) {
    return 1;
  }
  
  w25n_dieSelectOnAdd(me, pageAdd);
  
  uint8_t pageHigh = (char)((pageAdd & 0xFF00) >> 8);
  uint8_t pageLow = (char)(pageAdd);
  
  w25n_writeEnable(me);
  
  uint8_t buf[4] = {W25N_PROG_EXECUTE, 0x00, pageHigh, pageLow};
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, buf, sizeof(buf), 1000);
  fGpio_Set_(me->Cs);
  
  return 0;
}

//w25n_pageDataw25n_read(uint32_t add) -- Commands the flash to read from the given page address into
    //its internal buffer, to be read using the w25n_read() function. 
    //This command will put the flash in a busy state for a time, so busy checking is required after use.
int w25n_readPageToInternalBuffer(sCdrvW25Nxx * const me, uint32_t pageAdd) {
  
  if(pageAdd > w25n_getMaxPage(me)) {
    return 1;
  }
  
  w25n_dieSelectOnAdd(me, pageAdd);
  
  uint8_t pageHigh = (char)((pageAdd & 0xFF00) >> 8);
  uint8_t pageLow = (char)(pageAdd);
  uint8_t buf[4] = {W25N_PAGE_DATA_READ, 0x00, pageHigh, pageLow};
  
  if(w25n_block_WIP(me, BUSY_TIMEOUT_ms) != 0) {
    return 1;
  }
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, buf, sizeof(buf), 1000);
  fGpio_Set_(me->Cs);
  
  return 0;

}

//w25n_read(uint16_t columnAdd, char* buf, uint32_t dataLen) -- Reads data from the flash internal buffer
    //columnAdd is a buffer index (0-2047) or (0 - 2111) including ECC bits
    //char* buf is a pointer to the buffer to be read into
    //datalen is the length of data that should be read from the buffer (up to 2111)
int w25n_readInternalBuffer(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen) {
  
  if(columnAdd > (uint32_t)W25N_MAX_COLUMN) {
    return 1;
  }
  
  if(dataLen > (uint32_t)W25N_MAX_COLUMN - columnAdd) {
    return 1;
  }
  
  uint8_t columnHigh = (columnAdd & 0xFF00) >> 8;
  uint8_t columnLow = columnAdd & 0xff;
  uint8_t cmdbuf[4] = {W25N_READ, columnHigh, columnLow, 0x00};
  
  if(w25n_block_WIP(me, BUSY_TIMEOUT_ms) != 0) {
    return 1;
  }
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, cmdbuf, sizeof(cmdbuf), 1000);
  fSpi_Receive_(me->Spi, buf, dataLen, 1000);
  fGpio_Set_(me->Cs);
  
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param columnAdd 
 * @param buf 
 * @param dataLen 
 * @return int 
 */
int w25n_verifyByInternalBuffer(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen) {
  
  if(columnAdd > (uint32_t)W25N_MAX_COLUMN) {
    return 1;
  }
  
  if(dataLen > (uint32_t)W25N_MAX_COLUMN - columnAdd) {
    return 1;
  }
  
  uint8_t columnHigh = (columnAdd & 0xFF00) >> 8;
  uint8_t columnLow = columnAdd & 0xff;
  uint8_t cmdbuf[4] = {W25N_READ, columnHigh, columnLow, 0x00};
  
  if(w25n_block_WIP(me, BUSY_TIMEOUT_ms) != 0) {
    return 1;
  }
  
  fGpio_Reset_(me->Cs);
  fSpi_Transmit_(me->Spi, cmdbuf, sizeof(cmdbuf), 1000);
  fSpi_Receive_(me->Spi, me->_rxBuffer, dataLen, 1000);
  fGpio_Set_(me->Cs);
  
  for(int i=0; i<dataLen; i++) {
    
    if(me->_rxBuffer[i] != buf[i]) {
      return 1;
    }
    
  }
  
  return 0;
}

//w25n_check_WIP() -- checks if the flash is busy with an operation
    //Output: true if busy, false if free
int w25n_check_WIP(sCdrvW25Nxx * const me) {
  
  char status = w25n_getStatusReg(me, W25N_STAT_REG);
  if(status & 0x01){
    return 1;
  }
  return 0;
}                      

//w25n_block_WIP() -- checks if the flash is busy and only returns once free
    //Has a 15ms timeout
int w25n_block_WIP(sCdrvW25Nxx * const me, uint32_t timeout_ms){
  
  sChrono chrono;
  fChrono_StartTimeoutMs(&chrono, timeout_ms);
  
  while(w25n_check_WIP(me)){
    
    if(fChrono_IsTimeout(&chrono) == true) {
      return 1;
    }
    
    fChrono_DelayUs(10);
  }
  
  return 0;
}

int w25n_check_status(sCdrvW25Nxx * const me){
  
  return(w25n_getStatusReg(me, W25N_STAT_REG));
}

int w25n_write_page(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen, uint32_t pageAdd) {
  
  if(w25n_readPageToInternalBuffer(me, pageAdd) != 0) {
    return 1;
  }
  
  if(w25n_block_WIP(me, 5000) != 0) {
    return 1;
  }
  
  if(w25n_writeToInternalBuffer(me, columnAdd, buf, dataLen) != 0) {
    return 1;
  }
  
  if(w25n_block_WIP(me, 5000) != 0) {
    return 1;
  }
  
  if(w25n_writeInternalBufferToPage(me, pageAdd) != 0) {
    return 1;
  }
  
  if(w25n_block_WIP(me, 5000) != 0) {
    return 1;
  }
  
  return 0;
}

int w25n_read_page(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen, uint32_t pageAdd) {
  
  if(w25n_readPageToInternalBuffer(me, pageAdd) != 0) {
    return 1;
  }
  
  if(w25n_block_WIP(me, 5000) != 0) {
    return 1;
  }
  
  if(w25n_readInternalBuffer(me, columnAdd, buf, dataLen) != 0) {
    return 1;
  }
  
  return 0;
}

int w25n_verify_page(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen, uint32_t pageAdd) {
  
  if(w25n_readPageToInternalBuffer(me, pageAdd) != 0) {
    return 1;
  }
  
  if(w25n_block_WIP(me, 5000) != 0) {
    return 1;
  }
  
  if(w25n_verifyByInternalBuffer(me, columnAdd, buf, dataLen) != 0) {
    return 1;
  }
  
  return 0;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
