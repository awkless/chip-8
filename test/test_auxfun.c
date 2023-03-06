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
 * Starting point of test suite.
 */
int main(void)
{
	plan(7);
	test_chip8_arrsize();
	done_testing();
}
