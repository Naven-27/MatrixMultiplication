# Matrix Multiplication Performance Comparison and Repository Maintenance

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Test Cases](#test-cases)
- [Memory Error Detection](#memory-error-detection)
- [Prerequisites](#prerequisites)
- [Compilation and Execution](#compilation-and-execution)
## Overview
This project implements various matrix multiplication algorithms using different loop orderings to study their performance and compare the results. The program dynamically allocates memory for square matrices, performs the multiplication, and verifies the results against a reference matrix provided in a `.txt` file.

## Features
- Implements six different matrix multiplication methods:
  - `ijk`
  - `ikj`
  - `jik`
  - `jki`
  - `kij`
  - `kji`
- Dynamically allocates memory for matrices.
- Compares the result matrices from each multiplication method with a reference matrix in a text file.
- Frees allocated memory after use to avoid memory leaks.

### Description of Key Files and Directories
1. **driver.c**  
   The main program that controls the execution of the matrix multiplication methods and their performance comparison.

2. **matmul.c**  
   Contains implementations of the six matrix multiplication methods (`ijk`, `ikj`, etc.).

3. **generate.c**  
   A utility program to generate random matrices for testing.

4. **matmul.h**  
   Header file that contains function declarations for matrix multiplication.

5. **run_tests.sh**  
   A shell script to automate the testing of various matrix multiplication methods. It compiles the program, runs tests, and generates results.

6. **Unit_test**  
   Contains unit tests for validating matrix multiplication. Each subdirectory (e.g., `unit_100` `unit_120...`) has:
   - `A.txt`: Input matrix A
   - `B.txt`: Input matrix B
   - `C.txt`: Expected result matrix
   Contains corner tests for validating matrix multiplication. Subdirectories (e.g., `smallest_size` `identity_matrix_correct..`)

## Test Cases
- Corner Test Cases:
- Smallest Matrix Size: Tests with matrix size = 1x1.
- Identity Matrix: Validates multiplication involving identity matrices.
- Non-Numeric Matrices: Detects and handles invalid input.
### Large Matrices: Tests from 100x100 to 500x500 matrices.

## Memory Error Detection
 - Used tools - Address Sanitizer and Memcheck for detecting memory errors and leaks.

## Prerequisites
- **C Compiler**: Any C compiler such as `gcc`.

## Compilation and Execution
1. Clone the repository or copy the source files into a directory.
2. Compile the program using the :
   ```bash
   gcc filename.c -o [object file name] 

3.Run the program:
    Install Git Bash and move to the project directory. Run the following command to execute the source code
  ```bash
  ./run_tests.sh

