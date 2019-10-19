#include <cuda.h>

#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

CUresult cuDeviceTotalMem(size_t* bytes, CUdevice dev) {
    void *handle;
    handle = dlopen("/usr/lib/x86_64-linux-gnu/libcuda.so.1", RTLD_LAZY);

    printf("%s\n", "I just want to tell you that cuDeviceTotalMem is STILL hijacked!");
    
    CUresult (*ori_cu_device_total_mem)(size_t*, CUdevice);
    ori_cu_device_total_mem = (CUresult (*)(size_t *, CUdevice))dlsym(handle, "cuDeviceTotalMem_v2");

    CUresult res = ori_cu_device_total_mem(bytes, dev);

    dlclose(handle);
    return res;
}
