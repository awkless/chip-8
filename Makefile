# SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

include config.mk

# Uncomment for debug tracing...
#DEBUG = -DDEBUG_TRACE

# CHIP-8 source code...
BIN_SRCS = src/utils/error.c \
           src/utils/auxfun.c \
	   src/core/opcode.c \
	   src/core/cpu.c \
	   src/core/keypad.c \
	   src/core/video.c \
	   src/core/audio.c \
           src/main.c
BIN_OBJS = $(BIN_SRCS:.c=.o)

# Unit test source code...
TEST_SRCS  = $(BIN_SRCS:src/main.c=test/tap.c)
TEST_OBJS  = $(TEST_SRCS:.c=.o)
TEST_UNITS = test/test_error.c \
	     test/test_auxfun.c \
	     test/test_keypad.c \
	     test/test_video.c \
	     test/test_cpu.c
TEST_BINS  = $(TEST_UNITS:.c=)

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
	$(CC) $(CFLAGS) $(DEBUG) -o $@ $^ $(LDFLAGS)

# Execute unit tests...
test: options $(TEST_OBJS) $(TEST_BINS)
	@printf "\nTest output:\n"
	./test/test_error
	./test/test_auxfun
	./test/test_keypad
	./test/test_cpu
	./test/test_video

# Generate test executables...
.c:
	$(CC) $(CFLAGS) $(DEBUG) $< $(TEST_OBJS) -o $@ $(LDFLAGS)

# Generate object files...
.c.o:
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<

# Generate source code doucmentation with Doxygen...
docs: all
	doxygen docs/doxyfile

# Installation targets...
install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f chip-8 $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/chip-8

uninstall:
	@rm -fv $(DESTDIR)$(PREFIX)/bin/chip-8

# Clean up...
clean:
	@rm -rfv docs/doxygen src/*.o src/core/*.o src/utils/*.o \
	         test/*.o $(TEST_BINS) chip-8

# Avoid name conflicts...
.PHONEY: all clean install uninstall options chip-8
