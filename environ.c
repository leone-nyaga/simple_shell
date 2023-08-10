#include "simple_shell.h"

/**
* get_path - Get the fullhing through the directories
*            listed in the 'PATH' environment variable.
* @shell_info: Pointer to the ShellData structure.
*
* Return: string representing the full path of the command if found,
*         or the original command name if not found.
*/
char *get_path(ShellData *shell_info)
{
char *str = _getenv("PATH=", shell_info);
char *token, *strr;
static char command_buffer[256 + PATH_MAX];
struct stat st;
int i = 0, word = 0, count = 0;

if (!str)
return (shell_info->argument_array[0]);
if (str[0] == ':' && !stat(shell_info->argument_array[0], &st))
return (shell_info->argument_array[0]);
if (!_strncmp(shell_info->argument_array[0], "./", 2))
return (shell_info->argument_array[0]);
while (str && str[i])
{
if (!word && str[i] != ':')
{
word = 1;
++count;
}
else if (word && str[i] == ':')
word = 0;
i++;
}
token = strtok(str, ":");
while (token && shell_info->argument_array[0])
{
strr = _append(command_buffer, token, shell_info->argument_array[0]);
if (!stat(command_buffer, &st))
return (strr);
if (count-- > 1 && *(token + strlen(token) + 1) ==
':' && !stat(shell_info->argument_array[0], &st))
return (shell_info->argument_array[0]);
token = strtok(NULL, ":");
_memset(command_buffer, 0, 256 + PATH_MAX);
}
return (shell_info->argument_array[0]);
}

/**
* evaluate_var - Evaluate environment variables within  arguments.
* @shell_info: Pointer to the ShellData structure.
*
* Return: ray by replacing any environment variables found
*         with their corresponding values.
*/
void evaluate_var(ShellData *shell_info)
{
int i = 0, j = 0, flag = 0, len = 0;
static char *number;

while ((shell_info->argument_array)[i])
{
if (*((shell_info->argument_array))[i] == '$')
{
flag = 1;
break;
}
i++;
}

if (flag)
{
((shell_info->argument_array))[i]++;
len = strlen(((shell_info->argument_array))[i]);

if (strncmp(((shell_info->argument_array))[i], "$?", 2) == 0)
{
((shell_info->argument_array))[i] =
number = convert(shell_info->exit_status, 10);
}
else if (strncmp(((shell_info->argument_array))[i], "$$", 2) == 0)
{
((shell_info->argument_array))[i] = number = convert(getpid(), 10);
}
else
{
while (environ[j])
{
if (!strncmp(((shell_info->argument_array))[i], environ[j], len))
{
((shell_info->argument_array))[i] = environ[j] + len + 1;
break;
}
j++;
}
}
}
}

