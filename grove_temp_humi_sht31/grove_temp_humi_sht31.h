/*
 * grove_temp_humi_sht31.h
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


#ifndef __GROVE_TEMP_HUMI_SHT31_H__
#define __GROVE_TEMP_HUMI_SHT31_H__

#include "suli2.h"

//GROVE_NAME        "Grove - Temperature&Humidity Sensor (SHT31)"
//SKU               101020212
//IF_TYPE           I2C
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/grove_temp_humi_sht31.jpg
//DESCRIPTION       "Grove - Temp&Humi Sensor(SHT31) is a highly reliable, accurate, quick response and integrated temperature & humidity sensor. The typical accuracy of this module can be ±2%RH (for relative humidity) and ±0.3°C (for temperature)."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-TempAndHumi_Sensor-SHT31/
//ADDED_AT          "2018-08-01"
//AUTHOR            "SEEED"

class GroveTempHumiSHT31
{
public:
    GroveTempHumiSHT31(int pinsda, int pinscl);
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
     * @param humidity - unit: %
     *
     * @return bool
     */
    bool read_humidity(float *humidity);

    /**
     *
     *
     * @param onoff - 1: on, 0: off
     *
     * @return bool
     */
    bool write_heater_onoff(int onoff);

private:
    I2C_T *i2c;

    void SendCommand(uint16_t cmd);
    bool ReadTempHumi(float *temperature, float *humidity);

    static uint8_t CalcCRC8(const uint8_t *data, int len);

};

#endif
