/*
 * grove_ir_receiver.h
 *
 * Copyright (c) 2012 seeed technology inc.
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
 */


#ifndef __GROVE_IR_RECV_H__
#define __GROVE_IR_RECV_H__

#include "suli2.h"

//GROVE_NAME        "Grove - Infrared Receiver"
//SKU               101020016
//IF_TYPE           GPIO
//IMAGE_URL         https://s3-us-west-2.amazonaws.com/wio.seeed.cc/static/driver_images/Grove-Infrared_Receiver.jpg
//DESCRIPTION       "The Infrared Receiver is used to receive infrared signals and also used for remote control detection. There is an IR detector on the Infrared Receiver which is used to get the infrared light emitted by the Infrared Emitter. The IR detector have a demodulator inside that looks for modulated IR at 38 KHz. The Infrared Receiver can receive signals well within 10 meters. If more than 10 meters , the receiver may not get the signals. We often use the two Groves-the Infrared Receiver and the Grove - Infrared Emitter to work together."
//WIKI_URL          http://www.seeedstudio.com/wiki/Grove_-_Infrared_Receiver
//ADDED_AT          "2016-01-01"
//AUTHOR            "SEEED"

#define __IR_RECV_DEBUG    0

#define D_LEN       0
#define D_STARTH    1
#define D_STARTL    2
#define D_SHORT     3
#define D_LONG      4
#define D_DATALEN   5
#define D_DATA      6


#define USECPERTICK 50  // microseconds per clock interrupt tick
#define RAWBUF 300 // Length of raw duration buffer

// Marks tend to be 100us too long, and spaces 100us too short
// when received due to sensor lag.
#define MARK_EXCESS 100


typedef struct  {
    volatile unsigned int *rawbuf; // Raw intervals in .5 us ticks
    int rawlen;           // Number of records in rawbuf.
}decode_results;


#define ERR 0
#define DECODED 1

#define TOLERANCE 25  // percent tolerance in measurements
#define LTOL (1.0 - TOLERANCE/100.)
#define UTOL (1.0 + TOLERANCE/100.)

#define _GAP 5000 // Minimum map between transmissions
#define GAP_TICKS (_GAP/USECPERTICK)

#define TICKS_LOW(us) (int) (((us)*LTOL/USECPERTICK))
#define TICKS_HIGH(us) (int) (((us)*UTOL/USECPERTICK + 1))



// receiver states
#define STATE_IDLE     2
#define STATE_MARK     3
#define STATE_SPACE    4
#define STATE_STOP     5

// information for the interrupt handler
typedef struct {
    uint8_t recvpin;              // pin for IR data from detector
    uint8_t rcvstate;             // state machine
    unsigned int timer;           // state timer, counts 50uS ticks.
    unsigned int rawbuf[RAWBUF];  // raw data
    uint8_t rawlen;               // counter of entries in rawbuf
} irparams_t;

// IR detector output is active low
#define MARK  0
#define SPACE 1

#define TOPBIT 0x80000000


class GroveIRRecv
{
public:
    GroveIRRecv(int pin);

    /**
     * Read the last IR data received. The data will be cleared after this read.
     *
     * @param len - the number of bytes
     * @param data - a string in hex format, e.g. FFBBCC0011
     *
     * @return bool
     */
    bool read_last_data_recved(uint16_t *len, char **data);

    /**
     * Read the parameters of the IR protocol(NEC).
     *
     * @param start_h - the length of start high signal
     * @param start_l - the length of start low signal
     * @param n_short - the length of short signal
     * @param n_long - the length of long signal
     *
     * @return bool
     */
    bool read_protocol_parameters(uint8_t *start_h, uint8_t *start_l, uint8_t *n_short, uint8_t *n_long);

    /**
     * An event which indicates the length of data IR Receiver has received.
     */
    DEFINE_EVENT(ir_recv_data_len, SULI_EDT_UINT8);

    /**
     * An event which reports the data sequence IR Receiver has received, in HEX string.
     */
    DEFINE_EVENT(ir_recv_data_hex, SULI_EDT_STRING);


    IO_T *io;
    uint32_t time;
    TIMER_T *timer;
    decode_results results;
    volatile irparams_t irparams;
    uint8_t *data;
    uint8_t *data_hex;
    bool    new_data_available;

    void Clear() ICACHE_RAM_ATTR;
    int decode(decode_results *results) ICACHE_RAM_ATTR;
    uint8_t IsDta() ICACHE_RAM_ATTR;
    uint8_t Recv() ICACHE_RAM_ATTR;
    void check_data() ICACHE_RAM_ATTR;

    void _format_data() ICACHE_RAM_ATTR;

};

static void grove_ir_recv_timer_interrupt_handler(void *para) ICACHE_RAM_ATTR;

#endif
