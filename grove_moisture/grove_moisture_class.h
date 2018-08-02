/*
 * grove_moisture_class.h
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jacky Zhang
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


#ifndef __GROVE_MOISTURE_CLASS_H__
#define __GROVE_MOISTURE_CLASS_H__

#include "grove_moisture.h"

//GROVE_NAME        "Grove-Moisture"
//SKU               101020008
//IF_TYPE           ANALOG
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/grove-moisture.jpg
//DESCRIPTION       "The Grove - Moisture Sensor can be used to detect the moisture of soil, to judge if there is dampness around the sensor. It can be used to decide if the plants in a garden needs watering. It can be used in gardens to automate watering plants. It can be used very easily by just inserting the sensor into the soil and reading the output using ADC."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-Moisture_Sensor/
//ADDED_AT          "2015-10-01"
//AUTHOR            "SEEED"

class GroveMoisture
{
public:
    GroveMoisture(int pin);

    /**
     *
     *
     * @param moisture - analog value, range: 0~1023
     *
     * @return bool
     */
    bool read_moisture(uint16_t *moisture);

private:
    ANALOG_T *analog;
    bool _write_setup(void);
};

#endif
