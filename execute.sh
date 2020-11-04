#! /bin/sh

# cmake
cmake -S . -B build

# build
cd build ; make 

# run
./genalg
