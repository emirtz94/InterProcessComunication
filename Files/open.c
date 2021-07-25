#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main() {
	int file_descriptor, close_status, size;
	char filename[255];
	char *content = (char *)calloc(1000, sizeof(char));	

	printf("Enter the filename: ");
	scanf("%s", filename);

	file_descriptor = open(filename, O_RDONLY);

	if(file_descriptor != -1) {
		printf("%s Opened successfully!\n", filename);
	} else {
		printf("Unable to open %s\n", filename);
	}

	size = read(file_descriptor, content, 1000);

	printf("Number of bytes returned are: %d\n", size);

	content[999] = '\0';

	printf("File content: %s\n", content);
	
	close_status = close(file_descriptor);

	if(close_status == 0) {
 		printf("File Descriptor is closed Successfully\n");
 	} else {
 		printf("File Descriptor is not closed\n");
 	}
	return 0;
}
