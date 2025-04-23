/**
******************************************************************************
* @file           : cdrv_pca9551.c
* @brief          :
* @author         : Masoud Karimi
* @version        : 0.0.0.1
* @date           : 04/13/2022
* @copyright      : COPYRIGHT(c) 2022 NTP
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
* @verbatim
* @endverbatim
*/

/* Includes ------------------------------------------------------------------*/
#include "cdrv_pca9551.h"

#include "faraabin.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DRIVER_I2C_TIMEOUT_ms   1

#define SLAVE_ADDR_HIGH_NIBBLE  0xC0

#define REG_ADDR_INPUT          0X00
#define REG_ADDR_PSC0           0x01
#define REG_ADDR_PWM0           0x02
#define REG_ADDR_PSC1           0x03
#define REG_ADDR_PWM1           0x04
#define REG_ADDR_LS0            0x05
#define REG_ADDR_LS1            0x06
// I have only implemented set and reset of a pin. PWM mode is not impelemented for simplicity!

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
static uint8_t Set(TysGpio_Obj * const me);
static void Run(TysGpio_Obj * const me);
static uint8_t Reset(TysGpio_Obj * const me);
static uint8_t Toggle(TysGpio_Obj * const me);
static uint8_t Write(TysGpio_Obj * const me, uint8_t val);
static uint8_t Clock(TysGpio_Obj * const me);
static uint8_t Const_(TysGpio_Obj * const me);
static uint8_t Read(TysGpio_Obj * const me, uint8_t *val);
static uint8_t Output(TysGpio_Obj * const me);
static uint8_t Input(TysGpio_Obj * const me);
static uint8_t Event_Edge_Config(TysGpio_Obj * const me, TyeEdge_Event edge, void(*func)(TyeEdge_Event));
static uint8_t Event_Edge_Enable(TysGpio_Obj * const me);
static uint8_t Event_Edge_Disable(TysGpio_Obj * const me);

static void Gpio_ctor(TysGpio_Obj * const me, void * const private_);

static uint8_t ReadPortStatus(TysCdrvPCA9551_Obj * const me);
static uint8_t ReadPinStatus(TysCdrvPCA9551_Obj * const me, uint8_t pin_no, uint8_t *status);

static uint8_t WritePortStatus(TysCdrvPCA9551_Obj * const me);
static uint8_t WritePinStatus(TysCdrvPCA9551_Obj * const me, uint8_t pin_no, uint8_t status);

static uint8_t TogglePinStatus(TysCdrvPCA9551_Obj * const me, uint8_t pin_no);

static uint8_t ResetI2CAfterTranceiveFailure(TysCdrvPCA9551_Obj * const me);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                        ##### cdrv_pca9551.c Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @param phy_address 
 * @return uint8_t 
 */
uint8_t CdrvPCA9551_Init(TysCdrvPCA9551_Obj * const me, uint8_t phy_address) {
  me->init = false;

  if(phy_address < 8) {
    me->slave_addr = (SLAVE_ADDR_HIGH_NIBBLE + ((uint8_t)(phy_address) << 1));
  } else {
    return 1;
  }

  meI2c_Init_(me->u_i2c);
  
  CTOR_(led0, 0);
  CTOR_(led1, 1);
  CTOR_(led2, 2);
  CTOR_(led3, 3);
  CTOR_(led4, 4);
  CTOR_(led5, 5);
  CTOR_(led6, 6);
  CTOR_(led7, 7);

  me->init = true;
  return 0;
}

/*
===============================================================================
                    ##### cdrv_pca9551.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t Init(TysGpio_Obj * const me) {
  //TysHalGpioPrivate *pvt = (TysHalGpioPrivate*)me->private_;

  me->init = false;

  me->u_dir = eGPIO_DIR_OUTPUT;

  if((me->u_dir != eGPIO_DIR_INPUT) && (me->u_dir != eGPIO_DIR_OUTPUT)) {
    return 1;
  }

  me->init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
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
 * 
 * @param me 
 * @return uint8_t 
 */
