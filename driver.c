#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
    return matrix;
}
double time_matrix_multiplication(int version, int** A, int** B, int** C, int n) {
    clock_t start, end;
    int** result = NULL;
    start = clock();
    switch (version) {
        case 0: result = matrix_multiplication_ijk(A, B, n); break;
        case 1: result = matrix_multiplication_ikj(A, B, n); break;
        case 2: result = matrix_multiplication_jik(A, B, n); break;
        case 3: result = matrix_multiplication_jki(A, B, n); break;
        case 4: result = matrix_multiplication_kij(A, B, n); break;
        case 5: result = matrix_multiplication_kji(A, B, n); break;
    }
    end = clock();
    free_matrix(result, n);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}
void run_unit_tests() {
    int sizes[] = {100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400, 420, 440, 460, 480, 500};
    const char* loop_order[] = {"ijk", "ikj", "jik", "jki", "kij", "kji"};
    FILE* report = fopen("test_report.xlsx", "w");
    fprintf(report, "Matrix Size,ijk,ikj,jik,jki,kij,kji\n");
    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int n = sizes[i];
        char filename[100];
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/A.txt", n);
        int** A = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/B.txt", n);
        int** B = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/C.txt", n);
        int** C = read_matrix_from_file(filename, &n);
        fprintf(report, "%d", n);
        for (int version = 0; version < 6; version++) {
            double time_taken = time_matrix_multiplication(version, A, B, C, n);
            fprintf(report, ",%f", time_taken);
        }
        fprintf(report, "\n");
        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }
    fprintf(report, "Time is measured in seconds\n");
    fclose(report);
    printf("Unit tests completed. Report saved in test_report.csv\n");
}
int main() {
    run_unit_tests();
    return 0;
}
