#include <cuda.h>

#include <stdio.h>

CUresult cuDeviceTotalMem(size_t* bytes, CUdevice dev) {
    printf("%s\n", "I just want to tell you that cuDeviceTotalMem is hijacked!");
    *bytes = 1;
    return CUDA_SUCCESS;
}
