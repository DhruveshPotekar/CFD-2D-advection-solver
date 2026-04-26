#include <cmath>

// ============================================================
// Solver parameters
// ============================================================

struct Solver2D
{
    double a_x;
    double a_y;

    double cfl;
    double final_time;

    double time;
    double dt;

    int step;
};

// ============================================================
// Create solver parameters
// ============================================================

Solver2D createSolver(double a_x, double a_y, double cfl, double final_time)
{
    Solver2D solver;

    solver.a_x = a_x;
    solver.a_y = a_y;
    solver.cfl = cfl;
    solver.final_time = final_time;

    solver.time = 0.0;
    solver.dt = 0.0;
    solver.step = 0;

    return solver;
}

// ============================================================
// Compute stable time step
// ============================================================

double computeTimeStep(double dx, double dy, double a_x, double a_y, double cfl)
{
    double dt_x = 1.0e30;
    double dt_y = 1.0e30;

    if (std::abs(a_x) > 0.0)
        dt_x = dx / std::abs(a_x);

    if (std::abs(a_y) > 0.0)
        dt_y = dy / std::abs(a_y);

    return cfl * std::min(dt_x, dt_y);
}