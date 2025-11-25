#ifndef HEADER_FILE
#define HEADER_FILE

#include <limits.h>
#include <stdio.h>
#include "main.h"

int _printf(const char *format, ...);
int _putchar(char c);
int _puts(const char *s);
int handle_char(va_list args);
int handle_string(va_list args);
int handle_percent(void);

#endif
