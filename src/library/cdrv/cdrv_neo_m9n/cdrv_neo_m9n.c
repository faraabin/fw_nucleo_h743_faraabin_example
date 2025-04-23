/*
 * me.c
 *
 *  Created on: 03.10.2020
 *      Author: SimpleMethod
 *
 *Copyright 2020 SimpleMethod
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy of
 *this software and associated documentation files (the "Software"), to deal in
 *the Software without restriction, including without limitation the rights to
 *use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 *of the Software, and to permit persons to whom the Software is furnished to do
 *so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all
 *copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 ******************************************************************************
 */

#include "cdrv_neo_m9n.h"

#include "library\utility\chrono\me_chrono.h"

union u_Short uShort;
union i_Short iShort;
union u_Long uLong;
union i_Long iLong;

/*!
 * Structure initialization.
 * @param me Pointer to main me structure.
 * @param huart Pointer to uart handle.
 */
uint8_t fCdrvNeoM9n_Init(sCdrvNeoM9n_Obj *me, TysSerial_Obj *uart) {
	
	//me->huart = huart;
	me->uart = uart;
	me->year = 0;
	me->month = 0;
	me->day = 0;
	me->hour = 0;
	me->min = 0;
	me->sec = 0;
	me->fixType = 0;
	me->lon = 0;
	me->lat = 0;
	me->height = 0;
	me->hMSL = 0;
	me->hAcc = 0;
	me->vAcc = 0;
	me->gSpeed = 0;
	me->headMot = 0;
	
	return 0;
}

/*!
 * Searching for a header in data buffer and matching class and message ID to buffer data.
 * @param me Pointer to main me structure.
 */
void fCdrvNeoM9n_ParseBuffer(sCdrvNeoM9n_Obj *me) {

	for (int var = 0; var <= 100; ++var) {
		if (me->uartWorkingBuffer[var] == 0xB5
				&& me->uartWorkingBuffer[var + 1] == 0x62) {
			if (me->uartWorkingBuffer[var + 2] == 0x27
					&& me->uartWorkingBuffer[var + 3] == 0x03) { //Look at: 32.19.1.1 u-blox 8 Receiver description
				fCdrvNeoM9n_ParseUniqID(me);
			} else if (me->uartWorkingBuffer[var + 2] == 0x01
					&& me->uartWorkingBuffer[var + 3] == 0x21) { //Look at: 32.17.14.1 u-blox 8 Receiver description
				fCdrvNeoM9n_ParseNavigatorData(me);
			} else if (me->uartWorkingBuffer[var + 2] == 0x01
					&& me->uartWorkingBuffer[var + 3] == 0x07) { //ook at: 32.17.30.1 u-blox 8 Receiver description
				fCdrvNeoM9n_ParsePVTData(me);
			} else if (me->uartWorkingBuffer[var + 2] == 0x01
					&& me->uartWorkingBuffer[var + 3] == 0x02) { // Look at: 32.17.15.1 u-blox 8 Receiver description
				fCdrvNeoM9n_ParsePOSLLHData(me);
			}
		}
	}
}

/*!
 * Make request for unique chip ID data.
 * @param me Pointer to main me structure.
 */
void fCdrvNeoM9n_GetUniqID(sCdrvNeoM9n_Obj *me) {
	
	meSerial_SendNonBlock_(me->uart, (uint8_t*)getDeviceID,
			sizeof(getDeviceID) / sizeof(uint8_t));
	
}

/*!
 * Make request for UTC time solution data.
 * @param me Pointer to main me structure.
 */
void fCdrvNeoM9n_GetNavigatorData(sCdrvNeoM9n_Obj *me) {
	
	meSerial_SendNonBlock_(me->uart, (uint8_t*)getNavigatorData,
			sizeof(getNavigatorData) / sizeof(uint8_t));
	
}

/*!
 * Make request for geodetic position solution data.
 * @param me Pointer to main me structure.
 */
void fCdrvNeoM9n_GetPOSLLHData(sCdrvNeoM9n_Obj *me) {
	
	meSerial_SendNonBlock_(me->uart, (uint8_t*)getPOSLLHData,
			sizeof(getPOSLLHData) / sizeof(uint8_t));
	
}

/*!
 * Make request for navigation position velocity time solution data.
 * @param me Pointer to main me structure.
 */
void fCdrvNeoM9n_GetPVTData(sCdrvNeoM9n_Obj *me) {
	
	meSerial_SendNonBlock_(me->uart, (uint8_t*)getPVTData,
			sizeof(getPVTData) / sizeof(uint8_t));
	
}

