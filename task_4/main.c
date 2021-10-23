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

#define rows_1 10 // number of rows of left matrix
#define columns_1 5 // number of columns for left matrix
#define rows_2 columns_1 // numver rows for right matrix
#define columns_2 10 // number of columns of right matrix

// function for initialization
double** create_matrix(int rows, int columns)
{
    srand(time(NULL));
    double** matrix = NULL;
    matrix = calloc(sizeof(double*), rows);
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = calloc(sizeof(double), columns);
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

// function for printing
void print_matrix(double** matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        printf("|");
        for (int j = 0; j < columns; j++)
        { 
            printf("%4.0lf|", matrix[i][j]);
        }
        printf("\n|");
        for (int j = 0; j < columns; j++)
        {
            printf("____|");
        }
        printf("\n");
    }
}

// function to free memory
void free_matrix(double** matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char** argv)
{
    // Init and print
    double** m1 = create_matrix(rows_1, columns_1);
    double** m2 = create_matrix(rows_2, columns_2);
    double** m3 = create_matrix(rows_1, columns_2);
    printf("First matrix\n");
    print_matrix(m1, rows_1, columns_1);
    printf("\nSecond matrix\n");
    print_matrix(m2, rows_2, columns_2);
    // Naive algorithm. One thread calculate one cell 
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < rows_1; i++)
    {
        #pragma omp parallel for schedule(static)
        for (int j = 0; j < columns_2; j++)
        {
            DEBUG(
            int thread_id = omp_get_thread_num();
            printf("[Thread %.2d] Calculate [%d][%d] cell\n", thread_id, i, j);
            )
            double sum = 0;
            for (int r = 0; r < columns_1; r++)
            {
                sum += m1[i][r] * m2[r][j];
            }
            m3[i][j] = sum;
        }
    }
    // Print result and free memory
    printf("\nResult matrix\n");
    print_matrix(m3, rows_1, columns_2);
    free_matrix(m1, rows_1);
    free_matrix(m2, rows_2);
    free_matrix(m3, rows_1);
    return 0;
}
