/**
******************************************************************************
* @file           : cdrv_mfrc522.c
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
#include "cdrv_mfrc522.h"

/* Private define ------------------------------------------------------------*/
//------------------MFRC522 Register---------------
//Page 0:Command and Status
#define     Reserved00            0x00
#define     CommandReg            0x01
#define     CommIEnReg            0x02
#define     DivlEnReg             0x03
#define     CommIrqReg            0x04
#define     DivIrqReg             0x05
#define     ErrorReg              0x06
#define     Status1Reg            0x07
#define     Status2Reg            0x08
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     Reserved01            0x0F
//Page 1:Command
#define     Reserved10            0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     Reserved11            0x1A
#define     Reserved12            0x1B
#define     MifareReg             0x1C
#define     Reserved13            0x1D
#define     Reserved14            0x1E
#define     SerialSpeedReg        0x1F
//Page 2:CFG
#define     Reserved20            0x20
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     Reserved21            0x23
#define     ModWidthReg           0x24
#define     Reserved22            0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsPReg              0x28
#define     ModGsPReg             0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F
//Page 3:TestRegister
#define     Reserved30            0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39
#define     TestDAC2Reg           0x3A
#define     TestADCReg            0x3B
#define     Reserved31            0x3C
#define     Reserved32            0x3D
#define     Reserved33            0x3E
#define     Reserved34            0x3F

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t CdrvMfrc522_Write_MFRC522(sCdrvMfrc522 * const me, uint8_t addr, uint8_t val);
static uint8_t CdrvMfrc522_Read_MFRC522(sCdrvMfrc522 * const me, uint8_t addr);
static void CdrvMfrc522_SetBitMask(sCdrvMfrc522 * const me, uint8_t reg, uint8_t mask);
static void CdrvMfrc522_ClearBitMask(sCdrvMfrc522 * const me, uint8_t reg, uint8_t mask);

