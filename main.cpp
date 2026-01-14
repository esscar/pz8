#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    setlocale(LC_ALL, "RU");

    // Твои подобранные параметры
    double alpha = 0.1;
    double beta = 0.002;
    double gamma = 0.1;
    double delta = 0.001;

    // Временные настройки
    double t = 0.0;
    double t_end = 365.0; // 365 дней
    double dt = 0.1;      // Шаг 0.1 дня (достаточно точно)

    // ВЫБЕРИ ОДИН ИЗ ВАРИАНТОВ НИЖЕ:
    // 1) Превышение корма: x=80, y=10
    // 2) Превышение хищников: x=10, y=80
    // 3) Превышение корма (макс): x=150, y=20
    // 4) Превышение хищников (макс): x=20, y=150
    double x_start = 100.1;
    double y_start = 50.1;

    double x_e = x_start, y_e = y_start;   // Для Эйлера
    double x_rk = x_start, y_rk = y_start; // Для РК-2

    std::ofstream fout("results.txt");
    fout << "Time\tPrey_Euler\tPred_Euler\tPrey_RK2\tPred_RK2" << std::endl;

    while (t <= t_end) {
        fout << std::fixed << std::setprecision(3)
            << t << "\t" << x_e << "\t" << y_e << "\t" << x_rk << "\t" << y_rk << "\n";

        // Метод Эйлера
        double dx_e = (alpha - beta * y_e) * x_e;
        double dy_e = (-gamma + delta * x_e) * y_e;
        x_e += dt * dx_e;
        y_e += dt * dy_e;

        // Метод Рунге-Кутты 2
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
    std::cout << "Расчет для x0=" << x_start << ", y0=" << y_start << " завершен." << std::endl;
    return 0;
}