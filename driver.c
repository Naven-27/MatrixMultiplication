#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matmul.h"
#include <math.h>

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
    for (int i = 0; i < *n; i++) {
        matrix[i] = (int*)malloc((*n) * sizeof(int));
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
    return matrix;
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
    char filename[100];
    int n=1;
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/smallest_size/A.txt", n);
    int** A = read_matrix_from_file(filename, &n);
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/smallest_size/B.txt", n);
    int** B = read_matrix_from_file(filename, &n);
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/smallest_size/C.txt", n);
    int** C = read_matrix_from_file(filename, &n);
    fprintf(report, "1x1,1x1");
    if(A[0][0]*B[0][0] == C[0][0]){
        for(int i=0;i<6;i++)
         fprintf(report, "0.00000");
         fprintf(report, ",Pass\n");
    }
    else{
        for(int i=0;i<5;i++)
         fprintf(report, "-1");
         fprintf(report, ",Fail\n");
    }
    int test_passed = 1; // Assume test passes until a failure is encountered
    double avg_time;
    n=100;
    fprintf(report, "100x100,100x100");
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_correct/A.txt", n);
    A = read_matrix_from_file(filename, &n);
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_correct/B.txt", n);
    B = read_matrix_from_file(filename, &n);
    snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_correct/C.txt", n);
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

        fprintf(report, "100x100,100x100");
        snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_wrong/A.txt", n);
        A = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_wrong/B.txt", n);
        B = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_wrong/C.txt", n);
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
        
    fprintf(report, "Time is measured in seconds (average over %d iterations)\n", NUM_ITERATIONS);
    fclose(report);
    printf("Unit tests completed. Report saved in test_report.csv\n");
}

int main() {
    run_unit_tests();
    return 0;
}
