#include "grid.h"

grid2d::grid2d(double L_, double T_, double h_, double t_) : L(L_), T(T_), h(h_), t(t_) {
    nx = L / h + 1;
    ny = 1;

    x_coord.resize(nx);
    for (int i = 0; i < nx; i++) {
        x_coord[i] = i * h;
    }
    y_coord.resize(ny);
    for (int j = 0; j < ny; j++) {
        y_coord[j] = j * t;
    }
    u_value.resize(nx);
    v_value.resize(nx);
    for (int i = 0; i < nx; i++) {
        u_value[i].resize(ny, 0.0);
        v_value[i].resize(ny, 0.0);
    }
}

void grid2d::add_time_layer(double time) {
    ny++;
    y_coord.push_back(time);
    for (int i = 0; i < nx; i++) {
        u_value[i].push_back(0.0);
        v_value[i].push_back(0.0);
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

int grid2d::get_nx() {
    return this->nx;
}

int grid2d::get_ny() {
    return this->ny;
}

double grid2d::get_u(int i, int j) const {
    return u_value[i-1][j-1];
}

double grid2d::get_v(int i, int j) const {
    return v_value[i-1][j-1];
}

void grid2d::set_u(int i, int j, double val) {
    u_value[i-1][j-1] = val;
}

void grid2d::set_v(int i, int j, double val) {
    v_value[i-1][j-1] = val;
}

void grid2d::save_to_file(std::string name) {
    std::string path = "../data/";
    std::filesystem::create_directories(path);

    std::string filename_u = path + name + "_u.csv";
    std::ofstream file_u(filename_u);

    if (file_u.is_open()) {
        file_u << "time";
        for (int i = 1; i <= nx; i++) {
            file_u << ",x=" << std::fixed << std::setprecision(6) << x_coord[i-1];
        }
        file_u << "\n";
        for (int j = 1; j <= ny; j++) {
            file_u << std::fixed << std::setprecision(8) << y_coord[j-1];
            for (int i = 1; i <= nx; i++) {
                file_u << "," << u_value[i-1][j-1];
            }
            file_u << "\n";
        }
        file_u.close();
        std::cout << "Saved u to " << filename_u << std::endl;
    } else {
        std::cerr << "Error: Cannot open file " << filename_u << std::endl;
    }
    std::string filename_v = path + name + "_v.csv";
    std::ofstream file_v(filename_v);

    if (file_v.is_open()) {
        file_v << "time";
        for (int i = 1; i <= nx; i++) {
            file_v << ",x=" << std::fixed << std::setprecision(6) << x_coord[i-1];
        }
        file_v << "\n";
        for (int j = 1; j <= ny; j++) {
            file_v << std::fixed << std::setprecision(8) << y_coord[j-1];
            for (int i = 1; i <= nx; i++) {
                file_v << "," << v_value[i-1][j-1];
            }
            file_v << "\n";
        }
        file_v.close();
        std::cout << "Saved v to " << filename_v << std::endl;
    } else {
        std::cerr << "Error: Cannot open file " << filename_v << std::endl;
    }
}