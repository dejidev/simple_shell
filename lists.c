#include "shell.h"

/**
 * add_node_start - Adds a node to the start of the list
 * @head: Address of pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Pointer to the new head of the list
 */
list_t *add_node_start(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - Adds a node to the end of the list
 * @head: Address of pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Pointer to the new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;

		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_list_str - Prints only the str element of a list_t linked list
 * @h: Pointer to the first node
 *
 * Return: Number of nodes in the list
 */
size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * delete_node_at_index - Deletes a node at the given index
 * @head: Address of pointer to the first node
 * @index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *current, *prev_node;
	unsigned int count = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		current = *head;
		*head = (*head)->next;
		free(current->str);
		free(current);
		return (1);
	}

	current = *head;
	while (current)
	{
		if (count == index)
		{
			prev_node->next = current->next;
			free(current->str);
			free(current);
			return (1);
		}
		count++;
		prev_node = current;
		current = current->next;
	}

	return (0);
}

/**
 * free_list - Frees all nodes of a list
 * @head_ptr: Address of pointer to the head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *current, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	current = head;
	while (current)
	{
		next_node = current->next;
		free(current->str);
		free(current);
		current = next_node;
	}

	*head_ptr = NULL;
}
