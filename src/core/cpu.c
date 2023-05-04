/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 *
 * @file cpu.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "core/video.h"
#include "core/keypad.h"
#include "core/cpu.h"
#include "core/opcode.h"
#include "core/audio.h"
#include "utils/auxfun.h"

#define CHIP8_TIMER_FREQ (1.0f / 60.0f) /**< 60Hz timer frequency. */
#define CHIP8_DEFAULT_OPNUM 700         /**< Default opcodes per second. */

/**
 * @brief Initialize RAM.
 *
 * @note INTERNAL USE ONLY!
 * @pre #cpu cannot be NULL.
 *
 * @param[in,out] cpu CHIP-8 CPU context to init RAM of.
 * @return 0 (CHIP8_EOK) for success, chip8_error for failure.
 */
static chip8_error chip8_cpu_raminit(chip8_cpu *cpu)
{
	if (cpu == NULL)
		return CHIP8_EINVAL;

	const uint8_t font_map[] = {
		0xF0, 0x90, 0x90, 0x90, 0xF0, /* 0 */
		0x20, 0x60, 0x20, 0x20, 0x70, /* 1 */
		0xF0, 0x10, 0xF0, 0x80, 0xF0, /* 2 */
		0xF0, 0x10, 0xF0, 0x10, 0xF0, /* 3 */
		0x90, 0x90, 0xF0, 0x10, 0x10, /* 4 */
		0xF0, 0x80, 0xF0, 0x10, 0xF0, /* 5 */
		0xF0, 0x80, 0xF0, 0x90, 0xF0, /* 6 */
		0xF0, 0x10, 0x20, 0x40, 0x40, /* 7 */
		0xF0, 0x90, 0xF0, 0x90, 0xF0, /* 8 */
		0xF0, 0x90, 0xF0, 0x10, 0xF0, /* 9 */
		0xF0, 0x90, 0xF0, 0x90, 0x90, /* A */
		0xE0, 0x90, 0xE0, 0x90, 0xE0, /* B */
		0xF0, 0x80, 0x80, 0x80, 0xF0, /* C */
		0xE0, 0x90, 0x90, 0x90, 0xE0, /* D */
		0xF0, 0x80, 0xF0, 0x80, 0xF0, /* E */
		0xF0, 0x80, 0xF0, 0x80, 0x80, /* F */
	};

	memset(cpu->memory, 0, sizeof *(cpu->memory) * CHIP8_RAM_SIZE);
	memcpy(cpu->memory, font_map, chip8_arrsize(font_map));
	return CHIP8_EOK;
}

/**
 * @brief Calculate delta for instruction timing.
 *
 * @note INTERNAL USE ONLY!
 *
 * @pre cpu must not be NULL
 * @pre delta must not be NULL.
 *
 * @param[in,out] cpu CHIP-8 CPU context to set ticks for.
 * @param[out] delta The calculated delta.
 * @return 0 (CHIP8_EOK) for success, chip8_error for failure.
 */
static chip8_error chip8_cpu_getdelta(chip8_cpu *cpu, float *delta)
{
	if (cpu == NULL || delta == NULL)
		return CHIP8_EINVAL;

	Uint64 end = SDL_GetPerformanceCounter();
	*delta = (float)(end - cpu->ticks) / SDL_GetPerformanceFrequency();
	cpu->ticks = end;
	return CHIP8_EOK;
}

