/*
 * grove_oled_9696.cpp
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
#include "grove_oled_9696.h"
#include "base64.h"

const uint8_t BasicFont[][8] =
{
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},
    {0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},
    {0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},
    {0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},
    {0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},
    {0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},
    {0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},
    {0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},
    {0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},
    {0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},
    {0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},
    {0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},
    {0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},
    {0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},
    {0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},
    {0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},
    {0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},
    {0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},
    {0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},
    {0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},
    {0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},
    {0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},
    {0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},
    {0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},
    {0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},
    {0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},
    {0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},
    {0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},
    {0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},
    {0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},
    {0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},
    {0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},
    {0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},
    {0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},
    {0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},
    {0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},
    {0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},
    {0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},
    {0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},
    {0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},
    {0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},
    {0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},
    {0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},
    {0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},
    {0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},
    {0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},
    {0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},
    {0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},
    {0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},
    {0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},
    {0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},
    {0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},
    {0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},
    {0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},
    {0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
    {0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},
    {0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
    {0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},
    {0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},
    {0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},
    {0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},
    {0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},
    {0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},
    {0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},
    {0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},
    {0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},
    {0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},
    {0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},
    {0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},
    {0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},
    {0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},
    {0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},
    {0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},
    {0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},
    {0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},
    {0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},
    {0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},
    {0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},
    {0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},
    {0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},
    {0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},
    {0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},
    {0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},
    {0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},
    {0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},
    {0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00}
};

GroveOLED9696::GroveOLED9696(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    suli_i2c_init(this->i2c, pinsda, pinscl);
    _oled_96x96_init();
}

bool GroveOLED9696::write_clear()
{
    _oled_96x96_clear();
    return true;
}

bool GroveOLED9696::write_brightness(uint8_t brightness)
{
    _oled_96x96_cmd(OLED96_SET_CONTRAST_CMD);
    _oled_96x96_cmd(brightness);
    return true;
}

bool GroveOLED9696::write_integer(uint8_t row, uint8_t col, int32_t i)
{
    _oled_96x96_xy(row, col);
    _oled_96x96_num(i);
    return true;
}

bool GroveOLED9696::write_float(uint8_t row, uint8_t col, float floatNumber, uint8_t decimal)
{
    _oled_96x96_xy(row, col);
    _oled_96x96_float(floatNumber, decimal);
}

bool GroveOLED9696::write_string(uint8_t row, uint8_t col, char *str)
{
    _oled_96x96_xy(row, col);
    _oled_96x96_string(str);
    return true;
}

bool GroveOLED9696::write_base64_string(uint8_t row, uint8_t col, char *b64_str)
{
    _oled_96x96_xy(row, col);
    return _oled_96x96_string_base64(b64_str);
}

bool GroveOLED9696::write_scroll_left(uint8_t start_row, uint8_t end_row, uint8_t speed)
{
    _oled_96x96_cmd(OLED96_DEACTIVATE_SCROLL_CMD);
    _oled_96x96_h_scroll(false, start_row, end_row, speed);
    _oled_96x96_cmd(OLED96_ACTIVATE_SCROLL_CMD);
    return true;
}

bool GroveOLED9696::write_scroll_right(uint8_t start_row, uint8_t end_row, uint8_t speed)
{
    _oled_96x96_cmd(OLED96_DEACTIVATE_SCROLL_CMD);
    _oled_96x96_h_scroll(true, start_row, end_row, speed);
    _oled_96x96_cmd(OLED96_ACTIVATE_SCROLL_CMD);
    return true;
}

bool GroveOLED9696::write_stop_scroll()
{
    _oled_96x96_cmd(OLED96_DEACTIVATE_SCROLL_CMD);
    return true;
}

bool GroveOLED9696::write_inverse_display(uint8_t inverse_or_not)
{
    _oled_96x96_cmd((inverse_or_not) ? OLED96_INVERSE_DISPLAY_CMD : OLED96_NORMAL_DISPLAY_CMD);
    return true;
}

void GroveOLED9696::_oled_96x96_init() {
    _oled_96x96_cmd(0xFD);    // Unlock OLED driver IC MCU interface from entering command. i.e: Accept commands
    _oled_96x96_cmd(0x12);
    _oled_96x96_cmd(0xAE);    // Set display off
    _oled_96x96_cmd(0xA8);    // set multiplex ratio
    _oled_96x96_cmd(0x5F);    // 96
    _oled_96x96_cmd(0xA1);    // set display start line
    _oled_96x96_cmd(0x00);
    _oled_96x96_cmd(0xA2);    // set display offset
    _oled_96x96_cmd(0x60);
    _oled_96x96_cmd(0xA0);    // set remap
    _oled_96x96_cmd(0x46);
    _oled_96x96_cmd(0xAB);    // set vdd internal
    _oled_96x96_cmd(0x01);    //
    _oled_96x96_cmd(0x81);    // set contrast
    _oled_96x96_cmd(0x53);    // 100 nit
    _oled_96x96_cmd(0xB1);    // Set Phase Length
    _oled_96x96_cmd(0X51);    //
    _oled_96x96_cmd(0xB3);    // Set Display Clock Divide Ratio/Oscillator Frequency
    _oled_96x96_cmd(0x01);
    _oled_96x96_cmd(0xB9);    //
    _oled_96x96_cmd(0xBC);    // set pre_charge voltage/VCOMH
    _oled_96x96_cmd(0x08);    // (0x08);
    _oled_96x96_cmd(0xBE);    // set VCOMH
    _oled_96x96_cmd(0X07);    // (0x07);
    _oled_96x96_cmd(0xB6);    // Set second pre-charge period
    _oled_96x96_cmd(0x01);    //
    _oled_96x96_cmd(0xD5);    // enable second precharge and enternal vsl
    _oled_96x96_cmd(0X62);    // (0x62);
    _oled_96x96_cmd(0xA4);    // Set Normal Display Mode
    _oled_96x96_cmd(0x2E);    // Deactivate Scroll
    _oled_96x96_cmd(0xAF);    // Switch on display
    suli_delay_ms(100);

    // Row Address
    _oled_96x96_cmd(0x75);    // Set Row Address 
    _oled_96x96_cmd(0x00);    // Start 0
    _oled_96x96_cmd(0x5f);    // End 95 

    // Column Address
    _oled_96x96_cmd(0x15);    // Set Column Address 
    _oled_96x96_cmd(0x08);    // Start from 8th Column of driver IC. This is 0th Column for OLED 
    _oled_96x96_cmd(0x37);    // End at  (8 + 47)th column. Each Column has 2 pixels(segments)

    // Init gray level for text. Default:Brightest White
    _gray_high = 0xF0;
    _gray_low = 0x0F;
}

void GroveOLED9696::_oled_96x96_clear()
{
    unsigned char i, j;
    for (j = 0; j < 48; j++)
    {
        for (i = 0; i < 96; i++)
        {
            _oled_96x96_dta(0x00);
        }
    }
}

void GroveOLED9696::_oled_96x96_xy(uint8_t row, uint8_t column)
{
    _oled_96x96_cmd(0x15);                   // Set Column Address
    _oled_96x96_cmd(0x08 + (column * 4));    // Start Column: Start from 8
    _oled_96x96_cmd(0x37);                   // Row Address
    _oled_96x96_cmd(0x75);                   // Set Row Address
    _oled_96x96_cmd(0x00 + (row * 8));       // Start Row
    _oled_96x96_cmd(0x07 + (row * 8));       // End Row
}

void GroveOLED9696::_oled_96x96_char(uint8_t C)
{
    if (C == 255)
        return;

    if (C < 32 || C > 127) //Ignore non-printable ASCII characters. This can be modified for multilingual font.
        C = ' '; //Space

    for (char i = 0; i < 8; i = i + 2)
    {
        for (char j = 0; j < 8; j++)
        {
            // Character is constructed two pixel at a time using vertical mode from the default 8x8 font
            char c = 0x00;
            char bit1 = (BasicFont[C - 32][i] >> j) & 0x01;
            char bit2 = (BasicFont[C - 32][i + 1] >> j) & 0x01;
            // Each bit is changed to a nibble
            c |= (bit1) ? _gray_high : 0x00;
            c |= (bit2) ? _gray_low : 0x00;
            _oled_96x96_dta(c);
        }
    }
}

void GroveOLED9696::_oled_96x96_string(const char *str)
{
    unsigned char i = 0;
    while (str[i])
    {
        _oled_96x96_char(str[i]);
        i++;
    }
}

bool GroveOLED9696::_oled_96x96_string_base64(const char *b64_str) {
    int len = strlen(b64_str);
    uint8_t *buf = (uint8_t *)malloc(len);

    if (!buf)
    {
        error_desc = "run out of memory";
        return false;
    }
    if (base64_decode(buf, &len, (const unsigned char *)b64_str, len) != 0)
    {
        error_desc = "base64_decode error";
        return false;
    }
    buf[len] = '\0';

    //len = strlen(buf);
    int i = 0;

    while (buf[i])
    {
        if (buf[i] == '\\')
        {
            if (i < len - 1)
            {
                if (buf[i + 1] == 'r')
                {
                    buf[i] = '\r';
                    buf[i + 1] = 255;
                    i++;
                }
                else if (buf[i + 1] == 'n')
                {
                    buf[i] = '\n';
                    buf[i + 1] = 255;
                    i++;
                }
            }
        }
        i++;
    }

    _oled_96x96_string(buf);
    return true;
}

uint8_t GroveOLED9696::_oled_96x96_num(int32_t long_num)
{
    uint8_t char_buffer[10] = { 0 };
    uint8_t i = 0;
    uint8_t f = 0;

    if (long_num < 0)
    {
        f = 1;
        _oled_96x96_char('-');
        long_num = -long_num;
    }
    else if (long_num == 0)
    {
        f = 1;
        _oled_96x96_char('0');
        return f;
    }

    while (long_num > 0)
    {
        char_buffer[i++] = long_num % 10;
        long_num /= 10;
    }

    f = f + i;
    for (; i > 0; i--)
    {
        _oled_96x96_char('0' + char_buffer[i - 1]);
    }

    return f;
}

uint8_t GroveOLED9696::_oled_96x96_float(float floatNumber, uint8_t decimal) {
    unsigned int temp = 0;
    float decy = 0.0;
    float rounding = 0.5;
    uint8_t f = 0;

    if (floatNumber<0.0)
    {
        _oled_96x96_char('-');
        floatNumber = -floatNumber;
        f += 1;
    }

    for (unsigned char i = 0; i<decimal; ++i)
    {
        rounding /= 10.0;
    }

    floatNumber += rounding;
    temp = floatNumber;
    f += _oled_96x96_num(temp);

    if (decimal>0)
    {
        _oled_96x96_char('.');
        f += 1;
    }

    decy = floatNumber - temp;//decimal part,
    for (unsigned char i = 0; i<decimal; i++)//4
    {
        decy *= 10;// for the next decimal
        temp = decy;//get the decimal
        _oled_96x96_num(temp);
        decy -= temp;
    }

    f += decimal;
    return (bool)f;
}

void GroveOLED9696::_oled_96x96_h_scroll(bool direction, uint8_t start, uint8_t end, uint8_t scroll_speed)
{
    _oled_96x96_cmd((direction) ? OLED96_SCROLL_RIGHT_CMD : OLED96_SCROLL_LEFT_CMD);
    _oled_96x96_cmd(0x00);
    _oled_96x96_cmd(0x00 + (start * 8));
    _oled_96x96_cmd(scroll_speed);
    _oled_96x96_cmd(0x07 + (end * 8));
    _oled_96x96_cmd(0x08);
    _oled_96x96_cmd(0x37);
    _oled_96x96_cmd(0x00);
}

void GroveOLED9696::_oled_96x96_cmd(uint8_t command)
{
    suli_i2c_write_reg(i2c, OLED96_ADDRESS, OLED96_COMMAND_MODE, &command, 1);
}

void GroveOLED9696::_oled_96x96_dta(uint8_t data)
{
    suli_i2c_write_reg(i2c, OLED96_ADDRESS, OLED96_DATA_MODE, &data, 1);
}