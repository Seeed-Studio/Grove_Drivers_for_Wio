/*
 * grove_solid_relay.h
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


#ifndef __GROVE_SOLID_RELAY_H__
#define __GROVE_SOLID_RELAY_H__

#include "suli2.h"

//GROVE_NAME        "Grove-Solid State Relay"
//SKU               103020004
//IF_TYPE           GPIO
//IMAGE_URL         https://s3-us-west-2.amazonaws.com/wio.seeed.cc/static/driver_images/grove-solid-relay.jpg
//DESCRIPTION       "Grove – Solid State Relay is a non-contact electronic switch module that has relay features. Based on S208T02, it has a maximum output of 250VAC/4A, with a switching speed less than 10ms. This module is equipped with acrylic base and a 3D-printed protection insulation shield, for user’s safety. The featured LED indicates that the relay is on. It can be widely used in various areas such as computer peripheral interfaces, temperature/speed/light adjustment, servo control, petrochemical, medical instrumentations, financial devices, coal, meters, traffic signals, etc."
//WIKI_URL          http://www.seeedstudio.com/wiki/Grove_-_Solid_State_Relay
//ADDED_AT          "2015-10-01"
//AUTHOR            "SEEED"

class GroveSolidStateRelay
{
public:
    GroveSolidStateRelay(int pin);
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
