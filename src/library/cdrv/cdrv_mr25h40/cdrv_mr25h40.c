/**
 ******************************************************************************
 *  @file         cdrv_MR25H40.c
 *  @brief        ...
 *  @author       ...
 *  @version      0.0.0.1
 *  @date         yyyy/mm/dd
 *  @copyright    COPYRIGHT(c) 2018 MicroEmbeds
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 * DESCRIPTION:
 *
 ******************************************************************************
 * HOW TO USE:
 *
 ******************************************************************************
 @verbatim
 @endverbatim
*/

/* Includes ------------------------------------------------------------------*/
#include "cdrv_mr25h40.h"

#include "library\memory\me_memory_test.h"
#include <stdlib.h>

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MR25H40CDC_WREN	0x06
#define MR25H40CDC_WRDI	0x04
#define MR25H40CDC_RDSR	0x05
#define MR25H40CDC_WRSR	0x01
#define MR25H40CDC_READ	0x03
#define MR25H40CDC_WRITE	0x02
#define MR25H40CDC_SLEEP	0xB9
#define MR25H40CDC_WAKE	0xAB

#define MR25H40CDC_SIZE	0x7FFFF


#define FORMAT_VALUE 0xFF

#define PAGE_SIZE 128

#define SPI_TIMEOUT 1000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t Init(TysMemory_Obj * const me);
static uint8_t Erase(TysMemory_Obj * const me, uint32_t address, uint32_t size);
static uint8_t Erase_all(TysMemory_Obj * const me);
static uint8_t Read(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data);
static uint8_t Write(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data);
static uint8_t Verify(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                       ##### Exported Function #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t fCdrvMR25H40_Init(sCdrvMR25H40_Obj * const me) {
  me->init = false;
  
  if((me->u_spi == NULL) || (me->u_cs == NULL)) {
    return 1;
  }
  
  me->tmp_buffer = (uint8_t*)malloc(PAGE_SIZE);
  if(me->tmp_buffer == NULL) {
    return 1;
  }
      
  me->init = true;
  me->u_enable = true;
  
  fCdrvMR25H40_WP_Disable(me);
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
TysMemory_Obj* fCdrvMR25H40_CreatePartirion(sCdrvMR25H40_Obj * const me, uint32_t start_addr, uint32_t size) {
  meCHECK_INIT_(NULL);
  meCHECK_ENABLE_(NULL);
  
  static struct TysMemoryVtbl const vtbl = {
    Init,
    Erase,
    Erase_all,
    Read,
    Write,
    Verify,
  };
  
  if((start_addr + size) > fCdrvMR25H40_GetSize(me)) {
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
  * @note
  * @param
  * @retval
*/
uint8_t fCdrvMR25H40_WP_Disable(sCdrvMR25H40_Obj * const me) {
  meCHECK_INIT_(NULL);
  meCHECK_ENABLE_(NULL);
  
  if(me->u_wp != NULL) {
    meGpio_Write_(me->u_wp, 0);
  }
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t fCdrvMR25H40_WP_Enable(sCdrvMR25H40_Obj * const me) {
  meCHECK_INIT_(NULL);
  meCHECK_ENABLE_(NULL);
  
  if(me->u_wp != NULL) {
    meGpio_Write_(me->u_wp, 1);
  }
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint32_t fCdrvMR25H40_GetSize (sCdrvMR25H40_Obj * const me) {
  meCHECK_INIT_(NULL);
  meCHECK_ENABLE_(NULL);
  
  return MR25H40CDC_SIZE;
}

/*
===============================================================================
                       ##### Private Functios #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Init(TysMemory_Obj * const me) {
  me->init = true;
  me->u_enable = true;
  
  sCdrvMR25H40_Obj *dev = (sCdrvMR25H40_Obj*)me->device;
  
  /*Set WEL Bit*/
  dev->tmp_buffer[0] = MR25H40CDC_WREN;
  
  meGpio_Reset_(dev->u_cs);
  meSpi_Transmit_(dev->u_spi, dev->tmp_buffer, 1, SPI_TIMEOUT);
  meGpio_Set_(dev->u_cs);
  
  /*Set Status Register*/
  dev->tmp_buffer[0] = MR25H40CDC_WRSR;
  dev->tmp_buffer[1] = 0x82;		
  
  meGpio_Reset_(dev->u_cs);
  meSpi_Transmit_(dev->u_spi, dev->tmp_buffer, 2, SPI_TIMEOUT);
  meGpio_Set_(dev->u_cs);
  
  if(meMemoryTest_8Bit_NonDestructive_Connection(me) != 0) {
    me->init = false;
    me->u_enable = false;
    
    return 1;
  }
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Erase(TysMemory_Obj * const me, uint32_t address, uint32_t size) {
  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);
  
  sCdrvMR25H40_Obj *dev = (sCdrvMR25H40_Obj*)me->device;
  
  if(size  == 0) {
    return 1;
  }
  
  if((address + size) > (me->u_start_address + me->u_size)) {
    return 1;
  }
  
  address += me->u_start_address;
  
  for(uint16_t i = 0; i<PAGE_SIZE; i++) {
    dev->tmp_buffer[i] = FORMAT_VALUE;
  }
  
  uint16_t i;
  uint16_t first_page_byte_size, last_page_byte_size, complete_page_qty;
  uint32_t tmp_addr;
  
  first_page_byte_size = PAGE_SIZE - (address % PAGE_SIZE);

  if(size <= first_page_byte_size) {
    first_page_byte_size = size;
    last_page_byte_size = 0;
    complete_page_qty = 0;
  } else {
    last_page_byte_size = (address + size) % PAGE_SIZE;
    complete_page_qty= (size - (first_page_byte_size + last_page_byte_size)) / PAGE_SIZE;
  }
  
  tmp_addr = address;
  
  if(Write(me, tmp_addr, first_page_byte_size, dev->tmp_buffer) != 0) {
    return 1;
  }
  
  if(complete_page_qty > 0) {
    for(i=0; i<complete_page_qty; i++) {
      tmp_addr = address + first_page_byte_size + (i * PAGE_SIZE);
      
      if(Write(me, tmp_addr, PAGE_SIZE, dev->tmp_buffer) != 0) {
        return 1;
      }
    }
  }
  
  if(last_page_byte_size > 0) {
    tmp_addr = address + first_page_byte_size + (complete_page_qty * PAGE_SIZE);
    
    if(Write(me, tmp_addr, last_page_byte_size, dev->tmp_buffer) != 0) {
      return 1;
    }
  }
  
  return(0);
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Erase_all(TysMemory_Obj * const me) {
  return Erase(me, 0, me->u_size);
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Read(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data) {
  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);
  
  sCdrvMR25H40_Obj *dev = (sCdrvMR25H40_Obj*)me->device;
  
  if(size  == 0) {
    return 1;
  }
  
  if((address + size) > (me->u_start_address + me->u_size)) {
    return 1;
  }
  
  address += me->u_start_address;
  
  dev->tmp_buffer[0] = MR25H40CDC_READ;
	dev->tmp_buffer[1] = address >> 16;
	dev->tmp_buffer[2] = address >> 8;
	dev->tmp_buffer[3] = address;
	
  meGpio_Reset_(dev->u_cs);
	meSpi_Transmit_(dev->u_spi, dev->tmp_buffer, 4, SPI_TIMEOUT);
	meSpi_Receive_(dev->u_spi, data, size, SPI_TIMEOUT);
	meGpio_Set_(dev->u_cs);
  
  return 0;  
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Write(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data) {
  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);
  
  sCdrvMR25H40_Obj *dev = (sCdrvMR25H40_Obj*)me->device;
  
  if(size  == 0) {
    return 1;
  }
  
  if((address + size) > (me->u_start_address + me->u_size)) {
    return 1;
  }
  
  address += me->u_start_address;
  
  dev->tmp_buffer[0] = MR25H40CDC_WRITE;
	dev->tmp_buffer[1] = address >> 16;
	dev->tmp_buffer[2] = address >> 8;
	dev->tmp_buffer[3] = address;
	
  meGpio_Reset_(dev->u_cs);
  meSpi_Transmit_(dev->u_spi, dev->tmp_buffer, 4, SPI_TIMEOUT);
	meSpi_Transmit_(dev->u_spi, data, size, SPI_TIMEOUT);
  meGpio_Set_(dev->u_cs);
	
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Verify(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data) {
  meCHECK_INIT_(eME_RESULT_ERROR_INIT);
  meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);
  
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

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/
