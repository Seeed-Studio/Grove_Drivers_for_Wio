/*
 * grove_voltage_divider.h
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jack Shao (jacky.shaoxg@gmail.com)
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


#ifndef __GROVE_VOLTAGE_DIVIDER_H__
#define __GROVE_VOLTAGE_DIVIDER_H__

#include "suli2.h"

//GROVE_NAME        "Grove - Voltage Divider"
//SKU               104020000
//IF_TYPE           ANALOG
//IMAGE_URL         https://statics3.seeedstudio.com/product/Voltage%20Divider_01.jpg
//DESCRIPTION       "The Grove – Voltage Divider provides an interface for measuring extern voltage, eliminating the need to connect a resistance to input interface. Besides, The voltage gain can select by dial switch."
//WIKI_URL          http://www.seeedstudio.com/wiki/Grove_-_Voltage_Divider
//ADDED_AT          "2016-09-22"
//AUTHOR            "SEEED"

class GroveVolDivider
{
public:
    GroveVolDivider(int pin);

    /**
     * Read the voltage of the input with gain 3.
     *
     * @param volt - unit: V
     *
     * @return bool
     */
    bool read_voltage_x3(float *volt);

    /**
     * Read the voltage of the input with gain 10.
     *
     * @param volt - unit: V
     *
     * @return bool
     */
    bool read_voltage_x10(float *volt);

private:
    ANALOG_T *io;
};


#endif
