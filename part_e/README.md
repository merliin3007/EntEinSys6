# **Part E:** Simulated Threads

- We have decided to _not_ take two distinct integer arrays, one for the offsets and one for the period, but one array of `struct Thread`s containng both information. The reason is consistency with [excercise part d](../part_d/README.md).


> Now everything is deterministic again, but also try out your program with these inputs: `offsets=[0s,1/9s]`, `periods=[1s,4/9s]`.

# How do you encode these inputs into your functions interface? 

See [lib/src/blink_thread.c](/lib/src/blink_thread.c), lines 18-29:

```c
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
```

The macro `msecs_from_secs(x)` expands to `((mseconds_t)((x) * 1000.0)`. Thus, $1/9s$ is represented as $111$ milliseconds and $4/9s$ as $444$ milliseconds.

# What happens with your program at t=1s?

The LED gets toggled repeatedly nine times at t=1s.

# Is that the intended behavior of the inputs?

No, it is not.
