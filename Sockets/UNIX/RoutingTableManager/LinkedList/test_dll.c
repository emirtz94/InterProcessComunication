#include<stdio.h>
#include<stdlib.h>
#include "doubly_linked_list.h"

int main() {
	dll_t *dll = init_dll();
	
	for(int i = 0; i < 5; i++) {
		int *n = malloc(sizeof(int));
		*n = i;
		append(dll, n);
	}
	
	printf("Elements of list: \n");
	print(dll);
	
	for(int i = 0; i < 5; i++) {
		if(find(dll, i) != dll->head) {
			printf("Correct\n");
		}
	}

	del(dll, find(dll, 3));
	
	printf("Elements of list: \n");
	print(dll);

	return 0;
}
