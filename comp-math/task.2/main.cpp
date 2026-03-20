#include <iostream>
#include "algebra.h"

struct init_data {
    double v_L;  // 
    double ro_L; // кг/м3
    double P_L;  // атм
};


int main() {
    int L = 10;
    double gamma = 5.0 / 3.0;
    init_data left = {0.0, 13.0, 10.0};
    init_data right = {0.0, 1.3, 1.0};

    std::vector<double> c1 = {1, 2, -1, 3, 4, 0,};
    matrix m1(3, 2, c1);
    m1.print_matrix();

    std::cout << '\n';

    std::vector<double> c2 = {5, 6, 7, 8,};
    matrix m2(2, 2, c2);
    m2.print_matrix();

    std::cout << '\n';

    matrix m3 = m2 * m1;
    m3.print_matrix();

    return 0;
}

