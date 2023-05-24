#include "shell.h"

/**
 * print_error_message - prints an error message
 * @shellInfo: the parameter & return shellInfo struct
 * @estr: string containing specified error type
 * Return: Nothing
 */
void print_error_message(info_t *shellInfo, char *estr)
{
	_eputs(shellInfo->fname);
	_eputs(": ");
	print_decimal(shellInfo->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(shellInfo->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * err_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
int err_atoi(char *s)
{
	int index = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: investigate why this affects main return value */
	for (index = 0; s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			result *= 10;
			result += (s[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_decimal - prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 * Return: number of characters printed
 */
int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		absolute_value = -input;
		__putchar('-');
		count++;
	}
	else
		absolute_value = input;
	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function (clone of itoa)
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string representation of the number
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Nothing
 */
void remove_comments(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
}
