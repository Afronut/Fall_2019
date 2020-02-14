#ifndef SERVICE_H
#define SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <linux/unistd.h>
typedef struct file
{
    const char *file_name;
    int(*rev_id);
    int(*req_id);
} file_t;

typedef struct argument
{
    Node **head;
    Node **tail;
    file_t **file_name;
    FILE *rev_log;
    FILE *req_log;
    FILE *res_log;
    FILE *perf_log;
    int num_file;
    int *counter;
    pthread_mutex_t *mutex_head;
    pthread_mutex_t *mutex_tail;
    pthread_mutex_t *mutex_revlog;
    pthread_mutex_t *mutex_reqlog;
    pthread_cond_t *cond_wait;
} argument_t;

void *resolver(void *);

void *requester(void *);

#endif
