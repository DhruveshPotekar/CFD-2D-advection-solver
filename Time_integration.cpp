void applyPeriodicBoundary(Field2D& field, const Grid2D& grid);
void computeRHS_Central2(Field2D& field, const Grid2D& grid, const Solver2D& solver);

void rungeKutta4(Field2D& field, const Grid2D& grid, Solver2D& solver)
{
    Field2D temp = field;

    // -------------------------
    // k1
    // -------------------------
    applyPeriodicBoundary(field, grid);
    computeRHS_Central2(field, grid, solver);

    for (int i = 0; i < grid.nx; i++)
    {
        for (int j = 0; j < grid.ny; j++)
        {
            field.k1[i][j] = field.rhs[i][j];
            temp.u[i][j] = field.u[i][j] + 0.5 * solver.dt * field.k1[i][j];
        }
    }

    // -------------------------
    // k2
    // -------------------------
    applyPeriodicBoundary(temp, grid);
    computeRHS_Central2(temp, grid, solver);

    for (int i = 0; i < grid.nx; i++)
    {
        for (int j = 0; j < grid.ny; j++)
        {
            field.k2[i][j] = temp.rhs[i][j];
            temp.u[i][j] = field.u[i][j] + 0.5 * solver.dt * field.k2[i][j];
        }
    }

    // -------------------------
    // k3
    // -------------------------
    applyPeriodicBoundary(temp, grid);
    computeRHS_Central2(temp, grid, solver);

    for (int i = 0; i < grid.nx; i++)
    {
        for (int j = 0; j < grid.ny; j++)
        {
            field.k3[i][j] = temp.rhs[i][j];
            temp.u[i][j] = field.u[i][j] + solver.dt * field.k3[i][j];
        }
    }

    // -------------------------
    // k4
    // -------------------------
    applyPeriodicBoundary(temp, grid);
    computeRHS_Central2(temp, grid, solver);

    for (int i = 0; i < grid.nx; i++)
    {
        for (int j = 0; j < grid.ny; j++)
        {
            field.k4[i][j] = temp.rhs[i][j];

            field.u_new[i][j] =
                field.u[i][j]
                + (solver.dt / 6.0)
                * (field.k1[i][j]
                + 2.0 * field.k2[i][j]
                + 2.0 * field.k3[i][j]
                + field.k4[i][j]);
        }
    }

    applyPeriodicBoundary(field, grid);
}

void updateSolution(Field2D& field, const Grid2D& grid)
{
    for (int i = 0; i < grid.nx; i++)
    {
        for (int j = 0; j < grid.ny; j++)
        {
            field.u[i][j] = field.u_new[i][j];
        }
    }
}