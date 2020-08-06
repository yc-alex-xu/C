/*
*  clang -std=c11 -lpthread  threads.c 
*  gcc -std=c11   threads.c -lpthread
*/
/*
如果compiler 支持ansi c，使用　threads.h　即可
#if defined(__STDC_NO_THREADS) && __STDC_NO_THREADS__ == 1
#error "No threading support"
#else
#include <threads.h>
#endif
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5
void *hello(void *threadid)
{
  long tid;
  tid = (long)threadid;
  printf("Hello World! thread #%ld!\n", tid);
  sleep(1);
  pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  int rc;
  for (long t = 0; t < NUM_THREADS; t++)
  {
    rc = pthread_create(&threads[t], NULL, hello, (void *)t);
    if (rc)
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  pthread_exit(NULL);  // clean up procedure invoked
  printf("\nthe end"); // so here is unreachable
}