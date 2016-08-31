/*
 * grove_generic_digital_out.h
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


#ifndef __GROVE_GENERIC_DIGITAL_OUT_H__
#define __GROVE_GENERIC_DIGITAL_OUT_H__

#include "suli2.h"

//GROVE_NAME        "Generic Digital Output"
//SKU               3a9d9a84-8c59-11e5-8994-feff819cdc9f
//IF_TYPE           GPIO
//IMAGE_URL         https://s3-us-west-2.amazonaws.com/wio.seeed.cc/static/driver_images/wio_generic_dout.png
//DESCRIPTION       "The Grove Generic Digital Out can output a digital signal to IO. It can control another device such as Arduino, Raspberry Pi and so on. It also can be read for digital IO state."
//WIKI_URL          https://github.com/Seeed-Studio/Grove_Drivers_for_Wio/wiki/Grove_Generic_Digital_Out
//ADDED_AT          "2015-12-01"
//AUTHOR            "SEEED"

class GenericDOut
{
public:
    GenericDOut(int pin);

    /**
     * Control a generic digital output by writing 1 to pull it high and 0 to pull it low.
     *
     * @param onoff - 1: on/pull high, 0: off/pull low
     *
     * @return bool
     */
    bool write_onoff(int onoff);

    /**
     * Read back the status of this io
     *
     * @param onoff - 1: on/high, 0: off/low
     *
     * @return bool
     */
    bool read_onoff_status(int *onoff);

    /**
     * Output a high pulse in milliseconds
     *
     * @param ms - milliseconds
     *
     * @return bool
     */
    bool write_high_pulse(int ms);
    
    /**
     * Output a low pulse in milliseconds
     *
     * @param ms - milliseconds
     *
     * @return bool
     */
    bool write_low_pulse(int ms);
    
    IO_T *io;
    TIMER_T *timer;
};

static void grove_relay_timer_high_pulse_interrupt_handler(void *para);
static void grove_relay_timer_low_pulse_interrupt_handler(void *para);

#endif
