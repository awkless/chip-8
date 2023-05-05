/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */
#include <stdint.h>
#include <math.h>

#include "SDL.h"
#include "core/audio.h"
#include "utils/error.h"

#define CHIP8_AMPLITUDE 28000
#define CHIP8_SAMPLE_RATE 44100

static void chip8_beep(void *data, uint8_t *stream, int slen)
{
	Sint16 *buffer = (Sint16 *)stream;
	int len = slen / 2;
	int sample_nr = (*(int*)data);

	for (int i = 0; i < len; i++, sample_nr++) {
		double time = (double)sample_nr / (double)CHIP8_SAMPLE_RATE;
		buffer[i] = (Sint16)(CHIP8_AMPLITUDE * sin(2.0f * M_PI *
			             441.0f * time));
	}
}

chip8_error chip8_audio_init(chip8_audio **audio)
{
	chip8_audio *new = NULL;
	chip8_error flag = CHIP8_EOK;
	if (audio == NULL)
		return CHIP8_EINVAL;

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
		return CHIP8_ESDL;

	new = malloc(sizeof *new);
	if (new == NULL) {
		flag = CHIP8_ENOMEM;
		goto error;
	}

	new->sample_nr = 0;
	new->want.freq = CHIP8_SAMPLE_RATE;
	new->want.format = AUDIO_S16SYS;
	new->want.channels = 1;
	new->want.samples = 2048;
	new->want.callback = chip8_beep;
	new->want.userdata = &new->sample_nr;
	if (SDL_OpenAudio(&new->want, &new->have) < 0)
		return CHIP8_ESDL;
	goto done;
error:
	chip8_audio_free(new);
	new = NULL;
done:
	return flag;
}

void chip8_audio_play(void)
{
	SDL_PauseAudio(0);
}

void chip8_audio_pause(void)
{
	SDL_PauseAudio(1);
}

void chip8_audio_free(chip8_audio *audio)
{
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	free(audio);
}
