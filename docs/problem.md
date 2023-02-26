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

TODO

## 3 Functional Requirements

TODO

## 4 System and Non-Functional Requirements

TODO

### 4.1 External Interface Requirements

TODO

### 4.2 Performance Requirements

TODO

### 4.3 Design Constraints

TODO

### 4.4 Quality Requirements

TODO

### 4.5 Other Requirements

TODO

## 5 Appendices

TODO
