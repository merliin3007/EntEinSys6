#ifndef IO_H
#define IO_H

// The IO module.

#include <stdbool.h>

typedef unsigned int uint;

#define IO_IN false
#define IO_OUT true

// The IO pin to use for the LED. Turn the LED on by setting the pin low.
#define LED_PIN 4

/*
 * Initializes the given IO pin. This function must be called before any other
 * IO functions for that pin.
 */
void io_init(uint pin);

/*
 * Deinitializes the given IO pin. Turns off the pin for power saving.
 */
void io_deinit(uint pin);

/*
 * Sets the direction of the IO pin. If dir is IO_IN, the pin is an input. If
 * dir is IO_OUT, the pin is an output.
 */
void io_set_dir(uint pin, bool dir);

/*
 * Sets the value of the IO pin. True pulls the pin high, false pulls the pin
 * low.
 */
void io_put(uint pin, bool val);

/*
 * Reads the value of the IO pin. Returns true if the pin is high, false if the
 * pin is low.
 */
bool io_read(uint pin);

#endif // IO_H
