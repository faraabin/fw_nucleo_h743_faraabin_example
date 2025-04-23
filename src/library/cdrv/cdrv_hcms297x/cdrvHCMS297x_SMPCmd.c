/**
 ******************************************************************************
 *  @file 			cdrvHCMS297x_SMPCmd.c
 *  @brief 			
 *  @details 		
 *  @author 		Adel Ghaderan
 *  @version 		1.0.0
 *  @date 			1394/12/01
 *  @pre 				
 *  @bug 				
 *  @warning 		
 *  @copyright 	GNU Public License.
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 ==============================================================================
                    ##### -------- features #####
 ==============================================================================         
 


									##### How to use -------- #####
 ==============================================================================  
 


 ******************************************************************************
 @verbatim
 @endverbatim
*/
 
/* Includes ------------------------------------------------------------------*/
#include "cdrvHCMS297x_SMPCmd.h"
#include "cdrvHCMS297x.h"
#include "device.h"
#include "stdio.h"
#include "string.h"
#include "modGPTimer.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__Mod_Create_GPTimer_Object(vSPI_Test_Timer);
__Cdrv_Create_HCMS297x_Object(testDISPLAY);

/* Private function prototypes -----------------------------------------------*/
static void fCdrv_HCMS297x_SMPCmd_Init(void);
	
static void af_Cdrv_HCMS297x_SMPCmd_MRAM_Print (uint8_t *pvPar);
static void af_Cdrv_HCMS297x_SMPCmd_MRAM_Clear (uint8_t *pvPar);
static void af_Cdrv_HCMS297x_SMPCmd_MRAM_Contrast (uint8_t *pvPar);
static void af_Cdrv_HCMS297x_SMPCmd_MRAM_Blank_Enable (uint8_t *pvPar);
static void af_Cdrv_HCMS297x_SMPCmd_MRAM_Blank_Disable (uint8_t *pvPar);

extern void SPI_Transmit_Poll(uint8_t* pvBytes, uint16_t vSize);
/* Variables -----------------------------------------------------------------*/
__Cdrv_Create_HCMS297x_SMPCmd_API_Object(aCdrv_HCMS297x_SMPCmd) = 
{
	fCdrv_HCMS297x_SMPCmd_Init
};

/* Private functions ---------------------------------------------------------*/
uint8_t buffer[1000];
void testDISPLAY_Select(void)
{
    DisplaySel_Write(0);
}
void testDISPLAY_Deselect(void)
{
	DisplaySel_Write(1);
}
void testDISPLAY_BL_SET(void)
{
	DisplayBl_Write(1);
}
void testDISPLAY_BL_RESET(void)
{
	DisplayBl_Write(0);
}
void testDISPLAY_RST_SET(void)
{
	DisplayRst_Write(1);
}
void testDISPLAY_RST_RESET(void)
{
	DisplayRst_Write(0);
}
void testDISPLAY_RS_SET(void)
{
	DisplayRs_Write(1);
}
void testDISPLAY_RS_RESET(void)
{
    DisplayRs_Write(0);
}

