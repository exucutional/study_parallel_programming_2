/******************************************************************************
* ЗАДАНИЕ: bugged6.c
* ОПИСАНИЕ:
*   Множественные ошибки компиляции
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define VECLEN 100

float a[VECLEN], b[VECLEN];

float dotprod()
{
    int i, tid;
    float sum;

    tid = omp_get_thread_num();
    // Reduction нужен в верхнем omp paralle
    //#pragma omp for reduction(+:sum)
    #pragma omp for
    for (i = 0; i < VECLEN; i++)
    {
        sum = sum + (a[i] * b[i]);
        printf("  tid= %d i=%d\n", tid, i);
    }
    // Надо вернуть значение
    return sum;
}


int main (int argc, char *argv[])
{
    int i;
    float sum;

    for (i = 0; i < VECLEN; i++)
        a[i] = b[i] = 1.0 * i;
    sum = 0.0;

    // Уберем shared и добавим reduction чтобы складывать результаты вызовов dotprod в разных потоках
    //#pragma omp parallel shared(sum)
    #pragma omp parallel reduction(+:sum)
        sum = dotprod();

    printf("Sum = %f\n",sum);
}


