<!--
SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
SPDX-License-Identifier: MIT
-->

# Requirements Specification for Chip-8

## 1. Introduction

### 1.1 Purpose of Product

The Chip-8 emulation project aims to properly emulate the Chip-8 architecture
from the 1970's so that the user can run original ROMs from the system on
their machine without needing the original hardware.

### 1.2 Scope of Product

The Chip-8 project focuses on implementing the original Chip-8 system
without any extensions. Chip-8 has existed for a long time and has many
variations and extentions like SUPER CHIP-8. However, to keep things simple
this project just aims to implement the original architecture from the 1970s.

### 1.3 Acronyms, Abbreviations, Definitions

- CPU: centeral processing unit.
- Emulator: software that allows you to execute programs meant for
  different computer architectures.
- Register: fastest unit of memory in a CPU, typically the same size as the data
  bus or address bus.
- Register File: A collection of registers that the CPU can use per instruction.
- Instruction Cycle: The steps the CPU takes to process an instruction.

### 1.4 References

This simple website contains all references used throughout the project.

\<<https://chip-8.github.io/links/>\>

## 2 General Description of Product

The Chip-8 project's goal is to implement the CPU architecture, video system,
and audio system of the Chip-8 system. The goal is to give the user as close
of an experience to the original Chip-8 through software. This requires
accurate emulation with correct CPU timings to make this possible.

### 2.2 Domain Model with Description

TODO

### 2.3 Product Functions (General)

The general functions of the Chip-8 project boils down to accurate CPU, video,
and audio emulation such that the user can load up a Chip-8 video game ROM
file and play said ROM through usage of their keyboard.

### 2.4 User Characteristics and Expectations

The user will have the ability to load a Chip-8 video game ROM file and
interact with said ROM file through their keyboard as if they were using the
original keypad layout the Chip-8 had in the 1970s.

### 2.5 Constraints

The Chip-8 project will only be available on Unix-like distributions, and
will only emluate the original Chip-8 system. This means that the basic
Chip-8 features will be provided without any extensions like the ones found
in the SUPER CHIP-8 system.

### 2.6 Assumptions and Dependencies

The Chip-8 project requires that the user have the following software
packages and libraries to be able to build and install:

- SDL2 library.
- Standard C compiler like GCC or any equivalent.
- Git version control system.
- Make program like GNU Make or any equivalent.

## 3 Functional Requirements

These are the functional requirements of the project. You can view
the [user stories page][stories] for progression notes.

1. Implement the Chip 8 CPU
    1. Setup general purpose register file.
    1. Implement timer registers.
    1. Setup fetch, decode, execute cycle.
    1. Implement the `0NNN` instruction.
    1. Implement the `00E0` instruction.
    1. Implement the `00EE` instruction.
    1. Implement the `1NNN` instruction.
    1. Implement the `3XNN` instruction.
    1. Implement the `4XNN` instruction.
    1. Implement the `5XY0` instruction.
    1. Implement the `6XNN` instruction.
    1. Implement the `7XNN` instruction.
    1. Implement the `8XY0` instruction.
    1. Implement the `8XY1` instruction.
    1. Implement the `8XY2` instruction.
    1. Implement the `8XY3` instruction.
    1. Implement the `8XY4` instruction.
    1. Implement the `8XY5` instruction.
    1. Implement the `8XY7` instruction.
    1. Implement the `8XYE` instruction.
    1. Implement the `9XY0` instruction.
    1. Implement the `ANNN` instruction.
    1. Implement the `BNNN` instruction.
    1. Implement the `CXNN` instruction.
    1. Implement the `DXYN` instruction.
    1. Implement the `EX9E` instruction.
    1. Implement the `EXA1` instruction.
    1. Implement the `FX07` instruction.
    1. Implement the `FX0A` instruction.
    1. Implement the `FX15` instruction.
    1. Implement the `FX18` instruction.
    1. Implement the `FX1E` instruction.
    1. Implement the `FX29` instruction.
    1. Implement the `FX33` instruction.
    1. Implement the `FX55` instruction.
    1. Implement the `FX65` instruction.
1. Implement video system.
    1. Sync video drawing with timer registers.
    1. Implement the two color 64x64 display.
1. Implement audio system.
    1. Implement PCM audio emulation.
    1. Sync audio with timer registers.
1. Create user interface.
    1. Setup CLI user interface.

## 4 System and Non-Functional Requirements

### 4.1 External Interface Requirements

The Chip-8 project will only have a simple command line interface that
utilizes POSIX-style option formatting. The user is meant to interact with
loaded video games through their keyboard with the following layout:

```
1 2 3 4
Q W E R
A S D F
Z X C V
```

which map to these traditional Chip-8 keys:

```
1 2 3 C
4 5 6 D
7 8 9 E
A 0 B F
```

NF.4.1.1. Implement CLI interface with POSIX-style options.
NF.4.1.2. Implement keyboard interface as described above.

### 4.2 Performance Requirements

The Chip-8 emulator needs to accurately implement CPU instructions with
correct timings. The Chip-8 system calculates and renders video and audio
at 60 frames per second.

NF.4.2.1 All CPU instructions are implemented correctly at 60FPS.
NF.4.2.2 All video rendering occurs at 60FPS.
NF.4.2.3 All audio output occurs at 60FPS.

### 4.3 Design Constraints

The Chip-8 project aims to have its core emulation capabilities be
decoupled from its user interface. This will allow future updates or iterations
of the project to implement their own user interfaces without needing to
modify the core capabilities of the project.

NF.4.3.1 Project must be written in pure C99 without extensions.
NF.4.3.2 Projects emulator core must be decoupled from its user interface.

### 4.4 Quality Requirements

TODO

### 4.5 Other Requirements

TODO

## 5 Appendices

TODO
