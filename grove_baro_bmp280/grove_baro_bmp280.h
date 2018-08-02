/*
 * grove_baro_bmp280.h
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


#ifndef __GROVE_BARO_BMP280_H__
#define __GROVE_BARO_BMP280_H__

#include "suli2.h"

//GROVE_NAME        "Grove-Barometer(BMP280)"
//SKU               101020192
//IF_TYPE           I2C
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/grove-barometer-sensor-bmp280.jpg
//DESCRIPTION       "This sensor is high-precision and low-power digital barometer, can be used to detect temperature and atmospheric pressure accurately. As atmospheric pressure changes with altitude, it can also detect approximate altitude of a place."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-Barometer_Sensor-BMP280/
//ADDED_AT          "2015-10-01"
//AUTHOR            "SEEED"


#define BMP280_ADDRESS   (0x77<<1)

#define BMP280_REG_DIG_T1    0x88
#define BMP280_REG_DIG_T2    0x8A
#define BMP280_REG_DIG_T3    0x8C

#define BMP280_REG_DIG_P1    0x8E
#define BMP280_REG_DIG_P2    0x90
#define BMP280_REG_DIG_P3    0x92
#define BMP280_REG_DIG_P4    0x94
#define BMP280_REG_DIG_P5    0x96
#define BMP280_REG_DIG_P6    0x98
#define BMP280_REG_DIG_P7    0x9A
#define BMP280_REG_DIG_P8    0x9C
#define BMP280_REG_DIG_P9    0x9E

#define BMP280_REG_CHIPID          0xD0
#define BMP280_REG_VERSION         0xD1
#define BMP280_REG_SOFTRESET       0xE0

#define BMP280_REG_CONTROL         0xF4
#define BMP280_REG_CONFIG          0xF5
#define BMP280_REG_PRESSUREDATA    0xF7
#define BMP280_REG_TEMPDATA        0xFA


class GroveBaroBMP280
{
public:
    GroveBaroBMP280(int pinsda, int pinscl);

    /**
     * Read a rough temperature value of the envirenment
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
    bool read_pressure(int32_t *pressure);

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
    const uint8_t OSS = 0;  //0: lowpower 1: standard 2: high 3: ultrahigh accuration
    int32_t PressureCompensate;


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

    int32_t t_fine;

    uint8_t bmp280Read8(uint8_t reg);
    uint16_t bmp280Read16(uint8_t reg);
    uint16_t bmp280Read16LE(uint8_t reg);
    int16_t bmp280ReadS16(uint8_t reg);
    int16_t bmp280ReadS16LE(uint8_t reg);
    uint32_t bmp280Read24(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t val);

};

#endif
