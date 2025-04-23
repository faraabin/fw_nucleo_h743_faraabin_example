/**
 ******************************************************************************
 * @file           : cdrv_wiz850io.c
 * @brief          :
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 FaraabinCo.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component
 * 
 * https://faraabinco.ir/
 * https://github.com/FaraabinCo
 *
 ******************************************************************************
 * @verbatim
 * @endverbatim
 */

/* Includes ------------------------------------------------------------------*/
#include "cdrv_wiz850io.h"

#include "Ethernet\socket.h"
#include "ex\ex_tcp_udp_server.h"

#include <stdlib.h>

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/**
 * @brief 
 * 
 */
#define CHECK_INIT_(ret_)\
if(!me->_init) {\
  return (ret_);\
}

/**
 * @brief 
 * 
 */
#define CHECK_ENABLE_(ret_)\
if(!me->Enable) {\
  return (ret_);\
}

/* Private typedef -----------------------------------------------------------*/
typedef struct {

  bool IsBusy;

  uint8_t SocketNo;

  uint16_t Port;

  void(*fpClientConnectedEventCallback)(object sender, sTcpServerClientConnectedEventArgs *e);

  void(*fpServerEventCallback)(object sender, sTcpServerEventArgs *e);

  void(*fpReceiveDataEventCallback)(object sender, sTcpServerReceiveDataEventArgs *e);

  uint8_t *pBuffer;

  uint32_t BufferSize;

  sTcpServer *pTcpServer;
                               
}sTcpServerPrivate;

/* Private variables ---------------------------------------------------------*/
static sCdrvWiz850io *device;

static sTcpServerPrivate Socket_Private[8] = {
  {
    .IsBusy = false,
    .SocketNo = 0,
    .Port = 0,
    .fpClientConnectedEventCallback = NULL,
    .fpServerEventCallback = NULL,
    .fpReceiveDataEventCallback = NULL,
    .pBuffer = NULL,
    .BufferSize = 0,
    .pTcpServer = NULL
  },
  {
    .IsBusy = false,
    .SocketNo = 1,
    .Port = 0,
    .fpClientConnectedEventCallback = NULL,
    .fpServerEventCallback = NULL,
    .fpReceiveDataEventCallback = NULL,
    .pBuffer = NULL,
    .BufferSize = 0,
    .pTcpServer = NULL
  },
  {
    .IsBusy = false,
    .SocketNo = 2,
    .Port = 0,
    .fpClientConnectedEventCallback = NULL,
    .fpServerEventCallback = NULL,
    .fpReceiveDataEventCallback = NULL,
    .pBuffer = NULL,
    .BufferSize = 0,
    .pTcpServer = NULL
  },
  {
    .IsBusy = false,
    .SocketNo = 3,
    .Port = 0,
    .fpClientConnectedEventCallback = NULL,
    .fpServerEventCallback = NULL,
    .fpReceiveDataEventCallback = NULL,
    .pBuffer = NULL,
    .BufferSize = 0,
    .pTcpServer = NULL
  },
  {
    .IsBusy = false,
    .SocketNo = 4,
    .Port = 0,
    .fpClientConnectedEventCallback = NULL,
    .fpServerEventCallback = NULL,
    .fpReceiveDataEventCallback = NULL,
    .pBuffer = NULL,
    .BufferSize = 0,
    .pTcpServer = NULL
  },
  {
    .IsBusy = false,
    .SocketNo = 5,
    .Port = 0,
    .fpClientConnectedEventCallback = NULL,
    .fpServerEventCallback = NULL,
    .fpReceiveDataEventCallback = NULL,
    .pBuffer = NULL,
    .BufferSize = 0,
    .pTcpServer = NULL
  },
  {
    .IsBusy = false,
    .SocketNo = 6,
    .Port = 0,
    .fpClientConnectedEventCallback = NULL,
    .fpServerEventCallback = NULL,
    .fpReceiveDataEventCallback = NULL,
    .pBuffer = NULL,
    .BufferSize = 0,
    .pTcpServer = NULL
  },
  {
    .IsBusy = false,
    .SocketNo = 7,
    .Port = 0,
    .fpClientConnectedEventCallback = NULL,
    .fpServerEventCallback = NULL,
    .fpReceiveDataEventCallback = NULL,
    .pBuffer = NULL,
    .BufferSize = 0,
    .pTcpServer = NULL
  },
};

