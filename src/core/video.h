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

/**
 * @brief Create a new CHIP-8 video context.
 *
 * @note Set scale to 0 for default window size.
 *
 * @pre video cannot be NULL.
 * @post Will create a new video context with a fully rendered window.
 *
 * @param[in,out] video Video pointer to initialize.
 * @param[in] scale Scale of window to create.
 *
 * @return 0 (CHIP8_EOK) for success or chip8_error for failure.
 */
chip8_error chip8_video_init(chip8_video **video, unsigned int scale);

#endif /* CHIP8_CORE_VIDEO_H */
