#include "shell.h"

/**
 * copy_string - Copy a string
 * @destination: The destination string
 * @source: The source string
 *
 * Return: Pointer to the destination string
 */
char *copy_string(char *destination, char *source)
{
	int i = 0;

	if (destination == source || source == NULL)
		return (destination);
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (destination);
}

/**
 * duplicate_string - Duplicate a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *duplicate_string(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}

/**
 * print_string - Print a string
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		print_character(str[i]);
		i++;
	}
}

/**
 * print_character - Write a character to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int print_character(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buffer[i++] = c;
	return (1);
}
