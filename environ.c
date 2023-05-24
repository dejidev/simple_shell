#include "shell.h"

/**
 * print_environment - Prints the current environment.
 * @shellInfo: Structure containing potential arguments.
 * Return: Always 0.
 */
int print_environment(ShellInfo *shellInfo)
{
	print_list_str(shellInfo->environment);
	return (0);
}

/**
 * get_environment_variable - Retrieves the value of an environment variable.
 * @shellInfo: Structure containing potential arguments.
 * @name: Environment variable name.
 * Return: The value of the environment variable.
 */
char *get_environment_variable(ShellInfo *shellInfo, const char *name)
{
	list_t *node = shellInfo->environment;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_environment_variable - Initializes a new environment variable
 *                            or modifies an existing one.
 * @shellInfo: Structure containing potential arguments.
 * Return: Always 0.
 */
int set_environment_variable(ShellInfo *shellInfo)
{
	if (shellInfo->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(shellInfo, shellInfo->argv[1], shellInfo->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_environment_variable - Removes an environment variable.
 * @shellInfo: Structure containing potential arguments.
 * Return: Always 0.
 */
int unset_environment_variable(ShellInfo *shellInfo)
{
	int index;

	if (shellInfo->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (index = 1; shellInfo->argv[index]; index++)
		_unsetenv(shellInfo, shellInfo->argv[index]);

	return (0);
}

/**
 * populate_environment_list - Populates the environment linked list.
 * @shellInfo: Structure containing potential arguments.
 * Return: Always 0.
 */
int populate_environment_list(ShellInfo *shellInfo)
{
	list_t *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		add_node_end(&node, environ[index], 0);
	shellInfo->environment = node;
	return (0);
}
