/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 *
 * @file cpu.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "core/cpu.h"
#include "utils/auxfun.h"

/**
 * @brief Initialize RAM.
 *
 * @note INTERNAL USE ONLY!
 * @pre #cpu cannot be NULL.
 *
 * @param[in,out] cpu CHIP-8 CPU context to init RAM of.
 */
static void chip8_cpu_raminit(chip8_cpu **cpu)
{
	if (!*cpu)
		return;

	const uint8_t font_map[] = {
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80, // F
	};

	memset((*cpu)->memory, 0, sizeof *((*cpu)->memory) * CHIP8_RAM_SIZE);
	memcpy((*cpu)->memory, font_map, chip8_arrsize(font_map));
}

chip8_error chip8_cpu_init(chip8_cpu **cpu, const char *file)
{
	chip8_error flag = CHIP8_EOK;
	size_t romlen = 0;
	uint8_t *buffer = NULL;

	if (!file)
		return CHIP8_EINVAL;

	*cpu = malloc(sizeof **cpu);
	if (!*cpu)
		return CHIP8_ENOMEM;

	flag = chip8_cpu_reset(cpu);
	if (flag != CHIP8_EOK) {
		goto out_cpu;
	}

	chip8_cpu_raminit(cpu);
	flag = chip8_readrom(file, &buffer, &romlen);
	if (flag != CHIP8_EOK)
		goto out_cpu;

	if (romlen > CHIP8_ROM_LIMIT) {
		flag = CHIP8_EBIGFILE;
		goto out_cpu;
	}

	memcpy((*cpu)->memory + CHIP8_ROM_INIT, buffer, romlen);
	goto out_buffer;

out_cpu:
	chip8_cpu_free(cpu);
	cpu = NULL;
out_buffer:
	free(buffer);
	buffer = NULL;
	return flag;
}

chip8_error chip8_cpu_reset(chip8_cpu **cpu)
{
	if (!cpu)
		return CHIP8_EINVAL;

	memset((*cpu)->v, 0, sizeof *((*cpu)->v) * CHIP8_VREGS);
	memset((*cpu)->stack, 0, sizeof *((*cpu)->stack) * CHIP8_STACK_SIZE);
	(*cpu)->dt = 0;
	(*cpu)->st = 0;
	(*cpu)->sp = 0;
	(*cpu)->i  = 0;
	(*cpu)->pc = CHIP8_ROM_INIT;

	return CHIP8_EOK;
}
