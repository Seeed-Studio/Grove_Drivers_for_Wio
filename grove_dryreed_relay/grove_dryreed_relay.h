/*
 * grove_dryreed_relay.h
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


#ifndef __GROVE_DRYREED_RELAY_H__
#define __GROVE_DRYREED_RELAY_H__

#include "suli2.h"

//GROVE_NAME        "Grove-Dry-Reed Relay"
//SKU               103020014
//IF_TYPE           GPIO
//IMAGE_URL         https://s3-us-west-2.amazonaws.com/wio.seeed.cc/static/driver_images/grove-dryreed-relay.jpg
//DESCRIPTION       "The module is a relay module which works through magnetizing the vibration reed via the current in the coils. Compared to electromagnetic relays, the contacts completely sealed is the biggest feature of the Dry-Reed Relay. Besides, it features simplicity in construct, compactness, fast speed and long life, which make it widely applied in many fields such as microelectronic detection, Automatic Control etc."
//WIKI_URL          http://www.seeedstudio.com/wiki/Grove_-_Dry-Reed_Relay
//ADDED_AT          "2015-10-01"
//AUTHOR            "SEEED"

class GroveDryReedRelay
{
public:
    GroveDryReedRelay(int pin);
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
