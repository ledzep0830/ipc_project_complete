#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 100
#define NP_RECEIVE "./server_to_client"
#define NP_SEND "./client_to_server"

int main(void) {
	char receive_msg[BUFFER_SIZE], send_msg[BUFFER_SIZE];
	int receive_fd, send_fd;
	/*---------------------------------------*/
	/* TODO 1 : init receive_fd and send_fd  */

	if ((receive_fd = open(NP_RECEIVE, O_RDWR)) == -1) return -1;
	if ((send_fd = open(NP_SEND, O_WRONLY)) == -1) return -1;
	
	/* TODO 1 : END                          */
	/*---------------------------------------*/

	for (int i=12; i<16; i++) {
		printf("client : send %d\n", i);
		sprintf(send_msg, "%d", i);
		/*---------------------------------------*/
		/* TODO 2 : send msg and receive msg     */

		if (write(send_fd, send_msg, sizeof(send_msg)) == -1) return -1;

        if (read(receive_fd, receive_msg, sizeof(receive_msg)) == -1) return -1;

		/* TODO 2 : END                          */
		/*---------------------------------------*/

		printf("client : receive %s\n\n", receive_msg);

        usleep(500*1000);
	}
	return 0;
}
