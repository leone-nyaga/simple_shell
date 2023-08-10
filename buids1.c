#include "simple_shell.h"

/**
* _atoi - Converts a string to an integer.
* @s: The input string.
*
* Return: The converted integer if successful, or -1 if conversion fails.
*/
int _atoi(char *s)
{
unsigned int i = 0;
unsigned long n = 0;

if (*s == '+')
s++;
while (s[i])
{
if (s[i] >= '0' && s[i] <= '9')
n = n * 10 + (s[i] - '0');
else
return (-1);
i++;
}
if (n > INT_MAX)
return (-1);
return (n);
}

/**
* print_env - Prints the variables from the command history.
* @shell_info: Pointer to the ShellData structure.
*
* Return: 1 on success.
*/
int print_env(ShellData *shell_info)
{
list_t *head = shell_info->command_history;

while (head)
{
puts(head->str);
puts("\n");
head = head->next;
}
return (1);
}

/**
* call_exit - Calls the exit system call to terminate the shell.
* @shell_info: Pointer to the ShellData structure.
*
* Return: None (the function does not return).
*/
int call_exit(ShellData *shell_info)
{
int number = 0;

if (shell_info->argument_array[1])
{
number = _atoi(shell_info->argument_array[1]);
if (number == -1)
{
errno = ILLNUM;
error(shell_info, 21);
shell_info->exit_status = 2;
return (1);
}
}
else
{
number = shell_info->exit_status;
}
free(shell_info->argument_array);
free(shell_info->command_buffer);
free_list(shell_info->command_history);
exit(number);
}

/**
* custom_cd - Implements the "cd" built-in command.
* @shell_info: Pointer to the ShellData structure.
*
* Return: 1 on success.
*/
int custom_cd(ShellData *shell_info)
{
char *cwd = NULL, *temp = NULL;
char *oldwd = NULL;
int val = 0;
char *home = _getenv("HOME=", shell_info);

oldwd = getcwd(oldwd, 0);
if (shell_info->argument_array[1] == NULL)
{
val = chdir(home ? home : oldwd);
}
else if (*shell_info->argument_array[1] == '-')
{
val = chdir(_getenv("OLDPWD=", shell_info) ?
_getenv("OLDPWD=", shell_info) : oldwd);
puts(getcwd(temp, 0)), puts("\n"), free(temp);
}
else
val = chdir(shell_info->argument_array[1]);
if (val == -1)
{
errno = NOTDIR;
error(shell_info, 3);
}
if (1)
{
shell_info->argument_array[1] = "OLDPWD",
shell_info->argument_array[2] = oldwd;
_getenv("OLDPWD", shell_info);
shell_info->argument_array[1] = "PWD",
shell_info->argument_array[2] = cwd = getcwd(cwd, 0);
_setenv(shell_info);
free(cwd);
}
free(oldwd);
return (1);
}

/**
* builtins - Executes built-in commands based on the input command.
* @shell_info: Pointer to the ShellData structure.
*
* Return: 1 if a built-in command is , or 0 if no built-in command is found.
*/
int builtins(ShellData *shell_info)
{
built_ins_t func_array[] = {
{"env", print_env},
{"exit", call_exit},
{"cd", custom_cd},
{"unsetenv", unset_env},
{"setenv", set_env},
{"help", help},
{NULL, NULL}
};
int i = 0;

while (func_array[i].bi)
{
if (!_strcmp(shell_info->argument_array[0], func_array[i].bi))
return (func_array[i].function(shell_info));
i++;
}
return (0);
}

