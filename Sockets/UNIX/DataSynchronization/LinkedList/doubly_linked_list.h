#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

typedef struct dll_node {
	void *data;
	struct dll_node *next;
	struct dll_node *prev;
} dll_node_t;

typedef struct dll {
	dll_node_t *head;
	dll_node_t *tail;	
} dll_t;

dll_t *init_dll();
void append(dll_t *dll, void *data);
void del(dll_t *dll, dll_node_t *node);
void deinit_dll(dll_t *dll);

#endif
