/*
 * grove_dust.h
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


#ifndef __GROVE_DUST_SENSOR_H__
#define __GROVE_DUST_SENSOR_H__

#include "suli2.h"

//GROVE_NAME        "Grove - Dust Sensor"
//SKU               101020012
//IF_TYPE           GPIO
//IMAGE_URL         http://statics3.seeedstudio.com/product/Dustsensor_01.jpg
//DESCRIPTION       "This Dust Sensor gives a good indication of the air quality in an environment by measuring the dust concentration. The Particulate Matter level (PM level) in the air is measured by counting the Low Pulse Occupancy time (LPO time) in given time unit. LPO time is proportional to PM concentration. This sensor can provide reliable data for air purifier systems; it is responsive to PM of diameter 1μm."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-Dust_Sensor/
//HACK_GUIDE_URL    https://github.com/Seeed-Studio/Grove_Drivers_for_Wio/wiki/Hardware-Hacking-Guide
//ADDED_AT          "2016-08-11"
//AUTHOR            "t.renou@me.com"

class GroveDust
{
public:
    GroveDust(int pin);

    /**
     * Read the concentration dust from the dust sensor.
     *
     * @param dust - dust concentration pcs/0.01cf.
     *
     * @return bool
     */
    bool read_dust(float *dust);
    char *get_last_error() { return error_desc; };

    IO_T *digital;

    uint32_t duration;
    uint32_t sample_starttime;
    uint32_t duration_starttime;
    uint32_t starttime_preheat;
    uint32_t sampletime_ms;
    uint32_t lowpulseoccupancy;

    float concentration;

    char *error_desc;
};

static void dust_io_changed_interrupt_handler(void *para);

#endif
