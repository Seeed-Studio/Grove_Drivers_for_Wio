/*
 * grove_finger_clip_heart_rate.h
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


#ifndef __GROVE_FINGER_CLIP_HEART_RATE_H__
#define __GROVE_FINGER_CLIP_HEART_RATE_H__

#include "suli2.h"

//GROVE_NAME        "Grove - Finger-Clip Heart Rate Sensor"
//SKU               103020024
//IF_TYPE           I2C
//IMAGE_URL         http://statics3.seeedstudio.com/images/product/103020024%201.jpg
//DESCRIPTION       "Grove - Finger-clip Heart Rate Sensor is based on PAH8001EI-2G, a high performance and low power CMOS-process optical sensor with Green LED and DSP integrated serving as a Heart Reate Detection(HRD) sensor."
//WIKI_URL          http://www.seeedstudio.com/wiki/Grove_-_Finger-clip_Heart_Rate_Sensor
//ADDED_AT          "2016-07-01"
//AUTHOR            "SEEED"

// Device I2C Arress
#define GFCHR_ADDRESS 0xA0

class GroveFingerClipHeartRate
{
public:
    GroveFingerClipHeartRate(int pinsda, int pinscl);

    /**
    * Read the current heart rate in BPM.
    *
    * @param heart_rate - heart rate in BPM.
    *
    * @return bool
    */
    bool read_heart_rate(uint8_t *heart_rate);

//private:
    I2C_T *i2c;
};

#endif