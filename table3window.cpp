#include "table3window.h"
#include "ui_table3window.h"

Table3Window::Table3Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Table3Window)
{
    ui->setupUi(this);
    setWindowTitle("Таблица вычислений");
    // Create the table widget
    QTableWidget* tableWidget = new QTableWidget(this);

    // Set the number of rows and columns
    // Set the number of rows and columns in the table
    tableWidget->setColumnCount(3);
    tableWidget->setRowCount(1);

    // Set the column headers
    QStringList* headers = new QStringList();
    (*headers) << "Column A" << "Column B" << "Column C";
    tableWidget->setHorizontalHeaderLabels(*headers);
    // Set the table to stretch horizontally
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Add a row to the table with values "1", "2", and "3"
    QTableWidgetItem *item1 = new QTableWidgetItem("1");
    QTableWidgetItem *item2 = new QTableWidgetItem("2");
    QTableWidgetItem *item3 = new QTableWidgetItem("3");
    tableWidget->setItem(0, 0, item1);
    tableWidget->setItem(0, 1, item2);
    tableWidget->setItem(0, 2, item3);

    tableWidget->show();
    setCentralWidget(tableWidget);
}

Table3Window::~Table3Window()
{
    delete ui;
}
