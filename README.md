# 🖨️ Custom `_printf` Project

Projet réalisé dans le cadre du programme **Holberton School** – Recréation partielle de la fonction standard `printf`.

---

## 📌 Objectif du Projet
Implémenter une fonction `_printf` capable d'afficher du texte selon un format précis, en gérant une partie des spécificateurs utilisés par la fonction standard `printf` de la bibliothèque C.

Prototype attendu :
```c
int _printf(const char *format, ...);
```

Votre fonction doit :
- Écrire sur **stdout**.
- Retourner le **nombre total de caractères imprimés**.
- Gérer certains spécificateurs du `printf` classique.
- Utiliser les **variadic functions** (`stdarg.h`).

---

## ✅ Spécificateurs gérés
Votre `_printf` doit gérer les conversions suivantes :

| Spécificateur | Description |
|--------------|-------------|
| `%c` | Affiche un caractère |
| `%s` | Affiche une chaîne de caractères |
| `%%` | Affiche le caractère `%` |

> 🚫 Vous n'avez PAS à gérer : flags, field width, precision, length modifiers, ni tous les autres types (`d`, `i`, `u`, `x`...).

---

## 📁 Organisation des Fichiers
Le projet doit être organisé comme suit :
```
holbertonschool-printf/
│
├── _printf.c          # Fonction principale
├── main.h             # Header contenant prototypes et includes
├── utils.c            # Fonctions utilitaires (ex : print_char, print_string)
├── man_3_printf       # Page de manuel
└── README.md          # Documentation du projet
```

---

## 🧩 Fonctionnement Global
### 🔹 1. Parcours du format
`_printf` lit la chaîne caractère par caractère.
- Si le caractère n’est pas `%` → il est affiché tel quel.
- Si `%` est détecté → on regarde le caractère qui suit pour déterminer le bon traitement.

### 🔹 2. Gestion des arguments variables
Le projet utilise :
```c
#include <stdarg.h>
```
Pour récupérer les arguments passés après `format` :
- `va_list`
- `va_start`
- `va_arg`
- `va_end`

### 🔹 3. Gestion des erreurs
Votre fonction doit :
- Retourner `-1` si **format est NULL**.
- Retourner `-1` si un `%` est suivi d’un **caractère non géré**.
- Imprimer `(null)` si une chaîne `%s` vaut `NULL`.

---

## 🚀 Exemple d’Utilisation
```c
int len = _printf("Hello %s! This is char: %c and percent: %%
", "world", 'X');
printf("Printed length = %d
", len);
```
Sortie :
```
Hello world! This is char: X and percent: %
Printed length = 49
```

---

## 🧪 Compilation & Test
```bash
gcc -Wall -Wextra -Werror -pedantic *.c -o printf
./printf
```

---

## 🤝 Travail en Binôme
Pour organiser efficacement le travail :
### 🔸 Branche personnelle
Chaque membre crée une branche :
```bash
git checkout -b dev-tonprenom
```

### 🔸 Fusion (pull request)
Les contributions sont fusionnées dans `main` lorsqu’elles sont stables.

### 🔸 Bonne pratique Git
- Commit fréquemment
- Push tôt, push souvent
- Messages de commit clairs
- Résoudre les conflits ensemble

---

## 🧼 Norme Betty
Tout le code doit respecter :
- **Betty-style**
- **Betty-doc**

Commandes de vérification :
```bash
betty *.c
betty *.h
```

---

## 📖 Ressources utiles
- `man 3 printf`
- `man 3 stdarg`
- Documentation Holberton sur les variadic functions

---

## ✨ Auteurs
Projet réalisé par :
- **Ton Nom (@ton_github)**
- **Ton/binôme (@github_binome)**

---

Si tu veux, je peux aussi créer :
- un diagramme de fonctionnement
- un guide pour les tests unitaires
- un Makefile complet
- ou documenter chaque fonction indépendamment.
/* main.h */
#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stddef.h>

/* Prototype for our printf replacement */
int _printf(const char *format, ...);

/* low-level output */
int _putchar(char c);
int _puts(const char *s);

/* handlers */
int handle_char(va_list args);
int handle_string(va_list args);
int handle_percent(void);

#endif /* MAIN_H */


/* _putchar.c */
#include "main.h"
#include <unistd.h>

/**
 * _putchar - writes a single character to stdout
 * @c: character to write
 *
 * Return: number of bytes written (1) or -1 on error
 */
int _putchar(char c)
{
	if (write(1, &c, 1) != 1)
		return (-1);
	return (1);
}

/**
 * _puts - writes a NUL-terminated string to stdout
 * @s: input string
 *
 * Return: number of characters written or -1 on error
 */
int _puts(const char *s)
{
	int count = 0;
	const char *p = s;

	if (s == NULL)
	{
		/* write (null) as a convention */
		p = "(null)";
	}

	while (*p)
	{
		if (_putchar(*p) < 0)
			return (-1);
		count++;
		p++;
	}
	return (count);
}


/* handlers.c */
#include "main.h"

/**
 * handle_char - get a char from va_list and print it
 * @args: va_list containing the argument
 *
 * Return: number of characters printed (1) or -1 on error
 */
int handle_char(va_list args)
{
	int c = va_arg(args, int);
	return (_putchar((char)c));
}

/**
 * handle_string - get a string from va_list and print it
 * @args: va_list containing the argument
 *
 * Return: number of characters printed or -1 on error
 */
int handle_string(va_list args)
{
	char *s = va_arg(args, char *);
	return (_puts(s));
}

/**
 * handle_percent - print a literal percent sign
 *
 * Return: number of characters printed (1) or -1 on error
 */
int handle_percent(void)
{
	return (_putchar('%'));
}


/* _printf.c */
#include "main.h"
#include <stdarg.h>

/**
 * _printf - simplified printf that supports %c, %s and %%
 * @format: format string
 * @...: arguments corresponding to format specifiers
 *
 * Return: number of characters printed (excluding terminating '\0'),
 *         or -1 on error (for example, NULL format)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int printed = 0;
	int res;

	if (format == NULL)
		return (-1);

	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
		{
			res = _putchar(*format);
			if (res < 0)
			{
				va_end(args);
				return (-1);
			}
			printed += res;
			format++;
			continue;
		}

		/* we have a '%' */
		format++; /* move past '%' */
		if (*format == '\0')
		{
			/* malformed format string: trailing '%' */
			va_end(args);
			return (-1);
		}

		switch (*format)
		{
			case 'c':
				res = handle_char(args);
				break;
			case 's':
				res = handle_string(args);
				break;
			case '%':
				res = handle_percent();
				break;
			default:
				/* Unknown specifier: print '%' then the char (mirrors many simple
				   custom printf implementations and avoids undefined behaviour)
				 */
				if (_putchar('%') < 0)
				{
					va_end(args);
					return (-1);
				}
				printed++;
				res = _putchar(*format);
		}

		if (res < 0)
		{
			va_end(args);
			return (-1);
		}
		printed += res;
		format++;
	}

	va_end(args);
	return (printed);
}
