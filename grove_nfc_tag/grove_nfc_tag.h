/*
* grove_nfc_tag.h
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


#ifndef __GROVE_NFC_TAG_H__
#define __GROVE_NFC_TAG_H__

#include "suli2.h"

//GROVE_NAME        "Grove - NFC Tag"
//SKU               101020070
//IF_TYPE           I2C
//IMAGE_URL         http://www.seeedstudio.com/wiki/images/9/99/Grove_-_NFC_Tag_uasge.jpg
//DESCRIPTION       "Grove - NFC Tag is a highly integrated Near Field Communication Tag module,this module is I2C interface,which base on M24LR64E-R,M24LR64E-R have a 64-bit unique identifier and 64 -Kbit EEPROM."
//WIKI_URL          http://www.seeedstudio.com/wiki/Grove_-_NFC_Tag
//ADDED_AT          "2016-07-01"
//AUTHOR            "Travis Brown"

// Device I2C Address
#define NFC_TAG_ADDRESS                (0x57 << 1)

// Device EEPROM Addresses
#define NFC_TAG_DSFID_ADDR             2320    //1 byte
#define NFC_TAG_AFI_ADDR               2321    //1 byte
#define NFC_TAG_RFU_ADDR               2322    //2 bytes
#define NFC_TAG_UID_ADDR               2324    //8 bytes

// Device data lengths
#define NFC_TAG_PASSWD_LEN             4
#define NFC_TAG_UID_LENGTH               8

class GroveNfcTag
{
public:
    GroveNfcTag(int pinsda, int pinscl);

    /**
    * Read the data storage format identifier.
    *
    * @param dsfid - data storage format identifier
    *
    * @return bool
    */
    bool read_dsfid(uint8_t *dsfid);

    /**
    * Read the application format identifier.
    *
    * @param afi - application format identifier
    *
    * @return bool
    */
    bool read_afi(uint8_t *afi);

    bool read_rfu(uint16_t *rfu);

    /**
    * Read the chip unique identifier.
    *
    * @param uid - unique identifier
    *
    * @return bool
    */
    bool read_uid(uint8_t *uid);

    bool write_passwd_submit(uint8_t passwd);

    bool write_passwd_write(uint8_t passwd);

private:
    void _nfc_tag_passwd(uint8_t *passwd, bool write);
    void _nfc_tag_eeprom_write(uint8_t address, uint8_t *data);
    uint8_t _nfc_tag_eeprom_read(uint8_t address, uint8_t *buff, int len);

    I2C_T *i2c;

};

#endif