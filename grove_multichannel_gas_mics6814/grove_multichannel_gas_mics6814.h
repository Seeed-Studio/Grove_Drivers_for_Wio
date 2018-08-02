/*
 * grove_multichannel_gas_mics6814.h
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jacky Zhang
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



#ifndef __GROVE_MULTICHANNEL_GAS_MICS6814_H__
#define __GROVE_MULTICHANNEL_GAS_MICS6814_H__

//GROVE_NAME        "Grove-Multichannel Gas Sensor"
//SKU               101020088
//IF_TYPE           I2C
//IMAGE_URL         http://statics3.seeedstudio.com/images/product/101020088%201.jpg
//DESCRIPTION       "Grove – Multichannel Gas sensor is a environment detecting sensor with a built in MiCS-6814 which can detect many unhealthful gases, and three gases can be measured simultaneously due to its three channels, so it can help you to monitor the concentration which more than one gas. "
//WIKI_URL          http://wiki.seeedstudio.com/Grove-Multichannel_Gas_Sensor/
//ADDED_AT          "2015-10-01"
//AUTHOR            "SEEED"

#include "suli2.h"

#define MULTICHANNEL_GAS_ADDRESS (0x04<<1)

// Register Defines
#define READ_R0_CH1         0x11
#define READ_R0_CH2         0x12
#define READ_R0_CH3         0x13

#define READ_RS_CH1         0x01
#define READ_RS_CH2         0x02
#define READ_RS_CH3         0x03

#define CHANGE_I2C_ADDR     0x23
#define DO_CALIBARTE        0x22
#define POWER_ON            0x21
#define POWER_OFF           0x20

//version 2
#define ADDR_IS_SET             0           // if this is the first time to run, if 1126, set
#define ADDR_FACTORY_ADC_NH3    2
#define ADDR_FACTORY_ADC_CO     4
#define ADDR_FACTORY_ADC_NO2    6
#define ADDR_USER_ADC_HN3       8
#define ADDR_USER_ADC_CO        10
#define ADDR_USER_ADC_NO2       12
#define ADDR_IF_CALI            14          // IF USER HAD CALI
#define ADDR_I2C_ADDRESS        20

#define CH_VALUE_NH3            1
#define CH_VALUE_CO             2
#define CH_VALUE_NO2            3

#define CMD_ADC_RES0            1           // NH3
#define CMD_ADC_RES1            2           // CO
#define CMD_ADC_RES2            3           // NO2
#define CMD_ADC_RESALL          4           // ALL CHANNEL
#define CMD_CHANGE_I2C          5           // CHANGE I2C
#define CMD_READ_EEPROM         6           // READ EEPROM VALUE, RETURN UNSIGNED INT
#define CMD_SET_R0_ADC          7           // SET R0 ADC VALUE
#define CMD_GET_R0_ADC          8           // GET R0 ADC VALUE
#define CMD_GET_R0_ADC_FACTORY  9           // GET FACTORY R0 ADC VALUE
#define CMD_CONTROL_LED         10
#define CMD_CONTROL_PWR         11


enum{CO, NO2, NH3, C3H8, C4H10, CH4, H2, C2H5OH};


class GroveMultiChannelGas
{
public:
    GroveMultiChannelGas(int pinsda, int pinscl);

    void powerOn(void);
    void powerOff(void);

    /**
     * Read the concentration of CO gas with unit ppm.
     *
     * @param concentration_ppm - the concentration of CO gas, unit: ppm
     *
     * @return bool
     */
    bool read_CO(float *concentration_ppm);
    bool read_NO2(float *concentration_ppm);
    bool read_NH3(float *concentration_ppm);
    bool read_C3H8(float *concentration_ppm);
    bool read_C4H10(float *concentration_ppm);
    bool read_CH4(float *concentration_ppm);
    bool read_H2(float *concentration_ppm);
    bool read_C2H5OH(float *concentration_ppm);

    char *get_last_error() { return error_desc; };


private:
    I2C_T *i2c;
    TIMER_T *timer;
    int __version;
    uint16_t res0[3];//sensors res0
    uint16_t res[3];//sensors res
    uint8_t i2cAddress;//I2C address of the sensor
    uint8_t is_connected;

    //v1 read/write
    void sendCmd(uint8_t dta);
    int16_t readData(uint8_t cmd);
    int16_t readR0();
    void readR();

    //v2 read/write
    void sendCmdWithValue(uint8_t cmd, uint8_t value);
    uint16_t readEEP(uint8_t eep_addr);
    uint8_t getFWVersion();

    float calcGas(int gas);
    char *error_desc;

};

static void grove_multichal_gas_timer_interrupt_handler(void *para);



#endif
