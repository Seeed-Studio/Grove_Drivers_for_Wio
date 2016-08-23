/*
 * grove_recorder.h
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


#ifndef __GROVE_RECORDER_H__
#define __GROVE_RECORDER_H__

#include "suli2.h"

//GROVE_NAME        "Grove-Recorder"
//SKU               103020018
//IF_TYPE           GPIO
//IMAGE_URL         https://s3-us-west-2.amazonaws.com/wio.seeed.cc/static/driver_images/Grove-Recorder.jpg
//DESCRIPTION       "Grove - Recorder is based on ISD1820P, which can record 8~20 sec by set resistor and cycle play. It can offers true single-chip voice recording, no-volatile storage. Grove - Recorder is 100K and the total 10s for Recorder. This module is very easy to control, which can direct control by push button on board or by microcontroller. "
//WIKI_URL          http://www.seeedstudio.com/wiki/Grove_-_Recorder
//ADDED_AT          "2015-10-01"
//AUTHOR            "SEEED"

class GroveRecorder
{
public:
    GroveRecorder(int pin);

    /**
     * Play the sound which is recorded once.
     *
     * @param
     *
     * @return bool
     */
    bool write_play_once();
private:
    IO_T *io;
};


#endif
