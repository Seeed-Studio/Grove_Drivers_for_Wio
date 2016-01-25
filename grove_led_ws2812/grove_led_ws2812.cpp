/*
 * grove_led_ws2812.cpp
 *
 * Copyright (c) 2015 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jack Shao (jacky.shaoxg@gmail.com)
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
 *
 *
 */

/*
 * +++++++++++++++++++++++++++++++++
 * NOTE:
 * This library is only for esp8266
 * +++++++++++++++++++++++++++++++++
 */
 
#include "suli2.h"
#include "grove_led_ws2812.h"


static uint32_t _getCycleCount(void) __attribute__((always_inline));
static inline uint32_t _getCycleCount(void) {
  uint32_t ccount;
  __asm__ __volatile__("rsr %0,ccount":"=a" (ccount));
  return ccount;
}

void ICACHE_RAM_ATTR espShow(uint8_t pin, uint8_t *pixels, uint32_t numBytes, boolean is800KHz) {

#define CYCLES_800_T0H  (F_CPU / 2500000) // 0.4us
#define CYCLES_800_T1H  (F_CPU / 1250000) // 0.8us
#define CYCLES_800      (F_CPU /  800000) // 1.25us per bit
#define CYCLES_400_T0H  (F_CPU / 2000000) // 0.5uS
#define CYCLES_400_T1H  (F_CPU /  833333) // 1.2us
#define CYCLES_400      (F_CPU /  400000) // 2.5us per bit

  uint8_t *p, *end, pix, mask;
  uint32_t t, time0, time1, period, c, startTime, pinMask;

  pinMask   = _BV(pin);
  p         =  pixels;
  end       =  p + numBytes;
  pix       = *p++;
  mask      = 0x80;
  startTime = 0;

  if(is800KHz) {
    time0  = CYCLES_800_T0H;
    time1  = CYCLES_800_T1H;
    period = CYCLES_800;
  } else { // 400 KHz bitstream
    time0  = CYCLES_400_T0H;
    time1  = CYCLES_400_T1H;
    period = CYCLES_400;
  }

  {
      InterruptLock lock;
      for(t = time0;; t = time0) {
        if(pix & mask) t = time1;                             // Bit high duration
        while(((c = _getCycleCount()) - startTime) < period); // Wait for bit start
        GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, pinMask);       // Set high
        startTime = c;                                        // Save start time
        while(((c = _getCycleCount()) - startTime) < t);      // Wait high duration
        GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, pinMask);       // Set low
        if(!(mask >>= 1)) {                                   // Next bit/byte
          if(p >= end) break;
          pix  = *p++;
          mask = 0x80;
        }
      }
  }
  while((_getCycleCount() - startTime) < period); // Wait for last bit
}


GroveLedWs2812::GroveLedWs2812(int pin)
{
    this->io = (IO_T *)malloc(sizeof(IO_T));
    this->timer = (TIMER_T *)malloc(sizeof(TIMER_T));
    
    suli_pin_init(io, pin, SULI_OUTPUT);
    
    led_cnt = MAX_LED_CNT;
    
    for (int i = 0; i < led_cnt; i++)
    {
        rgb_buffer.pixels[i].r = 0;
        rgb_buffer.pixels[i].g = 0;
        rgb_buffer.pixels[i].b = 0;
    }
    memset(_color_towards, 0, sizeof(_color_towards));
}

bool GroveLedWs2812::write_clear(uint8_t total_led_cnt, char *rgb_hex_string)
{
    led_cnt = total_led_cnt > MAX_LED_CNT ? MAX_LED_CNT : total_led_cnt;
    
    if (_extract_rgb_from_string(0, rgb_hex_string))
    {
        suli_timer_remove(timer);
        
        for (int i = 1; i < led_cnt; i++)
        {
            rgb_buffer.pixels[i].r = rgb_buffer.pixels[0].r;
            rgb_buffer.pixels[i].g = rgb_buffer.pixels[0].g;
            rgb_buffer.pixels[i].b = rgb_buffer.pixels[0].b;
        }
        espShow(*io, rgb_buffer.buff, led_cnt*3, true);
        return true;
    }
    else return false;
    
}


bool GroveLedWs2812::write_segment(uint8_t start, char *rgb_hex_string)
{
    if (_extract_rgb_from_string(start, rgb_hex_string))
    {
        espShow(*io, rgb_buffer.buff, led_cnt*3, true);
        return true;
    }
    else return false;
}

