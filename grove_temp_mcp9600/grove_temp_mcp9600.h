/*
 * grove_temp_mcp9600.h
 *
 * Copyright (c) 2019 Seeed K.K.
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


#ifndef __GROVE_TEMP_MCP9600_H__
#define __GROVE_TEMP_MCP9600_H__

#include "suli2.h"

//GROVE_NAME        "Grove - I2C Thermocouple Amplifier (MCP9600)"
//SKU               101020594
//IF_TYPE           I2C
//IMAGE_URL         https://www.seeedstudio.com/media/catalog/product/cache/9d0ce51a71ce6a79dfa2a98d65a0f0bd/h/t/httpsstatics3.seeedstudio.comseeedfile2018-10bazaar970557_1.jpg
//DESCRIPTION       "The Grove - I2C Thermocouple Amplifier (MCP9600) is a thermocouple-to-digital converter with integrated cold-junction and I2C communication protocol."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-I2C_Thermocouple_Amplifier-MCP9600/
//ADDED_AT          "2019-08-27"
//AUTHOR            "Seeed K.K."

class GroveTempMCP9600
{
public:
    GroveTempMCP9600(int pinsda, int pinscl);

    /**
     * Set thermocouple type
     *
     * @param type - 0:K, 1:J, 2:T, 3:N, 4:S, 5:E, 6:B, 7:R
     *
     * @return bool
     */
    bool write_thermocouple_type(int type);

    /**
     * Read the temperature value of the envirenment
     *
     * @param temperature - unit: Celsius degree
     *
     * @return bool
     */
    bool read_temp(float *temperature);

private:
    I2C_T *i2c;
	bool error;

};

#endif
