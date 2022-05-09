#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 100
#define PIPENAME "./named_pipe_file"

int main(void) {
	char msg[BUFFER_SIZE];
	int pipefd;
	
	if ((pipefd = open(PIPENAME, O_WRONLY)) == -1) return -1;

	for (int i=0; i<5; i++) {
		sprintf(msg, "hello %d\n", i);
		if (write(pipefd, msg, sizeof(msg)) == -1) return -1;

		sleep(1);
	}
	sprintf(msg, "quit");
	if (write(pipefd, msg, BUFFER_SIZE) == -1) return -1;
	return 0;
}
