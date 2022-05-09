#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 100
#define PIPENAME "./named_pipe_file"

int main(void) {
	char msg[BUFFER_SIZE];
	int pipefd;

	// 기존 named_pipe 제거
	if (access(PIPENAME, F_OK) == 0) {
		unlink(PIPENAME);
	}
	
	// 접근 권한이 0666인 named_pipe 생성
	if (mkfifo(PIPENAME, 0666) == -1) return -1;

	if ((pipefd=open(PIPENAME, O_RDWR)) == -1) return -1;

	while (1) {
		if (read(pipefd, msg, sizeof(msg)) == -1) return -1;

		if (!strcmp(msg, "quit")) return 0;

		printf("receive msg : %s\n", msg);
	}
	return 0;
}
