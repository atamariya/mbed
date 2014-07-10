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
#include <msp430.h>
#include "mbed_assert.h"
#include "gpio_api.h"
#include "pinmap.h"

/*
 * For GPIO, sequence is init > write (for out) > dir > mode. So no need to call pin_function
 * here - called in dir. Effectively only needs to return mask. Hence can be renamed and
 * moved to pinmap.h.
 */
uint32_t gpio_set(PinName pin) {
	MBED_ASSERT(pin != (PinName )NC);
	//	pin_function(pin, 0);

	return (uint32_t)1 << get_pin_index(pin);
}

void gpio_init(gpio_t *obj, PinName pin) {
	obj->pin = pin;
	if (pin == (PinName) NC)
		return;

	obj->mask = get_pin_mask(pin);

	int port_index = get_port_index(pin);
	int pin_index = get_pin_index(pin);

	switch (port_index) {
		case 0:
			obj->reg_in = &P1IN;
			obj->reg_out = &P1OUT;
			obj->reg_dir = &P1DIR;
			break;
		default:
			return;
	}

}

void gpio_mode(gpio_t *obj, PinMode mode) {
	pin_mode(obj->pin, mode);
}

void gpio_dir(gpio_t *obj, PinDirection direction) {
	MBED_ASSERT(obj->pin != (PinName )NC);
	switch (direction) {
		case PIN_INPUT:
			*obj->reg_dir &= ~obj->mask;
			break;
		case PIN_OUTPUT:
			*obj->reg_dir |= obj->mask;
			break;
	}
}

void gpio_write(gpio_t *obj, int value) {
	MBED_ASSERT(obj->pin != (PinName )NC);
	if (value) {
		*obj->reg_out |= obj->mask;
	} else {
		*obj->reg_out &= ~obj->mask;
	}
}

int gpio_read(gpio_t *obj) {
	MBED_ASSERT(obj->pin != (PinName )NC);
	return (*obj->reg_in & obj->mask);
}

