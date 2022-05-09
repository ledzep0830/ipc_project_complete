#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define KEY 1234

int main(){
    int shmid;
    int *num;
    void *memory_segment=NULL;

    if ((shmid = shmget(KEY, sizeof(int), IPC_CREAT|0666)) == -1) return -1;

    printf("shmid : %d\n", shmid);

    if ((memory_segment = shmat(shmid, NULL, 0)) == (void*)-1) return -1;

    num = (int*)memory_segment;
    (*num)++;
    printf("num : %d\n", (*num));

    if (shmctl(shmid, IPC_RMID, NULL) == -1) return -1;

    return 0;
}