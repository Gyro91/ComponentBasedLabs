#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <pthread.h>
#define SIZE_MEM_SHARED 24
// Reader process

int main() {
    
    int id, id_mutex, i;
    char *mem_sh, *mutex_sh;
    char *tmp;
    int ret;


    
    id_mutex = shmget(18, sizeof(pthread_mutex_t), IPC_CREAT);
    if (id_mutex == -1) {
	printf("Error creating shared memory for mutex\n");
	return 1;
    }

    mutex_sh = (void *) shmat(id_mutex, NULL, 0);
    if (*mutex_sh == -1)
	printf("Error shmat mutex\n");

    id = shmget(17, SIZE_MEM_SHARED, IPC_CREAT);
    if (id == -1) {
	printf("Error creating shared memory\n");
	return 1;
    }

    mem_sh = (void *) shmat(id, NULL, 0);
    if (*mem_sh == -1)
	printf("Error shmat\n");
    
    
    tmp = (char *) mem_sh;
    while (1) {
	pthread_mutex_lock((pthread_mutex_t *)mutex_sh);
	if (*tmp == SIZE_MEM_SHARED - 1) {
	    for (i = 1; i < (SIZE_MEM_SHARED - 1); i++)
		printf("%d\n", tmp[i]);
	    *tmp = 0;
	    
	}
	pthread_mutex_unlock((pthread_mutex_t *)mutex_sh);
    }
    
    return 0;
}
