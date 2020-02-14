#include "sync.h"

void set_arg(file_t *file[], int len, char const *argv[])
{
    int array[100];
    for (size_t i = 0; i < 100; i++)
    {
        array[i] = -1;
    }
    for (size_t i = 0; i < (size_t)len; i++)
    {
        // printf("%s\n", argv[i + 5]);
        file_t *new_node;
        new_node = (file_t *)malloc(sizeof(file_t));
        file[i] = new_node;
        file[i]->file_name = argv[i + 5];
        file[i]->req_id = array;
        file[i]->rev_id = array;
    }
    // printf("%d\n", strlen(file));
}