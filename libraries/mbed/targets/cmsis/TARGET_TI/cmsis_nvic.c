/* mbed Microcontroller Library - cmsis_nvic for LPC11U24
 * Copyright (c) 2011 ARM Limited. All rights reserved.
 *
 * CMSIS-style functionality to support dynamic vectors
 */
#include "cmsis_nvic.h"

#define NVIC_RAM_VECTOR_ADDRESS (0x1FFFE000)  // Vectors positioned at start of RAM
#define NVIC_FLASH_VECTOR_ADDRESS (0x0)       // Initial vector position in flash

void NVIC_SetVector(IRQn_Type IRQn, uint32_t vector) {
}

uint32_t NVIC_GetVector(IRQn_Type IRQn) {
    return 0;
}
