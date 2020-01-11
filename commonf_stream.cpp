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

Stream& waitFor(Stream &obj, char c) {
    char b;
    obj.print('.');
    do {
        while(obj.available() == 0) yield(); 
        b = (char) obj.read();
    } while(b != c);
    return obj;
}

Stream& HexByte(Stream &obj, byte data) {
    static const char map[]={"0123456789ABCDEF"};
    obj.print(map[(uint8_t)((data&0xF0)>>4)]);
    obj.print(map[(uint8_t)(data&0x0F)]);
    return obj;
}

Stream& HexWord(Stream &obj, uint16_t data) {
    HexByte(obj, (byte)highByte(data));
    HexByte(obj, (byte)lowByte(data));
    return obj;
}

Stream& HexDWord(Stream &obj, uint32_t data) {
    HexByte(obj, (byte)((data>>24) & 0xFF));
    HexByte(obj, (byte)((data>>16) & 0xFF));
    HexByte(obj, (byte)((data>>8) & 0xFF));
    HexByte(obj, (byte)((data>>0) & 0xFF));
    return obj;
}

Stream& HexBuffer(Stream &obj, char * buf, size_t size) {
    if ((buf) && size > 0) {
        for(size_t i = 0; i < size ; i++) {
            HexByte(obj, (byte)buf[i]);
        }
    }
    return obj;
}

Stream& HexBufferArr(Stream &obj, char * buf, size_t size) {
    if ((buf) && size > 0) {
        for(size_t i = 0; i < size ; i++) {
            obj.print(F(" 0x"));
            HexByte(obj, (byte)buf[i]);
            obj.print(',');
        }
    }
    return obj;
}