#ifndef TABLE2WINDOW_H
#define TABLE2WINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QHeaderView>
#include "rk.h"
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QtCharts>
#include <cmath>

namespace Ui {
class Table2Window;
}

class Table2Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Table2Window(QWidget *parent = nullptr);
    ~Table2Window();

private:
    Ui::Table2Window *ui;
    static double function(double x, double u) {
        return 1.0 / (1 + x*x*x*x)* u*u + u - u*u*u * std::sin(10*x);
    }
};

#endif // TABLE2WINDOW_H
