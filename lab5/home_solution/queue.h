#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <pthread.h>
#define QTYPE int
#define SIZE_Q 5

typedef struct queue {
	
	pthread_mutex_t mux;
	pthread_cond_t cv_full;
	pthread_cond_t cv_empty;
	QTYPE buffer[SIZE_Q];
	int front;
	int rear;
	char is_empty;
	
} queue;

extern void init_q(queue *);
extern void insert_q(QTYPE, queue *);
extern QTYPE remove_q(queue *);
extern int is_full(queue *);
extern int is_empty(queue *);

#endif
