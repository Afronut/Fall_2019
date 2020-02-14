#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

void *odd(void *max)
{
  int i;
  FILE *fd;

  fd = fopen("odd_num", "w");
  for (i = 1; i < *(int *)max; i+= 2) {
    fprintf(fd, "%d\n", i);
    printf("odd %d\n", i);
    sleep(1);
  }
}

void *even(void *max)
{
  int i;
  FILE *fd;
 
  fd = fopen("even_num", "w");
  for (i = 0; i < *(int *)max; i+= 2) {
    fprintf(fd, "%d\n", i);
    printf("even %d\n", i);
    sleep(1);
  }
}

void main()
{
  int max = 5, max1 = 10, max2 = 10, i;
  FILE *fd;
  pthread_t *th1, *th2;

  th1 = (pthread_t *) malloc(sizeof(pthread_t));
  th2 = (pthread_t *) malloc(sizeof(pthread_t));

  if (pthread_create(th1, NULL, odd, (void *)&max1)) {
    perror("error creating the first thread");
    exit(1);
  }
  printf("Created the first thread\n");

  if (pthread_create(th2, NULL, even, (void *)&max2)) {
    perror("error creating the second thread");
    exit(1);
  }
  printf("Created the second thread\n");

  fd = fopen("whole_num", "w");
  for (i = 0; i < max; i++) {
    fprintf(fd, "%d\n", i);
    printf("main %d\n", i);
    sleep(1);
  }
  pthread_join(*th1, 0);
  pthread_join(*th2, 0);
}
