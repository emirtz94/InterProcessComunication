#ifndef ROUTING_TABLE_H
#define ROUTING_TABLE_H

#define IP_ADDR_LEN 16
#define OIF_LEN 32

typedef struct dll dll_t;
typedef struct dll_node dll_node_t;

typedef struct routing_table_entry {
	char dest[IP_ADDR_LEN];
	unsigned short mask;
	char gw[IP_ADDR_LEN];
	char oif[OIF_LEN];
} routing_table_entry_t;

void display_routing_table(const dll_t *routing_table);
dll_node_t *find_routing_table_entry(const dll_t *routing_table, const char *dest, const unsigned short mask);
void update(dll_node_t *node, const char *gw, const char *oif);

#endif
