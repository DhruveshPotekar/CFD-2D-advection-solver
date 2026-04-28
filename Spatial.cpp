// ============================================================
// First-order upwind finite difference
// ============================================================

void computeRHS_Upwind(Field2D& field, const Grid2D& grid, const Solver2D& solver)
{
    int nx = grid.nx;
    int ny = grid.ny;

    double dx = grid.dx;
    double dy = grid.dy;

    double a_x = solver.a_x;
    double a_y = solver.a_y;

    for (int i = 1; i < nx - 1; i++)
    {
        for (int j = 1; j < ny - 1; j++)
        {
            double dudx;
            double dudy;

            if (a_x > 0.0)
                dudx = (field.u[i][j] - field.u[i - 1][j]) / dx;
            else
                dudx = (field.u[i + 1][j] - field.u[i][j]) / dx;

            if (a_y > 0.0)
                dudy = (field.u[i][j] - field.u[i][j - 1]) / dy;
            else
                dudy = (field.u[i][j + 1] - field.u[i][j]) / dy;

            field.rhs[i][j] = -a_x * dudx - a_y * dudy;
        }
    }
}


// ============================================================
// Second-order central finite difference
// ============================================================

void computeRHS_Central2(Field2D& field, const Grid2D& grid, const Solver2D& solver)
{
    int nx = grid.nx;
    int ny = grid.ny;

    double dx = grid.dx;
    double dy = grid.dy;

    double a_x = solver.a_x;
    double a_y = solver.a_y;

    for (int i = 1; i < nx - 1; i++)
    {
        for (int j = 1; j < ny - 1; j++)
        {
            double dudx = (field.u[i + 1][j] - field.u[i - 1][j]) / (2.0 * dx);
            double dudy = (field.u[i][j + 1] - field.u[i][j - 1]) / (2.0 * dy);

            field.rhs[i][j] = -a_x * dudx - a_y * dudy;
        }
    }
}


// ============================================================
// Default RHS function
// Change this line to switch scheme
// ============================================================

void computeRHS(Field2D& field, const Grid2D& grid, const Solver2D& solver)
{
    // computeRHS_Upwind(field, grid, solver);
    computeRHS_Central2(field, grid, solver);
}