/*
 * grove_lcd_rgb.cpp
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


#include "suli2.h"
#include "grove_lcd_rgb.h"
#include "base64.h"

const unsigned char color_define[4][3] =
{
    {255, 255, 255},            // white
    {255, 0, 0},                // red
    {0, 255, 0},                // green
    {0, 0, 255},                // blue
};


GroveLCDRGB::GroveLCDRGB(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    this->timer = (TIMER_T *)malloc(sizeof(TIMER_T));

    suli_i2c_init(this->i2c, pinsda, pinscl);
    last_row = 0;
    _displayfunction = 0;
    _displaycontrol = 0;
    _displaymode = 0;
    _scroll_dir = LCD_MOVERIGHT;

    _init(16, 2);
}

void GroveLCDRGB::_init(uint8_t cols, uint8_t lines, uint8_t charsize)
{
    if (lines > 1) {
        _displayfunction |= LCD_2LINE;
    }

    // for some 1 line displays you can select a 10 pixel high font
    if ((charsize != 0) && (lines == 1)) {
        _displayfunction |= LCD_5x10DOTS;
    }

    // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
    // according to datasheet, we need at least 40ms after power rises above 2.7V
    // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
    suli_delay_ms(50);


    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    _command(LCD_FUNCTIONSET | _displayfunction);
    suli_delay_ms(4);  // wait more than 4ms

    // second try
    _command(LCD_FUNCTIONSET | _displayfunction);
    suli_delay_ms(1);

    // third go
    _command(LCD_FUNCTIONSET | _displayfunction);


    // finally, set # lines, font size, etc.
    _command(LCD_FUNCTIONSET | _displayfunction);

    // turn the display on with no cursor or blinking default
    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    write_display_on();

    // clear it off
    write_clear();

    // Initialize to default text direction (for romance languages)
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
    _command(LCD_ENTRYMODESET | _displaymode);


    // backlight init
    _bl_set_reg(REG_MODE1, 0);
    // set LEDs controllable by both PWM and GRPPWM registers
    _bl_set_reg(REG_OUTPUT, 0xFF);
    // set MODE2 values
    // 0010 0000 -> 0x20  (DMBLNK to 1, ie blinky mode)
    _bl_set_reg(REG_MODE2, 0x20);

    write_backlight_color(0);
}

void GroveLCDRGB::_i2c_send_byte(uint8_t dta)
{
    suli_i2c_write(i2c, LCD_ADDRESS, &dta, 1);
}

void GroveLCDRGB::_i2c_send_bytes(uint8_t *dta, uint8_t len)
{
    suli_i2c_write(i2c, LCD_ADDRESS, dta, len);
}

void GroveLCDRGB::_bl_set_reg(uint8_t addr, uint8_t dta)
{
    suli_i2c_write_reg(i2c, RGB_ADDRESS, addr, &dta, 1);
}

void GroveLCDRGB::_write_char(uint8_t ch)
{
    uint8_t buff[2] = { 0x40, ch };
    _i2c_send_bytes(buff, 2);
}

void GroveLCDRGB::_set_cursor(uint8_t row, uint8_t col)
{
    last_row = row;
    col = (row == 0 ? col|0x80 : col|0xc0);
    uint8_t dta[2] = {0x80, col};

    _i2c_send_bytes(dta, 2);
}

size_t GroveLCDRGB::write(uint8_t C)
{
    if (C == 255)
    {
        return 0;
    }

    if(C < 32) //Ignore non-printable ASCII characters.
    {
        if (C=='\r')
        {
            _set_cursor(last_row, 0);
            return 1;
        } else if (C=='\n')
        {
            _set_cursor(last_row + 1, 0);
            return 1;
        } else
        {
            C = ' ';
        }
    }
    _write_char(C);

    return 1;
}

///
///
bool GroveLCDRGB::write_clear()
{
    _command(LCD_CLEARDISPLAY);
    suli_delay_ms(2);
    return true;
}

bool GroveLCDRGB::write_backlight_color(uint8_t color_index)
{
    if (color_index > 3)  color_index = 3;
    write_backlight_color_rgb(color_define[color_index][0], color_define[color_index][1], color_define[color_index][2]);
    return true;
}

bool GroveLCDRGB::write_backlight_color_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    _bl_set_reg(REG_RED, r);
    _bl_set_reg(REG_GREEN, g);
    _bl_set_reg(REG_BLUE, b);
    return true;
}

bool GroveLCDRGB::write_integer(uint8_t row, uint8_t col, int32_t i)
{
    _set_cursor(row,col);
    print(i);
    return true;
}

bool GroveLCDRGB::write_float(uint8_t row, uint8_t col, float floatNumber, uint8_t decimal)
{
    _set_cursor(row,col);
    print(floatNumber, decimal);
    return true;
}

bool GroveLCDRGB::write_string(uint8_t row, uint8_t col, char *str)
{
    _set_cursor(row,col);
    print(str);
    return true;
}

bool GroveLCDRGB::write_base64_string(uint8_t row, uint8_t col, char *b64_str)
{

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
            if (i < len-1)
            {
                if (buf[i+1] == 'r')
                {
                    buf[i] = '\r';
                    buf[i + 1] = 255;
                    i++;
                }else if (buf[i+1] == 'n')
                {
                    buf[i] = '\n';
                    buf[i + 1] = 255;
                    i++;
                }
            }
        }
        i++;
    }
    write_string(row, col, buf);
    return true;
}

bool GroveLCDRGB::write_scroll_left(uint8_t speed)
{
    _displaymode |= LCD_ENTRYSHIFTINCREMENT;
    _command(LCD_ENTRYMODESET | _displaymode);

    _scroll_dir = LCD_MOVELEFT;

    uint32_t t = suli_map(speed, 1, 10, 1000000, 50000);

    suli_timer_install(timer, t, grove_lcd_rgb_timer_interrupt_handler, this, true);

    return true;
}

bool GroveLCDRGB::write_scroll_right(uint8_t speed)
{
    _displaymode |= LCD_ENTRYSHIFTINCREMENT;
    _command(LCD_ENTRYMODESET | _displaymode);

    _scroll_dir = LCD_MOVERIGHT;

    uint32_t t = suli_map(speed, 1, 10, 1000000, 50000);

    suli_timer_install(timer, t, grove_lcd_rgb_timer_interrupt_handler, this, true);

    return true;
}

bool GroveLCDRGB::write_stop_scroll()
{
    _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
    _command(LCD_ENTRYMODESET | _displaymode);

    suli_timer_remove(timer);

    return true;
}

void GroveLCDRGB::scroll()
{
    if (_scroll_dir == LCD_MOVELEFT)
    {
        _command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
    } else
    {
        _command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
    }
}

bool GroveLCDRGB::write_display_on()
{
    _displaycontrol |= LCD_DISPLAYON;
    _command(LCD_DISPLAYCONTROL | _displaycontrol);
    return true;
}

bool GroveLCDRGB::write_display_off()
{
    _displaycontrol &= ~LCD_DISPLAYON;
    _command(LCD_DISPLAYCONTROL | _displaycontrol);
    return true;
}

static void grove_lcd_rgb_timer_interrupt_handler(void *para)
{
    ((GroveLCDRGB *)para)->scroll();
}
