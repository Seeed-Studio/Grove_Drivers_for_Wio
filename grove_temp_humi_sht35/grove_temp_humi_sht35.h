/*
 * grove_temp_humi_sht35.h
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


#ifndef __GROVE_TEMP_HUMI_SHT35_H__
#define __GROVE_TEMP_HUMI_SHT35_H__

#include "suli2.h"

//GROVE_NAME        "Grove - I2C High Accuracy Temp&Humi Sensor (SHT35)"
//SKU               101020592
//IF_TYPE           I2C
//IMAGE_URL         https://www.seeedstudio.site/media/catalog/product/cache/ef3164306500b1080e8560b2e8b5cc0f/h/t/httpsstatics3.seeedstudio.comseeedfile2018-10bazaar951702_1010205922.jpg
//DESCRIPTION       "Grove - I2C High Accuracy Temp&Humi Sensor(SHT35) is a highly reliable, accurate, quick response and integrated temperature & humidity sensor. The typical accuracy of this module can be ±1.5%RH (for relative humidity) and ±0.1°C (for temperature)."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-I2C_High_Accuracy_Temp%26Humi_Sensor-SHT35/
//ADDED_AT          "2019-07-31"
//AUTHOR            "SEEED"

class GroveTempHumiSHT35
{
public:
    GroveTempHumiSHT35(int pinsda, int pinscl);
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
