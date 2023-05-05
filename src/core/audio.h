/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef AUDIO_H
#define AUDIO_H

#include "SDL.h"
#include "utils/error.h"

/**
 * @brief CHIP-8 audio context.
 */
typedef struct {
	SDL_AudioSpec want; /**< Audio specs we want. */
	SDL_AudioSpec have; /**< Audio specs we got. */
	int sample_nr;      /**< Current sample count. */
} chip8_audio;

/**
 * @brief Initialize audio system.
 *
 * @param[in,out] audio Pointer to audio context.
 * @return CHIP8_EOK on success or chip8_error on failure.
 */
chip8_error chip8_audio_init(chip8_audio **audio);

/**
 * @brief Play audio data in buffer.
 */
void chip8_audio_play(void);

/**
 * @brief Pause audio currently playing.
 */
void chip8_audio_pause(void);

/**
 * @brief Deallocate audio system.
 *
 * @param[in,out] audio Pointer to audio context to free.
 */
void chip8_audio_free(chip8_audio *audio);

#endif /* AUDIO_H */
