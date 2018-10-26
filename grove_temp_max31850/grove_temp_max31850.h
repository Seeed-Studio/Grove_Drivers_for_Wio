/*
 * grove_temp_max31850.h
 *
 * Copyright (c) 2018 Seeed K.K.
 * Website    : www.seeed.co.jp
 * Author     : Takashi Matsuoka
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


#ifndef __GROVE_TEMP_MAX31850_H__
#define __GROVE_TEMP_MAX31850_H__

#include "suli2.h"

//GROVE_NAME        "Grove - 1-Wire Thermocouple Amplifier (MAX31850K)"
//SKU               101020555
//IF_TYPE           GPIO
//IMAGE_URL         https://statics3.seeedstudio.com/seeed/file/2018-09/bazaar937434_img_0086a.JPG
//DESCRIPTION       "The Grove - 1-Wire Thermocouple Amplifier (MAX31850K) is a thermocouple-to-digital converters with 14-bit resolution and cold-junction compensation."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-1-Wire_Thermocouple_Amplifier-MAX31850K/
//ADDED_AT          "2018-10-26"
//AUTHOR            "Seeed K.K."

class GroveTempMAX31850
{
public:
	GroveTempMAX31850(int pin);

    /**
     * Read the celsius temperature from the temperature sensor.
     *
     * @param temperature - celsius degree.
     *
     * @return bool
     */
    bool read_temp(float *temperature);

private:
	IO_T *io;

	void pin_write(int value)
	{
		if (value) {
			suli_pin_dir(io, SULI_INPUT);
		}
		else {
			suli_pin_dir(io, SULI_OUTPUT);
			suli_pin_write(io, SULI_LOW);
		}
	}

	int pin_read()
	{
		return suli_pin_read(io) != SULI_LOW ? 1 : 0;
	}

	bool onewire_reset();
	bool onewire_skip_rom();
	int onewire_read_scratchpad(uint8_t* data, int dataSize);
	bool onewire_convert_t();

	bool internal_write_byte(uint8_t data);
	bool internal_read_byte(uint8_t* data);

};

#endif
