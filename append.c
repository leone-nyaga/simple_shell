#include "simple_shell.h"

/**
* _append - Concatenates strings and appends a token and s at the end of buff.
* @buff: The destination buffer.
* @token: The first string to be concatenated.
* @s: The second string to be concatenated.
*
* Return: Pointer to the resulting string in buff, or NULL on error.
*/
char *_append(char *buff, char *token, char *s)
{
size_t buff_len = strlen(buff);
size_t token_len = strlen(token);
size_t s_len = strlen(s);

if (buff_len + token_len + s_len + 2 > YOUR_BUFFER_SIZE)
{
return (NULL);
}
_strcat(buff, token);
_strcat(buff, "/");
_strcat(buff, s);
return (buff);
}

/**
* _getenv - Retrieves the value of an environment variable based on its name.
* @name: The name of the environment variable.
* @shell_info: Pointer to the ShellData structure.
*
* Return: Pointer to  value of the environment variable, or NULL if not found.
*/
char *_getenv(char *name, ShellData *shell_info)
{
size_t len = strlen(name);
list_t *head = shell_info->command_history;

while (head)
{
if (!_strncmp(name, head->str, len) && head->str[len] == '=')
{
return (head->str + len + 1);
}
head = head->next;
}
return (NULL);
}

