include "shell.h"

/**
 * interactive - checks if the shell is in interactive mode
 * @info: pointer to the info_t struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if a character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isalpha - checks if a character is alphabetic
 * @c: the character to check
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to convert
 *
 * Return: the converted integer, or 0 if no numbers in the string
 */
int _atoi(char *s)
{
	int index, sign = 1, flag = 0, result = 0;
	unsigned int tempResult = 0;

	for (index = 0; s[index] != '\0' && flag != 2; index++)
	{
		if (s[index] == '-')
			sign *= -1;

		if (s[index] >= '0' && s[index] <= '9')
		{
			flag = 1;
			tempResult *= 10;
			tempResult += (s[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -tempResult;
	else
		result = tempResult;

	return (result);
}
