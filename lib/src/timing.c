#include "common/timing.h"

#include <time.h>

// #define TIME_FACTOR (0.2)

int msleep(mseconds_t mseconds)
{
#ifdef TIME_FACTOR
    mseconds = (mseconds_t)(mseconds / (float)TIME_FACTOR);
#endif
    struct timespec ts;
    ts.tv_sec = mseconds / 1000;
    ts.tv_nsec = (mseconds % 1000) * 1000000;
    return nanosleep(&ts, NULL);
}
