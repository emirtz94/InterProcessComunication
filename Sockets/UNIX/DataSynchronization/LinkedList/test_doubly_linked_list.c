#include<stdio.h>
#include<stdlib.h>
#include"doubly_linked_list.h"

dll_node_t *find(dll_t *dll, int n) {
	dll_node_t *node = dll->head->next;
	while(node != dll->head) {
		if(*((int *) node->data) == n) {
			return node;
		}

		node = node->next;
	}

	
}

void print(dll_t *dll) {
    printf("Printing...\n");
    dll_node_t *node = dll->head->next;
    while (node != dll->head) {
        printf("%i\n", *((int *) node->data));
        node = node->next;
    }
}


int main() {
	dll_t *dll = init_dll();
	
	for(int i = 0; i < 5; i++) {
		int *n = malloc(sizeof(int));
		*n = i;
		append(dll, n);
	}
	print(dll);
	del(dll, find(dll, 3));
	print(dll);
}
