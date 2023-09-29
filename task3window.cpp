#include "task3window.h"
#include "ui_task3window.h"

Task3Window::Task3Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Task3Window)
{
    ui->setupUi(this);
    setWindowTitle("График решения ДУ y = u(x)");



    // Create a line series to hold the data points

    QLineSeries *exactSolutionSeries = new QLineSeries();
    exactSolutionSeries->setColor(QColor(0, 0, 0));
    exactSolutionSeries->setName("точное решение");
    // Generate the data points
    for (double x = 0; x <= 4.0; x += 0.1)
    {
        double y = sin(x) - x + 1;
        exactSolutionSeries->append(x, y);
    }

    Pair u0(1, 0);
    std::vector<step_sys> v = solveIvp(function, 0, u0, 0.00001, 4, 0.1, "RK4");
    QScatterSeries *approximateSeries = new QScatterSeries();
    approximateSeries->setColor(QColor(247, 82, 0));
    approximateSeries->setName("численное решение");
    approximateSeries->setMarkerSize(8);
    for (auto s: v)
    {
        approximateSeries->append(s.x, s.v.first);
    }
    // Create a chart and add the line series to it
    QChart *chart = new QChart();
    chart-> setAnimationOptions (QChart :: AllAnimations);
    chart->setLocalizeNumbers (true); // локализованы ли числа
    chart->addSeries(exactSolutionSeries);
    chart->addSeries(approximateSeries);
    chart->createDefaultAxes();

    // Create a chart view and set the chart as its model
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
}

Task3Window::~Task3Window()
{
    delete ui;
}
