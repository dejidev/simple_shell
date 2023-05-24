#include "shell.h"

/**
 * is_delim_chain - Checks if the current char.i
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise.
 */
int is_delim_chain(info_t *info, char *buf, size_t *p)
{
	size_t position = *p;

	if (buf[position] == '|' && buf[position + 1] == '|')
	{
		buf[position] = '\0';
		position++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[position] == '&' && buf[position + 1] == '&')
	{
		buf[position] = '\0';
		position++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[position] == ';') /* Found end of current command */
	{
		buf[position] = '\0'; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = position;
	return (1);
}

/**
 * ck_ch - Determines if we should continue chaining.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * @start_pos: Starting position in buf.
 * @length: Length of buf.
 *
 * Return: Void.
 */
void ck_ch(info_t *info, char *buf, size_t *p, size_t start_pos, size_t length)
{
	size_t position = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[start_pos] = '\0';
			position = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[start_pos] = '\0';
			position = length;
		}
	}

	*p = position;
}

/**
 * replace_alias - Replaces an alias in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int index;
	list_t *node;
	char *pointer;

	for (index = 0; index < 10; index++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		pointer = _strchr(node->str, '=');
		if (!pointer)
			return (0);
		pointer = _strdup(pointer + 1);
		if (!pointer)
			return (0);
		info->argv[0] = pointer;
	}
	return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int index = 0;
	list_t *node;

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;

		if (!_strcmp(info->argv[index], "$?"))
		{
			replace_string(&(info->argv[index]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[index], "$$"))
		{
			replace_string(&(info->argv[index]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[index][1], '=');
		if (node)
		{
			replace_string(&(info->argv[index]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[index], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaces a string.
 * @old_str: Address of the old string.
 * @new_str: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}
