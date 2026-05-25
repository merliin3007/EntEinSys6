#ifndef BLINK_THREAD_H
#define BLINK_THREAD_H

#include "timing.h"
#include "printer.h"

/**
 * Contains LED blink paramters as well as a name associated with it.
 */
struct Thread {
    mseconds_t offset;
    mseconds_t period;
    char *name;
};

/**
 * Example test data as defined in the exercise part d
 */
extern struct Thread example_threads_part_d[3];

/**
 * Example test data as defined in the exercise part e
 */
extern struct Thread example_threads_part_e[3];

/**
 * Example test data as defined in the exercise part e
 */
extern struct Thread example_threads_part_e2[2];

/**
 * Print the change of the LEDs state by a specific thread
 */
void print_blink_thread_state(
    struct printer *printer,
    char *name,
    bool state,
    int line
);

#endif // BLINK_THREAD_H
