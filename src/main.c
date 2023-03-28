/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <stdbool.h>

#include "SDL.h"
#include "utils/error.h"
#include "core/keypad.h"
#include "core/video.h"
#include "core/cpu.h"

/**
 * @brief Starting point of CHIP-8 emulator.
 *
 * @return 0 for success, or some @p chip8_error code to indicate failure.
 */
int main(void)
{
	chip8_video *video = NULL;
	chip8_keypad *keypad = NULL;
	chip8_cpu *cpu = NULL;
	chip8_error flag = CHIP8_EOK;
	bool quit = false;

	flag = chip8_video_init(&video, 10);
	if (flag != CHIP8_EOK)
		chip8_die(flag);

	flag = chip8_keypad_init(&keypad);
	if (flag != CHIP8_EOK)
		chip8_die(flag);

	flag = chip8_cpu_init(&cpu, video, keypad, 1);
	if (flag != CHIP8_EOK)
		chip8_die(flag);

	flag = chip8_cpu_romload(cpu, "test/roms/ibm_logo.ch8");
	if (flag != CHIP8_EOK)
		chip8_die(flag);

	while (!quit) {
		chip8_keypad_poll(&quit);
		chip8_keypad_process(keypad);
		flag = chip8_cpu_cycle(cpu);
		if (flag != CHIP8_EOK)
			chip8_die(flag);
		flag = chip8_video_render(video);
		if (flag != CHIP8_EOK)
			chip8_die(flag);
	}

	chip8_keypad_free(keypad);
	chip8_video_free(video);
	chip8_cpu_free(cpu);
	return 0;
}
