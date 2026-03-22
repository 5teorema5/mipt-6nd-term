#include "grid.h"

grid2d::grid2d(double L_, double T_, double h_, double t_) : L(L_), T(T_), h(h_), t(t_) {
    nx = L / h + 1;
    ny = T / t + 1;

    x_coord.resize(nx);
    for (int i = 0; i < nx; i++) {
        x_coord[i] = i * h;
    }
    y_coord.resize(ny);
    for (int j = 0; j < ny; j++) {
        y_coord[j] = j * t;
    }
    value.resize(nx);
    for (int i = 0; i < nx; i++) {
        value[i].resize(ny, 0.0);
    }
}

double grid2d::get_L() {
    return L;
}

double grid2d::get_T() {
    return T;
}

double grid2d::get_h() {
    return h;
}

double grid2d::get_t() {
    return t;
}

double grid2d::get_nx() {
    return this->nx;
}

double grid2d::get_ny() {
    return this->ny;
}

double grid2d::get_value(int i, int j) {
    return value[i][j];
}

void grid2d::set_value(int i, int j, double val) {
    value[i][j] = val;
}

void grid2d::clear_value() {
    for (int j = 1; j < ny + 1; j++) {
        for (int i = 1; i < nx + 1; i++) {
            value[i - 1][j - 1] = 0;
        }
    }
}

void grid2d::print_grid() {
    std::cout << "Сетка размером L=" << L << " и T=" << T << ", шаг сетки h=" << h << " и t=" << t << ":" << '\n';

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            std::cout << "(" << x_coord[i] << "," << y_coord[j] << "), ";
        }
        std::cout << '\n';
    }
}

void grid2d::print_all_value() {
    std::cout << std::fixed << std::setprecision(3);
    for (int j = 1; j < ny + 1; j++) {
        for (int i = 1; i < nx + 1; i++) {
            std::cout << value[i - 1][j - 1] << " ";
        }
        std::cout << '\n';
    }
}

std::string grid2d::formatIndex(int index, int width) {
    std::string result = std::to_string(index);
    if (result.length() < width) {
        result = std::string(width - result.length(), '0') + result;
    }
    return result;
}

void grid2d::save_to_file(std::string name) {
    std::string path = "../data/" + name;
    std::filesystem::create_directories(path);

    for (int j = 1; j < ny + 1; j++) {
        std::string filename = path + ".csv";

        std::ofstream file(filename);

        file << "x,value,time=" << y_coord[j - 1] << '\n';

        file << std::fixed << std::setprecision(6);
        for (int i = 1; i < nx + 1; i++) {
            file << x_coord[i - 1] << "," << value[i - 1][j - 1] << '\n';
        }

        file.close();
    }
}
