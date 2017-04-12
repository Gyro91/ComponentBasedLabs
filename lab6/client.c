#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <mqueue.h>


int main()
{
	char *buffer_name = "/Server6";
	char buffer_client= 1;
	
	int ret;
	mqd_t fd;
	
	
	fd = mq_open(buffer_name, O_CREAT | O_RDWR);
	if (fd < 0) {
		perror("Error creating memory queue\n");
		return EXIT_FAILURE;
	}
	
	printf("Sending to server %d\n", buffer_client);
	
	ret = mq_send(fd, &buffer_client, 1, 0);
	if (ret < 0) {
		perror("Error mq_receive");
		return EXIT_FAILURE;
	}
	
	printf("Receiving from the server\n");
	
	ret = mq_receive(fd, &buffer_client, 1, NULL);
	if (ret < 0) {
		perror("Error mq_receive");
		return EXIT_FAILURE;
	}
	
	printf("Received %d\n", buffer_client);
	
	mq_close(fd);
	
	return EXIT_SUCCESS;
}
