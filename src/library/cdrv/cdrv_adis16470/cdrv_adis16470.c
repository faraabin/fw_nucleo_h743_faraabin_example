#include "cdrv_adis16470.h"

static int16_t regRead(sAdis16470_Obj *me, uint8_t regAddr);// Read register
static int regWrite(sAdis16470_Obj *me, uint8_t regAddr, int16_t regData); // Write register
static void byteBurst(sAdis16470_Obj *me, uint8_t *data);// Burstread byte
static int16_t  checksum(uint16_t* burstArray); // Calculate checksum

static float accelScale(int16_t sensorData);// Calculate accelerator data
static float gyroScale(int16_t sensorData);// Calculate gyro data
static float tempScale(int16_t sensorData); // Calculate temperature data
static float deltaAngleScale(int16_t sensorData); // Calculate delta angle data
static float deltaVelocityScale(int16_t sensorData); // Calculate delta velocity

static void wordData(uint8_t* burstdata, uint16_t *burstdata_word);// Bytes are converted to words

uint8_t fAdis16470_Init(sAdis16470_Obj *me) {
	
	return 0;
}

uint8_t fAdis16470_Update(sAdis16470_Obj *me) {
	
	byteBurst(me, me->burstByte);
	
	wordData(me->burstByte, me->burstWord);
	
	me->gyro.x = gyroScale((int16_t)me->burstWord[1]);
	me->gyro.y = gyroScale((int16_t)me->burstWord[2]);
	me->gyro.z = gyroScale((int16_t)me->burstWord[3]);
	me->accel.x = accelScale((int16_t)me->burstWord[4]);
	me->accel.y = accelScale((int16_t)me->burstWord[5]);
	me->accel.z = accelScale((int16_t)me->burstWord[6]);
	me->temp = tempScale((int16_t)me->burstWord[7]);
	
	return 0;
}

static int16_t regRead(sAdis16470_Obj *me, uint8_t regAddr) {
	
	uint8_t tmp = 0x00;
	
	meGpio_Reset_(me->cs);
	meSpi_Transmit_(me->spi, &regAddr, 1, 1000);
	meSpi_Transmit_(me->spi, &tmp, 1, 1000);
	meGpio_Set_(me->cs);

	meDelay_us_(20);

	meGpio_Reset_(me->cs);
	uint8_t _msbData;
	meSpi_Receive_(me->spi, &_msbData, 1, 1000);
	uint8_t _lsbData;
	meSpi_Receive_(me->spi, &_lsbData, 1, 1000);
	meGpio_Set_(me->cs);

	meDelay_us_(20);

	int16_t _dataOut = (_msbData << 8) | (_lsbData & 0xFF);

	return (_dataOut);
}

/** Write registers using SPI.
    @param regAddr:the address of register
    @param regData:the value is writed
    @return true
*/
static int regWrite(sAdis16470_Obj *me, uint8_t regAddr, int16_t regData) {
	
	uint16_t addr = (((regAddr & 0x7F) | 0x80) << 8);
	uint16_t lowWord = (addr | (regData & 0xFF));
	uint16_t highWord = ((addr | 0x100) | ((regData >> 8) & 0xFF));

	// Split words into chars
	uint8_t highBytehighWord = (highWord >> 8);
	uint8_t lowBytehighWord = (highWord & 0xFF);
	uint8_t highBytelowWord = (lowWord >> 8);
	uint8_t lowBytelowWord = (lowWord & 0xFF);

	// Write highWord to SPI bus
	meGpio_Reset_(me->cs);
	meSpi_Transmit_(me->spi, &highBytelowWord, 1, 1000);
	meSpi_Transmit_(me->spi, &lowBytelowWord, 1, 1000);
	meGpio_Set_(me->cs);

	meDelay_us_(20);

	// Write lowWord to SPI bus
	meGpio_Reset_(me->cs);
	meSpi_Transmit_(me->spi, &highBytehighWord, 1, 1000);
	meSpi_Transmit_(me->spi, &lowBytehighWord, 1, 1000);
	meGpio_Set_(me->cs);

	meDelay_us_(20);

	return (1);
}

