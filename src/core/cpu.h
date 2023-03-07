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

/**
 * @brief Representation of CHIP-8 cpu.
 */
typedef struct {
	uint8_t memory[CHIP8_RAM_SIZE];   /**< 4KiB memory space. */
	uint8_t v[CHIP8_VREGS];           /**< 16 8-bit data registers. */
	uint8_t dt;                       /**< 8-bit delay timer. */
	uint8_t st;                       /**< 8-bit sound timer. */
	uint16_t stack[CHIP8_STACK_SIZE]; /**< 8-bit stack */
	uint16_t sp;                      /**< 8-bit stack pointer. */
	uint16_t i;                       /**< 8-bit index register. */
	uint16_t pc;                      /**< 8-bit program counter. */
} chip8_cpu;

/**
 * @brief Create a new CHIP-8 CPU with loaded ROM data.
 *
 * @pre #file cannot be NULL.
 * @post #cpu context will be initialized with zeroed data.
 * @post Do not forget to free the cpu context with #chip8_cpu_free().
 *
 * @param[in,out] cpu CHIP-8 CPU context to initialize.
 * @param[in] file ROM file to be loaded.
 * @return 0 (#CHIP8_EOK) for success or #chip8_error code for failure.
 */
chip8_error chip8_cpu_init(chip8_cpu **cpu, const char *file);

/**
 * @brief Reset CHIP-8 CPU.
 *
 * @note Does not reset RAM.
 *
 * @pre #cpu must be initialized with #chip8_cpu_init() beforehand.
 * @post #cpu state will be reset.
 *
 * @param[in,out] cpu CHIP-8 CPU context to reset.
 * @return 0 (#CHIP_EOK) for success, or #chip8_error code for failure.
 */
chip8_error chip8_cpu_reset(chip8_cpu **cpu);

#endif /* CHIP8_CORE_CPU */
