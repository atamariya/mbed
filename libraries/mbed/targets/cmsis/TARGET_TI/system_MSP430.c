#include "system.h"
#include <msp430.h>

void SystemInit () {
	WDTCTL = WDTPW + WDTHOLD;
}

