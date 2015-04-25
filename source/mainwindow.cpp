#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "diagowner.h"

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
	log.setEstado(0);
    log.setModal(true);
    log.exec();

}

void MainWindow::on_actionUsuario_triggered()
{
    Login log;
    log.setModal(true);
    log.setEstado(1);
    log.exec();

}

void MainWindow::on_actionOwner_triggered()
{
    diagOwner ow;
    //ow.setParent(this);
    ow.setOw(this->listaOw);
    ow.setModal(true);
    ow.exec();
}

std::vector<Owner> &MainWindow::getOwners() { return this->listaOw; }

void MainWindow::on_pushButton_3_clicked()
{
    this->ui->listWidget->clear();
    for(std::vector<Owner>::iterator it = this->listaOw.begin();it != this->listaOw.end();++it){

        this->ui->listWidget->addItem(it->getNombre());
    }
}
