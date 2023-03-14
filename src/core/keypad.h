/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef CHIP8_CORE_KEYBOARD_H
#define CHIP8_CORE_KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#include "utils/error.h"

#define CHIP8_KEYPAD_SIZE 16 /**< Amount of keys in CHIP-8 keypad. */

/**
 * @brief State a keypad key can have.
 */
typedef enum {
	CHIP8_KEY_DOWN = 1, /**< Key is pressed. */
	CHIP8_KEY_UP = 0    /**< Key is unpressed. */
} chip8_keypad_state;

/**
 * @brief Representation of CHIP-8 keypad.
 *
 * @note We are using SDL2 scan codes to determine what key is pressed, and
 *       whether or not the keypad is currently locked, i.e., the user is
 *       holding down a key.
 */
typedef struct {
	uint8_t keys[CHIP8_KEYPAD_SIZE]; /**< Keys of keypad. */
	uint8_t *states;                 /**< Scan code state. */
} chip8_keypad;

#endif /* CHIP8_CORE_KEYBOARD_H */
