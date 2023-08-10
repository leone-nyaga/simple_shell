#include "simple_shell.h"

/**
* _memset - Fills a block of memory with a specified value.
* @s: Pointer to the memory to be filled.
* @b: The value to be set.
* @n: The number of bytes to be set to the value.
*
* Return: Pointer to the memory area @s.
*/
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;

for (i = 0; i < n; ++i)
s[i] = b;
return (s);
}

/**
* _strcat - Concatenates two strings.
* @dest: Pointer to the destination string.
* @src: Pointer to the source string.
*
* Return: Pointer to the resulting string @dest.
*/
char *_strcat(char *dest, char *src)
{
int i = strlen(dest);
int j = 0;

while (src[j])
dest[i++] = src[j++];
dest[i] = src[j];
return (dest);
}

/**
* _strcmp - Compares two strings.
* @s1: Pointer to the first string.
* @s2: Pointer to the second string.
*
* Return: 0 if the strings are , the difference between the ASCII values
* of the first differing character.
*/
int _strcmp(const char *s1, const char *s2)
{
size_t i = 0;

while (s1[i] || s2[i])
{
if (s1[i] == s2[i])
++i;
else
return (s1[i] - s2[i]);
}
return (0);
}

/**
* _strncmp - Compares two strings up to a given number of characters.
* @s1: Pointer to the first string.
* @s2: Pointer to the second string.
* @n: The maximum number of characters to compare.
*
* Return: 0 if the first n characters of the strings are equal.
* Otherwise, the difference bett differing character.
*/
int _strncmp(const char *s1, const char *s2, size_t n)
{
size_t i = 0;

while ((s1[i] || s2[i]) && i < n)
{
if (s1[i] == s2[i])
++i;
else
return (s1[i] - s2[i]);
}
return (0);
}

/**
* printerr - Writes a string to the standard error (file descriptor 2).
* @str: Pointer to the string to be written.
*
* Return: The number of characters written to the standard error.
*/
int printerr(char *str)
{
size_t i = strlen(str);

write(STDERR_FILENO, str, i);
return (i);
}

