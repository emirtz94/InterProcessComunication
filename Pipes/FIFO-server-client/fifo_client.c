#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

#define FIFO_FILE "FIFO"

int file_descriptor;
int end_process;
int stringlen;
char message_buffer[1024];
char end_message_buffer[5];

void sendMessage() {
	while(1) {
		fgets(message_buffer, sizeof(message_buffer), stdin);
		stringlen = strlen(message_buffer);
		message_buffer[stringlen - 1] = '\0';
		end_process = strcmp(message_buffer, end_message_buffer);

		if(strcmp(message_buffer, "end") == 0){
			printf("FIFO PIPE is done with sending the data.\n");
			close(file_descriptor);
			exit(1);
		}

		if(end_process != 0) {
			write(file_descriptor, message_buffer, strlen(message_buffer));
			printf("Sent Message: %s\n", message_buffer);
			
		} else {
			write(file_descriptor, message_buffer, strlen(message_buffer));
			printf("Sent Message: %s\n", message_buffer);
			close(file_descriptor);
			break;
		}
	}
}


int main() {
	printf("FIFO CLIENT is ready to send the messages to server.\n");
	printf("Enter lines of text, enter \'end\' to quit:\n");

	file_descriptor = open(FIFO_FILE, O_CREAT | O_WRONLY);
	
	sendMessage();

	return 0;
}
