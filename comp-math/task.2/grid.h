#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

class grid2d{
private:
    double L, T;
    double h, t;
    int nx, ny;

    std::vector<double> x_coord;
    std::vector<double> y_coord;
    std::vector<std::vector<double>> value;

public:
    grid2d(double L_, double T_, double h_, double t_);

    double get_L();

    double get_T();

    double get_h();

    double get_t();

    double get_nx();

    double get_ny();

    double get_value(double i, double j);

    void set_value(double i, double j, double val);

    void clear_value();
    
    void print_grid();

    void print_all_value();

    std::string formatIndex(int index, int width);

    void save_to_file(std::string name);
};

#endif