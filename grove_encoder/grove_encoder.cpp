/*
 * grove_encoder.cpp
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


#include "suli2.h"
#include "grove_encoder.h"

// ----------------------------------------------------------------------------
// Acceleration configuration (for 1000Hz calls to ::service())
//
#define ENC_ACCEL_TOP      3072   // max. acceleration: *12 (val >> 8)
#define ENC_ACCEL_INC        25
#define ENC_ACCEL_DEC         2


#define IDLE_TIME               100


GroveEncoder::GroveEncoder(int pintx, int pinrx)
{
    this->io_a = (IO_T *)malloc(sizeof(IO_T));
    this->io_b = (IO_T *)malloc(sizeof(IO_T));
    this->timer = (TIMER_T *)malloc(sizeof(TIMER_T));

    suli_pin_init(io_a, pinrx, SULI_INPUT);
    suli_pin_init(io_b, pintx, SULI_INPUT);

    //suli_pin_write(io_a, SULI_HIGH);
    //suli_pin_write(io_b, SULI_HIGH);

    pos = 0;
    
    pinsActive = 0;
    steps = 4;
    delta = 0;
    last = 0;
    accelerationEnabled = true;

    on_power_on();
}

bool GroveEncoder::on_power_on()
{
    ms_cnt = 0;
    
    suli_timer_install(timer,  1000, timer_handler_encoder_update, this, true);

    if (suli_pin_read(io_a) == pinsActive)
    {
        last = 3;
    }

    if (suli_pin_read(io_b) == pinsActive)
    {
        last ^= 1;
    }

    return true;
}

bool GroveEncoder::on_power_off()
{
    suli_timer_remove(timer);
    return true;
}

bool GroveEncoder::read_position(int32_t *position)
{
    *position = pos;
    return true;
}

bool GroveEncoder::write_reset_position(int32_t position)
{
    pos = position;
    return true;
}

bool GroveEncoder::write_enable_acceleration(uint8_t enable)
{
    accelerationEnabled = enable;
    return true;
}

void GroveEncoder::update()
{
    bool moved = false;

    if (accelerationEnabled) // decelerate every tick
    {
        acceleration -= ENC_ACCEL_DEC;
        if (acceleration & 0x8000) // handle overflow of MSB is set
        {
            acceleration = 0;
        }
    }

    int8_t curr = 0;

    if (suli_pin_read(io_a) == pinsActive)
    {
        curr = 3;
    }

    if (suli_pin_read(io_b) == pinsActive)
    {
        curr ^= 1;
    }

    int8_t diff = last - curr;

    if (diff & 1)            // bit 0 = step
    {
        last = curr;
        delta += (diff & 2) - 1; // bit 1 = direction (+/-)
        moved = true;
    }

    if (accelerationEnabled && moved)
    {
        // increment accelerator if encoder has been moved
        if (acceleration <= (ENC_ACCEL_TOP - ENC_ACCEL_INC))
        {
            acceleration += ENC_ACCEL_INC;
        }
    }

    int16_t val = delta;

    if (steps == 2) delta = val & 1;
    else if (steps == 4) delta = val & 3;
    else delta = 0; // default to 1 step per notch

    if (steps == 4) val >>= 2;
    if (steps == 2) val >>= 1;

    int16_t r = 0;
    int16_t accel = ((accelerationEnabled) ? (acceleration >> 8) : 0);

    if (val < 0)
    {
        r -= 1 + accel;
    } else if (val > 0)
    {
        r += 1 + accel;
    }

    pos += r;
    
    //handle the ide state
    if (!moved)
    {
        ms_cnt++;
        if (ms_cnt == IDLE_TIME) 
        {
            //send event here
            POST_EVENT(encoder_position, &pos);
        }
        if (ms_cnt > 200)
        {
            ms_cnt = 200;
        }
    } else ms_cnt = 0;

}


static void timer_handler_encoder_update(void *para)
{

    GroveEncoder *g = (GroveEncoder *)para;
    g->update();

}



