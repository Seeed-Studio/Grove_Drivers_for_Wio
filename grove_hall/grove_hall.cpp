/*
 * grove_hall.cpp
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
#include "grove_hall.h"



GroveHall::GroveHall(int pin)
{
    this->io = (IO_T *)malloc(sizeof(IO_T));

    //somehow, SULI_INPUT tries to pull down the line state,
    //so we use the OUTPUT. It's ok to read the pin state though.
    suli_pin_init(io, pin, SULI_INPUT_PULLUP);
    time = millis();

    suli_pin_attach_interrupt_handler(io, &hall_state_change_interrupt_handler, SULI_CHANGE, this);
}

bool GroveHall::read_vout(uint8_t *vout)
{
    *vout = suli_pin_read(io);
    return true;
}


static void hall_state_change_interrupt_handler(void *para)
{
    GroveHall *g = (GroveHall *)para;
    if (millis() - g->time < 100)
    {
        return;
    }
    g->time = millis();

    if (suli_pin_read(g->io))
    {
        POST_EVENT_IN_INSTANCE(g, state_off, g->io);
    } else
    {
        POST_EVENT_IN_INSTANCE(g, state_on, g->io);
    }
}


