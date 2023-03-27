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
