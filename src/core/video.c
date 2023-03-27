/* SPDX-FileCoyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "SDL.h"
#include "core/video.h"
#include "utils/auxfun.h"
#include "utils/error.h"

#define CHIP8_DEFAULT_SCALE 10

chip8_error chip8_video_init(chip8_video **video, unsigned int scale)
{
	chip8_video *newvid = NULL;
	chip8_error flag = CHIP8_EOK;

	if (video == NULL)
		return CHIP8_EINVAL;

	if (scale == 0)
		scale = CHIP8_DEFAULT_SCALE;

	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
		return CHIP8_ESDL;

	newvid = malloc(sizeof *newvid);
	if (newvid == NULL) {
		flag = CHIP8_ESDL;
		goto error;
	}

	newvid->window = SDL_CreateWindow("CHIP-8",
			                  SDL_WINDOWPOS_UNDEFINED,
					  SDL_WINDOWPOS_UNDEFINED,
					  CHIP8_VIDEO_WIDTH * scale,
					  CHIP8_VIDEO_HEIGHT * scale,
					  SDL_WINDOW_SHOWN);
	if (newvid->window == NULL) {
		flag = CHIP8_ESDL;
		goto error;
	}

	newvid->renderer = SDL_CreateRenderer(newvid->window, -1,
			                      SDL_RENDERER_ACCELERATED);
	if (newvid->renderer == NULL) {
		flag = CHIP8_ESDL;
		goto error;
	}

	newvid->texture = SDL_CreateTexture(newvid->renderer,
			                    SDL_PIXELFORMAT_RGBA8888,
					    SDL_TEXTUREACCESS_TARGET,
					    CHIP8_VIDEO_WIDTH,
					    CHIP8_VIDEO_HEIGHT);
	if (newvid->texture == NULL) {
		flag = CHIP8_ESDL;
		goto error;
	}

	flag = chip8_video_clear(newvid);
	if (flag != CHIP8_EOK)
		goto error;

	*video = newvid;
	chip8_debugx("setup new video %p\n", (void *)(*video));
	goto done;
error:
	chip8_video_free(newvid);
	newvid = NULL;
done:
	return flag;
}
