# P1: [Simulation for quantum entanglement]

A console based simulation written in c++

## how to compile and run

### Using the batch file provided (Windows):
1. double click "compile_and_run.bat"

### Manual compilation:
this program makes use of c++ modules
1. Open terminal in src folder that is inside P1 folder
2. compile: g++ -std=c++20 -fmodules-ts LibEnt.cpp main.cpp -o app.exe
3. run: app.exe (pass arguments  for dimensions{hight & width}, number of turns, number of particles) eg. 20 25 10 15

## Simulation description
this simulation is to demonstrate the concept of quantum entanglement using a simple and fun approach.
1. first I created two grids grid A and Grid B of equal size containing the same number of particles.
2. The particles move randomly around the grid.
3. the simulation begins with normal particles denoted by ( . ) scatered around the grids.
4. only particles in grid A can move, Particles in grid B can only move if they are entangled.
5. Each particle in grid A move one location in a random direction.
6. If particle in Grid A moves into the same location (x,y coordinate system) as another particle in Grid B, they become Entangled for the rest of the simulation.
7. Entangled particle always move together for the rest of the simulation.
8. If Entangled particles cannot move they change their shape
9. Entangled particles will be denoted by ( *, @, #)

## Programing languages
- C++