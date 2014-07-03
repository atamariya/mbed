/* mbed Microcontroller Library
 *******************************************************************************
 * Copyright (c) 2014, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

typedef enum {
    P1_0  = 0x0,
    P1_1  = 0x01,
    P1_2  = 0x02,
    P1_3  = 0x03,
    P1_4  = 0x04,
    P1_5  = 0x05,
    P1_6  = 0x06,
    P1_7  = 0x07,


    P2_0  = 0x10,
    P2_1  = 0x11,
    P2_2  = 0x12,
    P2_3  = 0x13,
    P2_4  = 0x14,
    P2_5  = 0x15,
    P2_6  = 0x16,
    P2_7  = 0x17,


    P3_0  = 0x20,
    P3_1  = 0x21,
    P3_2  = 0x22,
    P3_3  = 0x23,
    P3_4  = 0x24,
    P3_5  = 0x25,
    P3_6  = 0x26,
    P3_7  = 0x27,


    // Generic signals namings
    LED1        = P1_5,
    LED2        = P1_5,
    LED3        = P1_5,
    LED4        = P1_5,
//    USER_BUTTON = P3_13,
    SERIAL_TX   = P1_2,
    SERIAL_RX   = P1_3,
//    USBTX       = P1_2,
//    USBRX       = P1_3,
//    I2C_SCL     = P2_8,
//    I2C_SDA     = P2_9,
    SPI_MOSI    = P1_7,
    SPI_MISO    = P1_6,
    SPI_SCK     = P1_5,
    SPI_CS      = P2_6,
    PWM_OUT     = P2_3,

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

typedef enum {
    PullNone  = 0,
    PullUp    = 1,
    PullDown  = 2,
    OpenDrain = 3,
    PullDefault = PullNone
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
