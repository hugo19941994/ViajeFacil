/*AUTORES: Hugo Ferrando
 *DESCRIPCION: se van a implementar las funciones definidas
 * previamente en diagowner.hpp
 */

#include "./ui_dialogOwner.h"
#include "./dialogOwner.hpp"


/**
 * @brief dialogOwner::dialogOwner
 * @param parent
 * tipo de funcion del dialog owner
 */
dialogOwner::dialogOwner(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogOwner) {
    ui->setupUi(this);
}

/**
 * @brief dialogOwner::~dialogOwner
 * destructor, se destruirán el o los datos seleccionados en owners
 */
dialogOwner::~dialogOwner() {
    delete ui;
}

/**
 * @brief dialogOwner::on_buttonBox_accepted
 * Funcion de aceptar en ventana de owner
 */
void dialogOwner::on_buttonBox_accepted() {
    // datos guardados en linea de texto nombre
    if (editando) {
        ownerAEditar->setNombre(ui->lineEdit->text().toStdString());
    } else {
        Owner *newO = new Owner;  // Va bien declararlo sin new? en el stack?
        newO->setNombre(ui->lineEdit->text().toStdString());  // Se crea nuevo owner
        ow->push_back(*newO);  // Devuelve el nuevo owner introducido perteneciente al vector owner
    }
}

/**
 * @brief dialogOwner::setOw
 * @param own
 */
void dialogOwner::setOw(pel::vector<Owner> *own) {
    // Pide datos en owner y los muestra en lista
    ow = own;
}

void dialogOwner::setOwnerAEditar(Owner &ow) {
    editando = true;
    ownerAEditar = &ow;
    ui->lineEdit->setText(ownerAEditar->getNombre().c_str());
}
