/*
 * grove_mp3_v2.cpp
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
#include "grove_mp3_v2.h"

GroveMP3V2::GroveMP3V2(int pintx, int pinrx)
{
    this->uart = (UART_T *)malloc(sizeof(UART_T));
    
    suli_uart_init(uart, pintx, pinrx, 9600);
        
    _select_storage();
}

void GroveMP3V2::_select_storage()
{
    uint8_t buff[8] = { 0x7e, 0xff, 0x06, 0x09, 0x00, 0x00, 0x02, 0xef };
    
    suli_uart_write_bytes(uart, buff, 8);
}

void GroveMP3V2::_drain_uart()
{
    while (suli_uart_readable(uart))
    {
        suli_uart_read(uart);
    }
}

bool GroveMP3V2::write_index_to_play(uint8_t index)
{
    uint8_t buff[8] = { 0x7e, 0xff, 0x06, 0x03, 0x00, 0x00, 0x00, 0xef };
    
    uint8_t hbyte, lbyte;
    hbyte = index / 256;
    lbyte = index % 256;
    
    buff[5] = hbyte; buff[6] = lbyte;
    
    suli_uart_write_bytes(uart, buff, 8);
    
    return true;
}

bool GroveMP3V2::write_pause()
{
    uint8_t buff[8] = { 0x7e, 0xff, 0x06, 0x0e, 0x00, 0x00, 0x00, 0xef };
    
    suli_uart_write_bytes(uart, buff, 8);
    
    return true;
}
bool GroveMP3V2::write_resume()
{
    uint8_t buff[8] = { 0x7e, 0xff, 0x06, 0x0d, 0x00, 0x00, 0x00, 0xef };

    suli_uart_write_bytes(uart, buff, 8);

    return true;
}
bool GroveMP3V2::write_next()
{
    uint8_t buff[8] = { 0x7e, 0xff, 0x06, 0x01, 0x00, 0x00, 0x00, 0xef };

    suli_uart_write_bytes(uart, buff, 8);

    return true;
}
bool GroveMP3V2::write_prev()
{
    uint8_t buff[8] = { 0x7e, 0xff, 0x06, 0x02, 0x00, 0x00, 0x00, 0xef };

    suli_uart_write_bytes(uart, buff, 8);

    return true;
}
bool GroveMP3V2::write_loop_all()
{
    uint8_t buff[8] = { 0x7e, 0xff, 0x06, 0x11, 0x00, 0x00, 0x01, 0xef };

    suli_uart_write_bytes(uart, buff, 8);

    return true;
}
bool GroveMP3V2::write_volume(uint8_t volume)
{
    if (volume > 0x1e)
    {
        volume = 0x1e;
    }
    uint8_t buff[8] = { 0x7e, 0xff, 0x06, 0x06, 0x00, 0x00, volume, 0xef };

    suli_uart_write_bytes(uart, buff, 8);

    return true;
}
