/* _printf.c - implémentation minimaliste de _printf
 * gère : %c, %s, %%
 *
 * Remarques :
 * - Toute la logique (table de spécificateurs + handlers) est incluse ici
 *   pour respecter ta demande: uniquement _printf.c et main.h dans le projet.
 * - <= 5 fonctions dans ce fichier : _printf, get_specifier_func,
 *   print_char, print_string, print_percent.
 */

#include "main.h"
#include <unistd.h> /* write */
#include <stdlib.h> /* NULL */

/**
 * print_char - affiche un caractère passé via va_list
 * @args: liste d'arguments
 *
 * Return: nombre de caractères écrits (1) ou -1 en cas d'erreur
 */
int print_char(va_list args)
{
    char c = (char)va_arg(args, int);

    if (write(1, &c, 1) != 1)
        return (-1);
    return (1);
}

/**
 * print_string - affiche une chaîne passée via va_list
 * @args: liste d'arguments
 *
 * Si la chaîne est NULL, on affiche "(null)" (convention courante).
 *
 * Return: nombre de caractères écrits ou -1 en cas d'erreur
 */
int print_string(va_list args)
{
    char *s = va_arg(args, char *);
    int len = 0;
    const char *p;

    if (s == NULL)
        p = "(null)";
    else
        p = s;

    while (p[len] != '\0')
        len++;

    if (len == 0)
        return (0);

    if (write(1, p, (size_t)len) != (ssize_t)len)
        return (-1);

    return (len);
}

/**
 * print_percent - affiche le caractère '%' (ne consomme aucun argument)
 * @args: liste d'arguments (non utilisée)
 *
 * Return: 1 ou -1 en cas d'erreur
 */
int print_percent(va_list args)
{
    (void)args;
    if (write(1, "%", 1) != 1)
        return (-1);
    return (1);
}

/**
 * get_specifier_func - retourne la fonction handler correspondant au type
 * @c: caractère du spécificateur (ex: 'c', 's', '%')
 *
 * Return: pointeur sur fonction (va_list -> int) ou NULL si non trouvé
 *
 * NOTE: la table est déclarée localement ici ; elle relie directement le
 * caractère du format au handler correspondant.
 */
int (*get_specifier_func(char c))(va_list)
{
    specifier_t table[] = {
        {'c', print_char},
        {'s', print_string},
        {'%', print_percent},
        {'\0', NULL}
    };
    int i;

    for (i = 0; table[i].type != '\0'; i++)
    {
        if (table[i].type == c)
            return (table[i].func);
    }
    return (NULL);
}

/**
 * _printf - version simplifiée de printf
 * @format: chaîne de format
 *
 * Gère : %c, %s et %%
 * Retourne: nombre total de caractères écrits, ou -1 si erreur
 *
 * Comportements d'erreur:
 * - format == NULL -> -1
 * - '%' final sans spécificateur -> -1 (format mal formé)
 * - handlers retournant -1 -> propagation de l'erreur
 */
int _printf(const char *format, ...)
{
    va_list args;
    int printed = 0;
    int res;
    int i = 0;
    int (*func)(va_list);

    if (format == NULL)
        return (-1);

    va_start(args, format);
    while (format[i] != '\0')
    {
        if (format[i] != '%')
        {
            if (write(1, &format[i], 1) != 1)
            {
                va_end(args);
                return (-1);
            }
            printed++;
            i++;
            continue;
        }

        /* Si on est ici, format[i] == '%' */
        i++; /* avancer sur le caractère après '%' */

        /* Cas où '%' est caractère final -> format mal formé */
        if (format[i] == '\0')
        {
            va_end(args);
            return (-1);
        }

        /* Récupère le handler correspondant */
        func = get_specifier_func(format[i]);

        if (func != NULL)
        {
            res = func(args);
            if (res == -1)
            {
                va_end(args);
                return (-1);
            }
            printed += res;
        }
        else
        {
            /* Spécificateur inconnu : comportement défensif
             * On affiche '%' puis le caractère inconnu pour éviter UB */
            if (write(1, "%", 1) != 1)
            {
                va_end(args);
                return (-1);
            }
            if (write(1, &format[i], 1) != 1)
            {
                va_end(args);
                return (-1);
            }
            printed += 2;
        }
        i++;
    }
    va_end(args);
    return (printed);
}
