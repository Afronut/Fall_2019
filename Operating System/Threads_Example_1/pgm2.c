#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#define MYSTACKSIZE 40960

void *odd(void *max)
{
  int i;
  struct timeval tp;

  for (i = 1; i < *(int *)max; i+=2){
    printf("odd %d\n", i);
    sleep(1);
  }
}

void *even(void *max)
{
  int i;
  struct timeval tp;
 
  for (i = 0; i < *(int *)max; i+=2) {
    printf("even %d\n", i);
    sleep(1);
  }
}

void main()
{
  int max = 5, max1 = 10, max2 = 20, i;
  pthread_attr_t attr;
  pthread_t *th1, *th2;
  void *st1, *st2;
  size_t sz;
  int policy;
  struct timeval tp;

  pthread_attr_init(&attr);
  st1 = (void *) malloc(MYSTACKSIZE);
  pthread_attr_setstacksize(&attr, MYSTACKSIZE);
  pthread_attr_setstack(&attr, st1, MYSTACKSIZE);

  pthread_attr_getstacksize(&attr, &sz);

  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
  pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

  th1 = (pthread_t *) malloc(sizeof(pthread_t));
  if (pthread_create(th1, &attr, odd, &max1)) {
    perror("error creating the first thread");
    exit(1);
  }
  printf("created the first thread\n");
 
  st2 = (void *)malloc(MYSTACKSIZE);
  pthread_attr_setstacksize(&attr, MYSTACKSIZE);
  pthread_attr_setstack(&attr, st2, MYSTACKSIZE);
  th2 = (pthread_t *) malloc(sizeof(pthread_t));
  if (pthread_create(th2, &attr, even, &max2)) {
    perror("error creating the second thread");
    exit(1);
  }
  printf("created the second thread\n");

  for (i = 0; i < max; i++) {
    printf("main %d\n", i);
    sleep(1);
  }
  pthread_join(*th1, 0);
  //pthread_join(*th2, 0);
}
