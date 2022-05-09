#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 25

int main(void) {
	int n, pipefd[2], pid;

	if (pipe(pipefd) < 0) return -1; // generate pipe

	if ((pid = fork()) < 0) return -1;
	else if (pid > 0) { // parent process
		close(pipefd[0]);
		char write_msg[BUFFER_SIZE] = "hello, korea\n";
		
		write(pipefd[1], write_msg, strlen(write_msg)+1);
		close(pipefd[1]);
	} else { // child process
		close(pipefd[1]);
		char read_msg[BUFFER_SIZE];
		
		n = read(pipefd[0], read_msg, BUFFER_SIZE);
		printf("child : %s\n", read_msg);
		close(pipefd[0]);
	}
	return 0;
}
