#include "simple_shell.h"

/**
* free_list - Fmory allocated for a linked list of strings.
* @command_history: Pointer to the head of the linked list.
*
* This f node in the linked list
* starting  to by 'command_history'. It iterates
* through tist, deallocating the memory for each string and node.
*
* Return: None.
*/
void free_list(list_t *command_history)
{
list_t *current = command_history;
while (current != NULL)
{
list_t *next = current->next;
free(current->str);
free(current);
current = next;
}
}
