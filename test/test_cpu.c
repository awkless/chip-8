/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stdint.h>
#include <stdlib.h>

#include "utils/error.h"
#include "utils/auxfun.h"
#include "core/cpu.h"
#include "core/keypad.h"
#include "core/video.h"
#include "core/audio.h"
#include "tap.h"

#define DEFAULT_TEST_ROM "test/roms/stub.ch8" /* Default ROM for testing. */

/* Expected font map. */
static const uint8_t EXPECTED_FONTMAP[] = {
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

/*
 * Test chip8_cpu_reset().
 *
 * TEST TYPES:
 *   1. chip8_cpu_reset catches invalid arguments.
 */
static void test_chip8_cpu_reset(void)
{
	cmp_ok(chip8_cpu_reset(NULL), "==", CHIP8_EINVAL,
	       "chip8_cpu_reset() catches invalid arguments");
}

/*
 * Test chip8_cpu_init().
 *
 * TEST TYPES:
 *   1. chip8_cpu_init() detects invalid argument.
 *   2. chip8_cpu_init() loads fontmap correctly.
 */
static void test_chip8_cpu_init(chip8_cpu *cpu, chip8_video *video,
		                chip8_keypad *keys, chip8_audio *audio)
{
	cmp_ok(chip8_cpu_init(NULL, NULL, NULL, NULL, 0), "==", CHIP8_EINVAL,
	       "chip8_cpu_init() detects NULL CPU");
	cmp_ok(chip8_cpu_init(&cpu, video, NULL, NULL, 0), "==", CHIP8_EINVAL,
	       "chip8_cpu_init() detects NULL keypad");
	cmp_ok(chip8_cpu_init(&cpu, NULL, keys, NULL, 0), "==", CHIP8_EINVAL,
	       "chip8_cpu_init() detects NULL video");
	cmp_mem(cpu->memory, EXPECTED_FONTMAP, chip8_arrsize(EXPECTED_FONTMAP),
		"chip8_cpu_init() loads fontmap correctly");
}

/*
 * Test chip8_cpu_romload().
 *
 * TEST TYPES:
 *   1. chip8_cpu_romload() detects invalid arguments.
 *   2. chip8_cpu_romload() loads ROM correctly.
 */
static void test_chip8_cpu_romload(chip8_cpu *cpu)
{
	chip8_error flag = CHIP8_EOK;
	uint8_t *buffer = NULL;
	size_t buflen = 0;

	cmp_ok(chip8_cpu_romload(NULL, "testing"), "==", CHIP8_EINVAL,
	       "chip8_cpu_romload() detects NULL CPU context");
	cmp_ok(chip8_cpu_romload(cpu, NULL), "==", CHIP8_EINVAL,
	       "chip8_cpu_romload() detects NULL ROM name");
	cmp_ok(chip8_cpu_romload(cpu, "bad.ch8"), "==", CHIP8_ENOFILE,
	       "chip8_cpu_romload() detects non-existant ROM");

	flag = chip8_cpu_romload(cpu, DEFAULT_TEST_ROM);
	if (flag != CHIP8_EOK)
		BAIL_OUT("stub rom could not be found");

	flag = chip8_readrom(DEFAULT_TEST_ROM, &buffer, &buflen);
	if (flag != CHIP8_EOK)
		BAIL_OUT("stub rom could not be found");
	cmp_mem(cpu->memory + CHIP8_ROM_INIT, buffer, buflen,
	        "chip8_cpu_init() loads rom correctly");
	free(buffer);
	buffer = NULL;
}

/*
 * Test chip8_cpu_cycle().
 *
 * TEST TYPES:
 *   1. chip8_cpu_cycle() detects NULL argument.
 */
static void test_chip8_cpu_cycle(void)
{
	cmp_ok(chip8_cpu_cycle(NULL), "==", CHIP8_EINVAL,
	       "chip8_cpu_cycle() detects NULL argument");
}

/*
 * Starting point of test suite.
 */
int main(void)
{
	chip8_video *video = NULL;
	chip8_keypad *keys = NULL;
	chip8_audio *audio = NULL;
	chip8_cpu *cpu = NULL;
	chip8_error flag = CHIP8_EOK;
	
	video = malloc(sizeof *video);
	if (video == NULL)
		BAIL_OUT("failed to create video system");

	keys = malloc(sizeof *keys);
	if (keys == NULL)
		BAIL_OUT("failed to create keypad system");

	flag = chip8_cpu_init(&cpu, video, keys, audio, 0);
	if (flag != CHIP8_EOK)
		BAIL_OUT("failed to create cpu system");

	plan(10);
	test_chip8_cpu_reset();
	test_chip8_cpu_init(cpu, video, keys, audio);
	test_chip8_cpu_romload(cpu);
	test_chip8_cpu_cycle();
	done_testing();

	free(video);
	free(keys);
	chip8_cpu_free(cpu);
}
