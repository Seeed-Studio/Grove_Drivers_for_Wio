/*
 * grove_i2c_adc.h
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jack Shao jack.shaoxg@gmail.com
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


#ifndef __GROVE_I2C_ADC_H__
#define __GROVE_I2C_ADC_H__

#include "suli2.h"

//GROVE_NAME        "Grove - I2C ADC"
//SKU               103020013
//IF_TYPE           I2C
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/grove-i2c-adc.jpg
//DESCRIPTION       "Grove - I2C ADC is a 12-bit precision ADC module based on ADC121C021."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-I2C_ADC/
//ADDED_AT          "2016-05-31"
//AUTHOR            "SEEED"

#define ADDR_ADC121             (0x55<<1)

#define V_REF 3.30

#define REG_ADDR_RESULT         0x00
#define REG_ADDR_ALERT          0x01
#define REG_ADDR_CONFIG         0x02
#define REG_ADDR_LIMITL         0x03
#define REG_ADDR_LIMITH         0x04
#define REG_ADDR_HYST           0x05
#define REG_ADDR_CONVL          0x06
#define REG_ADDR_CONVH          0x07




class GroveI2CAdc
{
public:
    GroveI2CAdc(int pinsda, int pinscl);

    bool on_power_on();
    bool on_power_off();

    /**
     * Read the 12bit value from ADC.
     *
     * @param adc_reading - 12bit adc result, max 2048 as the voltage-dividing
     *
     * @return bool
     */
    bool read_adc(uint32_t *adc_reading);

    /**
     * Read the voltage which is calculated against ref voltage 3.3V
     *
     * @param volt - unit: volt
     *
     * @return bool
     */
    bool read_voltage(float *volt);

//private:
    I2C_T *i2c;
    bool power_on = true;

};

#endif
