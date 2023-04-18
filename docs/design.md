<!--
SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
SPDX-License-Identifier: MIT
-->

# Design Document

## Architecture

![Domain Model][model-img]

Backend is the core emulator. Frontend is the UI the user uses to interface
with the emulator. The video, keyboard, and audio drivers pass data to and
from the CPU driver to be process and presented in the UI.

The CPU processes current ROM data under the internal timer that controls how
fast an instruction cycle occurs per second. The CHIP-8 specification does not
provide any information about instruction timing other than what was used to
implement the CHIP-8 on older systems. We decided to go with a simple timing
system that places all instructions on the same frequency such that we can
control emulation based on instructions per second in a fixed amount of time
rather than a variable amount of time. This keeps the implementation very
simple.

## Code Structure

The CHIP-8 coding project is written in C. Thus, there are no classes, but
rather routines and pointers to structures that make up the entire
interface and structure of the project.

> __NOTE__: All API routines are properly documented via Doxygen comments in the
> respective header files.

### Init and Free Routines

All drivers presented here follow a simple C design principle of allocation
and then freeing. Thus, before a driver can be used a corresponding
initialization function must be used to allocate proper resources for that
driver. Once the driver is done processing, then the corresponding free
function must be used to deallocate all resources used by the driver.
Failure to abide by this design will result in segmentation faults and
memory leaks.

Example:

```
/* Resources for keypad... */
chip8_error flag = CHIP8_EOK;
chip8_keypad *keys = NULL;

/* Setup keypad system */
flag = chip8_keypad_init(&keys);
if (flag != CHIP8_EOK)
        chip8_die(flag);

/* Do stuff with keypad... */

/* Free keypad... */
chip8_keypad_free(keys);
```

The above showcases how the init and free design is done. Even though the
example shows how to use the keypad driver of the emulator, the design is the
same for every other driver in the codebase.

### Exposed API Stuctures

This project exposes all structures for any interface to make testing easier.
Normally in C API's an opaque pointer is used to hide the details of a given
structure pointer like so:

```
/* In .h file */
typedef struct cpu_instance *cpu_handle;

/* Use the handle */
cpu_handle create_cpu();

/* In .c file */

/* Define handle */
struct cpu_instance {
    int opcode;
    /* other members here... */
}
```

This prevents anyone from change the members of a structure directly, thus the
following would cause an compile-time error:

```
cpu_handle->opcode = 0xDEADBEEF;
```

This forces people to use an API specific routine to perform such an action like
so:

```
modify_opcode(0xDEADBEEF);
```

However, this project does not use this design principle. The testing framwork
this project uses (aka libtap) is super minimal such that there is no way to
perform mocking. Thus, performing unit tests with an opaque pointer can get
really complicated. It is far easier to just set needed values directly for a
test rather than indirectly. Thus, the entire CHIP-8 emulation API assumes
that the programmer will not modify any structures directly, i.e., assume good
faith and competence.

Obviously, this can lead to some issues, but so far everything works :)

### Error System

Since C does not come with a standard error system like exceptions in Java and
C++, we needed to utilize a simple flagging system called `chip8_error`. Most
functions in the codebase follow this design:

```
chip8_error chip8_sometask(int params);
```

In otherwords, most functions return an error code such that 0 means success and
non-zero means failure. We can then output a helpful error message to the user
via `chip8_die(chip8_error code)`. Of course, this means that any call to a
CHIP-8 emulation routine needs its return value to be checked, otherwise
undefined behavior may result during runtime.

All error codes and routines are defined in `src/utils/error.h`. Some helpful
auxiliary routines are provided via `src/utils/auxfun.h`.

### Keypad System

This project converts user keyboard input into valid CHIP-8 keypad input via
`src/core/keypad.h`. This header file provides a standard interface for the CPU
to obtain user input. A standard keypad comes with a `chip8_keypad` structure
to be passed around in the keypad interface during execution. Here is how
chip8_keypad is setup.

```
#define CHIP8_KEYPAD_SIZE 16 /**< Amount of keys in CHIP-8 keypad. */

typedef enum {
	CHIP8_KEY_DOWN = 1, /**< Key is pressed. */
	CHIP8_KEY_UP = 0    /**< Key is unpressed. */
} chip8_keypad_state;

typedef struct {
	uint8_t keys[CHIP8_KEYPAD_SIZE]; /**< Keys of keypad. */
	uint8_t *states;                 /**< Scan code state. */
} chip8_keypad;
```

The `chip8_keypad->keys` member houses the current keypad being operated on,
while `chip8_keypad->states` keeps track of what SDL scan code is being
detected from the user's keyboard. There are also `chip8_keypad_state` enum
to keep track of what kind of key press is being used by the user.

### Video System

The project process video data via `src/core/video.h`. This header file
provides all the routines to process and convert CHIP-8 pixel data to valid
SDL2 texture rendering data on to the current window. A standard video object
comes with `chip8_video` structure to be passed around the video interface
during execution. Here is how `chip8_video` is structured:

