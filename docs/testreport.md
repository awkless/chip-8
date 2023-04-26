<!--
SPDX-FileCopyrightText: 2023 Jason Pena <jasonpena@awkless.com>
SPDX-License-Identifier: MIT
-->

# Test Report

## Component Testing

Unit testing was performed using the [libtap][libtap-lib] library, which is a
simple third-party unit testing library that follows the
[Test Anything Protocol][tap]. The libtap library is very simple such that it
does not come with any mocking features for mock testing. Thus, to make testing
easier we exposed the internal structures of various emulator interfaces so we
can quickly view and modify internal variables for testing.

We split up the testing into various components of the emulator: error system
testing, keypad testing, video testing, audio testing, and CPU testing. You can
view how these tests were done in the `test/` directory of the project at the
top-level.

We chose to test basic error cases pre function in any given component such as
invalid arguments, or non-existant opcodes. Then we tested the preconditions and
the postconditions of any given function according to our documentation. The
data we chose per test was based off of the pre and post conditions provided by
out documentation.

## System Testing

We tested the entire system by using simple test ROMs like the IBM logo test ROM
to see if the emulator properly interpreted and rendered graphics. We also
employed the usage of Corax89's CHIP-8 test ROM to verify that all of our
opcodes function correctly. These test ROMs gave us feedback about what was
correctly implemented, and what was broken.

Finally, as a sanity check we ran a simple Tetris ROM to ensure that simple game
data could run on our emulator.

We used GDB as the debugger to determine were certain opcode implementations
failed in our code base according to our test results.

## Acceptance Testing

We implemented a simple CI pipeline that would run our unit testing cases
through GitHub actions. Pull requests would be rejected if this CI pipeline
failed for any test case.

Upon code review (if the CI pipeline passed) we would then send the changes
through the test ROMs described in the previous section, and see if anything
failed through the entire system.

If all tests passed (both CI pipeline and ROM tests), and the code was well
written and documented, then the pull request would be accepted an merged into
the `main` branch to be apart of the next release.

[libtap-lib]: https://github.com/zorgnax/libtap
[tap]: https://testanything.org/
