/* SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef CHIP8_OPCODE_H
#define CHIP8_OPCODE_H

#include "core/cpu.h"

/**
 * @brief Clear the screen.
 *
 * @pre cpu must not be NULL.
 * @post Screen will be cleared fully.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_00E0(chip8_cpu *cpu);

/**
 * @brief Return from subroutine.
 *
 * @pre cpu must not be NULL.
 * @post PC will be loaded with popped value from stack.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_00EE(chip8_cpu *cpu);

/**
 * @brief Jump to address NNN.
 *
 * @pre cpu must not be NULL.
 * @post PC will be loaded with immediate value NNN.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_1NNN(chip8_cpu *cpu);

/**
 * @brief Execute subroutine starting at address NNN.
 *
 * @pre cpu must not be NULL.
 * @post PC will be pushed onto stack before jumping to address NNN.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_2NNN(chip8_cpu *cpu);

/**
 * @brief Skip next instruction if VX == NN.
 *
 * @pre cpu must not be NULL.
 * @post PC += 2 if VX == NN.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_3XNN(chip8_cpu *cpu);

/**
 * @brief Skip next instruction if VX != NN.
 *
 * @pre cpu must not be NULL.
 * @post PC += 2 if VX != NN.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_4XNN(chip8_cpu *cpu);

/**
 * @brief Skip next instruction if VX == VY.
 *
 * @pre cpu must not be NULL.
 * @post PC += 2 if VX == VY.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_5XY0(chip8_cpu *cpu);

/**
 * @brief Load NN into VX.
 *
 * @pre cpu must not be NULL.
 * @post VX = NN.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_6XNN(chip8_cpu *cpu);

/**
 * @brief Add NN to VX.
 *
 * @pre cpu must not be NULL.
 * @post VX = VX + NN.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_7XNN(chip8_cpu *cpu);

/**
 * @brief Store VY into VX.
 *
 * @pre cpu must not be NULL.
 * @post VX = VY.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_8XY0(chip8_cpu *cpu);

/**
 * @brief Logical OR VX with VY.
 *
 * @pre cpu must not be NULL.
 * @post VX = VX | VY.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_8XY1(chip8_cpu *cpu);

/**
 * @brief Logical AND VX with VY.
 *
 * @pre cpu must not be NULL.
 * @post VX = VX & VY.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_8XY2(chip8_cpu *cpu);

/**
 * @brief Logical XOR VX with VY.
 *
 * @pre cpu must not be NULL.
 * @post VX = VX ^ VY.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_8XY3(chip8_cpu *cpu);

/**
 * @brief Add VY to VX.
 *
 * @note Set VF to 1 if carry occurs, otherwise 0.
 *
 * @pre cpu must not be NULL.
 * @post VX = VX + VY and VF = 1 if carry occurs.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_8XY4(chip8_cpu *cpu);

/**
 * @brief Subtract VY from VX.
 *
 * @note Set VF to 1 if borrow occurs, otherwise 0.
 *
 * @pre cpu must not be NULL.
 * @post VX = VX - VY and VF = 1 if borrow occurs.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_8XY5(chip8_cpu *cpu);

/**
 * @brief Store right shifted VY into VX.
 *
 * @note Set VF to least significant bit prior to the shift.
 * @note VY is left unchanged.
 *
 * @pre cpu must not be NULL.
 * @post VX = VY >> 1 and VF = lsb prior to shift.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_8XY6(chip8_cpu *cpu);

/**
 * @brief Set VX to the value of VY minus VX.
 *
 * @note Set VF to 1 if borrow does not occur.
 *
 * @pre cpu must not be NULL.
 * @post VX = VY - VX and VF = 1 if borrow does not occur.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_8XY7(chip8_cpu *cpu);

/**
 * @brief Store left shifted VY into VX.
 *
 * @note Set VF to most significant bit prior to the shift.
 * @note VY is left unchanged.
 *
 * @pre cpu must not be NULL.
 * @post VX = VY << 1 and VF = msb prior to shift.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_8XYE(chip8_cpu *cpu);

/**
 * @brief Skip next instruction if VX != VY.
 *
 * @pre cpu must not be NULL.
 * @post PC += 2 if VX != VY.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_9XY0(chip8_cpu *cpu);

/**
 * @brief Store address NNN in I.
 *
 * @pre cpu must not be NULL.
 * @post I = NNN.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_ANNN(chip8_cpu *cpu);

/**
 * @brief Jump to address NNN + V0
 *
 * @pre cpu must not be NULL.
 * @post PC = NNN + V0.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_BNNN(chip8_cpu *cpu);

/**
 * @brief Store random number with mask of NN in VX.
 *
 * @pre cpu must not be NULL.
 * @post VX = rand() & NN.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_CXNN(chip8_cpu *cpu);

/**
 * @brief Draw sprite at position VX, VY with N bytes of sprite data starting
 *        at the address stored in I.
 *
 * @pre cpu must not be NULL.
 * @post Draw N + I sprite at position VX, VY.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_DXYN(chip8_cpu *cpu);

/**
 * @brief Skip next instruction if current key value == VX.
 *
 * @pre cpu must not be NULL.
 * @post PC += 2 if VX == Key vaule.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_EX9E(chip8_cpu *cpu);

/**
 * @brief Skip next instruction if current key value != VX.
 *
 * @pre cpu must not be NULL.
 * @post PC += 2 if VX != Key vaule.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_EXA1(chip8_cpu *cpu);

/**
 * @brief Store current value of delay timer in VX.
 *
 * @pre cpu must not be NULL.
 * @post VX = delay timer.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_FX07(chip8_cpu *cpu);

/**
 * @brief Wait for key press and store the key value in VX.
 *
 * @pre cpu must not be NULL.
 * @post Wait for keypress then VX = key value.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_FX0A(chip8_cpu *cpu);

/**
 * @brief Set delay timer to the value of register VX.
 *
 * @pre cpu must not be NULL.
 * @post Delay timer = VX.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_FX15(chip8_cpu *cpu);

/**
 * @brief Set sound timer to the value of register VX.
 *
 * @pre cpu must not be NULL.
 * @post Sound timer = VX
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_FX18(chip8_cpu *cpu);

/**
 * @brief Add VX to I.
 *
 * @pre cpu must not be NULL.
 * @post I = I + VX.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_FX1E(chip8_cpu *cpu);

/**
 * @brief Set I to the memory address of sprite data corresponding to the
 *        hex digit in VX.
 *
 * @pre cpu must not be NULL.
 * @post I = VX * 0x5.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_FX29(chip8_cpu *cpu);

/**
 * @brief Store the BCD of VX in I, I + 1, and I + 2.
 *
 * @pre cpu must not be NULL.
 * @post BCD of VX in I, I + 1, and I + 2.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_FX33(chip8_cpu *cpu);

/**
 * @brief Store the values of V0 to VX inclusive in memory starting at I.
 *
 * @pre cpu must not be NULL.
 * @post V0...VX in I.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_FX55(chip8_cpu *cpu);

/**
 * @brief Fill V0 to VX inclusive with values stored at memory starting at I.
 *
 * @note I is set to I + X + 1.
 *
 * @pre cpu must not be NULL.
 * @post V0...VX from I.
 *
 * @param[in,out] cpu CHIP-8 cpu context to process.
 */
void chip8_opcode_FX65(chip8_cpu *cpu);

#endif /* CHIP8_OPCODE_H */
