#ifndef PRINTER_H
#define PRINTER_H

// The printer module.

#include <stdbool.h>

// Number of lines in the printer.
#define LINES 5
// Length of each line in the printer. Includes space for the null terminator.
#define LENGTH 16

/*
 * The printer struct. Don't use its fields directly, only through the
 * functions.
 */
struct printer {
    char buffer[LINES][LENGTH];
    int currentLine;
};

/*
 * Creates a new printer.
 */
struct printer* printer_create();

/*
 * Adds the given string to the given line in the printer.
 */
void print(struct printer* p, char* str, int line);

/*
 * Adds the given string to the current line in the printer and moves the
 * printer forward by one line.
 */
void print_next_line(struct printer* p, char* str);

/*
 * Adds the given string to the given line in the printer, starting from the
 * given offset.
 */
void print_from_offset(struct printer* p, char* str, int line, int offset);

/*
 * Adds the given string to the current line in the printer, starting from the
 * given offset, and moves the printer forward by one line.
 */
void print_from_offset_next_line(struct printer* p, char* str, int offset);

/*
 * Refreshes the printer display. Call this to print the current state of the
 * printer.
 */
void refresh(struct printer* p);

#endif // PRINTER_H
