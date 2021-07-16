#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main() {
	key_t key = ftok("memory", 67);
	int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

	if(shmid == -1) {
		printf("Unable to connect with the shared memory segment.\n");
	}

	char *str = (char *) shmat(shmid, (void *) 0, 0);
	printf("Data read from memory: %s\n", str);

	shmdt(str);
	
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
