#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 500  // Matrix size

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

void initializeMatrices() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }
    }
}

void matrixMultiplicationParallel() {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    srand(time(0));
    initializeMatrices();

    double start = omp_get_wtime();
    matrixMultiplicationParallel();
    double end = omp_get_wtime();

    printf("Parallel Execution Time: %f seconds\n", end - start);

    return 0;
}
