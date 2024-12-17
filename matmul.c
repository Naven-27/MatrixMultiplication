#include <stdio.h>
#include <stdlib.h>
int** matrix_multiplication(int** A, int** B,int n) {
    int** result = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}
void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
