/*
 * grove_oled_9696.h
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


#ifndef __GROVE_OLED_96X96_H__
#define __GROVE_OLED_96X96_H__

#include "suli2.h"

//GROVE_NAME        "Grove - OLED Display 1.12''"
//SKU               104030011
//IF_TYPE           I2C
//IMAGE_URL         http://www.seeedstudio.com/wiki/images/thumb/9/90/Oled1281281.jpg/500px-Oled1281281.jpg
//DESCRIPTION       "Grove - OLED 96×96 is constructed with 96×96 dot matrix OLED module LY120 and SSD1327 driver IC which has a number of advantages such as high brightness, self-emission, high contrast ratio, slim / thin outline, wide viewing angle, wide temperature range, and low power consumption."
//WIKI_URL          http://www.seeedstudio.com/wiki/Grove_-_OLED_Display_1.12%22
//ADDED_AT          "2016-07-01"
//AUTHOR            "Travis Brown"

// Device i2c address
#define OLED96_ADDRESS                        (0x3c << 1)

// Device modes
#define OLED96_VERTICAL_MODE                01
#define OLED96_HORIZONTAL_MODE              02
#define OLED96_COMMAND_MODE                 0x80
#define OLED96_DATA_MODE                    0x40

// Device commands
#define OLED96_NORMAL_DISPLAY_CMD           0xA4
#define OLED96_INVERSE_DISPLAY_CMD          0xA7
#define OLED96_SET_CONTRAST_CMD             0x81
#define OLED96_ACTIVATE_SCROLL_CMD          0x2F
#define OLED96_DEACTIVATE_SCROLL_CMD        0x2E
#define OLED96_SCROLL_RIGHT_CMD             0x26
#define OLED96_SCROLL_LEFT_CMD              0x27

class GroveOLED9696
{
public:
    GroveOLED9696(int pinsda, int pinscl);

    /**
     * Clear the whole screen
     *
     * @return bool
     */
    bool write_clear();

    /**
     * Set the brightness for the screen
     *
     * @param brightness - 0~255
     *
     * @return bool
     */
    bool write_brightness(uint8_t brightness);

    /**
     * Print a integer
     *
     * @param row - 0~11
     * @param col - 0~11
     * @param i - the integer to display
     *
     * @return bool
     */
    bool write_integer(uint8_t row, uint8_t col, int32_t i);

    /**
     * Print a float number
     *
     * @param row - 0~11
     * @param col - 0~11
     * @param f - float number
     * @param decimal - the decimal bits
     *
     * @return bool
     */
    bool write_float(uint8_t row, uint8_t col, float f, uint8_t decimal);

    /**
     * Print a string in one line.
     * Note that the char must be letter or number, special chars may be ignored.
     * To display multilines and special chars, please use base64_string API.
     *
     * @param row - 0~11
     * @param col - 0~11
     * @param str - the string to display
     *
     * @return bool
     */
    bool write_string(uint8_t row, uint8_t col, char *str);

    /**
     * Print a multiline string encoded in base64.
     * Special chars is supported.
     *
     * @param row - 0~11
     * @param col - 0~11
     * @param b64_str - base64 encoded string, the max length is 256
     *
     * @return bool
     */
    bool write_base64_string(uint8_t row, uint8_t col, char *b64_str);

    /**
     * Let the specified rows to scroll left horizontally
     *
     * @param start_row - upper row index, 0~11
     * @param end_row - lower row index (closed range), 0~11, must be greater or equal start_row.
     * @param speed - 0~255
     *
     * @return bool
     */
    bool write_scroll_left(uint8_t start_row, uint8_t end_row, uint8_t speed);

    /**
     * Let the specified rows to scroll right horizontally
     *
     * @param start_row - upper row index, 0~11
     * @param end_row - lower row index (closed range), 0~11, must be greater or equal start_row.
     * @param speed - 0~255
     *
     * @return bool
     */
    bool write_scroll_right(uint8_t start_row, uint8_t end_row, uint8_t speed);

    /**
     * Stop all scrolling rows.
     *
     * @return bool
     */
    bool write_stop_scroll();

    /**
     * Set the screen to display in inverse mode.
     *
     * @param inverse_or_not - 1: inverse(white background), 0: normal(black background)
     *
     * @return bool
     */
    bool write_inverse_display(uint8_t inverse_or_not);

    char *get_last_error() { return error_desc; };

private:
    void _oled_96x96_init();
    void _oled_96x96_clear();
    void _oled_96x96_xy(uint8_t row, uint8_t column);

    void _oled_96x96_char(uint8_t C);
    void _oled_96x96_string(const char *str);
    bool _oled_96x96_string_base64(const char *b64_str);
    uint8_t _oled_96x96_num(int32_t long_num);
    uint8_t _oled_96x96_float(float floatNumber, uint8_t decimal);
    void _oled_96x96_h_scroll(bool direction, uint8_t start_page, uint8_t end_page, uint8_t scroll_speed);

    void _oled_96x96_cmd(uint8_t command);
    void _oled_96x96_dta(uint8_t data);

    I2C_T *i2c;
    char *error_desc;

    uint8_t _gray_high;
    uint8_t _gray_low;
};

#endif
