#include "algebra.h"

matrix::matrix(int x_size_, int y_size_, std::vector<double> content_) : x_size(x_size_), y_size(y_size_) {
    if (x_size * y_size != content_.size()) {
        std::cout << "Matrix size error" << '\n';
    } else {
        content.resize(y_size);
        for (int j = 0; j < y_size; j++) {
            content[j].resize(x_size);
            for (int i = 0; i < x_size; i++) {
                content[j][i] = content_[i + j * x_size];
            }
        }
    }
}

matrix::matrix(int x_size_, int y_size_) : x_size(x_size_), y_size(y_size_) {
    content.resize(this->y_size);
    for (int j = 0; j < this->y_size; j++) {
        content[j].resize(this->x_size, 0.0);
    }
}

int matrix::get_x_size() const {
    return this->x_size;
}

int matrix::get_y_size() const {
    return this->y_size;
}

matrix matrix::transposition() {
    std::vector<double> t_content(x_size * y_size);
    for (int j = 0; j < this->y_size; j++) {
        for (int i = 0; i < this->x_size; i++) {
            t_content[j + i * y_size] = this->content[j][i];
        }
    }
    return matrix(this->y_size, this->x_size, t_content);
}

matrix matrix::inverse() const {
    if (this->x_size != this->y_size) {
        std::cout << "Matrix size error" << '\n';
        return matrix(this->x_size, this->y_size);
    } else if (this->x_size == 3) {
        std::vector<double> new_content(this->x_size * this->y_size, 0.0);
        double a11 = this->content[0][0], a12 = this->content[0][1], a13 = this->content[0][2],
                a21 = this->content[1][0], a22 = this->content[1][1], a23 = this->content[1][2],
                a31 = this->content[2][0], a32 = this->content[2][1], a33 = this->content[2][2];
        double det = a11 * (a22 * a33 - a32 * a23) - a21 * (a12 * a33 - a32 * a13) + a31 * (a12 * a23 - a22 * a13);

        if (std::abs(det) < 1e-12) {
            std::cout << "Error: detA = 0" << '\n';
            return matrix(this->x_size, this->y_size);
        } else {
            new_content[0] = +(a22 * a33 - a32 * a23);
            new_content[1] = -(a12 * a33 - a32 * a13);
            new_content[2] = +(a12 * a23 - a22 * a13);

            new_content[3] = -(a12 * a33 - a13 * a32);
            new_content[4] = +(a11 * a33 - a13 * a31);
            new_content[5] = -(a11 * a32 - a12 * a31);

            new_content[6] = +(a12 * a23 - a13 * a22);
            new_content[7] = -(a11 * a23 - a13 * a21);
            new_content[8] = +(a11 * a22 - a12 * a21);

            return matrix(this->x_size, this->y_size, new_content).transposition() / det;
        }
    } else {
        std::cout << "In development..." << '\n';
        return matrix(this->x_size, this->y_size);
    }
}

double& matrix::operator()(int i, int j) {
    if (i >= this->x_size or j >= this->y_size) {
        std::cout << "Matrix size error" << '\n';
    } else {
        return this->content[j][i];
    }
}

double matrix::operator()(int i, int j) const {
    if (i >= this->x_size or j >= this->y_size) {
        std::cout << "Matrix size error" << '\n';
        return 0;
    } else {
        return this->content[j][i];
    }
}

matrix matrix::operator+(const matrix &other) const {
    if (this->x_size != other.x_size or this->y_size != other.y_size) {
        std::cout << "Matrix size error" << '\n';
        return matrix(0, 0);
    } else {
        std::vector<double> new_content(this->x_size * this->y_size);
        for (int j = 0; j < this->y_size; j++) {
            for (int i = 0; i < this->x_size; i++) {
                new_content[i + j * this->x_size] = this->content[j][i] + other(i, j);
            }
        }
        return matrix(this->x_size, this->y_size, new_content);
    }
}

matrix matrix::operator-(const matrix &other) const {
    if (this->x_size != other.x_size or this->y_size != other.y_size) {
        std::cout << "Matrix size error" << '\n';
        return matrix(0, 0);
    } else {
        std::vector<double> new_content(this->x_size * this->y_size);
        for (int j = 0; j < this->y_size; j++) {
            for (int i = 0; i < this->x_size; i++) {
                new_content[i + j * this->x_size] = this->content[j][i] - other(i, j);
            }
        }
        return matrix(this->x_size, this->y_size, new_content);
    }
}

matrix matrix::operator*(double c) const {
    std::vector<double> new_content(this->x_size * this->y_size);
    for (int j = 0; j < this->y_size; j++) {
        for (int i = 0; i < this->x_size; i++) {
            new_content[i + j * this->x_size] = c * this->content[j][i];
        }
    }
    return matrix(this->x_size, this->y_size, new_content);
}

matrix matrix::operator/(double c) const {
    std::vector<double> new_content(this->x_size * this->y_size);
    for (int j = 0; j < this->y_size; j++) {
        for (int i = 0; i < this->x_size; i++) {
            new_content[i + j * this->x_size] = this->content[j][i] / c;
        }
    }
    return matrix(this->x_size, this->y_size, new_content);
}

std::vector<double> matrix::operator*(const std::vector<double> other) const {
    if (this->x_size != other.size()) {
        std::cout << "Matrix-vector multiplication error" << '\n';
        return std::vector<double>();
    }
    std::vector<double> result(y_size, 0.0);
    for (int j = 0; j < y_size; j++) {
        double sum = 0;
        for (int i = 0; i < x_size; i++) {
            sum += content[j][i] * other[i];
        }
        result[i] = sum;
    }
    return result;
}

matrix matrix::operator*(const matrix &other) const {
    if (this->x_size != other.y_size) {
        std::cout << "Matrix multiplication error" << '\n';
        return matrix(0, 0, std::vector<double>());
    } else {
        int new_x = other.x_size;
        int new_y = y_size;
        std::vector<double> new_content(new_x * new_y);
        for (int j = 0; j < new_y; j++) {
            for (int i = 0; i < new_x; i++) {
                double sum = 0;
                for (int k = 0; k < x_size; k++) {
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
