/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef CHIP8_CORE_CPU
#define CHIP8_CORE_CPU

#include <stdint.h>

#include "core/video.h"
#include "core/keypad.h"
#include "core/audio.h"
#include "utils/error.h"

#define CHIP8_RAM_SIZE   0x1000 /**< Size of CHIP-8 RAM. */
#define CHIP8_STACK_SIZE 12     /**< Size of CHIP-8 stack. */
#define CHIP8_ROM_INIT   0x200  /**< Start of code segement in CHIP-8. */
#define CHIP8_ROM_LIMIT  0xFFF  /**< End of code segement in CHIP-8. */
#define CHIP8_VREGS      16     /**< Amount of registers in CHIP-8. */

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
	uint16_t opcode;                  /**< 16-bit current opcode. */
	chip8_video *video;               /**< Video context. */
	chip8_keypad *keypad;             /**< Keypad context. */
	chip8_audio *audio;               /**< Audio context. */
	uint64_t ticks;                   /**< Current total tick rate. */
	float timer_ticks;                /**< Current timer tick rate. */
	float cycle_ticks;                /**< Current opcode cycle ticks. */
	float cycle_freq;                 /**< Max opcode cycle frequency. */
} chip8_cpu;

/**
 * @brief Create a new CHIP-8 CPU context.
 *
 * @note If opnum is set to zero, then CHIP-8 CPU will default to 700
 *       instructions per second.
 *
 * @pre cpu must not be NULL.
 * @pre video must not be NULL.
 * @pre keypad must not be NULL.
 *
 * @param[in,out] cpu CHIP-8 CPU context to initialize.
 * @param[in] video Video context to apply to CPU.
 * @param[in] keypad Keypad context to apply to CPU.
 * @param[in] opnum  Number of instructions to process per second.
 * @return 0 (#CHIP8_EOK) for success or #chip8_error code for failure.
 */
chip8_error chip8_cpu_init(chip8_cpu **cpu, chip8_video *video,
		           chip8_keypad *keypad, chip8_audio *audio, unsigned int opnum);

/**
 * @brief Load rom data into CHIP-8 CPU context.
 *
 * @pre cpu must not be NULL.
 * @pre rom must not be NULL.
 *
 * @param[in,out] cpu CHIP-8 CPU context to load ROM data into.
 * @param[in] rom Name of the rom to load.
 * @return 0 (#CHIP8_EOK) for success or #chip8_error code for failure.
 */
chip8_error chip8_cpu_romload(chip8_cpu *cpu, const char *rom);

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
chip8_error chip8_cpu_reset(chip8_cpu *cpu);


/**
 * @brief Execute a CHIP-8 CPU cycle.
 *
 * @pre #cpu must be initialized with #chip8_cpu_init() beforehand.
 * @post #cpu state will be updated by whatever instruction was executed.
 *
 * @param[in,out] cpu CHIP-8 CPU context to execute cycle from.
 * @return 0 (#CHIP8_EOK) for success, or #chip8_error code for failure.
 */
chip8_error chip8_cpu_cycle(chip8_cpu *cpu);

/**
 * @brief Free CHIP-8 CPU context back to system.
 *
 * @pre #cpu must have been initialized with #chip8_cpu_init() beforehand.
 *
 * @param[in,out] cpu CHIP-8 cpu context to be freed.
 */
void chip8_cpu_free(chip8_cpu *cpu);

#endif /* CHIP8_CORE_CPU */
