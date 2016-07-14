/*
* grove_i2c_fm_receiver.cpp
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
#include "grove_i2c_fm_receiver.h"

GroveI2cFmReceiver::GroveI2cFmReceiver(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    suli_i2c_init(this->i2c, pinsda, pinscl);

    _fmrecv_init();
    _fmrecv_set_control_reg();
    _fmrecv_set_volume_level();
    _fmrecv_set_frequency();
}

bool GroveI2cFmReceiver::read_signal_level(uint8_t *signal_level)
{
    *signal_level = _fmrecv_get_signal_level();
    return true;
}

bool GroveI2cFmReceiver::read_mute_status(bool *muted) {
    *muted = !_mute_disable_bit;
    return true;
}

bool GroveI2cFmReceiver::write_mute(bool mute)
{
    _mute_disable_bit = !mute;
    _fmrecv_set_control_reg();
    return true;
}

bool GroveI2cFmReceiver::read_volume(uint8_t *level) {
    *level = _volume;
    return true;
}

bool GroveI2cFmReceiver::write_volume(uint8_t level)
{
    _volume = constrain(level, 0, 15);
    _fmrecv_set_volume_level();
    return true;
}

bool GroveI2cFmReceiver::read_frequency(uint16_t *frequency) {
    *frequency = _frequency;
    return true;
}

bool GroveI2cFmReceiver::write_frequency(uint16_t frequency)
{
     _mute_disable_bit = true;
    _fmrecv_set_control_reg();

    _frequency = frequency;
    _fmrecv_set_frequency();

    return true;
}

void GroveI2cFmReceiver::_fmrecv_init()
{
    uint8_t i = 0;
    uint8_t init_data[] = {
        0xC4, 0x05, 0x00, 0x00, 0x04, 0x00, 0xC3, 0xad,
        0x60, 0x00, 0x42, 0x12, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19,
        0x2a, 0x11, 0xB0, 0x42, 0x2A, 0x11, 0xb8, 0x31,
        0xc0, 0x00, 0x2a, 0x91, 0x94, 0x00, 0x00, 0xa8,
        0xc4, 0x00, 0xF7, 0xcF, 0x12, 0x14, 0x80, 0x6F,
        0x46, 0x08, 0x00, 0x86, 0x06, 0x61, 0x00, 0x00,
        0x10, 0x9E, 0x23, 0xC8, 0x04, 0x06, 0x0E, 0x1C
    };

    for (i = 0; i < 8; i++)
        _reg_data[i] = init_data[i];

    suli_i2c_write(i2c, FMRECV_ADDRESS, &init_data[0], sizeof(init_data));
}

uint16_t GroveI2cFmReceiver::_fmrecv_get_chip_id() {
    uint8_t data[10];
    suli_i2c_read(i2c, FMRECV_ADDRESS, data, 10);
    return ((data[8] << 8) | data[9]);
}

uint8_t GroveI2cFmReceiver::_fmrecv_get_signal_level()
{
    uint8_t data[4];
    suli_i2c_read(i2c, FMRECV_ADDRESS, data, 4);
    return (data[2] >> 1);
}

void GroveI2cFmReceiver::_fmrecv_set_control_reg()
{
    _reg_data[0] = (1 << 7) | (1 << 2)
        | (_mute_disable_bit << 6)
        | (_mono_enable_bit << 5)
        | (_bass_enable_bit << 4);

    suli_i2c_write(i2c, FMRECV_ADDRESS, &_reg_data[0], 2);
}

void GroveI2cFmReceiver::_fmrecv_set_volume_level()
{
    _reg_data[3] &= (~(0x10));
    _reg_data[7] = ((_reg_data[7] & 0xf0) | (_volume & 0x0f));

    suli_i2c_write(i2c, FMRECV_ADDRESS, &_reg_data[0], 8);
}

void GroveI2cFmReceiver::_fmrecv_set_frequency()
{
    uint16_t channel = 0;

    if ((_frequency >= 6500) && (_frequency < 7600))
    {
        _reg_data[3] = 0x0c;
        channel = (_frequency - 6500) / _station_step;

    }
    else if ((_frequency >= 7600) && (_frequency < 10800))
    {
        _reg_data[3] = 0x08;
        channel = (_frequency - 7600) / _station_step;
    }

    _reg_data[2] = channel >> 2;
    _reg_data[3] = (((channel & 0x0003) << 6) | 0x10) | (_reg_data[3] & 0x0f);

    suli_i2c_write(i2c, FMRECV_ADDRESS, &_reg_data[0], 4);
}