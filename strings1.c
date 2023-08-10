#include "simple_shell.h"

/**
* _strtok - Custom implementation of the strtok function.
* @buffer: The input string to tokenize.
* @delim: The delimiter used to split the string into tokens.
*
* Return: A pointer to the next token in the string.
* The function maintains 'p' to continue tokenizing the original string.
*/
char *_strtok(char *buffer, const char *delim)
{
    static char *p; /* Pointer to keep track of the next position to tokenize */
    int i = 0, letter = 0, stop = 0;
    char *sp;

    if (buffer)
        sp = buffer;
    p = sp;

    while (sp && *sp)
    {
        while (delim[i])
        {
            if (*sp == delim[i] && letter == 0)
            {
                ++p;
                ++sp;
                i = 0;
                continue;
            }
            if (*sp == delim[i] && letter == 1)
            {
                *sp++ = '\0';
                stop = 1;
                i = 0;
                break;
            }
            ++i;
        }
        if (stop)
            break;
        letter = 1;
        i = 0;
        ++sp;
    }

    if (!p || *p == '\0')
        return (NULL);
    return (p);
}

/**
* _putchar - Custom implementation of putchar with buffered output.
* @c: The character to print.
*
* Return: 1 on success, -1 on failure.
* The function uses a staticandard output when it's full or when 'F_FLUSH' is passed as input.
*/
int _putchar(int c)
{
	static int i;
	static char buf[BUFSIZ];

	if (c == F_FLUSH || i >= BUFSIZ)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != F_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
* _strlen - Calculate the length of a string.
* @str: The input string.
*
* Return: The length of the string.
*/
int _strlen(char *str)
{
	int i = 0;

	while (*(str + i))
		++i;

	return (i);
}

/**
* tokarr - Tokenize a string into an array of strings based on a delimiter.
* @buffer: The input string to tokenize.
*
* Return: A pointer to an array of strings (tokens).
* The last element of the array is NULL to indicate the end of tokens.
*/
char **tokarr(char *buffer)
{
	char *token;
	char **arr;
	char *pure = buffer;
	unsigned int i = 0, count = 0, word = 0, t = 0;

	while (pure && pure[i])
	{
		if (!word && pure[i] != ' ')
		{
			word = 1;
			++count;
		}
		else if (word && pure[i] == ' ')
			word = 0;
		i++;
	}

	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);

	token = _strtok(buffer, " \t\n");
	while (token)
	{
		arr[t] = token;
		t++;
		token = _strtok(NULL, " \t\n");
	}
	arr[t] = NULL;

	return (arr);
}

/**
* _eputs - Print a string to the standard output.
* @str: The input string to print.
*
* Return: The number of characters written.
*/
int _eputs(char *str)
{
	size_t i = _strlen(str);

	write(1, str, i);
	return (i);
}

