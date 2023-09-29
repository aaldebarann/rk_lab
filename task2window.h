#ifndef TASK2WINDOW_H
#define TASK2WINDOW_H


#include <QMainWindow>
#include "rk.h"
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QtCharts>
#include <cmath>

namespace Ui {
class Task2Window;
}

class Task2Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Task2Window(QWidget *parent = nullptr);
    ~Task2Window();

private:
    Ui::Task2Window *ui;
    static double function(double x, double u) {
        return 1.0 / (1 + x*x*x*x)* u*u + u - u*u*u * std::sin(10*x);
    }
};

#endif // TASK2WINDOW_H
