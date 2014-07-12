/*
 **     Copyright: 2014 Anand Tamariya, atamariya@gmail.com
 **
 */

/*!
 * @file system.h
 * @version 2.1
 * @date 2013-10-29
 * @brief Device specific configuration file (header file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_                        /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
#define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */

#include <stdint.h>

	/**
	 * @brief System clock frequency (core clock)
	 *
	 * The system clock frequency supplied to the SysTick timer and the processor
	 * core clock. This variable can be used by the user application to setup the
	 * SysTick timer or configure other parameters. It may also be used by debugger to
	 * query the frequency of the debug timer or configure the trace clock speed
	 * SystemCoreClock is initialized with a correct predefined value.
	 */
	extern uint32_t SystemCoreClock;

	/**
	 * @brief Setup the microcontroller system.
	 *
	 * Typically this function configures the oscillator (PLL) that is part of the
	 * microcontroller device. For systems with variable clock speed it also updates
	 * the variable SystemCoreClock. SystemInit is called from startup_device file.
	 */
	void SystemInit (void);

	/**
	 * @brief Updates the SystemCoreClock variable.
	 *
	 * It must be called whenever the core clock is changed during program
	 * execution. SystemCoreClockUpdate() evaluates the clock register settings and calculates
	 * the current core clock.
	 */
	void SystemCoreClockUpdate (void);

	void __enable_irq();
	void __disable_irq();

#ifdef __cplusplus
}
#endif

#endif  /* #if !defined(SYSTEM_H_) */

