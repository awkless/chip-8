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
