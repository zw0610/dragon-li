#!/bin/bash

nvcc ./hello_world.cu -O0 -o ./hello_world.out -std=c++11 -lcuda

nvcc ./vector_add.cu -O0 -o ./vector_add.out -std=c++11 -lcudart

