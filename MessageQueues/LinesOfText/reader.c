#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct my_msgbuf {
	long mtype;
	char mtext[200];
};

int main() {
	struct my_msgbuf buf;
	int msqid;
	key_t key;

	if((key = ftok("reader", 'B')) == -1) {
		perror("ftok");
		exit(1);
	}

	if((msqid = msgget(key, 0644)) == -1) {
		perror("msgget");
		exit(1);
	}

	printf("Ready to recive messages.\n");
	
	while(1) {
		if(msgrcv(msqid, &buf, sizeof buf.mtext, 0, 0) == -1) {
			perror("msgrcv");
			exit(1);
		}

		printf("%s\n", buf.mtext);
	}

	return 0;
}
