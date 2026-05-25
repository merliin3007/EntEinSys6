#include "io.h"
#include "printer.h"

#include <stdio.h>

#define for_pin(v) \
    for (uint v = 0; v < 8; ++v)

// When working with the Pololu robots in the next week, we will need knowledge of the
// C langauge. Lets freshen up your C skills a little with this task. You may program
// this task in any IDE, but we suggest you to use Visual Studio Code and install the
// C/C++ IntelliSense, debugging, and code browsing extension. Furthermore, install
// the gcc compiler on your machine so you can compile your C programs. You will need
// this for the next weeks, so you may as well make yourself comfortable with it now.
//
// Download the four files. They are a simple interface similar to what you will
// see when working with the robots. The io.h file provides an interface for IO
// pins and describes how they need to be used. We will use this interface to
// drive a (virtual) LED of our robot. The printer.h file provides an interface
// for a little display, that will show up to five lines of text. For this task,
// these five lines will then be displayed on your console. The other two files
// contain the implementations of the interfaces.
//
// # Part a (1 point)
//
// Go ahead and create a new file for your solution with a main method that
// includes both headers and play around with the functions. Create some script,
// makefile, VS Code launch configuration, or any other way to compile all files
// together into an executable using gcc. (hand in your solution on how you
// compile the program)

int main(void)
{
    struct printer *p = printer_create();
    print(p, "init pins..", 0);
    refresh(p);
    for_pin(i) {
        io_init(i);
    }

    io_set_dir(0, IO_IN);
    io_set_dir(1, IO_IN);
    io_set_dir(4, IO_OUT);

    for (size_t i = 0; i < 1000; ++i) {
        io_put(LED_PIN, io_read(0) && io_read(1));
        refresh(p);
    }

    puts("deinit pins..");
    for_pin(i) {
        io_deinit(i);
    }
}
