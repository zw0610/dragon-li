#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

 
int main( int argc, char* argv[] )
{
    // Size of vectors
    int n = 10;
 
    // Device input vectors
    double *d_a;
 
    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(double);
    
    // Allocate memory for each vector on GPU
    cudaMalloc(&d_a, bytes);

    // Free memory 
    cudaFree(d_a);
 
    return 0;
}
