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

void chip8_keypad_free(chip8_keypad *keypad)
{
	chip8_debug("shutdown SDL2 event sub-system");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	chip8_debug("free CHIP-8 keypad");
	free(keypad);
}

chip8_error chip8_keypad_clear(chip8_keypad *keypad)
{
	if (keypad == NULL)
		return CHIP8_EINVAL;

	memset(keypad->keys, CHIP8_KEY_UP, CHIP8_KEYPAD_SIZE);
	return CHIP8_EOK;
}

chip8_error chip8_keypad_setkey(chip8_keypad *keypad, uint8_t key, chip8_keypad_state state)
{
	if (keypad == NULL)
		return CHIP8_EINVAL;

	if (key >= CHIP8_KEYPAD_SIZE)
		return CHIP8_EINVAL;

	keypad->keys[key] = state;
	if ((keypad->states) != NULL && (state != CHIP8_KEY_UP)) {
		*(keypad->states) = key;
		keypad->states = NULL;
	}

	return CHIP8_EOK;
}

chip8_error chip8_keypad_getkey(chip8_keypad *keypad, uint8_t key, chip8_keypad_state *out)
{
	if (keypad == NULL)
		return CHIP8_EINVAL;

	if (key >= CHIP8_KEYPAD_SIZE)
		return CHIP8_EINVAL;

	if (out == NULL)
		return CHIP8_EINVAL;

	*out = keypad->keys[key];
	return CHIP8_EOK;
}
