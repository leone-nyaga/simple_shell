#include "simple_shell.h"

/**
* list_length - Counts the number of elements in a linked list.
* @hd: Pointer to the head of the linked list.
*
* Return: The number of elements in the linked list.
*/
size_t list_length(const list_t *hd)
{
size_t command_count = 0;

while (hd)
{
command_count++;
hd = hd->next;
}
return (command_count);
}

/**
* list_delete - Deletes a node at the specified index from the linked list.
* @head: Pointer to a pointer to the head of the linked list.
* @index: Index of the node to be deleted (0-indexed).
*
* Return: 1 if the node is deleted successfully, -1 on failure.
*/
int list_delete(list_t **head, size_t index)
{
unsigned int j;
list_t *current;
list_t *forward;

if (*head == NULL)
return (-1);

current = *head;

if (index == 0)
{
*head = current->next;
free(current->str);
free(current);
return (1);
}

for (j = 0; j < index - 1; j++)
{
if (current->next == NULL)
return (-1);
current = current->next;
}

forward = current->next;
if (forward == NULL)
return (-1);

current->next = forward->next;
free(forward->str);
free(forward);
return (1);
}

/**
* command_history - Creates a linked list containing environment variables.
*
* Return: A pointer to the head of the created linked list.
*/
list_t *command_history(void)
{
int i = 0;
list_t *head = NULL;

while (environ[i])
{
adding(&head, environ[i]);
++i;
}
return (head);
}

