/*
 * grove_relay.h
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


#ifndef __GROVE_RELAY_H__
#define __GROVE_RELAY_H__

#include "suli2.h"

//GROVE_NAME        "Grove-Relay"
//SKU               103020005
//IF_TYPE           GPIO
//IMAGE_URL         https://s3-us-west-2.amazonaws.com/wio.seeed.cc/static/driver_images/grove-relay.jpg
//DESCRIPTION       "The Relay is a digital normally open switch that controls a relay capable of switching much higher voltages and currents than your normal Arduino boards. When set to HIGH, the LED will light up and the relay will close allowing current to flow. The peak voltage capability is 250V at 10 amps."
//WIKI_URL          http://www.seeedstudio.com/wiki/Grove_-_Relay
//ADDED_AT          "2015-10-01"
//AUTHOR            "SEEED"

class GroveRelay
{
public:
    GroveRelay(int pin);

    /**
     *
     *
     * @param onoff - 1: on, 0: off
     *
     * @return bool
     */
    bool write_onoff(int onoff);

    /**
     * Read back the status of relay
     *
     * @param onoff - 1: on/high, 0: off/low
     *
     * @return bool
     */
    bool read_onoff_status(int *onoff);

private:
    IO_T *io;
};


#endif
