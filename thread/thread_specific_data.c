#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

static pthread_key_t thread_log_key;

void write_to_thread_log()
{
    char * filename = (char *)pthread_getspecific(thread_log_key);
    printf("%s \n", filename);
}

void *thread_function(void *args)
{
    char filename[30];
    FILE *thread_log;
    /* Generate the filename for this thread’s log file. */
    sprintf(filename, "thread_%d.log", (int)pthread_self());
    /* Store the file pointer in thread-specific data under thread_log_key. */
    pthread_setspecific(thread_log_key, filename);
    write_to_thread_log();
    /* Do work here... */
    return NULL;
}

void *thread_function2(void *args) //added by Alex
{
    static __thread char filename[30];
    /* Generate the filename for this thread’s log file. */
    sprintf(filename, "thread_%d.log", (int)pthread_self());
    printf("%s\n",filename);
    return NULL;
}
int main()
{
    int i;
    pthread_t threads[5]; //thread id will be reused if thread terminated

    pthread_key_create(&thread_log_key, NULL);

    for (i = 0; i < 2; ++i)
    {
        pthread_create(&(threads[i]), NULL, thread_function, NULL);
        printf("thread %lu is created !\n", threads[i]);
    }
    //another way of TSD
    for (i = 2; i < 4; ++i)
    {
        pthread_create(&(threads[i]), NULL, thread_function2, NULL);
        printf("thread %lu is created !\n", threads[i]);
    }
    for (i = 0; i < 4; ++i)
        pthread_join(threads[i], NULL);

    return 0;
}