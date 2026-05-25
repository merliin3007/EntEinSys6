#include "printer.h"

#include "io.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


extern bool pin_values[];

struct printer* printer_create() {
    struct printer* p = (struct printer*) malloc(sizeof(struct printer));
    for (int i = 0; i < LINES; i++) {
        p->buffer[i][0] = '\0';
    }
    p->currentLine = 0;
    return p;
}

void print(struct printer* p, char* str, int line) {
    print_from_offset(p, str, line, 0);
}

void print_next_line(struct printer* p, char* str) {
    print(p, str, p->currentLine);
    p->currentLine = (p->currentLine + 1) % LINES;
}

void print_from_offset(struct printer* p, char* str, int line, int offset) {
    if (line < 0 || line >= LINES) {
        return;
    }
    for (int i = 0; i < LENGTH - offset; i++) {
        if (str[i] == '\n') {
            p->buffer[line][i + offset] = ' ';
            continue;
        }
        p->buffer[line][i + offset] = str[i];
        if (str[i] == '\0') {
            break;
        }
    }
    p->buffer[line][LENGTH - 1] = '\0';
}

void print_from_offset_next_line(struct printer* p, char* str, int offset) {
    print_from_offset(p, str, p->currentLine, offset);
    p->currentLine = (p->currentLine + 1) % LINES;
}

void refresh(struct printer* p) {
    printf("\033[H\033[JBeep Bop. Robot speaking. My LED is currently %s\n%s\n%s\n%s\n%s\n%s\n", pin_values[LED_PIN] ? "OFF" : "ON", p->buffer[0], p->buffer[1], p->buffer[2], p->buffer[3], p->buffer[4]);
}
