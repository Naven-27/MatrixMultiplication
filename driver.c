#include <stdio.h>
#include <stdlib.h>
#include "matmul.h"

int** read_matrix_from_file(const char* filename, int* n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }
    fscanf(file, "%d", n);
    int** matrix = (int**)malloc((*n) * sizeof(int*));
    for (int i = 0; i < *n; i++) {
        matrix[i] = (int*)malloc((*n) * sizeof(int));
    }
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
    return matrix;
}

int compare_matrices(int** mat1, int** mat2, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat1[i][j] != mat2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

void print_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    int** A = read_matrix_from_file("Unit_test/unit_100/A.txt", &n);
    int** B = read_matrix_from_file("Unit_test/unit_100/B.txt", &n);
    int** C = read_matrix_from_file("Unit_test/unit_100/C.txt", &n);
    int** result = matrix_multiplication(A, B, n);
    if (compare_matrices(result, C, n)) {
        printf("Result matches the expected matrix C.\n");
    } else {
        printf("Result does not match the expected matrix C.\n");
    }
    printf("Result Matrix:\n");
    print_matrix(result, n);
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);
    free_matrix(result, n);
    return 0;
}
