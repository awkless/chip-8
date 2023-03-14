/**
 * SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 *
 * @file error.c
 */

#include <err.h>
#include <stdlib.h>

#include "SDL.h"
#include "utils/error.h"

static const char *const ERROR_MESSAGE[] = {
	[CHIP8_EOK] = "success",
	[CHIP8_EINVAL] = "invalid argument",
	[CHIP8_ENOMEM] = "no memory",
	[CHIP8_ENOFILE] = "no such file exists",
	[CHIP8_EBIGFILE] = "file is too big to load",
	[CHIP8_ESDL] = "SDL library failure",
	[CHIP8_EBADOP] = "encountered bad opcode during cpu cycle"
};

void chip8_die(chip8_error code)
{
	fprintf(stderr, "chip-8: ");
	if (code >= CHIP8_ECOUNT) {
		fprintf(stderr, "%s\n", ERROR_MESSAGE[CHIP8_EINVAL]);
		exit(CHIP8_EINVAL);
	}

	if (code == CHIP8_ESDL)
		fprintf(stderr, "%s, %s\n", ERROR_MESSAGE[code], SDL_GetError());
	else
		fprintf(stderr, "%s\n", ERROR_MESSAGE[code]);
	exit(code);
}
