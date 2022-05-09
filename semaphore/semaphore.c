#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>

#define SHM_KEY 4321
#define SEM_KEY 4321

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void s_wait(int semid) {
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf, 1) == -1) {
        printf("<s_wait> semop error!\n");
        return ;
    }
}

void s_quit(int semid) {
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf, 1) == -1) {
        printf("<s_quit> semop error!\n");
        return ;
    }
}

int main(){
    int shmid;
    int *num;
    void *memory_segment=NULL;

    int semid;
    union semun sem_union;

    // shared memory
    if ((shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT|0666)) == -1) return -1;

    printf("shmid : %d\n", shmid);

    if ((memory_segment = shmat(shmid, NULL, 0)) == (void*)-1) return -1;

    // semaphore
    if ((semid = semget(SEM_KEY, 1, IPC_CREAT|IPC_EXCL|0666)) == -1) {
        // try as a client
        if ((semid = semget(SEM_KEY, 0, 0)) == -1) return -1;
    } else {
        sem_union.val = 1;
        semctl(semid, 0, SETVAL, sem_union);
    }

    printf("semid : %d\n", semid);

    num = (int*)memory_segment;

    for (int i=0; i<1000000; i++) {
        s_wait(semid);
        (*num)++;
        s_quit(semid);
    }
    printf("num : %d\n", (*num));

    return 0;
}
