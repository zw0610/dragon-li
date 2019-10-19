#include <cuda.h>

#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

CUresult cuDeviceTotalMem(size_t* bytes, CUdevice dev) {
    void *handle;
    handle = dlopen("/usr/lib/x86_64-linux-gnu/libcuda.so.1", RTLD_LAZY);

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
