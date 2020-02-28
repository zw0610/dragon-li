#!/bin/bash

echo "Without LD_PRELOAD"
./a.out

echo ""
echo "With LD_PRELOAD"
MYMEM=999999 LD_PRELOAD="./libcudahijack.so" ./a.out
