/* _printf.c
 * Simplified _printf: supports %c, %s, %%, %d and %i
 */

#include "main.h"
#include <stdarg.h>

/**
 * _printf - prints formatted output (supports c, s, %, d, i)
 * @format: format string
 *
 * Return: number of characters printed, or -1 on error (format == NULL)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int total = 0;
    int i = 0;
    char *s;
    char ch;
    int n;
    int printed;

    if (format == NULL)
        return (-1);

    va_start(args, format);

    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            /* stray '%' at end */
            if (format[i] == '\0')
                break;

            switch (format[i])
            {
            case 'c':
                ch = (char)va_arg(args, int);
                _putchar(ch);
                total++;
                break;
            case 's':
                s = va_arg(args, char *);
                if (s == NULL)
                    s = "(null)";
                for (printed = 0; s[printed]; printed++)
                    _putchar(s[printed]);
                total += printed;
                break;
            case '%':
                _putchar('%');
                total++;
                break;
            case 'd':
            case 'i':
                n = va_arg(args, int);
                total += print_number(n);
                break;
            default:
                /* unknown specifier: print '%' and the char literally */
                _putchar('%');
                _putchar(format[i]);
                total += 2;
                break;
            }
        }
        else
        {
            _putchar(format[i]);
            total++;
        }
        i++;
    }

    va_end(args);
    return (total);
}
