#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NDEBUG

#ifndef NDEBUG
#define DEBUG(cmd) cmd;
#else
#define DEBUG(cmd) ;
#endif

#define N 100000 // size of array
#define n_per_line 5 // how many numbers to print per line

void init_array(double array[N])
{
    for (int i = 0; i < N; i++)
    {
        array[i] = i;
    }
}

void print_array(double array[N])
{
    for (int i = 0; i < N; i++)
    {
        printf("%.2lf ", array[i]);
        if (i % n_per_line == 0 && i != 0)
        {
            printf("\n");
        }
    }
}

int main(int argc, char** argv)
{
    double a[N] = {0}; // initial array
    double b[N] = {0}; // final array
    init_array(a);
    //printf("Initial array\n");
    //print_array(a);
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++)
    {
        DEBUG(
        int thread_id = omp_get_thread_num();
        printf("[Thread %.2d] Calculate b[%d]\n", thread_id, i);
        )
        // Let border condition to be zero
        if (i == 0 || i == N - 1)
        {
            b[i] = 0;
        }
        else
        {
            b[i] = (a[i - 1] * a[i] * a[i + 1]) / 3.0;
        }
    }
    printf("Result\n");
    print_array(b);
    return 0;
}
