#include "service.h"
#include "sync.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{
    clock_t t;
    t = clock();
    if (argc < 5)
    {
        printf("Input argument must at least 6\n");
        return EXIT_FAILURE;
    }
    int num_input_file = argc - 5;
    if (num_input_file == 0)
    {
        printf("Seems like you have not entered any file\n");
        return EXIT_FAILURE;
    }

    Node *head = NULL;
    Node *tail = NULL;
    char *ptr;
    int requesters = (int)strtol(argv[1], &ptr, 10);
    int resolvers = (int)strtol(argv[2], &ptr, 10);
    if (requesters <= 0 || resolvers <= 0)
    {
        printf("Number of thread to create must be integer and greater than zero.\n");
        printf("You entered %s, %s for req_thread and rev_thread respectively. Review those values\n", argv[1], argv[2]);
        return EXIT_FAILURE;
    }
    // printf("%d, %d\n", requesters, resolvers);
    pthread_t *request_th;
    pthread_t *resolve_th;
    request_th = malloc(requesters * sizeof(pthread_t));
    resolve_th = malloc(resolvers * sizeof(pthread_t));

    FILE *requesters_log, *resolvers_log, *result_log, *perf_log;
    fprintf(stdout, "\n");
    printf("Counting a total of %d file to process\n", num_input_file);
    fprintf(stdout, "\n");
    file_t *files[num_input_file];
    // printf("here\n");
    resolvers_log = fopen(argv[4], "w");
    if (resolvers_log == NULL)
    {
        printf("Can not open log file provided. Using resolver_log.txt instead\n");
        resolvers_log = fopen("resolver_log.txt", "w");
    }
    requesters_log = fopen(argv[3], "w");
    // printf("%s %s\n", argv[3], argv[4]);
    if (requesters_log == NULL)
    {
        printf("Can not open log file provided. Using requester_log.txt instead\n");
        requesters_log = fopen("requester_log.txt", "w");
    }
    result_log = fopen("results.txt", "w");
    perf_log = fopen("performance.txt", "a");
    fprintf(perf_log, "Number for requester thread=%d\n", requesters);
    fprintf(perf_log, "Number for resolver thread=%d\n", resolvers);
    fprintf(result_log, "%s\n", "Thread_ID      HOSTNAME     IP_Adress\n");

    ///////////////////////////////////////////
    // Create MUTEX  and Initialize  //////////
    ///////////////////////////////////////////
    pthread_mutex_t mutex_head;
    pthread_mutex_t mutex_tail;
    pthread_mutex_t mutex_revlog;
    pthread_mutex_t mutex_reqlog;
    pthread_cond_t cond_wait;

    pthread_mutex_init(&mutex_head, NULL);
    pthread_mutex_init(&mutex_tail, NULL);
    pthread_mutex_init(&mutex_reqlog, NULL);
    pthread_mutex_init(&mutex_revlog, NULL);
    pthread_cond_init(&cond_wait, NULL);

    ///////////////////////////////////////////
    // Set Thread Arguments/////////////// ////
    ///////////////////////////////////////////
    set_arg(files, num_input_file, argv);
    argument_t *args;
    int var = 0;
    args = (argument_t *)malloc(sizeof(argument_t));
    args->file_name = files;
    args->rev_log = resolvers_log;
    args->req_log = requesters_log;
    args->res_log = result_log;
    args->perf_log = perf_log;
    args->head = &head;
    args->tail = &tail;
    args->num_file = num_input_file;
    args->mutex_head = &mutex_head;
    args->mutex_tail = &mutex_tail;
    args->mutex_reqlog = &mutex_reqlog;
    args->mutex_revlog = &mutex_revlog;
    args->counter = &var;

    ///////////////////////////////////////////
    // Generate Requester Threads  /////// ////
    ///////////////////////////////////////////
    for (size_t j = 0; j < (size_t)requesters; j++)
    {
        int error = pthread_create(&(request_th[j]), NULL, requester, (void *)args);
        if (error != 0)
        {
            pthread_mutex_lock(args->mutex_reqlog);
            fprintf(requesters_log, "Thread can not be created\n");
            pthread_mutex_unlock(args->mutex_reqlog);
        }
    }

    ///////////////////////////////////////////
    // Generate resolver Threads////////// ////
    ///////////////////////////////////////////
    for (size_t j = 0; j < (size_t)resolvers; j++)
    {
        int error = pthread_create(&(resolve_th[j]), NULL, resolver, (void *)args);
        if (error != 0)
        {
            pthread_mutex_lock(args->mutex_revlog);
            fprintf(resolvers_log, "Thread can not be created\n");
            pthread_mutex_unlock(args->mutex_revlog);
        }
    }

    ///////////////////////////////////////////
    // Join requesters threads////////////// ////
    ///////////////////////////////////////////
    for (size_t j = 0; j < (size_t)requesters; j++)
    {
        pthread_join(request_th[j], NULL);
    }

    ///////////////////////////////////////////
    // Join resolver Threads////////////// ////
    ///////////////////////////////////////////
    for (size_t j = 0; j < (size_t)resolvers; j++)
    {
        pthread_join(resolve_th[j], NULL);
    }

    ///////////////////////////////////////////
    // close Open files///////////////////////
    ///////////////////////////////////////////
    fclose(result_log);
    fclose(resolvers_log);
    fclose(resolvers_log);
    ///////////////////////////////////////////
    // Destrot Mutex and free memories/// ////
    ///////////////////////////////////////////
    free(resolve_th);
    free(request_th);
    destroy_list(head);
    pthread_cond_destroy(&cond_wait);
    pthread_mutex_destroy(&mutex_reqlog);
    pthread_mutex_destroy(&mutex_revlog);
    pthread_mutex_destroy(&mutex_tail);
    free(args);
    for (size_t i = 0; i < (size_t)num_input_file; i++)
    {
        free(files[i]);
    }
    ///////////////////////////////////////////
    // Get Runtime And Writeup performance //////
    ///////////////////////////////////////////
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    fprintf(stdout, "\n");
    fprintf(stderr, "Multi_Thread program took: %f seconds to execute \n", time_taken);
    fprintf(perf_log, "Total run time=%fs\n", time_taken);
    fclose(perf_log);
    fprintf(stdout, "Time is measured using clock function in the main C file\n");

    return EXIT_SUCCESS;
}
