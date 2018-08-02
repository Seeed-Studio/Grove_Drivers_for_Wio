/*
 * grove_servo.h
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


#ifndef __GROVE_SERVO_H__
#define __GROVE_SERVO_H__

#include "suli2.h"

//GROVE_NAME        "Grove-Servo"
//SKU               316010005
//IF_TYPE           GPIO
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/grove-servo.jpg
//DESCRIPTION       "Grove - Servo is DC motor with gearing and feedback system. It is used in driving mechanism of robots. The module is a bonus product for Grove lovers. We regulated the three-wire servo into a Grove standard connector. You can plug and play it as a typical Grove module now, without jumper wires clutter. But if you feel more like a proto servo, check out EMAX 9g ES08A High Sensitive Mini Servo. They are the same model, both of good quality and burden-free price."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-Servo/
//ADDED_AT          "2015-10-01"
//AUTHOR            "SEEED"

class GroveServo
{
public:
    GroveServo(int pin);

    /**
     * Drive the servo to rotate a specified angle and hold on the servo driven PWM signal. <br>
     * The PWM signal maybe polluted by other PWM API calls if the others use different frequency. <br>
     * e.g. Grove - Infrared Emitter may affect the action of servo as it's using 38KHz PWM.
     *
     * @param degree - the angle in unit degress
     *
     * @return bool
     */
    bool write_angle(int degree);

    /**
     * Drive the servo to rotate a specified angle and shut down the servo driven PWM signal in specified seconds time. <br>
     * For normal servos, this API still works even if the PWM signal is off. But the servo losts the strength that holding the position. <br>
     * This API will avoid the servo from the influence of other PWM modules, e.g. Grove - Infrared Emitter
     *
     * @param degree - the angle in unit degress
     * @param seconds - the duration of the motion
     *
     * @return bool
     */
    bool write_angle_motion_in_seconds(int degree, int seconds);

    /**
     * Read back the angle of this servo
     *
     * @param degree - the angle in unit degress
     *
     * @return bool
     */
    bool read_angle(int *degree);



    PWM_T *io;
    TIMER_T *timer;
    int last_degree;

};

static void grove_servo_timer_interrupt_handler(void *para);



#endif
