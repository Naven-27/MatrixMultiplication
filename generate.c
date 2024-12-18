#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

// Check if a file exists.
int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

// Generate a matrix of random doubles and write it to a file.
void generate_matrix_to_file(int n, const char* filename) {
    srand(time(NULL));
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%.2f ", (double)(rand() % 100) / 10); // Generate random double.
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Read a matrix of doubles from a file.
double** read_matrix_from_file(const char* filename, int* n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }
    fscanf(file, "%d", n);
    double** matrix = (double**)malloc((*n) * sizeof(double*));
    for (int i = 0; i < *n; i++) {
        matrix[i] = (double*)malloc((*n) * sizeof(double));
    }
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
        }
    }
    fclose(file);
    return matrix;
}

// Perform matrix multiplication.
double** matrix_multiplication(double** A, double** B, int n) {
    double** C = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        C[i] = (double*)malloc(n * sizeof(double));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Write a matrix of doubles to a file.
void write_matrix_to_file(double** matrix, int n, const char* filename) {
    if (file_exists(filename)) {
        FILE *file = fopen(filename, "r+");
        if (file == NULL) {
            printf("Error opening file for modification: %s\n", filename);
            exit(1);
        }
        fseek(file, 0, SEEK_SET);
        fprintf(file, "%d\n", n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fprintf(file, "%.2f ", matrix[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    } else {
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Error opening file: %s\n", filename);
            exit(1);
        }
        fprintf(file, "%d\n", n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fprintf(file, "%.2f ", matrix[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
}

// Free the memory allocated for a matrix.
void free_matrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int sizes[] = {100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300,
                   320, 340, 360, 380, 400, 420, 440, 460, 480, 500};
    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int n = sizes[i];
        char filename[100];

        // Generate and save matrix A.
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/A.txt", n);
        generate_matrix_to_file(n, filename);

        // Generate and save matrix B.
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/B.txt", n);
        generate_matrix_to_file(n, filename);

        // Read matrices A and B.
        double** A = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/B.txt", n);
        double** B = read_matrix_from_file(filename, &n);

        // Perform matrix multiplication.
        double** C = matrix_multiplication(A, B, n);

        // Save the result matrix C.
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/C.txt", n);
        write_matrix_to_file(C, n, filename);

        // Free the allocated matrices.
        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }
    return 0;
}
