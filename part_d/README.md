# **Part D:** Non-Deterministic Behavior

## When executing this program, you may notice non-deterministic behavior. At which points in time is the behavior non-deterministic and why?

The timing of the sleep function is not 100% exact. If two threads change the state of the LED _almost_ at the same time, it is possible that some times one thread comes first, some times the other thread. If one thread wants to turn the LED on and the other off, this means it depends on wich thead comes first if the LED is on or off afterwards.

## Can this be solved via synchronization with semaphores? Argue!

No, this can not be solved by semaphores. Semaphores can be used to ensure only one thread at a time gets access to some resource.
However, semaphores can _not_ be used to ensure exact timing.
