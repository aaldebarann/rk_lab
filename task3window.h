#ifndef TASK3WINDOW_H
#define TASK3WINDOW_H

#include <QMainWindow>
#include "rk.h"
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QtCharts>
#include <cmath>
namespace Ui {
class Task3Window;
}

class Task3Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Task3Window(QWidget *parent = nullptr);
    ~Task3Window();

private:
    Ui::Task3Window *ui;
    static Pair function(double x, Pair u) {
        return {u.second, -std::sin(x)};
    }

};

#endif // TASK3WINDOW_H
