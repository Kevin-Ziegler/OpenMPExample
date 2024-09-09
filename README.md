# OpenMPExample
OMP example for trapezoid and simpsons rule numerical integration of sin(x) 0 to pi. The resulting answer should be 2. 

Two functions trapezoidalRuleP and simpsonsRuleP are tested in the main() driver with differing numbers of threads. As the number of threads is increased the runtime is decreased.

This program is ran in C++ and compiled in min gw 32bit with g++. To run:
g++ -fopenmp ExampleOpenMP.cpp -o Example
./Example

