#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#define SEGMENT_ID 100861

int main()
{
    int segment_id = 0;

    char * shared_memory = NULL;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size = 0x6400;

    segment_id = shmget(SEGMENT_ID, getpagesize(), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    shared_memory = (char *)shmat(segment_id, 0, 0);
    printf("shared memory attached at address %p, the id is %d\n", shared_memory, segment_id);
    shmctl(segment_id, IPC_STAT, &shmbuffer);
    segment_size = shmbuffer.shm_segsz;
    printf("segment size: %d\n", segment_size);
    sprintf(shared_memory, "Hello, Shared Memory.\n");
    shmdt(shared_memory);

    sleep(30);
    
    shmctl(segment_id, IPC_RMID, 0);
    return 0;
}