```
#define CHIP8_VIDEO_WIDTH 64  /**< Maximum CHIP-8 screen width. */
#define CHIP8_VIDEO_HEIGHT 32 /**< Maximum CHIP-8 screen hieght. */

/**
 * @brief CHIP-8 video information.
 */
typedef struct {
	SDL_Window *window;     /**< SDL window pointer. */
	SDL_Renderer *renderer; /**< SDL renderer pointer. */
	SDL_Texture *texture;   /**< SDL texture pointer. */

	/** Screen pixel data. */
	uint8_t pixels[CHIP8_VIDEO_HEIGHT][CHIP8_VIDEO_WIDTH];

	/** Texture buffer data. */
	uint32_t buffer[CHIP8_VIDEO_WIDTH * CHIP8_VIDEO_HEIGHT];
} chip8_video;
```

`chip8_video->window` is a standard SDL2 window object such that all pixel data
is rendered to this member according to the SDL2 library.
`chip8_video->renderer` is a standard SDL2 render object such that all pixel
data must be passed through this member to be rendered to `chip8_video->window`.
`chip8_video->texture` is a standard SDL2 texture object such that all pixel
data that must be rendered is plotted out before being passed to
`chip8_video->renderer`.

The `chip8_video->pixels` member represents the actual pixel data that must
be processed by the CPU and rendered by the video API. Finally, the
`chip8_video->buffer` member represents the RGBA pixel data of the
`chip8_video->pixels` member to be sent to the `chip8_video->texture`
member for rendering.

### The CPU

The CPU driver is the most complicated driver in the entire project. Firstly,
two files comprise the entire CPU design: `src/core/cpu.h` and
`src/core/opcode.h`.

The `src/core/cpu.h` file houses the standard interface for the CPU, which
houses the `chip8_cpu` structure. The `chip8_cpu` structure brings together all
the drivers of the codebase to perform proper execution of the instruction set.
Here is the design of the `chip8_cpu` structure:

```
#define CHIP8_RAM_SIZE   0x1000 /**< Size of CHIP-8 RAM. */
#define CHIP8_STACK_SIZE 12     /**< Size of CHIP-8 stack. */
#define CHIP8_ROM_INIT   0x200  /**< Start of code segement in CHIP-8. */
#define CHIP8_ROM_LIMIT  0xFFF  /**< End of code segement in CHIP-8. */
#define CHIP8_VREGS      16     /**< Amount of registers in CHIP-8. */

/**
 * @brief Representation of CHIP-8 cpu.
 */
typedef struct {
	uint8_t memory[CHIP8_RAM_SIZE];   /**< 4KiB memory space. */
	uint8_t v[CHIP8_VREGS];           /**< 16 8-bit data registers. */
	uint8_t dt;                       /**< 8-bit delay timer. */
	uint8_t st;                       /**< 8-bit sound timer. */
	uint16_t stack[CHIP8_STACK_SIZE]; /**< 8-bit stack */
	uint16_t sp;                      /**< 8-bit stack pointer. */
	uint16_t i;                       /**< 8-bit index register. */
	uint16_t pc;                      /**< 8-bit program counter. */
	uint16_t opcode;                  /**< 16-bit current opcode. */
	chip8_video *video;               /**< Video context. */
	chip8_keypad *keypad;             /**< Keypad context. */
	uint64_t ticks;                   /**< Current total tick rate. */
	float timer_ticks;                /**< Current timer tick rate. */
	float cycle_ticks;                /**< Current opcode cycle ticks. */
	float cycle_freq;                 /**< Max opcode cycle frequency. */
} chip8_cpu;
```

`chip8_cpu->memory` is a representation of the 4KiB memory space the CHIP-8
originally had. `chip8_cpu->v` represents the 16 8-bit general purpose
registers V0 through VF. `chip8_cpu->dt` and `chip8_cpu->st` are the
delay timer and sound timer registers used for counting/timing, and sound
generation in a CHIP-8 program. `chip8_cpu->stack` and `chip8_cpu->sp`
represents the CHIP-8 stack and stack pointer for subroutines. `chip8_cpu->i` is
the representation of the index register. `chip8_cpu->pc` is the representation
of the program counter. `chip8_cpu->opcode` houses the current opcode being
processed from `chip8_cpu->memory`. Finally, `chip8_cpu->ticks`,
`chip8_cpu->timer_ticks`, `chip8_cpu->cycle_ticks`, and `chip8_cpu->cycle_freq`
are all used by the in-built timing system of the CPU to make sure that
instruction decoding and execution occurs a specific rate per second.

The `chip8_video` and `chip8_keypad` drivers are also included so the
`chip8_cpu` can process video and keyboard input for the instructions that
require them.

Finally, the entire CHIP-8 CPU performs instruction decoding via a massive
switch case table. The compiler will optimize this switch table into a big
lookup table in assebly by default. The opcodes are executed by the routines
defined in `src/core/opcode.h`, which exists to help in making the switch
table more readable and maintainable in the long run.

Obviously, this implementation of the CPU is not the most pretty, but it makes
development a whole lot easier and managable.

[model-img]: {{site.baseurl}}/res/DomainModel.png
