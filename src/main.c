/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "utils/error.h"
#include "core/keypad.h"
#include "core/video.h"
#include "core/audio.h"
#include "core/cpu.h"

static void usage(void)
{
	printf("Usage: chip-8 [-l <rom>] [-f <ins/sec>] [-s <scale>] [-v] [-h]\n"
	       "Simple CHIP-8 emulator.\n\n"
	       "Options:\n"
	       "  -l <rom>     CHIP-8 ROM to load and process.\n"
	       "  -f <ins/sec> CPU speed (instructions per second).\n"
	       "  -s <scale>   Scale factor for window.\n"
	       "  -v           Print version info.\n"
	       "  -h           Print this help info.\n");
}

static void version(void)
{
	printf("CHIP-8 emulator "VERSION"\n\n"
	       "Written by Jason Pena, Nate Le, and John Cully\n");
}

/**
 * @brief Starting point of CHIP-8 emulator.
 *
 * @return 0 for success, or some @p chip8_error code to indicate failure.
 */
int main(int argc, char **argv)
{
	int opt = 0;
	int freq = 0;
	int scale = 0;
	char *rom = NULL;
	chip8_video *video = NULL;
	chip8_keypad *keypad = NULL;
	chip8_audio *audio = NULL;
	chip8_cpu *cpu = NULL;
	chip8_error flag = CHIP8_EOK;
	bool quit = false;

	while ((opt = getopt(argc, argv, "l:f:s:vh")) != -1) {
		switch (opt) {
		case 'l':
			rom = strdup(optarg);
			break;
		case 'f':
			freq = atoi(optarg);
			break;
		case 's':
			scale = atoi(optarg);
			break;
		case 'h':
			usage();
			exit(EXIT_SUCCESS);
			break;
		case 'v':
			version();
			exit(EXIT_SUCCESS);
			break;
		default:
			usage();
			exit(EXIT_FAILURE);
			break;
		}
	}

	flag = chip8_video_init(&video, scale);
	if (flag != CHIP8_EOK)
		chip8_die(flag);

	flag = chip8_keypad_init(&keypad);
	if (flag != CHIP8_EOK)
		chip8_die(flag);

	flag = chip8_audio_init(&audio);
	if (flag != CHIP8_EOK)
		chip8_die(flag);

	flag = chip8_cpu_init(&cpu, video, keypad, audio, freq);
	if (flag != CHIP8_EOK)
		chip8_die(flag);

	flag = chip8_cpu_romload(cpu, rom);
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

	free(rom);
	chip8_keypad_free(keypad);
	chip8_video_free(video);
	chip8_audio_free(audio);
	chip8_cpu_free(cpu);
	return 0;
}
