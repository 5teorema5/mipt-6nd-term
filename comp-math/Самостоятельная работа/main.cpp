#include <iostream>
#include <cmath>
#include <vector>
#include "grid.h"

int main() {
    double L = 2 * M_PI;
    double T = 10.0;
    double h = 0.1;
    double CFL = 0.5;
    double t = CFL * h;

    int Nx = static_cast<int>(L / h) + 1;
    int Ny = static_cast<int>(T / t) + 1;

    grid2d grid(L, T, h, t);
    for (int j = 2; j <= Ny; j++) {
        grid.add_time_layer((j - 1) * t);
    }

    for (int i = 1; i <= Nx; i++) {
        double x = (i - 1) * h;
        grid.set_u(i, 1, sin(x));
        grid.set_v(i, 1, cos(x));
    }

    double lambda = t / h;
    double f = 0.0, g = 0.0;

    for (int j = 2; j <= Ny; j++) {
        std::vector<double> u_half(Nx + 2), v_half(Nx + 2);

        // Вычисляем половинные значения для всех внутренних точек
        for (int i = 2; i <= Nx - 1; i++) {
            u_half[i] = 0.5 * (grid.get_u(i + 1, j - 1) + grid.get_u(i, j - 1))
                        - 0.5 * lambda * (grid.get_v(i + 1, j - 1) - grid.get_v(i, j - 1))
                        + 0.5 * t * f;
            v_half[i] = 0.5 * (grid.get_v(i + 1, j - 1) + grid.get_v(i, j - 1))
                        - 0.5 * lambda * (grid.get_u(i + 1, j - 1) - grid.get_u(i, j - 1))
                        + 0.5 * t * g;
        }

        // Граничные условия для i=1 (периодичность)
        u_half[1] = 0.5 * (grid.get_u(2, j - 1) + grid.get_u(1, j - 1))
                    - 0.5 * lambda * (grid.get_v(2, j - 1) - grid.get_v(1, j - 1))
                    + 0.5 * t * f;
        v_half[1] = 0.5 * (grid.get_v(2, j - 1) + grid.get_v(1, j - 1))
                    - 0.5 * lambda * (grid.get_u(2, j - 1) - grid.get_u(1, j - 1))
                    + 0.5 * t * g;

        // Граничные условия для i=Nx (периодичность)
        u_half[Nx] = 0.5 * (grid.get_u(1, j - 1) + grid.get_u(Nx, j - 1))
                     - 0.5 * lambda * (grid.get_v(1, j - 1) - grid.get_v(Nx, j - 1))
                     + 0.5 * t * f;
        v_half[Nx] = 0.5 * (grid.get_v(1, j - 1) + grid.get_v(Nx, j - 1))
                     - 0.5 * lambda * (grid.get_u(1, j - 1) - grid.get_u(Nx, j - 1))
                     + 0.5 * t * g;

        // Вычисляем новые значения для внутренних точек
        for (int i = 2; i <= Nx - 1; i++) {
            double u_new = grid.get_u(i, j - 1) - lambda * (v_half[i] - v_half[i - 1]) + t * f;
            double v_new = grid.get_v(i, j - 1) - lambda * (u_half[i] - u_half[i - 1]) + t * g;
            grid.set_u(i, j, u_new);
            grid.set_v(i, j, v_new);
        }

        // Граничные условия для i=1
        double u_new_1 = grid.get_u(1, j - 1) - lambda * (v_half[1] - v_half[Nx]) + t * f;
        double v_new_1 = grid.get_v(1, j - 1) - lambda * (u_half[1] - u_half[Nx]) + t * g;
        grid.set_u(1, j, u_new_1);
        grid.set_v(1, j, v_new_1);

        // Граничные условия для i=Nx
        double u_new_Nx = grid.get_u(Nx, j - 1) - lambda * (v_half[Nx] - v_half[Nx - 1]) + t * f;
        double v_new_Nx = grid.get_v(Nx, j - 1) - lambda * (u_half[Nx] - u_half[Nx - 1]) + t * g;
        grid.set_u(Nx, j, u_new_Nx);
        grid.set_v(Nx, j, v_new_Nx);
    }
    grid.save_to_file("f=0_g=0");

    return 0;
}