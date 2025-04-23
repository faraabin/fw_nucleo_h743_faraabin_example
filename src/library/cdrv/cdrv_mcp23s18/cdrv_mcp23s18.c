/**
 ******************************************************************************
 *  @file         cdrv_mcp23s18.c
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
#include "cdrv_mcp23s18.h"

#include <stdlib.h>

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MCP23S18WRADDR      0x40
#define MCP23S18RDADDR      0x41
 
#define IODIRA_BANK1        0x00
#define IODIRB_BANK1        0x10
#define IPOLA_BANK1         0x01
#define IPOLB_BANK1         0x11
#define GPINTENA_BANK1      0x02
#define GPINTENB_BANK1      0x12
#define DEFVALA_BANK1       0x03
#define DEFVALB_BANK1       0x13
#define INTCONA_BANK1       0x04
#define INTCONB_BANK1       0x14
#define IOCONA_BANK1        0x05
#define IOCONB_BANK1        0x15
#define GPPUA_BANK1         0x06
#define GPPUB_BANK1         0x16
#define INTFA_BANK1         0x07
#define INTFB_BANK1         0x17
#define INTCAPA_BANK1       0x08
#define INTCAPB_BANK1       0x18
#define GPIOA_BANK1         0x09
#define GPIOB_BANK1         0x19
#define OLATA_BANK1         0x0A
#define OLATB_BANK1         0x1A
 
// If you set IOCON.BANK = 1 then all
// the registers are set sequentially
// We will use this method to address
// the registers since it hurts my head less :)
 
#define IODIRA_BANK0        0x00
#define IODIRB_BANK0        0x01
#define IPOLA_BANK0         0x02
#define IPOLB_BANK0         0x03
#define GPINTENA_BANK0      0x04
#define GPINTENB_BANK0      0x05
#define DEFVALA_BANK0       0x06
#define DEFVALB_BANK0       0x07
#define INTCONA_BANK0       0x08
#define INTCONB_BANK0       0x09
#define IOCONA_BANK0        0x0A
#define IOCONB_BANK0        0x0B
#define GPPUA_BANK0         0x0C
#define GPPUB_BANK0         0x0D
#define INTFA_BANK0         0x0E
#define INTFB_BANK0         0x0F
#define INTCAPA_BANK0       0x10
#define INTCAPB_BANK0       0x11
#define GPIOA_BANK0         0x12
#define GPIOB_BANK0         0x13
#define OLATA_BANK0         0x14
#define OLATB_BANK0         0x15
 
#define IODIRn_IO0          (1<<0)
#define IODIRn_IO1          (1<<1)
#define IODIRn_IO2          (1<<2)
#define IODIRn_IO3          (1<<3)
#define IODIRn_IO4          (1<<4)
#define IODIRn_IO5          (1<<5)
#define IODIRn_IO6          (1<<6)
#define IODIRn_IO7          (1<<7)
 
#define IPOLn_IP0           (1<<0)
#define IPOLn_IP1           (1<<1)
#define IPOLn_IP2           (1<<2)
#define IPOLn_IP3           (1<<3)
#define IPOLn_IP4           (1<<4)
#define IPOLn_IP5           (1<<5)
#define IPOLn_IP6           (1<<6)
#define IPOLn_IP7           (1<<7)
 
#define GPINTENn_GPINT0     (1<<0)
#define GPINTENn_GPINT1     (1<<1)
#define GPINTENn_GPINT2     (1<<2)
#define GPINTENn_GPINT3     (1<<3)
#define GPINTENn_GPINT4     (1<<4)
#define GPINTENn_GPINT5     (1<<5)
#define GPINTENn_GPINT6     (1<<6)
#define GPINTENn_GPINT7     (1<<7)
 
#define DEFVALn_DEF0        (1<<0)
#define DEFVALn_DEF1        (1<<1)
#define DEFVALn_DEF2        (1<<2)
#define DEFVALn_DEF3        (1<<3)
#define DEFVALn_DEF4        (1<<4)
#define DEFVALn_DEF5        (1<<5)
#define DEFVALn_DEF6        (1<<6)
#define DEFVALn_DEF7        (1<<7)
 
#define INTCONn_IOC0        (1<<0)
#define INTCONn_IOC1        (1<<1)
#define INTCONn_IOC2        (1<<2)
#define INTCONn_IOC3        (1<<3)
#define INTCONn_IOC4        (1<<4)
#define INTCONn_IOC5        (1<<5)
#define INTCONn_IOC6        (1<<6)
#define INTCONn_IOC7        (1<<7)
 
#define IOCON_INTCC         (1<<0)
#define IOCON_INTPOL        (1<<1)
#define IOCON_ODR           (1<<2)
#define IOCON_RSVD0         (1<<3)
#define IOCON_RSVD1         (1<<4)
#define IOCON_SEQOP         (1<<5)
#define IOCON_MIRROR        (1<<6)
#define IOCON_BANK          (1<<7)
#define IOX_ALLOUTPUT       0x00000000
#define IOX_ALLINPUT        0xFFFFFFFF 
#define IOX_ALLINVERTED     0x00000000
#define IOX_NONEINVERTED    0xFFFFFFFF

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

//static uint8_t SetPortPullUp(TysCdrvMcp23s18_Obj * const me, uint16_t status);
static uint8_t ReadPortDirection(TysCdrvMcp23s18_Obj * const me);
static uint8_t WritePortDirection(TysCdrvMcp23s18_Obj * const me);
static uint8_t SetDirection(TysCdrvMcp23s18_Obj * const me, uint8_t pin_no, TyeGpio_Dir direction);

static uint8_t ReadPortStatus(TysCdrvMcp23s18_Obj * const me);
static uint8_t ReadPinStatus(TysCdrvMcp23s18_Obj * const me, uint8_t pin_no, uint8_t *status);

static uint8_t WritePortStatus(TysCdrvMcp23s18_Obj * const me);
static uint8_t WritePinStatus(TysCdrvMcp23s18_Obj * const me, uint8_t pin_no, uint8_t status);

static uint8_t TogglePinStatus(TysCdrvMcp23s18_Obj * const me, uint8_t pin_no);

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
uint8_t CdrvMcp23s18_Init(TysCdrvMcp23s18_Obj * const me) {
  
  me->init = false;
  
  if((me->u_cs == NULL) || (me->u_spi == NULL)) {
    return 1;
  }
  
  uint8_t tmp[10];
  
  tmp[0] = MCP23S18WRADDR;
  tmp[1] = IOCONA_BANK0;
  tmp[2] = IOCON_MIRROR|IOCON_SEQOP;
  
  meGpio_Reset_(me->u_cs);
  meSpi_Transmit_(me->u_spi, tmp, 3, 10000);
  meGpio_Set_(me->u_cs);
  
  tmp[0] = MCP23S18RDADDR;
  tmp[1] = IOCONA_BANK0;
  tmp[2] = IOCONA_BANK0;
  
  meGpio_Reset_(me->u_cs);
  meSpi_Transmit_(me->u_spi, tmp, 3, 10000);
  meGpio_Set_(me->u_cs);
  
  CTOR_(gpa0, 0);
  CTOR_(gpa1, 1);
  CTOR_(gpa2, 2);
  CTOR_(gpa3, 3);
  CTOR_(gpa4, 4);
  CTOR_(gpa5, 5);
  CTOR_(gpa6, 6);
  CTOR_(gpa7, 7);
  
  CTOR_(gpb0, 8);
  CTOR_(gpb1, 9);
  CTOR_(gpb2, 10);
  CTOR_(gpb3, 11);
  CTOR_(gpb4, 12);
  CTOR_(gpb5, 13);
  CTOR_(gpb6, 14);
  CTOR_(gpb7, 15);
  
  me->init = true;
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t CdrvMcp23s18_SyncUpdate(TysCdrvMcp23s18_Obj * const me) {
  
  if(me->u_online == true) {
    return 0;
  }
  
  if(WritePortStatus(me) != 0) {  
    return 1;
  }
  
  if(ReadPortStatus(me) != 0) {  
    return 1;
  }
  
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
  
	switch(me->mode) {
    
    case eGPIO_MODE_CONST: {
      
      break;
    }

    case eGPIO_MODE_CLOCK: {
      
      switch(me->val) {
        
        case 0: {
          
          if(meChrono_us_IsTimedOut(&me->chrono) == true) {
            
            meGpio_Set_(me);
            
            meChrono_StartTimeout_(&me->chrono, me->u_time_set_us);
          }
          break;
        }

        case 1: {
          
          if(meChrono_us_IsTimedOut(&me->chrono) == true) {
            
            meGpio_Reset_(me);
                        
            meChrono_StartTimeout_(&me->chrono, me->u_time_reset_us);
          }          
          break;
        }
      }
      break;
    }
  }
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
  
  TysHalGpioPrivate *pvt = (TysHalGpioPrivate*)me->private_;
  
  if(TogglePinStatus(pvt->parent, pvt->pin_no) != 0) {
    return 1;
  }
  
  if(me->val == 1) {
    me->val = 0;
  } else {
    me->val = 1;
  }
  
  return 0;
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
  meChrono_StartTimeout_(&(me->chrono), me->u_time_reset_us);
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
  
  if(ReadPinStatus(pvt->parent, pvt->pin_no, val) != 0) {
    return 1;
  }
  
  switch(me->u_dir) {
    
    case eGPIO_DIR_INPUT: {
      if(me->u_invert == true) {
        *val = !(*val);
      }
      break;
    }
    
    case eGPIO_DIR_OUTPUT: {
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
//static uint8_t SetPortPullUp(TysCdrvMcp23s18_Obj * const me, uint16_t status) {
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
static uint8_t ReadPortDirection(TysCdrvMcp23s18_Obj * const me) {
  
  uint8_t tx_tmp[4];
  uint8_t rx_tmp[4];
  
  tx_tmp[0] = MCP23S18RDADDR;
  tx_tmp[1] = IODIRA_BANK0;
  tx_tmp[2] = IODIRB_BANK0;
  tx_tmp[3] = IODIRA_BANK0;
  
  meGpio_Reset_(me->u_cs);
  if(meSpi_TransmitReceive_(me->u_spi, tx_tmp, rx_tmp, 4, 10000) != 0) {
    meGpio_Set_(me->u_cs);
    return 1;
  }
  meGpio_Set_(me->u_cs);
  
  me->direction = (uint16_t)rx_tmp[2] | ((uint16_t)rx_tmp[3] << 8);
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static uint8_t WritePortDirection(TysCdrvMcp23s18_Obj * const me) {
  
  uint8_t tmp[3];
  
  tmp[0] = MCP23S18WRADDR;
  tmp[1] = IODIRA_BANK0;
  tmp[2] = 0x000000FF & me->direction;
  
  meGpio_Reset_(me->u_cs);
  if(meSpi_Transmit_(me->u_spi, tmp, 3, 10000) != 0) {
    meGpio_Set_(me->u_cs);
    return 1;
  }
  meGpio_Set_(me->u_cs);
  
  tmp[0] = MCP23S18WRADDR;
  tmp[1] = IODIRB_BANK0;
  tmp[2] = 0x000000FF & (me->direction >> 8);
  
  meGpio_Reset_(me->u_cs);
  if(meSpi_Transmit_(me->u_spi, tmp, 3, 10000) != 0) {
    meGpio_Set_(me->u_cs);
    return 1;
  }
  meGpio_Set_(me->u_cs);
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static uint8_t SetDirection(TysCdrvMcp23s18_Obj * const me, uint8_t pin_no, TyeGpio_Dir direction) {
  
  if(pin_no > 15) {
    return 1;
  }
  
  //read port direction
  if(ReadPortDirection(me) != 0) {
    return 1;
  }
  
  //change desired pin direction
  switch(direction) {
    case eGPIO_DIR_INPUT: {
      meUINT_SET_BIT_(uint16_t, me->direction, pin_no);
      break;
    }
    
    case eGPIO_DIR_OUTPUT: {
      meUINT_RESET_BIT_(uint16_t, me->direction, pin_no);
      break;
    }
    
    default: {
      return 1;
    }
  }
  
  //write port direction
  if(WritePortDirection(me) != 0) {
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
static uint8_t ReadPortStatus(TysCdrvMcp23s18_Obj * const me) {
  
  uint8_t tx_tmp[4];
  uint8_t rx_tmp[4];
  
  tx_tmp[0] = MCP23S18RDADDR;
  tx_tmp[1] = GPIOA_BANK0;
  tx_tmp[2] = GPIOB_BANK0;
  tx_tmp[3] = GPIOA_BANK0;
  
  meGpio_Reset_(me->u_cs);
  if(meSpi_TransmitReceive_(me->u_spi, tx_tmp, rx_tmp, 4, 10000) != 0) {
    meGpio_Set_(me->u_cs);
    return 1;
  }
  meGpio_Set_(me->u_cs);
  
  me->read_value = (uint16_t)rx_tmp[2] | ((uint16_t)rx_tmp[3] << 8);
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static uint8_t ReadPinStatus(TysCdrvMcp23s18_Obj * const me, uint8_t pin_no, uint8_t *status) {
  
  if(pin_no > 15) {
    return 1;
  }
  
  if(me->u_online == true) {
    
    //read port status
    if(ReadPortStatus(me) != 0) {
      return 1;
    }
  }
  
  *status = meUINT_BIT_(uint16_t, me->read_value, pin_no);
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static uint8_t WritePortStatus(TysCdrvMcp23s18_Obj * const me) {
  
  uint8_t tmp[10];
  
  tmp[0] = MCP23S18WRADDR;
  tmp[1] = OLATA_BANK0;
  tmp[2] = 0x000000FF & me->write_value;
  
  meGpio_Reset_(me->u_cs);
  if(meSpi_Transmit_(me->u_spi, tmp, 3, 10000) != 0) {
    meGpio_Set_(me->u_cs);
    return 1;
  }
  meGpio_Set_(me->u_cs);
  
  tmp[0] = MCP23S18WRADDR;
  tmp[1] = OLATB_BANK0;
  tmp[2] = 0x000000FF & (me->write_value >> 8);
  
  meGpio_Reset_(me->u_cs);
  if(meSpi_Transmit_(me->u_spi, tmp, 3, 10000) != 0) {
    meGpio_Set_(me->u_cs);
    return 1;
  }
  meGpio_Set_(me->u_cs);
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static uint8_t WritePinStatus(TysCdrvMcp23s18_Obj * const me, uint8_t pin_no, uint8_t status) {
  
  if(pin_no > 15) {
    return 1;
  }
  
//  if(me->u_online == true) {
//    
//    //read port status
//    if(ReadPortStatus(me) != 0) {
//      return 1;
//    }
//  }
  
  //change desired pin status
  if(status == 0) {
    meUINT_RESET_BIT_(uint16_t, me->write_value, pin_no);
  } else {
    meUINT_SET_BIT_(uint16_t, me->write_value, pin_no);
  }
  
  if(me->u_online == true) {
    
    //write port status
    if(WritePortStatus(me) != 0) {
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
static uint8_t TogglePinStatus(TysCdrvMcp23s18_Obj * const me, uint8_t pin_no) {
  
  if(pin_no > 15) {
    return 1;
  }
  
//  if(me->u_online == true) {
//  
//    //read port status
//    if(ReadPortStatus(me) != 0) {
//      return 1;
//    }
//  }
  
  //toggle desired pin status
  uint8_t b = meUINT_BIT_(uint16_t, me->write_value, pin_no);
  if(b == 0) {
    meUINT_SET_BIT_(uint16_t, me->write_value, pin_no);
  } else {
    meUINT_RESET_BIT_(uint16_t, me->write_value, pin_no);
  }
  
  if(me->u_online == true) {
  
    //write port status
    if(WritePortStatus(me) != 0) {
      return 1;
    }
  }
  
  return 0;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/
