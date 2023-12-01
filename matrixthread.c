#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 3
#define NUM_THREADS 2

int A[MATRIX_SIZE][MATRIX_SIZE];
int B[MATRIX_SIZE][MATRIX_SIZE];
int C[MATRIX_SIZE][MATRIX_SIZE]; // Result matrix for addition
int D[MATRIX_SIZE][MATRIX_SIZE]; // Result matrix for multiplication

pthread_t threads[NUM_THREADS];

// Structure to pass arguments to the thread function
struct ThreadArgs {
    int start_row;
    int end_row;
};

// Function executed by each thread for matrix addition
void *addMatrices(void *args) {
    struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;

    for (int i = threadArgs->start_row; i < threadArgs->end_row; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    pthread_exit(NULL);
}

// Function executed by each thread for matrix multiplication
void *multiplyMatrices(void *args) {
    struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;

    for (int i = threadArgs->start_row; i < threadArgs->end_row; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            D[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                D[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    // Input matrices A and B
    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            scanf("%d", &B[i][j]);
        }
    }

    // Create thread arguments and divide work
    struct ThreadArgs threadArgs[NUM_THREADS];
    int rows_per_thread = MATRIX_SIZE / NUM_THREADS;
    int start_row = 0;

    for (int i = 0; i < NUM_THREADS; ++i) {
        threadArgs[i].start_row = start_row;
        threadArgs[i].end_row = start_row + rows_per_thread;
        start_row += rows_per_thread;
    }

    // Create threads for addition
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, addMatrices, (void *)&threadArgs[i]);
    }

    // Wait for addition threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Print the result matrix C (addition)
    printf("Matrix C (Addition):\n");
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Create threads for multiplication
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, multiplyMatrices, (void *)&threadArgs[i]);
    }

    // Wait for multiplication threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Print the result matrix D (multiplication)
    printf("Matrix D (Multiplication):\n");
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            printf("%d ", D[i][j]);
        }
        printf("\n");
    }

    return 0;
}
