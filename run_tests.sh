#!/bin/bash
gcc -std=c99 driver.c matmul.c -o matrix_multiplication_program
if [ $? -eq 0 ]; then
    ./matrix_multiplication_program
else
    echo "Compilation failed."
fi
