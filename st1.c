#include "simple_shell.h"

/**
* comments - Truncst '#' character or after a space preceded by '#'.
* @str: The input string to process.
*
* Return: Pointer to the processed string.
*/
char *comments(char *str)
{
size_t i;
char *s = NULL;

i = 0;
s = str;
while (str && str[i])
{
if (str[0] == '#' || (str[i] == '#' && str[i - 1] == ' '))
{
*s = '\0';
}
s++;
i++;
}
return (str);
}

/**
* _strchr - Locate the first occurrence of a character in a string.
* @s: Pointer to the string to search.
* @c: The character to search for.
*
* Return: Pointer to the first occurrence of character @c in the string @s.
* If the character is not found, return NULL.
*/
char *_strchr(char *s, char c)
{
while (*s && *s != c)
{
s++;
}
if (*s == c)
return (s);
return (NULL);
}