/* Private function prototypes -----------------------------------------------*/
static void fW5500_Select(void);
static void fW5500_Unselect(void);
static void fW5500_ReadBuff(uint8_t* buff, uint16_t len);
static void fW5500_WriteBuff(uint8_t* buff, uint16_t len);
static uint8_t fW5500_ReadByte(void);
static void fW5500_WriteByte(uint8_t byte);
static void fW5500_cris_en(void);
static void fW5500_cris_ex(void);

static uint8_t Init(sTcpServer * const me);
static uint8_t Listen(sTcpServer * const me, uint16_t port);
static void Stop(sTcpServer * const me);
static uint8_t Send(sTcpServer * const me, uint8_t *pData, uint16_t size);
static bool IsSending(sTcpServer * const me);
static uint8_t RegisterClientConnectedEvent(sTcpServer * const me, void(*fpCallback)(object sender, sTcpServerClientConnectedEventArgs *e));
static uint8_t RegisterServerEvent(sTcpServer * const me, void(*fpCallback)(object sender, sTcpServerEventArgs *e));
static uint8_t RegisterReceiveDataEvent(sTcpServer * const me, void(*fpCallback)(object sender, sTcpServerReceiveDataEventArgs *e));

static void fTcpServerRun(uint8_t sn);

/* Variables -----------------------------------------------------------------*/
extern uint16_t sock_is_sending;

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Exported Functions #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvWiz850io_Init(sCdrvWiz850io * const me) {
  
  me->_init = false;
  
  if((me->Spi == NULL) || (me->Cs == NULL)) {
    return 1;
  }
  
  me->Cs->Direction = eGPIO_DIR_OUTPUT;
  me->Cs->OutType = eGPIO_PUSH_PULL;
  if(fGpio_Init_(me->Cs) != 0) {
    return 1;
  }
  fGpio_Set_(me->Cs);

  me->Spi->Role = eSPI_ROLE_MASTER;
  me->Spi->Mode = eSPI_MODE_3;
  me->Spi->DataSize = 8;
  me->Spi->BitOrder = eSPI_FIRSTBIT_MSB;
  if(fSpi_Init_(me->Spi) != 0) {
    return 1;
  }

  device = me;
  
  reg_wizchip_cs_cbfunc(fW5500_Select, fW5500_Unselect);
  reg_wizchip_spi_cbfunc(fW5500_ReadByte, fW5500_WriteByte);
  reg_wizchip_spiburst_cbfunc(fW5500_ReadBuff, fW5500_WriteBuff);
  reg_wizchip_cris_cbfunc(fW5500_cris_en, fW5500_cris_ex);

  uint8_t rx_tx_buff_sizes[] = {2, 2, 2, 2, 2, 2, 2, 2};
  if(wizchip_init(rx_tx_buff_sizes, rx_tx_buff_sizes) != 0) {
    return 1;
  }
  
  me->_init = true;
  me->Enable = true;
  
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvWiz850io_Run(sCdrvWiz850io * const me) {

  for(int i=0; i<8 ;i++) {

    if(Socket_Private[i].IsBusy) {

      fTcpServerRun(i);
    }

  }

}

/**
 * @brief 
 * 
 * @param me 
 * @param ipMode 
 * @param mac 
 * @param ip 
 * @param subnetMask 
 * @param gateway 
 * @param dns 
 * @return uint8_t 
 */
