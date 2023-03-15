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
 * Test chip8_keypad_setkey().
 *
 * TEST TYPES:
 *   1. chip8_keypad_setkey() catches NULL keypad.
 *   2. chip8_keypad_setkey() catches invalid key index.
 */
static void test_chip8_keypad_setkey(void)
{
	chip8_keypad *stub = NULL;
	chip8_error flag = CHIP8_EOK;

	cmp_ok(chip8_keypad_setkey(NULL, 0, 0), "==", CHIP8_EINVAL,
	       "chip8_keypad_setkey() catches NULL keypad");

	flag = chip8_keypad_init(&stub);
	if (flag != CHIP8_EOK)
		BAIL_OUT("failed to create CHIP-8 keypad stub");

	cmp_ok(chip8_keypad_setkey(stub, 100, 1), "==", CHIP8_EINVAL,
	       "chip8_keypad_setkey() catches invalid key index");
	
	chip8_keypad_free(stub);
	stub = NULL;
}

/*
 * Test chip8_keypad_getkey().
 *
 * TEST TYPES:
 *   1. chip8_keypad_getkey() catches NULL keypad.
 *   2. chip8_keypad_getkey() catches invalid key index.
 *   3. chip8_keypad_getkey() catches NULL out.
 */
static void test_chip8_keypad_getkey(void)
{
	chip8_keypad *stub = NULL;
	chip8_keypad_state state = CHIP8_KEY_UP;
	chip8_error flag = CHIP8_EOK;

	cmp_ok(chip8_keypad_getkey(NULL, 0, &state), "==", CHIP8_EINVAL,
	       "chip8_keypad_getkey() catches NULL keypad");

	flag = chip8_keypad_init(&stub);
	if (flag != CHIP8_EOK)
		BAIL_OUT("failed to create CHIP-8 keypad stub");

	cmp_ok(chip8_keypad_getkey(stub, 100, &state), "==", CHIP8_EINVAL,
	       "chip8_keypad_setkey() catches invalid key index");
	cmp_ok(chip8_keypad_getkey(stub, 1, NULL), "==", CHIP8_EINVAL,
	       "chip8_keypad_getkey() catches NULL out");
	
	chip8_keypad_free(stub);
	stub = NULL;
}

/*
 * Test chip8_keypad_poll().
 *
 * TEST TYPES:
 *   1. chip8_keypad_poll() catches NULL argument.
 */
static void test_chip8_keypad_poll(void)
{
	cmp_ok(chip8_keypad_poll(NULL), "==", CHIP8_EINVAL,
	       "chip8_keypad_poll catches NULL argument");
}

/*
 * Starting point of tests.
 */
int main(void)
{
	plan(13);
	test_chip8_keypad_init();
	test_chip8_keypad_clear();
	test_chip8_keypad_setkey();
	test_chip8_keypad_getkey();
	test_chip8_keypad_poll();
	done_testing();
}
