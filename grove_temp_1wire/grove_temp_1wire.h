/*
 * grove_temp_1wire.h
 *
 * Copyright (c) 2017 Seeed K.K.
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


#ifndef __GROVE_TEMP_1WIRE_H__
#define __GROVE_TEMP_1WIRE_H__

#include "suli2.h"

//GROVE_NAME        "One Wire Temperature Sensor"
//SKU               101990019
//IF_TYPE           GPIO
//IMAGE_URL         https://statics3.seeedstudio.com/images/product/onewiretempsensor.jpg
//DESCRIPTION       "This 2m long One Wire Temperature Sensor has a waterproof probe and long wire shape, suitable for immersive temperature detection. Wide temperature range: -55°C to +125°C."
//WIKI_URL          https://www.seeedstudio.com/One-Wire-Temperature-Sensor-p-1235.html
//ADDED_AT          "2017-10-04"
//AUTHOR            "Seeed K.K."

class GroveTemp1Wire
{
public:
	GroveTemp1Wire(int pin);

    /**
     * Read the celsius temperature from the temperature sensor.
     *
     * @param temperature - celsius degree with an accuracy of +-0.5ｰC .
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
	bool onewire_write_scratchpad(uint8_t th, uint8_t tl, uint8_t config);
	int onewire_read_scratchpad(uint8_t* data, int dataSize);
	bool onewire_convert_t();

	bool internal_write_byte(uint8_t data);
	bool internal_read_byte(uint8_t* data);

};

#endif
