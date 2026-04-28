## Time-Dependent Solver Extension

The solver has been extended to support time-accurate simulations of the 2D linear advection equation.

### Key Features
- Explicit time integration using Forward Euler method
- Transient solution output at multiple time steps (`solution_*.dat`)
- Periodic boundary conditions applied at every time step
- Multiple spatial discretization schemes
- Simulation of scalar transport in a 2D domain

### Spatial Discretization Schemes
Two finite-difference schemes are implemented:

1. **First-order upwind scheme**
   - Directional (flow-dependent) discretization
   - Numerically stable
   - Introduces numerical diffusion (smoothing of solution)

2. **Second-order central difference scheme**
   - Higher-order accurate in space
   - Non-dissipative
   - Can introduce oscillations for pure advection with explicit time integration

This allows comparison between stability and accuracy characteristics of different schemes.

### What Changed
Previously, the solver produced only a single snapshot of the solution.  
With this update, the solver now captures the full time evolution of the scalar field and supports multiple spatial discretization methods.

### Governing Equation
The solver computes the solution of:

∂u/∂t + a ∂u/∂x + b ∂u/∂y = 0

where:
- `u` is the transported scalar
- `a`, `b` are constant velocities in x and y directions

### Numerical Method
- Spatial discretization: finite difference (upwind and central schemes)
- Time integration: explicit Forward Euler
- Grid: structured Cartesian grid

### Output
The solver generates:
- `solution_0.dat`, `solution_1.dat`, ... → solution at different time steps
- `residual.dat` → convergence / residual history

These outputs allow visualization of how the scalar field evolves over time.