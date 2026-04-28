#include <vector>

// ============================================================
// 2D scalar field storage
// ============================================================

struct Field2D
{
    std::vector<std::vector<double>> u;      // solution at current time
    std::vector<std::vector<double>> u_new;  // solution at next time step
    std::vector<std::vector<double>> rhs;    // right hand side
    std::vector<std::vector<double>> k1;
    std::vector<std::vector<double>> k2;
    std::vector<std::vector<double>> k3;
    std::vector<std::vector<double>> k4;
};

// ============================================================
// Allocate field arrays
// ============================================================

Field2D createField(int nx, int ny)
{
    Field2D field;

    field.u.resize(nx, std::vector<double>(ny, 0.0));
    field.u_new.resize(nx, std::vector<double>(ny, 0.0));
    field.rhs.resize(nx, std::vector<double>(ny, 0.0));

    field.k1.resize(nx, std::vector<double>(ny, 0.0));
    field.k2.resize(nx, std::vector<double>(ny, 0.0));
    field.k3.resize(nx, std::vector<double>(ny, 0.0));
    field.k4.resize(nx, std::vector<double>(ny, 0.0));
    
    return field;
}