chip8_error chip8_cpu_init(chip8_cpu **cpu, chip8_video *video,
		           chip8_keypad *keypad, chip8_audio *audio, unsigned int opnum)
{
	chip8_error flag = CHIP8_EOK;
	chip8_cpu *newcpu = NULL;

	if (cpu == NULL || video == NULL || keypad == NULL)
		return CHIP8_EINVAL;

	if (opnum == 0)
		opnum = CHIP8_DEFAULT_OPNUM;

	if (SDL_InitSubSystem(SDL_INIT_TIMER) < 0)
		return CHIP8_ESDL;

	newcpu = malloc(sizeof *newcpu);
	if (newcpu == NULL)
		return CHIP8_ENOMEM;

	flag = chip8_cpu_raminit(newcpu);
	if (flag != CHIP8_EOK)
		goto out_cpu;

	flag = chip8_cpu_reset(newcpu);
	if (flag != CHIP8_EOK) {
		goto out_cpu;
	}

	newcpu->video = video;
	newcpu->keypad = keypad;
	newcpu->audio = audio;
	newcpu->cycle_freq = (float)(1.0f / opnum);
	*cpu = newcpu;
	goto done;

out_cpu:
	chip8_cpu_free(newcpu);
	cpu = NULL;
done:
	return flag;
}

chip8_error chip8_cpu_romload(chip8_cpu *cpu, const char *rom)
{
	chip8_error flag = CHIP8_EOK;
	uint8_t *buffer = NULL;
	size_t romlen = 0;

	if (cpu == NULL || rom == NULL)
		return CHIP8_EINVAL;

	flag = chip8_readrom(rom, &buffer, &romlen);
	if (flag != CHIP8_EOK)
		goto out_buffer;

	if (romlen > CHIP8_ROM_LIMIT) {
		flag = CHIP8_EBIGFILE;
		goto out_buffer;
	}

	memcpy(cpu->memory + CHIP8_ROM_INIT, buffer, romlen);

out_buffer:
	free(buffer);
	buffer = NULL;
	return flag;
}

chip8_error chip8_cpu_reset(chip8_cpu *cpu)
{
	if (cpu == NULL)
		return CHIP8_EINVAL;

	memset(cpu->v, 0, sizeof *(cpu->v) * CHIP8_VREGS);
	memset(cpu->stack, 0, sizeof *(cpu->stack) * CHIP8_STACK_SIZE);
	cpu->dt = 0;
	cpu->st = 0;
	cpu->sp = 0;
	cpu->i  = 0;
	cpu->pc = CHIP8_ROM_INIT;
	cpu->opcode = 0;
	cpu->ticks = SDL_GetPerformanceCounter();
	cpu->timer_ticks = 0.0f;
	cpu->cycle_ticks = 0.0f;
	return CHIP8_EOK;
}

/**
 * @brief Execute current opcode.
 *
 * @note INTERNAL USE ONLY!
 *
 * @pre cpu must not be NULL.
 *
 * @param[in,out] cpu CHIP-8 CPU context to execute opcode with.
 * @return 0 (CHIP8_EOK) for success, chip8_error for failure.
 */
