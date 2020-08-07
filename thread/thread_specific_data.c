#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

void *thread_function(void *args) 
{
    static __thread char filename[30];
    /* Generate the filename for this thread’s log file. */
    sprintf(filename, "thread_%d.log", (int)pthread_self());
    printf("%s\n", filename);
    return NULL;
}

int main()
{
    int i;
    pthread_t threads[100]; //thread id will be reused if thread terminated
    //another way of TSD
    for (i = 0; i < 15; ++i)
    {
        pthread_create(&(threads[i]), NULL, thread_function, NULL);
    }
    for (i = 0; i < 15; ++i)
        pthread_join(threads[i], NULL);

    return 0;
}