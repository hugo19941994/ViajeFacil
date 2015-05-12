#include <vector>
#include <fstream>
#include <string>
#include <QStringBuilder>
#include "./mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "./login.hpp"
#include "./diagowner.hpp"
#include "./dialognego.hpp"
#include "./cereal/archives/json.hpp"
#include "./cereal/types/vector.hpp"
#include "./dialogpeticiones.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // TODO: Comprobar si existe
    std::ifstream myfile;
    myfile.open("../../data/data.json");
    cereal::JSONInputArchive ar(myfile);
    ar(this->listaOw);

    this->ui->listWidget_2->clear();
    for (auto &it : listaOw) {
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

void MainWindow::guardarEnArchivo() {
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
    for (auto it : ow.getNegos()) {
        QString orDe = it.getOrigen().c_str();  // TODO:Se puede hacer en una linea?
        orDe.append(" - ");
        orDe.append(it.getDestino().c_str());
        this->ui->listWidget->addItem(orDe);
    }

    // TODO: Cuando este oficinas hecho agregar
    // aqui el codigo de refresco de oficinas
}

void MainWindow::on_actionCrePeticion_triggered() {
    DialogPeticiones peticiones;
    peticiones.setOw(this->listaOw);
    peticiones.cargar();
    peticiones.setModal(true);
    peticiones.exec();

    this->ui->listWidget_4->clear();
    for (auto &it : listaOw){
        this->ui->listWidget_4->addItem(it.getNombre().c_str());
    }
}

void MainWindow::on_actionCreNego_triggered()
{
    DialogNego *ng = new DialogNego;
    ng->setOw(this->listaOw);
    ng->cargar();
    ng->setModal(true);
    ng->exec();

    guardarEnArchivo();

    // Refrescar la lista que corresponda - por ahora se limpia y hay que volver a hacer click
    this->ui->listWidget->clear();
}

void MainWindow::on_actionCreOwner_triggered()
{
    diagOwner ow;
    ow.setOw(this->listaOw);
    ow.setModal(true);
    ow.exec();

    this->ui->listWidget_2->clear();
    for (auto &it : listaOw) {
        this->ui->listWidget_2->addItem(it.getNombre().c_str());
    }

   guardarEnArchivo();
}

void MainWindow::on_actionCreUsuario_triggered()
{
    Login log;
    log.setModal(true);
    log.setEstado(1);
    log.exec();
}

void MainWindow::on_actionBorOwner_triggered()
{
    // TODO: Preguntar si estas seguro de borrar owner y mostrar datos

    // Calcular el indice del owner seleccionado y borrarlo
    QListWidgetItem *selected = this->ui->listWidget_2->selectedItems().first();
    if(selected != NULL)  // ARREGLAR - NO FUNCIONA
        listaOw.erase(listaOw.begin() + this->ui->listWidget_2->row(selected));

    this->ui->listWidget_2->clear();
    for (auto &it : listaOw) {
        this->ui->listWidget_2->addItem(it.getNombre().c_str());
    }

    guardarEnArchivo();
}

void MainWindow::on_actionModOwner_triggered()
{
    QListWidgetItem *selected = this->ui->listWidget_2->selectedItems().first();

    diagOwner ow;
    ow.setOw(this->listaOw);
    ow.setRow(this->ui->listWidget_2->row(selected)); // Le pasamos el indice del owner que queremos modificar
    ow.setMod();
    ow.setModal(true);
    ow.exec();

    this->ui->listWidget_2->clear();
    for (auto &it : listaOw) {
        this->ui->listWidget_2->addItem(it.getNombre().c_str());
    }

   guardarEnArchivo();
}

void MainWindow::on_actionModNego_triggered()
{
    QListWidgetItem *selectedOwner = this->ui->listWidget_2->selectedItems().first();
    QListWidgetItem *selectedNego = this->ui->listWidget->selectedItems().first();

    DialogNego *ng = new DialogNego;
    ng->setOw(this->listaOw);
    ng->cargar();
    ng->setRows(this->ui->listWidget_2->row(selectedOwner),
                this->ui->listWidget->row(selectedNego));
    ng->setMod();
    ng->setModal(true);
    ng->exec();

    guardarEnArchivo();

    // Refrescar la lista que corresponda - por ahora se limpia y hay que volver a hacer click
    this->ui->listWidget->clear();
}

void MainWindow::on_actionBorNego_triggered()
{
    QListWidgetItem *selectedOwner = this->ui->listWidget_2->selectedItems().first();
    QListWidgetItem *selectedNego = this->ui->listWidget->selectedItems().first();

    std::vector<Nego> &listaNegos = listaOw.at(this->ui->listWidget_2->row(selectedOwner)).getNegos();
    listaNegos.erase(listaNegos.begin() + this->ui->listWidget->row(selectedNego));

    // TODO: Refrescar la lista de negos que toque
    this->ui->listWidget->clear();

    guardarEnArchivo();
}
