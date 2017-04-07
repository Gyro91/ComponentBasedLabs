#include "queue.h"

void init_q(queue *q)
{
	q->front = q->rear = 0;
	q->is_empty = 1;
}

int is_full(queue *q)
{
	if (q->front == ((q->rear + 1) % SIZE_Q))
		return 1;
	else 
		return 0;
}

int is_empty(queue *q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

void insert_q(QTYPE data, queue *q) 
{
	q->buffer[q->rear] = data;
	q->rear = (q->rear + 1) % SIZE_Q;
} 

QTYPE remove_q(queue *q)
{
	QTYPE data = q->buffer[q->front];
	q->front = (q->front + 1) % SIZE_Q;
	
	return data;
}
