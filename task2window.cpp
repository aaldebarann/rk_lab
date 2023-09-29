#include "task2window.h"
#include "ui_task2window.h"

Task2Window::Task2Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Task2Window)
{
    ui->setupUi(this);
    setWindowTitle("График решения ДУ y = u(x)");

    std::vector<step> v = solveIvp(function, 0, 1, 0.00001, 0.48, 0.01, "RK4");
    QScatterSeries *approximateSeries = new QScatterSeries();
    approximateSeries->setColor(QColor(247, 82, 0));
    approximateSeries->setName("численное решение");
    approximateSeries->setMarkerSize(8);
    for (auto s: v)
    {
        approximateSeries->append(s.x, s.v);
    }
    // Create a chart and add the line series to it
    QChart *chart = new QChart();
    chart-> setAnimationOptions (QChart :: AllAnimations);
    chart->setLocalizeNumbers (true); // локализованы ли числа
    chart->addSeries(approximateSeries);
    chart->createDefaultAxes();

    // Create a chart view and set the chart as its model
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
}

Task2Window::~Task2Window()
{
    delete ui;
}
