#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdint.h>

#define SERVER_MSG ("Hello User! Welcome to my server!\n")

int main(int argc, char** argv) {
	
	int serversocket_fd = -1;
	int clientsocket_fd = -1;

	// > 1024
	int port = 9000;
	struct sockaddr_in address;
	int option = 1; 

	char buffer[1024];
	serversocket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(serversocket_fd < 0) {
		puts("This failed!");
		exit(1);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	setsockopt(serversocket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(int));

	if(bind(serversocket_fd, (struct sockaddr*) &address, sizeof(struct sockaddr_in))) {
		puts("This broke! :(");
		exit(1);
	}

	listen(serversocket_fd, 4);
	while(1) {
		uint32_t addrlen = sizeof(struct sockaddr_in);
		clientsocket_fd = accept(serversocket_fd, (struct sockaddr*) &address, &addrlen);
		pid_t p = fork();

		if(p == 0) {
			read(clientsocket_fd, buffer, 1024);
			puts(buffer);
			write(clientsocket_fd, SERVER_MSG, strlen(SERVER_MSG)+1); 

			close(clientsocket_fd);
			exit(1);
		}
	}
	close(serversocket_fd);
	return 0;
}
