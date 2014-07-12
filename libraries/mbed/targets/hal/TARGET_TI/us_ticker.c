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
#include <msp430.h>
#include "us_ticker_api.h"
#include "PeripheralNames.h"

#define US_TICKER_TIMER 0x160 
#define US_TICKER_TIMER_IRQn 0x160 

int us_ticker_inited = 0;

void us_ticker_init(void) {
	if (us_ticker_inited) return;
	us_ticker_inited = 1;

	BCSCTL1 = CALBC1_1MHZ;
        DCOCTL = CALDCO_1MHZ;

	//    NVIC_SetVector(US_TICKER_TIMER_IRQn, (uint32_t)us_ticker_irq_handler);
	//    NVIC_EnableIRQ(US_TICKER_TIMER_IRQn);
}

uint32_t us_ticker_read() {
	if (!us_ticker_inited)
		us_ticker_init();

	return TAR;
}

void us_ticker_set_interrupt(unsigned int timestamp) {
	// set match value
	//	US_TICKER_TIMER->CCR1 = timestamp;
	// enable compare interrupt
}

void us_ticker_disable_interrupt(void) {
}

void us_ticker_clear_interrupt(void) {
}

void wait_us(uint32_t us) {
	CCTL0 = CCIE;                            // CCR0 interrupt enabled
	CCR0 = 50000;
	TACTL = TASSEL_2 + MC_2;                 // SMCLK, contmode

	_BIS_SR(LPM0_bits + GIE);                // Enter LPM0 w/ interrupt
}
