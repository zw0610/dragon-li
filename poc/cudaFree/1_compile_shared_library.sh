#!/bin/bash
#nvcc -c -o hijack.o hijack.cu 
#nvcc -shared -Xcompiler -fPIC -o hijack.so hijack.o -ldl -lcuda -lcudart

g++ -I/usr/local/cuda/targets/x86_64-linux/include -Wall -fPIC -shared -ldl -o hijack.so hijack.cxx
