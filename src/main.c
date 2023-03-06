/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Starting point of CHIP-8 emulator.
 *
 * @return 0 for success, or some @chip8_error code to indicate failure.
 */
int main(void)
{
	/* Opening a basic window to test that SDL2 links properly... */
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *win = SDL_CreateWindow("chip-8 "VERSION,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			1280,
			720,
			0);

	SDL_Renderer *rend = SDL_CreateRenderer(win, -1, 0);
	SDL_Event event;
	bool run = true;
	while (run) {
		while (SDL_PollEvent(&event) > 0) {
			switch(event.type) {
			case SDL_QUIT:
				run = false;
				break;
			}
		}
		SDL_RenderPresent(rend);
	}
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
