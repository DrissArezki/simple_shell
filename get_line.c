#include <unistd.h>

#define BUFFER_SIZE 1024

char *custom_getline(void) {
	static char buffer[BUFFER_SIZE];
	static int buffer_index = 0;
	static int bytes_read = 0;
	static int eof_reached = 0;
	
	char *line = (char *)malloc(BUFFER_SIZE);
	
	if (line == NULL) {
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	
	int line_index = 0;
	int bytes_available = 0;
	
	while (!eof_reached) {
		if (buffer_index >= bytes_read) {
			bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buffer_index = 0;
			
			if (bytes_read <= 0) {
				eof_reached = 1;
				break;
			}
		}
		
		bytes_available = bytes_read - buffer_index;
		
		int i;
		
		for (i = 0; i < bytes_available; i++) {
			if (buffer[buffer_index + i] == '\n') {
				line[line_index++] = buffer[buffer_index + i++];
				buffer_index += i;
				break;
			} else {
				line[line_index++] = buffer[buffer_index + i];
			}
		}
		
		if (i < bytes_available)
			break;
		else
			buffer_index += i;
	}
	
	line[line_index] = '\0';
	
	if (line_index == 0 && eof_reached) {
		free(line);
		return (NUL)L;
	}
	
	return (line);
}

int main() {
	char *line;
	
	while ((line = custom_getline()) != NULL) {
		printf("Line: %s", line);
		free(line);
	}
	
	return (0);
}
