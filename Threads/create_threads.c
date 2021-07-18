#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *customThreadFunction() {
	for(int i = 0; i < 15; i++) {
		printf("I am a Custom Thread Function Created By Programer.\n");		
		sleep(1);
		
		if(i == 3) {
			printf("My JOB is done. I am being terminated by programer.\n");
			pthread_exit(NULL);
		}
	}

	return NULL;
}

int main() {
	pthread_t thread;
	int status = pthread_create(&thread, NULL, customThreadFunction, NULL);

	if(!status) {
		printf("Custom Thread Created Successfully.\n");
	} else {
		printf("Unable to create the Custom Thread.\n");
		return 0;
	}

	for(int i = 0; i < 15; i++) {
		printf("I am the process thread created by compiler by default.\n");
		sleep(1);
	}	

	return 0;
}
