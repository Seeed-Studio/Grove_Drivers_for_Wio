/*
 * grove_ir_distance_intr.h
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


#ifndef __GROVE_IR_DIST_INTR_H__
#define __GROVE_IR_DIST_INTR_H__

#include "suli2.h"

//GROVE_NAME        "Grove-IR Distance Interrupter"
//SKU               101020040
//IF_TYPE           GPIO
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/grove-ir_distance_interruper.jpg
//DESCRIPTION       "Grove - IR Distance Interrupter is used to detect any object blocking the path of light. The module consists of an IR LED and a photosensor (phototransistor) pair. The light emitted by the IR LED gets reflected by any object placed in front of the sensor and this reflection is detected by the photosensor(phototransistor). Any white (or lighter) colored surface reflects more than black (or darker) colored surface."
//WIKI_URL          http://www.seeedstudio.com/wiki/Grove_-_IR_Distance_Interrupter_v1.2
//ADDED_AT          "2015-10-01"
//AUTHOR            "SEEED"

class GroveIRDistanceInterrupter
{
public:
    GroveIRDistanceInterrupter(int pin);

    /**
     * Read the status if a object is approaching the sensor.
     *
     * @param approach - 1: something approached 0: not
     *
     * @return bool
     */
    bool read_approach(uint8_t *approach);

    /**
     * Triggered when IR object approach the sensor.
     */
    DEFINE_EVENT(ir_approached, SULI_EDT_INT);
    IO_T *io;
    uint32_t time;
};

static void approach_interrupt_handler(void *para);


#endif
