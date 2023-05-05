<!--
SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
SPDX-License-Identifier: MIT
-->

[![REUSE status][reuse-badge]][reuse-repo]

# Chip-8 Emulator

This is yet another [Chip-8][chip-8-wiki] emulator project aimed at emulating
the baseline features of the Chip-8 system from 1977. This project does not
aim to be the fastest, nor the most accurate. Instead, the goal was to
create a simple emulator both in design and maintenance.

## Project Site

If you want to know about the development of this project then follow this URL
\<<https://awkless.github.io/chip-8/>\>, which is a simple GitHub pages website.

## Usage

Perform the following in the terminal:

```
# chip-8 -l <rom>
```

Where `<rom>` is any proper Chip-8 ROM file that you want to play. This
emulator uses the following key layout as input:

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

When you load a ROM a new window will pop up so you can play your
Chip-8 game using the keyboard controls labeled above.

The `games` directory contains some sample CHIP-8 roms that you can play around
with in the project. If you forget how to use the emulator then just run the
following into your terminal:

```
# chip-8 -h
```

for a simple help message.

## Installation

You will need the following software:

- C99 compliant compiler.
- SDL2 library.
- Git [>= 2.20].
- Posix compliant Make.

After cloning this project, run the following commands at the top level of the
project:

```
# make
# sudo make install
```

You now have the `chip-8` program installed!

## Contribution

This project is open to the following forms of contribution:

- Bug reports
- Feature requests
- Improvements or fixes to dotfiles
- Improvements or fixes to scripts
- Improvements or fixes to CI pipeline
- Improvements or fixes to documentation

Please follow the guidelines outlined by the provided
[contribution guideline file][contributing]. Pull requests will not be accepted
if these guidelines are violated without good reason.

## License

This project uses the [MIT license][mit] for all source code and documentation.

[reuse-badge]: https://api.reuse.software/badge/github.com/fsfe/reuse-tool
[reuse-repo]: https://api.reuse.software/info/github.com/fsfe/reuse-tool
[contributing]: https://github.com/awkless/chip-8/blob/main/CONTRIBUTING.md
[chip-8-wiki]: https://en.wikipedia.org/wiki/CHIP-8
[mit]: https://github.com/awkless/chip-8/blob/main/LICENSE/MIT.txt
