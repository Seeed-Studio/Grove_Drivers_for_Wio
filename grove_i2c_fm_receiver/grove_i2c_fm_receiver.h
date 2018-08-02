/*
* grove_i2c_fm_receiver.h
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


#ifndef __GROVE_I2C_FM_RECEIVER_H__
#define __GROVE_I2C_FM_RECEIVER_H__

#include "suli2.h"

//GROVE_NAME        "Grove - I2C FM Receiver"
//SKU               107020006
//IF_TYPE           I2C
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/Grove-I2C_FM_Receiver.jpg
//DESCRIPTION       "Grove - I2C FM Receiver is a wideband FM receiver module, this module is based on RDA5807M. The RDA5807M series is the newest generation single-chip broadcast FM stereo radio tuner with fully integrated synthesizer."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-I2C_FM_Receiver/
//ADDED_AT          "2016-07-01"
//AUTHOR            "Travis Brown"

// Device i2c address
#define FMRECV_ADDRESS         (0x10 << 1)

// Set debug flag
#define FMRECV_DEBUG           1

class GroveI2cFmReceiver
{
public:
    GroveI2cFmReceiver(int pinsda, int pinscl);

    /**
    * Read current signal level.
    *
    * @param rssi - int
    *
    * @return bool
    */
    bool read_signal_level(uint8_t *rssi);

    /**
    * Read current mute setting.
    *
    * @param muted - 1: on, 0: off
    *
    * @return bool
    */
    bool read_mute_status(bool *muted);

    /**
    * Toggle mute on or off.
    *
    * @param mute - 1: on, 0: off
    *
    * @return bool
    */
    bool write_mute(bool mute);

    /**
    * Read current volume level setting.
    *
    * @param level - 0 - 15
    *
    * @return bool
    */
    bool read_volume(uint8_t *level);

    /**
    * Set volume level.
    *
    * @param level - 0 - 15
    *
    * @return bool
    */
    bool write_volume(uint8_t level);

    /**
    * Read current frequency setting.
    *
    * @param frequency
    *
    * @return bool
    */
    bool read_frequency(uint16_t *frequency);

    /**
    * Read current frequency setting.
    *
    * @param frequency
    *
    * @return bool
    */
    bool write_frequency(uint16_t frequency);

private:
    void _fmrecv_init();
    uint16_t _fmrecv_get_chip_id();
    uint8_t _fmrecv_get_signal_level();
    void _fmrecv_set_control_reg();
    void _fmrecv_set_volume_level();
    void _fmrecv_set_frequency();

    I2C_T *i2c;

    uint16_t _frequency = 10110;
    uint8_t _volume = 8;
    uint8_t _station_step = 10;
    bool _bass_enable_bit = true;
    bool _mono_enable_bit = false;
    bool _mute_disable_bit = false;

    uint8_t _reg_data[10];
};

#endif