/**
 * SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 *
 * @file auxfun.h
 */

#ifndef CHIP8_UTILS_H
#define CHIP8_UTILS_H

#include <stdio.h>
#include <stdint.h>

#include "utils/error.h"

#ifdef DEBUG_TRACE
/**
 * @brief Output debugging string with newline.
 *
 * @pre String to debug print.
 * @post Output debugging string onto stderr if -DDEBUG_TRACE is enabled.
 *
 * @param[in] x String to debug print.
 */
#define chip8_debug(x) fprintf(stderr, "chip-8 debug: %s\n", x);

/**
 * @brief Output debugging string with variadic arguments.
 *
 * @pre Variadic arguments to debug print.
 * @post Output debugging variadic string onto stderr if -DDEBUG_TRACE is
 *       enabled.
 *
 * @param[in] x String to print.
 * @param[in] ... Variadic arguments to substitute into string.
 */
#define chip8_debugx(x, ...) fprintf(stderr, "chip-8 debug: "x, ##__VA_ARGS__);
#else
#define chip8_debug(x);
#define chip8_debugx(x, ...);
#endif /* CHIP8_DEBUG */

/**
 * @brief Helper macro to calculate array sizes.
 *
 * @pre @p arr must be an actual array type, and NOT A POINTER TYPE!
 *
 * @param[in] arr Array to calculate size of.
 * @return Size of array in bytes.
 */
#define chip8_arrsize(arr) ((sizeof arr) / (sizeof *arr))

/**
 * @brief Helper to read binary rom data into a buffer.
 *
 * @pre @p path MUST NOT be NULL.
 * @pre @p path MUST point to a real file path.
 * @pre @p buffer MUST be NULL (uninitialized).
 * @pre @p size MUST NOT be NULL.
 * @post @p buffer WILL be filled with binary data.
 * @post @p size WILL house the size of the rom in bytes.
 *
 * @param[in] path Path to file to open.
 * @param[in,out] buffer Binary buffer to read rom data into.
 * @param[in,out] size Size of rom in bytes.
 * @return 0 (@p CHIP8_EOK) for success or @p chip8_error code for failure.
 */
chip8_error chip8_readrom(const char *path, uint8_t **buffer, size_t *size);

#endif /* CHIP8_UTILS_H */
