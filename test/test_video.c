/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include "tap.h"
#include "core/video.h"
#include "utils/error.h"

/*
 * Super minimal testing, because we could not find a reliable way to make
 * SDL fail in a controlled manner for further testing.
 */

/*
 * Test test_chip8_video_init().
 *
 * TEST TYPES
 *   1. chip8_video_init() catches NULL argument.
 */
static void test_chip8_video_init(void)
{
	cmp_ok(chip8_video_init(NULL, 0), "==", CHIP8_EINVAL,
	       "chip8_video_init() catches NULL argument");
}

/*
 * Test chip8_video_render().
 *
 * TEST TYPES
 *   1. chip8_video_render() catches NULL argument.
 */
static void test_chip8_video_render(void)
{
	cmp_ok(chip8_video_render(NULL), "==", CHIP8_EINVAL,
	       "chip8_video_render() catches NULL argument");
}

/*
 * Test chip8_video_clear().
 *
 * TEST TYPES
 *   1. chip8_video_clear() catches NULL argument.
 */
static void test_chip8_video_clear(void)
{
	cmp_ok(chip8_video_clear(NULL), "==", CHIP8_EINVAL,
	       "chip8_video_clear() catches NULL argument");
}

int main(void)
{
	plan(3);
	test_chip8_video_init();
	test_chip8_video_render();
	test_chip8_video_clear();
	done_testing();
}
