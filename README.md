# Matrix Multiplication Performance Comparison and Repository Maintenance

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

## Prerequisites
- **C Compiler**: Any C compiler such as `gcc`.

## Memory Error Detection
- Used tools - Address Sanitizer and Memcheck for detecting memory errors and leaks.

## Compilation and Execution
1. Clone the repository or copy the source files into a directory.
2. Compile the program using the :
   ```bash
   gcc filename.c -o [object file name]
3.Run the program:
    Install Git Bash and move to the project directory. Run the following command to execute the source code
  ```bash
  ./run_tests.sh

