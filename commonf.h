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
#ifndef _COMMONF_H_
#define _COMMONF_H_

#include <Arduino.h>

//////// Options ////////

//////// Defines ////////
/** Find Size of Array */
#define arraySize(arr) (sizeof(arr)/sizeof(arr[0]))

/**
 * Error Handler Macro definition
 * 
 * @param ret Return Variable used as part of @cond if needed
 * @param proc Procedure to be executed before error code is returned
 * @param cond The condition to be validated as true for error
 * @param errdo What to do when we face the error
 */
#define ERR_HANDLE_PROC(ret,proc,cond,errdo) ret = (proc); \
  if ( cond ) { \
    (errdo); \
  }

/**
 * Break on Error Handler Macro definition
 * 
 * @param ret Return Variable used as part of @cond if needed
 * @param proc Procedure to be executed before error code is returned
 * @param cond The condition to be validated as true for error
 * @param errdo What to do when we face the error
 */
#define ERR_HANDLE_PROC_BREAK(ret,proc,cond,errdo) ret = (proc); \
  if ( (cond) ) { \
    (errdo); \
    break;
  }

/**
 * Error Handler Macro definition with Else
 * 
 * @param ret Return Variable used as part of @cond if needed
 * @param proc Procedure to be executed before error code is returned
 * @param cond The condition to be validated as true for error
 * @param errdo What to do when we face the error
 */
#define ERR_HANDLE_PROC_WITH_ELSE(ret,proc,cond,errdo) ret = (proc); \
  if ( cond ) { \
    (errdo); \
  } else

/**
 * Break on Error Handler Macro definition with Else
 * 
 * @param ret Return Variable used as part of @cond if needed
 * @param proc Procedure to be executed before error code is returned
 * @param cond The condition to be validated as true for error
 * @param errdo What to do when we face the error
 */
#define ERR_HANDLE_PROC_BREAK_WITH_ELSE(ret,proc,cond,errdo) ret = (proc); \
  if ( (cond) ) { \
    (errdo); \
    break;
  } else

//////// Functions ////////
/**
 * openDrain helps to Turn On and Off the GPIO pins in
 * open-collector 0r open-drain format
 * 
 * @param pin [in] The Variant listed Pin number that needs to be controlled
 * @param value [in] State of the pin to be configured 
 *                  true - Make the pin Open
 *                  false - Make the pin connected to Ground
 * 
 * @return None
 * 
 */ 
void openDrain(uint32_t pin, bool value);

/**
 * togglePin Helps to Flip / alternate the pin state on a listed 
 * Arduino GPIO capable pin
 * 
 * @note This function can get inlined based on usage and compiler used.
 * 
 * @param pin [in] The Variant listed Pin number
 * 
 * @return None
 */ 
inline void togglePin(int pin)
{
    if (digitalRead(pin)) {
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW);
    }
}

/**
 * blinkLed helps to flip the pin for a fixed number of times.
 * It can be used for both active high and active low logic.
 * The delay for each blink (one On and one Off) can also be controlled.
 * 
 * @param pin [in] The Variant listed Pin number
 * @param n [in] Number of times the Blink needs to be performed
 * @param onLevel [in] Active-low and Active-High selection
 *              true - Active High
 *              false - Active low
 * @param delayms [in] Delay between the two changes (one On and one Off)
 *               in millisecond units
 * 
 * @return None
 * 
 */ 
void blinkLed(uint32_t pin, uint32_t n=3, bool onLevel=true, uint32_t delayms=300ul);

/**
 * Generic Template operator overloading for `<<` Operator
 * to help direct printing for any type of inputs.
 * Internally the overloading as part of the `Print` class
 * are used.
 * The stream objects include Serial and LCD like classes.
 * Basically it helps to write code like:
 *      Serial << F("This is a String");
 * 
 * @param obj [ref] LHS for the `>>` Operator is a Stream class object
 * @param arg [template] RHS for the `>>` Operator is a Template type argument
 * 
 * @return Object reference from @ref obj
 */ 
template<class T> 
inline Stream& operator <<(Stream &obj, T arg) 
{ obj.print(arg); return obj; }

/**
 * Stream WaitFor function is used to block execution till the required 
 * input is received from the passed stream reference.
 * 
 * @note This function "Blocks" till the particular @ref c is received
 * 
 * @note This functional additionally prints a '.' dot before going into
 *        wait loop.
 * 
 * @param obj [ref] Stream Object to be waited upon and polled from
 * @param c [in] Charcater which is matched for the received item
 * 
 * @return Object reference from @ref obj
 */