/*!
 * Parse data to unique chip ID standard.
 * Look at: 32.19.1.1 u-blox 8 Receiver description
 * @param me Pointer to main me structure.
 */
void fCdrvNeoM9n_ParseUniqID(sCdrvNeoM9n_Obj *me) {
	
	for (int var = 0; var < 5; ++var) {
		me->uniqueID[var] = me->uartWorkingBuffer[10 + var];
	}
}

/*!
 * Changing the me mode.
 * Look at: 32.10.19 u-blox 8 Receiver description
 */
void fCdrvNeoM9n_SetMode(sCdrvNeoM9n_Obj *me, short meMode) {
	
	if (meMode == 0) {
		meSerial_SendNonBlock_(me->uart, (uint8_t*)setPortableMode,sizeof(setPortableMode) / sizeof(uint8_t));
	} else if (meMode == 1) {
		meSerial_SendNonBlock_(me->uart, (uint8_t*)setStationaryMode,sizeof(setStationaryMode) / sizeof(uint8_t));
	} else if (meMode == 2) {
		meSerial_SendNonBlock_(me->uart, (uint8_t*)setPedestrianMode,sizeof(setPedestrianMode) / sizeof(uint8_t));
	} else if (meMode == 3) {
		meSerial_SendNonBlock_(me->uart, (uint8_t*)setAutomotiveMode,sizeof(setAutomotiveMode) / sizeof(uint8_t));
	} else if (meMode == 4) {
		meSerial_SendNonBlock_(me->uart, (uint8_t*)setAutomotiveMode,sizeof(setAutomotiveMode) / sizeof(uint8_t));
	} else if (meMode == 5) {
		meSerial_SendNonBlock_(me->uart, (uint8_t*)setAirbone1GMode,sizeof(setAirbone1GMode) / sizeof(uint8_t));
	} else if (meMode == 6) {
		meSerial_SendNonBlock_(me->uart, (uint8_t*)setAirbone2GMode,sizeof(setAirbone2GMode) / sizeof(uint8_t));
	} else if (meMode == 7) {
		meSerial_SendNonBlock_(me->uart, (uint8_t*)setAirbone4GMode,sizeof(setAirbone4GMode) / sizeof(uint8_t));
	} else if (meMode == 8) {
		meSerial_SendNonBlock_(me->uart, (uint8_t*)setWirstMode,sizeof(setWirstMode) / sizeof(uint8_t));
	} else if (meMode == 9) {
		meSerial_SendNonBlock_(me->uart, (uint8_t*)setBikeMode,sizeof(setBikeMode) / sizeof(uint8_t));
	}
}
/*!
 * Parse data to navigation position velocity time solution standard.
 * Look at: 32.17.15.1 u-blox 8 Receiver description.
 * @param me Pointer to main me structure.
 */
void fCdrvNeoM9n_ParsePVTData(sCdrvNeoM9n_Obj *me) {
	
	uShort.bytes[0] = me->uartWorkingBuffer[10];
	me->yearBytes[0]=me->uartWorkingBuffer[10];
	uShort.bytes[1] = me->uartWorkingBuffer[11];
	me->yearBytes[1]=me->uartWorkingBuffer[11];
	me->year = uShort.uShort;
	me->month = me->uartWorkingBuffer[12];
	me->day = me->uartWorkingBuffer[13];
	me->hour = me->uartWorkingBuffer[14];
	me->min = me->uartWorkingBuffer[15];
	me->sec = me->uartWorkingBuffer[16];
	me->fixType = me->uartWorkingBuffer[26];

	for (int var = 0; var < 4; ++var) {
		iLong.bytes[var] = me->uartWorkingBuffer[var + 30];
		me->lonBytes[var]= me->uartWorkingBuffer[var + 30];
	}
	me->lon = iLong.iLong;
	me->fLon=(float)iLong.iLong/10000000.0f;
	for (int var = 0; var < 4; ++var) {
		iLong.bytes[var] = me->uartWorkingBuffer[var + 34];
		me->latBytes[var]=me->uartWorkingBuffer[var + 34];
	}
	me->lat = iLong.iLong;
	me->fLat=(float)iLong.iLong/10000000.0f;
	for (int var = 0; var < 4; ++var) {
		iLong.bytes[var] = me->uartWorkingBuffer[var + 38];
	}
	me->height = iLong.iLong;

	for (int var = 0; var < 4; ++var) {
		iLong.bytes[var] = me->uartWorkingBuffer[var + 42];
		me->hMSLBytes[var] = me->uartWorkingBuffer[var + 42];
	}
	me->hMSL = iLong.iLong;

	for (int var = 0; var < 4; ++var) {
		uLong.bytes[var] = me->uartWorkingBuffer[var + 46];
	}
	me->hAcc = uLong.uLong;

	for (int var = 0; var < 4; ++var) {
		uLong.bytes[var] = me->uartWorkingBuffer[var + 50];
	}
	me->vAcc = uLong.uLong;

	for (int var = 0; var < 4; ++var) {
		iLong.bytes[var] = me->uartWorkingBuffer[var + 66];
		me->gSpeedBytes[var] = me->uartWorkingBuffer[var + 66];
	}
	me->gSpeed = iLong.iLong;

	for (int var = 0; var < 4; ++var) {
		iLong.bytes[var] = me->uartWorkingBuffer[var + 70];
	}
	me->headMot = iLong.iLong * 1e-5; // todo I'm not sure this good options.
}

