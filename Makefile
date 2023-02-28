# SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

include config.mk

# Core emulation source code...
CORE_SRCS = src/utils/error.c \
	    src/core/cpu.c
CORE_OBJS = $(CORE_SRCS:.c=.o)

# Binary source code...
BIN_SRCS  = $(CORE_SRCS) \
	    src/main.c
BIN_OBJS  = $(BIN_SRCS:.c=.o)

# Unit test source code...
TEST_SRCS = test/test_error.c \
	    test/test_cpu.c
TAP = test/tap.c
TEST_BINS = $(TEST_SRCS:.c=)

# Default target...
all: options chip-8

# State build options...
options:
	@printf "Compiler options for chip-8 $(VERSION):\n"
	@printf "CFLAGS  = $(CFLAGS)\n"
	@printf "LDFLAGS = $(LDFLAGS)\n"
	@printf "CC      = $(CC)\n\n"
	@printf "Compiler output:\n"

# Build chip-8 binary...
chip-8: $(BIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Execute unit tests...
test: options $(CORE_OBJS) $(TEST_BINS)
	@printf "\nTest output:\n"
	./test/test_error
	./test/test_cpu

# Generate test executables...
.c:
	$(CC) $(CFLAGS) $(TAP) $< $(CORE_OBJS) -o $@ $(LDFLAGS)

# Generate object files...
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# Installation targets...
install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f chip-8 $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/chip-8

uninstall:
	rm -fv $(DESTDIR)$(PREFIX)/bin/chip-8

# Clean up...
clean:
	rm -rfv src/*.o src/utils/*.o src/core/*.o $(TEST_BINS) chip-8

# Avoid name conflicts...
.PHONEY: all clean install uninstall options chip-8
