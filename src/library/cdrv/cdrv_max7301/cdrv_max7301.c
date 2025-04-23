/**
 ******************************************************************************
 *  @file         cdrv_max7301.c
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
#include "cdrv_max7301.h"

#include <stdlib.h>

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define CTOR_(pin_obj_, pin_no_) \
  do{\
    me->privates.pin_obj_.parent = me;\
    me->privates.pin_obj_.pin_no = pin_no_;\
    Gpio_ctor(&me->u_pins.pin_obj_, &me->privates.pin_obj_);\
  }while(0)

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t Init(TysGpio_Obj * const me);
static void Run(TysGpio_Obj * const me);
static uint8_t Set(TysGpio_Obj * const me);
static uint8_t Reset(TysGpio_Obj * const me);
static uint8_t Toggle(TysGpio_Obj * const me);
static uint8_t Write(TysGpio_Obj * const me, uint8_t val);
static uint8_t Clock(TysGpio_Obj * const me);
static uint8_t Const(TysGpio_Obj * const me);
static uint8_t Read(TysGpio_Obj * const me, uint8_t *val);
static uint8_t Output(TysGpio_Obj * const me);
static uint8_t Input(TysGpio_Obj * const me);
static uint8_t Event_Edge_Config(TysGpio_Obj * const me, TyeEdge_Event edge, void(*func)(TyeEdge_Event));
static uint8_t Event_Edge_Enable(TysGpio_Obj * const me);
static uint8_t Event_Edge_Disable(TysGpio_Obj * const me);

static void Gpio_ctor(TysGpio_Obj * const me, void * const private_);

static uint8_t ReadRegister(TysCdrvMax7301_Obj *me, uint8_t address);
static void WriteRegister(TysCdrvMax7301_Obj *me, uint8_t address, uint8_t data);
	
//static uint8_t ReadPortDirection(TysCdrvMax7301_Obj * const me);
//static uint8_t WritePortDirection(TysCdrvMax7301_Obj * const me);
static uint8_t SetDirection(TysCdrvMax7301_Obj * const me, uint8_t pin_no, TyeGpio_Dir direction);

//static uint8_t ReadPortStatus(TysCdrvMax7301_Obj * const me);
static uint8_t ReadPinStatus(TysCdrvMax7301_Obj * const me, uint8_t pin_no, uint8_t *status);

//static uint8_t WritePortStatus(TysCdrvMax7301_Obj * const me);
static uint8_t WritePinStatus(TysCdrvMax7301_Obj * const me, uint8_t pin_no, uint8_t status);

//static uint8_t TogglePinStatus(TysCdrvMax7301_Obj * const me, uint8_t pin_no);

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
uint8_t CdrvMax7301_Init(TysCdrvMax7301_Obj * const me) {
  
  me->init = false;
  
  if((me->u_cs == NULL) || (me->u_spi == NULL)) {
    return 1;
  }
	
	me->u_cs->u_dir = eGPIO_DIR_OUTPUT;
	me->u_cs->u_out_type = eGPIO_PUSH_PULL;
	if(meGpio_Init_(me->u_cs) != 0) {
		return 1;
	}
	meGpio_Set_(me->u_cs);
	
	me->u_spi->u_bit_order = eSPI_FIRSTBIT_MSB;
	me->u_spi->u_data_size = 8;
	me->u_spi->u_mode = eSPI_MODE_0;
	me->u_spi->u_role = eSPI_ROLE_MASTER;
	if(meSpi_Init_(me->u_spi) != 0) {
		return 1;
	}
  
  CTOR_(p4, 4);
	CTOR_(p5, 5);
	CTOR_(p6, 6);
	CTOR_(p7, 7);
	CTOR_(p8, 8);
	CTOR_(p9, 9);
	CTOR_(p10, 10);
	CTOR_(p11, 11);
	CTOR_(p12, 12);
	CTOR_(p13, 13);
	CTOR_(p14, 14);
	CTOR_(p15, 15);
	CTOR_(p16, 16);
	CTOR_(p17, 17);
	CTOR_(p18, 18);
	CTOR_(p19, 19);
	CTOR_(p20, 20);
	CTOR_(p21, 21);
	CTOR_(p22, 22);
	CTOR_(p23, 23);
	CTOR_(p24, 24);
	CTOR_(p25, 25);
	CTOR_(p26, 26);
	CTOR_(p27, 27);
	CTOR_(p28, 28);
	CTOR_(p29, 29);
	CTOR_(p30, 30);
	CTOR_(p31, 31);
	
	WriteRegister(me, 0x04, 0x01);
  
  me->init = true;
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t CdrvMax7301_SyncUpdate(TysCdrvMax7301_Obj * const me) {
  
  if(me->u_online == true) {
    return 0;
  }
  
//  if(WritePortStatus(me) != 0) {  
//    return 1;
//  }
//  
//  if(ReadPortStatus(me) != 0) {  
//    return 1;
//  }
  
  return 0;
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
static uint8_t Init(TysGpio_Obj * const me) {
  
  TysHalGpioPrivate *pvt = (TysHalGpioPrivate*)me->private_;
  
  me->init = false;
  
  if((me->u_dir != eGPIO_DIR_INPUT) && (me->u_dir != eGPIO_DIR_OUTPUT)) {
    return 1;
  }
  
  if(SetDirection(pvt->parent, pvt->pin_no, me->u_dir) != 0) {
    return 1;
  }
  
  me->init = true;
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static void Run(TysGpio_Obj * const me) {
  
//	switch(me->mode) {
//
//    case eGPIO_MODE_CONST: {
//
//      break;
//    }
//
//    case eGPIO_MODE_CLOCK: {
//
//      switch(me->val) {
//
//        case 0: {
//
//          if(meChrono_us_IsTimedOut(&me->chrono) == true) {
//
//            meGpio_Set_(me);
//
//            meChrono_StartTimeout_(&me->chrono, me->u_time_set_us);
//          }
//          break;
//        }
//
//        case 1: {
//
//          if(meChrono_us_IsTimedOut(&me->chrono) == true) {
//
//            meGpio_Reset_(me);
//
//            meChrono_StartTimeout_(&me->chrono, me->u_time_reset_us);
//          }
//          break;
//        }
//      }
//      break;
//    }
//  }
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Set(TysGpio_Obj * const me) {
  
  TysHalGpioPrivate *pvt = (TysHalGpioPrivate*)me->private_;
  
  uint8_t val = 1;
  
  if(me->u_invert == true) {
    val = 0;
  }
  
  if(WritePinStatus(pvt->parent, pvt->pin_no, val) != 0) {
    return 1;
  }
  
  me->val = 1;
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Reset(TysGpio_Obj * const me) {
  
  TysHalGpioPrivate *pvt = (TysHalGpioPrivate*)me->private_;
  
  uint8_t val = 0;
  if(me->u_invert == true) {
    val = 1;
  }
  
  if(WritePinStatus(pvt->parent, pvt->pin_no, val) != 0) {
    return 1;
  }
  
  me->val = 0;
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Toggle(TysGpio_Obj * const me) {

  uint8_t val = 0;
  Read(me, &val);
  if(val) {
    Reset(me);
  } else {
    Set(me);
  }
  
//  TysHalGpioPrivate *pvt = (TysHalGpioPrivate*)me->private_;
//  
//  if(TogglePinStatus(pvt->parent, pvt->pin_no) != 0) {
//    return 1;
//  }
//  
//  if(me->val == 1) {
//    me->val = 0;
//  } else {
//    me->val = 1;
//  }
//  
//  return 0;
	return 1;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Write(TysGpio_Obj * const me, uint8_t val) {
  
  //uint8_t tmp = val;
  
  TysHalGpioPrivate *pvt = (TysHalGpioPrivate*)me->private_;
  
  if(me->u_invert == true) {
    val = !val;
  }
  
  if(WritePinStatus(pvt->parent, pvt->pin_no, val) != 0) {
    return 1;
  }
  
  me->val = val;
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static uint8_t Clock(TysGpio_Obj * const me) {
  
	meCHECK_INIT_(eME_RESULT_ERROR_INIT);
	meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);
	
  meGpio_Reset_(me);
//  meChrono_StartTimeout_(&(me->chrono), me->u_time_reset_us);
  me->mode = eGPIO_MODE_CLOCK;
	
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static uint8_t Const(TysGpio_Obj * const me) {
  
	meCHECK_INIT_(eME_RESULT_ERROR_INIT);
	meCHECK_ENABLE_(eME_RESULT_ERROR_ENABLE);
	
  me->mode = eGPIO_MODE_CONST;
	
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Read(TysGpio_Obj * const me, uint8_t *val) {
  
  TysHalGpioPrivate *pvt = (TysHalGpioPrivate*)me->private_;
  
  ReadPinStatus(pvt->parent, pvt->pin_no, val);
  
  switch(me->u_dir) {
    
    case eGPIO_DIR_INPUT: {
      if(me->u_invert == true) {
        *val = !(*val);
      }
      break;
    }
    
    case eGPIO_DIR_OUTPUT: {
      if(me->u_invert == true) {
        *val = !(*val);
      }
      break;
    }
  }
  
  me->val = *val;
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Output(TysGpio_Obj * const me) {
  
  TysHalGpioPrivate *pvt = (TysHalGpioPrivate*)me->private_;
  
  if(SetDirection(pvt->parent, pvt->pin_no, eGPIO_DIR_OUTPUT) != 0) {
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
static uint8_t Input(TysGpio_Obj * const me) {
  
  TysHalGpioPrivate *pvt = (TysHalGpioPrivate*)me->private_;
  
  if(SetDirection(pvt->parent, pvt->pin_no, eGPIO_DIR_INPUT) != 0) {
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
static uint8_t Event_Edge_Config(TysGpio_Obj * const me, TyeEdge_Event edge, void(*func)(TyeEdge_Event)) {
  
  return 1;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Event_Edge_Enable(TysGpio_Obj * const me) {
  
  return 1;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t Event_Edge_Disable(TysGpio_Obj * const me) {
  
  return 1;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static void Gpio_ctor(TysGpio_Obj * const me, void * const private_) {
  static struct TysGpioVtbl const vtbl = {
    Init,
    Run,
    Set,
    Reset,
    Toggle,
    Write,
    Clock,
    Const,
    Read,
    Output,
    Input,
    Event_Edge_Config,
    Event_Edge_Enable,
    Event_Edge_Disable
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
  
  me->u_dir = eGPIO_DIR_INPUT;
  me->u_in_type = eGPIO_PULL_NONE;
  me->u_out_type = eGPIO_PUSH_PULL;
  me->val = 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
//static uint8_t SetPortPullUp(TysCdrvMax7301_Obj * const me, uint16_t status) {
//  
//  uint8_t tmp[4];
//  
//  tmp[0] = MCP23S18WRADDR;
//  tmp[1] = GPPUA_BANK0;
//  tmp[2] = 0x000000FF & status;
//  tmp[3] = 0x000000FF & (status >> 8);
//  
//  meGpio_Reset_(me->u_cs);
//  if(meSpi_Transmit_(me->u_spi, tmp, 4, 10000) != 0) {
//    meGpio_Set_(me->u_cs);
//    return 1;
//  }
//  meGpio_Set_(me->u_cs);
//  
//  return 0;
//}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
//static uint8_t ReadPortDirection(TysCdrvMax7301_Obj * const me) {
//  
////  uint8_t tx_tmp[4];
////  uint8_t rx_tmp[4];
////  
////  tx_tmp[0] = MCP23S18RDADDR;
////  tx_tmp[1] = IODIRA_BANK0;
////  tx_tmp[2] = IODIRB_BANK0;
////  tx_tmp[3] = IODIRA_BANK0;
////  
////  meGpio_Reset_(me->u_cs);
////  if(meSpi_TransmitReceive_(me->u_spi, tx_tmp, rx_tmp, 4, 10000) != 0) {
////    meGpio_Set_(me->u_cs);
////    return 1;
////  }
////  meGpio_Set_(me->u_cs);
////  
////  me->direction = (uint16_t)rx_tmp[2] | ((uint16_t)rx_tmp[3] << 8);
////  
////  return 0;
//	
//	return 1;
//}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
//static uint8_t WritePortDirection(TysCdrvMax7301_Obj * const me) {
//  
////  uint8_t tmp[3];
////  
////  tmp[0] = MCP23S18WRADDR;
////  tmp[1] = IODIRA_BANK0;
////  tmp[2] = 0x000000FF & me->direction;
////  
////  meGpio_Reset_(me->u_cs);
////  if(meSpi_Transmit_(me->u_spi, tmp, 3, 10000) != 0) {
////    meGpio_Set_(me->u_cs);
////    return 1;
////  }
////  meGpio_Set_(me->u_cs);
////  
////  tmp[0] = MCP23S18WRADDR;
////  tmp[1] = IODIRB_BANK0;
////  tmp[2] = 0x000000FF & (me->direction >> 8);
////  
////  meGpio_Reset_(me->u_cs);
////  if(meSpi_Transmit_(me->u_spi, tmp, 3, 10000) != 0) {
////    meGpio_Set_(me->u_cs);
////    return 1;
////  }
////  meGpio_Set_(me->u_cs);
////  
////  return 0;

//	return 1;
//}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static uint8_t SetDirection(TysCdrvMax7301_Obj * const me, uint8_t pin_no, TyeGpio_Dir direction) {
  
  if((pin_no > 31) || (pin_no < 4)) {
    return 1;
  }
	
	uint8_t reg = (pin_no / 4) + 0x08;
  uint8_t offset = 2 * (pin_no % 4);
	
	uint8_t mode = 0;
	switch(direction) {
		case eGPIO_DIR_INPUT: {
			mode = 0x02;
			break;
		}
		case eGPIO_DIR_OUTPUT: {
			mode = 0x01;
			break;
		}
	}
	
  WriteRegister(me, reg, (ReadRegister(me, reg) & ~(0x03 << offset)) | (mode << offset));
  
//  //read port direction
//  if(ReadPortDirection(me) != 0) {
//    return 1;
//  }
//  
//  //change desired pin direction
//  switch(direction) {
//    case eGPIO_DIR_INPUT: {
//      meUINT_SET_BIT_(uint16_t, me->direction, pin_no);
//      break;
//    }
//    
//    case eGPIO_DIR_OUTPUT: {
//      meUINT_RESET_BIT_(uint16_t, me->direction, pin_no);
//      break;
//    }
//    
//    default: {
//      return 1;
//    }
//  }
//  
//  //write port direction
//  if(WritePortDirection(me) != 0) {
//    return 1;
//  }
  
  return 0;
}

///**
//  * @brief
//  * @note  
//  * @param  
//  * @retval
//*/
//static uint8_t ReadPortStatus(TysCdrvMax7301_Obj * const me) {
//  
////  uint8_t tx_tmp[4];
////  uint8_t rx_tmp[4];
////  
////  tx_tmp[0] = MCP23S18RDADDR;
////  tx_tmp[1] = GPIOA_BANK0;
////  tx_tmp[2] = GPIOB_BANK0;
////  tx_tmp[3] = GPIOA_BANK0;
////  
////  meGpio_Reset_(me->u_cs);
////  if(meSpi_TransmitReceive_(me->u_spi, tx_tmp, rx_tmp, 4, 10000) != 0) {
////    meGpio_Set_(me->u_cs);
////    return 1;
////  }
////  meGpio_Set_(me->u_cs);
////  
////  me->read_value = (uint16_t)rx_tmp[2] | ((uint16_t)rx_tmp[3] << 8);
////  
////  return 0;
//	
//	return 1;
//}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static uint8_t ReadPinStatus(TysCdrvMax7301_Obj * const me, uint8_t pin_no, uint8_t *status) {
  
  if((pin_no > 31) || (pin_no < 4)) {
    return 1;
  }
	
	*status = ReadRegister(me, pin_no + 0x20);
	
	return 0;
  
