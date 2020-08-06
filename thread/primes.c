/*
can be debugged via VS Code partly 
gcc -g primes.c  -lpthread -lm
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
Return the Nth prime number, where N is the value pointed to by *ARG.
*/
void *compute_prime(void *arg)
{
    //因为64位系统中，void * 已经是64bits,而int还是32bits,所以转换时会有警告
    long candidate = 2;
    int n = *((int *)arg);
    for (;;)
    {
        int factor;
        int is_prime = 1;
        int top = floor(sqrt(candidate));
        /* Test primality by successive division. */
        for (factor = 2; factor <= top; ++factor)
            if (candidate % factor == 0)
            {
                is_prime = 0;
                break;
            }
        /* Is this the prime number we’re looking for? */
        if (is_prime)
        {
            if (--n == 0)
                /* Return the desired prime number as the thread return value. */
                return (void *)candidate;
        }
        ++candidate;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread;
    int n = 5;
    if (argc == 2)
    {
        n = atoi(argv[1]);
    }

    pthread_create(&thread, NULL, &compute_prime, &n);
  
    /* Do some other work here... */
  
    /* Wait for the prime number thread to complete, and get the result. */
    void *ret; //这里void * 只是表示一下　data size
    pthread_join(thread, &ret);
    printf("The % dth prime number is %ld\n", n, (long)ret);
    return 0;
}