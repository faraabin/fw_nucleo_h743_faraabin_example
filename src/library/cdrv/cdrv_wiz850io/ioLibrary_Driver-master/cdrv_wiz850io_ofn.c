/**
******************************************************************************
* @file           : cdrv_wiz850io_ofn.c
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2024 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2024 FaraabinCo.
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
#include "cdrv_wiz850io_ofn.h"

#include "cdrv_wiz850io.h"

#include "Ethernet\socket.h"

#include <string.h>

#ifdef FARAABIN_ENABLE

/* Private typedef -----------------------------------------------------------*/
FARAABIN_FUNCTION_GROUP_TYPE_DEF_(sCdrvWiz850io);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Functions Declaration #####                       ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/

/**
 * @brief 
 * 
 */
FARAABIN_FUNCTION_(CdrvWiz850io, IPCONFIG, "help") {

  wiz_NetInfo net_info;
  
  wizchip_getnetinfo(&net_info);
  
  FARAABIN_PrintfToFunction_("\n\nW5500 Ethernet adapter:\n");
  FARAABIN_PrintfToFunction_("\n  Physical Address.....: %x-%x-%x-%x-%x-%x", net_info.mac[0], net_info.mac[1], net_info.mac[2], net_info.mac[3], net_info.mac[4], net_info.mac[5]);
  FARAABIN_PrintfToFunction_("\n  DHCP Enabled.........: %s", (net_info.dhcp == NETINFO_STATIC) ? "No" : "Yes");
  FARAABIN_PrintfToFunction_("\n  IPv4 Address.........: %u.%u.%u.%u", net_info.ip[0], net_info.ip[1], net_info.ip[2], net_info.ip[3]);
  FARAABIN_PrintfToFunction_("\n  Subnet Mask..........: %u.%u.%u.%u", net_info.sn[0], net_info.sn[1], net_info.sn[2], net_info.sn[3]);
  FARAABIN_PrintfToFunction_("\n  Default Gateway......: %u.%u.%u.%u", net_info.gw[0], net_info.gw[1], net_info.gw[2], net_info.gw[3]);

  FARAABIN_FUNCTION_END_();
}



/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Group Declaration #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
* @brief 
* 
*/
FARAABIN_FUNCTION_GROUP_(CdrvWiz850io, "help") {
	
  FARAABIN_FUNCTION_GROUP_ADD_(CdrvWiz850io, IPCONFIG);
  
}

#endif

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