//  if(me->u_online == true) {
//    
//    //read port status
//    if(ReadPortStatus(me) != 0) {
//      return 1;
//    }
//  }
//  
//  *status = meUINT_BIT_(uint16_t, me->read_value, pin_no);
//  
//  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
//static uint8_t WritePortStatus(TysCdrvMax7301_Obj * const me) {
//  
////  uint8_t tmp[10];
////  
////  tmp[0] = MCP23S18WRADDR;
////  tmp[1] = OLATA_BANK0;
////  tmp[2] = 0x000000FF & me->write_value;
////  
////  meGpio_Reset_(me->u_cs);
////  if(meSpi_Transmit_(me->u_spi, tmp, 3, 10000) != 0) {
////    meGpio_Set_(me->u_cs);
////    return 1;
////  }
////  meGpio_Set_(me->u_cs);
////  
////  tmp[0] = MCP23S18WRADDR;
////  tmp[1] = OLATB_BANK0;
////  tmp[2] = 0x000000FF & (me->write_value >> 8);
////  
////  meGpio_Reset_(me->u_cs);
////  if(meSpi_Transmit_(me->u_spi, tmp, 3, 10000) != 0) {
////    meGpio_Set_(me->u_cs);
////    return 1;
////  }
////  meGpio_Set_(me->u_cs);
////  
////  return 0;