static chip8_error chip8_cpu_execute(chip8_cpu *cpu)
{
	chip8_error flag = CHIP8_EOK;
	uint16_t opcode = 0; 

	if (cpu == NULL)
		return CHIP8_EINVAL;

	/* User is holding down a key... */	
	bool lock = false;
	flag = chip8_keypad_islock(cpu->keypad, &lock);
	if (lock == true)
		return flag;

	/* Fetch opcode... */
	opcode = cpu->memory[cpu->pc] << 8 | cpu->memory[cpu->pc + 1];
	cpu->opcode = opcode;
	cpu->pc += 2;

	/* Decode and execute... */
	switch (opcode & 0xF000) {
	case 0x0000:
		switch(opcode & 0x00FF) {
		case 0x00E0:
			chip8_opcode_00E0(cpu);
			break;
		case 0x00EE:
			chip8_opcode_00EE(cpu);
			break;
		/* Bad opcode... */
		default:
			flag = CHIP8_EBADOP;
			break;
		}
		break;
	case 0x1000:
		chip8_opcode_1NNN(cpu);
		break;
	case 0x2000:
		chip8_opcode_2NNN(cpu);
		break;
	case 0x3000:
		chip8_opcode_3XNN(cpu);
		break;
	case 0x4000:
		chip8_opcode_4XNN(cpu);
		break;
	case 0x5000:
		chip8_opcode_5XY0(cpu);
		break;
	case 0x6000:
		chip8_opcode_6XNN(cpu);
		break;
	case 0x7000:
		chip8_opcode_7XNN(cpu);
		break;
	case 0x8000:
		switch (opcode & 0x000F)
		{
		case 0x0000:
			chip8_opcode_8XY0(cpu);
			break;
		case 0x0001:
			chip8_opcode_8XY1(cpu);
			break;
		case 0x0002:
			chip8_opcode_8XY2(cpu);
			break;
		case 0x0003:
			chip8_opcode_8XY3(cpu);
			break;
		case 0x0004:
			chip8_opcode_8XY4(cpu);
			break;
		case 0x0005:
			chip8_opcode_8XY5(cpu);
			break;
		case 0x0006:
			chip8_opcode_8XY6(cpu);
			break;
		case 0x0007:
			chip8_opcode_8XY7(cpu);
			break;
		case 0x000E:
			chip8_opcode_8XYE(cpu);
			break;
		/* Bad opcode... */
		default:
			flag = CHIP8_EBADOP;
			break;
		}
		break;
	case 0x9000:
		chip8_opcode_9XY0(cpu);
		break;
	case 0xA000:
		chip8_opcode_ANNN(cpu);
		break;
	case 0xB000:
		chip8_opcode_BNNN(cpu);
		break;
	case 0xC000:
		chip8_opcode_CXNN(cpu);
		break;
	case 0xD000:
		chip8_opcode_DXYN(cpu);
		break;
	case 0xE000:
		switch (opcode & 0x00FF) {
		case 0x009E:
			chip8_opcode_EX9E(cpu);
			break;
		case 0x00A1:
			chip8_opcode_EXA1(cpu);
			break;
		/* Bad opcode... */
		default:
			flag = CHIP8_EBADOP;
			break;
		}
		break;
	case 0xF000:
		switch (opcode & 0x00FF) {
		case 0x0007:
			chip8_opcode_FX07(cpu);
			break;
		case 0x000A:
			chip8_opcode_FX0A(cpu);
			break;
		case 0x0015:
			chip8_opcode_FX15(cpu);
			break;
		case 0x0018:
			chip8_opcode_FX18(cpu);
			break;
		case 0x001E:
			chip8_opcode_FX1E(cpu);
			break;
		case 0x0029:
			chip8_opcode_FX29(cpu);
			break;
		case 0x0033:
			chip8_opcode_FX33(cpu);
			break;
		case 0x0055:
			chip8_opcode_FX55(cpu);
			break;
		case 0x0065:
			chip8_opcode_FX65(cpu);
			break;
		/* Bad opcode... */
		default:
			flag = CHIP8_EBADOP;
			break;
		}
		break;
	/* Bad opcode... */
	default:
		flag = CHIP8_EBADOP;
		break;
	}
	return flag;
}


chip8_error chip8_cpu_cycle(chip8_cpu *cpu)
{
	chip8_error flag = CHIP8_EOK;
	float delta = 0.0f;

	if (cpu == NULL)
		return CHIP8_EINVAL;

	flag = chip8_cpu_getdelta(cpu, &delta);
	if (flag != CHIP8_EOK)
		return flag;

	cpu->timer_ticks += delta;
	while (cpu->timer_ticks > CHIP8_TIMER_FREQ) {
		cpu->timer_ticks -= CHIP8_TIMER_FREQ;
		if (cpu->dt != 0) {
			cpu->dt -= 1;
		}
		if (cpu->st != 0) {
			cpu->st -= 1;
		}
	}

	if (cpu->st != 0) {
		chip8_audio_play();
	} else {
		chip8_audio_pause();
	}


	cpu->cycle_ticks += delta;
	while (cpu->cycle_ticks > cpu->cycle_freq) { 
		cpu->cycle_ticks -= cpu->cycle_freq;
		flag = chip8_cpu_execute(cpu);
	}
	return flag;
}

void chip8_cpu_free(chip8_cpu *cpu)
{
	SDL_QuitSubSystem(SDL_INIT_TIMER);
	free(cpu);
}
