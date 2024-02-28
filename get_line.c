#include "shell.h"


/**
 * bring_line - assigns the line var for get_line
 * @lineptr: Buffer that store the user_in str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFFERSIZE)
			*n = j;

		else
			*n = BUFFERSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFFERSIZE)
			*n = j;
		else
			*n = BUFFERSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * get_line - Read stdin from stream
 * @lineptr: buffer that stores the user_in
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t user_in;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (user_in == 0)
		fflush(stream);
	else
		return (-1);
	user_in = 0;

	buffer = malloc(sizeof(char) * BUFFERSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && user_in == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && user_in != 0)
		{
			user_in++;
			break;
		}
		if (user_in >= BUFFERSIZE)
			buffer = func_realloc(buffer, user_in, user_in + 1);
		buffer[user_in] = t;
		user_in++;
	}
	buffer[user_in] = '\0';
	bring_line(lineptr, n, buffer, user_in);
	retval = user_in;
	if (i != 0)
		user_in = 0;
	return (retval);
}
