#include "tokarr.h"
#include "simple_shell.h"

/**
* error - Function to handle and display errors based on the error type and errno.
* @shell_info: Pointer to the ShellData struct containing shell information.
* @errortype: Integer representing the type of error.
*/
void error(ShellData *shell_info, int errortype)
{
char *number = convert(shell_info->command_count, 10);

printerr(shell_info->argv);
printerr(": ");
if (errno == ENOTDIR || errno == ENOENT || errno == ENOTTY)
{
printerr(number);
printerr(": ");
printerr(shell_info->argument_array[0]);
write(STDERR_FILENO, ": not found\n", 12);
}
else if (errortype == 1)
{
printerr(number);
printerr(": ");
printerr(shell_info->argument_array[0]);
printerr(": bad variable name\n");
}
else if (errortype == 2)
{
printerr(number);
printerr(": ");
printerr(shell_info->argument_array[0]);
write(STDERR_FILENO, ": no help topics match '", 24);
write(STDERR_FILENO, shell_info->argument_array[1], strlen(shell_info->argument_array[1]));
write(STDERR_FILENO, "'.\n", 3);
}
else if (errno == NOTDIR)
{
printerr(number);
printerr(": ");
printerr(shell_info->argument_array[0]);
write(STDERR_FILENO, ": can't cd to ", 14);
write(STDERR_FILENO, shell_info->argument_array[1], strlen(shell_info->argument_array[1]));
write(STDERR_FILENO, "\n", 1);
}
else if (errno == ILLNUM)
{
printerr(number);
printerr(": ");
printerr(shell_info->argument_array[0]);
printerr(": Illegal number: ");
printerr(shell_info->argument_array[1]);
printerr("\n");
}
else
{
printerr(number);
printerr(": ");
printerr(shell_info->argument_array[0]);
printerr(": ");
perror(NULL);
}
}

/**
* _shell - Main function that runs the shell.
* @shell_info: Pointer to the ShellData struct containing shell information.
*/
void _shell(ShellData *shell_info)
{
int get, val = 0;
size_t len = 0;
char *pt1, *pt2;

while (1)
{
if (isatty(STDIN_FILENO))
write(STDERR_FILENO, "$ ", 2);
get = getline(&(shell_info->command_buffer), &len, stdin);
if (get == -1)
{
if (isatty(STDIN_FILENO))
puts("\n");
free(shell_info->command_buffer);
free(shell_info->command_history);
exit(shell_info->exit_status);
}
pt1 = shell_info->command_buffer;
pt2 = strchr(pt1, ';');
if (pt2)
*pt2++ = '\0';
while (pt1)
{
shell_info->command_count++;
shell_info->argument_array = tokarr(comments(pt1));
if (!shell_info->argument_array[0])
{
free(shell_info->argument_array);
break;
}
/* evaluate_var(shell_info); */
val = builtins(shell_info);
if (!val)
_fork(shell_info);
free(shell_info->argument_array);
pt1 = pt2;
if (pt1)
pt2 = strchr(pt1, ';');
if (pt2)
*pt2++ = '\0';
}
}
free(shell_info->command_buffer);
free(shell_info->command_history);
free(shell_info->argument_array);
}

/**
* str_dup - Function to duplicate a string.
* @str: Pointer to the input string.
* Return: Pointer to the newly duplicated string.
*/
char *str_dup(const char *str)
{
char *s;
int i = 0;

if (str == NULL)
return (NULL);
while (str[i])
i++;
s = malloc(sizeof(char) * i + 1);
if (s == NULL)
return (NULL);
i = 0;
while (str[i])
{
s[i] = str[i];
i++;
}
s[i++] = '\0';
return (s);
}

/**
* _isalpha - Function to check if a character is an alphabet or underscore.
* @c: The character to check.
* Return: 1 if the character is an alphabet or underscore, 0 otherwise.
*/
int _isalpha(int c)
{
if ((c >= 'a' && c <= 'z') || ((c >= 'A' && c <= 'Z')) || c == '_')
return (1);
else
return (0);
}

