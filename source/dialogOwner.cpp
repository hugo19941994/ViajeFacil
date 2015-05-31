/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  se van a implementar las funciones definidas previamente en diagowner.hpp
 */

#include "./ui_dialogOwner.h"
#include "./dialogOwner.hpp"

dialogOwner::dialogOwner(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogOwner) {
    ui->setupUi(this);
}

dialogOwner::~dialogOwner() { delete ui; }

void dialogOwner::on_buttonBox_accepted() {
    if (editando)
        ownerAEditar->setNombre(ui->lineEdit->text().toStdString());
}

void dialogOwner::setOwnerAEditar(Owner &ow) {
    editando = true;
    ownerAEditar = &ow;
    ui->lineEdit->setText(ownerAEditar->getNombre().c_str());
}

Owner dialogOwner::crear() {
    Owner ow {ui->lineEdit->text().toStdString()};
    return ow;
}
