/*
 * grove_dust.cpp
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

#include "suli2.h"
#include "grove_dust.h"
#include "math.h"

GroveDust::GroveDust(int pin)
{
    this->digital = (IO_T *)malloc(sizeof(IO_T));
    suli_pin_init(digital, pin, SULI_INPUT);

    sample_starttime = starttime_preheat = suli_millis();

    sampletime_ms = 2000;
    lowpulseoccupancy = 0;
    concentration = 0.0;

    suli_pin_attach_interrupt_handler(digital, &dust_io_changed_interrupt_handler, SULI_CHANGE, this);
}

bool GroveDust::read_dust(float *dust)
{
    // judge if the sensor is prepared OK
    // 3 min preheat time is required while using for the first time.
    uint32_t now = suli_millis();
    if(now - starttime_preheat < 180000)
    {
        error_desc = "the sensor is heating and can be read after 3 min preheat time.";
        return false;
    }

    *dust = concentration;

    return true;
}

static void dust_io_changed_interrupt_handler(void *para)
{
    GroveDust *g = (GroveDust *)para;

    if (suli_pin_read(g->digital) == 0)  //fall
    {
        g->duration_starttime = suli_millis();
    } else
    {
        uint32_t now = suli_millis();
        uint32_t duration = now - g->duration_starttime;
        if (duration > 10 && duration < 200)
        {
            g->lowpulseoccupancy += duration;
        }
        if ((now - g->sample_starttime) > g->sampletime_ms)
        {
            float ratio = (g->lowpulseoccupancy * 100.0) / g->sampletime_ms;  // Integer percentage 0=>100
            g->concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve
            g->lowpulseoccupancy = 0;
            g->sample_starttime = now;
        }
    }
}

