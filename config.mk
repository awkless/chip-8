# SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

# chip-8 version...
VERSION = 0.2.0

# Paths...
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# Libraries and includes...
LIBS = -lSDL2
INCS = -I/usr/include/SDL2 -Isrc/

# Flags...
CPPFLAGS = -D_DEFAULT_SOURCE \
	   -D_BSD_SOURCE \
	   -D_POSIX_C_SOURCE=200809L \
	   -D_REENTRANT \
	   -DVERSION=\"$(VERSION)\"
CFLAGS   = -std=c99 \
	   -pedantic \
	   -Wall \
	   -g \
	   -Os \
	   $(INCS) \
	   $(CPPFLAGS)
LDFLAGS  = $(LIBS)

# Compiler and linker...
CC = cc
