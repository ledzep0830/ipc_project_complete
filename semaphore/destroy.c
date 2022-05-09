#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(){
    int shmid;
    int *num;
    void *memory_segment=NULL;

    int semid;
    union semun sem_union;

    // shared memory
    if ((shmid = shmget(1234, sizeof(int), IPC_CREAT|0666)) == -1) return -1;

    if(shmctl(shmid, IPC_RMID, NULL) == -1) return -1;
    printf("destroy shmid : %d\n", shmid);

    if ((shmid = shmget(4321, sizeof(int), IPC_CREAT|0666)) == -1) return -1;

    if(shmctl(shmid, IPC_RMID, NULL) == -1) return -1;
    printf("destroy shmid : %d\n", shmid);

    // semaphore
    if ((semid = semget(4321, 1, IPC_CREAT|IPC_EXCL|0666)) == -1) {
        // try as a client
        if ((semid = semget(4321, 0, 0)) == -1) return -1;
    }

    if (semctl(semid, 0, IPC_RMID) == -1) return -1;
    printf("destroy semid : %d\n", semid);

    return 0;
}