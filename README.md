# 2D Linear Advection Solver (C++)

This project implements a 2D linear advection solver using a structured grid and explicit time integration.

## Features
- Finite-difference discretization
- Explicit time integration (Forward Euler)
- Periodic boundary conditions
- Structured grid
- Residual monitoring
- Tecplot-compatible output

## Governing Equation
∂u/∂t + a ∂u/∂x + b ∂u/∂y = 0

## How to Run

```bash
g++ -std=c++17 -O2 main.cpp -o solver.exe
./solver.exe
