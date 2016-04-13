/*
 * grove_baro_bmp280.cpp
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Lambor, Jack
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
#include "grove_baro_bmp280.h"

GroveBaroBMP280::GroveBaroBMP280(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    suli_i2c_init(i2c, pinsda, pinscl);

    uint8_t chipid = bmp280Read8(BMP280_REG_CHIPID);

    //Serial1.print("chip id: ");
    //Serial1.println(chipid, HEX);

    dig_T1 = bmp280Read16LE(BMP280_REG_DIG_T1);
    dig_T2 = bmp280ReadS16LE(BMP280_REG_DIG_T2);
    dig_T3 = bmp280ReadS16LE(BMP280_REG_DIG_T3);

    dig_P1 = bmp280Read16LE(BMP280_REG_DIG_P1);
    dig_P2 = bmp280ReadS16LE(BMP280_REG_DIG_P2);
    dig_P3 = bmp280ReadS16LE(BMP280_REG_DIG_P3);
    dig_P4 = bmp280ReadS16LE(BMP280_REG_DIG_P4);
    dig_P5 = bmp280ReadS16LE(BMP280_REG_DIG_P5);
    dig_P6 = bmp280ReadS16LE(BMP280_REG_DIG_P6);
    dig_P7 = bmp280ReadS16LE(BMP280_REG_DIG_P7);
    dig_P8 = bmp280ReadS16LE(BMP280_REG_DIG_P8);
    dig_P9 = bmp280ReadS16LE(BMP280_REG_DIG_P9);

    writeRegister(BMP280_REG_CONTROL, 0x3F);

}

uint8_t GroveBaroBMP280::bmp280Read8(uint8_t reg)
{
    suli_i2c_read_reg(i2c, BMP280_ADDRESS, reg, databuf, 1);
    return databuf[0];

}

uint16_t GroveBaroBMP280::bmp280Read16(uint8_t reg)
{
    suli_i2c_read_reg(i2c, BMP280_ADDRESS, reg, databuf, 2);
    return (databuf[0] << 8) | databuf[1];

}

uint16_t GroveBaroBMP280::bmp280Read16LE(uint8_t reg)
{
    suli_i2c_read_reg(i2c, BMP280_ADDRESS, reg, databuf, 2);
    return (databuf[1] << 8) | databuf[0];
}

int16_t GroveBaroBMP280::bmp280ReadS16(uint8_t reg)
{
    suli_i2c_read_reg(i2c, BMP280_ADDRESS, reg, databuf, 2);
    return (int16_t)((databuf[0] << 8) | databuf[1]);
}

int16_t GroveBaroBMP280::bmp280ReadS16LE(uint8_t reg)
{
    suli_i2c_read_reg(i2c, BMP280_ADDRESS, reg, databuf, 2);
    return (int16_t)((databuf[1] << 8) | databuf[0]);
}

uint32_t GroveBaroBMP280::bmp280Read24(uint8_t reg)
{
    uint32_t data;

    suli_i2c_read_reg(i2c, BMP280_ADDRESS, reg, databuf, 3);

    data = databuf[0];
    data <<= 8;
    data |= databuf[1];
    data <<= 8;
    data |= databuf[2];

    return data;
}

void GroveBaroBMP280::writeRegister(uint8_t reg, uint8_t val)
{
    cmdbuf[0] = reg;
    cmdbuf[1] = val;
    suli_i2c_write(i2c, BMP280_ADDRESS, cmdbuf, 2);
}


bool GroveBaroBMP280::read_temperature(float *temperature)
{
    int32_t var1, var2;

    int32_t adc_T = bmp280Read24(BMP280_REG_TEMPDATA);
    adc_T >>= 4;
    var1 = (((adc_T >> 3) - ((int32_t)(dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;

    var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;

    t_fine = var1 + var2;
    float T = (t_fine * 5 + 128) >> 8;
    *temperature = T / 100;

    return true;

}

bool GroveBaroBMP280::read_pressure(int32_t *pressure)
{
    int64_t var1, var2, p;

    // Call getTemperature to get t_fine
    float t;
    read_temperature(&t);

    int32_t adc_P = bmp280Read24(BMP280_REG_PRESSUREDATA);
    adc_P >>= 4;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;
    if (var1 == 0)
    {
        return false;
    }
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
    *pressure = (int32_t)p / 256;

    return true;
}

bool GroveBaroBMP280::read_altitude(float *altitude)
{
    int32_t p;
    read_pressure(&p);
    //Serial1.println(p);

    float A = ((float)p) / 101325.0f;
    float B = 1 / 5.25588;
    float C = pow(A, B);
    C = 1.0 - C;
    C = C / 0.0000225577;
    *altitude = C;
    return true;
}

