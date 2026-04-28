#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>

// ============================================================
// Write solution in Tecplot ASCII format
// ============================================================

void writeTecplot(const Field2D& field,
                  const Grid2D& grid,
                  const std::string& filename)
{
    std::ofstream file(filename);
    file << std::scientific << std::setprecision(6);

    file << "TITLE = \"2D Linear Advection\"\n";
    file << "VARIABLES = \"x\" \"y\" \"u\"\n";
    file << "ZONE I=" << grid.nx << ", J=" << grid.ny << ", F=POINT\n";

    for (int j = 0; j < grid.ny; j++)
    {
        for (int i = 0; i < grid.nx; i++)
        {
            file << grid.x[i] << " "
                 << grid.y[j] << " "
                 << field.u[i][j] << "\n";
        }
    }

    file.close();
}

// ============================================================
// Compute residual between u_new and u
// ============================================================

double computeResidual(const Field2D& field, const Grid2D& grid)
{
    double sum = 0.0;
    int N = grid.nx * grid.ny;

    for (int i = 0; i < grid.nx; i++)
    {
        for (int j = 0; j < grid.ny; j++)
        {
            double diff = field.u_new[i][j] - field.u[i][j];
            sum += diff * diff;
        }
    }

    return std::sqrt(sum / N);
}

// ============================================================
// Write residual history line
// ============================================================

void writeResidualHeader(const std::string& filename)
{
    std::ofstream file(filename);
    file << "TITLE = \"Residual History\"\n";
    file << "VARIABLES = \"Step\" \"Time\" \"Residual\"\n";
    file << "ZONE F=POINT\n";
    file.close();
}

void appendResidual(const std::string& filename,
                    int step,
                    double time,
                    double residual)
{
    std::ofstream file(filename, std::ios::app);
    file << step << " " << time << " " << residual << "\n";
    file.close();
}