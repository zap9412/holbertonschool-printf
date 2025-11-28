#include "main.h"

/**
 * print_number - prints an integer and returns count of chars printed
 * @n: integer to print
 * Return: number of characters printed
 */
int print_number(int n)
{
    char buffer[12]; /* enough for "-2147483648" + '\0' */
    int i = 0, j;
    unsigned int num;
    int count = 0;

    if (n < 0)
    {
        _putchar('-');
        count++;
        /* handle INT_MIN safely */
        num = (unsigned int)(-(n + 1)) + 1;
    }
    else
        num = (unsigned int)n;

    if (num == 0)
    {
        _putchar('0');
        return (count + 1);
    }

    while (num > 0)
    {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    for (j = i - 1; j >= 0; j--)
        count += _putchar(buffer[j]);

    return (count);
}
