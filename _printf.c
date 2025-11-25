#include "main.h"

/**
 * _printf - print function
 * @format: str
 * Return: integer
 */

int _printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    if (format == NULL)
    return (-1);

}