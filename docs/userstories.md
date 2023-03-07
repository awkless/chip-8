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
