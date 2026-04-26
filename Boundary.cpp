// ============================================================
// Apply periodic boundary conditions
// ============================================================

void applyPeriodicBoundary(Field2D& field, const Grid2D& grid)
{
    int nx = grid.nx;
    int ny = grid.ny;

    // Periodic in x-direction
    for (int j = 0; j < ny; j++)
    {
        field.u[0][j] = field.u[nx-2][j];
        field.u[nx-1][j] = field.u[1][j];
    }

    // Periodic in y-direction
    for (int i = 0; i < nx; i++)
    {
        field.u[i][0] = field.u[i][ny-2];
        field.u[i][ny-1] = field.u[i][1];
    }
}