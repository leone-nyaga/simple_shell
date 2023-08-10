#include "simple_shell.h"

/**
* convert - Convert an unsigned integer to a string in a specified base.
* @num: The unsigned integer to convert.
* @base: The base to use for conversion (e.g., 2 for binecimal).
*
* Return: A pointer to the resulting string representing the converted number.
* The function uses a static buffer, so subsequent callsrite the buffer.
*/
char *convert(unsigned int num, int base)
{
	static const char rep[] = "0123456789ABCDEF";
	static char buffer[11]; /* Buffer size to hold  null-terminator */
	char *ptr;

	ptr = &buffer[10]; /* Point to the last positioull-terminator) */
	*ptr = '\0'; /* Set the last position to null-terminator */
	do {
		*--ptr = rep[num % base]; /* Convert thdigit and move to the next position */
		num /= base; /* Divide the number base */
	} while (num != 0);
	return (ptr);
}

/**
* signal_hand - Signal handler function for SIGINT (Ctrlnd a shell prompt.
* @signum: The signal number (unused, but required by thtotype).
*/
void signal_hand(int signum __attribute__((unused)))
{
	puts("\n"); /* Print a newline */
	write(STDERR_FILENO, "$ ", 2); /* Write the shellstandard error stream */
	fflush(stdout); /* Flush the standard output str is displayed immediately */
}

