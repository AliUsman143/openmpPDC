#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 500

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

// Function to initialize matrices
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

// Parallel Matrix Multiplication using OpenMP (Dynamic Scheduling)
void parallelMatrixMultiplication()
{
#pragma omp parallel for collapse(2) schedule(dynamic)
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
    int num_threads[] = {4, 8, 16}; // Thread counts
    double execution_times[3];      // Store execution times

    srand(time(0));
    initializeMatrices();

    for (int t = 0; t < 3; t++)
    {
        omp_set_num_threads(num_threads[t]); // Set number of threads
        printf("\n--- Testing with %d Threads ---\n", num_threads[t]);

        double start = omp_get_wtime();
        parallelMatrixMultiplication();
        double end = omp_get_wtime();

        execution_times[t] = end - start; // Store execution time
        printf("Execution Time with %d Threads: %f seconds\n", num_threads[t], execution_times[t]);
    }

    // Calculate and print the average execution time
    double avg_time = (execution_times[0] + execution_times[1] + execution_times[2]) / 3;
    printf("\nAverage Execution Time: %f seconds\n", avg_time);

    return 0;
}
