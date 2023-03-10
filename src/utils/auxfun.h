/**
 * SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 *
 * @file auxfun.h
 */

#ifndef CHIP8_UTILS_H
#define CHIP8_UTILS_H

#include <stdint.h>

#include "utils/error.h"

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
