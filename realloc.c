#include "shell.h"

/**
 * fill_memory - Fills a memory area with a constant byte.
 * @mem: Pointer to the memory area.
 * @value: The byte value to fill the memory with.
 * @size: The number of bytes to be filled.
 *
 * Return: Pointer to the filled memory area.
 */
char *fill_memory(char *mem, char value, unsigned int size)
{
	unsigned int index;

	for (index = 0; index < size; index++)
		mem[index] = value;
	return (mem);
}

/**
 * free_string_array - Frees an array of strings.
 * @str_arr: The string array to free.
 */
void free_string_array(char **str_arr)
{
	char **ptr = str_arr;

	if (!str_arr)
		return;
	while (*str_arr)
		free(*str_arr++);
	free(ptr);
}

/**
 * re_al_mem - Reallocates a block of memory.
 * @ptr: Pointer to the previous allocated block.
 * @old_size: Size of the previous block in bytes.
 * @new_size: Size of the new block in bytes.
 *
 * Return: Pointer to the reallocated block of memory.
 */
void *re_al_mem(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
