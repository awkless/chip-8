# SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

# chip-8 version...
VERSION = 0.0.0

# Paths...
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# Libraries and includes...
LIBS = -lSDL2
INCS = -Iinclude/

# Flags...
CPPFLAGS = -D_DEFAULT_SOURCE \
	   -D_BSD_SOURCE \
	   -D_POSIX_C_SOURCE=200809L \
	   -DVERSION=\"$(VERSION)\"
CFLAGS   = -std=c99 \
	   -pedantic \
	   -Wall \
	   -Os \
	   $(INCS) \
	   $(CPPFLAGS)
LDFLAGS  = $(LIBS)

# Compiler and linker...
CC = cc
