#include "shell.h"

/**
 * custom_strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @num: the number of characters to be copied
 * Return: the concatenated string
 */
char *custom_strncpy(char *dest, char *src, int num)
{
	int index1, index2;
	char *s = dest;

	index1 = 0;
	while (src[index1] != '\0' && index1 < num - 1)
	{
		dest[index1] = src[index1];
		index1++;
	}
	if (index1 < num)
	{
		index2 = index1;
		while (index2 < num)
		{
			dest[index2] = '\0';
			index2++;
		}
	}
	return (s);
}

/**
 * custom_strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: a pointer to the memory area s
 */
char *custom_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * custom_strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @num: the number of bytes to be maximally used
 * Return: the concatenated string
 */
char *custom_strncat(char *dest, char *src, int num)
{
	int index1, index2;
	char *s = dest;

	index1 = 0;
	index2 = 0;
	while (dest[index1] != '\0')
		index1++;
	while (src[index2] != '\0' && index2 < num)
	{
		dest[index1] = src[index2];
		index1++;
		index2++;
	}
	if (index2 < num)
		dest[index1] = '\0';
	return (s);
}
