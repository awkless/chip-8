/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include "tap.h"
#include "core/keypad.h"
#include "utils/error.h"

/*
 * Test chip8_keypad_init()
 *
 * TEST TYPES:
 *   1. chip8_keypad_init() catches NULL keypad
 */
static void test_chip8_keypad_init(void)
{
	cmp_ok(chip8_keypad_init(NULL), "==", CHIP8_EINVAL,
	       "chip8_keypad_init() catches NULL keypad");
}

/*
 * Test chip8_keypad_clear()
 *
 * TEST TYPES:
 *   1. chip8_keypad_clear() catches NULL keypad
 */
static void test_chip8_keypad_clear(void)
{
	cmp_ok(chip8_keypad_clear(NULL), "==", CHIP8_EINVAL,
	       "chip8_keypad_clear() catches NULL keypad");
}

/*
 * Starting point of tests.
 */
int main(void)
{
	plan(11);
	test_chip8_keypad_init();
	test_chip8_keypad_clear();
	done_testing();
}
