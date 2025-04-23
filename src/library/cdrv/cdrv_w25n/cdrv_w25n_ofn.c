/**
 ******************************************************************************
 *  @file         cdrv_w25n_ocmd.c
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
#include "cdrv_w25n_ocmd.h"

#include "cdrv_w25n.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(TysCdrvW25Nxx_Obj);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
static TysChrono_Obj chrono_elapsed;

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
meCONSOLE_CMD_(cdrv_w25n, BEGIN,
"type cmd help here") {
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_begin(me);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  }
  
  mePRINTF_("\r\n(%f us)0x%X-0x%X-0x%X", elapsed, me->rx_buffer[2], me->rx_buffer[3], me->rx_buffer[4]);
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, RESET,
"type cmd help here") {
  
  meChrono_Start(&chrono_elapsed);
  w25n_reset(me);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  mePRINTF_("\r\n(%f us)", elapsed);
	
	meCONSOLE_END_;
}
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, RESET_BN,
"type cmd help here") {
  
  meChrono_Start(&chrono_elapsed);
  w25n_reset(me);
  int bn_res = w25n_block_WIP(me, 1000);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  mePRINTF_("\r\n(%f us) - %s", elapsed, (bn_res == 0) ? "OK" : "TIMEOUT");
  
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, DIE_SELECT,
"type cmd help here") {
  
  int die;
  meCONSOLE_GET_PAR_(1, "%u", &die);
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_dieSelect(me, die);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us)", elapsed);
    
  }
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, DIE_SELECT_ON_ADDR,
"type cmd help here") {
  
  int page_addr;
  meCONSOLE_GET_PAR_(1, "%u", &page_addr);
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_dieSelectOnAdd(me, page_addr);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us)", elapsed);
    
  }
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, GET_STATUS,
"type cmd help here") {
  
  int reg;
  meCONSOLE_GET_PAR_(1, "%u", &reg);
  
  meChrono_Start(&chrono_elapsed);
  int val = w25n_getStatusReg(me, reg);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  mePRINTF_("\r\n(%f us)Reg(%u) = %u", elapsed, reg, val);
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, SET_STATUS,
"type cmd help here") {
  
  int reg, value;
  meCONSOLE_GET_PAR_(2, "%u %u", &reg, &value);
  
  meChrono_Start(&chrono_elapsed);
  w25n_setStatusReg(me, reg, value);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  mePRINTF_("\r\n(%f us)Reg(%u) = %u", elapsed, reg, w25n_getStatusReg(me, reg));
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, GET_MAX_PAGE,
"type cmd help here") {
  
  meChrono_Start(&chrono_elapsed);
  int val = w25n_getMaxPage(me);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  mePRINTF_("\r\n(%f us)MaxPage = %u", elapsed, val);
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, WRITE_ENABLE,
"type cmd help here") {
  
  meChrono_Start(&chrono_elapsed);
  w25n_writeEnable(me);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  mePRINTF_("\r\n(%f us)", elapsed);
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, WRITE_DISABLE,
"type cmd help here") {
  
  meChrono_Start(&chrono_elapsed);
  w25n_writeDisable(me);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  mePRINTF_("\r\n(%f us)", elapsed);
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, BLOCK_ERASE,
"type cmd help here") {
  
  int addr;
  meCONSOLE_GET_PAR_(1, "%u", &addr);
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_blockErase(me, addr);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us)", elapsed);
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, BLOCK_ERASE_BN,
"type cmd help here") {
  
  int addr;
  meCONSOLE_GET_PAR_(1, "%u", &addr);
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_blockErase(me, addr);
  int bn_res = w25n_block_WIP(me, 1000);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us) - %s", elapsed, (bn_res == 0) ? "OK" : "TIMEOUT");
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, BULK_ERASE,
"type cmd help here") {
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_bulkErase(me);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us)", elapsed);
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, BULK_ERASE_BN,
"type cmd help here") {
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_bulkErase(me);
  int bn_res = w25n_block_WIP(me, 60000);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us) - %s", elapsed, (bn_res == 0) ? "OK" : "TIMEOUT");
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, WRITE_TO_INTERNAL_BUFFER,
"type cmd help here") {
  
  int columnAddr, dataLen;
  meCONSOLE_GET_PAR_(2, "%u %u", &columnAddr, &dataLen);
  uint8_t buf[2100];
  
  if(dataLen > 2048) {
    mePRINTF_("\r\nERROR dataLen");
    return 1;
  }
  
  for(int i=0; i<dataLen; i++) {
    buf[i] = i;
  }
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_writeToInternalBuffer(me, columnAddr, buf, dataLen);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us)", elapsed);
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, WRITE_TO_INTERNAL_BUFFER_BN,
"type cmd help here") {
  
  int columnAddr, dataLen;
  meCONSOLE_GET_PAR_(2, "%u %u", &columnAddr, &dataLen);
  uint8_t buf[2100];
  
  if(dataLen > 2048) {
    mePRINTF_("\r\nERROR dataLen");
    return 1;
  }
  
  for(int i=0; i<dataLen; i++) {
    buf[i] = i;
  }
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_writeToInternalBuffer(me, columnAddr, buf, dataLen);
  int bn_res = w25n_block_WIP(me, 1000);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us) - %s", elapsed, (bn_res == 0) ? "OK" : "TIMEOUT");
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, VERIFY_BY_INTERNAL_BUFFER,
"type cmd help here") {
  
  int columnAddr, dataLen;
  meCONSOLE_GET_PAR_(2, "%u %u", &columnAddr, &dataLen);
  uint8_t buf[2100];
  
  if(dataLen > 2048) {
    mePRINTF_("\r\nERROR dataLen");
    return 1;
  }
  
  for(int i=0; i<dataLen; i++) {
    buf[i] = i;
  }
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_verifyByInternalBuffer(me, columnAddr, buf, dataLen);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us)", elapsed);
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, WRITE_INTERNAL_BUFFER_TO_PAGE,
"type cmd help here") {
  
  int pageAddr;
  meCONSOLE_GET_PAR_(1, "%u", &pageAddr);
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_writeInternalBufferToPage(me, pageAddr);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us)", elapsed);
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, WRITE_INTERNAL_BUFFER_TO_PAGE_BN,
"type cmd help here") {
  
  int pageAddr;
  meCONSOLE_GET_PAR_(1, "%u", &pageAddr);
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_writeInternalBufferToPage(me, pageAddr);
  int bn_res = w25n_block_WIP(me, 1000);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us) - %s", elapsed, (bn_res == 0) ? "OK" : "TIMEOUT");
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, READ_PAGE_TO_INTERNAL_BUFFER,
"type cmd help here") {
  
  int pageAddr;
  meCONSOLE_GET_PAR_(1, "%u", &pageAddr);
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_readPageToInternalBuffer(me, pageAddr);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us)", elapsed);
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, READ_PAGE_TO_INTERNAL_BUFFER_BN,
"type cmd help here") {
  
  int pageAddr;
  meCONSOLE_GET_PAR_(1, "%u", &pageAddr);
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_readPageToInternalBuffer(me, pageAddr);
  int bn_res = w25n_block_WIP(me, 1000);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us) - %s", elapsed, (bn_res == 0) ? "OK" : "TIMEOUT");
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, READ_INTERNAL_BUFFER,
"type cmd help here") {
  
  int columnAddr, dataLen;
  meCONSOLE_GET_PAR_(2, "%u %u", &columnAddr, &dataLen);
  uint8_t buf[2100];
  
  if(dataLen > 2048) {
    mePRINTF_("\r\nERROR dataLen");
    return 1;
  }
  
  for(int i=0; i<2100; i++) {
    buf[i] = 0;
  }
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_readInternalBuffer(me, columnAddr, buf, dataLen);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us)", elapsed);
    
  }
  
  for(int i=0; i<dataLen; i++) {
    mePRINTF_("\r\n%u", buf[i]);
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, READ_INTERNAL_BUFFER_BN,
"type cmd help here") {
  
  int columnAddr, dataLen;
  meCONSOLE_GET_PAR_(2, "%u %u", &columnAddr, &dataLen);
  uint8_t buf[2100];
  
  if(dataLen > 2048) {
    mePRINTF_("\r\nERROR dataLen");
    return 1;
  }
  
  for(int i=0; i<2100; i++) {
    buf[i] = 0;
  }
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_readInternalBuffer(me, columnAddr, buf, dataLen);
  int bn_res = w25n_block_WIP(me, 1000);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us) - %s", elapsed, (bn_res == 0) ? "OK" : "TIMEOUT");
    
  }
  
  for(int i=0; i<dataLen; i++) {
    mePRINTF_("\r\n%u", buf[i]);
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, CHECK_WIP,
"type cmd help here") {
  
  meChrono_Start(&chrono_elapsed);
  int val = w25n_check_WIP(me);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  mePRINTF_("\r\n(%f us)%u", elapsed, val);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, BLOCK_WIP,
"type cmd help here") {
  
  int timeout_ms = 10;
  meCONSOLE_GET_PAR_(1, "%u", &timeout_ms);
  
  meChrono_Start(&chrono_elapsed);
  int val = w25n_block_WIP(me, timeout_ms);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  mePRINTF_("\r\n(%f us)%u", elapsed, val);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, CHECK_STATUS,
"type cmd help here") {
  
  meChrono_Start(&chrono_elapsed);
  int val = w25n_check_status(me);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  mePRINTF_("\r\n(%f us)%u", elapsed, val);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, WRITE_PAGE_BN,
"type cmd help here") {
  
  int pageAddr, value;
  meCONSOLE_GET_PAR_(2, "%u %u", &pageAddr, &value);
  uint8_t buf[2100];
  
  int dataLen = 2048;
  
  if(dataLen > 2048) {
    mePRINTF_("\r\nERROR dataLen");
    return 1;
  }
  
  for(int i=0; i<dataLen; i++) {
    buf[i] = value;
  }
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_write_page(me, 0, buf, dataLen, pageAddr);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us) - OK", elapsed);
    
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_w25n, READ_PAGE_BN,
"type cmd help here") {
  
  int pageAddr, columnAddr, dataLen;
  meCONSOLE_GET_PAR_(3, "%u %u %u", &pageAddr, &columnAddr, &dataLen);
  uint8_t buf[2100];
  
  if(dataLen > 2048) {
    mePRINTF_("\r\nERROR dataLen");
    return 1;
  }
  
  for(int i=0; i<2100; i++) {
    buf[i] = 0;
  }
  
  meChrono_Start(&chrono_elapsed);
  int res = w25n_read_page(me, columnAddr, buf, dataLen, pageAddr);
  float elapsed = meChrono_us_fElapsed(&chrono_elapsed);
  
  if(res != 0) {
    
    mePRINTF_("\r\nERROR");
    return 1;
  } else {
    
    mePRINTF_("\r\n(%f us) - OK", elapsed);
    
  }
  
  for(int i=0; i<dataLen; i++) {
    mePRINTF_("\r\n%u", buf[i]);
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static uint8_t buffer[2048];
meCONSOLE_CMD_(cdrv_w25n, TEST_WRITE_VERIFY,
"type cmd help here") {
  
  int res = 0;
  uint32_t page_index = 0;
  
  if(w25n_bulkErase(me) != 0) {
    
    mePRINTF_NOW_("\r\nBulk Erase ERROR");
    return 1;
  }
  
  if(w25n_block_WIP(me, 60000) != 0) {
    
    mePRINTF_NOW_("\r\nBulk Erase WIP ERROR");
    return 1;
  }
  
  mePRINTF_NOW_("\r\nErase OK");
  
  meCONSOLE_LOOP_(5) {
    
    for(int i=0; i<2048; i++) {
      buffer[i] = (i%0xFF) + page_index;
    }
    
    meChrono_Start(&chrono_elapsed);
    res = w25n_write_page(me, 0, buffer, 2048, page_index);
    float elapsed_write = meChrono_us_fElapsed(&chrono_elapsed);
    if(res != 0) {
      mePRINTF_NOW_("\r\nWrite ERROR");
      return 1;
    }
    
    meChrono_Start(&chrono_elapsed);
    res = w25n_verify_page(me, 0, buffer, 2048, page_index);
    float elapsed_verify = meChrono_us_fElapsed(&chrono_elapsed);
    if(res != 0) {
      mePRINTF_NOW_("\r\nVerify ERROR");
      return 1;
    }
    
    meRUN_EVERY_QTY_(printf, 20) {
      mePRINTF_NOW_("\r\nOK[Page : %u/w:%f us/v:%f us]", page_index, elapsed_write, elapsed_verify);
      meRUN_EVERY_END_;
    }
    
    page_index++;
    if(page_index >= w25n_getMaxPage(me)) {
      mePRINTF_NOW_("\r\nEND");
      return 0;
    }
    
    meCONSOLE_LOOP_END_;
  }
    
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
meCONSOLE_GROUP_(cdrv_w25n,
"type cmd help here") {

	meCONSOLE_ADD_CMD_(cdrv_w25n, BEGIN, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, RESET, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, RESET_BN, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, DIE_SELECT, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, DIE_SELECT_ON_ADDR, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, GET_STATUS, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, SET_STATUS, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, GET_MAX_PAGE, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, WRITE_ENABLE, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, WRITE_DISABLE, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, BLOCK_ERASE, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, BLOCK_ERASE_BN, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, BULK_ERASE, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, BULK_ERASE_BN, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, WRITE_TO_INTERNAL_BUFFER, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, WRITE_TO_INTERNAL_BUFFER_BN, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, VERIFY_BY_INTERNAL_BUFFER, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, WRITE_INTERNAL_BUFFER_TO_PAGE, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, WRITE_INTERNAL_BUFFER_TO_PAGE_BN, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, READ_PAGE_TO_INTERNAL_BUFFER, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, READ_PAGE_TO_INTERNAL_BUFFER_BN, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, READ_INTERNAL_BUFFER, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, READ_INTERNAL_BUFFER_BN, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, CHECK_WIP, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, BLOCK_WIP, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, CHECK_STATUS, 0);
  
  meCONSOLE_ADD_CMD_(cdrv_w25n, WRITE_PAGE_BN, 0);
  meCONSOLE_ADD_CMD_(cdrv_w25n, READ_PAGE_BN, 0);
  
  meCONSOLE_ADD_CMD_(cdrv_w25n, TEST_WRITE_VERIFY, 0);
  
  meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/
