/*
 * grove_temp_humi_baro_bme280.h
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


#ifndef __GROVE_BME280_H__
#define __GROVE_BME280_H__

#include "suli2.h"

//GROVE_NAME        "Grove - Temp&Humi&Barometer Sensor (BME280)"
//SKU               101020193
//IF_TYPE           I2C
//IMAGE_URL         http://statics3.seeedstudio.com/seeed/img/2016-06/R425Ianm2Rr93qmJQFUEwGx7.jpg
//DESCRIPTION       "The module provides precise measurement of not only barometric pressure and temperature, but also the humidity in the environment."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-Barometer_Sensor-BME280/
//ADDED_AT          "2016-06-17"
//AUTHOR            "SEEED"


#define BME280_ADDRESS   (0x76<<1)

#define BME280_REG_DIG_T1    0x88
#define BME280_REG_DIG_T2    0x8A
#define BME280_REG_DIG_T3    0x8C

#define BME280_REG_DIG_P1    0x8E
#define BME280_REG_DIG_P2    0x90
#define BME280_REG_DIG_P3    0x92
#define BME280_REG_DIG_P4    0x94
#define BME280_REG_DIG_P5    0x96
#define BME280_REG_DIG_P6    0x98
#define BME280_REG_DIG_P7    0x9A
#define BME280_REG_DIG_P8    0x9C
#define BME280_REG_DIG_P9    0x9E

#define BME280_REG_DIG_H1    0xA1
#define BME280_REG_DIG_H2    0xE1
#define BME280_REG_DIG_H3    0xE3
#define BME280_REG_DIG_H4    0xE4
#define BME280_REG_DIG_H5    0xE5
#define BME280_REG_DIG_H6    0xE7

#define BME280_REG_CHIPID          0xD0
#define BME280_REG_VERSION         0xD1
#define BME280_REG_SOFTRESET       0xE0

#define BME280_REG_CAL26           0xE1

#define BME280_REG_CONTROLHUMID    0xF2
#define BME280_REG_CONTROL         0xF4
#define BME280_REG_CONFIG          0xF5
#define BME280_REG_PRESSUREDATA    0xF7
#define BME280_REG_TEMPDATA        0xFA
#define BME280_REG_HUMIDITYDATA    0xFD


class GroveBME280
{
public:
    GroveBME280(int pinsda, int pinscl);
    bool on_power_on();
    bool on_power_off();

    /**
     * Read the temperature value of the envirenment
     *
     * @param temperature - unit: Celsius degree
     *
     * @return bool
     */
    bool read_temperature(float *temperature);

    /**
     *
     *
     * @param pressure - unit: Pa
     *
     * @return bool
     */
    bool read_pressure(uint32_t *pressure);

    /**
     *
     *
     * @param humidity - unit: %
     *
     * @return bool
     */
    bool read_humidity(uint32_t *humidity);

    /**
     *
     *
     * @param altitude - the absolute altitude, unit: m
     *
     * @return bool
     */
    bool read_altitude(float *altitude);


private:
    I2C_T *i2c;
    uint8_t cmdbuf[2];
    uint8_t databuf[3];

    // Calibratino data
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;

    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;

    uint8_t dig_H1;
    int16_t dig_H2;
    uint8_t dig_H3;
    int16_t dig_H4;
    int16_t dig_H5;
    int8_t  dig_H6;

    int32_t t_fine;

    uint8_t BME280Read8(uint8_t reg);
    uint16_t BME280Read16(uint8_t reg);
    uint16_t BME280Read16LE(uint8_t reg);
    int16_t BME280ReadS16(uint8_t reg);
    int16_t BME280ReadS16LE(uint8_t reg);
    uint32_t BME280Read24(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t val);
};

#endif
