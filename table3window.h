#ifndef TABLE3WINDOW_H
#define TABLE3WINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QHeaderView>

namespace Ui {
class Table3Window;
}

class Table3Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Table3Window(QWidget *parent = nullptr);
    ~Table3Window();

private:
    Ui::Table3Window *ui;
};

#endif // TABLE3WINDOW_H
