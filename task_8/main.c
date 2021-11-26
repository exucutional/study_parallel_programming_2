#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <assert.h>

#define N 10000// max number of elements
#define NDEBUG

#ifndef NDEBUG
#define DEBUG(cmd) cmd;
#else
#define DEBUG(cmd) ;
#endif

int read_from_file(char* filename, int* arr)
{
    FILE* fin = fopen(filename, "r");
    if (!fin)
    {
        fprintf(stderr, "ERROR: Cannot open file %s\n", filename);
        assert(fin);
    }
    int value = 0;
    int n = 0;
    while(fscanf(fin, "%d", &value) != EOF)
    {
        arr[n++] = value;
        assert(n < N);
    }
    fclose(fin);
    return n;
}

void read_from_keyboard(int n, int* arr)
{
    printf("Enter numbers: ");
    int value = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &value);
        arr[i] = value;
    }
}

void sort_task(int arr[N], int n, int low, int high)
{
    if (low < 0 || low >= high)
        return;

    DEBUG(
    int thread_id = omp_get_thread_num();
    printf("[Thread %.2d] %d %d\n", thread_id, low, high);
    )
    int pivot = arr[(high + low) / 2];
    int i = low - 1;
    int j = high + 1;
    while (true)
    {
        do {} while (arr[++i] < pivot);

        do {} while (arr[--j] > pivot);

        if (i >= j)
            break;

        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    #pragma omp task firstprivate(low, j)
        sort_task(arr, n, low, j);
    #pragma omp task firstprivate(j, high)
        sort_task(arr, n, j + 1, high);
}

void sort(int arr[N], int n, int low, int high)
{
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task firstprivate(low, high)
                sort_task(arr, n, low, high);
        }
    }
}

int main(int argc, char** argv)
{
    int n = 0; // default number of elements in range
    int arr[N] = {0}; // initial array
    int sarr[N] = {0}; // sorted array
    if (argc == 3) // input
    {
        if (strcmp(argv[1], "-f") == 0)
        {
            n = read_from_file(argv[2], arr);
        }
        else if (strcmp(argv[1], "-n") == 0)
        {
            n = atoi(argv[2]);
            assert(n < N);
            read_from_keyboard(n, arr);
        }
        else
        {
            fprintf(stderr, "ERROR: Wrong input.\nExample ./run.out [-f {filename}] [-n {length < 10000}]\n");
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Wrong input.\nExample ./run.out [-f {filename}] [-n {length < 10000}]\n");
        return -1;
    }
    assert(n);
    sort(arr, n, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
