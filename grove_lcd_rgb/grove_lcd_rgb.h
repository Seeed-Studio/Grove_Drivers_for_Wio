/*
 * grove_lcd_rgb.h
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jack Shao
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


#ifndef __LCD_RGB_H__
#define __LCD_RGB_H__

#include "suli2.h"
#include "Print.h"

//GROVE_NAME        "Grove - LCD RGB Backlight"
//SKU               104030001
//IF_TYPE           I2C
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/grove-lcd_rgb.jpg
//DESCRIPTION       "Done with tedious mono color backlight? This Grove enables you to set the color to whatever you like via the simple and concise Grove interface. It takes I2C as communication method with your microcontroller. So number of pins required for data exchange and backlight control shrinks from ~10 to 2, relieving IOs for other challenging tasks. Besides, Grove - LCD RGB Backlight supports user-defined characters. Want to get a love heart or some other foreign characters? Just take advantage of this feature and design it!"
//WIKI_URL          http://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
//HACK_GUIDE_URL    https://github.com/Seeed-Studio/Grove_Drivers_for_Wio/wiki/Hardware-Hacking-Guide
//ADDED_AT          "2016-01-08"
//AUTHOR            "SEEED"

// Device I2C Arress
#define LCD_ADDRESS     (0x7c)
#define RGB_ADDRESS     (0xc4)


// color define
#define WHITE           0
#define RED             1
#define GREEN           2
#define BLUE            3

#define REG_RED         0x04        // pwm2
#define REG_GREEN       0x03        // pwm1
#define REG_BLUE        0x02        // pwm0

#define REG_MODE1       0x00
#define REG_MODE2       0x01
#define REG_OUTPUT      0x08

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


class GroveLCDRGB : public Print
{
public:
    GroveLCDRGB(int pinsda, int pinscl);

    virtual size_t write(uint8_t);

    /**
     * [Please notice that you must jump VCC of Grove-LCD to 5V]
     * Clear the whole screen.
     *
     * @return bool
     */
    bool write_clear();

    /**
     * [Please notice that you must jump VCC of Grove-LCD to 5V]
     *
     * @param color_index - 0: white, 1: red, 2: green, 3: blue
     *
     * @return bool
     */
    bool write_backlight_color(uint8_t color_index);

    /**
     * [Please notice that you must jump VCC of Grove-LCD to 5V]
     * Set the RGB color for the backlight.
     *
     * @param brightness - 0~255
     *
     * @return bool
     */
    bool write_backlight_color_rgb(uint8_t r, uint8_t g, uint8_t b);

    /**
     * [Please notice that you must jump VCC of Grove-LCD to 5V]
     * Print a integer.
     *
     * @param row - 0~1
     * @param col - 0~15
     * @param i - the integer to display
     *
     * @return bool
     */
    bool write_integer(uint8_t row, uint8_t col, int32_t i);

    /**
     * [Please notice that you must jump VCC of Grove-LCD to 5V]
     * voltage] Print a float number.
     *
     * @param row - 0~1
     * @param col - 0~15
     * @param f - float number
     * @param decimal - the decimal bits
     *
     * @return bool
     */
    bool write_float(uint8_t row, uint8_t col, float f, uint8_t decimal);

    /**
     * [Please notice that you must jump VCC of Grove-LCD to 5V]
     * Print a string in one line.
     * Note that the char must be letter or number, special chars
     * may be ignored. To display multilines and special chars,
     * please use base64_string API.
     *
     * @param row - 0~1
     * @param col - 0~15
     * @param str - the string to display
     *
     * @return bool
     */
    bool write_string(uint8_t row, uint8_t col, char *str);

    /**
     * [Please notice that you must jump VCC of Grove-LCD to 5V]
     * Print a multiline string encoded in base64. Special chars is supported.
     *
     * @param row - 0~7
     * @param col - 0~15
     * @param b64_str - base64 encoded string, the max length is 256
     *
     * @return bool
     */
    bool write_base64_string(uint8_t row, uint8_t col, char *b64_str);

    /**
     * [Please notice that you must jump VCC of Grove-LCD to 5V]
     * Let the specified rows to scroll left horizontally.
     *
     * @param speed - 1~10, 10 is the fastest
     *
     * @return bool
     */
    bool write_scroll_left(uint8_t speed);

    /**
     * [Please notice that you must jump VCC of Grove-LCD to 5V]
     * Let the specified rows to scroll right horizontally
     *
     * @param speed - 1~10, 10 is the fastest
     *
     * @return bool
     */
    bool write_scroll_right(uint8_t speed);

    /**
     * [Please notice that you must jump VCC of Grove-LCD to 5V]
     * Stop all scrolling rows.
     *
     * @return bool
     */
    bool write_stop_scroll();

    /**
     * [Please notice that you must jump VCC of Grove-LCD to a 5V voltage]
     *
     *
     * @return bool
     */
    bool write_display_on();

    /**
     * [Please notice that you must jump VCC of Grove-LCD to a 5V voltage]
     *
     *
     * @return bool
     */
    bool write_display_off();




    char *get_last_error() { return error_desc; };

    void scroll();


private:
    I2C_T *i2c;
    TIMER_T *timer;


    char *error_desc;
    int last_row;
    uint8_t _displayfunction, _displaycontrol, _displaymode;
    uint8_t _scroll_dir;

    void _init(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

    void _i2c_send_byte(uint8_t dta);

    void _i2c_send_bytes(uint8_t *dta, uint8_t len);

    inline void _command(uint8_t value)
    {
        uint8_t dta[2] = { 0x80, value };
        _i2c_send_bytes(dta, 2);
    }

    void _bl_set_reg(uint8_t addr, uint8_t dta);

    void _write_char(uint8_t);

    void _set_cursor(uint8_t, uint8_t);

};

static void grove_lcd_rgb_timer_interrupt_handler(void *para) ICACHE_RAM_ATTR;


#endif
