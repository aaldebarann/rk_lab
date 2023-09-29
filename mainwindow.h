#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "plotwindow.h"
#include "task3window.h"
#include "task3_1window.h"
#include "table3window.h"
#include "table2window.h"
#include "task2window.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *m_button;
    QPushButton *m_button2;

    Task3Window* wplot3;
    task3_1Window* wplot31;
    Table3Window* wtable3;

    Task2Window* wplot2;
    Table2Window* wtable2;
private slots:
    void handleButton();
    void handleButton2();
};

#endif // MAINWINDOW_H
