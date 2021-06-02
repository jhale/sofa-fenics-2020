# FEniCSx Code Generation demo
### SOFA Technical Committee Meeting, 2 June 2021

This code was shown as part of a presentation at the SOFA Technical Committee
Meeting in June 2021.

It is a short example showing direct use of the automatically generated code
capabilities of the FEniCS Project from C++ at the lowest level.

### Acknowledgements

The DRIVEN project has received funding from the European Union’s Horizon 2020
research and innovation programme under grant agreement No 811099

### Instructions

Launch a Docker container

  ./launch-container.sh

Use `ffcx` to compile the UFL file `poisson.ufl` describing the bilinear
form for the Poisson problem on a P1 finite element space.

  ffcx poisson.ufl

Note the output `poisson.h` and `poisson.c`. They conform to the UFC header
which you can see in the header file 
`/usr/local/lib/python3.8/dist-packages/ffcx/codegeneration/ufc.h` inside the
container.

Now you can build a shared object from the generated code

  gcc -I/usr/local/lib/python3.8/dist-packages/ffcx/codegeneration -shared poisson.c -o libpoisson.so

And subsequently build the `main.cpp` file into an executable

  g++ -I/usr/local/lib/python3.8/dist-packages/ffcx/codegeneration -L$(pwd) main.cpp -o main -lpoisson

Which can be executed using

  ./main

The above build steps can be executed simply using

  ./build.sh
