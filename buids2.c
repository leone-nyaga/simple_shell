#include "simple_shell.h"

/**
 * list_insert - Inserts a new node with specified string at a given index
 *              in a linked list.
 * @head: Double pointer to the head of the linked list.
 * @index: Index where the new node should be inserted.
 * @str: String to be inserted in the new node.
 *
 * Return: Pointer to the newly inserted node, or NULL on failure.
 */
list_t *list_insert(list_t **head, unsigned int index, char *str)
{
unsigned int i;
list_t *tmp;
list_t *new_node;
i = 0;
tmp = *head;

    /* Traverse the linked list to find the node before the insertion point. */
while (i < index - 1)
{
if (!tmp)
	return (NULL);
tmp = tmp->next;
i++;
}

    /* Create a new node and allocate memory for it. */
new_node = malloc(sizeof(list_t));
if (!new_node)
	return (NULL);

    /* Insert the new node at the specified index. */
if (index)
{
new_node->next = tmp->next;
tmp->next = new_node;
}
else
{
new_node->next = tmp;
*head = new_node;
}

    /* Copy the string into the new node. */
new_node->str = str_dup(str);

return (new_node);
}

