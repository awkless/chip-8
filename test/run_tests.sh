#!/bin/sh
# SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT
#
# Simple shell script designed to run all test executables in this directory.

find ./ -type f -name 'test_*' -executable -exec sh -c 'exec "$1"' _ {} \;
