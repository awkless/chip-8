/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils/error.h"

chip8_error chip8_readrom(const char *path, uint8_t **buffer, size_t *size)
{
	FILE *rom = NULL;

	if (!path || !size)
		return CHIP8_EINVAL;

	rom = fopen(path, "rb");
	if (!rom)
		return CHIP8_ENOFILE;

	fseek(rom, 0, SEEK_END);
	*size = ftell(rom);
	rewind(rom);

	*buffer = malloc(sizeof **buffer * *size);
	if (!*buffer) {
		fclose(rom);
		return CHIP8_ENOMEM;
	}

	fread(*buffer, sizeof **buffer, *size, rom);
	fclose(rom);
	return CHIP8_EOK;
}
