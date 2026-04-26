#include <iostream>
#include <chrono>

#include "Grid.cpp"
#include "Field.cpp"
#include "Solver.cpp"
#include "Initial.cpp"
#include "Spatial.cpp"
#include "Time_integration.cpp"
#include "Output.cpp"
#include "Boundary.cpp"

int main()
{   
    std::cout << "Program started\n";
    // ============================================================
    // Grid parameters
    // ============================================================

    int nx = 102;
    int ny = 102;

    double x_min = 0.0;
    double x_max = 1.0;
    double y_min = 0.0;
    double y_max = 1.0;

    // ============================================================
    // Solver parameters
    // ============================================================

    double a_x = 1.0;
    double a_y = 1.0;
    double cfl = 0.4;
    double final_time = 1.0;

    // ============================================================
    // Initial condition parameters
    // ============================================================

    InitialCondition2D ic;
    ic.x0 = 0.25;
    ic.y0 = 0.25;
    ic.sigma_x = 0.085;
    ic.sigma_y = 0.085;

    // ============================================================
    // Create grid, field, solver
    // ============================================================

    Grid2D grid = createGrid(nx, ny, x_min, x_max, y_min, y_max);
    Field2D field = createField(nx, ny);
    Solver2D solver = createSolver(a_x, a_y, cfl, final_time);

    solver.dt = computeTimeStep(grid.dx, grid.dy, solver.a_x, solver.a_y, solver.cfl);

    // ============================================================
    // Initialize field
    // ============================================================

    initializeGaussian(field, grid, ic);

    // ============================================================
    // Initialize residual output
    // ============================================================

    writeResidualHeader("residual.dat");

    // ============================================================
    // Time loop
    // ============================================================

    auto start_time = std::chrono::high_resolution_clock::now();

    while (solver.time < solver.final_time)
    {
        if (solver.time + solver.dt > solver.final_time)
            solver.dt = solver.final_time - solver.time;

        applyPeriodicBoundary(field, grid);

        computeRHS(field, grid, solver);

        forwardEuler(field, grid, solver.dt);

        double residual = computeResidual(field, grid);

        updateSolution(field, grid);

        applyPeriodicBoundary(field, grid);

        solver.time += solver.dt;
        solver.step += 1;

        appendResidual("residual.dat", solver.step, solver.time, residual);

        if (solver.step % 20 == 0)
        {
            std::cout << "Step: " << solver.step
                    << ", Time: " << solver.time
                    << ", Residual: " << residual << "\n";
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    // ============================================================
    // Write final solution
    // ============================================================

    writeTecplot(field, grid, "solution.dat");

    // ============================================================
    // Final output
    // ============================================================

    std::cout << "Finished.\n";
    std::cout << "Total steps = " << solver.step << "\n";
    std::cout << "Final time  = " << solver.time << "\n";
    std::cout << "Wall time   = " << elapsed.count() << " seconds\n";

    return 0;
}