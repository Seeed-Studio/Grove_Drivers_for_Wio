/*
 * grove_temp_humi_sht31.cpp
 *
 * Copyright (c) 2019 Seeed K.K.
 * Website    : www.seeed.co.jp
 * Author     : Takashi Matsuoka
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "suli2.h"
#include "grove_temp_humi_sht31.h"

#define I2C_ADDRESS         (0x44 << 1)
#define CMD_SOFT_RESET	    (0x30a2)
#define CMD_SINGLE_HIGH		(0x2400)
#define CMD_HEATER_ON		(0x306d)
#define CMD_HEATER_OFF		(0x3066)

#define POLYNOMIAL			(0x31)

GroveTempHumiSHT31::GroveTempHumiSHT31(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    suli_i2c_init(i2c, pinsda, pinscl);

    on_power_on();
}

bool GroveTempHumiSHT31::on_power_on()
{
	SendCommand(CMD_SOFT_RESET);
    suli_delay_ms(1);

    return true;
}

bool GroveTempHumiSHT31::on_power_off()
{
    return true;
}

bool GroveTempHumiSHT31::read_temperature(float *temperature)
{
	return ReadTempHumi(temperature, NULL);
}

bool GroveTempHumiSHT31::read_humidity(float *humidity)
{
	return ReadTempHumi(NULL, humidity);
}

bool GroveTempHumiSHT31::write_heater_onoff(int onoff)
{
	if (onoff)
		SendCommand(CMD_HEATER_ON);
	else
		SendCommand(CMD_HEATER_OFF);
}

void GroveTempHumiSHT31::SendCommand(uint16_t cmd)
{
	uint8_t writeData[2];
	writeData[0] = cmd >> 8;
	writeData[1] = cmd & 0xff;
    suli_i2c_write(i2c, I2C_ADDRESS, writeData, sizeof(writeData));
}

bool GroveTempHumiSHT31::ReadTempHumi(float *temperature, float *humidity)
{
	SendCommand(CMD_SINGLE_HIGH);
	delay(15);

	uint8_t readData[6];
    if (suli_i2c_read(i2c, I2C_ADDRESS, readData, sizeof(readData)) != 6) return false;

	if (readData[2] != CalcCRC8(&readData[0], 2)) return false;
	if (readData[5] != CalcCRC8(&readData[3], 2)) return false;

	uint16_t ST;
	ST = readData[0];
	ST <<= 8;
	ST |= readData[1];

	uint16_t SRH;
	SRH = readData[3];
	SRH <<= 8;
	SRH |= readData[4];

	if (temperature != NULL) *temperature = (float)ST * 175 / 0xffff - 45;
	if (humidity != NULL) *humidity = (float)SRH * 100 / 0xffff;

    return true;
}

static uint8_t GroveTempHumiSHT31::CalcCRC8(const uint8_t *data, int len)
{
	uint8_t crc = 0xff;
  
	for (int j = len; j > 0; j--)
	{
		crc ^= *data++;

		for (int i = 8; i > 0; i--)
		{
			crc = crc & 0x80 ? crc << 1 ^ POLYNOMIAL : crc << 1;
		}
	}

	return crc; 
}
