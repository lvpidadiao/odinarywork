#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#define SEGMENT_ID 100861

int main()
{
    int segment_id = 0;

    char *shared_memory = NULL;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size = 0x6400;

    segment_id = shmget(SEGMENT_ID, getpagesize(), IPC_CREAT | S_IRUSR | S_IWUSR);

    printf("the segment_id is %d\n", segment_id);

    shared_memory = (char *)shmat(segment_id, 0, 0);

    if (*shared_memory != -1) {
	printf("ths string is %s", shared_memory);
    }
    else {
	printf("err occur.\n");
    }

    shmdt(shared_memory);
    return 0;
}
