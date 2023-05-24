#include "shell.h"

/**
 * _myhistory - displays the history list with line numbers
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int _myhistory(ShellInfo *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_custom_alias - removes an alias from the alias list
 * @info: parameter struct
 * @custom_alias: the alias to unset
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_custom_alias(ShellInfo *info, char *custom_alias)
{
	char *p, c;
	int ret;

	p = _strchr(custom_alias, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, custom_alias, -1)));
	*p = c;
	return (ret);
}

/**
 * set_custom_alias - sets an alias to a string
 * @info: parameter struct
 * @custom_alias: the alias to set
 *
 * Return: Always 0 on success, 1 on error
 */
int set_custom_alias(ShellInfo *info, char *custom_alias)
{
	char *p;

	p = _strchr(custom_alias, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_custom_alias(info, custom_alias));

	unset_custom_alias(info, custom_alias);
	return (add_node_end(&(info->alias), custom_alias, 0) == NULL);
}

/**
 * print_custom_alias - prints an alias string
 * @alias_node: the alias node to print
 *
 * Return: Always 0 on success, 1 on error
 */
int print_custom_alias(list_t *alias_node)
{
	char *p = NULL, *a = NULL;

	if (alias_node)
	{
		p = _strchr(alias_node->str, '=');
		for (a = alias_node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_custom_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int my_custom_alias(ShellInfo *info)
{
	int index = 0;
	char *p = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_custom_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (index = 1; info->argv[index]; index++)
	{
		p = _strchr(info->argv[index], '=');
		if (p)
			set_custom_alias(info, info->argv[index]);
		else
			print_custom_alias(node_starts_with(info->alias, info->argv[index], '='));
	}

	return (0);
}
