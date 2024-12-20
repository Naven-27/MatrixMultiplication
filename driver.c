#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matmul.h"
#include <math.h>
// Number of iterations for averaging timings
#define NUM_ITERATIONS 10

// Read matrix from file and store it in an integer matrix
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
int compare_matrix(int** A,int** B,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(A[i][j]!=B[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}
// Measure average time for a specific multiplication order
double measure_average_time(int** A, int** B, int** C, int n, int** (*matmul_func)(int**, int**, int)) {
    double total_time = 0.0;
    int flag=1;
    for(int i=0;i<NUM_ITERATIONS;i++)
    {
        clock_t start, end;
        int** result;
        start = clock();
        result = matmul_func(A, B, n);
        end = clock();
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        if (compare_matrix(result, C, n) == 0) {
            printf("Test case failed for matrix size %d during iteration %d\n", n,i);
            flag = 0;
            break;
        }
        free_matrix(result, n);
    }
    if (flag==0)
    {
        return -1;
    }
    return total_time / NUM_ITERATIONS;
}

// Run unit tests with different matrix sizes and loop orders
void run_unit_tests() {
    int sizes[] = {100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500};
    FILE* report = fopen("test_report.csv", "w");
    if (report == NULL) {
        printf("Error: Unable to create test_report.csv\n");
        exit(1);
    }
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
        // Measure and record average time for each loop order
        double avg_time = measure_average_time(A, B, C, n, matrix_multiplication_ijk);
        if(avg_time==-1)
        {
            for(int i=0;i<5;i++)
                fprintf(report, ",err");
        }
        else{
            fprintf(report, ",%.2f", avg_time);
            avg_time = measure_average_time(A, B, C, n, matrix_multiplication_ikj);
            fprintf(report, ",%.2f", avg_time);
            avg_time = measure_average_time(A, B, C, n, matrix_multiplication_jik);
            fprintf(report, ",%.2f", avg_time);
            avg_time = measure_average_time(A, B, C, n, matrix_multiplication_jki);
            fprintf(report, ",%.2f", avg_time);
            avg_time = measure_average_time(A, B, C, n, matrix_multiplication_kij);
            fprintf(report, ",%.2f", avg_time);
            avg_time = measure_average_time(A, B, C, n, matrix_multiplication_kji);
            fprintf(report, ",%.2f", avg_time);
        }
        fprintf(report, "\n");

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }
    fprintf(report, "Time is measured in seconds (average over %d iterations)\n", NUM_ITERATIONS);
    fclose(report);
    printf("Unit tests completed. Report saved in test_report.csv\n");
}

int main() {
    run_unit_tests();
    return 0;
}
