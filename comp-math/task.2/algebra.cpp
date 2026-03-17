#include "algebra.h"

matrix::matrix(int x_size_, int y_size_, std::vector<double> new_content) : x_size(x_size_), y_size(y_size_) {
    content.resize(y_size_);
    for (int j = 0; j < y_size; j++) {
        std::vector<double> row;
        for (int i = 0; i < x_size; i++) {
            row.push_back(content_[i+j*x_size]);
        } 
    }
}