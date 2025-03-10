#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void matrixMultiplication()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < SIZE; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    srand(time(0));
    initializeMatrices();
    clock_t start = clock();
    matrixMultiplication();
    clock_t end = clock();
    printf("Execution Time: %f second \n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}