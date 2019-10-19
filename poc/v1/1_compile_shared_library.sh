#!/bin/bash
nvcc -c -o hijack.o hijack.cu 
nvcc -shared -o hijack.so hijack.o -ldl -lcuda
