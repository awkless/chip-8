/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef CHIP8_CORE_VIDEO_H
#define CHIP8_CORE_VIDEO_H

#include <stdint.h>

#include "utils/error.h"
#include "SDL.h"

#define CHIP8_VIDEO_WIDTH 64
#define CHIP8_VIDEO_HEIGHT 32

/**
 * @brief CHIP-8 video information.
 */
typedef struct {
	SDL_Window *window;     /**< SDL window pointer. */
	SDL_Renderer *renderer; /**< SDL renderer pointer. */
	SDL_Texture *texture;   /**< SDL texture pointer. */
	
	/** Screen pixel data. */
	uint8_t pixels[CHIP8_VIDEO_HEIGHT][CHIP8_VIDEO_WIDTH];

	/** Texture buffer data. */
	uint32_t buffer[CHIP8_VIDEO_WIDTH * CHIP8_VIDEO_HEIGHT];
} chip8_video;

#endif /* CHIP8_CORE_VIDEO_H */
