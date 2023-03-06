/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef CHIP8_UTILS_H
#define CHIP8_UTILS_H

#include <stdint.h>

#include "utils/error.h"

/**
 * @brief Helper macro to calculate array sizes.
 *
 * @pre @arr must be an actual array type, and NOT A POINTER TYPE!
 *
 * @param[in] arr Array to calculate size of.
 * @return Size of array in bytes.
 */
#define chip8_arrsize(arr) ((sizeof arr) / (sizeof *arr))

#endif /* CHIP8_UTILS_H */
