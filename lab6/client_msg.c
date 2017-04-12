#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "msg.h"

int main()
{
	char *buffer_name = "/Server7";
	message msg_t;
	int ret;
	mqd_t fd;
	
	msg_t.a = 1;
	msg_t.b = 1;
	
	fd = mq_open(buffer_name, O_CREAT | O_RDWR);
	if (fd < 0) {
		perror("Error creating memory queue\n");
		return EXIT_FAILURE;
	}
	
	printf("Sending to server %d %d\n", msg_t.a, msg_t.b);
	
	ret = mq_send(fd, (char *) &msg_t, sizeof(msg_t), 0);
	if (ret < 0) {
		perror("Error mq_receive");
		return EXIT_FAILURE;
	}
	
	printf("Receiving from the server\n");
	
	ret = mq_receive(fd, (char *)&msg_t, sizeof(msg_t), NULL);
	if (ret < 0) {
		perror("Error mq_receive");
		return EXIT_FAILURE;
	}
	
	printf("Received %d\n", msg_t.ret);
	
	mq_close(fd);
	
	return EXIT_SUCCESS;
}
