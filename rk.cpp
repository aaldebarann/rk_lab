#include "rk.h"

// РЕШЕНИЕ УРАВНЕНИЙ
// шаг метода
std::pair<double, double> RK2(double (*f)(double, double), double x0, double u0, double h) {
    double x = x0, v = u0; // x_n, v_n - значения на текущем шаге
    double xx, vv; // x_n+1, v_n+1 - значения на следующем шаге
    xx = x + h;
    double k1 = f(x, v);
    double k2 = f(x + h / 2, v + k1 * h / 2);
    vv = v + k2 * h;
    return {xx, vv};
}
std::pair<double, double> RK4(double (*f)(double, double), double x0, double u0, double h) {
    double x = x0, v = u0; // x_n, v_n - значения на текущем шаге
    double xx, vv; // x_n+1, v_n+1 - значения на следующем шаге
    xx = x + h;
    double k1 = f(x, v);
    double k2 = f(x + h / 2, v + k1 * h / 2);
    double k3 = f(x + h / 2, v + k2 * h / 2);
    double k4 = f(x + h, v + k3 * h);
    vv = v + (k1 + 2*k2 + 2*k3 + k4) * h / 6;
    return {xx, vv};
}
// численное интегрирование
std::vector<step> solveIvp(double (*f)(double , double), double x0, double u0, double eps, double xMax, double borderEps,
                           const std::string& method, bool variableStep) {

    std::pair<double, double> (*RK)(double (*f)(double, double), double, double, double);
    size_t order;
    if(method == "RK2") {
        RK = RK2;
        order = 2;
    } else if(method == "RK4") {
        RK = RK4;
        order = 4;
        // TODO: check
    } else {
        throw std::invalid_argument("Unknow method. Available methods: \"RK2\".");
    }

    double h = 0.001; // шаг
    double le = 0; // локальная погрешность
    size_t C1 = 0, C2 = 0; // счетчики деления шага и удвоения шага
    std::vector<step> result;
    result.emplace_back(x0, u0, h, le, u0, 0, 0);
    double x = x0, v = u0; // координаты последней посчитанной точки
    std::pair<double, double> p1, p2, p3;
    while(xMax - x > borderEps) {
        p1 = RK(f, x, v, h); // делаем шаг из (x, v)
        p2 = RK(f, x, v, h/2); // делаем половинный шаг из (x, v)
        p3 = RK(f, p2.first, p2.second, h/2); // делаем половинный шаг из (x_+1/2, v_+1/2)

        double s = (p1.second - p3.second) / ((1 << order) - 1.0);
        le = s * (1 << order);

        if((!variableStep) || std::abs(s) <= eps) {
            // принимается значение, откорректированное на оценку локальной погрешности
            x = p1.first;
            v = p1.second + eps;
            if(variableStep && std::abs(s) < eps / (1 << (order+1)) ) {
                // шаг удваивается
                h *= 2;
                C2++;
            }
            result.emplace_back(x, v, h, le, p3.second, C1, C2);
            // C1 = C2 = 0;
        } else {
            // значение не принимается, требуется пересчёт с половинным шагом
            h /= 2;
            C1++;
            // проверка на близость к вертикальной асимптоте
            if(h < 0.00000001)
                break;
        }
    }
    return result;
}

// РЕШЕНИЕ СИСТЕМ УРАВНЕНИЙ (ВТОРОГО ПОРЯДКА)

// шаг метода
std::pair<double, Pair> RK2_sys(Pair (*f)(double, Pair), double x0, Pair u0, double h) {
    // значения на текущем шаге
    double x = x0; // x_n
    Pair v = u0; // v_n
    // x_n+1, v_n+1 - значения на следующем шаге
    double xx; // x_n+1
    Pair vv;  // v_n+1

    xx = x + h;
    Pair k1 = f(x, v) * h;
    Pair k2 = f(x + h / 2, v + k1 / 2) * h;
    vv = v + k2;
    return {xx, vv};
}
std::pair<double, Pair> RK4_sys(Pair (*f)(double, Pair), double x0, Pair u0, double h) {
    // значения на текущем шаге
    double x = x0; // x_n
    Pair v = u0; // v_n
    // x_n+1, v_n+1 - значения на следующем шаге
    double xx; // x_n+1
    Pair vv;  // v_n+1

    xx = x + h;
    Pair k1 = f(x, v);
    Pair k2 = f(x + h / 2, v + k1 * h / 2);
    Pair k3 = f(x + h / 2, v + k2 * h / 2);
    Pair k4 = f(x + h, v + k3 * h);
    vv = v + (k1 + k2 * 2 + k3 * 2 + k4) * h / 6;
    return {xx, vv};
}
std::vector<step_sys> solveIvp(Pair (*f)(double , Pair), double x0, Pair u0, double eps, double xMax, double borderEps,
                           const std::string& method, bool variableStep) {

    std::pair<double, Pair> (*RK)(Pair (*f)(double, Pair), double, Pair, double);
    size_t order;
    if(method == "RK2") {
        RK = RK2_sys;
        order = 2;
    } else if(method == "RK4") {
        RK = RK4_sys;
        order = 4;
    } else {
        throw std::invalid_argument("Unknow method. Available methods: \"RK2\".");
    }
    double h = 0.0001; // шаг
    double le = 0; // локальная погрешность
    size_t C1 = 0, C2 = 0; // счетчики деления шага и удвоения шага
    std::vector<step_sys> result;
    result.emplace_back(x0, u0, h, le, u0, 0, 0);
    // координаты последней посчитанной точки
    double x = x0;
    Pair v = u0;
    std::pair<double, Pair> p1, p2, p3;
    while(xMax - x > borderEps) {
        p1 = RK(f, x, v, h); // делаем шаг из (x, v)
        p2 = RK(f, x, v, h/2); // делаем половинный шаг из (x, v)
        p3 = RK(f, p2.first, p2.second, h/2); // делаем половинный шаг из (x_+1/2, v_+1/2)

        Pair s = (p1.second - p3.second) / ((1 << order) - 1.0);
        le = s.norm() * (1 << order);

        if((!variableStep) || s.norm() <= eps) {
            // принимается значение, откорректированное на оценку локальной погрешности
            x = p1.first;
            v = p1.second + eps;
            if(variableStep && s.norm() < eps / (1 << (order+1)) ) {
                // шаг удваивается
                h *= 2;
                C2++;
            }
            result.emplace_back(x, v, h, le, p3.second, C1, C2);
            // C1 = C2 = 0;
        } else {
            // значение не принимается, требуется пересчёт с половинным шагом
            h /= 2;
            C1++;
            // проверка на близость к вертикальной асимптоте
            if(h < 0.00000001)
                break;
        }
    }
    return result;
}
