#include "shell.h"

/**
 * free_data - Frees the memory allocated for the data structure.
 *
 * @datash: Data structure to free.
 * Return: No return value.
 */
void free_data(data_shell *datash)
{
	unsigned int i;

	/* Free each environment variable */
	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ); /* Free the environment array */
	free(datash->pid); /* Free the process ID string */
}

/**
 * set_data - Initializes the data structure with initial values.
 *
 * @datash: Data structure to initialize.
 * @av: Argument vector.
 * Return: No return value.
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av; /* Set the argument vector */
	datash->input = NULL; /* Set input to NULL */
	datash->args = NULL; /* Set arguments to NULL */
	datash->status = 0; /* Set status to 0 */
	datash->counter = 1; /* Set counter to 1 */

	/* Count the number of environment variables */
	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1)); /* Allocate memory  */

	/* Copy each environment variable to the data structure */
	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdup(environ[i]);
	}

	datash->_environ[i] = NULL; /* Set the last element of the env */
	datash->pid = aux_itoa(getpid()); /* Convert the process ID to a string */
}

/**
 * main - Entry point of the shell program.
 *
 * @ac: Argument count.
 * @av: Argument vector.
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint); /* Set up the signal handler for SIGINT */
	set_data(&datash, av); /* Initialize the data structure */
	shell_loop(&datash); /* Start the shell loop */
	free_data(&datash); /* Free the allocated memory */
	if (datash.status < 0)
		return (255); /* Return 255 if status is negative */
	return (datash.status); /* Return the status value */
}
