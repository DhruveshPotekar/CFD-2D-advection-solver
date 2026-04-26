#include <cmath>

// ============================================================
// Initial condition parameters
// ============================================================

struct InitialCondition2D
{
    double x0;        // center in x
    double y0;        // center in y
    double sigma_x;   // width in x
    double sigma_y;   // width in y
};

// ============================================================
// Initialize Gaussian field
// ============================================================

void initializeGaussian(
    Field2D& field,
    const Grid2D& grid,
    const InitialCondition2D& ic)
{
    for (int i = 0; i < grid.nx; i++)
    {
        for (int j = 0; j < grid.ny; j++)
        {
            double x = grid.x[i];
            double y = grid.y[j];

            double dx = (x - ic.x0) / ic.sigma_x;
            double dy = (y - ic.y0) / ic.sigma_y;

            field.u[i][j] = std::exp(-(dx*dx + dy*dy));
        }
    }
}