#include<stdio.h>
#include<stdlib.h>
#include"doubly_linked_list.h"

dll_t *init_dll() {
	dll_t *dll = calloc(1, sizeof(dll_t));
	dll_node_t *node = calloc(1, sizeof(dll_t));
	
	node->next = node;
	node->prev = node;
	
	dll->head = node;
	dll->tail = node;
	
	return dll;
}

void append(dll_t *dll, void *data) {
	dll_node_t *head = dll->head;
	dll_node_t *node = calloc(1, sizeof(dll_node_t));

	node->data = data;
	node->next = dll->head;
	node->prev = dll->tail;

	dll->head->prev = node;
	dll->tail->next = node;
	dll->tail = node;

	if(dll->head != head) {
		printf("Something went wrong...\n");
	}
}

void del(dll_t *dll, dll_node_t *node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;

	if(node == dll->tail) {
		dll->tail = node->prev;
	}	
	free(node);
}

void deinit_dll(dll_t *dll) {
	dll_node_t *node = dll->head->next;
	
	while(node != dll->head) {
		dll_node_t *next = node->next;
		del(dll, node);
		node = next;
	}
	
	free(dll);
}

dll_node_t *find(dll_t *dll, int n) {
	dll_node_t *node = dll->head->next;
	
	while(node != dll->head) {
		if(*((int *) node->data) == n) {
			return node;
		}
		
		node = node->next;
	}
	return node;
}

void print(dll_t *dll) {
	dll_node_t *node = dll->head->next;
	
	while(node != dll->head) {
		printf("%i\n", *((int *) node->data));
		node = node->next;
	}
}
