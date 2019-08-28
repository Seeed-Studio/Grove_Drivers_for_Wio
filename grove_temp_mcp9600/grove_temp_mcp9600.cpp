/*
 * grove_temp_mcp9600.cpp
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
#include "grove_temp_mcp9600.h"

#define I2C_ADDRESS								(0x60 << 1)

#define REG_HOT_JUNCTION_TEMPERATURE			(0x00)
#define REG_JUNCTIONS_TEMPERATURE_DELTA			(0x01)
#define REG_COLD_JUNCTION_TEMPERATURE			(0x02)
#define REG_RAW_DATA_ADC						(0x03)
#define REG_STATUS								(0x04)
#define REG_THERMOCOUPLE_SENSOR_CONFIGURATION	(0x05)
#define REG_DEVICE_CONFIGURATION				(0x06)
#define REG_DEVICE_ID							(0x20)

GroveTempMCP9600::GroveTempMCP9600(int pinsda, int pinscl)
{
	error = false;

    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    suli_i2c_init(i2c, pinsda, pinscl);
	suli_i2c_clock(i2c, 50000);

	uint8_t readData[2];
	if (suli_i2c_read_reg(i2c, I2C_ADDRESS, REG_DEVICE_ID, readData, sizeof(readData)) != sizeof(readData))
	{
		error = true;
		return;
	}
	if (readData[0] != 0x40)
	{
		error = true;
	}
}

bool GroveTempMCP9600::write_thermocouple_type(int type)
{
	if (error) return false;

	uint8_t data[1];
	if (suli_i2c_read_reg(i2c, I2C_ADDRESS, REG_THERMOCOUPLE_SENSOR_CONFIGURATION, data, sizeof(data)) != sizeof(data)) return false;
	data[0] &= ~0x70;
	data[0] |= (type & 0x07) << 4;
	if (suli_i2c_write_reg(i2c, I2C_ADDRESS, REG_THERMOCOUPLE_SENSOR_CONFIGURATION, data, sizeof(data)) != sizeof(data)) return false;

	return true;
}

bool GroveTempMCP9600::read_temp(float *temperature)
{
	if (error) return false;

	uint8_t readData[2];
	if (suli_i2c_read_reg(i2c, I2C_ADDRESS, REG_HOT_JUNCTION_TEMPERATURE, readData, sizeof(readData)) != sizeof(readData)) return false;
	uint16_t tc_u16 = readData[0] << 8 | readData[1];
	int16_t tc_i16 = *(int16_t*)&tc_u16;

	*temperature = (float)tc_i16 / 16;

	return true;
}
