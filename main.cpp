#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    setlocale(LC_ALL, "RU");
    double alpha = 0.1;
    double beta = 0.002;
    double gamma = 0.1;
    double delta = 0.001;
    double t = 0.0;
    double ted = 365.0;
    double dt = 0.1;
    double x_start = 100.1;
    double y_start = 50.1;
    double x_e = x_start, y_e = y_start;   
    double x_rk = x_start, y_rk = y_start; 
    std::ofstream fout("results.txt");
    fout << "Time\tPrey_Euler\tPred_Euler\tPrey_RK2\tPred_RK2" << std::endl;
    while (t <= ted) {
        fout << std::fixed << std::setprecision(3)
            << t << "\t" << x_e << "\t" << y_e << "\t" << x_rk << "\t" << y_rk << "\n";
        double dx_e = (alpha - beta * y_e) * x_e;
        double dy_e = (-gamma + delta * x_e) * y_e;
        x_e += dt * dx_e;
        y_e += dt * dy_e;
        double k1x = (alpha - beta * y_rk) * x_rk;
        double k1y = (-gamma + delta * x_rk) * y_rk;
        double xt = x_rk + dt * k1x;
        double yt = y_rk + dt * k1y;
        double k2x = (alpha - beta * yt) * xt;
        double k2y = (-gamma + delta * xt) * yt;
        x_rk += (dt / 2.0) * (k1x + k2x);
        y_rk += (dt / 2.0) * (k1y + k2y);
        t += dt;
    }

    fout.close();
    return 0;
}