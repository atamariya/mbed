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
#include "mbed_assert.h"
#include "gpio_api.h"
#include "pinmap.h"

// Utility funtions - start
uint32_t get_port_index(PinName pin) {
	return (uint32_t) pin >> 4;
}

uint32_t get_pin_index(PinName pin) {
	return (uint32_t) pin & 0xF;
}
// Utility funtions - End

uint32_t gpio_set(PinName pin) {
    MBED_ASSERT(pin != (PinName)NC);

    return 1 << get_pin_index(pin);
}

void gpio_init(gpio_t *obj, PinName pin) {
    obj->pin = pin;
    if (pin == (PinName)NC)
        return;

    obj->mask = gpio_set(pin);
}

void gpio_mode(gpio_t *obj, PinMode mode) {
    pin_mode(obj->pin, mode);
}

void gpio_dir(gpio_t *obj, PinDirection direction) {
    MBED_ASSERT(obj->pin != (PinName)NC);
    switch (direction) {
        case PIN_INPUT :
            pin_function(obj->pin, PIN_INPUT);
            break;
        case PIN_OUTPUT:
            pin_function(obj->pin, PIN_OUTPUT);
            break;
    }
}
