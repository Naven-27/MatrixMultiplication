#ifndef MATMUL_H
#define MATMUL_H

int** matrix_multiplication_ijk(int** A, int** B, int n);
int** matrix_multiplication_ikj(int** A, int** B, int n);
int** matrix_multiplication_jik(int** A, int** B, int n);
int** matrix_multiplication_jki(int** A, int** B, int n);
int** matrix_multiplication_kij(int** A, int** B, int n);
int** matrix_multiplication_kji(int** A, int** B, int n);
int** matrix_multiplication_tiled(int** A,int** B,int n);
void free_matrix(int** matrix, int rows);
#endif
