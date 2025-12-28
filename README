# Molecular Dynamics (MD) Simulation

## Overview
This directory contains a simple molecular dynamics (MD) application designed to simulate particle interactions under gravitational and viscous forces.

The program reads input from `input.dat` and outputs results to `output.dat`. A test utility in the `Test` directory is available to compare `output.dat` files, reporting only differences above a preset tolerance value.

## Installation and Building
### Requirements
- Intel oneAPI (2024.0.2)

### Compilation
A ```Makefile``` is provided to compile the application from the root directory:
```sh
make -j
```

A ```submit.srun``` file is also provided which can be used to submit a job to the backend compute node of Cirrus:

_Make sure to correctly set your account code_
```
sbatch submit.srun
```

## Usage
To execute the program, run:
```sh
./build/md
```
This will read `input.dat`, run the molecular dynamics simulation and then produce `output.dat`.

### Correctness Testing
The `test` directory contains a utility to compare `output.dat` files:
```sh
./test/diff-output output_original/output.dat500 output.dat500
```
This will report any differences exceeding a preset tolerance.