/*
 * grove_co2_mhz16.cpp
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Pontus "Mirar" Hagland
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
#include "grove_co2_mhz16.h"

GroveCo2MhZ16::GroveCo2MhZ16(int pintx, int pinrx)
{
    this->uart = (UART_T *)malloc(sizeof(UART_T));

    /* MH-Z16 talks 9600 baud */
    suli_uart_init(uart, pintx, pinrx, 9600);
    last_error="no error";
}

void GroveCo2MhZ16::_drain_uart()
{
    while (suli_uart_readable(uart))
    {
        suli_uart_read(uart);
    }
}

bool GroveCo2MhZ16::_update_from_sensor(void)
{
   /* MH-Z16 "get" command */
   /* suli can't use const constraint */
   /*const*/ uint8_t cmd_get_sensor[] =
      { 0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79 };

   _drain_uart(); // just to be sure there's no leftovers
   suli_uart_write_bytes(uart, cmd_get_sensor, sizeof(cmd_get_sensor));

   suli_delay_ms(10);

#define BYTES_IN_ANSWER 9
   byte data[BYTES_IN_ANSWER];
   int n =
      suli_uart_read_bytes_timeout(uart,data,BYTES_IN_ANSWER,100);

   if (n!=9)
   {
      last_error="too few bytes read";
      return false;
   }

   // checksum :
   if ((1 + (0xFF ^ (byte)(data[1] + data[2] + data[3]
                           + data[4] + data[5] + data[6]
                           + data[7]))) != data[8])
   {
      last_error="checksum error";
      return false;
   }

   CO2PPM = (int)data[2] * 256 + (int)data[3];
   temp = (int)data[4] - 40;

   return true;
}

bool GroveCo2MhZ16::read_concentration_and_temperature(float *concentration,float *temperature)
{
   if (!_update_from_sensor()) return false;
   *concentration = CO2PPM;
   *temperature   = temp;
   return true;
}

bool GroveCo2MhZ16::read_concentration(float *concentration)
{
   if (!_update_from_sensor()) return false;
   *concentration = CO2PPM;
   return true;
}

bool GroveCo2MhZ16::read_temperature(float *temperature)
{
   if (!_update_from_sensor()) return false;
   *temperature   = temp;
   return true;
}

const char* GroveCo2MhZ16::get_last_error(void)
{
   return last_error;
}
