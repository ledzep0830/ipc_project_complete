#include "message_buffer_semaphore.h"
#include <stdio.h>

int main(void) {
    MessageBuffer *buffer;
    Message *msg;

    init_buffer(&buffer);
    init_sem();

    while (1) {
        if (consume(&buffer, &msg) == 0) {
            printf("sender_id : %d\naccount_id : %d\nbalance : %d\n\n", msg->sender_id, buffer->account_id, msg->data);
        }
    }
    return 0;
}
