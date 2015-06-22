/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  se van a implementar las funciones definidas previamente en diagowner.hpp
 */

#include <QMessageBox>
#include "./ui_dialogOwner.h"
#include "./dialogOwner.hpp"

dialogOwner::dialogOwner(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogOwner) {
    ui->setupUi(this);
}

dialogOwner::~dialogOwner() { delete ui; }

void dialogOwner::accept(){
    if (maybeSave) {
        done(1);  // Termina y emite accepted
    }
}

void dialogOwner::on_buttonBox_accepted() {
    maybeSave = true;
    if (editando) {
        if (ui->lineEdit->text().isEmpty()) {
            QMessageBox::information(this, "",QString ("Nombre no puede ser vacío"));
            maybeSave = false;
            accept();
        }

        for (auto it : *listaOw)
            if (ui->lineEdit->text().toStdString() == it.getNombre()) {
                QMessageBox::information(this, "",QString ("Ya hay un owner con este nombre"));
                maybeSave = false;
                accept();
            }

        if (maybeSave) {
            ownerAEditar->setNombre(ui->lineEdit->text().toStdString());
            maybeSave = true;
            accept();
        }
    }
    else {  // Creando un owner nuevo
        maybeSave = true;
        accept();
    }
}

void dialogOwner::setOwnerAEditar(Owner *ow) {
    editando = true;
    ownerAEditar = ow;
    ui->lineEdit->setText(ownerAEditar->getNombre().c_str());
}

Owner dialogOwner::crear() {
    Owner ow {ui->lineEdit->text().toStdString()};
    return ow;
}
