#include "service.h"
#include "util.h"
#include <unistd.h>

void *requester(void *arg)
{
    argument_t *args = (argument_t *)arg; // cast void var
    int len = args->num_file;             // total num of file to process
    int **i = &args->counter;             // a shared counter
    while (**i < len)
    {
        ///////////////////////////////////////////
        // Thread Grab a file and wait/proceed ////
        ///////////////////////////////////////////
        pthread_mutex_lock(args->mutex_reqlog); // lock head of queue
        if (**i > len - 1)                      // if get cut up with all file already served. exit
        {
            fprintf(args->req_log, "%d All file was served: ", (int)pthread_self());
            fprintf(args->req_log, "\n");
            pthread_mutex_unlock(args->mutex_reqlog); //unlock mutex
            break;
        }
        const char *fl = args->file_name[**i]->file_name;
        fprintf(args->req_log, "%d servicing: ", (int)pthread_self());
        fprintf(args->req_log, "%s; ", args->file_name[**i]->file_name);
        fprintf(args->req_log, "\n");
        fprintf(args->perf_log, "%d servicing: ", (int)pthread_self());
        fprintf(args->perf_log, "%s; ", args->file_name[**i]->file_name);
        fprintf(args->perf_log, "\n");
        **i = **i + 1;
        ///////////////////////////////////////////
        //     Thread wait/Queue hostname /////////
        ///////////////////////////////////////////
        pthread_mutex_lock(args->mutex_head);
        FILE *fd = fopen(fl, "r");
        if (fd == NULL){
            fprintf(args->req_log,"Thread %d Can not open files %s\n", (int)pthread_self(),fl);
            pthread_mutex_unlock(args->mutex_head);
            pthread_mutex_unlock(args->mutex_reqlog);
            break;
        }
        else{
            char host_name[1024]; // hostname length
            while (fscanf(fd, "%s\n", host_name) != EOF)
            {
                add_node_head(&args->head, &args->tail, host_name, fl);
            }
            pthread_mutex_unlock(args->mutex_reqlog);
            sleep(0.001);
        }
        pthread_mutex_unlock(args->mutex_head);
    }
    return NULL;
}

void *resolver(void *arg)
{
    argument_t *args = (argument_t *)arg; //cast argument from void*
    while (*args->counter <= args->num_file/2)
    {
        // wait for the requester to queue in all host names;
    }
    while (*args->tail != NULL) // loop over the queue for ip look up
    {
        ///////////////////////////////////////////
        // Thread Grab a node and wait/proceed ////
        ///////////////////////////////////////////
        pthread_mutex_lock(args->mutex_tail); //lock the queue
        if ((*args->tail) == NULL)
        {
            pthread_mutex_unlock(args->mutex_tail); //unlock the queue if queue is empty
            break;
        }
        Node *temp = *args->tail;
        *args->tail = (*args->tail)->prev;      //Move to the next node
        //////////////////////////////////////////
        // Thread wait/proceed to loopup ip  ////
        ///////////////////////////////////////////
        char *host_name = (char *)malloc(1025);
        host_name = strncpy(host_name, temp->host_name, 1025); //copy hostname
        char ip[INET6_ADDRSTRLEN];                             //Typical ip len
        int ret = dnslookup(host_name, ip, sizeof(ip));        // loop up for the ip
        pthread_mutex_unlock(args->mutex_tail); //unlock  mutex
        pthread_mutex_lock(args->mutex_revlog);
        if (ret == -1)
        {
            fprintf(args->res_log, "%d, %s, %s\n", (int)pthread_self(), host_name, "IP can not be resolved");
            fprintf(stdout, "\n");
        }
        else
            fprintf(args->res_log, "%d, %s, %s\n", (int)pthread_self(), host_name, ip); //write ip and hostname to file
        free(host_name);
        pthread_mutex_unlock(args->mutex_revlog);
        sleep(0.001);
        //release memory
    }
    return NULL;
}
