#include <iostream>
#include <cstdlib>
#include <cmath>
#include "algebra.h"
#include "grid.h"
#include "state.h"

int main() {
    int L = 10;
    double T = 0.015;
    double gamma = 5.0 / 3.0;
    double h = 0.1;             // шаг по пространству
    double t_init = 10e-7;      // шаг по времени
    double t = t_init;
    double CFL_max = 0.01;      // число Куранта меньше 0.01 для устойчивости

    state left_state = {0.0, 13.0, 10e5, 0.0};
    state right_state = {0.0, 1.3, 1e5, 0.0};

    grid2d grid_rho(2 * L, T, h, t_init);
    grid2d grid_u(2 * L, T, h, t_init);
    grid2d grid_e(2 * L, T, h, t_init);
    grid2d grid_p(2 * L, T, h, t_init);

    int nx = static_cast<int>(grid_rho.get_nx());

    std::vector<state> variables;
    variables.resize(nx);
    std::vector<std::vector<double>> w;
    w.resize(nx, std::vector<double>(3, 0.0));

    for (int i = 0; i < nx; i++) {
        double x = i * h - L;
        if (x < 0) {
            variables[i] = left_state;
        } else {
            variables[i] = right_state;
        }
        variables[i].calculate_e(gamma);
        w[i] = variables[i].toCons();

        grid_rho.set_value(i, 0, variables[i].rho);
        grid_u.set_value(i, 0, variables[i].u);
        grid_e.set_value(i, 0, variables[i].e);
        grid_p.set_value(i, 0, variables[i].p);
    }

    double time = 0.0;
    while (time < T) {
        std::cout << time << '\n';

        double max_lambda = 0.0;
        for (int i = 0; i < nx; i++) {
            double c = variables[i].calculete_c(gamma);
            double u = variables[i].u;
            double lambda_1 = std::abs(u + c);
            double lambda_2 = std::abs(u - c);
            double lambda_3 = std::abs(u);
            max_lambda = std::max(max_lambda, std::max(std::max(lambda_1, lambda_2), lambda_3));
        }

        t = t_init;
        double CFL = t * max_lambda / h;
        while (CFL > CFL_max) {
            t /= 2.0;
            CFL = t * max_lambda / h;
        }

        std::vector<std::vector<double>> w_old = w;

        for (int i = 1; i < nx - 1; i++) {
            double u = variables[i].u;
            double c = variables[i].calculete_c(gamma);
            double e = variables[i].e;

            std::vector<double> omega_data = {
                    -u * c, c, gamma - 1.0,
                    -c * c, 0.0, gamma - 1.0,
                    u * c, -c, gamma - 1.0
            };
            matrix OmegaT = matrix(3, 3, omega_data);

            matrix OmegaT_inv = OmegaT.inverse();

            std::vector<double> lambda_data = {
                    u + c, 0.0, 0.0,
                    0.0, u, 0.0,
                    0.0, 0.0, u - c,
            };
            matrix Lambda = matrix(3, 3, lambda_data);

            matrix A = OmegaT.inverse() * (Lambda * OmegaT);

            std::vector<double> grad_one(3, 0.0);
            std::vector<double> grad_two(3, 0.0);

            for (int k = 0; k < A.get_y_size(); k++) {
                grad_one[k] = (w_old[i + 1][k] - w_old[i - 1][k]) / (2.0 * h);
                grad_two[k] = (w_old[i + 1][k] - 2.0 * w_old[i][k] + w_old[i - 1][k]) / (2.0 * h);
            }
            matrix D = OmegaT_inv * Lambda.abs() * OmegaT;
            std::vector<double> A_grad = A * grad_one;
            std::vector<double> D_grad = D * grad_two;

            for (int k = 0; k < A.get_y_size(); k++) {
                w[i][k] = w_old[i][k] - t * A_grad[k] + t * D_grad[k];
            }
        }
        for (int i = 0; i < nx; i++) {
            double rho = w[i][0];
            double u = std::abs(w[i][1] / rho);
            double e = w[i][2] / rho;
            double p = (gamma - 1) * rho * e;
            variables[i] = state(u, rho, p, e);
        }
        for (int k = 0; k < 3; k++) {
            w[0][k] = w[1][k];
            w[nx - 1][k] = w[nx - 2][k];
        }
        time += t;
        for (int i = 0; i < nx; i++) {
            grid_rho.set_value(i, 0, variables[i].rho);
            grid_u.set_value(i, 0, variables[i].u);
            grid_p.set_value(i, 0, variables[i].p);
            grid_e.set_value(i, 0, variables[i].e);
        }
        if (T - time < 10e-12) {
            std::cout << "Break" << '\n';
            break;
        }
    }

    grid_rho.save_to_file("rho");
    grid_u.save_to_file("u");
    grid_p.save_to_file("p");
    grid_e.save_to_file("e");

    return 0;
}