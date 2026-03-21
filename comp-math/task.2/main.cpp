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
    double h = 0.001;       // шаг по пространству
    double tau = 0.001;     // шаг по времени
    double CFL = 0.005;     // число Куранта меньше 0.01 для устойчивости

    matrix m = matrix(3, 3, std::vector<double>{9, 2, 3, 4, 5, 6, 7, 8, 9});
    matrix m_inv = m.inverse();
    m_inv.print_matrix();
    matrix res = (m * m_inv);
    res.print_matrix();

    return 0;
}

