#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"

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

void MainWindow::on_pushButton_2_clicked()
{
    Login log;
    log.setModal(true);
    log.exec();
}
