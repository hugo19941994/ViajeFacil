#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "mainwindow2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void openNewWindow2();

private:
    Ui::MainWindow *ui;
    //Ui::MainWindow2 *ui2;
};

#endif // MAINWINDOW_H