uint8_t fCdrvWiz850io_SetNetInfo(sCdrvWiz850io * const me, 
  eCdrvWiz850io_IpMode ipMode, 
  uint8_t *mac,
  uint8_t *ip,
  uint8_t *subnetMask,
  uint8_t *gateway,
  uint8_t *dns) {

  wiz_NetInfo netInfo;
	for(int i=0; i<6; i++) {
    netInfo.mac[i] = mac[i];
  }

  for(int i=0; i<4; i++) {
    netInfo.ip[i] = ip[i];
  }

  for(int i=0; i<4; i++) {
    netInfo.sn[i] = subnetMask[i];
  }

  for(int i=0; i<4; i++) {
    netInfo.gw[i] = gateway[i];
  }

  for(int i=0; i<4; i++) {
    netInfo.dns[i] = dns[i];
  }

  switch(ipMode) {

    case eIP_MODE_STATIC: {
      netInfo.dhcp = NETINFO_STATIC;
      break;
    }

    case eIP_MODE_DHCP: {
      netInfo.dhcp = NETINFO_DHCP;
      break;
    }

    default: {
      return 1;
    }
  }
  
  wizchip_setnetinfo(&netInfo);

  uint8_t *ptr = (uint8_t*)&netInfo;
  for(int i=0; i<sizeof(wiz_NetInfo); i++) {
    ptr[i] = 0;
  }

  wizchip_getnetinfo(&netInfo);
  
  //Compare
  switch(ipMode) {

    case eIP_MODE_STATIC: {
      if(netInfo.dhcp != NETINFO_STATIC) {
        return 1;
      }
      break;
    }

    case eIP_MODE_DHCP: {
      if(netInfo.dhcp != NETINFO_DHCP) {
        return 1;
      }
      break;
    }

    default: {
      return 1;
    }
  }

  for(int i=0; i<6; i++) {
    if(netInfo.mac[i] != mac[i]) {
      return 1;
    }
  }

  for(int i=0; i<4; i++) {
    if(netInfo.ip[i] != ip[i]) {
      return 1;
    }
  }

  for(int i=0; i<4; i++) {
    if(netInfo.sn[i] != subnetMask[i]) {
      return 1;
    }
  }

  for(int i=0; i<4; i++) {
    if(netInfo.gw[i] != gateway[i]) {
      return 1;
    }
  }

  for(int i=0; i<4; i++) {
    if(netInfo.dns[i] != dns[i]) {
      return 1;
    }
  }

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param socketNo 
 * @return sTcpServer* 
 */
sTcpServer* fCdrvWiz850io_CreateTcpServer(sCdrvWiz850io * const me, uint8_t socketNo, uint8_t *pBuffer, uint32_t bufferSize) {

  CHECK_INIT_(NULL);
  CHECK_ENABLE_(NULL);

  if(socketNo >= 8) {
    return NULL;
  }

  if(pBuffer == NULL) {
    return NULL;
  }

  if(bufferSize == 0) {
    return NULL;
  }
  
  static struct sTcpServerVtbl const vtbl = {
    Init,
    Listen,
    Stop,
    Send,
    IsSending,
    RegisterClientConnectedEvent,
    RegisterServerEvent,
    RegisterReceiveDataEvent
  };
  
  sTcpServer *s = (sTcpServer*)malloc(sizeof(sTcpServer));
  if(s == NULL) {
    return NULL;
  }
  
  s->_init = false;
  s->Enable = false;
  s->_vtbl = &vtbl;
  s->_device = me;
  s->_pvt = &(Socket_Private[socketNo]);
  
  Socket_Private[socketNo].pBuffer = pBuffer;
  Socket_Private[socketNo].BufferSize = bufferSize;
  Socket_Private[socketNo].pTcpServer = s;
  Socket_Private[socketNo].IsBusy = true;

  return s;  
}

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Private Functions #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/

static uint8_t Init(sTcpServer * const me) {

  return 0;
}

static uint8_t Listen(sTcpServer * const me, uint16_t port) {

  return 0;
}

static void Stop(sTcpServer * const me) {

}

static uint8_t Send(sTcpServer * const me, uint8_t *pData, uint16_t size) {

  sTcpServerPrivate *pvt = (sTcpServerPrivate*)me->_pvt;

  int32_t len = send(pvt->SocketNo, pData, size);
  
  if(len != size) {
    return 1;
  }

  return 0;
}

static bool IsSending(sTcpServer * const me) {

  sTcpServerPrivate *pvt = (sTcpServerPrivate*)me->_pvt;
  uint8_t tmp;
  
  if(sock_is_sending & (1<<(pvt->SocketNo))) {

    tmp = getSn_IR(pvt->SocketNo);
    if(tmp & Sn_IR_SENDOK) {
      setSn_IR(pvt->SocketNo, Sn_IR_SENDOK);
      sock_is_sending &= ~(1<<(pvt->SocketNo));
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

static uint8_t RegisterClientConnectedEvent(sTcpServer * const me, void(*fpCallback)(object sender, sTcpServerClientConnectedEventArgs *e)) {

  sTcpServerPrivate *pvt = (sTcpServerPrivate*)me->_pvt;

  pvt->fpClientConnectedEventCallback = fpCallback;

  return 0;
}

static uint8_t RegisterServerEvent(sTcpServer * const me, void(*fpCallback)(object sender, sTcpServerEventArgs *e)) {
  
  sTcpServerPrivate *pvt = (sTcpServerPrivate*)me->_pvt;

  pvt->fpServerEventCallback = fpCallback;

  return 0;
}

static uint8_t RegisterReceiveDataEvent(sTcpServer * const me, void(*fpCallback)(object sender, sTcpServerReceiveDataEventArgs *e)) {

  sTcpServerPrivate *pvt = (sTcpServerPrivate*)me->_pvt;

  pvt->fpReceiveDataEventCallback = fpCallback;

  return 0;
}

/**
 * @brief 
 * 
 */
static void fW5500_Select(void) {

  fGpio_Reset_(device->Cs);
}

/**
 * @brief 
 * 
 */
static void fW5500_Unselect(void) {

  fGpio_Set_(device->Cs);
}

/**
 * @brief 
 * 
 * @param buff 
 * @param len 
 */
static void fW5500_ReadBuff(uint8_t* buff, uint16_t len) {

  fSpi_Receive_(device->Spi, buff, len, device->SpiTimeoutMs);
}

/**
 * @brief 
 * 
 * @param buff 
 * @param len 
 */
static void fW5500_WriteBuff(uint8_t* buff, uint16_t len) {

    fSpi_Transmit_(device->Spi, buff, len, device->SpiTimeoutMs);
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
static uint8_t fW5500_ReadByte(void) {
  
  uint8_t byte;
  
  fW5500_ReadBuff(&byte, sizeof(byte));
  
  return byte;
}

/**
 * @brief 
 * 
 * @param byte 
 */
static void fW5500_WriteByte(uint8_t byte) {

  fW5500_WriteBuff(&byte, sizeof(byte));
}

/**
 * @brief 
 * 
 */
static void fW5500_cris_en(void) {
}

/**
 * @brief 
 * 
 */
static void fW5500_cris_ex(void) {
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static void fTcpServerRun(uint8_t sn) {

  sTcpServerPrivate *pvt = &(Socket_Private[sn]);

  uint8_t ret;
  uint16_t size = 0;
  uint8_t destip[4];
  uint16_t destport;

  switch(getSn_SR(sn)) {
    
    case SOCK_ESTABLISHED: {

      if(getSn_IR(sn) & Sn_IR_CON) {
          
        getSn_DIPR(sn, destip);
        destport = getSn_DPORT(sn);
        
        if(pvt->fpClientConnectedEventCallback != NULL) {

          sTcpServerClientConnectedEventArgs args;
          for(int i=0; i<6; i++) {
            args.ClientIP[i] = 0;
          }
          args.ClientIP[0] = destip[0];
          args.ClientIP[1] = destip[1];
          args.ClientIP[2] = destip[2];
          args.ClientIP[3] = destip[3];
          args.ClientPort = destport;

          pvt->fpClientConnectedEventCallback(pvt->pTcpServer, &args);
        }

        setSn_IR(sn,Sn_IR_CON);
      }
		 
      if((size = getSn_RX_RSR(sn)) > 0) {
        if(size > pvt->BufferSize) {
          size = pvt->BufferSize;
        }
        ret = recv(sn, pvt->pBuffer, size);

        if(ret > 0) {
          if(pvt->fpReceiveDataEventCallback != NULL) {

            sTcpServerReceiveDataEventArgs args;
            args.pData = pvt->pBuffer;
            args.Size = ret;

            pvt->fpReceiveDataEventCallback(pvt->pTcpServer, &args);
          }
        }
      }
      break;
    }
    
    case SOCK_CLOSE_WAIT: {

      ret = disconnect(sn);

      if(pvt->fpServerEventCallback != NULL) {

        sTcpServerEventArgs args;
        args.EventId = (ret == SOCK_OK) ? eTCP_SERVER_CLOSE : eTCP_SERVER_CLOSE_ERROR;
        
        pvt->fpServerEventCallback(pvt->pTcpServer, &args);
      }

      break;
    }
      
    case SOCK_INIT: {

      ret = listen(sn);

      if(pvt->fpServerEventCallback != NULL) {

        sTcpServerEventArgs args;
        args.EventId = (ret == SOCK_OK) ? eTCP_SERVER_LISTEN : eTCP_SERVER_LISTEN_ERROR;
        
        pvt->fpServerEventCallback(pvt->pTcpServer, &args);
      }

      break;
    }
    
    case SOCK_CLOSED: {

      ret = socket(sn, Sn_MR_TCP, pvt->Port, SF_IO_NONBLOCK);

      if(ret != sn) {

        if(pvt->fpServerEventCallback != NULL) {

          sTcpServerEventArgs args;
          args.EventId = eTCP_SERVER_INIT_ERROR;
        
          pvt->fpServerEventCallback(pvt->pTcpServer, &args);
        }
      }

      break;
    }

    default: {
      break;
    }
  }
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
