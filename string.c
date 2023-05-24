#include "shell.h"

/**
 * get_string_length - Get the length of a string
 * @s: The string to get the length of
 *
 * Return: The length of the string
 */
int get_string_length(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s++)
		length++;
	return (length);
}

/**
 * compare_strings - Compare two strings lexicographically
 * @string1: The first string to compare
 * @string2: The second string to compare
 *
 * Return: Negative if string1 < string2, positive if string1 > string2,
 *         zero if string1 == string2
 */
int compare_strings(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * find_substring - Find if a string starts with a specific substring
 * @str: The string to search in
 * @substr: The substring to find
 *
 * Return: Address of the next character of str if found, NULL otherwise
 */
char *find_substring(const char *str, const char *substr)
{
	while (*substr)
		if (*substr++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * concatenate_strings - Concatenate two strings
 * @destination: The destination buffer
 * @source: The source buffer
 *
 * Return: Pointer to the destination buffer
 */
char *concatenate_strings(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (result);
}
