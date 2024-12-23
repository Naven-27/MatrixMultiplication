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
// Generate a matrix of random integers and write it to a file.
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
            fprintf(file, "%d ", rand() % 100); // Generate random integer.
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
// Read a matrix of integers from a file.
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
// Perform matrix multiplication.
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
void generate_identity_matrix_to_file(int n, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%d ", (i == j) ? 1 : 0); // Identity matrix condition.
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void generate_wrong_identity_matrix_to_file(int n, const char* filename) {
    srand(time(NULL));
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%d ", (i == j) ? rand() % 10 + 1 : 0); // Introduce errors in the diagonal.
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
// Write a matrix of integers to a file.
void write_matrix_to_file(int** matrix, int n, const char* filename) {
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
                fprintf(file, "%d ", matrix[i][j]);
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
                fprintf(file, "%d ", matrix[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
}
// Free the memory allocated for a matrix.
void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int main() {
    int sizes[] = {100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500};
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
        int** A = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/B.txt", n);
        int** B = read_matrix_from_file(filename, &n);
        // Perform matrix multiplication.
        int** C = matrix_multiplication(A, B, n);
        // Save the result matrix C.
        snprintf(filename, sizeof(filename), "Unit_test/unit_%d/C.txt", n);
        write_matrix_to_file(C, n, filename);
        // Free the allocated matrices.
        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);    
    }
        int n = 1;
        // Read matrix A.
        char filename[100];
        snprintf(filename, sizeof(filename), "Unit_test/corner_tests/smallest_size/A.txt");
        generate_matrix_to_file(n, filename);
        int** A = read_matrix_from_file(filename, &n);
        // Read matrix B.
        snprintf(filename, sizeof(filename), "Unit_test/corner_tests/smallest_size/B.txt");
        generate_matrix_to_file(n, filename);
        int** B = read_matrix_from_file(filename, &n);
        // Perform matrix multiplication.
        int** C = matrix_multiplication(A, B, n);
        // Save the result matrix C.
        snprintf(filename, sizeof(filename), "Unit_test/corner_tests/smallest_size/C.txt");
        write_matrix_to_file(C, n, filename);
        // Free the allocated matrices.
        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
        n = 100;
        snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_correct/A.txt");
        generate_identity_matrix_to_file(n, filename);
        snprintf(filename, sizeof(filename), "Unit_test/corner_tests/identity_matrix_correct/B.txt");
        generate_wrong_identity_matrix_to_file(n, filename);
        const char *correct_dir = "Unit_test/corner_tests/identity_matrix_correct";
        const char *wrong_dir = "Unit_test/corner_tests/identity_matrix_wrong";    
        snprintf(filename, sizeof(filename), "%s/A.txt", correct_dir);
        generate_identity_matrix_to_file(n, filename);
        snprintf(filename, sizeof(filename), "%s/B.txt", correct_dir);
        generate_matrix_to_file(n, filename);
        int **A_correct = read_matrix_from_file("Unit_test/corner_tests/identity_matrix_correct/A.txt", &n);
        int **B_correct = read_matrix_from_file("Unit_test/corner_tests/identity_matrix_correct/B.txt", &n);
        int **C_correct = matrix_multiplication(A_correct, B_correct, n);
        snprintf(filename, sizeof(filename), "%s/C.txt", correct_dir);
        write_matrix_to_file(C_correct, n, filename);
        free_matrix(A_correct, n);
        free_matrix(B_correct, n);
        free_matrix(C_correct, n);
        snprintf(filename, sizeof(filename), "%s/A.txt", wrong_dir);
        generate_identity_matrix_to_file(n, filename);
        snprintf(filename, sizeof(filename), "%s/B.txt", wrong_dir);
        generate_matrix_to_file(n, filename);
        A_correct = read_matrix_from_file("Unit_test/corner_tests/identity_matrix_wrong/A.txt", &n);
        B_correct = read_matrix_from_file("Unit_test/corner_tests/identity_matrix_wrong/B.txt", &n);
        int** C_wrong = matrix_multiplication(A_correct, B_correct, n);
        snprintf(filename, sizeof(filename), "%s/C.txt", wrong_dir);
        write_matrix_to_file(C_wrong, n, filename);
        free_matrix(A_correct, n);
        free_matrix(B_correct, n);
        free_matrix(C_wrong, n);
    return 0;
}
