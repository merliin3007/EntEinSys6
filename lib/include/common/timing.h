#ifndef TIMING_H
#define TIMING_H

// jaa, ich weiß, dass _t reserved ist.
typedef unsigned int mseconds_t;

#define msecs_from_secs(secs) ((mseconds_t)((secs) * 1000.0))

/**
 * Sleep mseconds milliseconds, or until a signal arrives that is not blocked or
 * ignored.
 */
int msleep(mseconds_t mseconds);

#endif // TIMING_H
