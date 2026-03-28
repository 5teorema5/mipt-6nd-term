#ifndef THERIEMANPROBLEM_STATE_H
#define THERIEMANPROBLEM_STATE_H

struct state {
    double u;       // скорость, м/с
    double rho;     // плотность, кг/м3
    double p;       // давление, Па
    double e;       // удельная внутренняя энергия, Дж/кг

    state() : u(0), rho(0), p(0), e(0) {}

    state(double u_, double rho_, double p_, double e_) : u(u_), rho(rho_), p(p_), e(e_) {}

    // консервативные переменные
    std::vector<double> toCons() const {
        return std::vector<double>{rho, rho * u, rho * e};
    }

    static state fromCons(std::vector<double> toCons_, double gamma) {
        double rho = toCons_[0];
        double u = toCons_[1] / rho;
        double e = toCons_[2] / rho;
        double p = (gamma - 1) * rho * e;
        return state(u, rho, p, e);
    }

    // скорость звука
    double calculete_c(double gamma) const {
        return sqrt(gamma * p / rho);
    }

    void calculate_e(double gamma) {
        e = p / ((gamma - 1) * rho);
    }
};

#endif //THERIEMANPROBLEM_STATE_H
