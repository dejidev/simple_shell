#include "shell.h"

/**
 * print_error_string - Prints an input string to stderr.
 * @string: The string to be printed.
 *
 * Return: Nothing.
 */
void print_error_string(char *string)
{
	int index = 0;

	if (!string)
		return;
	while (string[index] != '\0')
	{
		print_error_character(string[index]);
		index++;
	}
}

/**
 * print_error_character - Writes the character c to stderr.
 * @character: The character to print.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int print_error_character(char character)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (character != BUF_FLUSH)
		buffer[index++] = character;
	return (1);
}

/**
 * print_string_to_fd - Prints an input string to the given file descriptor.
 * @string: The string to be printed.
 * @file_descriptor: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int print_string_to_fd(char *string, int file_descriptor)
{
	int index = 0;

	if (!string)
		return (0);
	while (*string)
	{
		index += write_character_to_fd(*string++, file_descriptor);
	}
	return (index);
}

/**
 * write_character_to_fd - Writes the character c to the given file descriptor.
 * @character: The character to print.
 * @file_descriptor: The file descriptor to write to.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int write_character_to_fd(char character, int file_descriptor)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(file_descriptor, buffer, index);
		index = 0;
	}
	if (character != BUF_FLUSH)
		buffer[index++] = character;
	return (1);
}
