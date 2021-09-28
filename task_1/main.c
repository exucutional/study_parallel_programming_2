#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{
    printf("Hello world\n");
    int max_thread = omp_get_max_threads();
    printf("Thread max count: %d\n", max_thread);
    #pragma omp parallel
    {
        for (int i = max_thread; i > 0; i--)
        {
            #pragma omp barrier
            {
                int thread_id = omp_get_thread_num();
                if (i == thread_id + 1)
                {
                    printf("Thread id: %d\n", thread_id);
                }
            }
        }
    }
    return 0;
}
