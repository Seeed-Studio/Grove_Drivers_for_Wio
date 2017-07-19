/*
 * grove_generic_uart.cpp
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
#include "grove_generic_uart.h"
#include "base64.h"


GroveUART::GroveUART(int pintx, int pinrx)
{
    this->uart = (UART_T *)malloc(sizeof(UART_T));

    suli_uart_init(uart, pintx, pinrx, 9600);
    _pintx = pintx;
    _pinrx = pinrx;

    this->timer = (TIMER_T *)malloc(sizeof(TIMER_T));

    suli_timer_install(timer,  1000000, timer_handler_check_uart_rx, this, true);

    this->_buffer = (char *)malloc(130);
}

bool GroveUART::write_baudrate(uint8_t index)
{
    if (index >= 0 && index <= 4)
    {
        uint32_t baudrates[5] = {9600, 19200, 38400, 57600, 115200};
        suli_uart_init(uart, _pintx, _pinrx, baudrates[index]);
        return true;
    } else
    {
        error_desc = "baud rate index is wrong";
        return false;
    }
}

bool GroveUART::write_string(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] != 255)
        {
            suli_uart_write(uart, (uint8_t)str[i]);
        }
        i++;
    }
    return true;
}

bool GroveUART::write_base64_string(char *b64_str)
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

    write_string(buf);

    free(buf);

    return true;
}

void GroveUART::_check_rx()
{
    if (suli_uart_readable(uart))
    {
        int idx = 0;
        while (suli_uart_readable(uart) && idx < 127)
        {
            uint8_t c = suli_uart_read(uart);
            if (c == '\r')
            {
                _buffer[idx++] = '\\';
                _buffer[idx++] = 'r';
            } else if (c == '\n')
            {
                _buffer[idx++] = '\\';
                _buffer[idx++] = 'n';
            }else if (c > 0)
            {
                _buffer[idx++] = c;
            } else
            {
                break;
            }
        }
        _buffer[idx] = '\0';
        POST_EVENT(uart_rx, _buffer);
    }
}

static void timer_handler_check_uart_rx(void *para)
{
    GroveUART *g = (GroveUART *)para;

    g->_check_rx();
}



