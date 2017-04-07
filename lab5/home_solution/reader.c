#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "queue.h"



int main() {
    
    int id, i;
    QTYPE data;
    void *mem_sh;
    queue *qpointer;
    
    id = shmget(22, sizeof(queue), IPC_CREAT | 0666);
    if (id == -1) {
		perror("Error creating shared memory\n");
		return EXIT_FAILURE;
    }

    mem_sh = (void *) shmat(id, NULL, 0);
    if (mem_sh == (void *)-1) {
		perror("Error shmat\n");
		return EXIT_FAILURE;
	}
	
	qpointer = (queue *)mem_sh;
	
	// CRITICAL SECTION
	pthread_mutex_lock(&qpointer->mux);
	
	while (qpointer->is_empty) 
		pthread_cond_wait(&qpointer->cv_full, &qpointer->mux);
		
		for (i = 0; i < SIZE_Q; i++) {
			data = remove_q(qpointer);
			printf("Value read: %d\n", data);
		}
		
		qpointer->is_empty = 1;
	
	pthread_mutex_unlock(&qpointer->mux);
	pthread_cond_signal(&qpointer->cv_empty);
	
    return EXIT_SUCCESS;
}
