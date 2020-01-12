/**
 * Common Function Library used as storage generic and reusable functionality.
 * Highly opinionated version and collection of @boseji's common reusable functions.
 * 
 * Copyright (c) 2006-2020 Abhijit Bose (@boseji).  All right reserved.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 */ 

#include <commonf.h>

void setup() {
    Serial.begin(115200);
    delay(2000);
}

void loop() {
    int lettera = 'A';
    int month = 4, day = 17, year = 2036;
    int cost1 = 12, cost2 = 34, cost4 = 71;
    uint8_t buf[] = {0x23, 0x57, 0x33, 0x37, 0xAB};
    Serial << "\n Press Space to begin executing the example ..." << waitFor(Serial, ' ') << endl;
    Serial << F("\n We also support Flash Strings") << endl;
    Serial << F("\n Press C to continue to the next stage ...") << SerialWaitFor('C') << endl;
    Serial << F("\n Press Enter to continue ...") << _Wait('\n') << endl;

    Serial << F("\n A is ") << lettera << '.' << endl;
    Serial << F(" Dated :") << day << '-' << month << '-' << year << '.' << endl;
    Serial << F(" Alternate Costs: ") << cost1, cost2, cost4;

    Serial << F("\n\n Press Any Key to continue ...") << _WaitAny() << endl;

    Serial << F("\n Printing a Hex Byte : ") << HexByte(Serial, 0x55);
    Serial << F("\n Another way Printing a Hex Byte : ") << _HEX(0x35);
    Serial << F("\n Let's print a bigger Hex : ") << _HEX16(0x3508);
    Serial << F("\n Let's print a even bigger Hex : ") << _HEX32(0xAB003508);
    Serial << F("\n Now Lets look at a Buffer: ") << HexBuffer(Serial, (char *)buf, arraySize(buf));
    Serial << F("\n Simpler Buffer printing : ") << _HEXbuf(buf, arraySize(buf));
    Serial << F("\n Printing Buffer C Style : {") << _HEXarr(buf, arraySize(buf));
    Serial << F(" }") << endl;

    Serial << F("\n\n Press Any Key to End Example ...") << _WaitAny() << endl;
}