/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef CHIP8_CORE_CPU
#define CHIP8_CORE_CPU

#include <stdint.h>

#include "utils/error.h"

#define CHIP8_RAM_SIZE   0x1000 /**< Size of CHIP-8 RAM. */
#define CHIP8_STACK_SIZE 12     /**< Size of CHIP-8 stack. */
#define CHIP8_ROM_INIT   0x200  /**< Start of code segement in CHIP-8. */
#define CHIP8_ROM_LIMIT  0xFFF  /**< End of code segement in CHIP-8. */
#define CHIP8_VREGS      0xF    /**< Amount of registers in CHIP-8. */

#endif /* CHIP8_CORE_CPU */
