#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matmul.h"
#include <math.h>
#include <ctype.h>
// Number of iterations for averaging timings
#define NUM_ITERATIONS 10
// Reading matrix from file and store it in an integer matrix
int** read_matrix_from_file(const char* filename, int* n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }
    fscanf(file, "%d", n);
    int** matrix = (int**)malloc((*n) * sizeof(int*));
    if (!matrix) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        exit(1);
    }
    for (int i = 0; i < *n; i++) {
        matrix[i] = (int*)malloc((*n) * sizeof(int));
        if (!matrix[i]) {
            printf("Error: Memory allocation failed\n");
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            fclose(file);
            exit(1);
        }
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
    return matrix;
}
int is_numeric(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-') {
            return 0; // Non-numeric character found
        }
    }
    return 1;
}
int read_matrix_from_file_with_validation(const char* filename, int* n) {
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
    char buffer[100];
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%s", buffer); // Read as string
            if (!is_numeric(buffer)) {
                fclose(file);
                free_matrix(matrix, *n);
                return 0;
                
            }
            matrix[i][j] = atoi(buffer); // Convert to integer
        }
    }
    fclose(file);
    return 1;
}
// Comparing two matrices for equality
int compare_matrix(int** A, int** B, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != B[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}
// Measuring average time for a specific multiplication order
double measure_average_time(int** A, int** B, int** C, int n, int** (*matmul_func)(int**, int**, int)) {
    double total_time = 0.0;
    int flag = 1;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        clock_t start, end;
        int** result;
        start = clock();
        result = matmul_func(A, B, n);
        end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        if (compare_matrix(result, C, n) == 0) {
            flag = 0;
            free_matrix(result, n);
            return -1;
        }
        free_matrix(result, n);
    }
    return total_time / NUM_ITERATIONS;
}
// Running unit tests with different matrix sizes and loop orders
void run_unit_tests() {
    int sizes[] = {100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400, 420, 440, 460, 480, 500};
    FILE* report = fopen("test_report.csv", "w");
    if (report == NULL) {
        printf("Error: Unable to create test_report.csv\n");
        exit(1);
    }
    fprintf(report, "Matrix A,Matrix B,ijk,ikj,jik,jki,kij,kji,Result\n");
    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int n = sizes[i];
        char filename[100];
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/A.txt", n);
        int** A = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/B.txt", n);
        int** B = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/C.txt", n);
        int** C = read_matrix_from_file(filename, &n);
        // Print matrix dimensions in the format requested
        fprintf(report, "%dx%d,%dx%d", n, n, n, n);
        // Measure and record average time for each loop order
        int test_passed = 1; // Assume test passes until a failure is encountered
        double avg_time;
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_ijk);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_ikj);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_jik);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_jki);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_kij);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_kji);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        // Add test result (Pass/Fail) to the report
        if (test_passed) {
            fprintf(report, ",Pass\n");
        } else {
            fprintf(report, ",Fail\n");
        }
        // Free memory
        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }
    // Corner tests (1x1 matrix, identity matrices)
    char filename[100];
    int n = 1;
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/smallest_size/A.txt");
    int** A = read_matrix_from_file(filename, &n);
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/smallest_size/B.txt");
    int** B = read_matrix_from_file(filename, &n);
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/smallest_size/C.txt");
    int** C = read_matrix_from_file(filename, &n);
    fprintf(report, "1x1,1x1");
    if (A[0][0] * B[0][0] == C[0][0]) {
        for (int i = 0; i < 6; i++)
            fprintf(report, "0.00000");
        fprintf(report, ",Pass\n");
    } else {
        for (int i = 0; i < 5; i++)
            fprintf(report, "-1");
        fprintf(report, ",Fail\n");
    }
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);
    // Test 100x100 identity matrix
     int test_passed = 1; // Assume test passes until a failure is encountered
    double avg_time;
    n=100;
    fprintf(report, "100x100,100x100");
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_correct/A.txt");
    A = read_matrix_from_file(filename, &n);
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_correct/B.txt");
    B = read_matrix_from_file(filename, &n);
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_correct/C.txt");
    C = read_matrix_from_file(filename, &n);
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_ijk);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_ikj);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_jik);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_jki);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_kij);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_kji);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        // Add test result (Pass/Fail) to the report
        if (test_passed) {
            fprintf(report, ",Pass\n");
        } else {
            fprintf(report, ",Fail\n");
        }
        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
        test_passed = 1; // Assume test passes until a failure is encountered
        n=100;
        fprintf(report, "100x100,100x100");
        snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_wrong/A.txt");
        A = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_wrong/B.txt");
        B = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_wrong/C.txt");
        C = read_matrix_from_file(filename, &n);
        test_passed = 1; // Assume test passes until a failure is encountered
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_ijk);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_ikj);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_jik);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_jki);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_kij);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        avg_time = measure_average_time(A, B, C, n, matrix_multiplication_kji);
        if (avg_time == -1) {
            test_passed = 0;
            fprintf(report, ",-1");
        } else {
            fprintf(report, ",%.5f", avg_time);
        }
        // Add test result (Pass/Fail) to the report
        if (test_passed) {
            fprintf(report, ",Pass\n");
        } else {
            fprintf(report, ",Fail\n");
        }
    free_matrix(A,n);
    free_matrix(B,n);
    free_matrix(C,n);
    // Check Non numeric type of inputs in the matrix
    n = 5;
    int s;
    fprintf(report, "5x5,5x5");
    const char* other_dir = "Unit_test/corner_tests/non_numeric";
    snprintf(filename, sizeof(filename), "%s/A.txt", other_dir);
    int r= read_matrix_from_file_with_validation(filename, &n);
    if(r==0)
    {
        for (int i = 0; i < 6; i++)
            fprintf(report, "invalid");
        fprintf(report, ",Pass\n");
    }
    else
    {
        snprintf(filename, sizeof(filename), "%s/B.txt", other_dir);
        s = read_matrix_from_file_with_validation(filename, &n);
        if(s==0)
        {
            for (int i = 0; i < 6; i++)
               fprintf(report, "invalid");
            fprintf(report, ",Pass\n");
        }
    }
    fprintf(report, "Time is measured in seconds (average over %d iterations)\n", NUM_ITERATIONS);
    fclose(report);
    printf("Unit tests completed. Report saved in test_report.csv\n");
}
int main() {
    run_unit_tests();
    return 0;
}
