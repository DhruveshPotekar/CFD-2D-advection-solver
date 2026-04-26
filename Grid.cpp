#include <vector>

// ============================================================
// 2D structured Cartesian grid
// ============================================================

struct Grid2D
{
    int nx, ny;

    double x_min, x_max;
    double y_min, y_max;

    double dx, dy;

    std::vector<double> x;
    std::vector<double> y;
};

// ============================================================
// Grid generation
// ============================================================

Grid2D createGrid(
    int nx,
    int ny,
    double x_min,
    double x_max,
    double y_min,
    double y_max)
{
    Grid2D grid;

    grid.nx = nx;
    grid.ny = ny;

    grid.x_min = x_min;
    grid.x_max = x_max;
    grid.y_min = y_min;
    grid.y_max = y_max;

    // compute grid spacing
    grid.dx = (x_max - x_min) / nx;
    grid.dy = (y_max - y_min) / ny;

    // allocate coordinate arrays
    grid.x.resize(nx);
    grid.y.resize(ny);

    // compute cell-center coordinates
    for (int i = 0; i < nx; i++)
        grid.x[i] = x_min + (i + 0.5) * grid.dx;

    for (int j = 0; j < ny; j++)
        grid.y[j] = y_min + (j + 0.5) * grid.dy;

    return grid;
}