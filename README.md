<!--
SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
SPDX-License-Identifier: MIT
-->

# Chip-8 Emulator

This is yet another [Chip-8][chip-8-wiki] emulator project aimed at emulating
the baseline features of the Chip-8 system from 1977. This project does not
aim to be the fastest, nor the most accurate. Instead, the goal was to
create a simple emulator both in design and maintenance.

## Usage

Perform the following in the terminal:

```
# chip-8 <rom>
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

## Installation

TODO

## Contribution

TODO

## License

This project uses the [MIT license][mit] for all source code and documentation.

[mit]: https://github.com/awkless/dotfiles/blob/main/LICENSE/MIT.txt
