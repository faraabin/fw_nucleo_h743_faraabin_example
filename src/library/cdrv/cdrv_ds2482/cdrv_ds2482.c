/**
******************************************************************************
* @file           : cdrv_ds2482.c
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
#include "cdrv_ds2482.h"
#include "library\chrono\me_chrono.h"

/* Private define ------------------------------------------------------------*/
/*
 * The DS2482 registers - there are 3 registers that are addressed by a read
 * pointer. The read pointer is set by the last command executed.
 *
 * To read the data, issue a register read for any address
 */
#define DS2482_CMD_RESET		        0xF0	/* No param */
#define DS2482_CMD_SET_READ_PTR		  0xE1	/* Param: DS2482_PTR_CODE_xxx */
#define DS2482_CMD_CHANNEL_SELECT	  0xC3	/* Param: Channel byte - DS2482-800 only */
#define DS2482_CMD_WRITE_CONFIG		  0xD2	/* Param: Config byte */
#define DS2482_CMD_1WIRE_RESET		  0xB4	/* Param: None */
#define DS2482_CMD_1WIRE_SINGLE_BIT 0x87	/* Param: Bit byte (bit7) */
#define DS2482_CMD_1WIRE_WRITE_BYTE 0xA5	/* Param: Data byte */
#define DS2482_CMD_1WIRE_READ_BYTE  0x96	/* Param: None */
/* Note to read the byte, Set the ReadPtr to Data then read (any addr) */
#define DS2482_CMD_1WIRE_TRIPLET    0x78	/* Param: Dir byte (bit7) */

/* Values for DS2482_CMD_SET_READ_PTR */
#define DS2482_PTR_CODE_STATUS		  0xF0
#define DS2482_PTR_CODE_DATA		    0xE1
#define DS2482_PTR_CODE_CONFIG		  0xC3

/*
 * Status Register bit definitions (read only)
 */
#define DS2482_REG_STS_DIR		      0x80
#define DS2482_REG_STS_TSB		      0x40
#define DS2482_REG_STS_SBR		      0x20
#define DS2482_REG_STS_RST		      0x10
#define DS2482_REG_STS_LL		        0x08
#define DS2482_REG_STS_SD		        0x04
#define DS2482_REG_STS_PPD		      0x02
#define DS2482_REG_STS_1WB		      0x01

#define IS_BUSY_POLL_TIMEOUT_ms     100

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t CalculateCrc8(uint8_t data);
static uint8_t WriteRegister(sCdrvDs2482Obj * const me, uint8_t regAddr, uint8_t data);
static uint8_t CommandRegister(sCdrvDs2482Obj * const me, uint8_t regAddr);
static uint8_t SetReadPointer(sCdrvDs2482Obj * const me, uint8_t readPointerCode);
static uint8_t ReadRegister(sCdrvDs2482Obj * const me, uint8_t *data);
static uint8_t WaitUntillBusIdle(sCdrvDs2482Obj * const me, uint32_t timeout_ms);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                ##### cdrv_ds2482.c Exported Functions #####
===============================================================================*/
/**
 * @brief DS2428 Detect routine that sets the I2C address and then performs a
 * device reset followed by writing the configuration byte to default values:
 * 1-Wire speed = standard (0)
 * Strong pullup = off (0)
 * Presence pulse masking = off (0)
 * Active pullup = on (CONFIG_APU = 0x01)
 * 
 * @param addr 
 * @return uint8_t 
 */
