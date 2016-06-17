/*
 * grove_temp_humi_baro_GroveBME280.cpp
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
#include "grove_temp_humi_baro_bme280.h"

GroveBME280::GroveBME280(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    suli_i2c_init(i2c, pinsda, pinscl);

    on_power_on();
}

bool GroveBME280::on_power_on()
{
    uint8_t chipid = BME280Read8(BME280_REG_CHIPID);

    //Serial1.print("chip id: ");
    //Serial1.println(chipid, HEX); //should be 0x60

    dig_T1 = BME280Read16LE(BME280_REG_DIG_T1);
    dig_T2 = BME280ReadS16LE(BME280_REG_DIG_T2);
    dig_T3 = BME280ReadS16LE(BME280_REG_DIG_T3);

    dig_P1 = BME280Read16LE(BME280_REG_DIG_P1);
    dig_P2 = BME280ReadS16LE(BME280_REG_DIG_P2);
    dig_P3 = BME280ReadS16LE(BME280_REG_DIG_P3);
    dig_P4 = BME280ReadS16LE(BME280_REG_DIG_P4);
    dig_P5 = BME280ReadS16LE(BME280_REG_DIG_P5);
    dig_P6 = BME280ReadS16LE(BME280_REG_DIG_P6);
    dig_P7 = BME280ReadS16LE(BME280_REG_DIG_P7);
    dig_P8 = BME280ReadS16LE(BME280_REG_DIG_P8);
    dig_P9 = BME280ReadS16LE(BME280_REG_DIG_P9);

    dig_H1 = BME280Read8(BME280_REG_DIG_H1);
    dig_H2 = BME280Read16LE(BME280_REG_DIG_H2);
    dig_H3 = BME280Read8(BME280_REG_DIG_H3);
    dig_H4 = (BME280Read8(BME280_REG_DIG_H4) << 4) | (0x0F & BME280Read8(BME280_REG_DIG_H4 + 1));
    dig_H5 = (BME280Read8(BME280_REG_DIG_H5 + 1) << 4) | (0x0F & BME280Read8(BME280_REG_DIG_H5) >> 4);
    dig_H6 = (int8_t)BME280Read8(BME280_REG_DIG_H6);

    writeRegister(BME280_REG_CONTROLHUMID, 0x05);  //Choose 16X oversampling
    writeRegister(BME280_REG_CONTROL, 0xB7);  //Choose 16X oversampling

    return true;
}

bool GroveBME280::on_power_off()
{
    return true;
}

bool GroveBME280::read_temperature(float *temperature)
{
    int32_t var1, var2;

    int32_t adc_T = BME280Read24(BME280_REG_TEMPDATA);
    adc_T >>= 4;
    var1 = (((adc_T >> 3) - ((int32_t)(dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;

    var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;

    t_fine = var1 + var2;
    float T = (t_fine * 5 + 128) >> 8;
    *temperature = T / 100;

    return true;
}

bool GroveBME280::read_pressure(uint32_t *pressure)
{
    int64_t var1, var2, p;
    float t;

    // Call getTemperature to get t_fine
    read_temperature(&t);

    int32_t adc_P = BME280Read24(BME280_REG_PRESSUREDATA);
    adc_P >>= 4;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;
    if (var1 == 0)
    {
        return 0; // avoid exception caused by division by zero
    }
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
    *pressure = (uint32_t)p / 256;

    return true;
}

bool GroveBME280::read_humidity(uint32_t *humidity)
{
    int32_t v_x1_u32r, adc_H;
    float t;

    // Call getTemperature to get t_fine
    read_temperature(&t);

    adc_H = BME280Read16(BME280_REG_HUMIDITYDATA);

    v_x1_u32r = (t_fine - ((int32_t)76800));
    v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)dig_H2) + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
    *humidity = (uint32_t)(v_x1_u32r >> 12) / 1024.0;

    return true;
}

bool GroveBME280::read_altitude(float *altitude)
{
    uint32_t pressure;
    read_pressure(&pressure);

    float A = ((float)pressure) / 101325.0f;
    float B = 1 / 5.25588;
    float C = pow(A, B);
    C = 1.0 - C;
    C = C / 0.0000225577;
    *altitude = C;

    return true;
}

uint8_t GroveBME280::BME280Read8(uint8_t reg)
{
    suli_i2c_read_reg(i2c, BME280_ADDRESS, reg, databuf, 1);
    return databuf[0];
}

uint16_t GroveBME280::BME280Read16(uint8_t reg)
{
    suli_i2c_read_reg(i2c, BME280_ADDRESS, reg, databuf, 2);
    return (databuf[0] << 8) | databuf[1];
}

uint16_t GroveBME280::BME280Read16LE(uint8_t reg)
{
    suli_i2c_read_reg(i2c, BME280_ADDRESS, reg, databuf, 2);
    return (databuf[1] << 8) | databuf[0];
}

int16_t GroveBME280::BME280ReadS16(uint8_t reg)
{
    return (int16_t)BME280Read16(reg);
}

int16_t GroveBME280::BME280ReadS16LE(uint8_t reg)
{
    return (int16_t)BME280Read16LE(reg);
}

uint32_t GroveBME280::BME280Read24(uint8_t reg)
{
    uint32_t data;

    suli_i2c_read_reg(i2c, BME280_ADDRESS, reg, databuf, 3);

    data = databuf[0];
    data <<= 8;
    data |= databuf[1];
    data <<= 8;
    data |= databuf[2];

    return data;
}

void GroveBME280::writeRegister(uint8_t reg, uint8_t val)
{
    cmdbuf[0] = reg;
    cmdbuf[1] = val;
    suli_i2c_write(i2c, BME280_ADDRESS, cmdbuf, 2);
}

