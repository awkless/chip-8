#include <stdint.h>
#include <stdlib.h>

#include "utils/error.h"
#include "utils/auxfun.h"
#include "core/cpu.h"
#include "tap.h"

#define TEST_COUNT 5                          /* Amount of tests to run. */                         
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
 *   2. chip8_cpu_init() detects non-existant file.
 *   3. chip8_cpu_init() loads rom correctly.
 *   4. chip8_cpu_init() loads fontmap correctly.
 */
static void test_chip8_cpu_init(void)
{
	chip8_cpu *cpu = NULL;
	chip8_error flag = CHIP8_EOK;
	uint8_t *buffer = NULL;
	size_t buflen = 0;

	cmp_ok(chip8_cpu_init(&cpu, NULL), "==", CHIP8_EINVAL,
	   "chip8_cpu_init() detects invalid argument");
	cmp_ok(chip8_cpu_init(&cpu, "bad_rom.ch8"), "==", CHIP8_ENOFILE,
	   "chip8_cpu_init() detects non-existant file");

	flag = chip8_cpu_init(&cpu, DEFAULT_TEST_ROM);
	if (flag != CHIP8_EOK)
		BAIL_OUT("failed to create a CHIP-8 CPU");

	flag = chip8_readrom(DEFAULT_TEST_ROM, &buffer, &buflen);
	if (flag != CHIP8_EOK)
		BAIL_OUT("failed to read ROM data");

	cmp_mem(cpu->memory + CHIP8_ROM_INIT, buffer, buflen,
	        "chip8_cpu_init() loads rom correctly");
	cmp_mem(cpu->memory, EXPECTED_FONTMAP, chip8_arrsize(EXPECTED_FONTMAP),
		"chip8_cpu_init() loads fontmap correctly");

	chip8_cpu_free(&cpu);
	cpu = NULL;
	free(buffer);
	buffer = NULL;
}

/*
 * Starting point of test suite.
 */
int main(void)
{
	plan(TEST_COUNT);
	test_chip8_cpu_reset();
	test_chip8_cpu_init();
	done_testing();
}
