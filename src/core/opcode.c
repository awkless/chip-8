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
