/*
 * grove_co2_mhz16.h
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Pontus "Mirar" Hagland
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


#ifndef __GROVE_MP3V2_H__
#define __GROVE_MP3V2_H__

#include "suli2.h"

//GROVE_NAME        "Grove - CO2 MH-Z16"
//SKU               101020067
//IF_TYPE           UART
//IMAGE_URL         http://statics3.seeedstudio.com/images/product/Grove%20CO2%20Sensor.jpg
//DESCRIPTION       "The Grove - CO2 Sensor module is infrared CO2 sensor with high sensitivity and high resolution."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-CO2_Sensor/
//ADDED_AT          "2016-06-13"
//AUTHOR            "Mirar"


class GroveCo2MhZ16
{
public:

    GroveCo2MhZ16(int pintx, int pinrx);

    /**
     * Get concentration and temperature.
     *
     * @param concentration - unit: PPM
     * @param temperature - unit: Celsius degree
     *
     * @return bool
     */

    bool read_concentration_and_temperature(float *concentration,float *temperature);

    /**
     * Get concentration
     *
     * @param concentration - unit: PPM
     *
     * @return bool
     */

    bool read_concentration(float *concentration);

    /**
     * Get temperature.
     *
     * @param temperature - unit: Celsius degree
     *
     * @return bool
     */

    bool read_temperature(float *temperature);

    /**
     * Get last error.
     *
     * @return char*
     */

    const char* get_last_error(void);

private:

    UART_T *uart;

    void _drain_uart();
    bool _update_from_sensor(void);

    float CO2PPM;
    float temp;
    const char* last_error;
};

#endif
