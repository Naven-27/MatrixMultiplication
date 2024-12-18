#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

// Function to check if the file exists
int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

// Function to generate random matrix and write it to a file
void generate_matrix_to_file(int n, const char* filename) {
    srand(time(NULL)); // Initialize random number generator

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }
    fprintf(file, "%d\n", n);  // Write matrix size at the beginning
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%d ", rand() % 100); // Random values between 0 and 99
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Function to read matrix from file
int** read_matrix_from_file(const char* filename, int* n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }
    fscanf(file, "%d", n);  // Read matrix size from the first line

    int** matrix = (int**)malloc((*n) * sizeof(int*));
    for (int i = 0; i < *n; i++) {
        matrix[i] = (int*)malloc((*n) * sizeof(int));
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%d", &matrix[i][j]); // Read matrix values
        }
    }

    fclose(file);
    return matrix;
}

// Function to multiply two matrices
int** matrix_multiplication(int** A, int** B, int n) {
    int** C = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        C[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Function to write matrix to file
void write_matrix_to_file(int** matrix, int n, const char* filename) {
    // Check if file exists, if so modify it (write only the matrix part)
    if (file_exists(filename)) {
        FILE *file = fopen(filename, "r+");
        if (file == NULL) {
            printf("Error opening file for modification: %s\n", filename);
            exit(1);
        }

        // Skip the first line that contains the matrix size
        fseek(file, 0, SEEK_SET);
        fprintf(file, "%d\n", n); // Modify matrix size if necessary

        // Write the new matrix data
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fprintf(file, "%d ", matrix[i][j]);
            }
            fprintf(file, "\n");
        }

        fclose(file);
    } else {
        // If file doesn't exist, create it and write matrix
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Error opening file: %s\n", filename);
            exit(1);
        }
        fprintf(file, "%d\n", n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fprintf(file, "%d ", matrix[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
}

// Function to free the allocated memory for the matrix
void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int sizes[] = {120, 140, 160, 180, 200, 220, 240, 260, 280, 300,
                   320, 340, 360, 380, 400, 420, 440, 460, 480, 500};

    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int n = sizes[i];
        char filename[100];

        // Generate matrices A and B for the given size
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/A.txt", n);
        generate_matrix_to_file(n, filename);

        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/B.txt", n);
        generate_matrix_to_file(n, filename);

        // Read matrices A and B
        int** A = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/B.txt", n);
        int** B = read_matrix_from_file(filename, &n);

        // Perform matrix multiplication
        int** C = matrix_multiplication(A, B, n);

        // Write result matrix C to file
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/C.txt", n);
        write_matrix_to_file(C, n, filename);

        // Free allocated memory for matrices
        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);

        printf("Generated matrices for size %d and computed A * B to create C\n", n);
    }

    return 0;
}