uint8_t fCdrvDs2482_Init(sCdrvDs2482Obj * const me, uint8_t addr) {
  me->init = false;
  me->_deviceAddress = addr;
  
  if(me->I2c == NULL) {
    return 1;
  }
  if(meI2c_Init_(me->I2c) != 0) {
    return 1;
  }

  if(fCdrvDs2482_Reset(me) != 0) {
    return 1;
  }

  me->Config = eCONFIG_NONE;
  if(fCdrvDs2482_WriteConfig(me, me->Config) != 0) {
    return 1;
  }

  me->init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t fCdrvDs2482_Reset(sCdrvDs2482Obj * const me) {
  if(CommandRegister(me, DS2482_CMD_RESET) != 0) {
    return 1;
  }

  meDelay_ms_(IS_BUSY_POLL_TIMEOUT_ms);

  if(SetReadPointer(me, DS2482_PTR_CODE_STATUS) != 0) {
    return 1;
  }
  if(ReadRegister(me, &me->_deviceStatus) != 0) {
    return 1;
  }
  if((me->_deviceStatus & 0xF7) != 0x10) {
    return 1;
  }

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param config 
 * @return uint8_t 
 */
uint8_t fCdrvDs2482_WriteConfig(sCdrvDs2482Obj * const me, uint8_t config) {
  uint8_t newConfig;

  if(WaitUntillBusIdle(me, IS_BUSY_POLL_TIMEOUT_ms) != 0) {
    return 1;
  }

  newConfig = ((~config) << 4) | config;
  me->_deviceConfig = newConfig;
  if(WriteRegister(me, DS2482_CMD_WRITE_CONFIG, newConfig) != 0) {
    return 1;
  }
  if(SetReadPointer(me, DS2482_PTR_CODE_CONFIG) != 0) {
    return 1;
  }
  if(ReadRegister(me, &newConfig) != 0) {
    return 1;
  }
  if(newConfig != config) {
    return 1;
  }

  return 0;
}

/**
 * @brief Reset all of the devices on the 1-Wire Net and return the result.
 * 
 * @return uint8_t 
 */
uint8_t fCdrvDs2482_OneWireReset(sCdrvDs2482Obj * const me) {

  if(CommandRegister(me, DS2482_CMD_1WIRE_RESET) != 0) {
    return 1;
  }

  meDelay_ms_(IS_BUSY_POLL_TIMEOUT_ms);

  if(WaitUntillBusIdle(me, IS_BUSY_POLL_TIMEOUT_ms) != 0) {
    return 1;
  }
  if(me->_deviceStatus & DS2482_REG_STS_PPD) {
    return 1;
  } else {
    return 0;
  }
}

/**
 * @brief Send 1 bit of communication to the 1-Wire Net.
 * 
 * @param sendbit 
 */
uint8_t fCdrvDs2482_OneWireWriteBit(sCdrvDs2482Obj * const me, uint8_t sendbit) {
  return fCdrvDs2482_OneWireTouchBit(me, sendbit);
}

/**
 * @brief Reads 1 bit of communication from the 1-Wire Net and returns the
 * result.
 * 
 * @return uint8_t 
 */
uint8_t fCdrvDs2482_OneWireReadBit(sCdrvDs2482Obj * const me) {
  return fCdrvDs2482_OneWireTouchBit(me, 0x01);
}

/**
 * @brief Send 1 bit of communication to the 1-Wire Net and return the
 * result 1 bit read from the 1-Wire Net. The parameter 'sendbit'
 * least significant bit is used and the least significant bit
 * of the result is the return bit.
 * 
 * @param sendbit 
 * @return uint8_t 
 */
uint8_t fCdrvDs2482_OneWireTouchBit(sCdrvDs2482Obj * const me, uint8_t sendbit) {

  WriteRegister(me, DS2482_CMD_1WIRE_SINGLE_BIT, sendbit ? 0xFF : 0x00);

  WaitUntillBusIdle(me, IS_BUSY_POLL_TIMEOUT_ms);

  return (me->_deviceStatus & DS2482_REG_STS_SBR) ? 1 : 0;
}

/**
 * @brief Send 8 bits of communication to the 1-Wire Net and verify that the
 * 8 bits read from the 1-Wire Net are the same (write operation).
 * 
 * @param sendbyte 
 */
uint8_t fCdrvDs2482_OneWireWriteByte(sCdrvDs2482Obj * const me, uint8_t sendbyte) {

  if(WriteRegister(me, DS2482_CMD_1WIRE_WRITE_BYTE, sendbyte) != 0) {
    return 1;
  }

  if(WaitUntillBusIdle(me, IS_BUSY_POLL_TIMEOUT_ms) != 0) {
    return 1;
  }

  return 0;
}

/**
 * @brief Send 8 bits of read communication to the 1-Wire Net and return the
 * result 8 bits read from the 1-Wire Net.
 * 
 * @return uint8_t 
 */
uint8_t fCdrvDs2482_OneWireReadByte(sCdrvDs2482Obj * const me) {
  uint8_t readData = 0;

  if(CommandRegister(me, DS2482_CMD_1WIRE_READ_BYTE) != 0) {
    return 1;
  }

  if(WaitUntillBusIdle(me, IS_BUSY_POLL_TIMEOUT_ms) != 0) {
    return 1;
  }

  if(SetReadPointer(me, DS2482_PTR_CODE_DATA) != 0) {
    return 1;
  }

  ReadRegister(me, &readData);

  return readData;
}

/**
 * @brief The 'OWBlock' transfers a block of data to and from the
 * 1-Wire Net. The result is returned in the same buffer.
 * 
 * @param tran_buf 
 * @param tran_len 
 */
uint8_t fCdrvDs2482_OneWireBlock(sCdrvDs2482Obj * const me, uint8_t *tran_buf, uint16_t tran_len) {
  for(int i = 0; i < tran_len; i++) {
    tran_buf[i] = fCdrvDs2482_OneWireTouchByte(me, tran_buf[i]);
  }

  return 0;
}

/**
 * @brief Send 8 bits of communication to the 1-Wire Net and return the
 * result 8 bits read from the 1-Wire Net. The parameter 'sendbyte'
 * least significant 8 bits are used and the least significant 8 bits
 * of the result are the return byte.
 * 
 * @param sendbyte 
 * @return uint8_t 
 */
uint8_t fCdrvDs2482_OneWireTouchByte(sCdrvDs2482Obj * const me, uint8_t sendbyte) {
  if (sendbyte == 0xFF)
    return fCdrvDs2482_OneWireReadByte(me);
  else
  {
    fCdrvDs2482_OneWireWriteByte(me, sendbyte);
    return sendbyte;
  }
}

/**
 * @brief Find the 'first' devices on the 1-Wire network.
 * 
 * @return int 
 */
int fCdrvDs2482_OneWireFirst(sCdrvDs2482Obj * const me) {
  me->LastDiscrepancy = 0;
  me->LastDeviceFlag = false;
  me->LastFamilyDiscrepancy = 0;

  return fCdrvDs2482_OneWireSearch(me, ONEWIRE_CMD_SEARCHROM);
}

/**
 * @brief Find the 'next' devices on the 1-Wire network.
 * 
 * @return int 
 */
int fCdrvDs2482_OneWireNext(sCdrvDs2482Obj * const me) {
  return fCdrvDs2482_OneWireSearch(me, ONEWIRE_CMD_SEARCHROM);
}

/**
 * @brief The 'fCdrvDs2482_OneWireSearch' function does a general search.
 * This function continues from the previous search state. The search state
 * can be reset by using the 'fCdrvDs2482_OneWireFirst' function.
 * This function contains one parameter 'alarm_only'.
 * When 'alarm_only' is TRUE (1) the find alarm command
 * 0xEC is sent instead of the normal search command 0xF0.
 * Using the find alarm command 0xEC will limit the search to only
 * 1-Wire devices that are in an 'alarm' state.
 * 
 * @return int 
 */
int fCdrvDs2482_OneWireSearch(sCdrvDs2482Obj * const me, uint8_t cmd) {
  int id_bit_number;
  int last_zero, rom_byte_number, search_result;
  int id_bit, cmp_id_bit;
  uint8_t rom_byte_mask, search_direction, status;
  uint8_t crc8;

  // initialize for search
  id_bit_number = 1;
  last_zero = 0;
  rom_byte_number = 0;
  rom_byte_mask = 1;
  search_result = 0;
  crc8 = 0;

  // if the last call was not the last one
  if (!me->LastDeviceFlag) {
    // 1-Wire reset
    if (!fCdrvDs2482_OneWireReset(me)) {
      // reset the search
      me->LastDiscrepancy = 0;
      me->LastDeviceFlag = false;
      me->LastFamilyDiscrepancy = 0;
      return 1;
    }
    
    // issue the search command
    fCdrvDs2482_OneWireWriteByte(me, cmd);

    // loop to do the search
    do {
      // if this discrepancy is before the Last Discrepancy
      // on a previous next then pick the same as last time
      if (id_bit_number < me->LastDiscrepancy) {
        if ((me->ROM_NO[rom_byte_number] & rom_byte_mask) > 0) {
          search_direction = 1;
        } else {
          search_direction = 0;
        }
      } else {
        // if equal to last pick 1, if not then pick 0
        if (id_bit_number == me->LastDiscrepancy) {
          search_direction = 1;
        } else {
          search_direction = 0;
        }
      }
      
      // Perform a triple operation on the DS2482 which will perform
      // 2 read bits and 1 write bit
      status = fCdrvDs2482_OneWireSearchTriplet(me, search_direction);

      // check bit results in status byte
      id_bit = ((status & DS2482_REG_STS_SBR) == DS2482_REG_STS_SBR);
      cmp_id_bit = ((status & DS2482_REG_STS_TSB) == DS2482_REG_STS_TSB);
      search_direction = ((status & DS2482_REG_STS_DIR) == DS2482_REG_STS_DIR) ? 1 : 0;
          
      // check for no devices on 1-Wire
      if ((id_bit) && (cmp_id_bit)) {
        break;
      } else {
        if ((!id_bit) && (!cmp_id_bit) && (search_direction == 0)) {
          last_zero = id_bit_number;

          // check for Last discrepancy in family
          if (last_zero < 9) {
            me->LastFamilyDiscrepancy = last_zero;
          }
        }

        // set or clear the bit in the ROM byte rom_byte_number
        // with mask rom_byte_mask
        if (search_direction == 1) {
            me->ROM_NO[rom_byte_number] |= rom_byte_mask;
        } else {
          me->ROM_NO[rom_byte_number] &= (uint8_t)~rom_byte_mask;
        }

        // increment the byte counter id_bit_number
        // and shift the mask rom_byte_mask
        id_bit_number++;
        rom_byte_mask <<= 1;

        // if the mask is 0 then go to new SerialNum byte rom_byte_number
        // and reset mask
        if (rom_byte_mask == 0) {
          CalculateCrc8(me->ROM_NO[rom_byte_number]);  // accumulate the CRC
          rom_byte_number++;
          rom_byte_mask = 1;
        }
      }
    }
    while(rom_byte_number < 8);  // loop until through all ROM bytes 0-7
    
    // if the search was successful then
    if (!((id_bit_number < 65) || (crc8 != 0))) {
      // search successful so set LastDiscrepancy,LastDeviceFlag
      // search_result
      me->LastDiscrepancy = last_zero;

      // check for last device
      if (me->LastDiscrepancy == 0) {
        me->LastDeviceFlag = true;
      }

      search_result = true;
    }
  }

  // if no device found then reset counters so next
  // 'search' will be like a first

  if (!search_result || (me->ROM_NO[0] == 0)) {
    me->LastDiscrepancy = 0;
    me->LastDeviceFlag = false;
    me->LastFamilyDiscrepancy = 0;
    search_result = false;
  }

  return (search_result == true) ? 1 : 0;
}

/**
 * @brief Use the DS2482 help command '1-Wire triplet' to perform one bit of a
 * 1-Wire search. This command does two read bits and one write bit. The write bit
 * is either the default direction (all device have same bit) or in case of
 * a discrepancy, the 'search_direction' parameter is used.
 * 
 * @param search_direction 
 * @return uint8_t 
 */
uint8_t fCdrvDs2482_OneWireSearchTriplet(sCdrvDs2482Obj * const me, uint8_t search_direction) {
  uint8_t dirBit = search_direction ? 0xFF : 0x00;
  me->_deviceStatus = (3 << 5);

  if(WriteRegister(me, DS2482_CMD_1WIRE_TRIPLET, dirBit) != 0) {
    return 1;
  }

  if(WaitUntillBusIdle(me, IS_BUSY_POLL_TIMEOUT_ms) != 0) {
    return 1;
  }

  return (me->_deviceStatus);
}

/**
 * @brief
 *
 * @param me
 * @param max_device
 * @param deviceRom
 * @return uint8_t
 */
uint16_t fCdrvDs2482_OneWireScan(sCdrvDs2482Obj * const me, uint16_t max_device, uint64_t *deviceRom) {
  uint16_t count = 0;
  uint8_t devices = fCdrvDs2482_OneWireFirst(me);
  while(devices) {
    count++;

    if(count >= max_device) {
      return count;
    }

    uint8_t *rom = (uint8_t*)&(deviceRom[count - 1]);
    OneWire_GetFullROM(me, rom);
    devices = fCdrvDs2482_OneWireNext(me);
  }

  return count;
}

/**
 * @brief
 *
 * @param me
 * @param addr
 */
void fCdrvDs2482_Select(sCdrvDs2482Obj * const me, uint8_t* addr) {
  fCdrvDs2482_OneWireWriteByte(me, ONEWIRE_CMD_MATCHROM);

  for(int i = 0; i < 8; i++) {
    fCdrvDs2482_OneWireWriteByte(me, *(addr + i));
  }
}

/**
 * @brief
 *
 * @param me
 * @param rom
 */
void fCdrvDs2482_SelectWithPointer(sCdrvDs2482Obj * const me, uint8_t *rom) {
  fCdrvDs2482_OneWireWriteByte(me, ONEWIRE_CMD_MATCHROM);

  for(int i = 0; i < 8; i++) {
    fCdrvDs2482_OneWireWriteByte(me, rom[i]);
  }

//  Tyu_8Byte tmp;
//  for(int i = 0 ; i < 8; i ++) {
//    tmp.byte[i] = rom[i];
//  }
//  tmp.u64 = rom;

//  for(int i = 0; i < 8; i++) {
//      fCdrvDs2482_OneWireWriteByte(me, tmp.byte[i]);
//  }
}

/**
 * @brief
 *
 * @param addr
 * @param len
 * @return uint8_t
 */
uint8_t OneWire_CRC8(uint8_t *addr, uint8_t len) {

  uint8_t crc = 0, inbyte, i, mix;

  while (len--) {
    inbyte = *addr++;
    for (i = 8; i; i--) {
      mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix) {
        crc ^= 0x8C;
      }
      inbyte >>= 1;
    }
  }

  /* Return calculated CRC */
  return crc;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
void OneWire_GetFullROM(sCdrvDs2482Obj * const me, uint8_t *firstIndex) {

  for (int i = 0; i < 8; i++) {
    *(firstIndex + i) = me->ROM_NO[i];
  }
}

/*
===============================================================================
                  ##### cdrv_ds2482.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param data
 * @return uint8_t 
 */
static uint8_t CalculateCrc8(uint8_t data) {
  uint8_t crc8 = 0;

  crc8 = crc8 ^ data;
  for (int i = 0; i < 8; ++i) {
    if (crc8 & 1) {
      crc8 = (crc8 >> 1) ^ 0x8c;
    } else {
      crc8 = (crc8 >> 1);
    }
  }

  return crc8;
}

/**
 * @brief
 *
 * @param me
 * @param regAddr
 * @param data
 * @return uint8_t
 */
static uint8_t WriteRegister(sCdrvDs2482Obj * const me, uint8_t regAddr, uint8_t data) {

  me->_txData[0] = regAddr;
  me->_txData[1] = data;

  return meI2c_Transmit_(me->I2c, me->_deviceAddress >> 1, me->_txData, 2, me->I2cTimeout_ms);
}

/**
 * @brief
 *
 * @param me
 * @param regAddr
 * @return uint8_t
 */
static uint8_t CommandRegister(sCdrvDs2482Obj * const me, uint8_t regAddr) {
  me->_txData[0] = regAddr;

  return meI2c_Transmit_(me->I2c, me->_deviceAddress >> 1, me->_txData, 1, me->I2cTimeout_ms);
}

/**
 * @brief
 *
 * @param me
 * @param readPointerCode
 * @return uint8_t
 */
static uint8_t SetReadPointer(sCdrvDs2482Obj * const me, uint8_t readPointerCode) {

  me->_txData[0] = DS2482_CMD_SET_READ_PTR;
  me->_txData[1] = readPointerCode;
  switch(me->_txData[1]) {
  case DS2482_PTR_CODE_STATUS:
  case DS2482_PTR_CODE_DATA:
  case DS2482_PTR_CODE_CONFIG:
  {
    return meI2c_Transmit_(me->I2c, me->_deviceAddress >> 1, me->_txData, 2, me->I2cTimeout_ms);
  }
  default:
    return 1;
  }
}

/**
 * @brief
 *
 * @param me
 * @param data
 * @return uint8_t
 */
static uint8_t ReadRegister(sCdrvDs2482Obj * const me, uint8_t *data) {

  return meI2c_Receive_(me->I2c, me->_deviceAddress >> 1, data, 1, me->I2cTimeout_ms);
}

/**
 * @brief
 *
 * @param me
 * @param timeout_ms
 * @return uint8_t
 */
static uint8_t WaitUntillBusIdle(sCdrvDs2482Obj * const me, uint32_t timeout_ms) {
  TysChrono_Obj timeout;

  //Check for 1wire busy status
  if(SetReadPointer(me, DS2482_PTR_CODE_STATUS) != 0) {
    return 1;
  }
  meChrono_StartTimeout_(&timeout, timeout_ms);
  do {
    if(ReadRegister(me, &me->_deviceStatus) != 0) {
      return 1;
    }
  }while(meChrono_ms_IsTimedOut(&timeout) || ((me->_deviceStatus & DS2482_REG_STS_1WB) == 1));

  return 0;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
