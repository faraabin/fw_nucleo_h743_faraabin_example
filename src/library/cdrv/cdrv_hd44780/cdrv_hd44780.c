/**
******************************************************************************
* @file           : cdrv_hd44780.c
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
#include "cdrv_hd44780.h"
#include "library\chrono\me_chrono.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define HD44780_ASSERT_NOT_NULL_RET_(obj_) \
if(obj_ == NULL) {\
  return 1;\
}

#define HD44780_InitGpioDo_(obj_) \
do {\
  obj_->u_dir = eGPIO_DIR_OUTPUT;\
  obj_->u_out_type = eGPIO_PUSH_PULL;\
  meGpio_Init_(obj_);\
}while(0)

#define HD44780_InitGpioDi_(obj_) \
do {\
  obj_->u_dir = eGPIO_DIR_INPUT;\
  obj_->u_in_type = eGPIO_PULL_UP;\
  meGpio_Init_(obj_);\
}while(0)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void HD44780_CheckBFin8bitMode(sCdrvHd44780Obj * const me);
static void HD44780_CheckBFin4bitMode(sCdrvHd44780Obj * const me);
static void HD44780_SendInstruction(sCdrvHd44780Obj * const me, unsigned short int);
static void HD44780_SendData(sCdrvHd44780Obj * const me, unsigned short int);
static void HD44780_Send4bitsIn4bitMode(sCdrvHd44780Obj * const me, unsigned short int);
static void HD44780_Send8bitsIn4bitMode(sCdrvHd44780Obj * const me, unsigned short int);
static void HD44780_Send8bitsIn8bitMode(sCdrvHd44780Obj * const me, unsigned short int);
static void HD44780_SetUppNibble(sCdrvHd44780Obj * const me, unsigned short int);
static void HD44780_SetLowNibble(sCdrvHd44780Obj * const me, unsigned short int);
static void HD44780_PulseE(sCdrvHd44780Obj * const me);
static void HD44780_SetPORT_DATA4to7(sCdrvHd44780Obj * const me);
static void HD44780_SetDDR_DATA4to7(sCdrvHd44780Obj * const me);
static void HD44780_ClearDDR_DATA4to7(sCdrvHd44780Obj * const me);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                ##### cdrv_hd44780.c Exported Functions #####
===============================================================================*/
// +---------------------------+
// |         Power on          |
// | Wait for more than 15 ms  |   // 15 ms wait
// | after VCC rises to 4.5 V  |
// +---------------------------+
//              |
// +---------------------------+ 
// |  RS R/W DB7 DB6 DB5 DB4   |   
// |   0   0   0   0   1   1   |   // Initial sequence 0x30
// | Wait for more than 4.1 ms |   // 4.1 ms us writing DATA into DDRAM or CGRAM
// +---------------------------+
//              |
// +---------------------------+
// |  RS R/W DB7 DB6 DB5 DB4   |   
// |   0   0   0   0   1   1   |   // Initial sequence 0x30
// | Wait for more than 0.1 ms |   // 100 us writing DATA into DDRAM or CGRAM
// +---------------------------+
//              |
// +---------------------------+
// |  RS R/W DB7 DB6 DB5 DB4   |   // Initial sequence 0x30
// |   0   0   0   0   1   1   |   // 37 us writing DATA into DDRAM or CGRAM 4 us tadd - time after busy flag disapeared
// | Wait for more than 45 us  |   // 37 us + 4 us = 41 us * (270/250) = 45us
// +---------------------------+  
//              |
// +---------------------------+   // 4bit mode 0x20 !!! MUST BE SET TIME, BF CHECK DOESN'T WORK CORRECTLY !!!
// |  RS R/W DB7 DB6 DB5 DB4   |   // 
// |   0   0   0   0   1   0   |   // 37 us writing DATA into DDRAM or CGRAM 4 us tadd - time after busy flag disapeared
// | Wait for more than 45 us  |   // !!! MUST BE SET DELAY TIME, BUSY FLAG CHECK DOESN'T WORK CORRECTLY !!!
// +---------------------------+
//              |
// +---------------------------+
// |  RS R/W DB7 DB6 DB5 DB4   |   // Display off 0x08
// |   0   0   0   0   1   0   |   // 
// |   0   0   1   0   0   0   |   // 
// |    Wait for BF Cleared    |   // Wait for BF Cleared
// +---------------------------+
//              |
// +---------------------------+
// |  RS R/W DB7 DB6 DB5 DB4   |   // Display clear 0x01
// |   0   0   0   0   0   0   |   //
// |   0   0   0   0   0   1   |   //
// |    Wait for BF Cleared    |   // Wait for BF Cleared
// +---------------------------+
//              |
// +---------------------------+
// |  RS R/W DB7 DB6 DB5 DB4   |   // Entry mode set 0x06
// |   0   0   0   0   0   0   |   // 
// |   0   0   0   1   1   0   |   // shift cursor to the left, without text shifting
// |    Wait for BF Cleared    |   // Wait for BF Cleared
// +---------------------------+

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t fCdrvHD44780_Init(sCdrvHd44780Obj * const me) {
  me->init = false;
	
	HD44780_ASSERT_NOT_NULL_RET_(me->EnPin);
  HD44780_ASSERT_NOT_NULL_RET_(me->RsPin);
  HD44780_ASSERT_NOT_NULL_RET_(me->RwPin);
  HD44780_ASSERT_NOT_NULL_RET_(me->Db7Pin);
  HD44780_ASSERT_NOT_NULL_RET_(me->Db6Pin);
  HD44780_ASSERT_NOT_NULL_RET_(me->Db5Pin);
  HD44780_ASSERT_NOT_NULL_RET_(me->Db4Pin);
	
	// set E as output
	HD44780_InitGpioDo_(me->EnPin);
	// set RS as output
  HD44780_InitGpioDo_(me->RsPin);
	// set RW as output
  HD44780_InitGpioDo_(me->RwPin);
	// set DB7-DB4 as output
	HD44780_SetDDR_DATA4to7(me);
  
	meGpio_Reset_(me->RsPin);
	meGpio_Reset_(me->RwPin);
	meGpio_Reset_(me->EnPin);

  // delay > 15ms
  meDelay_ms_(16);

  // Busy Flag (BF) cannot be checked in these instructions
  // ---------------------------------------------------------------------
  // Initial sequence 0x30 - send 4 bits in 4 bit mode
  HD44780_SendInstruction(me, HD44780_INIT_SEQ);
  // delay > 4.1ms
  meDelay_ms_(5);

  // pulse E
  HD44780_PulseE(me);
  // delay > 100us
  meDelay_us_(110);

  // pulse E
  HD44780_PulseE(me);
  // delay > 45us (=37+4 * 270/250)
  meDelay_us_(50);

  // 4 bit mode 0x20 - send 4 bits in 4 bit mode
  HD44780_Send4bitsIn4bitMode(me, HD44780_4BIT_MODE);
  // pulse E
  HD44780_PulseE(me);
  // delay > 45us (=37+4 * 270/250)
  meDelay_us_(50);
  // ----------------------------------------------------------------------
  
  // 4-bit & 2-lines & 5x8-dots 0x28 - send 8 bits in 4 bit mode
  HD44780_SendInstruction(me, HD44780_4BIT_MODE | HD44780_2_ROWS | HD44780_FONT_5x8);

  // display off 0x08 - send 8 bits in 4 bit mode
  HD44780_SendInstruction(me, HD44780_DISP_OFF);

  // display clear 0x01 - send 8 bits in 4 bit mode
  HD44780_SendInstruction(me, HD44780_DISP_CLEAR);

  // entry mode set 0x06 - send 8 bits in 4 bit mode
  HD44780_SendInstruction(me, HD44780_ENTRY_MODE);

  me->init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvHD44780_DisplayClear(sCdrvHd44780Obj * const me) {
  // Diplay clear
  HD44780_SendInstruction(me, HD44780_DISP_CLEAR);
	meDelay_ms_(100);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvHD44780_DisplayOn(sCdrvHd44780Obj * const me) {
  // send instruction - display on
  HD44780_SendInstruction(me, HD44780_DISP_ON);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvHD44780_CursorOn(sCdrvHd44780Obj * const me) {
  // send instruction - cursor on
  HD44780_SendInstruction(me, HD44780_CURSOR_ON);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvHD44780_CursorOff(sCdrvHd44780Obj * const me) {
  // send instruction - cursor on
  HD44780_SendInstruction(me, HD44780_CURSOR_OFF);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvHD44780_CursorBlink(sCdrvHd44780Obj * const me) {
  // send instruction - Cursor blink
  HD44780_SendInstruction(me, HD44780_CURSOR_BLINK);
}

/**
 * @brief 
 * 
 * @param me 
 * @param character 
 */
void fCdrvHD44780_DrawChar(sCdrvHd44780Obj * const me, char character) {
  // Diplay clear
  HD44780_SendData(me, character);
}

/**
 * @brief 
 * 
 * @param me 
 * @param str 
 */
void fCdrvHD44780_DrawString(sCdrvHd44780Obj * const me, char *str){
  unsigned char i = 0;
  // loop through 5 bytes
  while (str[i] != '\0') {
    //read characters and increment index
    HD44780_SendData(me, str[i++]);
  }
}

/**
 * @brief 
 * 
 * @param me 
 * @param x 
 * @param y 
 * @return char 
 */
char fCdrvHD44780_PositionXY(sCdrvHd44780Obj * const me, char x, char y) {
  if (x > HD44780_COLS || y > HD44780_ROWS) {
    // error
    return 1;
  }
  // check which row
  if (y == 0) {
    // send instruction 1st row
    HD44780_SendInstruction(me, HD44780_POSITION | (HD44780_ROW1_START + x));
  } else if (y == 1) {
    // send instruction 2nd row
    HD44780_SendInstruction(me, HD44780_POSITION | (HD44780_ROW2_START + x));
  }
  // success
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param item 
 * @param direction 
 * @return char 
 */
char fCdrvHD44780_Shift(sCdrvHd44780Obj * const me, char item, char direction) {
  // check if item is cursor or display or direction is left or right
  if ((item != HD44780_DISPLAY) && (item != HD44780_CURSOR)) {
    // error
    return 1;
  }
  // check if direction is left or right
  if ((direction != HD44780_RIGHT) && (direction != HD44780_LEFT)) {
    // error
    return 1;
  }

  // cursor shift
  if (item == HD44780_CURSOR) {
    // right shift
    if (direction == HD44780_RIGHT) {
      // shit cursor / display to right / left
      HD44780_SendInstruction(me, HD44780_SHIFT | HD44780_CURSOR | HD44780_RIGHT);
    } else {
      // shit cursor / display to right / left
      HD44780_SendInstruction(me, HD44780_SHIFT | HD44780_CURSOR | HD44780_LEFT);
    }
  // display shift
  } else {
    // right shift
    if (direction == HD44780_RIGHT) {
      // shit cursor / display to right / left
      HD44780_SendInstruction(me, HD44780_SHIFT | HD44780_DISPLAY | HD44780_RIGHT);
    } else {
      // shit cursor / display to right / left
      HD44780_SendInstruction(me, HD44780_SHIFT | HD44780_DISPLAY | HD44780_LEFT);
    }
  }
  // success
  return 0;
}

/*
===============================================================================
                ##### cdrv_hd44780.c Private Functions #####
===============================================================================*/
/**
 * @desc    Check Busy Flag (BF) in 4 bit mode
 *
 * @param   void
 *
 * @return  void
 */
static void HD44780_CheckBFin4bitMode(sCdrvHd44780Obj * const me)
{
  unsigned char input = 0;

  // clear DB7-DB4 as input
  HD44780_ClearDDR_DATA4to7(me);
  // set pull-up resistors for DB7-DB4 
  HD44780_SetPORT_DATA4to7(me);
	
	meGpio_Reset_(me->RsPin);
	meGpio_Set_(me->RwPin);

  // test HIGH level on PIN DB7
  // after clear PIN DB7 should continue
  // -------------------------------------
  //  us:     0.5|0.5|0.5
  //          ___     ___
  //   E: ___/   \___/   \__
  //           ___     ___
  // DB7: \___/   \___/   \__
  //
  while (1) {

    // Read upper nibble
    // --------------------------------
    // Set E
		meGpio_Set_(me->EnPin);
    // PWeh > 0.5us
    meDelay_us_(1);
    // read upper nibble (tDDR > 360ns)
		uint8_t tmp = 0;
		meGpio_Read_(me->Db4Pin, &tmp);
		input |= (tmp << 4);
		meGpio_Read_(me->Db5Pin, &tmp);
		input |= (tmp << 5);
		meGpio_Read_(me->Db6Pin, &tmp);
		input |= (tmp << 6);
		meGpio_Read_(me->Db7Pin, &tmp);
		input |= (tmp << 7);
		
    // Clear E
		meGpio_Reset_(me->EnPin);
    // TcycE > 1000ns -> delay depends on PWeh delay time
    // delay = TcycE - PWeh = 1000 - 500 = 500ns
    meDelay_us_(1);

    // Read lower nibble
    // --------------------------------
    // Set E
		meGpio_Set_(me->EnPin);
    // PWeh > 0.5us
    meDelay_us_(1);
    // read lower nibble (tDDR > 360ns)
//    input |= HD44780_PIN_DATA >> 4;
    // Clear E
		meGpio_Reset_(me->EnPin);
    // TcycE > 1000ns -> delay depends on PWeh delay time
    // delay = TcycE - PWeh = 1000 - 500 = 500ns
		meDelay_us_(1);
    // check if DB7 is cleared
//    if (!(input & (1 << HD44780_DATA7))) {
		meGpio_Read_(me->Db7Pin, &tmp);
		if (!((tmp >> 7) & 0xFF)) {
      // if BF cleared -> end loop
      break;
    }
  }

  // clear RW
	meGpio_Reset_(me->RwPin);

  // set DB7-DB4 as output
  HD44780_SetDDR_DATA4to7(me);
}

/**
 * @desc    Check Busy Flag (BF) in 8 bit mode
 *
 * @param   void
 * @return  void
 */
static void HD44780_CheckBFin8bitMode(sCdrvHd44780Obj * const me)
{
	
}

/**
 * @desc    LCD send instruction
 *
 * @param   unsigned short int 
 *
 * @return  void
 */
static void HD44780_SendInstruction(sCdrvHd44780Obj * const me, unsigned short int data)
{
  // Clear RS
	meGpio_Reset_(me->RsPin);

  // 4bit mode
  // ------------------------------------------
  if (HD44780_MODE == HD44780_4BIT_MODE) {
    // send required data in required mode
    HD44780_Send8bitsIn4bitMode(me, data);
    // check busy flag
    HD44780_CheckBFin4bitMode(me);
  // 8 bit mode
  // ------------------------------------------
  } else if (HD44780_MODE == HD44780_8BIT_MODE) {
    // send required data in required mode
    HD44780_Send8bitsIn8bitMode(me, data);
    // check busy flag
    HD44780_CheckBFin8bitMode(me);
  }
}

/**
 * @desc    LCD send data
 *
 * @param   unsigned short int
 *
 * @return  void
 */
static void HD44780_SendData(sCdrvHd44780Obj * const me, unsigned short int data)
{
  // Set RS
	meGpio_Set_(me->RsPin);

  // 4bit mode
  // ------------------------------------------
  if (HD44780_MODE == HD44780_4BIT_MODE) {
    // send required data in required mode
    HD44780_Send8bitsIn4bitMode(me, data);
    // check busy flag
    HD44780_CheckBFin4bitMode(me);
  // 8 bit mode
  // ------------------------------------------
  } else if (HD44780_MODE == HD44780_8BIT_MODE) {
    // send required data in required mode
    HD44780_Send8bitsIn8bitMode(me, data);
    // check busy flag
    HD44780_CheckBFin8bitMode(me);
  }

  // Clear RS
	meGpio_Reset_(me->RsPin);
}

/**
 * @desc    LCD send 4bits instruction in 4 bit mode
 *
 * @param   unsigned short int
 *
 * @return  void
 */
static void HD44780_Send4bitsIn4bitMode(sCdrvHd44780Obj * const me, unsigned short int data)
{
  // Set E
	meGpio_Set_(me->EnPin);
  // send data to LCD
  HD44780_SetUppNibble(me, data);
  // PWeh delay time > 450ns
  meDelay_us_(1);
  // Clear E
  meGpio_Reset_(me->EnPin);
  // TcycE > 1000ns -> delay depends on PWeh delay time
  // delay = TcycE - PWeh = 1000 - 500 = 500ns
  meDelay_us_(1);
}

/**
 * @desc    LCD send 8bits instruction in 4 bit mode
 *
 * @param   unsigned short int
 *
 * @return  void
 */
static void HD44780_Send8bitsIn4bitMode(sCdrvHd44780Obj * const me, unsigned short int data)
{
  // Send upper nibble
  // ----------------------------------
  // Set E
	meGpio_Set_(me->EnPin);
  // send data to LCD
  HD44780_SetUppNibble(me, data);
  // PWeh delay time > 450ns
  meDelay_us_(1);
  // Clear E
	meGpio_Reset_(me->EnPin);
  // TcycE > 1000ns -> delay depends on PWeh delay time
  // delay = TcycE - PWeh = 1000 - 500 = 500ns
  meDelay_us_(1);

  // Send lower nibble
  // ----------------------------------
  // Set E
  meGpio_Set_(me->EnPin);
  // send data to LCD
  HD44780_SetUppNibble(me, data << 4);
  // PWeh delay time > 450ns
  meDelay_us_(1);
  // Clear E
  meGpio_Reset_(me->EnPin);
  // TcycE > 1000ns -> delay depends on PWeh delay time
  // delay = TcycE - PWeh = 1000 - 500 = 500ns
  meDelay_us_(1);
}

/**
 * @desc    LCD send 8bits instruction in 8 bit mode
 *
 * @param   unsigned short int
 *
 * @return  void
 */
static void HD44780_Send8bitsIn8bitMode(sCdrvHd44780Obj * const me, unsigned short int data)
{
  // Set E
	meGpio_Set_(me->EnPin);
  // send data to LCD
  HD44780_SetUppNibble(me, data);
  // send data to LCD
  HD44780_SetLowNibble(me, data);
  // PWeh delay time > 450ns
  meDelay_us_(1);
  // Clear E
	meGpio_Reset_(me->EnPin);
  // TcycE > 1000ns -> delay depends on PWeh delay time
  // delay = TcycE - PWeh = 1000 - 500 = 500ns
  meDelay_us_(1);
}

/**
 * @desc    LCD send upper nibble
 *
 * @param   unsigned short int
 *
 * @return  void
 */
static void HD44780_SetUppNibble(sCdrvHd44780Obj * const me, unsigned short int data)
{
  // clear bits DB7-DB4
	meGpio_Reset_(me->Db7Pin);
	meGpio_Reset_(me->Db6Pin);
	meGpio_Reset_(me->Db5Pin);
	meGpio_Reset_(me->Db4Pin);
  // set DB7-DB4 if corresponding bit is set
  if (data & 0x80) { meGpio_Set_(me->Db7Pin); }
  if (data & 0x40) { meGpio_Set_(me->Db6Pin); }
  if (data & 0x20) { meGpio_Set_(me->Db5Pin); }
  if (data & 0x10) { meGpio_Set_(me->Db4Pin); }
}

/**
 * @desc    LCD send lower nibble
 *
 * @param   unsigned short int
 *
 * @return  void
 */
static void HD44780_SetLowNibble(sCdrvHd44780Obj * const me, unsigned short int data)
{
  // clear bits DB3-DB0
	meGpio_Reset_(me->Db3Pin);
	meGpio_Reset_(me->Db2Pin);
	meGpio_Reset_(me->Db1Pin);
	meGpio_Reset_(me->Db0Pin);
  // set DB3-DB0 if corresponding bit is set
  if (data & 0x80) { meGpio_Set_(me->Db3Pin); }
  if (data & 0x40) { meGpio_Set_(me->Db2Pin); }
  if (data & 0x20) { meGpio_Set_(me->Db1Pin); }
  if (data & 0x10) { meGpio_Set_(me->Db0Pin); }
}

/**
 * @desc    LCD pulse E
 *
 * @param   void
 *
 * @return  void
 */
static void HD44780_PulseE(sCdrvHd44780Obj * const me)
{
  // Set E
	meGpio_Set_(me->EnPin);
  // PWeh delay time > 450ns
  meDelay_us_(1);
  // Clear E
	meGpio_Reset_(me->EnPin);
  // TcycE > 1000ns -> delay depends on PWeh delay time
  // delay = TcycE - PWeh = 1000 - 500 = 500ns
  meDelay_us_(1);
}

/**
 * @desc    Set PORT DB4 to DB7
 *
 * @param   void
 *
 * @return  void
 */
static void HD44780_SetPORT_DATA4to7(sCdrvHd44780Obj * const me)
{
}

/**
 * @desc    Clear DDR DB4 to DB7
 *
 * @param   void
 *
 * @return  void
 */
static void HD44780_ClearDDR_DATA4to7(sCdrvHd44780Obj * const me)
{
  HD44780_InitGpioDi_(me->Db7Pin);
  HD44780_InitGpioDi_(me->Db6Pin);
  HD44780_InitGpioDi_(me->Db5Pin);
  HD44780_InitGpioDi_(me->Db4Pin);
}

/**
 * @desc    Set DDR DB4 to DB7
 *
 * @param   void
 *
 * @return  void
 */
static void HD44780_SetDDR_DATA4to7(sCdrvHd44780Obj * const me)
{
  // set DB7-DB4 as output
  HD44780_InitGpioDo_(me->Db7Pin);
  HD44780_InitGpioDo_(me->Db6Pin);
  HD44780_InitGpioDo_(me->Db5Pin);
  HD44780_InitGpioDo_(me->Db4Pin);
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/