static void MFRC522_Init(sCdrvMfrc522 * const me);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                  ##### cdrv_mfrc522.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvMfrc522_Init(sCdrvMfrc522 * const me) {
  me->init = false;
	
	if(me->u_spi == NULL) {
		return 1;
	} else {
		me->u_spi->BitOrder = eSPI_FIRSTBIT_MSB;
		me->u_spi->DataSize = 8;
		me->u_spi->Mode = eSPI_MODE_0;
		me->u_spi->Role = eSPI_ROLE_MASTER;
		if(fSpi_Init_(me->u_spi) != 0) {
			return 1;
		}
	}
	if(me->u_cs == NULL) {
		return 1;
	} else {
		me->u_cs->Direction = eGPIO_DIR_OUTPUT;
		me->u_cs->OutType = eGPIO_PUSH_PULL;
		if(fGpio_Init_(me->u_cs) != 0) {
			return 1;
		}
		fGpio_Set_(me->u_cs);
	}
	if(me->u_reset == NULL) {
		return 1;
	} else {
		me->u_reset->Direction = eGPIO_DIR_OUTPUT;
		me->u_reset->OutType = eGPIO_PUSH_PULL;
		if(fGpio_Init_(me->u_reset) != 0) {
			return 1;
		}
		fGpio_Set_(me->u_reset);
	}

  MFRC522_Init(me);

  me->init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvMfrc522_AntennaOn(sCdrvMfrc522 * const me) {
	CdrvMfrc522_SetBitMask(me, TxControlReg, 0x03);
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvMfrc522_AntennaOff(sCdrvMfrc522 * const me) {
	CdrvMfrc522_ClearBitMask(me, TxControlReg, 0x03);
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvMfrc522_Reset(sCdrvMfrc522 * const me) {
	return CdrvMfrc522_Write_MFRC522(me, CommandReg, (uint8_t)ePCD_RESETPHASE);
}

/**
 * @brief 
 * 
 * @param me 
 * @param reqMode 
 * @param tagType 
 * @return eMfrc522Status 
 */
eMfrc522Status fCdrvMfrc522_Request(sCdrvMfrc522 * const me, uint8_t reqMode, uint8_t *tagType) {
	eMfrc522Status status;
  uint16_t backBits; // The received data bits

  CdrvMfrc522_Write_MFRC522(me, BitFramingReg, 0x07);   // TxLastBists = BitFramingReg[2..0]

  tagType[0] = reqMode;

  status = fCdrvMfrc522_ToCard(me, ePCD_TRANSCEIVE, tagType, 1, tagType, &backBits);
  if ((status != eMFRC522_OK) || (backBits != 0x10)) {
    status = eMFRC522_ERROR;
  }

  return status;
}

/**
 * @brief 
 * 
 * @param me 
 * @param cmd 
 * @param txData 
 * @param txLen 
 * @param rxData 
 * @param rxLen 
 * @return eMfrc522Status 
 */
eMfrc522Status fCdrvMfrc522_ToCard(sCdrvMfrc522 * const me, uint8_t cmd, uint8_t *txData, uint8_t txLen, uint8_t *rxData, uint16_t *rxLen) {
	eMfrc522Status status = eMFRC522_ERROR;
  uint8_t irqEn = 0x00;
  uint8_t waitIRq = 0x00;
  uint8_t lastBits;
  uint8_t n;
  uint16_t i;

  switch (cmd)
  {
    case ePCD_AUTHENT:     // Certification cards close
      {
        irqEn = 0x12;
        waitIRq = 0x10;
        break;
      }
    case ePCD_TRANSCEIVE:  // Transmit FIFO data
      {
        irqEn = 0x77;
        waitIRq = 0x30;
        break;
      }
    default:
      break;
  }

  CdrvMfrc522_Write_MFRC522(me, CommIEnReg, irqEn | 0x80);  // Interrupt request
  CdrvMfrc522_ClearBitMask(me, CommIrqReg, 0x80);         // Clear all interrupt request bit
  CdrvMfrc522_SetBitMask(me, FIFOLevelReg, 0x80);         // FlushBuffer=1, FIFO Initialization

  CdrvMfrc522_Write_MFRC522(me, CommandReg, ePCD_IDLE);    // NO action; Cancel the current command

  // Writing data to the FIFO
  for (i = 0; i < txLen; i++)
  {
    CdrvMfrc522_Write_MFRC522(me, FIFODataReg, txData[i]);
  }

  // Execute the command
  CdrvMfrc522_Write_MFRC522(me, CommandReg, cmd);
  if (cmd == ePCD_TRANSCEIVE)
  {
    CdrvMfrc522_SetBitMask(me, BitFramingReg, 0x80);      // StartSend=1,transmission of data starts
  }

  // Waiting to receive data to complete
  i = 2000;	// i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms
  do {
    // CommIrqReg[7..0]
    // Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
    n = CdrvMfrc522_Read_MFRC522(me, CommIrqReg);
    i--;
  } while ((i != 0) && !(n & 0x01) && !(n & waitIRq));

  CdrvMfrc522_ClearBitMask(me, BitFramingReg, 0x80);      // StartSend=0

  if (i != 0)
  {
    if (!(CdrvMfrc522_Read_MFRC522(me, ErrorReg) & 0x1B))  // BufferOvfl Collerr CRCErr ProtecolErr
    {
      status = eMFRC522_OK;
      if (n & irqEn & 0x01)
      {
        status = eMFRC522_NOTAG;             // ??
      }

      if (cmd == ePCD_TRANSCEIVE)
      {
				n = CdrvMfrc522_Read_MFRC522(me, FIFOLevelReg);
        lastBits = CdrvMfrc522_Read_MFRC522(me, ControlReg) & 0x07;
        if (lastBits)
        {
          *rxLen = (n - 1) * 8 + lastBits;
        }
        else
        {
          *rxLen = n * 8;
        }

        if (n == 0)
        {
          n = 1;
        }
        if (n > MAX_LEN)
        {
          n = MAX_LEN;
        }

        // Reading the received data in FIFO
        for (i = 0; i < n; i++)
        {
					rxData[i] = CdrvMfrc522_Read_MFRC522(me, FIFODataReg);
        }
      }
    }
    else {
      //printf("~~~ buffer overflow, collerr, crcerr, or protecolerr\r\n");
      status = eMFRC522_ERROR;
    }
  }
  else {
    //printf("~~~ request timed out\r\n");
  }

  return status;
}

/**
 * @brief 
 * 
 * @param me 
 * @param serialNum 
 * @return eMfrc522Status 
 */
eMfrc522Status fCdrvMfrc522_Anticollision(sCdrvMfrc522 * const me, uint8_t *serialNum) {
	eMfrc522Status status;
  uint8_t i;
  uint8_t serNumCheck = 0;
  uint16_t unLen;


  //ClearBitMask(Status2Reg, 0x08);		//TempSensclear
  //ClearBitMask(CollReg,0x80);			//ValuesAfterColl
  CdrvMfrc522_Write_MFRC522(me, BitFramingReg, 0x00);		//TxLastBists = BitFramingReg[2..0]

  serialNum[0] = ePICC_ANTICOLL;
  serialNum[1] = 0x20;
  status = fCdrvMfrc522_ToCard(me, ePCD_TRANSCEIVE, serialNum, 2, serialNum, &unLen);

  if (status == eMFRC522_OK)
  {
    //Check card serial number
    for (i = 0; i < 4; i++)
    {
      serNumCheck ^= serialNum[i];
    }
    if (serNumCheck != serialNum[i])
    {
      status = eMFRC522_ERROR;
    }
  }

  //SetBitMask(CollReg, 0x80);		//ValuesAfterColl=1

  return status;
}

/**
 * @brief 
 * 
 * @param me 
 * @param input 
 * @param len 
 * @param output 
 */
void fCdrvMfrc522_CalulateCRC(sCdrvMfrc522 * const me, uint8_t *input, uint8_t len, uint8_t *output) {
	uint8_t i, n;

  CdrvMfrc522_ClearBitMask(me, DivIrqReg, 0x04);			//CRCIrq = 0
  CdrvMfrc522_SetBitMask(me, FIFOLevelReg, 0x80);			//Clear the FIFO pointer
  //Write_MFRC522(CommandReg, PCD_IDLE);

  //Writing data to the FIFO
  for (i = 0; i < len; i++)
  {
    CdrvMfrc522_Write_MFRC522(me, FIFODataReg, *(input + i));
  }
  CdrvMfrc522_Write_MFRC522(me, CommandReg, ePCD_CALCCRC);

  //Wait CRC calculation is complete
  i = 0xFF;
  do {
    n = CdrvMfrc522_Read_MFRC522(me, DivIrqReg);
    i--;
  } while ((i != 0) && !(n & 0x04));			//CRCIrq = 1

  //Read CRC calculation result
  output[0] = CdrvMfrc522_Read_MFRC522(me, CRCResultRegL);
  output[1] = CdrvMfrc522_Read_MFRC522(me, CRCResultRegM);
}

/**
 * @brief 
 * 
 * @param me 
 * @param serialNum 
 * @return uint8_t 
 */
uint8_t fCdrvMfrc522_SelectTag(sCdrvMfrc522 * const me, uint8_t *serialNum) {
	uint8_t i;
  uint8_t status;
  uint8_t size;
  uint16_t recvBits;
  uint8_t buffer[9];

  //ClearBitMask(Status2Reg, 0x08);			//MFCrypto1On=0

  buffer[0] = ePICC_SElECTTAG;
  buffer[1] = 0x70;
  for (i = 0; i < 5; i++)
  {
    buffer[i + 2] = *(serialNum + i);
  }
  fCdrvMfrc522_CalulateCRC(me, buffer, 7, &buffer[7]);		//??
  status = fCdrvMfrc522_ToCard(me, ePCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);

  if ((status == eMFRC522_OK) && (recvBits == 0x18))
  {
    size = buffer[0];
  }
  else
  {
    size = 0;
  }

  return size;
}

/**
 * @brief 
 * 
 * @param me 
 * @param mode 
 * @param block 
 * @param sectorKey 
 * @param serialNum 
 * @return eMfrc522Status 
 */
eMfrc522Status fCdrvMfrc522_Authenticate(sCdrvMfrc522 * const me, eAuthenticateMode mode, uint8_t block, uint8_t *sectorKey, uint8_t *serialNum) {
	eMfrc522Status status;
  uint16_t recvBits;
  uint8_t i;
  uint8_t buff[12];

  //Verify the command block address + sector + password + card serial number
  buff[0] = mode;
  buff[1] = block;
  for (i = 0; i < 6; i++)
  {
    buff[i + 2] = sectorKey[i];
  }
  for (i = 0; i < 4; i++)
  {
    buff[i + 8] = serialNum[i];
  }
  status = fCdrvMfrc522_ToCard(me, ePCD_AUTHENT, buff, 12, buff, &recvBits);

  if ((status != eMFRC522_OK) || (!(CdrvMfrc522_Read_MFRC522(me, Status2Reg) & 0x08)))
  {
    status = eMFRC522_ERROR;
  }

  return status;
}

/**
 * @brief 
 * 
 * @param me 
 * @param block 
 * @param data 
 * @return eMfrc522Status 
 */
eMfrc522Status fCdrvMfrc522_ReadBlock(sCdrvMfrc522 * const me, uint8_t block, uint8_t *data) {
	eMfrc522Status status;
  uint16_t unLen;

  data[0] = ePICC_READ;
  data[1] = block;
  fCdrvMfrc522_CalulateCRC(me, data, 2, &data[2]);
  status = fCdrvMfrc522_ToCard(me, ePCD_TRANSCEIVE, data, 4, data, &unLen);

  if ((status != eMFRC522_OK) || (unLen != 0x90))
  {
    status = eMFRC522_ERROR;
  }

  return status;
}

/**
 * @brief 
 * 
 * @param me 
 * @param block 
 * @param data 
 * @return eMfrc522Status 
 */
eMfrc522Status fCdrvMfrc522_WriteBlock(sCdrvMfrc522 * const me, uint8_t block, uint8_t *data) {
	eMfrc522Status status;
  uint16_t recvBits;
  uint8_t i;
  uint8_t buff[18];

  buff[0] = ePICC_WRITE;
  buff[1] = block;
  fCdrvMfrc522_CalulateCRC(me, buff, 2, &buff[2]);
  status = fCdrvMfrc522_ToCard(me, ePCD_TRANSCEIVE, buff, 4, buff, &recvBits);

  if ((status != eMFRC522_OK))// || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
  {
    status = eMFRC522_ERROR;
  }

  if (status == eMFRC522_OK)
  {
    for (i = 0; i < 16; i++)		//Data to the FIFO write 16Byte
    {
      buff[i] = *(data+i);
    }
    fCdrvMfrc522_CalulateCRC(me, buff, 16, &buff[16]);
    status = fCdrvMfrc522_ToCard(me, ePCD_TRANSCEIVE, buff, 18, buff, &recvBits);

    if ((status != eMFRC522_OK))// || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
    {
      status = eMFRC522_ERROR;
    }
  }

  return status;
}

/**
 * @brief 
 * 
 * @param me 
 */
eMfrc522Status fCdrvMfrc522_Halt(sCdrvMfrc522 * const me) {
  uint16_t unLen;
  uint8_t buff[4];

  buff[0] = ePICC_HALT;
  buff[1] = 0;
  fCdrvMfrc522_CalulateCRC(me, buff, 2, &buff[2]);

  return fCdrvMfrc522_ToCard(me, ePCD_TRANSCEIVE, buff, 4, buff, &unLen);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMfrc522_StopCrypto1(sCdrvMfrc522 * const me) {
	CdrvMfrc522_ClearBitMask(me, Status2Reg, 0x08); // Status2Reg[7..0] bits are: TempSensClear I2CForceHS reserved reserved   MFCrypto1On ModemState[2:0]
}

/*
===============================================================================
                  ##### cdrv_mfrc522.c Private Functions #####
===============================================================================*/
/**
 * @brief Initialize RC522
 * 
 */
static void MFRC522_Init(sCdrvMfrc522 * const me) {
  fCdrvMfrc522_Reset(me);

  // Timer: TPrescaler*TreloadVal/6.78MHz = 24ms
  CdrvMfrc522_Write_MFRC522(me, TModeReg, 0x80); // 0x8D);      // Tauto=1; f(Timer) = 6.78MHz/TPreScaler
  CdrvMfrc522_Write_MFRC522(me, TPrescalerReg, 0xA9); //0x34); // TModeReg[3..0] + TPrescalerReg
  CdrvMfrc522_Write_MFRC522(me, TReloadRegL, 0x03); //30);
  CdrvMfrc522_Write_MFRC522(me, TReloadRegH, 0xE8); //0);
  CdrvMfrc522_Write_MFRC522(me, TxAutoReg, 0x40);     // force 100% ASK modulation
  CdrvMfrc522_Write_MFRC522(me, ModeReg, 0x3D);       // CRC Initial value 0x6363

  // interrupts, still playing with these
  // Write_MFRC522(CommIEnReg, 0xFF);
  // Write_MFRC522(DivlEnReg, 0xFF);

  // turn antenna on
  fCdrvMfrc522_AntennaOn(me);
}

/**
 * @brief Write a byte of data of value val on MFRC522 register with address addr
 * 
 * @param me 
 * @param addr 
 * @param val 
 */
uint8_t CdrvMfrc522_Write_MFRC522(sCdrvMfrc522 * const me, uint8_t addr, uint8_t val) {
  uint8_t addr_bits = (((addr<<1) & 0x7E));
	uint8_t value = val;

  fGpio_Reset_(me->u_cs);
  if(fSpi_Transmit_(me->u_spi, &addr_bits, 1, me->u_spi_timeout) != 0) {
    return 1;
  }
  if(fSpi_Transmit_(me->u_spi, &value, 1, me->u_spi_timeout) != 0) {
    return 1;
  }
  fGpio_Set_(me->u_cs);

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param addr 
 * @return uint8_t 
 */
uint8_t CdrvMfrc522_Read_MFRC522(sCdrvMfrc522 * const me, uint8_t addr) {
  uint8_t addr_bits = (((addr<<1) & 0x7E) | 0x80);

  fGpio_Reset_(me->u_cs);
  if(fSpi_Transmit_(me->u_spi, &addr_bits, 1, me->u_spi_timeout) != 0) {
    return 1;
  }
  if(fSpi_Receive_(me->u_spi, &me->read_value, 1, me->u_spi_timeout) != 0) {
    return 1;
  }
  fGpio_Set_(me->u_cs);

  return me->read_value;
}

/**
 * @brief 
 * 
 * @param me 
 */
void CdrvMfrc522_SetBitMask(sCdrvMfrc522 * const me, uint8_t reg, uint8_t mask) {
  CdrvMfrc522_Write_MFRC522(me, reg, CdrvMfrc522_Read_MFRC522(me, reg) | mask);
}

/**
 * @brief 
 * 
 * @param me 
 */
void CdrvMfrc522_ClearBitMask(sCdrvMfrc522 * const me, uint8_t reg, uint8_t mask) {
	CdrvMfrc522_Write_MFRC522(me, reg, CdrvMfrc522_Read_MFRC522(me, reg) & (~mask));
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
