#include "system.h"
#include "InterruptManager.h"
#include <msp430.h>

uint32_t SystemCoreClock = 16000000;

void SystemInit() {
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

	/* Check if 1MHz Calibration is present */
	if (CALBC1_1MHZ != 0xFF) {

		DCOCTL = 0;             // Select lowest DCOx and MODx

		BCSCTL1 = CALBC1_1MHZ;  // Set range

		DCOCTL = CALDCO_1MHZ;   // Set DCO step + modulation

	}

	/* Check if 8MHz Calibration is present */
	if (CALBC1_8MHZ != 0xFF) {

		DCOCTL = 0;             // Select lowest DCOx and MODx

		BCSCTL1 = CALBC1_8MHZ;  // Set range

		DCOCTL = CALDCO_8MHZ;   // Set DCO step + modulation

	}

	/* Check if 12MHz Calibration is present */
	if (CALBC1_12MHZ != 0xFF) {

		DCOCTL = 0;             // Select lowest DCOx and MODx

		BCSCTL1 = CALBC1_12MHZ;  // Set range

		DCOCTL = CALDCO_12MHZ;   // Set DCO step + modulation

	}

	/* Check if 16MHz Calibration is present */
	if (CALBC1_16MHZ != 0xFF) {

		DCOCTL = 0;             // Select lowest DCOx and MODx

		BCSCTL1 = CALBC1_16MHZ;  // Set range

		DCOCTL = CALDCO_16MHZ;   // Set DCO step + modulation

	}
}

void __enable_irq(void) {
	__eint();
}

void __disable_irq(void) {
	__dint();
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void) {
	InterruptManager::get()->addEvent(IRQn_Type event);
}
