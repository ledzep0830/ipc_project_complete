#define SEM_KEY 54321
#define SHM_KEY 54321
#define BUFFER_SIZE 10

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

typedef struct {
    int sender_id;
    int data;
} Message;

typedef struct {
    Message messages[BUFFER_SIZE];
    int is_empty;
    int account_id;
} MessageBuffer;

void init_sem();
void destroy_sem();
void s_wait();
void s_quit();

int init_buffer(MessageBuffer **buffer);
int attach_buffer(MessageBuffer **buffer);
int detach_buffer();
int destroy_buffer();
int produce(MessageBuffer **buffer, int sender_id, int data, int account_id);
int consume(MessageBuffer **buffer, Message **message);
