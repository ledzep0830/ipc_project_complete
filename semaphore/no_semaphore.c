#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHM_KEY 1234

int main(){
    int shmid;
    int *num;
    void *memory_segment=NULL;

    // shared memory
    if ((shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT|0666)) == -1) return -1;

    printf("shmid : %d\n", shmid);

    if ((memory_segment = shmat(shmid, NULL, 0)) == (void*)-1) return -1;

    num = (int*)memory_segment;

    for (int i=0; i<1000000; i++) {
        (*num)++;
    }
    printf("num : %d\n", (*num));

    return 0;
}