//	return 1;
//}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static uint8_t WritePinStatus(TysCdrvMax7301_Obj * const me, uint8_t pin_no, uint8_t status) {
  
  if((pin_no > 31) || (pin_no < 4)) {
    return 1;
  }
	
	WriteRegister(me, pin_no + 0x20, status);
	
//  if(me->u_online == true) {
//    
//    //read port status
//    if(ReadPortStatus(me) != 0) {
//      return 1;
//    }
//  }
  
  //change desired pin status
//  if(status == 0) {
//    meUINT_RESET_BIT_(uint16_t, me->write_value, pin_no);
//  } else {
//    meUINT_SET_BIT_(uint16_t, me->write_value, pin_no);
//  }
//  
//  if(me->u_online == true) {
//    
//    //write port status
//    if(WritePortStatus(me) != 0) {
//      return 1;
//    }
//  }
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
//static uint8_t TogglePinStatus(TysCdrvMax7301_Obj * const me, uint8_t pin_no) {
//  
//  if(pin_no > 15) {
//    return 1;
//  }
//  
////  if(me->u_online == true) {
////  
////    //read port status
////    if(ReadPortStatus(me) != 0) {
////      return 1;
////    }
////  }
//  
//  //toggle desired pin status
//  uint8_t b = meUINT_BIT_(uint16_t, me->write_value, pin_no);
//  if(b == 0) {
//    meUINT_SET_BIT_(uint16_t, me->write_value, pin_no);
//  } else {
//    meUINT_RESET_BIT_(uint16_t, me->write_value, pin_no);
//  }
//  
//  if(me->u_online == true) {
//  
//    //write port status
//    if(WritePortStatus(me) != 0) {
//      return 1;
//    }
//  }
//  
//  return 0;
//}

static uint8_t ReadRegister(TysCdrvMax7301_Obj *me, uint8_t address) {
  
	uint8_t tx[2];
	uint8_t rx[2];

	meGpio_Reset_(me->u_cs);
  
	tx[0] = address | 0x80;
	tx[1] = 0x00;
	meSpi_Transmit_(me->u_spi, tx, 2, 1000);
  
	meGpio_Set_(me->u_cs);

  meGpio_Reset_(me->u_cs);
	
	meSpi_Receive_(me->u_spi, rx, 2, 1000);
  
	meGpio_Set_(me->u_cs);

  return rx[1];
}

static void WriteRegister(TysCdrvMax7301_Obj *me, uint8_t address, uint8_t data) { 
	
  meGpio_Reset_(me->u_cs);
	
	uint8_t tx[2];
	tx[0] = address & ~0x80;
	tx[1] = data;
  meSpi_Transmit_(me->u_spi, tx, 2, 1000);
	
  meGpio_Set_(me->u_cs);
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/
