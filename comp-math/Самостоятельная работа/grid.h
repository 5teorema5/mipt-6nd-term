#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

class grid2d {
private:
    double L, T;
    double h, t;
    int nx, ny;

    std::vector<double> x_coord;
    std::vector<double> y_coord;
    std::vector<std::vector<double>> u_value;
    std::vector<std::vector<double>> v_value;

public:
    grid2d(double L_, double T_, double h_, double t_);

    void add_time_layer(double time);

    double get_L();

    double get_T();

    double get_h();

    double get_t();

    int get_nx();

    int get_ny();

    double get_u(int i, int j) const;

    double get_v(int i, int j) const;

    void set_u(int i, int j, double val);

    void set_v(int i, int j, double val);

    void save_to_file(std::string name);
};

#endif