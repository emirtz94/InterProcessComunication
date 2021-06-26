#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include<unistd.h>

#define SERVER_PATH "tpf_unix_sock.server"
#define DATA "Hello from client\n"

int main() {
	int client_socket, rc;
	struct sockaddr_un remote;
	char buf[256];
	
	memset(&remote, 0, sizeof(struct sockaddr_un));

	client_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(client_socket == -1) {
	        perror("socket");
	        exit(1);
	}
	
	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SERVER_PATH);
	
	strcpy(buf, DATA);
	printf("Sending data...\n");
	
	rc = sendto(client_socket, buf, strlen(buf), 0, (struct sockaddr *) &remote, sizeof(remote));
	if(rc == -1) {
	        perror("sendto");
        	close(client_socket);
		exit(1);
	}

	printf("Data sent!\n");

	rc = close(client_socket);
	
	return 0;
}
