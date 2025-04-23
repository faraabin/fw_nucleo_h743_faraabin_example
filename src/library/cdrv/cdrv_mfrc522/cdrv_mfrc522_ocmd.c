/**
******************************************************************************
* @file           : cdrv_mfrc522_ocmd.c
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
#include "cdrv_mfrc522_ocmd.h"
#include "cdrv_mfrc522.h"

#include "library\chrono\me_chrono.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(sCdrvMfrc522Obj);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                      ##### cdrv_mfrc522_ocmd.c Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(mfrc522, REQ_IDLE,
"type cmd help here") {
	TysChrono_Obj timeout;
	uint8_t cardData[16];
	
	meChrono_StartTimeout_(&timeout, 1000);
	while(fCdrvMfrc522_Request(me, ePICC_REQIDL, cardData) != eMFRC522_OK) {
		if(meChrono_ms_IsTimedOut(&timeout)) {
			mePRINTF_ERROR_("FAILED.");
			return 1;
		}
	}
	mePRINTF_("Card 0x%02x 0x%02x 0x%02x detected.\r\n", cardData[0], cardData[1], cardData[2]);
		
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(mfrc522, ANTICOLLISION,
"type cmd help here") {
	TysChrono_Obj timeout;
	uint8_t cardData[16];
	
	meChrono_StartTimeout_(&timeout, 1000);
	while(fCdrvMfrc522_Anticollision(me, cardData) != eMFRC522_OK) {
		if(meChrono_ms_IsTimedOut(&timeout)) {
			mePRINTF_ERROR_("FAILED.");
			return 1;
		}
	}
	mePRINTF_("Card UID: 0x%02x 0x%02x 0x%02x 0x%02x\r\n", cardData[0], cardData[1], cardData[2], cardData[3]);
	mePRINTF_("Card CB: 0x%02x\r\n", cardData[4]);
	
	mePRINTF_("Card UID in decimal: %d %d %d %d\r\n", cardData[0], cardData[1], cardData[2], cardData[3]);
	mePRINTF_("Card CB in decimal: %d\r\n", cardData[4]);
		
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(mfrc522, READ_BLOCK,
"type cmd help here") {
	TysChrono_Obj timeout;
	uint8_t key[6];
	uint8_t uid[5];
	uint8_t block;
	uint8_t cardData[16];
	
	mePRINTF_NOW_("Enter UID:\r\n");
	meCONSOLE_GET_INPUT_(5, 100000, "%x %x %x %x %x", &uid[0], &uid[1], &uid[2], &uid[3], &uid[4]);
	
	mePRINTF_NOW_("Enter KEY:\r\n");
	meCONSOLE_GET_INPUT_(6, 100000, "%x %x %x %x %x %x", &key[0], &key[1], &key[2], &key[3], &key[4], &key[5]);
	
	mePRINTF_NOW_("Enter block to read:\r\n");
	meCONSOLE_GET_INPUT_(1, 100000, "%d", &block);
	
	meChrono_StartTimeout_(&timeout, 1000);
	while(fCdrvMfrc522_Request(me, ePICC_REQIDL, cardData) != eMFRC522_OK) {
		if(meChrono_ms_IsTimedOut(&timeout)) {
			mePRINTF_ERROR_("Request failed.");
			return 1;
		}
	}
	while(fCdrvMfrc522_Anticollision(me, cardData) != eMFRC522_OK) {
		if(meChrono_ms_IsTimedOut(&timeout)) {
			mePRINTF_ERROR_("Anticollision failed.");
			return 1;
		}
	}
	fCdrvMfrc522_SelectTag(me, uid);
	while(fCdrvMfrc522_Authenticate(me, eAUTH_KEY_A, block, key, uid) != eMFRC522_OK) {
		if(meChrono_ms_IsTimedOut(&timeout)) {
			mePRINTF_ERROR_("Authentication failed.");
			return 1;
		}
	}
	fCdrvMfrc522_ReadBlock(me, block, cardData);
	mePRINTF_("Sector[%d]-Block[%d]: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x", block / 4, block % 4,  cardData[0], cardData[1], cardData[2], cardData[3], cardData[4],
			cardData[5], cardData[6], cardData[7], cardData[8], cardData[9], cardData[10], cardData[11], cardData[12], cardData[13], cardData[14], cardData[15]);
	meDelay_ms_(10);
	fCdrvMfrc522_StopCrypto1(me);
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(mfrc522, READ_CARD,
"type cmd help here") {
	TysChrono_Obj timeout;
	TysChrono_Obj execution;
	uint8_t key[6];
	uint8_t uid[5];
	uint8_t cardData[16];
	
	meChrono_Start(&execution);
	
	mePRINTF_NOW_("Enter UID:\r\n");
	meCONSOLE_GET_INPUT_(5, 100000, "%x %x %x %x %x", &uid[0], &uid[1], &uid[2], &uid[3], &uid[4]);
	
	mePRINTF_NOW_("Enter KEY:\r\n");
	meCONSOLE_GET_INPUT_(6, 100000, "%x %x %x %x %x %x", &key[0], &key[1], &key[2], &key[3], &key[4], &key[5]);
	
	meChrono_StartTimeout_(&timeout, 1000);
	while(fCdrvMfrc522_Request(me, ePICC_REQIDL, cardData) != eMFRC522_OK) {
		if(meChrono_ms_IsTimedOut(&timeout)) {
			mePRINTF_ERROR_("Request failed.");
			return 1;
		}
	}
	while(fCdrvMfrc522_Anticollision(me, cardData) != eMFRC522_OK) {
		if(meChrono_ms_IsTimedOut(&timeout)) {
			mePRINTF_ERROR_("Anticollision failed.");
			return 1;
		}
	}
	fCdrvMfrc522_SelectTag(me, uid);
	
	for(int i = 0; i < 64; i++) {
		while(fCdrvMfrc522_Authenticate(me, eAUTH_KEY_A, i, key, uid) != eMFRC522_OK) {
			if(meChrono_ms_IsTimedOut(&timeout)) {
				mePRINTF_ERROR_("Authentication failed.");
				return 1;
			}
		}
		fCdrvMfrc522_ReadBlock(me, i, cardData);
		mePRINTF_NOW_("Sector[%02d]-Block[%d]: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x", i / 4, i % 4,  cardData[0], cardData[1], cardData[2], cardData[3], cardData[4],
				cardData[5], cardData[6], cardData[7], cardData[8], cardData[9], cardData[10], cardData[11], cardData[12], cardData[13], cardData[14], cardData[15]);
		
		meDelay_ms_(10);
	}
	
	fCdrvMfrc522_StopCrypto1(me);
	
	uint32_t exeTime_ms = meChrono_ms_Elapsed(&execution);
	mePRINTF_("Read time: %d(ms)", exeTime_ms);
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(mfrc522, WRITE_BLOCK,
"type cmd help here") {
	TysChrono_Obj timeout;
	TysChrono_Obj execution;
	uint8_t key[6];
	uint8_t uid[5];
	uint8_t block;
	uint8_t cardData[16];
	uint8_t dataToWrite[16];
	
	mePRINTF_NOW_("Enter UID:\r\n");
	meCONSOLE_GET_INPUT_(5, 100000, "%x %x %x %x %x", &uid[0], &uid[1], &uid[2], &uid[3], &uid[4]);
	
	mePRINTF_NOW_("Enter KEY:\r\n");
	meCONSOLE_GET_INPUT_(6, 100000, "%x %x %x %x %x %x", &key[0], &key[1], &key[2], &key[3], &key[4], &key[5]);
	
	mePRINTF_NOW_("Enter block to write:\r\n");
	meCONSOLE_GET_INPUT_(1, 100000, "%d", &block);
	
	mePRINTF_NOW_("Enter data to write:\r\n");
	meCONSOLE_GET_INPUT_(16, 100000, "%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x", &dataToWrite[0], &dataToWrite[1], &dataToWrite[2], &dataToWrite[3], &dataToWrite[4], &dataToWrite[5],
											&dataToWrite[6], &dataToWrite[7], &dataToWrite[8], &dataToWrite[9], &dataToWrite[10], &dataToWrite[11], &dataToWrite[12], &dataToWrite[13], &dataToWrite[14], &dataToWrite[15]);
	
	meChrono_StartTimeout_(&timeout, 1000);
	while(fCdrvMfrc522_Request(me, ePICC_REQIDL, cardData) != eMFRC522_OK) {
		if(meChrono_ms_IsTimedOut(&timeout)) {
			mePRINTF_ERROR_("Request failed.");
			return 1;
		}
	}
	while(fCdrvMfrc522_Anticollision(me, cardData) != eMFRC522_OK) {
		if(meChrono_ms_IsTimedOut(&timeout)) {
			mePRINTF_ERROR_("Anticollision failed.");
			return 1;
		}
	}
	fCdrvMfrc522_SelectTag(me, uid);
	
	for(int i = 0; i < 64; i++) {
		while(fCdrvMfrc522_Authenticate(me, eAUTH_KEY_A, i, key, uid) != eMFRC522_OK) {
			if(meChrono_ms_IsTimedOut(&timeout)) {
				mePRINTF_ERROR_("Authentication failed.");
				return 1;
			}
		}
		fCdrvMfrc522_WriteBlock(me, block, dataToWrite);
		mePRINTF_NOW_("Sector[%02d]-Block[%d]: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x", i / 4, i % 4,  cardData[0], cardData[1], cardData[2], cardData[3], cardData[4],
				cardData[5], cardData[6], cardData[7], cardData[8], cardData[9], cardData[10], cardData[11], cardData[12], cardData[13], cardData[14], cardData[15]);
		
		meDelay_ms_(10);
	}
	
	fCdrvMfrc522_StopCrypto1(me);
	
	uint32_t exeTime_ms = meChrono_ms_Elapsed(&execution);
	mePRINTF_("Read time: %d(ms)", exeTime_ms);
	
	meCONSOLE_END_;
}

/*
===============================================================================
                ##### cdrv_mfrc522_ocmd.c Private Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_GROUP_(mfrc522,
"type cmd help here") {
	meCONSOLE_ADD_CMD_(mfrc522, REQ_IDLE, 0);
	meCONSOLE_ADD_CMD_(mfrc522, ANTICOLLISION, 0);
	meCONSOLE_ADD_CMD_(mfrc522, READ_BLOCK, 0);
	meCONSOLE_ADD_CMD_(mfrc522, READ_CARD, 0);
	meCONSOLE_ADD_CMD_(mfrc522, WRITE_BLOCK, 0);

	meCONSOLE_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
