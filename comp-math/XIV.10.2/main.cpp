#include <iostream>
#include <cmath>
#include "grid.h"

int main() {
    // задание начальных данных
    double L = 20;
    double T = 18;
    double h = 0.5;
    std::vector<double> CFL = {0.6, 1.0, 1.01};
    std::vector<double> t;
    for (int i = 0; i < 3; i++) {
       t.push_back(CFL[i] * h);
    }

    // double L = 5.0;
    // double T = 6.0;
    // double h = 1.0;
    // double t = 1.0;

    double x_0 = 0;
    double x_nx = L;
    
    for (int z = 0; z < 3; z++) {
        // генерация сетки
        int Nx = L / h + 1;
        // std::cout << "Число узлов по x: " << Nx << '\n';
        int Ny = T / t[z] + 1;
        // int Ny = T / t + 1;
        // std::cout << "Число узлов по y: " << Ny << '\n';
        grid2d grid(L, T, h, t[z]);

        // """Схема Курсанта-Изаксона-Риса"""

        // начальные условия
        for (int i = 1; i < Nx+1; i++) {
            grid.set_value(i, 1, sin(4*M_PI*(x_0 + h*(i-1))/grid.get_L()));
        }

        // grid.print_grid();
        // grid.print_all_value();

        // цикл по времени
        for (int j = 2; j < Ny+1; j++) {\
            grid.set_value(1, j, 0);
            for (int i = 2; i < Nx+1; i++) {
                grid.set_value(i, j, grid.get_value(i, j-1) - grid.get_t()*(grid.get_value(i, j-1)-grid.get_value(i-1, j-1))/grid.get_h());
            }
            grid.set_value(1, j, grid.get_value(Nx, j));
        }
        // grid.print_grid();
        // grid.print_all_value();
        std::ostringstream cfl_str;
        cfl_str << std::fixed << std::setprecision(2) << CFL[z];
        grid.save_to_file("kurant-isakson-ris-CFL=" + cfl_str.str());
        std::cout << "Finish KIR CFL=" << CFL[z] << '\n';

        // """Схема Лакса-Вендроффа"""

        // начальные условия
        for (int i = 1; i < Nx+1; i++) {
            grid.set_value(i, 1, sin(4*M_PI*(x_0 + h*(i-1))/grid.get_L()));
        }

        // цикл по времени
        for (int j = 2; j < Ny+1; j++) {\
            grid.set_value(1, j, 0);
            for (int i = 2; i < Nx; i++) {
                grid.set_value(i, j, grid.get_value(i, j-1) + grid.get_t()*grid.get_t()*(grid.get_value(i+1, j-1) - 2*grid.get_value(i, j-1) + grid.get_value(i-1, j-1))/(2*grid.get_h()*grid.get_h())-grid.get_t()*(grid.get_value(i+1, j-1) - grid.get_value(i-1, j-1))/(2*grid.get_h()));
            }
            grid.set_value(1, j, grid.get_value(1, j-1) + grid.get_t()*grid.get_t()*(grid.get_value(2, j-1) - 2*grid.get_value(1, j-1) + grid.get_value(Nx, j-1))/(2*grid.get_h()*grid.get_h())-grid.get_t()*(grid.get_value(2, j-1) - grid.get_value(Nx, j-1))/(2*grid.get_h()));
            grid.set_value(Nx, j, grid.get_value(Nx, j-1) + grid.get_t()*grid.get_t()*(grid.get_value(1, j-1) - 2*grid.get_value(Nx, j-1) + grid.get_value(Nx-1, j-1))/(2*grid.get_h()*grid.get_h())-grid.get_t()*(grid.get_value(1, j-1) - grid.get_value(Nx-1, j-1))/(2*grid.get_h()));
        }


        grid.save_to_file("laks-vendroff-CFL=" + cfl_str.str());
        std::cout << "Finish LV CFL=" << CFL[z] << '\n';
    }
    
    return 0;
}

