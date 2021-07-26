#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>

#define BUFFER_SIZE 1024

int pipefds[2];
int status, pid;

char writemessage[BUFFER_SIZE];
char readmessage[BUFFER_SIZE];

void pipeOperation() {
	pid = fork();

	if(pid == 0) {
		read(pipefds[0], readmessage, sizeof(readmessage));
		printf("Child process: Reading from pipe - Message is %s", readmessage);
		
	} else {
		printf("Parent process: Writing to pipe - Message is %s", writemessage);
		write(pipefds[1], writemessage, sizeof(writemessage));
	}
}

int main() {
	status = pipe(pipefds);
	
	if(status == -1) {
		printf("Unable to create pipe\n");
		return 1;
	}

	printf("Enter the message to write into Pipe\n");
	printf("To exit type \"quit\" \n");

	fgets(writemessage, BUFSIZ, stdin);

	while(strcmp(writemessage, "quit\n") != 0) {
		pipeOperation();
		fgets(writemessage, BUFSIZ, stdin);
		kill(pid, SIGKILL);
	}
	return 0;
}
