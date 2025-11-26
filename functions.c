#include "main.h"

/**
 * print_char - Affiche un caractère
 * @args: Liste d'arguments
 * Return: 1
 */
int print_char(va_list args)
{
	char c = va_arg(args, int);
	return (_putchar(c));
}

/**
 * print_string - Affiche une chaîne de caractères
 * @args: Liste d'arguments
 * Return: Nombre de caractères affichés
 */
int print_string(va_list args)
{
	char *str = va_arg(args, char *);
	int i = 0;

	if (str == NULL)
		str = "(null)";

	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
	return (i);
}

/**
 * print_percent - Affiche le symbole %
 * @args: Liste d'arguments (non utilisée)
 * Return: 1
 */
int print_percent(va_list args)
{
	(void)args;
	return (_putchar('%'));
}

/**
 * print_int - Affiche un entier (pour d et i)
 * @args: Liste d'arguments
 * Return: Nombre de chiffres affichés
 */
int print_int(va_list args)
{
	int n = va_arg(args, int);
	int count = 0;
	unsigned int num;
	unsigned int div = 1;

	/* Gestion du signe */
	if (n < 0)
	{
		count += _putchar('-');
		num = (unsigned int)-n;
	}
	else
	{
		num = (unsigned int)n;
	}

	/* Calcul du diviseur pour extraire les chiffres un par un */
	while (num / div > 9)
		div *= 10;

	/* Boucle d'affichage */
	while (div != 0)
	{
		count += _putchar((num / div) + '0');
		num %= div;
		div /= 10;
	}

	return (count);
}
