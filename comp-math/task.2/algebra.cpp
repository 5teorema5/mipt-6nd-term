#include "algebra.h"

matrix::matrix(int x_size_, int y_size_, std::vector<double> new_content) : x_size(x_size_), y_size(y_size_) {
    if (x_size * y_size != new_content.size()) {
        std::cout << "Matrix size error" << '\n';
    } else {
        content.resize(y_size);
        for (int j = 0; j < y_size; j++) {
            content[j].resize(x_size);
            for (int i = 0; i < x_size; i++) {
                content[j][i] = new_content[i + j * x_size];
            }
        }
    }
}

int matrix::get_x_size() {
    return x_size;
}

int matrix::get_y_size() {
    return y_size;
}

matrix matrix::operator*(matrix &other) {
    if (this->x_size != other.get_y_size()) {
        std::cout << "Matrix multiplication error" << '\n';
        return matrix(0, 0, std::vector<double>());
    } else {
        int new_x = other.get_x_size();
        int new_y = y_size;
        std::vector<double> new_content(new_x * new_y);
        for (int j = 0; j < new_y; j++) {
            for (int i = 0; i < new_x; i++) {
                double sum = 0;
                for (int k = 0; k < x_size; k++) {
//                    std::cout << content[k][j] << " * " << other.content[j][k] << '\n';
                    sum += content[j][k] * other.content[k][i];
                }
                new_content[i + j * new_x] = sum;
            }
        }
        return matrix(new_x, new_y, new_content);
    }
}

void matrix::print_matrix() {
    for (int j = 0; j < y_size; j++) {
        for (int i = 0; i < x_size; i++) {
            std::cout << content[j][i] << " ";
        }
        std::cout << '\n';
    }
}
