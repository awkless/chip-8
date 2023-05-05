<!--
SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
SPDX-License-Identifier: MIT
-->

# User Stories

## 1. Setup Build System

As a manager we need to setup a standard build system to perform the
following:

- Compile the chip-8 executable with target dependencies.
- Install or uninstall the chip-8 executable with a single command.
- Compile and execute all unit tests.

Constraints: We must only use Make.

Acceptance Test: Build system fulfills the requirements above.

Effort Estimation: 5 person-hours 

## 1.1. Setup Makefile

As a developer we need to setup a Makefile so that the user can compile and
install/uninstall the CHIP-8 application.

Elaboration: The CHIP-8 project will be using the standard Make utility program
to allow the user to install or uninstall the project.

Constraints: Maintain POSIX compliance

Acceptance Test: Builds sample SDL2 code in `src/main.c` with no errors.

Effort Estimation: 2 person-hours

## 1.2. Setup Unit Test Suite

As a developer we need to setup the libtap unit testing suite so we can
perform test driven development.

Elaboration: Libtap is a simple library that implements the "Test Anything
Protocol", which we will be using to confirm that all important units of
code in the code base work correctly.

Constraints: Integrate libtap sources directly into code base.

Acceptance Test: Special target `make test` can build and execute all
unit tests.

Effort Estimation: 2 person-hours

## 1.3. Setup Doxygen

As a scribe we need to setup Doxygen so that we can document the code base
through source code.

Elaboration: We can document important aspects of the API through simple yet
descriptive Doxygen-style comments, which can then be extracted by the Doxygen
tool to generate HTML (or any other format) documentation.

Constraints: Doxygen-style comments should only be used in `src/` directory.

Acceptance Test: Special target `make docs` generates correct documentation
from `src/` directory.

Effort Estimiation: 1 person-hours

# 2. Setup CPU

As a developer we need to setup the base skeleton of the CHIP-8 CPU. We need to
setup the registers, RAM, and determine the method of opcode decoding and
execution.

Constraints: Internals must match the CHIP-8 specs as closely as possible.

Acceptance Test: CPU can load and obtain a basic opcode from a ROM.

Effort Estimation: 3 person-hours

## 2.1. Opcode Timing

As a developer we need a way to make sure the CPU executes an opcode with a
specific amount of timing. The CHIP-8 specs are very obtuse about how
instruction cycle timing works, so we will go with a simple design of "How
many opcodes can the CPU process in one second?".

Constraints: We must use the SDL2 timer sub-system to get the correct timing
for instruction cycles.

Acceptance Test: The CPU clearly shows that it processes a specific number
of instruction in under one second, e.g., if CPU is set to one instruction
per second, then the CPU will only process one instruction in one second.

Effort Estimation: 4 person-hours

# 3. Keypad System

As a developer we need to setup the keypad module to allow the CPU module to
process user input from the keyboard such that the keypad module converts
keyboard input into the traditional CHIP-8 keypad.

constraints: We must use the SDL2 event API.

Acceptance test: Keypad module can process keyboard presses of target keys.

Effort Estimation: 2 person-hours

## 3.1. Keypad API

As a developer we need to determine the design of the keypad API. We need it
to be simple and easy to test. We need to following kinds of functions:

- A way to initialize the keypad system.
- A way to free the memory of the keypad system.
- A way to clear the keypad state.
- A way to make the CPU poll for input.
- A way to get and set keys in the keypad.
- A way to verify that the CPU is polling for input.

Constraints: Keypad API must use the SDL2 events sub-system.

Acceptance Test: Creation of unit tests to verify functionality of all
components of the API.

Effort Estimation: 5 person-hours

# 4. Setup Video System

As a developer we need to setup a video system in order to allow the CPU to
calculate and render pixels to the screen.

Constraints: Video system must use SDL2 video sub-system.

Acceptance Test: A window is properly opened.

Effort Estimation: 4 person-hours

## 4.1. Video API

As a developer we need to determine the API design of the video system such
that it can be easy to use and test. We need the following:

- A way to create a new video system.
- A way to free a video system from memory.
- A way to store and render pixel data.
- A way to clear pixel data when needed.

Constraints: Video system API uses SDL2 video sub-system only.

Acceptance Test: Unit test cases for each API routine that all pass.

Effort Estimation: 5 person-hours

# 5. Combine Video and Keypad System with CPU

As a manager we need to combine the video and keypad systems with the CPU
system in order to begin emulation of core opcode routines like DXYN or FX0A
for Demo 1.

Constraints: CPU can only use the video and keypad systems for pixel calculations,
pixel rendering, and user input polling and processing.

Acceptance Test: CPU can run the IBM Logo ROM where an IBM Logo is displayed
properly.

Effort Estimation: 3 person-hours

## 6. Setup CI pipeline

As a manager we need to setup a simple CI pipeline on GitHub actions to perform
automated execution of our unit testing suite. If any test fails for pull
requests, then the pull request must be rejected automatically with an error
report stating what failed.

Acceptance Test: GitHub actions runs and passes current unit tests.

Effort Estimation: 2 person-hours

## 7. Run Corax89's ROM test

As a developer we need to see if our CPU implementation performs the proper
decoding and execution of instructions as a whole. Thus, as a full system test
we need to run the Corax89 ROM for this purpose.

Acceptance Test: Corax89 ROM states that all opcodes are implemented correctly.

Effort Estimation: 1 person-hours

## 8. Implement Sound System

As a developer we need to setup the sound system. The emulator should beep when
the sound timer is equal to zero.

Acceptance Test: Emulator beeps when sound timer is not equal to zero.

Effort Estimation: 2 person-hours
