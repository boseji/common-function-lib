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

void openDrain(uint32_t pin, bool value) {
    if(value) pinMode(pin, INPUT);
    else pinMode(pin, OUTPUT); 
    digitalWrite(pin, LOW);
}

void blinkLed(uint32_t pin, uint32_t n, bool onLevel, uint32_t delayms) {
    pinMode(pin, OUTPUT);
    for(size_t i=0; i<n; i++)
    { 
        digitalWrite(pin, onLevel);
        delay(delayms);
        digitalWrite(pin, !onLevel);
        delay(delayms);
    }
}