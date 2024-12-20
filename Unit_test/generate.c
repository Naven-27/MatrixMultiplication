#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif
int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}
void create_directory(const char *dir_name) {
    #ifdef _WIN32
    if (_mkdir(dir_name) != 0 && errno != EEXIST) { 
        perror("Error creating directory");
        exit(1);
    }
    #else
    if (mkdir(dir_name, 0777) != 0 && errno != EEXIST) { 
        perror("Error creating directory");
        exit(1);
    }
    #endif
}
void generate_matrix_to_file(int n, const char* filename) {
    srand(time(NULL)); 
    create_directory(filename);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filename);
        perror("Error");
        exit(1);
    }
    fprintf(file, "%d\n", n); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%d ", rand() % 100);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
int** read_matrix_from_file(const char* filename, int* n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        perror("Error");
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
void write_matrix_to_file(int** matrix, int n, const char* filename) {
    if (file_exists(filename)) {
        FILE *file = fopen(filename, "r+");
        if (file == NULL) {
            printf("Error opening file for modification: %s\n", filename);
            perror("Error");
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
            perror("Error");
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
void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int main() {
    int sizes[] = {100,120, 140, 160, 180, 200, 220, 240, 260, 280, 300,
                   320, 340, 360, 380, 400, 420, 440, 460, 480, 500};
    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int n = sizes[i];
        char filename[100];
        char dir_name[100];
        snprintf(dir_name, sizeof(dir_name), "Unit_test/unit_%d", n);
        create_directory(dir_name);
        snprintf(filename, sizeof(filename), "%s/A.txt", dir_name);
        generate_matrix_to_file(2, filename);
        snprintf(filename, sizeof(filename), "%s/B.txt", dir_name);
        generate_matrix_to_file(2, filename);
        int** A = read_matrix_from_file(filename, &n);
        snprintf(filename, sizeof(filename), "%s/B.txt", dir_name);
        int** B = read_matrix_from_file(filename, &n);
        int** C = matrix_multiplication(A, B, 2);
        snprintf(filename, sizeof(filename), "%s/C.txt", dir_name);
        write_matrix_to_file(C, 2, filename);
        free_matrix(A, 2);
        free_matrix(B, 2);
        free_matrix(C, 2);
        printf("Generated matrices for size %d and computed A * B to create C\n", n);
    }
    return 0;
}
