#include <cuda.h>

#include <iostream>


#define checkCudaErrors(err)  __checkCudaErrors (err, __FILE__, __LINE__)

inline void __checkCudaErrors( CUresult err, const char *file, const int line )
{
    if( CUDA_SUCCESS != err) {
        fprintf(stderr,
                "CUDA Driver API error = %04d from file <%s>, line %i.\n",
                err, file, line );
        exit(-1);
    }
}

int main() {

    checkCudaErrors(cuInit(0));

    int device_count = 0;
    checkCudaErrors(cuDeviceGetCount(&device_count));

    std::cout << "Hello World!" << std::endl;
    std::cout << "Find " << device_count << " device(s)." << std::endl;

    CUdevice device;
    checkCudaErrors(cuDeviceGet(&device, 0));

    char name[100];
    checkCudaErrors(cuDeviceGetName(name, 100, device));

    size_t bytes = 0;
    checkCudaErrors(cuDeviceTotalMem(&bytes, device));

    std::cout << name << " has total memory of " << bytes << " bytes." << std::endl;

    return 0;
}
