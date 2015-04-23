#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow2.h"

MainWindow2 * w = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    QMainWindow *MainWindow2 = new MainWindow2::MainWindow2();
//    //w.setModal(true);
//    MainWindow2->show();
//    this->hide();
    w = new MainWindow2();
    w->show();
}
