#!/bin/bash
ffcx poisson.ufl
gcc -I/usr/local/lib/python3.8/dist-packages/ffcx/codegeneration -shared poisson.c -o libpoisson.so
g++ -I/usr/local/lib/python3.8/dist-packages/ffcx/codegeneration -L$(pwd) main.cpp -o main -lpoisson 