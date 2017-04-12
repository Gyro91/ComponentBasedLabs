#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>



int main() {
	
	int ret, val = 1, sckt;
	char tmp = 1;
	struct sockaddr_in addr;
	socklen_t addrlen_val = sizeof(addr);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(4321);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
	
	sckt = socket(AF_INET, SOCK_STREAM, 0);
	
	setsockopt(sckt, IPPROTO_TCP, SO_REUSEADDR, (void *)&val, sizeof(val));
	
	ret = connect(sckt, (struct sockaddr *)&addr, addrlen_val);
	if (ret < 0) {
		perror("Error connect\n");
		exit(-1);
	}
	
	printf("Sended %d\n", tmp);
	ret = send(sckt, (void *)&tmp, 1, 0);
	if (ret < 0) {
		perror("Error sending\n");
		exit(-1);
	}
	
	ret = recv(sckt, (void *)&tmp, 1, MSG_WAITALL);
	if (ret < 0) {
		perror("Error receiving\n");
		exit(-1);
	}
	
	printf("Received %d\n", tmp);
	
	close(sckt);
	
	return EXIT_SUCCESS;
}
