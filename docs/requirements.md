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

<https://chip-8.github.io/links/>

## 2 General Description of Product

The Chip-8 project's goal is to implement the CPU architecture, video system,
and audio system of the Chip-8 system. The goal is to give the user as close
of an experience to the original Chip-8 through software. This requires
accurate emulation with correct CPU timings to make this possible.

### 2.2 Domain Model with Description

![Domain Model][model-img]

The above image is the Chip-8 project's domain model. There are five simple
components that make up the application: CPU, Video, Keyboard, Audio, and UI.
The dotted line indicates that the CPU, Video, Keyboard, and Audio components
are apart of the application's backend. The UI is considered the frontend.
The purpose of this is to decouple the core emulator from the UI to allow
future updates or iterations of the project to more easily add their own
user interfaces without having to modify the backend.

The CPU is the core component that allows the emulator to function. It is
responsible for processing all data given from the Video, Audio, and Keyboard
components. The CPU also sends out data to the Video and Audio components to
either be rendered, or outputted through PCM. The CPU will also be responsible
for correct timing in the system.

The Keyboard component is the simplest since all it does is give the CPU user
input to process from the keyboard.

The Video component is responsible for correctly rendering any pixel data
the CPU gave it into a 64x64 two pixel (traditionally black and white) screen.

The Audio component performs PCM processing and outputs any sound data given
to it by the CPU.

Finally, the UI (User Interface) component bundles all video data from the
Video component and audio data from the Audio component into a common
interface that the user is meant to interact with. This UI can be a simple
command-line interface or a graphical user interface. For now, the Chip-8
project will focus on a command-line interface to reduce workload.

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

F.4.1.2. Implement keyboard interface as described above.

### 4.2 Performance Requirements

The Chip-8 emulator needs to accurately implement CPU instructions with
correct timings. The Chip-8 system calculates and renders video and audio
at 60 frames per second.

F.4.2.1 All CPU instructions are implemented correctly at 60FPS.

F.4.2.2 All video rendering occurs correctly.

F.4.2.3 All audio output occurs correctly.

### 4.3 Design Constraints

The Chip-8 project aims to have its core emulation capabilities be
decoupled from its user interface. This will allow future updates or iterations
of the project to implement their own user interfaces without needing to
modify the core capabilities of the project.

F.4.3.1 Project must be written in pure C99 without extensions.

F.4.3.2 Projects emulator core must be decoupled from its user interface.

### 4.4 Quality Requirements

The Chip-8 project's quality is determined by how accurately it can decode
and interpret original Chip-8 CPU instructions. All video, audio, and CPU
instruction handling must be done between 60FPS. A special ROM testing suite
will be used in the regular testing suite to ensure this quality.

F.4.4.1 Implement the CPU, audio, and video systems of the Chip-8 correctly.

F.4.4.2 Integrate standard ROM testing suites into unit testing framework.

### 4.5 Other Requirements

The Chip-8 project cannot have any segmentation faults, memory leaks, or
any other pieces of insecure code.

F.4.4.1 No segmentation faults.

F.4.4.2 No memory leaks.

F.4.4.3 No insecure code.

## 5 Appendices

Chip-8 techincal reference:

<https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Technical-Reference>

[stories]: https://github.com/awkless/chip-8/blob/main/docs/userstories.md
[model-img]: {{site.baseurl}}/res/DomainModel.png
