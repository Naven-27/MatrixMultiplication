#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int** allocate_matrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}
void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int** matrix_multiplication_ijk(int** A, int** B, int rowsA, int colsA, int colsB) {
    int** result = allocate_matrix(rowsA, colsB);

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}
int** matrix_multiplication_ikj(int** A, int** B, int rowsA, int colsA, int colsB) {
    int** result = allocate_matrix(rowsA, colsB);

    for (int i = 0; i < rowsA; i++) {
        for (int k = 0; k < colsA; k++) {
            for (int j = 0; j < colsB; j++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}
int** matrix_multiplication_jik(int** A, int** B, int rowsA, int colsA, int colsB) {
    int** result = allocate_matrix(rowsA, colsB);

    for (int j = 0; j < colsB; j++) {
        for (int i = 0; i < rowsA; i++) {
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}
int** matrix_multiplication_jki(int** A, int** B, int rowsA, int colsA, int colsB) {
    int** result = allocate_matrix(rowsA, colsB);

    for (int j = 0; j < colsB; j++) {
        for (int k = 0; k < colsA; k++) {
            for (int i = 0; i < rowsA; i++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}
int** matrix_multiplication_kij(int** A, int** B, int rowsA, int colsA, int colsB) {
    int** result = allocate_matrix(rowsA, colsB);

    for (int k = 0; k < colsA; k++) {
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsB; j++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}
int** matrix_multiplication_kji(int** A, int** B, int rowsA, int colsA, int colsB) {
    int** result = allocate_matrix(rowsA, colsB);

    for (int k = 0; k < colsA; k++) {
        for (int j = 0; j < colsB; j++) {
            for (int i = 0; i < rowsA; i++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}
void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int rowsA = 100, colsA = 100, colsB = 100;
    int** A = allocate_matrix(rowsA, colsA);
    int** B = allocate_matrix(colsA, colsB);
    int** C = allocate_matrix(rowsA, colsB); 
    
    free_matrix(A, rowsA);
    free_matrix(B, colsA);
    free_matrix(C, rowsA);

    return 0;
}
