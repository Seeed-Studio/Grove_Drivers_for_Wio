/*
* grove_nfc_tag.cpp
*
* Copyright (c) 2016 seeed technology inc.
* Website    : www.seeed.cc
* Author     : Travis Brown (warriorrocker@gmail.com)
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
#include "grove_nfc_tag.h"

GroveNfcTag::GroveNfcTag(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    suli_i2c_init(this->i2c, pinsda, pinscl);
}

bool GroveNfcTag::read_dsfid(uint8_t *dsfid)
{
    _nfc_tag_eeprom_read(NFC_TAG_DSFID_ADDR, dsfid, 1);
    return true;
}

bool GroveNfcTag::read_afi(uint8_t *afi)
{
    _nfc_tag_eeprom_read(NFC_TAG_AFI_ADDR, afi, 1);
    return true;
}

bool GroveNfcTag::read_rfu(uint16_t *rfu)
{
    uint8_t data, data2;

    _nfc_tag_eeprom_read(NFC_TAG_RFU_ADDR, &data, 1);
    _nfc_tag_eeprom_read(NFC_TAG_RFU_ADDR + 1, &data2, 1);

    return ((uint16_t)data << 8 | data2);
}

bool GroveNfcTag::read_uid(uint8_t *uid)
{
    _nfc_tag_eeprom_read(NFC_TAG_UID_ADDR, uid, NFC_TAG_UID_LENGTH);
    return true;
}

bool GroveNfcTag::write_passwd_submit(uint8_t passwd)
{
    _nfc_tag_passwd(&passwd, false);
    return true;
}

bool GroveNfcTag::write_passwd_write(uint8_t passwd)
{
    _nfc_tag_passwd(&passwd, true);
    return true;
}

void GroveNfcTag::_nfc_tag_passwd(uint8_t *passwd, bool write)
{
    int i;
    uint8_t pw_data[(NFC_TAG_PASSWD_LEN * 2) + 3] = { 0x09, 0x00 };

    pw_data[6] = ((write) ? 0x07 : 0x09);

    for (i = 0; i < NFC_TAG_PASSWD_LEN; i++) {
        pw_data[(i + 2)] = passwd[i];
        pw_data[(i + 5)] = passwd[i];
    }

    suli_i2c_write(i2c, NFC_TAG_ADDRESS, &pw_data[0], sizeof(pw_data));
}

void GroveNfcTag::_nfc_tag_eeprom_write(uint8_t address, uint8_t *data)
{
    int i;
    uint8_t ee_data[(sizeof(data) + 2)];

    ee_data[0] = (address >> 8); // MSB
    ee_data[1] = (address & 0xFF); // LSB

    for (i = 0; i < sizeof(data); i++)
        ee_data[(i + 2)] = data[i];

    suli_i2c_write(i2c, NFC_TAG_ADDRESS, &ee_data[0], sizeof(ee_data));
}

uint8_t GroveNfcTag::_nfc_tag_eeprom_read(uint8_t address, uint8_t *buff, int len)
{
    int i;
    uint8_t r_data[2];

    r_data[0] = (address >> 8); // MSB
    r_data[1] = (address & 0xFF); // LSB

    suli_i2c_write(i2c, NFC_TAG_ADDRESS, &r_data[0], sizeof(r_data));

    return suli_i2c_read(i2c, NFC_TAG_ADDRESS, buff, len);
}