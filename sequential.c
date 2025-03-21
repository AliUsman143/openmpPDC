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

// Sequential Matrix Multiplication
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

// Parallel Matrix Multiplication (Dynamic Scheduling)
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
    double execution_times[4];      // Store execution times (0 = Sequential, others = Parallel)
    
    srand(time(0));
    initializeMatrices();

    // **Sequential Execution**
    printf("\n--- Running Sequential Execution ---\n");
    clock_t start_seq = clock();
    matrixMultiplication();
    clock_t end_seq = clock();
    execution_times[0] = (double)(end_seq - start_seq) / CLOCKS_PER_SEC;
    printf("Sequential Execution Time: %f seconds\n", execution_times[0]);

    // **Parallel Execution with Different Threads**
    for (int t = 0; t < 3; t++)
    {
        initializeMatrices(); // Reset matrices to ensure fair comparison

        omp_set_num_threads(num_threads[t]); // Set number of threads
        printf("\n--- Running Parallel Execution with %d Threads ---\n", num_threads[t]);

        double start = omp_get_wtime();
        parallelMatrixMultiplication();
        double end = omp_get_wtime();

        execution_times[t + 1] = end - start; // Store execution time
        printf("Execution Time with %d Threads: %f seconds\n", num_threads[t], execution_times[t + 1]);
    }

    // **Calculate and print average execution time for parallel executions**
    double avg_parallel_time = (execution_times[1] + execution_times[2] + execution_times[3]) / 3;
    printf("\n--- Final Comparison ---\n");
    printf("Sequential Execution Time: %f seconds\n", execution_times[0]);
    printf("Average Parallel Execution Time: %f seconds\n", avg_parallel_time);

    return 0;
}
