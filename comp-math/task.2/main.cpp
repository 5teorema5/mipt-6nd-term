#include <iostream>

struct init_data
{
    double v_L;  // 
    double ro_L; // кг/м3
    double P_L;  // атм
};


int main() {
    int L = 10;
    double gamma = 5/3;
    init_data left = {0.0, 13.0, 10.0};
    init_data right = {0.0, 1.3, 1.0};
    return 0;
}

