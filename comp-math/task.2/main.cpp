#include <iostream>
#include "algebra.h"
#include "grid.h"

struct state {
    double u;       // скорость, м/с
    double rho;     // плотность, кг/м3
    double p;       // давление, атм
    double e;       // удельная внутренняя энергия, Дж/кг

    state() : u(0), rho(0), p(0), e(0) {}

    state(double u_, double rho_, double p_, double e_) : u(u_), rho(rho_), p(p_), e(e_) {}

    // консервативные переменные
    std::vector<double> toCons() const {
        return std::vector<double>{rho, rho * u, rho * e};
    }

    state fromCons(matrix toCons_, double gamma) {
        double rho = toCons_(0, 0), u = toCons_(0, 1) / rho, e = toCons_(0, 2) / e;
        double = (gamma - 1) * rho * e;
        return state(u, rho, p, e);
    }

    // скорость звука
    double c(double gamma) {
        return std::sqrt(gamma * p / rho);
    }

    void calculate_e(gamma) {
        e = p / ((gamma - 1) * rho)
    }


};


int main() {
    int L = 10;
    double T = 0.02;
    double gamma = 5.0 / 3.0;
    double h = 0.001;       // шаг по пространству
    double t = 0.001;     // шаг по времени
    double CFL = 0.005;     // число Куранта меньше 0.01 для устойчивости

    state left_state = {0.0, 13.0, 10.0, 0.0};
    state right_state = {0.0, 1.3, 1.0, 0.0};

    grid2d grid_rho(L, T, h, t);
    grid2d grid_u(L, T, h, t);
    grid2d grid_e(L, T, h, t);
    grid2d grid_p(L, T, h, t);

    double nx = grid_rho.get_nx();

    std::vector<state> variables;
    variables.resize(nx);
    std::vector<std::vector<double> w;
    w.resize(nx, std::vector<double>(3, 0.0));

    for (int i = 0; i < nx; i++) {
        double x = i * h - l / 2.0;
        if (x < 0) {
            variables[i] = left_state;
        } else {
            variables[i] = right_state;
        }
        variables[i].calculate_e(gamma);
        w = variables[i].toCons();

        grid_rho.set_value(i, 0, variables[i].rho);
        grid_u.set_value(i, 0, variables[i].u);
        grid_e.set_value(i, 0, variables[i].e);
        grid_p.set_value(i, 0, variables[i].p);
    }

    return 0;
}

