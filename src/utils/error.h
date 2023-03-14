/**
 * SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 *
 * @file error.h
 */

#ifndef CHIP8_UTILS_ERROR_H
#define CHIP8_UTILS_ERROR_H

/**
 * @brief Enumeration representing standard application error codes.
 */
typedef enum {
	CHIP8_EOK = 0,  /**< No errors. */
	CHIP8_EINVAL,   /**< Invalid argument. */
	CHIP8_ENOMEM,   /**< No memory. */
	CHIP8_ENOFILE,  /**< No such file exists. */
	CHIP8_EBIGFILE, /**< File is to big to load. */
	CHIP8_EBADOP,   /**< CPU encounted bad opcode. */
	CHIP8_ESDL,     /**< SDL library failure. */
	CHIP8_ECOUNT	/**< Error code count INTERAL USE ONLY!. */
} chip8_error;

/**
 * @brief Print error message from error code and exit with status.
 *
 * @pre @code must be a valid error code.
 * @post Application will print message and die (exit with error code as
 *       status).
 *
 * @param[in] code Error code to obtain error message from.
 */
void chip8_die(chip8_error code);

#endif /* CHIP8_UTILS_ERROR_H */
