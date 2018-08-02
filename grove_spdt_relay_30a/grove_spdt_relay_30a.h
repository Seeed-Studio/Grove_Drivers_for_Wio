/*
 * grove_spdt_relay_30a.h
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jacky Zhang (qi.zhang@seeed.cc)
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


#ifndef __GROVE_SPDT_RELAY_30A_H__
#define __GROVE_SPDT_RELAY_30A_H__

#include "suli2.h"

//GROVE_NAME        "Grove - SPDT Relay(30A)"
//SKU               103020012
//IF_TYPE           GPIO
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/grove-spdt_relay_30a.jpg
//DESCRIPTION       "The SPDT Relay(30A) is a high quality Single Pole Double Throw Relay(SPDT).The Relay consists of a coil, 1 common terminal, 1 normally closed terminal, and one normally open terminal. When the coil of the relay is at rest (not energized), the common terminal and the normally closed terminal have continuity. When the coil is energized, the common terminal and the normally open terminal have continuity. This relay's coil is rated up to 5V and the contact is rated up to 30A (@250VAC, 30VDC).You can use it to control high current devices."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-SPDT_Relay_30A/
//HACK_GUIDE_URL    https://github.com/Seeed-Studio/Grove_Drivers_for_Wio/wiki/Hardware-Hacking-Guide
//ADDED_AT          "2015-10-01"
//AUTHOR            "SEEED"

class GroveSPDTRelay30A
{
public:
    GroveSPDTRelay30A(int pin);
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
