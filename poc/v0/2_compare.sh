#!/bin/bash

echo "Without LD_PRELOAD"
./a.out

echo ""
echo "With LD_PRELOAD"
LD_PRELOAD="./hijack.so" ./a.out
