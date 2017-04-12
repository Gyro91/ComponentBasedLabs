#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "msg.h"

int main()
{
	char *buffer_name = "/Server7";
	message msg_t;
	struct mq_attr attr;
	int ret;
	mqd_t fd;
	
	
	attr.mq_flags = 0;
	attr.mq_maxmsg =  10;
	attr.mq_msgsize = sizeof(msg_t);
	attr.mq_curmsgs = 0;
	
	fd = mq_open(buffer_name, O_CREAT | O_RDWR, 0666, &attr);
	if (fd < 0) {
		perror("Error creating memory queue\n");
		return EXIT_FAILURE;
	}
	
	ret = mq_receive(fd, (char *)&msg_t, sizeof(msg_t), NULL);
	if (ret < 0) {
		perror("Error mq_receive");
		return EXIT_FAILURE;
	}
	
	printf("Client %d %d\n", msg_t.a, msg_t.b);
	
	msg_t.ret = msg_t.a + msg_t.b;
	
	ret = mq_send(fd, (char *)&msg_t, sizeof(msg_t), 0);
	if (ret < 0) {
		perror("Error mq_receive");
		return EXIT_FAILURE;
	}
	
	mq_close(fd);
	
	return EXIT_SUCCESS;
}
