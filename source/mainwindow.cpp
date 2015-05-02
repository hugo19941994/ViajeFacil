#include <vector>
#include <fstream>
#include "./mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "./login.hpp"
#include "./diagowner.hpp"
#include "./dialognego.hpp"
#include "./cereal/archives/json.hpp"
#include "./cereal/types/vector.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_2_clicked() {
    Login log;
    log.setEstado(0);
    log.setModal(true);
    log.exec();
}

void MainWindow::on_actionUsuario_triggered() {
    Login log;
    log.setModal(true);
    log.setEstado(1);
    log.exec();
}

void MainWindow::on_actionOwner_triggered() {
    diagOwner ow;
    ow.setOw(this->listaOw);
    ow.setModal(true);
    ow.exec();

    this->ui->listWidget_2->clear();
    for (std::vector<Owner>::iterator it = this->listaOw.begin(); it != this->listaOw.end(); ++it) {
        this->ui->listWidget_2->addItem(it->getNombre());
    }

    std::ofstream myfile;
    myfile.open("../../data/data.json");
    std::vector<int> list;
    list.push_back(0);
    list.push_back(2);
    cereal::JSONOutputArchive archive(myfile);
    archive(cereal::make_nvp("Owner", this->listaOw));
}

std::vector<Owner> &MainWindow::getOwners() { return this->listaOw; }

void MainWindow::on_actionNego_triggered() {
    DialogNego ng;
    ng.setOw(this->listaOw);
    ng.setModal(true);
    ng.exec();
}
