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

chip8_error chip8_keypad_poll(bool *status)
{
	if (status == NULL)
		return CHIP8_EINVAL;

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			*status = true;
		}
	}

	return CHIP8_EOK;
}

chip8_error chip8_keypad_process(chip8_keypad *keypad)
{
	if (keypad == NULL)
		return CHIP8_EINVAL;
	
	const Uint8 *keystates = SDL_GetKeyboardState(NULL);
	const int keymap[] = {
		SDL_SCANCODE_X, /* 0 */
		SDL_SCANCODE_1, /* 1 */
		SDL_SCANCODE_2, /* 2 */
		SDL_SCANCODE_3, /* 3 */
		SDL_SCANCODE_Q, /* 4 */
		SDL_SCANCODE_W, /* 5 */
		SDL_SCANCODE_E, /* 6 */
		SDL_SCANCODE_A, /* 7 */
		SDL_SCANCODE_S, /* 8 */
		SDL_SCANCODE_D, /* 9 */
		SDL_SCANCODE_Z, /* A */
		SDL_SCANCODE_C, /* B */
		SDL_SCANCODE_4, /* C */
		SDL_SCANCODE_R, /* D */
		SDL_SCANCODE_F, /* E */
		SDL_SCANCODE_V  /* F */
	};

	for (uint8_t i = 0; i < chip8_arrsize(keymap); ++i) {
		chip8_keypad_setkey(keypad, i, keystates[keymap[i]]);
	}
	return CHIP8_EOK;
}

chip8_error chip8_keypad_lock(chip8_keypad *keypad, uint8_t *state)
{
	if (keypad == NULL)
		return CHIP8_EINVAL;

	if (state == NULL)
		return CHIP8_EINVAL;

	keypad->states = state;
	return CHIP8_EOK;
}
