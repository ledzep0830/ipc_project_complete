#include "message_buffer.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    MessageBuffer *buffer;
    int account_id = atoi(argv[1]);
    int data = atoi(argv[2]);
    pid = getpid();

    attach_buffer(&buffer);
    produce(&buffer, (int)pid, data, account_id);

    return 0;
}
