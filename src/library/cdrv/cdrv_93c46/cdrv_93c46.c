/**
 ******************************************************************************
 *  @file         cdrv_93c46.c
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
#include "cdrv_93c46.h"

#include "library\memory\me_memory_test.h"
#include <stdlib.h>

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
enum OP { // Operations
	WRITE 		= 0x40,
	READ 		= 0x80, 
	ERASE 		= 0xC0
};

enum CC { // Control Codes
	EW_DISABLE 	= 0x00, 
	WRITE_ALL 	= 0x10, 
	ERASE_ALL 	= 0x20, 
	EW_ENABLE 	= 0x30
};


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t Init(TysMemory_Obj * const me);
static uint8_t Erase(TysMemory_Obj * const me, uint32_t address, uint32_t size);
static uint8_t Erase_all(TysMemory_Obj * const me);
static uint8_t Read(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data);
static uint8_t Write(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data);
static uint8_t Verify(TysMemory_Obj * const me, uint32_t address, uint32_t size, uint8_t *data);

static void ew_enable(TysCdrv93C46_Obj * const me);
static void ew_disable(TysCdrv93C46_Obj * const me);
//static void erase_all(TysCdrv93C46_Obj * const me);
//static void write_all(TysCdrv93C46_Obj * const me, uint16_t value);
static void write(TysCdrv93C46_Obj * const me, uint8_t addr, uint16_t value);
static void erase(TysCdrv93C46_Obj * const me, uint8_t addr);
static uint16_t read(TysCdrv93C46_Obj * const me, uint8_t addr);
static void send_bits(TysCdrv93C46_Obj * const me, uint16_t value, uint16_t len);
static void wait(TysCdrv93C46_Obj * const me);
  
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
uint8_t Cdrv93C46_Init(TysCdrv93C46_Obj * const me, TyeCdrv93C46_Mode mode) {
  
  me->init = false;
  
  if((me->u_cs == NULL) || (me->u_di == NULL) || (me->u_do == NULL) || (me->u_clk == NULL)) {
    return 1;
  }
  
  me->mode = mode;
  
  me->init = true;
  me->u_enable = true;
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
TysMemory_Obj* Cdrv93C46_CreatePartirion(TysCdrv93C46_Obj * const me, uint32_t start_addr, uint32_t size) {
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
  
  if((start_addr + size) > Cdrv93C46_GetSize(me)) {
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
uint32_t Cdrv93C46_GetSize (TysCdrv93C46_Obj * const me) {
  meCHECK_INIT_(NULL);
  meCHECK_ENABLE_(NULL);
  
  return 128;
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
  
  if(meMemoryTest_8Bit_NonDestruvtive_Connection(me) != 0) {
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
  
  TysCdrv93C46_Obj *dev = (TysCdrv93C46_Obj*)me->device;
  
  if(size  == 0) {
    return 1;
  }
  
  if((address + size) > (me->u_start_address + me->u_size)) {
    return 1;
  }
  
  address += me->u_start_address;
  
  for(uint32_t i=0; i<size; i++) {
    erase(dev, address + i);
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
  
  TysCdrv93C46_Obj *dev = (TysCdrv93C46_Obj*)me->device;
  
  if(size  == 0) {
    return 1;
  }
  
  if((address + size) > (me->u_start_address + me->u_size)) {
    return 1;
  }
  
  address += me->u_start_address;
  
  for(uint32_t i=0; i<size; i++) {
    data[i] = read(dev, address + i);
  }
  
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
  
  TysCdrv93C46_Obj *dev = (TysCdrv93C46_Obj*)me->device;
  
  if(size  == 0) {
    return 1;
  }
  
  if((address + size) > (me->u_start_address + me->u_size)) {
    return 1;
  }
  
  address += me->u_start_address;
  
  for(uint32_t i=0; i<size; i++) {
    
    write(dev, address + i, data[i]);
  }
  
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

///////////////////
static void ew_enable(TysCdrv93C46_Obj * const me) {
	
  meGpio_Set_(me->u_cs);
  
  send_bits(me, 1, 1);
	if(me->mode == e93C46_MODE_16BIT) {
		send_bits(me, EW_ENABLE, 8);
	} else {
		send_bits(me, EW_ENABLE<<1, 9);
	}
	meGpio_Reset_(me->u_cs);
	me->ew = true;
};

static void ew_disable(TysCdrv93C46_Obj * const me) {
	
  meGpio_Set_(me->u_cs);
	send_bits(me, 1, 1);
	if(me->mode == e93C46_MODE_16BIT) {
		send_bits(me, EW_DISABLE, 8);
	} else {
		send_bits(me, EW_DISABLE<<1, 9);
	}
	meGpio_Reset_(me->u_cs);
	me->ew = false;
}

//static void erase_all(TysCdrv93C46_Obj * const me) {
//	
//  if(me->ew == false) {
//		return;
//	}
//	meGpio_Set_(me->u_cs);
//	send_bits(me, 1, 1);
//	if(me->mode == e93C46_MODE_16BIT) {
//		send_bits(me, ERASE_ALL, 8);
//	} else {
//		send_bits(me, ERASE_ALL<<1, 9);
//	}
//	meGpio_Reset_(me->u_cs);
//	wait(me);
//}

//static void write_all(TysCdrv93C46_Obj * const me, uint16_t value) {
//	
//  if(me->ew == false) {
//		return;
//	}
//  meGpio_Set_(me->u_cs);
//	send_bits(me, 1, 1);
//	if(me->mode == e93C46_MODE_16BIT) {
//		send_bits(me, WRITE_ALL, 8);
//		send_bits(me, 0xFFFF & value, 16);
//	} else {
//		send_bits(me, WRITE_ALL<<1, 9);
//		send_bits(me, 0xFF & value, 8);
//	}
//	meGpio_Reset_(me->u_cs);
//	wait(me);
//}

static void write(TysCdrv93C46_Obj * const me, uint8_t addr, uint16_t value) {
  
  ew_enable(me);
	
  if(me->ew == false) {
		return;
	}
	meGpio_Set_(me->u_cs);
	send_bits(me, 1, 1);
	if(me->mode == e93C46_MODE_16BIT) {
		send_bits(me, WRITE | (addr & 0x3F), 8);
		send_bits(me, 0xFFFF & value, 16);
	} else {
		send_bits(me, WRITE<<1 | (addr & 0x7F), 9);
		send_bits(me, 0xFF & value, 8);
	}
	meGpio_Reset_(me->u_cs);
	wait(me);
  
  ew_disable(me);
}

static void erase(TysCdrv93C46_Obj * const me, uint8_t addr) {
	
  if(me->ew == false) {
		return;
	}
	meGpio_Set_(me->u_cs);
	send_bits(me, 1, 1);
	if(me->mode == e93C46_MODE_16BIT) {
		send_bits(me, ERASE | (addr & 0x3F), 8);
	} else {
		send_bits(me, ERASE<<1 | (addr & 0x7F), 9);
	}
	
	meGpio_Reset_(me->u_cs);
	wait(me);
}

static uint16_t read(TysCdrv93C46_Obj * const me, uint8_t addr) {
	
  uint16_t val = 0;
	meGpio_Set_(me->u_cs);
	send_bits(me, 1, 1);
	
	int amtBits;
	if(me->mode == e93C46_MODE_16BIT) {
		send_bits(me, READ | (addr & 0x3F), 8);
		amtBits = 16;
	} else {
		send_bits(me, READ<<1 | (addr & 0x7F), 9);
		amtBits = 8;
	}
	// Read bits
	for(int i = amtBits; i>0; i--) {
		meDelay_us_(2);
    meGpio_Write_(me->u_clk, 1);
		meDelay_us_(2);
    
    uint8_t in = 0;
    meGpio_Read_(me->u_do, &in);
		meGpio_Write_(me->u_clk, 0);
		val |= (in << (i-1));
	}
	meGpio_Reset_(me->u_cs);
	return val;
}

static void send_bits(TysCdrv93C46_Obj * const me, uint16_t value, uint16_t len) {
	
  for(int i = len-1; i>=0; i--)
	{
		bool toSend = (value & 1<<i);
		// Send bit
    meGpio_Write_(me->u_di, toSend);
		meDelay_us_(2);
		meGpio_Write_(me->u_clk, 1);
		meDelay_us_(2);
		meGpio_Write_(me->u_clk, 0);
		meGpio_Write_(me->u_di, 0);
	}
}

static void wait(TysCdrv93C46_Obj * const me) {
  
	meDelay_us_(2);
	meGpio_Set_(me->u_cs);
  
  uint8_t tmp = 0;
	while(tmp == 0) {
		meDelay_us_(1);
    
    meGpio_Read_(me->u_do, &tmp);
	}
	meGpio_Reset_(me->u_cs);
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/