/*!
 * Parse data to UTC time solution standard.
 * Look at: 32.17.30.1 u-blox 8 Receiver description.
 * @param me Pointer to main me structure.
 */
void fCdrvNeoM9n_ParseNavigatorData(sCdrvNeoM9n_Obj *me) {
	
	uShort.bytes[0] = me->uartWorkingBuffer[18];
	uShort.bytes[1] = me->uartWorkingBuffer[19];
	me->year = uShort.uShort;
	me->month = me->uartWorkingBuffer[20];
	me->day = me->uartWorkingBuffer[21];
	me->hour = me->uartWorkingBuffer[22];
	me->min = me->uartWorkingBuffer[23];
	me->sec = me->uartWorkingBuffer[24];
}

/*!
 * Parse data to geodetic position solution standard.
 * Look at: 32.17.14.1 u-blox 8 Receiver description.
 * @param me Pointer to main me structure.
 */
void fCdrvNeoM9n_ParsePOSLLHData(sCdrvNeoM9n_Obj *me) {
	
	for (int var = 0; var < 4; ++var) {
		iLong.bytes[var] = me->uartWorkingBuffer[var + 10];
	}
	me->lon = iLong.iLong;
	me->fLon=(float)iLong.iLong/10000000.0f;

	for (int var = 0; var < 4; ++var) {
		iLong.bytes[var] = me->uartWorkingBuffer[var + 14];
	}
	me->lat = iLong.iLong;
	me->fLat=(float)iLong.iLong/10000000.0f;

	for (int var = 0; var < 4; ++var) {
		iLong.bytes[var] = me->uartWorkingBuffer[var + 18];
	}
	me->height = iLong.iLong;

	for (int var = 0; var < 4; ++var) {
		iLong.bytes[var] = me->uartWorkingBuffer[var + 22];
	}
	me->hMSL = iLong.iLong;

	for (int var = 0; var < 4; ++var) {
		uLong.bytes[var] = me->uartWorkingBuffer[var + 26];
	}
	me->hAcc = uLong.uLong;

	for (int var = 0; var < 4; ++var) {
		uLong.bytes[var] = me->uartWorkingBuffer[var + 30];
	}
	me->vAcc = uLong.uLong;
}

/*!
 *  Sends the basic configuration: Activation of the UBX standard, change of NMEA version to 4.10 and turn on of the Galileo system.
 * @param me Pointer to main me structure.
 */
void fCdrvNeoM9n_LoadConfig(sCdrvNeoM9n_Obj *me) {
	
	meSerial_SendNonBlock_(me->uart, (uint8_t*)configUBX,
			sizeof(configUBX) / sizeof(uint8_t));
	
	meDelay_ms_(250);
	
	meSerial_SendNonBlock_(me->uart, (uint8_t*)setNMEA410,
			sizeof(setNMEA410) / sizeof(uint8_t));
	
	meDelay_ms_(250);
	
	meSerial_SendNonBlock_(me->uart, (uint8_t*)setGNSS,
			sizeof(setGNSS) / sizeof(uint8_t));
	
	meDelay_ms_(250);
}



/*!
 *  Creates a checksum based on UBX standard.
 * @param class Class value from UBX doc.
 * @param messageID MessageID value from UBX doc.
 * @param dataLength Data length value from UBX doc.
 * @param payload Just payload.
 * @return  Returns checksum.
 */
uint8_t fCdrvNeoM9n_Checksum(uint8_t class, uint8_t messageID, uint8_t dataLength,uint8_t *payload) {
//todo: Look at 32.4 UBX Checksum
	return 0;
}