static void Run(TysGpio_Obj * const me) {
	
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
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
 * 
 * @param me 
 * @return uint8_t 
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
 * 
 * @param me 
 * @param val 
 * @return uint8_t 
 */
static uint8_t Write(TysGpio_Obj * const me, uint8_t val) {
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
 * 
 * @param me 
 * @param val 
 * @return uint8_t 
 */
static uint8_t Clock(TysGpio_Obj * const me) {
	return 1;
}

/**
 * @brief 
 * 
 * @param me 
 * @param val 
 * @return uint8_t 
 */
static uint8_t Const_(TysGpio_Obj * const me) {
	return 1;
}

/**
 * @brief 
 * 
 * @param me 
 * @param val 
 * @return uint8_t 
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
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t Output(TysGpio_Obj * const me) {
  return 1;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t Input(TysGpio_Obj * const me) {
  return 1;
}

/**
 * @brief 
 * 
 * @param me 
 * @param edge 
 * @param func 
 * @return uint8_t 
 */
static uint8_t Event_Edge_Config(TysGpio_Obj * const me, TyeEdge_Event edge, void(*func)(TyeEdge_Event)) {
  return 1;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t Event_Edge_Enable(TysGpio_Obj * const me) {
  return 1;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t Event_Edge_Disable(TysGpio_Obj * const me) {
  return 1;
}

/**
 * @brief 
 * 
 * @param me 
 * @param private_ 
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
		Const_,
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

  me->u_dir = eGPIO_DIR_OUTPUT;
  me->u_in_type = eGPIO_PULL_NONE;
  me->u_out_type = eGPIO_PUSH_PULL;
  me->val = 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t ReadPortStatus(TysCdrvPCA9551_Obj * const me) {

  uint8_t tx_data;
  uint8_t rx_data;

  tx_data = REG_ADDR_INPUT;
  if(meI2c_Transmit_(me->u_i2c, me->slave_addr, &tx_data, 1, DRIVER_I2C_TIMEOUT_ms) != 0) {
    ResetI2CAfterTranceiveFailure(me);
    return 1;
  }
  if(meI2c_Receive_(me->u_i2c, (me->slave_addr) | 0x01, &rx_data, 1, DRIVER_I2C_TIMEOUT_ms) != 0) {
    ResetI2CAfterTranceiveFailure(me);
    return 1;
  }

  me->read_value = rx_data;

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param pin_no 
 * @param status 
 * @return uint8_t 
 */
static uint8_t ReadPinStatus(TysCdrvPCA9551_Obj * const me, uint8_t pin_no, uint8_t *status) {
  
  if(pin_no > 7) {
    return 1;
  }

  if(ReadPortStatus(me) != 0) {
    return 1;
  }
  
  *status = meUINT_BIT_(uint8_t, me->read_value, pin_no);
  
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t WritePortStatus(TysCdrvPCA9551_Obj * const me) {

  uint8_t tx_data[2];
  uint8_t ls0_value = 0;
  uint8_t ls1_value = 0;

  for(int i = 0; i < 8; i++) {
      
  if(i < 4) {
    (meUINT_BIT_(uint8_t, me->write_value, i) == 0) ? (ls0_value |= (1 << (2 * i))) : (ls0_value &= ~(1 << (2 * i)));
  }else {
    (meUINT_BIT_(uint8_t, me->write_value, i) == 0) ? (ls1_value |= (1 << (2 * (i % 4)))) : (ls1_value &= ~(1 << (2 * (i % 4))));
    }
  }

  tx_data[0] = REG_ADDR_LS0;
  tx_data[1] = ls0_value;
  if(meI2c_Transmit_(me->u_i2c, me->slave_addr, tx_data, sizeof(tx_data), DRIVER_I2C_TIMEOUT_ms) != 0) {
    ResetI2CAfterTranceiveFailure(me);
    return 1;
  }

  tx_data[0] = REG_ADDR_LS1;
  tx_data[1] = ls1_value;
  if(meI2c_Transmit_(me->u_i2c, me->slave_addr, tx_data, sizeof(tx_data), DRIVER_I2C_TIMEOUT_ms) != 0) {
    ResetI2CAfterTranceiveFailure(me);
    return 1;
  }
  
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param pin_no 
 * @param status 
 * @return uint8_t 
 */
static uint8_t WritePinStatus(TysCdrvPCA9551_Obj * const me, uint8_t pin_no, uint8_t status) {
  
  if(pin_no > 8) {
    return 1;
  }
  
  //change desired pin status
  if(status == 0) {
    meUINT_RESET_BIT_(uint8_t, me->write_value, pin_no);
  } else {
    meUINT_SET_BIT_(uint8_t, me->write_value, pin_no);
  }

  if(WritePortStatus(me) != 0) {
      return 1;
  }
  
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param pin_no 
 * @return uint8_t 
 */
static uint8_t TogglePinStatus(TysCdrvPCA9551_Obj * const me, uint8_t pin_no) {
    
  if(pin_no > 8) {
    return 1;
  }

  uint8_t b = meUINT_BIT_(uint8_t, me->write_value, pin_no);
  if(b == 0) {
    meUINT_SET_BIT_(uint16_t, me->write_value, pin_no);
  } else {
    meUINT_RESET_BIT_(uint16_t, me->write_value, pin_no);
  }

  if(WritePortStatus(me) != 0) {
    return 1;
  }

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t ResetI2CAfterTranceiveFailure(TysCdrvPCA9551_Obj * const me) {
  
  meCRIT_ENTRY_();
  meI2c_Init_(me->u_i2c);
  meCRIT_EXIT_();
  
  meRUN_EVERY_ms_(i2c, 250) {
    mePRINTF_TRACE_ERROR_("I2C failure ERROR");
    meRUN_EVERY_END_;
  }
  
  return 0;
}

 /************************ (C) COPYRIGHT 2022 NTP *****END OF FILE****/
