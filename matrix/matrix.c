#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 4 // Change this to the size of your matrix

int matrixA[N][N];
int matrixB[N][N];
int resultMatrix[N][N];

// Structure to pass parameters to the thread function
typedef struct {
    int row;
    int col;
} MatrixIndex;

// Function to perform parallel matrix addition
void *matrixAddition(void *arg) {
    MatrixIndex *index = (MatrixIndex *)arg;
    int row = index->row;
    int col = index->col;

    resultMatrix[row][col] = matrixA[row][col] + matrixB[row][col];

    pthread_exit(NULL);
}

// Function to perform parallel matrix subtraction
void *matrixSubtraction(void *arg) {
    MatrixIndex *index = (MatrixIndex *)arg;
    int row = index->row;
    int col = index->col;

    resultMatrix[row][col] = matrixA[row][col] - matrixB[row][col];

    pthread_exit(NULL);
}

// Function to perform parallel matrix multiplication
void *matrixMultiplication(void *arg) {
    MatrixIndex *index = (MatrixIndex *)arg;
    int row = index->row;
    int col = index->col;

    resultMatrix[row][col] = 0;
    for (int k = 0; k < N; ++k) {
        resultMatrix[row][col] += matrixA[row][k] * matrixB[k][col];
    }

    pthread_exit(NULL);
}

int main() {
    // Initialize matrices (you may read them from a file or generate randomly)
    // For simplicity, initializing with random values for demonstration
    srand(time(NULL));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
        }
    }

    // Declare and initialize thread IDs
    pthread_t threads[N][N];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // Perform parallel matrix addition
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            MatrixIndex *index = (MatrixIndex *)malloc(sizeof(MatrixIndex));
            index->row = i;
            index->col = j;
            pthread_create(&threads[i][j], &attr, matrixAddition, (void *)index);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Display result of matrix addition
    printf("Matrix Addition Result:\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d ", resultMatrix[i][j]);
        }
        printf("\n");
    }

    // Perform parallel matrix subtraction
    // (You can reuse the same resultMatrix)
    // ...

    // Perform parallel matrix multiplication
    // (You can reuse the same resultMatrix)
    // ...

    return 0;
}
