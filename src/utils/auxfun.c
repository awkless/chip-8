/**
 * SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 *
 * @file auxfun.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils/error.h"
#include "utils/auxfun.h"

chip8_error chip8_readrom(const char *path, uint8_t **buffer, size_t *size)
{
	FILE *rom = NULL;
	uint8_t *newbuf = NULL;

	if ((path == NULL) || (buffer == NULL) || (size == NULL))
		return CHIP8_EINVAL;

	rom = fopen(path, "rb");
	if (!rom)
		return CHIP8_ENOFILE;

	fseek(rom, 0, SEEK_END);
	*size = ftell(rom);
	rewind(rom);

	newbuf = malloc(sizeof *newbuf * *size);
	if (!newbuf) {
		fclose(rom);
		return CHIP8_ENOMEM;
	}

	fread(newbuf, sizeof *newbuf, *size, rom);
	fclose(rom);

	*buffer = newbuf;
	return CHIP8_EOK;
}
