/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stddef.h>
#include "us_ticker_api.h"
#include "PeripheralNames.h"

static void timer_init(void);
static void ticker_init(void);


static int us_ticker_inited = 0;
static uint32_t clk_mhz;

void us_ticker_init(void) {
    if (us_ticker_inited)
        return;
    us_ticker_inited = 1;
    
    clk_mhz = bus_frequency() / 1000000;

    timer_init();
    ticker_init();
}

/******************************************************************************
 * Timer for us timing.
 *
 * The K20D5M does not have a prescaler on its PIT timer nor the option
 * to chain timers, which is why a software timer is required to get 32-bit
 * word length.
 ******************************************************************************/
static volatile uint32_t msb_counter = 0;
static uint32_t timer_ldval = 0;

static void timer_isr(void) {
    msb_counter++;
}

static void timer_init(void) {  
}

uint32_t us_ticker_read() {
    return 0;
}

/******************************************************************************
 * Timer Event
 *
 * It schedules interrupts at given (32bit)us interval of time.
 * It is implemented using PIT channel 1, since no prescaler is available,
 * some bits are implemented in software.
 ******************************************************************************/
static void ticker_isr(void);

static void ticker_init(void) {
}

void us_ticker_disable_interrupt(void) {
}

void us_ticker_clear_interrupt(void) {
    // we already clear interrupt in lptmr_isr
}

static uint32_t us_ticker_int_counter = 0;

inline static void ticker_set(uint32_t count) {
}

static void ticker_isr(void) {
    if (us_ticker_int_counter > 0) {
        ticker_set(0xFFFFFFFF);
        us_ticker_int_counter--;
    } else {
        // This function is going to disable the interrupts if there are
        // no other events in the queue
        us_ticker_irq_handler();
    }
}

void us_ticker_set_interrupt(unsigned int timestamp) {
    int delta = (int)(timestamp - us_ticker_read());
    if (delta <= 0) {
        // This event was in the past:
        us_ticker_irq_handler();
        return;
    }

    //Calculate how much falls outside the 32-bit after multiplying with clk_mhz
    //We shift twice 16-bit to keep everything within the 32-bit variable
    us_ticker_int_counter = (uint32_t)(delta >> 16);
    us_ticker_int_counter *= clk_mhz;
    us_ticker_int_counter >>= 16;
    
    uint32_t us_ticker_int_remainder = (uint32_t)delta * clk_mhz;
    if (us_ticker_int_remainder == 0) {
        ticker_set(0xFFFFFFFF);
        us_ticker_int_counter--;
    } else {
        ticker_set(us_ticker_int_remainder);
    }
}
