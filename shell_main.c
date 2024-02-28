#include <sys/types.h>
#include <sys/wait.h>

int main() {
	char command[1024];

	while (1) {
		printf("MyShell> ");
		fflush(stdout);
		
		if (fgets(command, sizeof(command), stdin) == NULL) {
			if (feof(stdin)) {
				printf("\nExiting\n");
				exit(0);
			} else {
				perror("Error in input");
				exit(1);
			}
		}
		
		command[strcspn(command, "\n")] = '\0';
		
		pid_t pid = fork();
		
		if (pid < 0) {
			perror("Fork failed");
			exit(1);
		} else if (pid == 0) {
			execlp(command, command, NULL);
			fprintf(stderr, "Error: The Command '%s' not found\n", command);
			exit(1);
		} else {
			int status;
			waitpid(pid, &status, 0);
			if (!WIFEXITED(status)) {
				fprintf(stderr, "Error: Command '%s' terminated abnormally\n", command);
			}
		}
	}
	
	return (0);
}
