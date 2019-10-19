#!/bin/bash

echo "Without LD_PRELOAD"
./a.out

echo ""
echo "With LD_PRELOAD"
MYMEM=123 LD_PRELOAD="./hijack.so" ./a.out
