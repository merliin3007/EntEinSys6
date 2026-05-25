#include "common/timing.h"
#include "io.h"
#include "printer.h"

#include <unistd.h>

// # Part b (1.5 points)
//
// Your task is to write a function that takes an offset and a period as
// parameters. It first waits offset milliseconds, and then turns the LED from
// the IO module on and off repeatedly, each after period milliseconds. You may
// use any C functions, as well as the functions defined in the IO module's io.h
// file. You may not accesses other variables or methods defined only in the
// corresponding .c file. Read the comments above the functions and fields to
// gain insight on the usage. As an example, calling the function with an offset
// of 500 and a period of 1500 will first turn the LED on after 500 ms, then
// turn it off after 2000 (500+1500) ms, turn it on again after 3500 (500 + 2 *
// 1500) ms, etc. You will notice that changing the current state of the LED
// will print to the console, if the LED is now on or off, as well as the
// current time since the LED's initialization in full seconds that this change
// occurrs.
//
// Hint: including <time.h> or <unistd.h> in your program lets you use timing in
//       your program. The function nanosleep pauses execution for a number of
//       nanoseconds usleep for a number of microseconds, so you might want to define
//       an own function msleep using that to pause execution for a number of
//       milliseconds instead.
//
// # Part c (1.5 points)
//
// Usually when you program with the robot, there is no easy way to show debug
// logs on the console, but you are restricted to a very small screen, or only
// showing debug output by toggling LEDs. We are lucky, as we have a screen to
// show outputs, whose API you can find in the printer.h file. The display can
// handle up to 5 lines of output with at most 15 characters per line (16 if you
// include the terminating null byte \0 at the end of each string). Your task is
// to write something sensible onto the display to show the user each time you
// turn the LED on or off. An example message could be "LED turns ON". Printing
// to this printer is not as convenient as using the printf function, but the
// API defines multiple functions to ultimately modify any line and character on
// the screen. Again, you are only allowed to use the functions and constants in
// the printer.h file and no further variables and functions defined in the
// printer.c file. Furthermore, do not access the fields of the printer struct
// directly, but use the functions from the API instead.
//
// Hints:
//
//  - Notice that showing the current content of the screen via the refresh function
//    will erase anything otherwise shown on the console, including the statements
//    from the IO module. If you want to debug something for this task via printf
//    statements, you may want to comment out any calls to the refresh function
//    temporarily to let any other print statements get through.
//  - Calling the refresh function will also print the actual current state of the LED
//    to the console, so you can compare your intended behavior with the actual
//    behavior of the robot.


static struct printer *printer;

/**
 * Wait offset milliseconds and then start to turn the LED repeatedly on and off
 * again each period milliseconds.
 */
void led_blink(mseconds_t offset, mseconds_t period)
{
    // assume the LED is off at start
    bool state = true;
    // wait offset milliseconds
    msleep(offset);
    // repeat for ever :)
    for (;;) {
        // toggle stored state of the LED
        state ^= true;
        // set LED to the value of the stored state
        io_put(LED_PIN, state);
        // refresh printer
        print(printer, state ? "LED turns OFF" : "LED turns ON", 1);
        refresh(printer);
        // wait period milliseconds
        msleep(period);
    }
}

int main(void)
{
    io_init(LED_PIN);
    io_set_dir(LED_PIN, IO_OUT);
    printer = printer_create();
    led_blink(150, 500);
}
