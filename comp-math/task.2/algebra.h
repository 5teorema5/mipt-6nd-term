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
    matrix(int x_size_, int y_size_, std::vector<double> content_array_);

    matrix(int x_size_, int y_size_);

    int get_x_size() const;

    int get_y_size() const;

    matrix transposition();

    matrix inverse() const;

    double &operator()(int i, int j);           // запись

    double operator()(int i, int j) const;      // чтение

    matrix operator+(const matrix &other) const;

    matrix operator-(const matrix &other) const;

    matrix operator*(double c) const;

    matrix operator/(double c) const;

    matrix operator*(const matrix &other) const;

    void print_matrix();
};

#endif