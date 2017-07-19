/*
 * grove_generic_uart.h
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


#ifndef __GROVE_GENERIC_UART_H__
#define __GROVE_GENERIC_UART_H__

#include "suli2.h"

//GROVE_NAME        "Generic UART"
//SKU               856faea2-dbbe-11e6-ab2c-9f75fb373732
//IF_TYPE           UART
//IMAGE_URL         https://github.com/Seeed-Studio/Grove_Drivers_for_Wio/raw/static/images/wio_generic_uart.png
//DESCRIPTION       "The Generic UART module can forward short messages between the internet and the UART port."
//WIKI_URL          https://github.com/Seeed-Studio/Grove_Drivers_for_Wio/wiki/Grove_Generic_UART
//ADDED_AT          "2017-01-16"
//AUTHOR            "SEEED"

class GroveUART
{
public:

    GroveUART(int pintx, int pinrx);

    /**
     * Change the baudrate of UART.
     *
     * @param index - 0:9600(default), 1:19200, 2:38400, 3:57600, 4:115200
     *
     * @return bool
     */
    bool write_baudrate(uint8_t index);

    /**
     * Send a string to the UART port. URL special chars must be escaped.
     *
     * @param str - the string, must not have URL special chars.
     *
     * @return bool
     */
    bool write_string(char *str);

    /**
     * Send base64 encoded string, with this method you can send chars like carriage return or
     * URL special chars.
     *
     * @param b64_str - the base64 encoded string
     *
     * @return bool
     */
    bool write_base64_string(char *b64_str);

    /**
     * This event reports the message received from the UART port.
     */
    DEFINE_EVENT(uart_rx, SULI_EDT_STRING);

    char *get_last_error() { return error_desc; };

    void _check_rx();


private:

    UART_T *uart;
    TIMER_T *timer;

    char *error_desc;

    int _pintx;
    int _pinrx;
    char *_buffer;

};

static void timer_handler_check_uart_rx(void *para);


#endif
