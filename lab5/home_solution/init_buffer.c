#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"



int main() {
	
	int ret, id;
	pthread_mutexattr_t mux_att;
	pthread_condattr_t attrcond;
	queue q;
	void *mem_sh;
	
	pthread_mutexattr_init(&mux_att);
    ret = pthread_mutexattr_setpshared(&mux_att, PTHREAD_PROCESS_SHARED);
    if (ret != 0) {
		perror("Error setpshared\n");
		return EXIT_FAILURE;
    }

    ret =  pthread_mutex_init(&q.mux, &mux_att);
    if (ret != 0) {
		perror("Error mutex init\n");
		return EXIT_FAILURE;
    }
    
    pthread_condattr_init(&attrcond);
    pthread_condattr_setpshared(&attrcond, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&q.cv_full, &attrcond);
    pthread_cond_init(&q.cv_empty, &attrcond);
    
    // Initializing the queue
    init_q(&q);
    
    
    // Creating Shared Memory
	id = shmget(22, sizeof(q), IPC_CREAT | 0666);
    if (id == -1) {
		perror("Error creating shared memory\n");
		return EXIT_FAILURE;
    }

    mem_sh = (void *) shmat(id, NULL, 0);
    if (mem_sh == (void *)-1) {
		perror("Error shmat\n");
		return EXIT_FAILURE;
	}
    
    memcpy(mem_sh, &q, sizeof(q));
    
	
	return EXIT_SUCCESS;
}
