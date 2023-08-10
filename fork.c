#include "simple_shell.h"

/**
* execute_command - Execute a command in a child process and wait for completion
*                   in the parent process.
* @shell_info: Pointer to the ShellData structure.
*
* Return: None.
*/
void execute_command(ShellData *shell_info)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        char **env;
        env = argument_array_to_array(shell_info->command_history);
        shell_info->argument_array[0] = get_path(shell_info);
        if (execve(shell_info->argument_array[0], shell_info->argument_array, env) == -1)
        {
            perror("execve");
            free(shell_info->argument_array);
            free(shell_info->command_buffer);
            free_list(shell_info->command_history);
            free(env);
            exit(127);
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            shell_info->exit_status = WEXITSTATUS(status);
        }
    }
}


/**
* _fork - Fork a child process to execute a command and wait for its compon.
* @shell_info: Pointer to the ShellData structure.
*
* Return: None.
*/
void _fork(ShellData *shell_info)
{
pid_t pid = 0;
char **env = NULL;

if (*shell_info->argument_array[0] == '/' || _getenv("PATH=", shell_info))
{
pid = fork();
if (pid < 0)
return;
if (pid == 0)
{
shell_info->argument_array[0] = get_path(shell_info);
env = argument_array_to_array(shell_info->command_history);

evaluate_var(shell_info);

if (execve(shell_info->argument_array[0]
, shell_info->argument_array, env) == -1)
{
error(shell_info, 0), free(shell_info->argument_array)
, free(shell_info->command_buffer);
free(shell_info->command_history), free(env), exit(127);
}
}
else
{
waitpid(-1, &(shell_info->status), 0);
if (WIFEXITED(shell_info->status))
shell_info->exit_status = WEXITSTATUS(shell_info->status);
}
}
else
{
errno = ENOTDIR, shell_info->exit_status = 127,  error(shell_info, 0);
}
}

