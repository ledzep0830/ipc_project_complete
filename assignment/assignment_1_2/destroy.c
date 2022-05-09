#include "message_buffer_semaphore.h"

int main(void) {
    MessageBuffer *buffer;
    attach_buffer(&buffer);
    destroy_buffer();
    return 0;
}
