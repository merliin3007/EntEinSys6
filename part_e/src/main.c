// # Part e (3 points)
//
// To have a deterministic behavior, we decide to produce an alternative
// solution without threads, where the intended behavior is mimicked in a single
// thread. You task is to implement a solution where your function gets arrays
// of ints for multiple offset and period values in milliseconds and toggles the
// LEDs in a deterministic way for each of the inputs, thus simulating the
// threads of above. If two simulated threads want to access the LED at the same
// time, execute them in the same order as they occur in the arrays.
//
// For an input with the values offsets=[0ms, 100ms, 0ms] and periods=[300ms,
// 500ms, 600ms], this would be the expected behavior and a possible output on
// the printer:
//
// "T0:ON,0ms" (Simulated thread 0 turns the LED on at t=0ms)
// "T2:ON,0ms" (Simulated thread 2 turns the LED on at t=0ms)
// (program sleeps for 100ms)
// "T1:ON,100ms" (Simulated thread 1 turns the LED on at t=100ms)
// (program sleeps for 200ms)
// "T0:OFF,300ms" (Simulated thread 0 turns the LED off at t=300ms)
// (program sleeps for 300ms)
// "T0:ON,600ms" (you get the idea)
// "T1:OFF,600ms"
// "T2:OFF,600ms"
// etc.
//
// Now everything is deterministic again, but also try out your program with
// these inputs: offsets=[0s,1/9s], periods=[1s,4/9s]. How do you encode these
// inputs into your functions interface? What happens with your program at t=1s?
// Is that the intended behavior of the inputs?
//
// Overall hints:
//
//  - Hand in your fully commented solution of all parts in .c files. Hand in two
//    complete solutions: one for the threaded solution and one for the solution with
//    the merged behavior. You do not need to hand in your solutions for the interim
//    parts.
//  - Hand in how you compile your files into an executable program.
//  - Make sure that your program is compilable, solutions that do not compile will
//    get points deducted!
//  - Give a short answer to each question in the parts (when in doubt, look for
//    question marks in the text).

#include "common/blink_thread.h"
#include "io.h"

#include <stdlib.h>
#include <stdbool.h>

static struct printer *printer;

struct ThreadState {
    mseconds_t remaining_time;
    bool value;
};

int led_blink_multiple(struct Thread *threads, size_t count)
{
    // assert at least one thread
    if (count < 1) {
        return 1;
    }
    // init array of states
    struct ThreadState *states = malloc(sizeof(*states) * count);
    for (size_t i = 0; i < count; ++i) {
        // wait offset milliseconds initially
        states[i].remaining_time = threads[i].offset;
        // assume led to be turned off initially
        states[i].value = true;
    }
    for (;;) {
        // determine how long to wait until next event(s)
        mseconds_t wait_msecs = states[0].remaining_time;
        for (struct ThreadState *state = states + 1; state < states + count; ++state) {
            if (state->remaining_time < wait_msecs) {
                wait_msecs = state->remaining_time;
            }
        }
        // wait for next event(s)
        msleep(wait_msecs);
        // process event(s)
        for (size_t i = 0; i < count; ++i) {
            struct ThreadState *state = states + i;
            struct Thread *thread = threads + i;
            state->remaining_time -= wait_msecs;
            if (state->remaining_time == 0) {
                // toggle state
                state->value ^= true;
                io_put(LED_PIN, state->value);
                print_blink_thread_state(printer, thread->name, state, 1);
                // let thread wait for peroid milliseconds
                state->remaining_time = thread->period;
            }
        }
    }
    // just in case this function might be used by someone else...
    free(states);
    return 0;
}

int main(void)
{
    io_init(LED_PIN);
    io_set_dir(LED_PIN, IO_OUT);
    printer = printer_create();
    //led_blink_multiple(example_threads_part_d, 3);
    //led_blink_multiple(example_threads_part_e, 3);
    led_blink_multiple(example_threads_part_e2, 2);
    return 0;
}
