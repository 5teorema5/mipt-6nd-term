#ifndef ALGEBRA_H
#define ALGEBRA_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

class matrix {
private:
    int x_size;
    int y_size;
    std::vector<std::vector<double>> content;
public:
    matrix(int x_size_, int y_size_, std::vector<double> content_);

    int get_x_size();

    int get_y_size();

    matrix operator*(matrix &other);

    void print_matrix();
};

#endif