#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

static void ctrlc_signal_handler(int sig) {
	printf("Ctrl-C pressed\n");
    	printf("Bye Bye\n");
    	exit(0);
}

static void abort_signal_handler(int sig) {
	printf("process is aborted\n");
    	printf("Bye Bye\n");
    	exit(0);
}

int main() {
	signal(SIGINT, ctrlc_signal_handler);
	signal(SIGABRT, abort_signal_handler);
	char ch;
	printf("Abort process (y/n) ?\n");
	scanf("%c",&ch);

	if(ch == 'y') {
		abort();
	}

	return 0;
}
