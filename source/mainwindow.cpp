#include <vector>
#include <fstream>
#include <QStringBuilder>
#include "./mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "./login.hpp"
#include "./diagowner.hpp"
#include "./dialognego.hpp"
#include "./cereal/archives/json.hpp"
#include "./cereal/archives/xml.hpp"
#include "./cereal/types/vector.hpp"
#include "./dialogpeticiones.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    std::ifstream myfile;
    myfile.open("../../data/data.json");
    cereal::JSONInputArchive ar(myfile);
    ar(this->listaOw);

    this->ui->listWidget_2->clear();
    for(auto &it : listaOw){
        this->ui->listWidget_2->addItem(it.getNombre().c_str());  // Convertir con c_string porque convierte implicitamente a QString
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_2_clicked() {
    Login log;
    log.setEstado(0);
    log.setModal(true);
    // Signal & slot mechanism with new syntax http://wiki.qt.io/New_Signal_Slot_Syntax
    connect(&log, &Login::cambioDeUsuario, this, &MainWindow::cambiarUsuario);
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
    for(auto &it : listaOw){
        this->ui->listWidget_2->addItem(it.getNombre().c_str());
    }

   guardarEnArchivo();
}

std::vector<Owner> &MainWindow::getOwners() { return this->listaOw; }

void MainWindow::on_actionNego_triggered() {
    DialogNego *ng = new DialogNego;
    ng->setOw(this->listaOw);
    ng->cargar();
    ng->setModal(true);
    ng->exec();

    guardarEnArchivo();

    // Refrescar la lista que corresponda - por ahora se limpia y hay que volver a hacer click
    this->ui->listWidget->clear();
}

void MainWindow::guardarEnArchivo(){
    std::ofstream myfile;
    myfile.open("../../data/data.json");
    cereal::JSONOutputArchive archive(myfile);
    archive(cereal::make_nvp("Owner", this->listaOw));
}

void MainWindow::cambiarUsuario(std::string nombre) {
    QString QNombre = QString::fromUtf8(nombre.c_str());
    this->ui->label_2->setText(QNombre);
}

void MainWindow::on_listWidget_2_pressed(const QModelIndex &index) {
    auto ow = this->listaOw.at(index.row());
    this->ui->listWidget->clear();
    for(auto it : ow.getNegos()){
        QString orDe = it.getOrigen().c_str();  // TODO:Se puede hacer en una linea?
        orDe.append(" - ");
        orDe.append(it.getDestino().c_str());
        this->ui->listWidget->addItem(orDe);
    }
}

void MainWindow::on_actionPeticion_triggered()
{
    DialogPeticiones* vpeticion = new DialogPeticiones;
}
