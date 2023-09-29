#include "plotwindow.h"
#include "ui_mainwindow.h"



Pair task3(double x, Pair u) {
    return {u.second, -std::sin(x)};
}

void plotData3(QChart* chart) {
    QLineSeries *series = new QLineSeries();
    series->setColor(QColor(0, 0, 0));
    series->setName("точное решение");
    //series->setMarkerSize(8);
    // Generate the data points for the sine function
    for (double x = 0; x <= 4.0; x += 0.1)
    {
        double y = sin(x) - x + 1;
        series->append(x, y);
    }

    // Generate the data points for our function
    Pair u0(1, 0);
    std::vector<step_sys> v = solveIvp(task3, 0, u0, 0.00001, 4, 0.1, "RK4");
    QScatterSeries *series1 = new QScatterSeries();
    series1->setColor(QColor(247, 82, 0));
    series1->setName("численное решение u(x)");
    series1->setMarkerSize(8);
    for (auto s: v)
    {
        series1->append(s.x, s.v.first);
    }
    QScatterSeries *series2 = new QScatterSeries();
    series2->setColor(QColor(184, 70, 173));
    series2->setName("численное решение du/dx");
    series2->setMarkerSize(8);
    for (auto s: v)
    {
        series2->append(s.x, s.v.second);
    }
    chart->addSeries(series);
    chart->addSeries(series1);
    chart->addSeries(series2);
}

PlotWindow::PlotWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Create a line series to hold the data points



    // Create a chart and add the line series to it
    QChart *chart = new QChart();
    chart-> setAnimationOptions (QChart :: AllAnimations);
    chart->setLocalizeNumbers (true); // локализованы ли числа
    plotData3(chart);
    chart->createDefaultAxes();

    // Create a chart view and set the chart as its model
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);

}

PlotWindow::~PlotWindow()
{
    delete ui;
}

