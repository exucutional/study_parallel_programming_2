#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>

#define NDEBUG

#ifndef NDEBUG
#define DEBUG(cmd) cmd;
#else
#define DEBUG(cmd) ;
#endif

// Check if number is prime
bool is_prime(int n)
{
    DEBUG(
    int thread_id = omp_get_thread_num();
    printf("[Thread %.2d] Check number %d\n", thread_id, n);
    )
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    int n = 10; // default number of elements in range
    if (argc == 2)
    {
        n = atoi(argv[1]); // read n from cmd input
    }
    int primes_len = 0; // result
    #pragma omp parallel for schedule(static) reduction(+:primes_len)
    for (int i = 2; i <= n; i++)
    {
        if (is_prime(i))
        {
            primes_len++;
        }
    } 
    printf("The number of primes in range 1 ... %d: %d\n", n, primes_len);
    return 0;
}
