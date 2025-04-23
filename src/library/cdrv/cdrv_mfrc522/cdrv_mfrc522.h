/**
******************************************************************************
* @file           : cdrv_mfrc522.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_mfrc522_H
#define __cdrv_mfrc522_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\i_driver\i_gpio.h"
#include "library\i_driver\i_spi.h"

#include <stdint.h>
#include <stdbool.h>

/* Exported defines ----------------------------------------------------------*/
#define MAX_LEN 16

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
  eMFRC522_OK,
  eMFRC522_NOTAG,
  eMFRC522_ERROR
}eMfrc522Status;

typedef enum {
  ePCD_IDLE = 0x00,       //NO action; Cancel the current command
  ePCD_AUTHENT = 0x0E,    //Authentication Key
  ePCD_RECEIVE = 0x08,    //Receive Data
  ePCD_TRANSMIT = 0x04,   //Transmit data
  ePCD_TRANSCEIVE = 0x0C, //Transmit and receive data,
  ePCD_RESETPHASE = 0x0F, //Reset
  ePCD_CALCCRC = 0x03,    //CRC Calculate
}ePcdCommand;

typedef enum {
  ePICC_REQIDL = 0x26,    // find the antenna area does not enter hibernation
  ePICC_REQALL = 0x52,    // find all the cards antenna area
  ePICC_ANTICOLL = 0x93,  // anti-collision
  ePICC_SElECTTAG = 0x93, // election card
  ePICC_AUTHENT1A = 0x60, // authentication key A
  ePICC_AUTHENT1B = 0x61, // authentication key B
  ePICC_READ = 0x30,      // Read Block
  ePICC_WRITE = 0xA0,     // write block
  ePICC_DECREMENT = 0xC0, // debit
  ePICC_INCREMENT = 0xC1, // recharge
  ePICC_RESTORE = 0xC2,   // transfer block data to the buffer
  ePICC_TRANSFER = 0xB0,  // save the data in the buffer
  ePICC_HALT = 0x50,      // Sleep
}ePiccCommand;

typedef enum {
  eAUTH_KEY_A = 0x60,
  eAUTH_KEY_B = 0x61
}eAuthenticateMode;

typedef struct {
  bool init;

  sGpio *u_cs;
  sGpio *u_reset;
  sSpi *u_spi;
  uint32_t u_spi_timeout;
	
	uint8_t read_value;
}sCdrvMfrc522;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvMfrc522_Init(sCdrvMfrc522 * const me);

uint8_t fCdrvMfrc522_AntennaOn(sCdrvMfrc522 * const me);
uint8_t fCdrvMfrc522_AntennaOff(sCdrvMfrc522 * const me);
uint8_t fCdrvMfrc522_Reset(sCdrvMfrc522 * const me);

eMfrc522Status fCdrvMfrc522_Request(sCdrvMfrc522 * const me, uint8_t reqMode, uint8_t *tagType);
eMfrc522Status fCdrvMfrc522_ToCard(sCdrvMfrc522 * const me, uint8_t cmd, uint8_t *txData, uint8_t txLen, uint8_t *rxData, uint16_t *rxLen);
eMfrc522Status fCdrvMfrc522_Anticollision(sCdrvMfrc522 * const me, uint8_t *serialNum);
void fCdrvMfrc522_CalulateCRC(sCdrvMfrc522 * const me, uint8_t *input, uint8_t len, uint8_t *output);
uint8_t fCdrvMfrc522_SelectTag(sCdrvMfrc522 * const me, uint8_t *serialNum);
eMfrc522Status fCdrvMfrc522_Authenticate(sCdrvMfrc522 * const me, eAuthenticateMode mode, uint8_t block, uint8_t *sectorKey, uint8_t *serialNum);
eMfrc522Status fCdrvMfrc522_ReadBlock(sCdrvMfrc522 * const me, uint8_t block, uint8_t *data);
eMfrc522Status fCdrvMfrc522_WriteBlock(sCdrvMfrc522 * const me, uint8_t block, uint8_t *data);
eMfrc522Status fCdrvMfrc522_Halt(sCdrvMfrc522 * const me);
void fCdrvMfrc522_StopCrypto1(sCdrvMfrc522 * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_MFRC522_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
