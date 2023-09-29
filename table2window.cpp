#include "table2window.h"
#include "ui_table2window.h"
#include <string>
#include <cstring>
#include <charconv>
#include <sstream>
#include <iomanip>

using std::string;
using std::to_string;

#define TOSTRS(x) (doubleToScientificString(x).c_str())
#define TOSTR(x) (to_string(x).c_str())

std::string doubleToScientificString(double value) {
    std::ostringstream oss;
    oss << std::scientific << std::setprecision(6) << value;
    return oss.str();
}



Table2Window::Table2Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Table2Window)
{
    ui->setupUi(this);
    setWindowTitle("Таблица вычислений");
    // Create the table widget
    QTableWidget* tableWidget = new QTableWidget(this);

    // Set the number of rows and columns
    // Set the number of rows and columns in the table
    tableWidget->setColumnCount(9);


    // Set the column headers
    QStringList* headers = new QStringList();
    (*headers) << "Шаг" << "x" << "v"<<"v2"<<"v - v2"<<"ОЛП"<<"h"<<"c1"<<"c2";
    tableWidget->setHorizontalHeaderLabels(*headers);
    // Set the table to stretch horizontally
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Add a row to the table with values "1", "2", and "3"
    std::vector<step> v = solveIvp(function, 0, 1, 0.00001, 0.48, 0.01, "RK4");
    tableWidget->setRowCount(v.size());
    int i = 0;
    for(auto s: v) {
        tableWidget->setItem(i, 0, new QTableWidgetItem(TOSTR(i)));
        tableWidget->setItem(i, 1, new QTableWidgetItem(TOSTR(s.x)));
        tableWidget->setItem(i, 2, new QTableWidgetItem(TOSTR(s.v)));
        tableWidget->setItem(i, 3, new QTableWidgetItem(TOSTR(s.v2)));
        tableWidget->setItem(i, 4, new QTableWidgetItem(TOSTRS(s.v - s.v2)));
        tableWidget->setItem(i, 5, new QTableWidgetItem(TOSTRS(s.le)));
        tableWidget->setItem(i, 6, new QTableWidgetItem(TOSTRS(s.h)));
        tableWidget->setItem(i, 7, new QTableWidgetItem(TOSTR(s.C1)));
        tableWidget->setItem(i, 8, new QTableWidgetItem(TOSTR(s.C2)));
        i++;
    }

    tableWidget->show();
    setCentralWidget(tableWidget);
}

Table2Window::~Table2Window()
{
    delete ui;
}
