/*
* grove_luminance.cpp
*
* Copyright (c) 2016 seeed technology inc.
* Website    : www.seeed.cc
* Author     : Travis Brown (warriorrocker@gmail.com)
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
#include "grove_luminance.h"

GroveLuminance::GroveLuminance(int pin)
{
    this->io = (ANALOG_T *)malloc(sizeof(ANALOG_T));
    suli_analog_init(io, pin);
}

bool GroveLuminance::read_luminance(float *lux)
{
    float vout_array[] = { 0.0011498, 0.0033908, 0.011498, 0.041803, 0.15199, 0.53367, 1.3689, 1.9068, 2.3 };
    float  lux_array[] = { 1.0108,    3.1201,    9.8051,   27.43,    69.545,  232.67,  645.11, 973.52, 1000 };

    float vout = suli_analog_voltage(io);
    *lux = _multi_map(vout, vout_array, lux_array, 9);

    return true;
}

float GroveLuminance::_multi_map(float val, float * _in, float * _out, uint8_t size)
{
    // take care the value is within range
    // val = constrain(val, _in[0], _in[size-1]);
    if (val <= _in[0]) return _out[0];
    if (val >= _in[size - 1]) return _out[size - 1];

    // search right interval
    uint8_t pos = 1;  // _in[0] allready tested
    while (val > _in[pos]) pos++;

    // this will handle all exact "points" in the _in array
    if (val == _in[pos]) return _out[pos];

    // interpolate in the right segment for the rest
    return (val - _in[pos - 1]) * (_out[pos] - _out[pos - 1]) / (_in[pos] - _in[pos - 1]) + _out[pos - 1];
}
