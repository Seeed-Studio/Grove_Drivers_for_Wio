/*
 * grove_encoder.h
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jack Shao
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


#ifndef __GROVE_ENCODER_H__
#define __GROVE_ENCODER_H__

#include "suli2.h"

//GROVE_NAME        "Grove - Encoder"
//SKU               111020001
//IF_TYPE           UART
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/grove-encoder.jpg
//DESCRIPTION       "This module is an incremental rotary encoder. It encodes the rotation signal from the axis and output the signal by electronic pulse. "
//WIKI_URL          http://wiki.seeedstudio.com/Grove-Encoder/
//HACK_GUIDE_URL    https://github.com/Seeed-Studio/Grove_Drivers_for_Wio/wiki/Hardware-Hacking-Guide
//ADDED_AT          "2015-12-01"
//AUTHOR            "SEEED"

class GroveEncoder
{
public:

    GroveEncoder(int pintx, int pinrx);

    bool on_power_on();
    bool on_power_off();

    /**
     * Read the position of the encoder. The position can be positive or negative number.
     * The position increases when rotate clockwise and decreases when rotate anti-clockwise. <br>
     * <br>
     * PLEASE NOTE: To use the encoder, you need either using battery to power the board or manually soldering to short R1 of Grove-Encoder.
     * This is due to the RX pin of UART interface is pulled up to CP2102's TX pin with a 1K resister and R1 on encoder board
     * with the value 3.3K will obstruct the encoder to correctly pull down the signal A pin.
     *
     * @param position
     *
     * @return bool
     */
    bool read_position(int32_t *position);

    /**
     * Reset the position to a specified number.
     *
     * @param position
     *
     * @return bool
     */
    bool write_reset_position(int32_t position);

    /**
     * Enable or disable the acceleration feature of the step counting.
     *
     * @param enable - 1: enable acceleration, 0: disable
     *
     * @return bool
     */
    bool write_enable_acceleration(uint8_t enable);

    /**
     * Report the current position when the knob idles for 100ms. The event data is the current position.
     * <br>
     * PLEASE NOTE: To use the encoder, you need either using battery to power the board or manually soldering to short R1 of Grove-Encoder.
     * This is due to the RX pin of UART interface is pulled up to CP2102's TX pin with a 1K resister and R1 on encoder board
     * with the value 3.3K will obstruct the encoder to correctly pull down the signal A pin.
     */
    DEFINE_EVENT(encoder_position, SULI_EDT_INT32);


private:
    IO_T *io_a;  // siga pin
    IO_T *io_b;  // sigb pin
    TIMER_T *timer;

    int32_t pos;
    bool pinsActive;
    volatile int16_t delta;
    volatile int16_t last;
    uint8_t steps;
    bool accelerationEnabled;
    volatile uint16_t acceleration;
    uint8_t ms_cnt;

public:
    void update() ICACHE_RAM_ATTR;

};


static void timer_handler_encoder_update(void *para) ICACHE_RAM_ATTR;

#endif
