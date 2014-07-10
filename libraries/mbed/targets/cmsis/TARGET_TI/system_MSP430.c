#include "system.h"
#include <msp430.h>

void SystemInit () {
	WDTCTL = WDTPW + WDTHOLD;
}

void __enable_irq(void)
{
	__eint();
}

void __disable_irq(void)
{
	__dint();
}
