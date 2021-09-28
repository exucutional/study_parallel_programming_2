#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NDEBUG

#ifndef NDEBUG
#define DEBUG(cmd) cmd;
#else
#define DEBUG(cmd) ;
#endif


int main(int argc, char** argv)
{
    int max_thread = omp_get_max_threads();
    int n = 5;
    int sum = 0;
    if (argc == 2)
    {
        n = atoi(argv[1]);
    }
    #pragma omp parallel for schedule(static) reduction(+:sum)
    for (int i = 1; i <= n; i++)
    {
        DEBUG(
        int thread_id = omp_get_thread_num();
        printf("[Thread %.2d] Add %d\n", thread_id, i);
        )
        sum += i;
    }
    printf("Sum of the first %d numbers is %d", n, sum);
    return 0;
}
