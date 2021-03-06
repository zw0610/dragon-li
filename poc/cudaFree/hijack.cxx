#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

#include <builtin_types.h>
#include <cuda.h>

CUresult cuDeviceTotalMem(size_t* bytes, CUdevice dev) {
    void *handle;
    handle = dlopen("/usr/lib64/libcuda.so", RTLD_NOW | RTLD_NODELETE);

    printf("%s\n", "cuDeviceTotalMem is hijacked based on env MYMEM!");

    const char* mymem = getenv("MYMEM");
    int env_set_mem_i = 0;
    sscanf(mymem, "%d", &env_set_mem_i);
    size_t env_set_mem = env_set_mem_i < 0 ? 0 : env_set_mem_i;

    CUresult (*ori_cu_device_total_mem)(size_t*, CUdevice);
    ori_cu_device_total_mem = (CUresult (*)(size_t *, CUdevice))dlsym(handle, "cuDeviceTotalMem_v2");

    size_t total_mem = 0;
    CUresult res = ori_cu_device_total_mem(&total_mem, dev);

    *bytes = env_set_mem < total_mem ? env_set_mem : total_mem;

    dlclose(handle);
    return res;
}


// Hijack cudaFree
cudaError_t cudaFree(void* devPtr) {
    void *handle;
    handle = dlopen("/usr/local/cuda-10.1/targets/x86_64-linux/lib/libcudart.so", RTLD_NOW | RTLD_NODELETE);

    printf("%s\n", "The hijacked cudaFree is called!");

    cudaError_t (*ori_cuda_free)(void*);
    ori_cuda_free = (cudaError_t (*)(void*))dlsym(handle, "cudaFree");

    cudaError_t res = ori_cuda_free(devPtr);

    dlclose(handle);

    return res;
}

