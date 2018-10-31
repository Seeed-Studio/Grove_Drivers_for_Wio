/*
 * grove_temp_max31850.cpp
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

#include "suli2.h"
#include "grove_temp_max31850.h"
#include "math.h"

GroveTempMAX31850::GroveTempMAX31850(int pin)
{
	this->io = (IO_T *)malloc(sizeof(IO_T));

	suli_pin_init(io, pin, SULI_INPUT);
	pin_write(1);
}

bool GroveTempMAX31850::read_temp(float *temperature)
{
	if (!onewire_reset()) return false;
	if (!onewire_skip_rom()) return false;
	if (!onewire_convert_t()) return false;

	if (!onewire_reset()) return false;
	if (!onewire_skip_rom()) return false;
	uint8_t data[9];
	if (onewire_read_scratchpad(data, sizeof(data)) != 9) return false;

	*temperature = (float)(*(int16_t*)&data[0] >> 2) / 4.f;

    return true;
}

bool GroveTempMAX31850::onewire_reset()
{
	pin_write(0);
	suli_delay_us(480);
	pin_write(1);
	suli_delay_us(480);

	// Check bus.
	if (!pin_read()) return false;

	return true;
}

bool GroveTempMAX31850::onewire_skip_rom()
{
	if (!internal_write_byte(0xcc)) return false;	// Skip Rom

	return true;
}

int GroveTempMAX31850::onewire_read_scratchpad(uint8_t* data, int dataSize)
{
	if (dataSize < 9) return -1;

	internal_write_byte(0xbe);	// Write Scratchpad
	for (int i = 0; i < 9; i++) {
		if (!internal_read_byte(&data[i])) return -1;
	}

	return 9;
}

bool GroveTempMAX31850::onewire_convert_t()
{
	if (!internal_write_byte(0x44)) return false;	// Convert T

	int done;
	do {
		// Start of slot.
		pin_write(0);
		suli_delay_us(1);

		// free bus.
		pin_write(1);
		suli_delay_us(9);

		// Read.
		done = pin_read();

		// End of slot.
		suli_delay_us(50);

		// Check bus.
		if (!pin_read()) return false;
	}
	while (!done);

	return true;
}

bool GroveTempMAX31850::internal_write_byte(uint8_t data)
{
	for (int i = 0; i < 8; i++) {
		// Start of slot.
		pin_write(0);
		suli_delay_us(1);

		if (data & 1 << i) {
			// Write 1.
			pin_write(1);
			suli_delay_us(59);
		}
		else {
			// Write 0.
			suli_delay_us(59);
		}

		// End of slot.
		pin_write(1);
		suli_delay_us(1);

		// Check bus.
		if (!pin_read()) return false;
	}

	return true;
}

bool GroveTempMAX31850::internal_read_byte(uint8_t* data)
{
	*data = 0;

	for (int i = 0; i < 8; i++) {
		// Start of slot.
		pin_write(0);
		suli_delay_us(1);

		// free bus.
		pin_write(1);
		suli_delay_us(9);

		// Read.
		*data |= pin_read() << i;

		// End of slot.
		suli_delay_us(50);

		// Check bus.
		if (!pin_read()) return false;
	}

	return true;
}
