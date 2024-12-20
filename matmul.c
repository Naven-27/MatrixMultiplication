#include "matmul.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Allocates memory for a square matrix of size n x n.
 * Each row is dynamically allocated as a pointer to an array of ints.
 *
 * @param n The size of the matrix (n x n).
 * @return A pointer to the allocated matrix.
 */
int** allocate_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

/**
 * Performs matrix multiplication using the ijk loop ordering.
 * This order iterates over rows of A, then columns of B, and computes elements of the result.
 * @param A The first matrix.
 * @param B The second matrix.
 * @param n The size of the matrices (n x n).
 * @return A pointer to the resulting matrix after multiplication.
 */
int** matrix_multiplication_ijk(int** A, int** B, int n) {
    int** result = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];

            }
           // printf("%d ",result[i][j]);
        }
       // printf("\n");
    }
    return result;
}

/**
 * Performs matrix multiplication using the ikj loop ordering.
 * This order iterates over rows of A, then rows of B, and computes elements of the result.
 * @param A The first matrix.
 * @param B The second matrix.
 * @param n The size of the matrices (n x n).
 * @return A pointer to the resulting matrix after multiplication.
 */
int** matrix_multiplication_ikj(int** A, int** B, int n) {
    int** result = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;  // Initialize each element to 0
        }
    }
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

/**
 * Performs matrix multiplication using the jik loop ordering.
 * This order iterates over columns of A, rows of B, and computes elements of the result.
 * @param A The first matrix.
 * @param B The second matrix.
 * @param n The size of the matrices (n x n).
 * @return A pointer to the resulting matrix after multiplication.
 */
int** matrix_multiplication_jik(int** A, int** B, int n) {
    int** result = allocate_matrix(n);
    
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

/**
 * Performs matrix multiplication using the jki loop ordering.
 * @param A The first matrix.
 * @param B The second matrix.
 * @param n The size of the matrices (n x n).
 * @return A pointer to the resulting matrix after multiplication.
 */
int** matrix_multiplication_jki(int** A, int** B, int n) {
    int** result = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;  // Initialize each element to 0
        }
    }
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

/**
 * Performs matrix multiplication using the kij loop ordering.
 * @param A The first matrix.
 * @param B The second matrix.
 * @param n The size of the matrices (n x n).
 * @return A pointer to the resulting matrix after multiplication.
 */
int** matrix_multiplication_kij(int** A, int** B, int n) {
    int** result = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;  // Initialize each element to 0
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

/**
 * Performs matrix multiplication using the kji loop ordering.
 * This order iterates over rows of B, columns of A, and computes elements of the result.
 * @param A The first matrix.
 * @param B The second matrix.
 * @param n The size of the matrices (n x n).
 * @return A pointer to the resulting matrix after multiplication.
 */
int** matrix_multiplication_kji(int** A, int** B, int n) {
    int** result = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;  // Initialize each element to 0
        }
    }
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

/**
 * Frees the allocated memory for a matrix.
 * @param matrix The matrix to be freed.
 * @param rows The number of rows in the matrix.
 */
void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
