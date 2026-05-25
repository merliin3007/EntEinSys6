#include "common/blink_thread.h"
#include "common/timing.h"

#include <string.h>

struct Thread example_threads_part_d[3] = {
    {.offset = 0, .period = 500, .name = "T0"},
    {.offset = 250, .period = 500, .name = "T1"},
    {.offset = 500, .period = 100, .name = "T2"}
};

struct Thread example_threads_part_e[3] = {
    {.offset = 0, .period = 300, .name = "T0"},
    {.offset = 100, .period = 500, .name = "T1"},
    {.offset = 0, .period = 600, .name = "T2"}
};

struct Thread example_threads_part_e2[2] = {
    {
        .offset = 0,
        .period = msecs_from_secs(1.f/9.f),
        .name = "T0"
    },
    {
        .offset = msecs_from_secs(1),
        .period = msecs_from_secs(4.f/9.f),
        .name = "T1"
    },
};

void print_blink_thread_state(
    struct printer *printer,
    char *name,
    bool state,
    int line
)
{
    print(printer, name, line);
    print_from_offset(
        printer,
        state ? ": LED OFF" : ": LED ON",
        line,
        strnlen(name, 16)
    );
}
