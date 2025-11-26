#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stddef.h>

/**
 * Prototype principal de _printf
 */
int _printf(const char *format, ...);

/**
 * Type pour associer un caractère de spécificateur à une fonction handler.
 * - type : caractère du format (ex: 'c', 's', '%')
 * - func : pointeur vers la fonction qui traitera ce type (va_list -> int)
 */
typedef struct specifier_s
{
    char type;
    int (*func)(va_list);
} specifier_t;

/* Prototypes des handlers définis dans _printf.c (déclarés ici pour éviter
 * implicit declaration errors lors de la compilation). */
int print_char(va_list args);
int print_string(va_list args);
int print_percent(va_list args);
int (*get_specifier_func(char c))(va_list);

#endif /* MAIN_H */
