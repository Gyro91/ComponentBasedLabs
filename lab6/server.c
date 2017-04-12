#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <mqueue.h>

int main()
{
	char *buffer_name = "/Server6";
	char buffer_server;
	struct mq_attr attr;
	int ret;
	mqd_t fd;
	
	
	attr.mq_flags = 0;
	attr.mq_maxmsg =  10;
	attr.mq_msgsize = 1;
	attr.mq_curmsgs = 0;
	
	fd = mq_open(buffer_name, O_CREAT | O_RDWR, 0666, &attr);
	if (fd < 0) {
		perror("Error creating memory queue\n");
		return EXIT_FAILURE;
	}
	
	ret = mq_receive(fd, &buffer_server, 1, NULL);
	if (ret < 0) {
		perror("Error mq_receive");
		return EXIT_FAILURE;
	}
	printf("Client %d\n", buffer_server);
	
	buffer_server++;
	
	ret = mq_send(fd, &buffer_server, 1, 0);
	if (ret < 0) {
		perror("Error mq_receive");
		return EXIT_FAILURE;
	}
	
	mq_close(fd);
	
	return EXIT_SUCCESS;
}
