#include "io.h"

#include <time.h>
#include <stdio.h>
#include <unistd.h>

// internal variables.
const int DIR_IN = -1;
const int DIR_OFF = 0;
const int DIR_OUT = 1;

time_t start_time;

bool initialized_pins[8] = {0}; 
bool initialized = false;

int pin_directions[8] = {DIR_OFF};

bool pin_values[8] = {false};

bool pin_allowed_range(uint pin) {
    return pin >= 0 && pin < 8;
}

void io_init(uint pin) {
    if (!pin_allowed_range(pin)) {
        return;
    }

    initialized_pins[pin] = true;

    if (pin == LED_PIN) {
        pin_values[pin] = true;
    }

    if (!initialized) {
        start_time = time(NULL);
        initialized = true;
    }
}

void io_deinit(uint pin) {
    if (!pin_allowed_range(pin)) {
        return;
    }

    pin_directions[pin] = DIR_OFF;
    initialized_pins[pin] = false;
}

void io_set_dir(uint pin, bool dir) {
    if (!pin_allowed_range(pin) || !initialized_pins[pin]) {
        return;
    }

    if (dir == IO_IN) {
        pin_directions[pin] = DIR_IN;
    } else if (dir == IO_OUT) {
        pin_directions[pin] = DIR_OUT;
    }
}

void io_put(uint pin, bool val) {
    if (!pin_allowed_range(pin) || !initialized_pins[pin] || pin_directions[pin] != DIR_OUT) {
        return;
    }

    bool hasChanged = pin_values[pin] != val;
    pin_values[pin] = val;

    if (pin == LED_PIN && hasChanged) {
        printf("LED is turning %s at time t=%ds.\n", val ? "off" : "on ", (int)(time(NULL) - start_time));
    }
}

bool io_read(uint pin) {
    if (!pin_allowed_range(pin) || !initialized_pins[pin] || pin_directions[pin] != DIR_IN) {
        return false;
    }

    return pin_values[pin];
}