#!/bin/bash

echo "HELLO WORLD Without LD_PRELOAD"
./hello_world.out

echo ""
echo "HELLO WORLD With LD_PRELOAD"
MYMEM=999999 LD_PRELOAD="./hijack.so" ./hello_world.out

echo ""
echo "VECTOR ADD Without LD_PRELOAD"
./vector_add.out

echo ""
echo "VECTOR ADD With LD_PRELOAD"
LD_PRELOAD="./hijack.so" ./vector_add.out
