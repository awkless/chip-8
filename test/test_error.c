/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include "tap.h"
#include "utils/error.h"

/*
 * Test chip8_die().
 *
 * TEST TYPES:
 *   1. chip8_die() catches error code equals CHIP8_ECOUNT.
 *   2. chip8_die() catches error code greater than CHIP8_ECOUNT.
 *   3. chip8_die() catches negative error code.
 */
static void test_chip8_die(void)
{
	dies_ok({chip8_die(CHIP8_ECOUNT);},
		"chip8_die() catches error code == CHIP8_ECOUNT");
	dies_ok({chip8_die(1024);},
		"chip8_die() catches error code > CHIP8_ECOUNT");
	dies_ok({chip8_die(-1024);},
		"chip8_die() catches negative error code");
}

/*
 * Starting point of test suite.
 */
int main(void)
{
	plan(3);
	test_chip8_die();
	done_testing();
}
