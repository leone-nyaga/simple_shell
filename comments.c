#include "simple_shell.h"

/**
* help - Display help information for built-in commands or general help.
* @shell_info: Pointer to the ShellData structure.
*
* Return: 1 on success.
*/
int help(ShellData *shell_info)
{
if (shell_info->argument_array[1])
{
help2(shell_info);
}
else
{
puts("Type 'help name' to find out more about the function 'name'.\n\n"
"env\nexit [n]\ncd [dir]\nunsetenv [name]\nsetenv [name]\nhelp [pattern...]\n");
}
return 1;
}

/**
* help2 - Display detailed help information for specific built-in commands.
* @shell_info: Pointer to the ShellData structure.
*
* Return: None (prints help information).
*/
void help2(ShellData *shell_info)
{
if (!_strcmp(shell_info->argument_array[1], "env"))
{
puts("env - Print the environment variables");
}
else if (!_strcmp(shell_info->argument_array[1], "exit"))
{
puts("exit - Exit the shell");
puts("    Usage: exit [n]");
puts("    Exit the shell with the given status 'n', which should be an integer.");
puts("    If 'n' is not provided, the exit status is that of the last command executed.");
}
else if (!_strcmp(shell_info->argument_array[1], "cd"))
{
puts("cd - Change the shell working directory");
puts("    Usage: cd [dir]");
puts("    Change the current working directory to 'dir'.");
puts("    If 'dir' is not provided, the shell's working directory is changed to the HOME directory.");
}
else if (!_strcmp(shell_info->argument_array[1], "unsetenv"))
{
puts("unsetenv - Remove an environmental variable");
puts("    Usage: unsetenv [name]");
puts("    Remove the environmental variable 'name' from the environment.");
puts("    The environment is unchanged if 'name' does not exist.");
}
else if (!_strcmp(shell_info->argument_array[1], "setenv"))
{
puts("setenv - Change or add an environmental variable");
puts("    Usage: setenv [name] [value] [overwrite]");
puts("    Add the environmental variable 'name' to the environment with the given 'value'.");
puts("    If 'name' already exists and 'overwrite' is 0, the value of 'name' is not changed.");
puts("    If 'overwrite' is 1, the value of 'name' is updated with the new 'value'.");
}
else if (!_strcmp(shell_info->argument_array[1], "help"))
{
puts("help - Display brief summaries of built-in commands");
puts("    Usage: help [pattern...]");
puts("    Display a brief summary of built-in commands that match the given 'pattern'.");
puts("    If 'pattern' is not provided, display help for all built-in commands.");
}
else
{
error(shell_info, 2);
}
}

