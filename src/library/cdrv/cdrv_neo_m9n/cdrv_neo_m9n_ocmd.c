/**
 ******************************************************************************
 *  @file         cdrv_neo_m9n_ocmd.c
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
#include "cdrv_neo_m9n_ocmd.h"

#include "cdrv_neo_m9n.h"
#include "bsp.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(sCdrvNeoM9n_Obj);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

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
meCONSOLE_CMD_(cdrv_neo_m9n, READ,
"type cmd help here") {
  
  fCdrvNeoM9n_GetUniqID(me);
	meDelay_ms_(100);
	fCdrvNeoM9n_GetPVTData(me);
	meDelay_ms_(100);
	
	mePRINTF_("\r\nDay: %d-%d-%d \r\n", me->day, me->month,me->year);
	mePRINTF_("Time: %d:%d:%d \r\n", me->hour, me->min,me->sec);
	mePRINTF_("Status of fix: %d \r\n", me->fixType);
	mePRINTF_("Latitude: %f \r\n", me->fLat);
	mePRINTF_("Longitude: %f \r\n",(float) me->lon / 10000000.0);
	mePRINTF_("Height above ellipsoid: %d \r\n", me->height);
	mePRINTF_("Height above mean sea level: %d \r\n", me->hMSL);
	mePRINTF_("Ground Speed (2-D): %d \r\n", me->gSpeed);
	mePRINTF_("Unique ID: %04X %04X %04X %04X\n\r",
			me->uniqueID[0], me->uniqueID[1],
			me->uniqueID[2], me->uniqueID[3]);
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_neo_m9n, READ_1,
"type cmd help here") {
  
  BspGPS_NavMsgRequest();
	meDelay_ms_(100);
	
	mePRINTF_("\r\nDay: %d-%d-%d \r\n", bsp.GPS_NAV_PVT_Union.data.day, bsp.GPS_NAV_PVT_Union.data.month, bsp.GPS_NAV_PVT_Union.data.year);
	mePRINTF_("Time: %d:%d:%d \r\n", bsp.GPS_NAV_PVT_Union.data.hour, bsp.GPS_NAV_PVT_Union.data.min, bsp.GPS_NAV_PVT_Union.data.sec);
	mePRINTF_("Status of fix: %d \r\n", bsp.GPS_NAV_PVT_Union.data.fixType);
	mePRINTF_("valid: %d \r\n", bsp.GPS_NAV_PVT_Union.data.valid);
	mePRINTF_("Latitude: %f \r\n", (float)bsp.GPS_NAV_PVT_Union.data.latitude_deg / 10000000);
	mePRINTF_("Longitude: %f \r\n", (float)bsp.GPS_NAV_PVT_Union.data.longitude_deg / 10000000);
	mePRINTF_("height: %d \r\n", bsp.GPS_NAV_PVT_Union.data.height);
	mePRINTF_("hMSL: %d \r\n", bsp.GPS_NAV_PVT_Union.data.hMSL);
	mePRINTF_("hAcc / vAcc: %d / %d \r\n", bsp.GPS_NAV_PVT_Union.data.hAcc, bsp.GPS_NAV_PVT_Union.data.vAcc);
	mePRINTF_("vel(NED): %d %d %d \r\n", bsp.GPS_NAV_PVT_Union.data.velN, bsp.GPS_NAV_PVT_Union.data.velE, bsp.GPS_NAV_PVT_Union.data.velD);
	mePRINTF_("headMot: %i \r\n", bsp.GPS_NAV_PVT_Union.data.headMot);
	mePRINTF_("Ground Speed (2-D): %d \r\n", me->gSpeed);
	
	meCONSOLE_END_;
}

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
meCONSOLE_GROUP_(cdrv_neo_m9n,
"type cmd help here") {

	meCONSOLE_ADD_CMD_(cdrv_neo_m9n, READ, 0);
	meCONSOLE_ADD_CMD_(cdrv_neo_m9n, READ_1, 0);
  
  meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/
