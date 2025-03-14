#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 500

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
void initializeMatrices()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }
    }
}

void parallelMatrixMultiplicationstatic()
{
#pragma omp parallel for collapse(2) schedule(static)
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int sum = 0; // private variable
            for (int k = 0; k < SIZE; k++)
            {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main()
{
    srand(time(0));
    initializeMatrices();

    double start = omp_get_wtime();
    parallelMatrixMultiplicationstatic();
    double end = omp_get_wtime();
    printf("Parallel Execution Time: %f second \n", end - start);

    return 0;
}