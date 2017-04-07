#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define SIZE_MEM_SHARED 24

pthread_mutex_t mux;
pthread_mutexattr_t matt;

// Writer process

int main() {
    
    int id, id_mutex, i;
    char val = 0;
    char *mem_sh, *mutex_sh;
    char *tmp;
    int ret;

    pthread_mutexattr_init(&matt);
    ret = pthread_mutexattr_setpshared(&matt, PTHREAD_PROCESS_SHARED);
    if (ret != 0) {
	printf("Error setpshared\n");
    }

    tmp = (char *) &mux;
    
    ret =  pthread_mutex_init(&mux, &matt);
    if (ret != 0) {
	printf("Error setpshared\n");
    }

    
    id_mutex = shmget(18, sizeof(mux), IPC_CREAT);
    if (id_mutex == -1) {
	printf("Error creating shared memory for mutex\n");
	return 1;
    }

    mutex_sh = (void *) shmat(id_mutex, NULL, 0);
    if (*mutex_sh == -1)
	printf("Error shmat mutex\n");

    mutex_sh = (char *) mutex_sh;
    for (i = 0; i < sizeof(mux); i++)
	mutex_sh[i] = tmp[i];
   
    id = shmget(17, SIZE_MEM_SHARED, IPC_CREAT);
    if (id == -1) {
	printf("Error creating shared memory\n");
	return 1;
    }

    mem_sh = (void *) shmat(id, NULL, 0);
    if (*mem_sh == -1)
	printf("Error shmat\n");


    pthread_mutex_lock((pthread_mutex_t *)mutex_sh);
    *(char *)mem_sh = 0;
    pthread_mutex_unlock((pthread_mutex_t *)mutex_sh);


    while (1) {
	pthread_mutex_lock((pthread_mutex_t *)mutex_sh);

	sleep(1);

	tmp = (char *) mem_sh;
    
	if (*tmp == 0) {
	    for (i = 1; i < SIZE_MEM_SHARED; i++) {
		tmp[i] = val;
		val++;
		if (val > 100)
		    val = 0;
	    }

	    *tmp = SIZE_MEM_SHARED - 1;
	}
	pthread_mutex_unlock((pthread_mutex_t *)mutex_sh);
    }
    
    return 0;
}
