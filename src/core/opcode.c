#include "core/opcode.h"
#include "core/cpu.h"
#include "core/video.h"
#include "core/keypad.h"
#include "utils/auxfun.h"

void chip8_opcode_00E0(chip8_cpu *cpu)
{
	chip8_video_clear(cpu->video);
	chip8_debug("opcode 0E00");
}

void chip8_opcode_00EE(chip8_cpu *cpu)
{
	cpu->sp--;
	cpu->pc = cpu->stack[cpu->sp];
	chip8_debug("opcode 00EE");
}

void chip8_opcode_1NNN(chip8_cpu *cpu)
{
	uint16_t nnn = cpu->opcode & 0x0FFF;
	cpu->pc = nnn;
	chip8_debugx("opcode 1NNN - %04X\n", cpu->opcode);
}

void chip8_opcode_2NNN(chip8_cpu *cpu)
{
	uint16_t nnn = cpu->opcode & 0x0FFF;
	cpu->stack[cpu->sp] = cpu->pc;
	cpu->sp++;
	cpu->pc = nnn;
	chip8_debug("opcode 2NNN");
}

void chip8_opcode_6XNN(chip8_cpu *cpu)
{
	uint8_t x = (cpu->opcode & 0x0F00) >> 8;
	uint8_t nn = cpu->opcode & 0x00FF;
	cpu->v[x] = nn;
	chip8_debugx("opcode 6XNN - %04X\n", cpu->opcode);
}

void chip8_opcode_7XNN(chip8_cpu *cpu)
{
	uint8_t x = (cpu->opcode & 0x0F00) >> 8;
	uint8_t nn = cpu->opcode & 0x00FF;
	cpu->v[x] += nn;
	chip8_debugx("opcode 7XNN - %04X\n", cpu->opcode);
}

void chip8_opcode_ANNN(chip8_cpu *cpu)
{
	uint16_t nnn = cpu->opcode & 0x0FFF;
	cpu->i = nnn;
	chip8_debugx("opcode ANNN - %04X\n", cpu->opcode);
}


void chip8_opcode_CXNN(chip8_cpu *cpu)
{
	uint8_t x = (cpu->opcode & 0x0F00) >> 8;
	uint8_t nn = cpu->opcode & 0x00FF;
	uint8_t r = rand() % 256;

	cpu->v[x] = r & nn;
	chip8_debug("opcode CXNN");
}

void chip8_opcode_DXYN(chip8_cpu *cpu)
{
	uint8_t x = (cpu->opcode & 0x0F00) >> 8;
	uint8_t y = (cpu->opcode & 0x00F0) >> 4;
	uint8_t n = cpu->opcode & 0x000F;
	uint8_t xpos = cpu->v[x];
	uint8_t ypos = cpu->v[y];
	uint8_t pixel = 0;

	cpu->v[0xF] = 0;
	for (int col = 0; col < n; col++) {
		pixel = cpu->memory[cpu->i + col];
		for (int row = 0; row < 8; row++) {
			if ((pixel & (0x80 >> row)) != 0) {
				if (cpu->video->pixels[ypos + col][xpos + row] == 1)
					cpu->v[0xF] = 1;
				cpu->video->pixels[ypos + col][xpos + row] ^= 1;
			}
		}
	}
	chip8_debugx("opcode DXYN - %04X, X=%d, Y=%d\n", cpu->opcode, cpu->v[x], cpu->v[y]);
}

void chip8_opcode_EX9E(chip8_cpu *cpu)
{
	uint8_t x = (cpu->opcode & 0x0F00) >> 8;
	chip8_keypad_state state = 0;
	chip8_keypad_getkey(cpu->keypad, cpu->v[x], &state);
	if (state == CHIP8_KEY_DOWN)
		cpu->pc += 2;
	chip8_debug("opcode EX9E");
}

void chip8_opcode_EXA1(chip8_cpu *cpu)
{
	uint8_t x = (cpu->opcode & 0x0F00) >> 8;
	chip8_keypad_state state = 0;
	chip8_keypad_getkey(cpu->keypad, cpu->v[x], &state);
	if (state == CHIP8_KEY_UP)
		cpu->pc += 2;
	chip8_debug("opcode EXA1");
}

void chip8_opcode_FX0A(chip8_cpu *cpu)
{
	uint8_t x = (cpu->opcode & 0x0F00) >> 8;
	chip8_keypad_lock(cpu->keypad, &cpu->v[x]);
	chip8_debug("opcode FX0A");
}