/** Burstread value(byte)
    @return  20 bytes value
*/
static void byteBurst(sAdis16470_Obj *me, uint8_t *burstdata) {

	uint8_t tmp;
	
	// Trigger Burst Read
	meGpio_Reset_(me->cs);

	tmp = 0x68;
	meSpi_Transmit_(me->spi, &tmp, 1, 1000);
	
	tmp = 0x00;
	meSpi_Transmit_(me->spi, &tmp, 1, 1000);
	
	meSpi_Receive_(me->spi, burstdata, 20, 1000);

	meGpio_Set_(me->cs);

	burstdata[20] = 0x01; //firmware version 1.0
}

/** Calculate checksum value.
    @param burstArray:the array of burstread value
    @return checksum value
*/
static int16_t checksum(uint16_t* burstArray) {
	
    int16_t s = 0;
    for (int i = 0; i < 9; i++) { // Checksum value is not part of the sum!!
        s += (burstArray[i] & 0xFF); // Count lower byte
        s += ((burstArray[i] >> 8) & 0xFF); // Count upper byte
    }

    return s;
}

/** Calculate accelerator data
    @param sensorData:data output from regRead()
    @return signed/scaled accelerometer in g's
*/
static float accelScale(int16_t sensorData) {
	
    float finalData = sensorData * 0.00125; // Multiply by accel sensitivity (0.00125g/LSB)
    return finalData;
}

/** Calculate gyro data
    @param sensorData:data output from regRead()
    @return signed/scaled gyro in degrees/sec
*/
static float gyroScale(int16_t sensorData) {
	
    float finalData = sensorData * 0.1; // Multiply by gyro sensitivity (0.1 deg/LSB)
    return finalData;
}

/** Calculate temperature data
    @param sensorData:data output from regRead()
    @return signed/scaled temperature in degrees Celcius
*/
static float tempScale(int16_t sensorData) {
	
    float finalData = (sensorData * 0.1); // Multiply by temperature scale (0.1 deg C/LSB)
    return finalData;
}

/** Calculate delta angle data
    @param sensorData:data output from regRead()
    @return signed/scaled delta angle in degrees
*/
static float deltaAngleScale(int16_t sensorData) {
	
    float finalData = sensorData * 0.061; // Multiply by delta angle scale (0.061 degrees/LSB)
    return finalData;
}

/** Calculate delta velocity
    @param sensorData:data output from regRead()
    @return signed/scaled delta velocity in m/sec
*/
static float deltaVelocityScale(int16_t sensorData) {
	
    float finalData = sensorData * 0.01221; // Multiply by velocity scale (0.01221 m/sec/LSB)
    return finalData;
}


/** Burstread value(word)
    @param burstdata:the 20 bytes value
    @return 10 words value
*/
static void wordData(uint8_t* burstdata, uint16_t *burstdata_word) {

    // Convert Data
    burstdata_word[0] = ((burstdata[0] << 8) | (burstdata[1] & 0xFF)); //DIAG_STAT
    burstdata_word[1] = ((burstdata[2] << 8) | (burstdata[3] & 0xFF)); //XGYRO
    burstdata_word[2] = ((burstdata[4] << 8) | (burstdata[5] & 0xFF)); //YGYRO
    burstdata_word[3] = ((burstdata[6] << 8) | (burstdata[7] & 0xFF)); //ZGYRO
    burstdata_word[4] = ((burstdata[8] << 8) | (burstdata[9] & 0xFF)); //XACCEL
    burstdata_word[5] = ((burstdata[10] << 8) | (burstdata[11] & 0xFF)); //YACCEL
    burstdata_word[6] = ((burstdata[12] << 8) | (burstdata[13] & 0xFF)); //ZACCEL
    burstdata_word[7] = ((burstdata[14] << 8) | (burstdata[15] & 0xFF)); //TEMP_OUT
    burstdata_word[8] = ((burstdata[16] << 8) | (burstdata[17] & 0xFF)); //TIME_STMP
    burstdata_word[9] = ((burstdata[18] << 8) | (burstdata[19] & 0xFF)); //CHECKSUM
}