bool GroveLedWs2812::_extract_rgb_from_string(int start, char *str)
{
    int len = strlen(str);
    len = len - len % 6;
    int cnt = len / 6;
    
    uint8_t hex[3];
    hex[2] = '\0';
    uint32_t ul;
    
    for (int i = 0; i < cnt && (start+i)<led_cnt; i++)
    {
        memcpy(hex, (str + i * 6), 2);
        ul = strtoul((const char *)hex, NULL, 16);
        if (ul >= 0 && ul <=255)
        {
            rgb_buffer.pixels[start + i].r = ul;
        } else
        {
            error_desc = "invalid R value";
            return false;
        }

        memcpy((void *)hex, (void *)(str + i * 6 + 2), 2);
        ul = strtoul((const char *)hex, NULL, 16);
        if (ul >= 0 && ul <=255)
        {
            rgb_buffer.pixels[start + i].g = ul;
        } else
        {
            error_desc = "invalid G value";
            return false;
        }

        memcpy((void *)hex, (void *)(str + i * 6 + 4), 2);
        ul = strtoul((const char *)hex, NULL, 16);
        if (ul >= 0 && ul <=255)
        {
            rgb_buffer.pixels[start + i].b = ul;
        } else
        {
            error_desc = "invalid B value";
            return false;
        }

    }
    
    return true;
}

bool GroveLedWs2812::write_start_rainbow_flow(uint8_t length, uint8_t brightness, uint8_t speed)
{
    led_cnt = length > MAX_LED_CNT ? MAX_LED_CNT : length;
    _rainbow_flow_brightness = constrain(brightness, 0, 100);
    
    int8_t step_r, step_g, step_b;
    uint8_t start_r, start_g, start_b;
    uint8_t next_towards = 0;
    
    memset(_color_towards, 0, led_cnt);
    
    
    for (int i = 0; i < led_cnt; i++)
    {
        _color_towards[i] = next_towards;
        switch (_color_towards[i])
        {
        case 0:
            start_r = 0; 
            start_g = 0; 
            start_b = 250;
            step_r = 25; 
            step_g = 0; 
            step_b = -25;
            break;
        case 1:
            start_r = 250; 
            start_g = 0; 
            start_b = 0;
            step_r = -25; 
            step_g = 25; 
            step_b = 0;
            break;
        case 2:
            start_r = 0; 
            start_g = 250; 
            start_b = 0;
            step_r = 0; 
            step_g = -25; 
            step_b = 25;
            break;
        default:
            break;
        }
        int ii = i % 10;
        if (ii == 0) ii = 10;
        rgb_buffer.pixels[i].r = start_r + ii*step_r;
        rgb_buffer.pixels[i].g = start_g + ii*step_g;
        rgb_buffer.pixels[i].b = start_b + ii*step_b;

        if (i % 10 == 0)
        {
            next_towards += 1;
            if (next_towards > 2)
            {
               next_towards = 0;
            }
            _color_towards[i] = next_towards;
        }
    }
    espShow(*io, rgb_buffer.buff, led_cnt*3, true);
    
    long s = constrain(speed, 1, 10);
    int32_t interval = suli_map(s, 1, 10, 200000, 10000);

    suli_timer_install(timer,  (uint32_t)interval, timer_handler, this, true);
    return true;
}

bool GroveLedWs2812::write_stop_rainbow_flow()
{
    suli_timer_remove(timer);
    return true;
}

void GroveLedWs2812::update_color()
{
    int8_t step_r = 25;
    int8_t step_g = 0;
    int8_t step_b = -25;
    
    uint8_t tmp[3];
    
    for (int i = 0; i < led_cnt; i++)
    {
        switch (_color_towards[i])
        {
        case 0:
            step_r = 25; 
            step_g = 0; 
            step_b = -25;
            break;
        case 1:
            step_r = -25; 
            step_g = 25; 
            step_b = 0;
            break;
        case 2:
            step_r = 0; 
            step_g = -25; 
            step_b = 25;
            break;
        default:
            break;
        }
        rgb_buffer.pixels[i].r += step_r;
        rgb_buffer.pixels[i].g += step_g;
        rgb_buffer.pixels[i].b += step_b; 
        
        if (rgb_buffer.pixels[i].r >= 250)
        {
            rgb_buffer.pixels[i].r = 250;
            rgb_buffer.pixels[i].g = 0;
            rgb_buffer.pixels[i].b = 0;
            _color_towards[i] = 1;
        }
        else if (rgb_buffer.pixels[i].g >= 250)
        {
            rgb_buffer.pixels[i].r = 0;
            rgb_buffer.pixels[i].g = 250;
            rgb_buffer.pixels[i].b = 0;
            _color_towards[i] = 2;
        }
        else if (rgb_buffer.pixels[i].b >= 250)
        {
            rgb_buffer.pixels[i].r = 0;
            rgb_buffer.pixels[i].g = 0;
            rgb_buffer.pixels[i].b = 250;
            _color_towards[i] = 0;
        }
        
        memcpy(tmp, rgb_buffer.buff + i * 3, 3);
        tmp[0] = tmp[0] * _rainbow_flow_brightness / 100;
        tmp[1] = tmp[1] * _rainbow_flow_brightness / 100;
        tmp[2] = tmp[2] * _rainbow_flow_brightness / 100;
        
        espShow(*io, tmp, 3, true);
    }
}


static void timer_handler(void *para)
{
    GroveLedWs2812 *g = (GroveLedWs2812 *)para;
    
    g->update_color();
}




