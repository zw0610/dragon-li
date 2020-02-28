#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

#include <builtin_types.h>
#include <cuda.h>

CUresult cuDeviceTotalMem(size_t* bytes, CUdevice dev) {
    void *handle;
    handle = dlopen("/usr/lib/x86_64-linux-gnu/libcuda.so.1", RTLD_NOW | RTLD_NODELETE);

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

CUresult cuMemFree_v2(CUdeviceptr dptr) {
    void *handle;
    handle = dlopen("/usr/lib/x86_64-linux-gnu/libcuda.so.1", RTLD_NOW | RTLD_NODELETE);

    printf("%s\n", "The hijacked cuMemFree is called!");

    CUresult (*ori_cu_mem_free)(CUdeviceptr);
    ori_cu_mem_free = (CUresult (*)(CUdeviceptr))dlsym(handle, "cuMemFree_v2");

    CUresult res = ori_cu_mem_free(dptr);

    dlclose(handle);
    return res;
}

// CUresult cuMemFree(CUdeviceptr dptr) {
//     void *handle;
//     handle = dlopen("/usr/lib/x86_64-linux-gnu/libcuda.so.1", RTLD_LAZY);

//     printf("%s\n", "The hijacked cuMemFree is called!");

//     CUresult (*ori_cu_mem_free)(CUdeviceptr);
//     ori_cu_mem_free = (CUresult (*)(CUdeviceptr))dlsym(handle, "cuMemFree_v2");

//     CUresult res = ori_cu_mem_free(dptr);

//     dlclose(handle);
//     return res;
// }

CUresult cuMemAlloc_v2(CUdeviceptr* dptr, size_t bytesize) {
    void *handle;
    handle = dlopen("/usr/lib/x86_64-linux-gnu/libcuda.so.1", RTLD_NOW | RTLD_NODELETE);

    printf("%s\n", "The hijacked cuMemAlloc is called!");

    CUresult (*ori_cu_mem_alloc)(CUdeviceptr*, size_t);
    ori_cu_mem_alloc = (CUresult (*)(CUdeviceptr*, size_t))dlsym(handle, "cuMemAlloc_v2");

    printf("Allocating %zu bytes GPU memory", bytesize);
    CUresult res = ori_cu_mem_alloc(dptr, bytesize);

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

// Hijack cudaMalloc

cudaError_t cudaMalloc ( void** devPtr, size_t size ) {
    void *handle;
    handle = dlopen("/usr/local/cuda-10.1/targets/x86_64-linux/lib/libcudart.so", RTLD_NOW | RTLD_NODELETE);

    printf("%s\n", "The hijacked cudaMalloc is called!");

    cudaError_t (*ori_cuda_malloc)(void**, size_t);
    ori_cuda_malloc = (cudaError_t (*)(void**, size_t))dlsym(handle, "cudaMalloc_v2");

    cudaError_t res = ori_cuda_malloc(devPtr, size);

    dlclose(handle);

    return res;
}