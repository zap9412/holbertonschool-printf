#include "main.h"

/**
 * get_op - Sélectionne la fonction correspondant au caractère
 * @c: Le caractère specifier (c, s, %, d, i)
 *
 * Return: Pointeur vers la fonction ou NULL
 */
int (*get_op(char c))(va_list)
{
	specifier_t specs[] = {
		{'c', print_char},
		{'s', print_string},
		{'%', print_percent},
		{'d', print_int},
		{'i', print_int},
		{'\0', NULL}
	};
	int i = 0;

	while (specs[i].type != '\0')
	{
		if (specs[i].type == c)
			return (specs[i].func);
		i++;
	}
	return (NULL);
}

/**
 * _printf - Fonction principale
 * @format: Chaîne de format
 *
 * Return: Nombre de caractères imprimés
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i = 0, count = 0;
	int (*f)(va_list);

	if (format == NULL)
		return (-1);

	va_start(args, format);
	while (format[i])
	{
		/* Cas normal : on imprime le caractère */
		if (format[i] != '%')
		{
			_putchar(format[i]);
			count++;
			i++;
			continue;
		}

		/* Cas du % : On regarde le suivant */
		if (format[i + 1] == '\0') /* Erreur: fin de chaîne après % */
			return (-1);

		f = get_op(format[i + 1]);

		if (f != NULL) /* Specifier trouvé */
		{
			count += f(args);
			i += 2;
		}
		else /* Specifier inconnu : on imprime le % et le char */
		{
			_putchar('%');
			_putchar(format[i + 1]);
			count += 2;
			i += 2;
		}
	}
	va_end(args);
	return (count);
}
