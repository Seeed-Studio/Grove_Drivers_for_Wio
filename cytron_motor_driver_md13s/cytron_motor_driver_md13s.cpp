/*
 * cytron_motor_driver_md13s.cpp
 *
 * Copyright (c) 2016 Cytron Technologies Sdn Bhd.
 * Website    : www.cytron.com.my
 * Author     : Kong Wai Weng (waiweng@cytron.com.my)
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
#include "cytron_motor_driver_md13s.h"

CytronMD13S::CytronMD13S(int pintx, int pinrx)
{
    this->io_pwm = (PWM_T *)malloc(sizeof(PWM_T));
    this->io_dir = (IO_T *)malloc(sizeof(IO_T));

    suli_pwm_init(this->io_pwm, pintx);
    suli_pin_init(this->io_dir, pinrx, SULI_OUTPUT);
    
    this->speed = 0.0;
    
    suli_pwm_output(this->io_pwm, 0.0);
    suli_pin_write(this->io_dir, SULI_LOW);
}



bool CytronMD13S::write_speed(float speed)
{
    this->speed = speed;
    suli_pwm_output(this->io_pwm, speed);
    
    return true;
}

bool CytronMD13S::read_speed(float *speed)
{
    *speed = this->speed;
    
    return true;
}



bool CytronMD13S::write_direction(int direction)
{
    suli_pin_write(this->io_dir, direction);
    return true;
}

bool CytronMD13S::read_direction(int *direction)
{
    *direction = suli_pin_read(this->io_dir);
    return true;
}



bool CytronMD13S::write_speed_dir(float speed, int direction)
{
    this->speed = speed;
    suli_pwm_output(this->io_pwm, speed);
    suli_pin_write(this->io_dir, direction);
    
    return true;
}

bool CytronMD13S::read_speed_dir(float *speed, int *direction)
{
    *speed = this->speed;
    *direction = suli_pin_read(this->io_dir);
    
    return true;
}
