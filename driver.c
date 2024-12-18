#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void run_unit_tests() {

    int sizes[] = {100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 
                   300, 320, 340, 360, 380, 400, 420, 440, 460, 480, 500};
    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int n = sizes[i];
        char filename[100];        
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/A.txt", n);
        int** A = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/B.txt", n);
        int** B = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/C.txt", n);
        int** C = read_matrix_from_file(filename, &n);
        int** result = matrix_multiplication(A, B, n);
        if (compare_matrices(result, C, n)) {
            printf("Test passed for unit_%d: Result matches the expected matrix C.\n", n);
        } else {
            printf("Test failed for unit_%d: Result does not match the expected matrix C.\n", n);
        }
        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
        free_matrix(result, n);
    }
}
int main() {
    run_unit_tests();
    return 0;
}
