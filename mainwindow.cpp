#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::handleButton()
{
  // change the text
  m_button->setText("Example");
  // resize button
  m_button->resize(100,100);
  wplot3 = new Task3Window();
  wplot31 = new task3_1Window();
  wtable3 = new Table3Window();
  wplot3->show();
  wplot31->show();
  wtable3->show();
}

void MainWindow::handleButton2()
{
  // change the text
  m_button2->setText("Example2");
  // resize button
  m_button2->resize(100,100);
  wplot2 = new Task2Window();
  wplot2->show();
  wtable2 = new Table2Window();
  wtable2->show();
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the button, make "this" the parent
    m_button = new QPushButton("My Button", this);
    // set size and location of the button
    m_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

    // Connect button signal to appropriate slot
    connect(m_button, &QPushButton::released, this, &MainWindow::handleButton);



    // Create the button, make "this" the parent
    m_button2 = new QPushButton("My Button2", this);
    // set size and location of the button
    m_button2->setGeometry(QRect(QPoint(400, 400), QSize(200, 50)));

    // Connect button signal to appropriate slot
    connect(m_button2, &QPushButton::released, this, &MainWindow::handleButton2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
