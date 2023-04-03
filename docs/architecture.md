<!--
SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
SPDX-License-Identifier: MIT
-->

# Architecture

## Project Overview

Implementation of a CHIP-8 emulator. CHIP-8 is an 8-bit virtual machine
architecture created in the mid-1970s by Joseph Weisbecker. Our project
focuses on implementing the original instruction set in C using the
SDL2 library for video and sound support.

## Key Architectural Drivers

- Keyboard/keypad driver for user input.
- Video driver to process and display pixel data.
- Audio driver to provide PCM sound.
- CPU driver to fetch, decode, and execute CHIP-8 opcodes that utilize
the keyboard, video, or audio drivers.

## Architecture Design

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

## Opcode Decoder Choices

There are two main ways to perform opcode dispatching/decoding: Table/Switch
case decoding, and algorithmic decoding.

Switch case decoding is easy to implement and debug. All you need to do is
compare the correct bits and perform the operation in one massive switch case
statement. However, this style requires a lot of code repetition as most the
CHIP-8 instruction set performs a number of the same operations.

Algorithmic decoding is harder to implement and debug. You must design an
algorithm that can properly perform the decoding based on a pattern of common
bits in any given instruction. The CHIP-8 lends itself nicely to an algorithmic
decoder given that all instructions are fixed width and come in 3 basic formats:
CNNN, CXNN, and CXYN. Each letter is a nibble in size and represent the
following:

- C = opcode category.
- N = immediate nibble.
- NN = immediate byte.
- NNN = immediate 12-bit number.
- X = Destination and operand register.
- Y = Operand register.

As you can see, designing an algorithm for the CHIP-8 decoder would be possible
but hard given all the different bit combinations an instruction can have.

If you read our code, then you will see we went with the giant switch case
decoder. This was the easiest and most maintainable method of implementing the
CHIP-8 instruction set.

[model-img]: {{site.baseurl}}/res/DomainModel.png
