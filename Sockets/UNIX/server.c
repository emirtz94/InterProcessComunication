#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>

#define SOCKET_NAME "/tmp/DemoSocket"
#define BUFFER_SIZE 128

int main() {
	/*The socket address specifies the family of the communication facility and the communication media.  The Unix domain socket address structure 
	sockaddr_un is defined in <sys/un.h>.*/
	struct sockaddr_un name;

	#if 0
	struct sockaddr_un {
		sa_family_t sun_family;
		char sun_path[108];
	};	
	#endif

	int ret;
	int connection_socket;
	int data_socket;
	int result;
	int data;
	char buffer[BUFFER_SIZE];

    	/*In case the program exited inadvertently on the last run,
     	*remove the socket.
     	**/
	unlink(SOCKET_NAME);
	
	/*
	The socket() function creates an endpoint for communication and returns a socket descriptor representing the endpoint. 
	Different types of sockets provide different communication services.
	*/
	connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);

	if(connection_socket == -1) {
		/* The perror() function produces a message on standard error
      		describing the last error encountered during a call to a system
       		or library function.*/
		perror("socket");
		exit(EXIT_FAILURE);
	}

	printf("Master socket created.\n");

	/*
	void *memset(void *str, int c, size_t n) - copies the character c (an unsigned char) to the first n characters of the string pointed to, 
						   by the argument str.

	str − This is a pointer to the block of memory to fill.

	c − This is the value to be set. The value is passed as an int, 
	but the function fills the block of memory using the unsigned char conversion of this value.

	n − This is the number of bytes to be set to the value.
	*/
	memset(&name, 0, sizeof(struct sockaddr_un));
	name.sun_family = AF_UNIX;
	
	strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);

	/*
	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	
	When a socket is created with socket(), it exists in a name
       	space (address family) but has no address assigned to it.  bind()
       	assigns the address specified by addr to the socket referred to
       	by the file descriptor sockfd.  addrlen specifies the size, in
       	bytes, of the address structure pointed to by addr.
       	Traditionally, this operation is called “assigning a name to a
       	socket”.
	*/
	ret = bind(connection_socket, (const struct sockaddr *) &name, sizeof(struct sockaddr_un));

	if(ret == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	while(1) {
		printf("Waiting on accept() sys call\n");
		/*
		int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
		
		The accept() system call is used with connection-based socket
       		types (SOCK_STREAM, SOCK_SEQPACKET).  It extracts the first
      	 	connection request on the queue of pending connections for the
       		listening socket, sockfd, creates a new connected socket, and
      		returns a new file descriptor referring to that socket.  The
       		newly created socket is not in the listening state.  The original
       		socket sockfd is unaffected by this call.

		*/

		data_socket = accept(connection_socket, NULL, NULL);		
		if(data_socket == -1) {
			perror("accept");
			exit(EXIT_FAILURE);
		}

		printf("Connection accepted from the client\n");

		result = 0;

		while(1) {
			memset(buffer, 0, BUFFER_SIZE);
			
			printf("Waiting for data from the client\n");

			/*
			ssize_t read(int fd, void *buf, size_t count);
			
   		        read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.

       			On files that support seeking, the read operation commences at
     			the file offset, and the file offset is incremented by the number
       			of bytes read.  If the file offset is at or past the end of file,
       			no bytes are read, and read() returns zero.

       			If count is zero, read() may detect the errors described below.
       			In the absence of any errors, or if read() does not check for
       			errors, a read() with a count of 0 returns zero and has no other effects.
			*/
			ret = read(data_socket, buffer, BUFFER_SIZE);
			
			if(ret == -1) {
				perror("read");
				exit(EXIT_FAILURE);
			}
			memcpy(&data, buffer, sizeof(int));
			if(data == 0)
				break;
			result += data;
		}
		
		memset(buffer, 0, BUFFER_SIZE);
		sprintf(buffer, "Result = %d", result);
		printf("Sending final result back to client\n");
		
		/*
		ssize_t write(int fd, const void *buf, size_t count);
		
		write() writes up to count bytes from the buffer starting at buf
       		to the file referred to by the file descriptor fd.
		
		*/
		ret = write(data_socket, buffer, BUFFER_SIZE);
		
		if(ret == -1) {
			perror("write");
			exit(EXIT_FAILURE);
		}

		close(data_socket);
	}

	close(connection_socket);
	unlink(SOCKET_NAME);
	exit(EXIT_SUCCESS);
}

