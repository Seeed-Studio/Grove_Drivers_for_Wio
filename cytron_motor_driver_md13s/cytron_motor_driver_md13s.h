/*
 * cytron_motor_driver_md13s.h
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


#ifndef __CYTRON_MOTOR_DRIVER_MD13S_H__
#define __CYTRON_MOTOR_DRIVER_MD13S_H__

#include "suli2.h"

//GROVE_NAME        "Cytron 13Amp DC Motor Driver - SMD Compatible (MD13S)"
//SKU               MD13S
//IF_TYPE           UART
//IMAGE_URL         https://c6.staticflickr.com/9/8757/28828082141_246df104a1.jpg
//DESCRIPTION       "Grove compatible DC motor driver which supports 6-30V, 30A peak and 13A continuous current."
//WIKI_URL          https://docs.google.com/document/d/1icu1GVDxZhUn3ADSUc3JknNcmUMdPcsnJ4MhxOPRo-I/view
//ADDED_AT          "2016-08-10"
//AUTHOR            "CYTRON"

class CytronMD13S
{
public:
    CytronMD13S(int pintx, int pinrx);

    /**
     * Change the motor speed. The initial speed is 0 when the module is powered on.
     *
     * @param speed - motor speed, 0.0~100.0
     *
     * @return bool
     */
    bool write_speed(float speed);

    /**
     * Read the motor speed. This is the PWM duty cycle and is not the actual motor speed.
     *
     * @param speed - motor speed, 0.0~100.0
     *
     * @return bool
     */
    bool read_speed(float *speed);
    
    
    
    /**
     * Change the motor direction. The initial direction is 0 when the module is powered on.
     *
     * @param direction - motor direction, 0 or 1
     *
     * @return bool
     */
    bool write_direction(int direction);
    
    /**
     * Read the motor direction.
     *
     * @param direction - motor direction, 0 or 1
     *
     * @return bool
     */
    bool read_direction(int *direction);
    
    
    
    /**
     * Change the motor speed and direction together.
     *
     * @param speed - motor speed, 0.0~100.0
     * @param direction - motor direction, 0 or 1
     *
     * @return bool
     */
    bool write_speed_dir(float speed, int direction);
    
    
    /**
     * Read the motor speed and direction together.
     *
     * @param speed - motor speed, 0.0~100.0
     * @param direction - motor direction, 0 or 1
     *
     * @return bool
     */
    bool read_speed_dir(float *speed, int *direction);
    


private:
    PWM_T *io_pwm;
    IO_T *io_dir;
    
    float speed;
};


#endif
