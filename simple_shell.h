#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

#define F_FLUSH -1
#define ILLNUM 666
#define NOTDIR 777
#define YOUR_BUFFER_SIZE 1024


int _getc(int fd);
char *_fgets(char *s, int n, int fd);
int _getline(char **lineptr, int fd);

extern char **environ;

typedef struct list_s
{
    char *str;
    struct list_s *next;
} list_t;

typedef struct ShellData
{
    char *command_buffer;
    char **argument_array;
    int command_count;
    pid_t status;
    list_t *command_history;
    char *argv;
    int argc;
    int exit_status;
    int index;
} ShellData;

typedef struct built_ins
{
    char *bi;
    int (*function)(ShellData *shell_info);
} built_ins_t;

void initialize_struct(ShellData *shell_info);
int get_exit_status(void);

size_t list_length(const list_t *hd);
int list_delete(list_t **head, size_t index);
list_t *command_history(void);
void execute_command(ShellData *shell_info);
char **tokarr(char *str);

char **argument_array_to_array(list_t *head);
int unset_env(ShellData *shell_info);
int set_env(ShellData *shell_info);
int help(ShellData *shell_info);
void help2(ShellData *shell_info);

int _atoi(char *s);
int print_env(ShellData *shell_info);
int call_exit(ShellData *shell_info);
int custom_cd(ShellData *shell_info);
int builtins(ShellData *shell_info);

list_t *list_insert(list_t **head, unsigned int index, char *str);

char *get_path(ShellData *shell_info);
char *_append(char *buff, char *token, char *s);
char *_getenv(char *name, ShellData *shell_info);
void evaluate_var(ShellData *shell_info);

void error(ShellData *shell_info, int errortype);
void _shell(ShellData *shell_info);
char *str_dup(const char *str);
int _isalpha(int c);

void free_list(list_t *command_history);
list_t *adding(list_t **head, const char *str);

char *convert(unsigned int num, int base);
void _fork(ShellData *shell_info);
void signal_hand(int signum __attribute__((unused)));

char *_memset(char *s, char b, unsigned int n);
char *_strcat(char *dest, char *src);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int printerr(char *str);

char *comments(char *str);
int _setenv(ShellData *shell_info);

#endif /* _SIMPLE_SHELL_H_ */

