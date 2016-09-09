/*
 * grove_sunlight.cpp
 * Copyright (c) 2015 seeed technology inc.
 * Website : www.seeed.cc
 * Author : Fuhua.Chen adapted by Airdissy for WioLink
 * Modified Time: August 2016
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
#include "grove_sunlight.h"

/*--------------------------------------------------------//
default init

 */

GroveSI114X::GroveSI114X(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    suli_i2c_init(this->i2c, pinsda, pinscl);
    i2cAddress = SI114X_ADDRESS;
    begin();

}

void GroveSI114X::deInit(void)
{
    //ENABLE UV reading
    //these reg must be set to the fixed value
    writeByte(SI114X_UCOEFF0, 0x29);
    writeByte(SI114X_UCOEFF1, 0x89);
    writeByte(SI114X_UCOEFF2, 0x02);
    writeByte(SI114X_UCOEFF3, 0x00);
    writeParamData(SI114X_CHLIST, SI114X_CHLIST_ENUV | SI114X_CHLIST_ENALSIR | SI114X_CHLIST_ENALSVIS | SI114X_CHLIST_ENPS1);
    //
    //set LED1 CURRENT(22.4mA)(It is a normal value for many LED)
    //
    writeParamData(SI114X_PS1_ADCMUX, SI114X_ADCMUX_LARGE_IR);
    writeByte(SI114X_PS_LED21, SI114X_LED_CURRENT_22MA);
    writeParamData(SI114X_PSLED12_SELECT, SI114X_PSLED12_SELECT_PS1_LED1); //
                                                                           //
                                                                           //PS ADC SETTING
                                                                           //
    writeParamData(SI114X_PS_ADC_GAIN, SI114X_ADC_GAIN_DIV1);
    writeParamData(SI114X_PS_ADC_COUNTER, SI114X_ADC_COUNTER_511ADCCLK);
    writeParamData(SI114X_PS_ADC_MISC, SI114X_ADC_MISC_HIGHRANGE | SI114X_ADC_MISC_ADC_RAWADC);
    //
    //VIS ADC SETTING
    //
    writeParamData(SI114X_ALS_VIS_ADC_GAIN, SI114X_ADC_GAIN_DIV1);
    writeParamData(SI114X_ALS_VIS_ADC_COUNTER, SI114X_ADC_COUNTER_511ADCCLK);
    writeParamData(SI114X_ALS_VIS_ADC_MISC, SI114X_ADC_MISC_HIGHRANGE);
    //
    //IR ADC SETTING
    //
    writeParamData(SI114X_ALS_IR_ADC_GAIN, SI114X_ADC_GAIN_DIV1);
    writeParamData(SI114X_ALS_IR_ADC_COUNTER, SI114X_ADC_COUNTER_511ADCCLK);
    writeParamData(SI114X_ALS_IR_ADC_MISC, SI114X_ADC_MISC_HIGHRANGE);
    //
    //interrupt enable
    //
    writeByte(SI114X_INT_CFG, SI114X_INT_CFG_INTOE);
    writeByte(SI114X_IRQ_ENABLE, SI114X_IRQEN_ALS);
    //
    //AUTO RUN
    //
    writeByte(SI114X_MEAS_RATE0, 0xFF);
    writeByte(SI114X_COMMAND, SI114X_PSALS_AUTO);
}

/*--------------------------------------------------------//
 Init the si114x and begin to collect data
 */

bool GroveSI114X::begin(void)
{
    //
    //Init IIC  and reset si1145
    //
    uint8_t id = readByte(SI114X_PART_ID);
    //Serial1.println(id, HEX);
    if (id != 0x45)
    {
        return false;
    }
    reset();
    //
    //INIT
    //
    deInit();
    return true;
}

/*--------------------------------------------------------//
reset the si114x
inclue IRQ reg, command regs...

 */
void GroveSI114X::reset(void)
{
    writeByte(SI114X_MEAS_RATE0, 0);
    writeByte(SI114X_MEAS_RATE1, 0);
    writeByte(SI114X_IRQ_ENABLE, 0);
    writeByte(SI114X_IRQ_MODE1, 0);
    writeByte(SI114X_IRQ_MODE2, 0);
    writeByte(SI114X_INT_CFG, 0);
    writeByte(SI114X_IRQ_STATUS, 0xFF);
    writeByte(SI114X_COMMAND, SI114X_RESET);
    suli_delay_ms(10);
    writeByte(SI114X_HW_KEY, 0x17);
    suli_delay_ms(10);
}

/*********************************************************************************************************
** Function name:           writeByte
** Descriptions:            write one byte into si114x's reg
*********************************************************************************************************/
void GroveSI114X::writeByte(uint8_t reg, uint8_t val)
{
    suli_i2c_write_reg(this->i2c, i2cAddress, reg, &val, 1);
}

/*********************************************************************************************************
** Function name:           readByte
** Descriptions:            read one byte data from si114x
*********************************************************************************************************/
uint8_t GroveSI114X::readByte(uint8_t reg)
{
    suli_i2c_read_reg(this->i2c, i2cAddress, reg, buffer, 1);
    return buffer[0];
}

/*********************************************************************************************************
** Function name:           readHalfWord
** Descriptions:            read half word(2 bytes) data from si114x
*********************************************************************************************************/
uint16_t GroveSI114X::readHalfWord(uint8_t reg)
{
    suli_i2c_read_reg(this->i2c, i2cAddress, reg, buffer, 2);
    return (buffer[1] << 8) | buffer[0];
}

/*********************************************************************************************************
** Function name:           readParamDate
** Descriptions:            read param data
*********************************************************************************************************/
uint8_t GroveSI114X::readParamData(uint8_t Reg)
{
    writeByte(SI114X_COMMAND, Reg | SI114X_QUERY);
    return readByte(SI114X_RD);
}

/*********************************************************************************************************
** Function name:           WriteParamDate
** Descriptions:            write param data
*********************************************************************************************************/
uint8_t GroveSI114X::writeParamData(uint8_t Reg, uint8_t Value)
{
    //write Value into PARAMWR reg first
    writeByte(SI114X_WR, Value);
    writeByte(SI114X_COMMAND, Reg | SI114X_SET);

    //SI114X writes value out to PARAM_RD,read and confirm its right
    return readByte(SI114X_RD);
}

/*********************************************************************************************************
** Function name:           Read light
** Descriptions:            All user ask to I2C
*********************************************************************************************************/

/*--------------------------------------------------------//
Read Visible Value

 */
bool GroveSI114X::read_visiblelight(float *VL)
{
    *VL = readHalfWord(SI114X_ALS_VIS_DATA0);
    return true;
}
/*--------------------------------------------------------//
Read IR Value

 */
bool GroveSI114X::read_IR(float *IR)
{
    *IR = readHalfWord(SI114X_ALS_IR_DATA0);
    return true;
}

/*--------------------------------------------------------//
Read UV Value
this function is a int value ,but the real value must be div 100
 */

bool GroveSI114X::read_UV(float *UV)
{
    *UV = readHalfWord(SI114X_AUX_DATA0_UVINDEX0)/100.0f;
    return true;
}
