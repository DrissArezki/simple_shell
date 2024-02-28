#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

typedef struct LineList
{
	char *line;
	struct LineList *next;
} list_ln;

ssize_t get_line(char **lineptr, size_t *n, FILE *stream);





#endif
