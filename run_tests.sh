#!/bin/bash
gcc -std=c99 matmul.c driver.c -o matrix_multiplication_program
if [ $? -eq 0 ]; then
    ./matrix_multiplication_program
else
    echo "Compilation failed."
fi
