#ifndef AUDIO_H
#define AUDIO_H

#include "SDL.h"
#include "utils/error.h"

typedef struct {
	SDL_AudioSpec want;
	SDL_AudioSpec have;
	int sample_nr;
} chip8_audio;

chip8_error chip8_audio_init(chip8_audio **audio);
void chip8_audio_play(void);
void chip8_audio_pause(void);
void chip8_audio_free(chip8_audio *audio);

#endif /* AUDIO_H */
