#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"routing-table.h"
#include"./LinkedList/doubly_linked_list.h"

void display_routing_table(const dll_t *routing_table) {
	printf("Printing routing table: \n");
	
	dll_node_t *node = routing_table->head->next;
	while(node != routing_table->head) {
		routing_table_entry_t entry = *((routing_table_entry_t *) node->data);
		printf("Destination IP: %s Mask: %u Gateway IP: %s OIF: %s\n", entry.dest, entry.mask, entry.gw, entry.oif);
		node = node->next;
	}
}

dll_node_t *find_routing_table_entry(const dll_t *routing_table, const char *dest, const unsigned short mask) {
	
}
