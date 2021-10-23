#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NDEBUG

#ifndef NDEBUG
#define DEBUG(cmd) cmd;
#else
#define DEBUG(cmd) ;
#endif

// sin(x)_i = (-1)^i*x^(2i+1)/(2i+1)! 
double get_element(double x, u_int64_t n, double prev)
{
    if (n % 2 == 0)
    {
        return 0;
    }
    if (prev != 0)
    {
        return -prev * x * x / n / (n - 1);
    }
    double res = x;
    for (u_int64_t i = 3; i <= n; i += 2)
    {
        res *= -x * x / i / (i - 1);
    }
    return res;
}

int main(int argc, char** argv)
{
    u_int64_t n = 10; // default number of elements in range
    double x = 1; // sin argument
    double sum = 0; // result
    if (argc == 2)
    {
        n = atoi(argv[1]); // read n from cmd input
    }
    double elem = 0; // element value
    #pragma omp parallel for schedule(static) reduction(+:sum) firstprivate(elem)
    for (u_int64_t i = 0; i < n; i++)
    {
        double elem_tmp = get_element(x, i, elem);
        if (elem_tmp != 0)
        {
            elem = elem_tmp;
        }
        DEBUG(
        int thread_id = omp_get_thread_num();
        printf("[Thread %d] [%ld = %.10lf]\n", thread_id, i, elem_tmp);
        )
        sum += elem_tmp;
    }
    printf("Result sin(%.0lf) = %.20lf\n", x, sum);
    return 0;
}