uint8_t testDISPLAY_SPI_IsReady(void)
{
	if(1/*aPdrv_SPI4.pfIsReady() == eSPI_OK*/)
	{
		return(1);
	}
	return(0);
}
uint8_t testDISPLAY_SPI_Transmit(uint8_t *pvTxData, uint16_t vQty)
{
	SPI_Transmit_Poll(pvTxData, vQty);
	
    return(1);
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static void af_Cdrv_HCMS297x_SMPCmd_MRAM_Print (uint8_t *pvPar)
{
	char vStr[20];
	unsigned int vOffset;
	uint16_t i = 0;
	uint8_t vSize;
	
	for(i=0; i<strlen((char*)pvPar); i++)
	{
		if(pvPar[i] == ',')
		{
			pvPar[i] = ' ';
		}
	}
	
	if(sscanf((char*)pvPar, "%s %u", vStr, &vOffset) == 2)
	{
		vSize = strlen(vStr);
		if(vSize > 8)
		{
			vSize = 8;
		}
		
		if(aCdrv_HCMS297x.pfPrint(&testDISPLAY, (uint8_t*)vStr, vSize, vOffset) == 0)
		{
			sprintf((char*)svSMP_TempStr, "\nERROR");
			aMod_SMP.pfSerialSend(svSMP_TempStr, strlen((char *)svSMP_TempStr));
		}
	}
	else
	{
		sprintf((char*)svSMP_TempStr, "\nError Parameter Qty");
		aMod_SMP.pfSerialSend(svSMP_TempStr, strlen((char *)svSMP_TempStr));
	}
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static void af_Cdrv_HCMS297x_SMPCmd_MRAM_Clear (uint8_t *pvPar)
{
	aCdrv_HCMS297x.pfClear(&testDISPLAY);
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static void af_Cdrv_HCMS297x_SMPCmd_MRAM_Contrast (uint8_t *pvPar)
{
	unsigned int vContrast;
	uint16_t i = 0;
	
	for(i=0; i<strlen((char*)pvPar); i++)
	{
		if(pvPar[i] == ',')
		{
			pvPar[i] = ' ';
		}
	}
	
	if(sscanf((char*)pvPar, "%u", &vContrast) == 1)
	{
		aCdrv_HCMS297x.pfSetContrast(&testDISPLAY, vContrast);
	}
	else
	{
		sprintf((char*)svSMP_TempStr, "\nError Parameter Qty");
		aMod_SMP.pfSerialSend(svSMP_TempStr, strlen((char *)svSMP_TempStr));
	}
}
	
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static void af_Cdrv_HCMS297x_SMPCmd_MRAM_Blank_Enable (uint8_t *pvPar)
{
	aCdrv_HCMS297x.pfBlank_Enable(&testDISPLAY);
}
	
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
static void af_Cdrv_HCMS297x_SMPCmd_MRAM_Blank_Disable (uint8_t *pvPar)
{
	aCdrv_HCMS297x.pfBlank_Disable(&testDISPLAY);
}

/*
===============================================================================
                       ##### ---------- functions #####
===============================================================================*/
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
void fCdrv_HCMS297x_SMPCmd_Init(void)
{	
	aCdrv_HCMS297x.pfStruct_Init(&testDISPLAY);
	testDISPLAY.pfSelect 				= testDISPLAY_Select;
	testDISPLAY.pfDeselect 			= testDISPLAY_Deselect;
	testDISPLAY.pfBL_SET 				= testDISPLAY_BL_SET;
	testDISPLAY.pfBL_RESET 			= testDISPLAY_BL_RESET;
	testDISPLAY.pfRST_SET 			= testDISPLAY_RST_SET;
	testDISPLAY.pfRST_RESET 		= testDISPLAY_RST_RESET;
	testDISPLAY.pfRS_SET 				= testDISPLAY_RS_SET;
	testDISPLAY.pfRS_RESET 			= testDISPLAY_RS_RESET;
	testDISPLAY.pfSPI_IsReady 	= testDISPLAY_SPI_IsReady;
	testDISPLAY.pfSPI_Transmit	= testDISPLAY_SPI_Transmit;
	aCdrv_HCMS297x.pfInit(&testDISPLAY);
	
	aMod_SMP.pfAddCommand((uint8_t*)"DISPLAY", (uint8_t*)"PRINT"/*Command Text*/, 		af_Cdrv_HCMS297x_SMPCmd_MRAM_Print,  				(uint8_t*)""/*Command Help Text*/);
	aMod_SMP.pfAddCommand((uint8_t*)"DISPLAY", (uint8_t*)"CLEAR"/*Command Text*/, 		af_Cdrv_HCMS297x_SMPCmd_MRAM_Clear,  				(uint8_t*)""/*Command Help Text*/);
	aMod_SMP.pfAddCommand((uint8_t*)"DISPLAY", (uint8_t*)"CONTRAST"/*Command Text*/, 	af_Cdrv_HCMS297x_SMPCmd_MRAM_Contrast,  		(uint8_t*)""/*Command Help Text*/);
	aMod_SMP.pfAddCommand((uint8_t*)"DISPLAY", (uint8_t*)"BL_EN"/*Command Text*/, 		af_Cdrv_HCMS297x_SMPCmd_MRAM_Blank_Enable,  (uint8_t*)""/*Command Help Text*/);
	aMod_SMP.pfAddCommand((uint8_t*)"DISPLAY", (uint8_t*)"BL_DIS"/*Command Text*/, 		af_Cdrv_HCMS297x_SMPCmd_MRAM_Blank_Disable, (uint8_t*)""/*Command Help Text*/);
}

/**End of Group_Name
  * @}
  */

/********************************* END OF FILE ********************************/