Stream& waitFor(Stream &obj, char c);
#define SerialWaitFor(C) waitFor(Serial, (char)C)
#define _Wait(C) waitFor(Serial, (char)C)
/**
 * Stream HexByte function is used to correctly represent zero based
 * hexadecimal numbers. This function works for `byte` or `uint8_t` type
 * input data only. Hence only has 2 nibble processing.
 * 
 * @note This function directly prints the nibble through the stream
 * 
 * @param obj [ref] Stream Object to be waited upon and polled from
 * @param data [in] The byte that needs to be represented in Hex
 * 
 * @return Object reference from @ref obj
 */
Stream& HexByte(Stream &obj, byte data);
#define printHexByte(C) HexByte(Serial, (byte)C)
#define _HEX(C) HexByte(Serial, (byte)C)

/**
 * Stream HexWord function is used to correctly represent zero based
 * hexadecimal numbers. This function works for `word` or `uint16_t` type
 * input data only. Hence only has 4 nibble processing.
 * 
 * @note This function directly prints the nibble through the stream
 * 
 * @note This function internally uses @ref HexByte
 * 
 * @param obj [ref] Stream Object to be waited upon and polled from
 * @param data [in] The word that needs to be represented in Hex
 * 
 * @return Object reference from @ref obj
 */ 
Stream& HexWord(Stream &obj, uint16_t data);
#define printHexWord(C) HexWord(Serial, (uint16_t)C)
#define _HEX16(C) HexWord(Serial, (uint16_t)C)

/**
 * Stream HexDWord function is used to correctly represent zero based
 * hexadecimal numbers. This function works for `uint32_t` type
 * input data only. 
 * 
 * @note This function directly prints the nibble through the stream
 * 
 * @note This function internally uses @ref HexByte
 * 
 * @param obj [ref] Stream Object to be waited upon and polled from
 * @param data [in] The 32-bit that needs to be represented in Hex
 * 
 * @return Object reference from @ref obj
 */ 
Stream& HexDWord(Stream &obj, uint32_t data);
#define printHexDWord(C) HexDWord(Serial, (uint32_t)C)
#define printHex(C) HexDWord(Serial, (uint32_t)C)
#define _HEX32(C) HexDWord(Serial, (uint32_t)C)

/**
 * Stream HexBuffer function is used to print a complete input
 * buffer in single byte processed Hex string.
 * 
 * @note This function directly prints complete buffer 
 *        through the stream processing single byte at a time
 * 
 * @note This function internally uses @ref HexByte
 * 
 * @warning This function checks @ref buf is `null` or invalid or
 *      the buffer size @ref size is Zero. Then it would bypass 
 *      of the buffer altogether printing.
 * 
 * @param obj [ref] Stream Object to be waited upon and polled from
 * @param buf [in] Pointer to the Buffer to be printed
 * @param size [in] The size of the buffer @ref buf to be printed
 * 
 * @return Object reference from @ref obj
 */
Stream& HexBuffer(Stream &obj, char * buf, size_t size);
#define printHexBuffer(B, SZ) HexBuffer(Serial, (char *)B, (size_t)SZ)
#define _HEXbuf(B, SZ) HexBuffer(Serial, (char *)B, (size_t)SZ)

/**
 * Stream HexBufferArr function is used to print a complete input
 * buffer in single byte processed Hex string in C style
 * array format.
 * 
 * @note This function directly prints complete buffer 
 *        through the stream processing single byte at a time
 * 
 * @note This function prepends the hex byte with "0x" and adds
 *        "," coma at the end for array like representation.
 * 
 * @note This function internally uses @ref HexByte
 * 
 * @warning This function checks @ref buf is `null` or invalid or
 *      the buffer size @ref size is Zero. Then it would bypass 
 *      of the buffer altogether printing.
 * 
 * @param obj [ref] Stream Object to be waited upon and polled from
 * @param buf [in] Pointer to the Buffer to be printed
 * @param size [in] The size of the buffer @ref buf to be printed
 * 
 * @return Object reference from @ref obj
 */
Stream& HexBufferArr(Stream &obj, char * buf, size_t size);
#define printHexBufferArr(B, SZ) HexBufferArr(Serial, (char *)B, (size_t)SZ)
#define _HEXarr(B, SZ) HexBufferArr(Serial, (char *)B, (size_t)SZ)

/**
 * Generic Template operator overloading for `<<` Operator
 * to help forwarding other Stream operations.
 * Basically it helps to write code like:
 *      Serial << F("This is a String") << HexWord(Serial, 0x3508);
 * 
 * @param obj [ref] LHS for the `>>` Operator is a Stream class object
 * @param arg [template] RHS for the `>>` Operator is also 
 *       Stream class object from another operation
 * 
 * @return Object reference from @ref obj
 */ 
inline Stream& operator <<(Stream &obj, Stream& arg) 
{ return obj; }

#endif /* _COMMONF_H_ */