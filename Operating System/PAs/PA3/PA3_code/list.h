#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    char *host_name;
    const char *file_name;
    int t_id;
    struct node_t *next;
    struct node_t *prev;
} Node;

Node *create_node(char *, const char *);

void add_node_head(Node ***head, Node ***tail, char *, const char *);

void delete_tail(Node ***node1);
void destroy_list(Node *node);
Node *delete_head(Node *node);

int next_is_null(Node *node);

int prev_is_null(Node *node);
void print_list_head(Node *);
void print_list_tail(Node *);

#endif
