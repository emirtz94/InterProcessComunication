#include<stdio.h>
#include<fcntl.h>

int main() {
	int file_descriptor;
	char filename[255];

	printf("Enter the filename: ");
	scanf("%s", filename);

	file_descriptor = creat(filename, O_RDWR | O_CREAT);

	if(file_descriptor != -1) {
		printf("File created successfully!\n");
	} else {
		printf("Unable to create the file.");
	}
	
	return 0;
}
