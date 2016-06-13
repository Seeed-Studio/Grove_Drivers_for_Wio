/*
 * grove_i2c_adc.cpp
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


#include "suli2.h"
#include "grove_i2c_adc.h"

GroveI2CAdc::GroveI2CAdc(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    suli_i2c_init(this->i2c, pinsda, pinscl);
    on_power_on();
}

bool GroveI2CAdc::on_power_on()
{
    uint8_t r = 0x20;
    suli_i2c_write_reg(i2c, ADDR_ADC121, REG_ADDR_CONFIG, &r, 1);
    power_on = true;
    return true;
}

bool GroveI2CAdc::on_power_off()
{
    power_on = false;
    return true;
}

bool GroveI2CAdc::read_adc(uint32_t *adc_reading)
{
    if (!power_on)
    {
        *adc_reading = 0;
        return true;
    }

    uint8_t result[2];
    uint32_t adc_readings[100];

    for (int i = 0; i < 100;i++)
    {
        suli_i2c_read_reg(i2c, ADDR_ADC121, REG_ADDR_RESULT, result, 2);
        adc_readings[i] = (result[0] << 8) | result[1];
    }

    uint32_t temp= 0;

    for(int i=0;i<100;i++)
    {
        for(int j=i+1;j<100;j++)
        {
            if(adc_readings[i] > adc_readings[j])
            {
                temp = adc_readings[i];
                adc_readings[i] = adc_readings[j];
                adc_readings[j] = temp;
            }
        }
    }

    temp = 0;
    for (int i = 20; i < 80; i++)
    {
        temp += adc_readings[i];
    }

    *adc_reading = temp/60;

    return true;
}

bool GroveI2CAdc::read_voltage(float *volt)
{
    if (!power_on)
    {
        *volt = 0.0f;
        return true;
    }

    uint32_t adc;
    read_adc(&adc);

    float ret = adc * V_REF * 2 / 4096;

    *volt = ret;

    return true;
}


