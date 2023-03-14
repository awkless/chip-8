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

/**
 * @brief Initialize keypad.
 *
 * @pre #keypad cannot be NULL.
 * @post #keypad will be allocated dynamically with cleared state.
 * @post You must call #chip8_keypad_free() to deallocate #keypad to avoid
 *       memory leaks.
 *
 * @param[in,out] keypad Keypad to initialize.
 * @return 0 (#CHIP8_EOK) for success, or #chip8_error code for failure.
 */
chip8_error chip8_keypad_init(chip8_keypad **keypad);

/**
 * @brief Deinitialize keypad.
 *
 * @pre #keypad must be initialized by #chip8_keypad_init() beforehand.
 * @post #keypad will be deinitialized from memory.
 *
 * @param[in,out] keypad Keypad to free.
 */
void chip8_keypad_free(chip8_keypad *keypad);

/**
 * @brief Clear keypad.
 *
 * @pre #keypad cannot be NULL.
 * @post #keypad state will be cleared.
 *
 * @param[in,out] keypad Keypad to clear.
 * @return 0 (#CHIP8_EOK) for success, or #chip8_error code for failure.
 */
chip8_error chip8_keypad_clear(chip8_keypad *keypad);

/**
 * @brief Set a key in keypad.
 *
 * @pre #keypad cannot be NULL.
 * @pre #key cannot be larger that #CHIP8_KEYPAD_SIZE.
 * @post #key in keypad will be set to target #state.
 *
 * @param[in,out] keypad Keypad to set key into.
 * @param[in] key Key to set.
 * @param[in] state State to set target key too.
 * @return 0 (#CHIP8_EOK) for success, or #chip8_error code for failure.
 */
chip8_error chip8_keypad_setkey(chip8_keypad *keypad, uint8_t key, chip8_keypad_state state);

/**
 * @brief Get key information from keypad.
 *
 * @pre #keypad cannot be NULL.
 * @pre #key cannot be larger that #CHIP8_KEYPAD_SIZE.
 * @pre #out cannot be NULL.
 * @post #out will contain the current state of target #key.
 *
 * @param[in,out] keypad Keypad to get key from.
 * @param[in] key Key to get.
 * @param[out] out State of target key to give back to caller.
 * @return 0 (#CHIP8_EOK) for success, or #chip8_error code for failure.
 */
chip8_error chip8_keypad_getkey(chip8_keypad *keypad, uint8_t key, chip8_keypad_state *out);

/**
 * @brief Poll for keypad input.
 *
 * @pre #status cannot be NULL.
 * @post Return true if poll wants to exit main loop, false otherwise.
 *
 * @param[out] status Status of poll.
 * @return 0 (#CHIP8_EOK) for success, or #chip8_error code for failure.
 */
chip8_error chip8_keypad_poll(bool *status);

#endif /* CHIP8_CORE_KEYBOARD_H */
