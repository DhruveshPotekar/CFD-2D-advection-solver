// ============================================================
// Forward Euler time integration
// ============================================================

void forwardEuler(Field2D& field, const Grid2D& grid, double dt)
{
    int nx = grid.nx;
    int ny = grid.ny;

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            field.u_new[i][j] = field.u[i][j] + dt * field.rhs[i][j];
        }
    }
}

// ============================================================
// Copy new solution into current solution
// ============================================================

void updateSolution(Field2D& field, const Grid2D& grid)
{
    int nx = grid.nx;
    int ny = grid.ny;

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            field.u[i][j] = field.u_new[i][j];
        }
    }
}