#include "simple_shell.h"

/**
* initialize_struct - Initialize the ShellData structure with default values.
* @shell_info: Pointer to the ShellData structure to be initialized.
*
* This function sets default values for the members of the ShellData structure.
* It initializes the command buffer and array to NULL, sets the command
* count to 0, initializes the command history linked list, ane exit status
* to 0.
*
* Return: None.
*/
void initialize_struct(ShellData *shell_info)
{
shell_info->command_buffer = NULL;
shell_info->argument_array = NULL;
shell_info->command_count = 0;
shell_info->command_history = command_history();
shell_info->exit_status = 0;
}

/**
* get_exit_status - Getp exit status based on the value of errno.
*
* This function returns an exit
* Return: The exit status code.
*/
int get_exit_status(void)
{
int number = 0;

if (errno == EACCES)
number = 126;
else if (errno == ENOTDIR || errno == ENOENT)
number = 127;
return (number);
}

/**
* main - Entry point of the simple shell program.
* @argc: The number of command-line arguments.
* @argv: An array of strings containing the command-line arguments.
*
* This function initializes*
* Return: 0 on success.
*/
int main(int argc, char **argv)
{
ShellData shell_info;
char *line = NULL;
size_t len = 0;
ssize_t read;

shell_info.argc = argc;
shell_info.argv = argv[0];
initialize_struct(&shell_info);
signal(SIGINT, signal_hand);

if (argc == 2)
{
FILE *file = fopen(argv[1], "r");
if (file == NULL)
{
perror("Error opening file");
return (1);
}

while ((read = getline(&line, &len, file)) != -1)
{
if (read > 1)
{
line[read - 1] = '\0';
shell_info.command_buffer = line;
_shell(&shell_info);
}
}
fclose(file);
if (line)
free(line);
}
else
{
_shell(&shell_info);
}

return (0);
}

