#include <stdio.h>
#include <stdlib.h>

/**
 * buffer_input - Reads and buffers chained commands
 * @info: Parameter struct
 * @buf: Address of the buffer
 * @len: Address of the length variable
 *
 * Return: Number of bytes read
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
	ssize_t read_bytes = 0;
	size_t new_len = 0;

	if (!*len) /* If nothing is left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_sigint);

#if USE_GETLINE
		read_bytes = getline(buf, &new_len, stdin);
#else
		read_bytes = _getline(info, buf, &new_len);
#endif

		if (read_bytes > 0)
		{
			if ((*buf)[read_bytes - 1] == '\n')
			{
				(*buf)[read_bytes - 1] = '\0'; /* Remove trailing newline */
				read_bytes--;
			}

			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			/* Check if there is a command chain */
			*len = read_bytes;
			info->cmd_buf = buf;
		}
	}

	return (read_bytes);
}

/**
 * get_input - Gets a line of input without the newline character
 * @info: Parameter struct
 *
 * Return: Number of bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* Buffer for ';' command chain */
	static size_t index1, j, len;
	ssize_t read_bytes = 0;
	char **buf_p = &(info->arg);
	char *p;

	_putchar(BUF_FLUSH);
	read_bytes = buffer_input(info, &buf, &len);

	if (read_bytes == -1) /* End-of-file (EOF) */
		return (-1);

	if (len) /* There are commands left in the chain buffer */
	{
		j = index1; /* Initialize new iterator to current buffer position */
		p = buf + index1; /* Get pointer for return */

		check_chain(info, buf, &j, index1, len);

		while (j < len) /* Iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		index1 = j + 1; /* Increment past nullified ';' */

		if (index1 >= len) /* Reached end of buffer */
		{
			index1 = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Pass back pointer to current command position */
		return (_strlen(p)); /* Return length of current command */
	}

	*buf_p = buf; /* Not a chain, pass back buffer from _getline() */
	return (read_bytes); /* Return length of buffer from _getline() */
}

/**
 * read_buffer - Reads a buffer
 * @info: Parameter struct
 * @buf: Buffer
 * @i: Size
 *
 * Return: Number of bytes read
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t read_bytes = 0;

	if (*i)
		return (0);

	read_bytes = read(info->readfd, buf, READ_BUF_SIZE);
	if (read_bytes >= 0)
		*i = read_bytes;

	return (read_bytes);
}

/**
 * _getline - Gets the next line of input from STDIN
 * @info: Parameter struct
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 *
 * Return: Number of bytes read
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t read_bytes = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		read_bytes = *length;

	if (i == len)
		i = len = 0;

	read_bytes = read_buffer(info, buf, &len);
	if (read_bytes == -1 || (read_bytes == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, read_bytes, read_bytes ? read_bytes + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? (free(p), -1) : -1);

	if (read_bytes)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	read_bytes += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = read_bytes;
	*ptr = p;
	return (read_bytes);
}

/**
 * handle_sigint - Handles the SIGINT signal (Ctrl+C)
 * @sig_num: The signal number
 *
 * Return: void
 */
void handle_sigint(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
