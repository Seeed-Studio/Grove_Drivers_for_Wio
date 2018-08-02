/*
 * grove_loudness.h
 *
 * Copyright (c) 2016 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Travis Brown (warriorrocker@gmail.com)
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


#ifndef __GROVE_LOUDNESS_H__
#define __GROVE_LOUDNESS_H__

#include "suli2.h"

//GROVE_NAME        "Grove - Loudness Sensor"
//SKU               101020063
//IF_TYPE           ANALOG
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/grove-loudness-sensor.jpg
//DESCRIPTION       "The Grove - Loudness Sensor is designed to detect the loudness of environmental sound. Based on amplifier LM2904 and a built-in microphone, it amplifies and filters the high frequency signal that received from the microphone, and outputs a positive envelop."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-Loudness_Sensor/
//ADDED_AT          "2016-07-01"
//AUTHOR            "Travis Brown"

class GroveLoudness
{
public:
    GroveLoudness(int pin);

    /**
    * Read intensity of ultraviolet(UV) radiation.
    *
    * @param uv_index - UV Index
    *
    * @return bool
    */
    bool read_loudness(int *loudness);

private:
    ANALOG_T *io;
};

#endif
