#include "list.h"

Node *create_node(char *host_name, const char *fl)
{
    Node *new_node = NULL;
    new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
        return NULL;
    new_node->file_name = fl;
    new_node->host_name = host_name;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->t_id = -1;
    return new_node;
}
void print_list_tail(Node *node)
{
    Node *temp = node;
    if (node == NULL)
    {
        printf("List is empty\n");
        return;
    }
    while (temp != NULL)
    {
        printf("%s, %s ,%d\n", temp->file_name, temp->host_name, temp->t_id);
        temp = temp->prev;
    }
}
void print_list_head(Node *node)
{
    Node *temp = node;
    if (node == NULL)
    {
        printf("List is empty\n");
        return;
    }
    while (temp != NULL)
    {
        printf("%s, %s ,%d\n", temp->file_name, temp->host_name, temp->t_id);
        temp = temp->next;
    }
}

void add_node_head(Node ***head, Node ***tail, char *host_name, const char *fl)
{
    char *host = (char *)malloc(1025);
    host = strncpy(host, host_name, 1025);
    Node *new_node = create_node(host, fl);
    if (**head == NULL)
    {
        **head = new_node;
        **tail = **head;
        return;
    }

    (**head)->prev = new_node;
    new_node->next = (**head);
    (**head) = new_node;
}

void destroy_list(Node *node)
{
    if (node == NULL)
        node = node->next;
    while (node != NULL)
    {

        Node *temp = node;
        // printf("%d\n", prev_is_null(node));
        node = (node)->next;
        free(temp->host_name);
        free(temp);
        temp = NULL;
        if (node == NULL)
        {
            ;
        }
        // printf("HERE\n");
    }
}
void delete_tail(Node ***tail)
{

    if (**tail == NULL)
    {
        return;
    }
    if ((**tail)->prev == NULL || (**tail)->next == NULL)
    {
        **tail = NULL;
        return;
    }
    Node *temp;
    temp = **tail;
    (**tail)->prev->next = NULL;
    **tail = (**tail)->prev;
    free(temp->host_name);

    free(temp);
}

int next_is_null(Node *node)
{
    if (node == NULL)
        return 0;
    if (node->next == NULL)
        return 1;
    return 0;
}

int prev_is_null(Node *node)
{
    if (node->prev == NULL)
        return 1;
    return 0;
}