/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SDPX-License-Identifier: MIT
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"
#include "utils/error.h"
#include "utils/auxfun.h"
#include "core/keypad.h"

chip8_error chip8_keypad_init(chip8_keypad **keypad)
{
	chip8_error flag = CHIP8_EOK;
	chip8_keypad *newpad = NULL;

	if (keypad == NULL)
		return CHIP8_EINVAL;

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
		return CHIP8_ESDL;
	chip8_debug("setup SDL2 event sub-system");

	newpad = malloc(sizeof *newpad);
        if (newpad == NULL)
		return CHIP8_ENOMEM;

	flag = chip8_keypad_clear(newpad);
	if (flag != CHIP8_EOK)
		goto error;

	newpad->states = NULL;
	*keypad = newpad;
	chip8_debugx("setup new keypad %p\n", (void *)(*keypad));
	goto done;
error:
	chip8_keypad_free(newpad);
	newpad = NULL;
done:
	return flag;
}
