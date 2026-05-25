// # Part d (3 points)
//
// Now that you can turn a single LED on and off with a fixed frequency, you
// wonder what will happen if you overlay multiple frequencies and different
// offsets to turn the LED on and off. Implement the same behavior as above for
// multiple threads, such that your main function can spawn multiple threads
// with the same function as above, each individually switching between turning
// the LED on and off, disregarding if the LED has already been turned to the
// same state by another thread. For example, starting two threads with the same
// offset and period will not change the behavior compared to a single thread,
// because both threads turn the LED on or off at the same time. Use pthreads by
// including <pthread.h> and spawning new threads with pthread_create.
// Furthermore, modify your print statements to the printer by adding an
// identifier of the thread that is currently setting the LED. An output may
// look like this: "T0: LED OFF" (thread with ID 0 turns the LED off).
//
// Test your program with different offsets and periods. Hand in one such test
// with these parameters:
//
// Thread 0: offset 0, period 500
// Thread 1: offset 250, period 500
// Thread 2: offset 500, period 1000
//
// When executing this program, you may notice non-deterministic behavior. At
// which points in time is the behavior non-deterministic and why? Can this be
// solved via synchronization with semaphores? Argue!
//
// Hints:
//
//  - To correctly compile threaded programs, call the gcc compiler with the -pthread
//    flag.
//  - Any function that you call with pthread_create needs to return a void* and take
//    a single parameter of the type void*. This is a pointer of any type that you can
//    cast to a void* when calling pthread_create and cast back to its original type
//    in the called function. A sensible way to give the function the necessary
//    parameters is via a struct.

#include "io.h"
#include "printer.h"
#include "common/blink_thread.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static struct printer *printer;

/**
 * Wait offset milliseconds and then start to turn the LED repeatedly on and off
 * again each period milliseconds.
 */
void *led_blink(void *arg)
{
    struct Thread *thread = (struct Thread *)arg;
    // assume the LED is off at start
    bool state = true;
    // wait offset milliseconds
    msleep(thread->offset);
    // repeat for ever :)
    for (;;) {
        // toggle stored state of the LED
        state ^= true;
        // set LED to the value of the stored state
        io_put(LED_PIN, state);
        // print
        print_blink_thread_state(printer, thread->name, state, 1);
        refresh(printer);
        // wait period milliseconds
        msleep(thread->period);
    }
    return NULL;
}

void led_blink_multiple(struct Thread *threads, size_t count)
{
    // allocate some memory to store thread ids
    pthread_t *thread_ids = malloc(sizeof(pthread_t) * count);
    // start one thread for each param
    for (size_t i = 0; i < count; ++i) {
        pthread_create(thread_ids + i, NULL, led_blink, threads + i);
    }
    // wait for all threads to finish
    for (size_t i = 0; i < count; ++i) {
        pthread_join(thread_ids[i], NULL);
    }
}

int main(void)
{
    io_init(LED_PIN);
    io_set_dir(LED_PIN, IO_OUT);
    printer = printer_create();
    led_blink_multiple(example_threads_part_d, 3);
    return 0;
}
