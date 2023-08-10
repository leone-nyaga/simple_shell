#include "simple_shell.h"

/**
 * free_l - Frees the memory allocated for a linked list.
 * @command_history: Pointer to the head of the linked list.
 *
 * Return: None.
 */
void free_l(list_t *command_history)
{
	list_t *current = command_history;
	list_t *next = NULL;

	if (command_history == NULL)
		return;

	/* Traverse the linked list and free each node */
	while (current->next != NULL)
	{
		free(current->str); /* Free the string stored in the node */
		next = current->next;
		free(current); /* Free the current node */
		current = next;
	}

	free(current->str); /* Free the string stored in the last node */
	free(current); /* Free the last node */
}

/**
 * adding - Adds a new node to the end of a linked list.
 * @head: Pointer to the pointer to the head of the linked list.
 * @str: The string to be stored in the new node.
 *
 * Return: Pointer to the newly created node, or NULL on failure.
 */
list_t *adding(list_t **head, const char *str)
{
	list_t *new_node = NULL;
	list_t *current = *head;

	/* Allocate memory for the new node */
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	/* Duplicate the input string and store it in the new node */
	new_node->str = str_dup(str);

	new_node->next = NULL;

	if (!*head)
	{
		/* If the linked list is empty, make the new node the head */
		*head = new_node;
		return (*head);
	}

	/* Traverse the linked list to find the last node */
	while (current->next)
		current = current->next;

	/* Append the new node to the end of the linked list */
	current->next = new_node;
	return (new_node);
}

