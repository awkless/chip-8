/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "tap.h"
#include "utils/error.h"
#include "utils/auxfun.h"

/*
 * Default stub rom to test with.
 */
#define DEFAULT_ROM_FILE "test/roms/stub.ch8"

/*
 * Expected binary data from stub rom. These bytes represent the following
 * CHIP-8 instructions:
 *
 * LD V1, 2
 * LD V2, 3
 * ADD V1, V2
 */
#define EXPECTED_ROM_DATA_SIZE 6
static const uint8_t EXPECTED_ROM_DATA[EXPECTED_ROM_DATA_SIZE] = {
	0x61, 0x02, 0x62, 0x03, 0x81, 0x24
};

/*
 * Test chip8_arrsize() macro.
 *
 * TEST TYPES:
 *   1. chip8_arrsize() can calculate correct array sizes for array types.
 */
static void test_chip8_arrsize(void)
{
	int arr1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	cmp_ok(chip8_arrsize(arr1), "==", 10,
	       "chip8_arrsize() calculates array size correctly");
}

/*
 * Test test_chip8_readrom().
 *
 * TEST TYPES:
 *   1. chip8_readrom() catches NULL file path.
 *   2. chip8_readrom() catches non-existant file path.
 *   3. chip8_readrom() catches NULL buffer.
 *   4. chip8_readrom() catches NULL size parameter.
 *   5. chip8_readrom() returns no errors for opening a binary file.
 *   6. chip8_readrom() counts binary file size correctly in bytes.
 *   7. chip8_readrom() reads binary files correctly.
 */
static void test_chip8_readrom(void)
{
	char *path = DEFAULT_ROM_FILE;
	uint8_t *buffer = NULL;
	size_t size = 0;
	chip8_error code = 0;
	cmp_ok(chip8_readrom(NULL, &buffer, &size), "==", CHIP8_EINVAL,
	       "chip8_readrom() catches NULL file path");
	cmp_ok(chip8_readrom(path, &buffer, NULL), "==", CHIP8_EINVAL,
	       "chip8_readrom() catches NULL buffer size variable");
	cmp_ok(chip8_readrom(path, NULL, &size), "==", CHIP8_EINVAL,
	       "chip8_readrom() catches NULL buffer variable");
	cmp_ok(chip8_readrom("badrom.ch8", &buffer, &size), "==", CHIP8_ENOFILE,
	       "chip8_readrom() catches non-existant file path");

	code = chip8_readrom(path, &buffer, &size);
	cmp_ok(code, "==", CHIP8_EOK,
	       "chip8_readrom() returns no error for opening a binary file");
	cmp_ok(EXPECTED_ROM_DATA_SIZE, "==", size,
	       "chip8_readrom() counts binary file size correctly");
	cmp_mem(buffer, EXPECTED_ROM_DATA, size,
		"chip8_readrom() reads binary files correctly)");
	free(buffer);
	buffer = NULL;
}

/*
 * Starting point of test suite.
 */
int main(void)
{
	plan(8);
	test_chip8_arrsize();
	test_chip8_readrom();
	done_testing();
}
