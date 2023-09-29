#ifndef TASK3_1WINDOW_H
#define TASK3_1WINDOW_H

#include <QMainWindow>
#include "rk.h"
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QtCharts>
#include <cmath>


namespace Ui {
class task3_1Window;
}

class task3_1Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit task3_1Window(QWidget *parent = nullptr);
    ~task3_1Window();

private:
    Ui::task3_1Window *ui;
    static Pair function(double x, Pair u) {
        return {u.second, -std::sin(x)};
    }

};

#endif // TASK3_1WINDOW_H
