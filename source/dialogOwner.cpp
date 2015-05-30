/*AUTORES: Hugo Ferrando
 *DESCRIPCION: se van a implementar las funciones definidas previamente en diagowner.hpp
 *
 */

#include "./dialogOwner.hpp"
#include "ui_dialogOwner.h"

/**
 * @brief dialogOwner::dialogOwner
 * @param parent
 */
dialogOwner::dialogOwner(QWidget *parent) :  // tipo de funcion del dialog owner

    QDialog(parent),
    /**
         * @brief ui
         */
    ui(new Ui::dialogOwner) {

    ui->setupUi(this);
}
/**
 * @brief dialogOwner::~dialogOwner
 */
dialogOwner::~dialogOwner() {  // destructor, se destruirán el o los datos seleccionados en owners
    delete ui;
}

// Funcion de aceptar en ventana de owner
/**
 * @brief dialogOwner::on_buttonBox_accepted
 */
void dialogOwner::on_buttonBox_accepted() {
    // datos guardados en linea de texto nombre
    if (editando) {
        ownerAEditar->setNombre(this->ui->lineEdit->text().toStdString());
    } else {
        Owner *newO = new Owner;  // Va bien declararlo sin new? en el stack?
        newO->setNombre(this->ui->lineEdit->text().toStdString());  // Se crea nuevo owner
        this->ow->push_back(*newO);  // Devuelve el nuevo owner introducido perteneciente al vector owner
    }
}

/**
 * @brief dialogOwner::setOw
 * @param own
 */
void dialogOwner::setOw(pel::vector<Owner> &own) {
    // Pide datos en owner y los muestra en lista
    this->ow = &own;
}

void dialogOwner::setOwnerAEditar(Owner &ow) {
    editando = true;
    ownerAEditar = &ow;
    ui->lineEdit->setText(ownerAEditar->getNombre().c_str());
}
