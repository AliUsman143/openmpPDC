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