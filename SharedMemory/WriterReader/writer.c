#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main() {
	// generate unique key
	key_t key = ftok("memory", 67);
	
	int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

	if(shmid == -1) {
		printf("Unable to create Shared Memory Segment.\n");
	}

	char *str = (char *) shmat(shmid, (void *) 0, 0);
	printf("Enter data to write into the Shared Memory Segment: \n");
	scanf("%[^\n]s", str);

	printf("Data written in memory: %s\n", str);
	shmdt(str);

	return 0;
}
