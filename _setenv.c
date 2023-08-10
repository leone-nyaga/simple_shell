#include "simple_shell.h"

/**
* _setenv - Function to set or update an environment variable in the shell.
* @shell_info: Pointer to the ShellData struct containing shell information.
*
* Return: 0 on success, -1 on failure.
*/
int _setenv(ShellData *shell_info)
{
char *name, *value, *env_var;
int env_count = 0, index = -1, i;

if (shell_info->argc != 3)
{
fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
return (-1);
}

name = shell_info->argument_array[1];
value = shell_info->argument_array[2];

env_var = (char *)malloc(strlen(name) + strlen(value) + 2);
if (!env_var)
{
perror("malloc");
return (-1);
}
sprintf(env_var, "%s=%s", name, value);

while (environ[env_count])
{
env_count++;
}

for (i = 0; i < env_count; i++)
{
if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=')
{
index = i;
break;
}
}

if (index != -1)
{
free(environ[index]);
environ[index] = env_var;
}
else
{
char **new_environ = (char **)realloc(environ, sizeof(char *) * (env_count + 2));
if (!new_environ)
{
perror("realloc");
free(env_var);
return (-1);
}
environ = new_environ;
environ[env_count] = env_var;
environ[env_count + 1] = NULL;
}

free(env_var);

return (0);
}
