#include "dialogOficinas.hpp"
#include "ui_dialogOficinas.h"
#include "./pel_vector.hpp"

dialogOficinas::dialogOficinas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogOficinas) {
    ui->setupUi(this);
}

dialogOficinas::~dialogOficinas() {
    delete ui;
}

void dialogOficinas::setOw(pel::vector<Owner> &own) {
    this->ow = &own;
}

void dialogOficinas::setOf(pel::vector<Oficina> &ofc) {
    this->of = &ofc;
}

void dialogOficinas::setPe(pel::vector<Peticion> &pet) {
    this->pe = &pet;
}

void dialogOficinas::cargar() {
   for(auto &it : *this->ow)
       this->ui->comboBox->addItem(it.getNombre().c_str());
}

void dialogOficinas::setRows(int modRowOwner, int modRowOficina) {
    this->modRowOwner = modRowOwner;  // datos modificados de owner
    this->modRowOficina = modRowOficina;  // datos modificados en oficina
    Owner *ow = &this->ow->at(modRowOwner);  // puntero de modificacion de owners en opcion modificar oficina
    // si no hay owners, no hay oficinas
    this->setOf(ow->getOficinas());

    // lugar donde se van a modificar los datos
    this->ui->lineNombre->setText(this->of->at(this->modRowOficina).getNombre().c_str());
    this->ui->linePais->setText(this->of->at(this->modRowOficina).getPais().c_str());
    this->ui->lineCont->setText(this->of->at(this->modRowOficina).getContinente().c_str());

    // this->ui->comboBox->setItemText(this->ow->at(modRowOwner).getNombre().c_str());
    this->ui->comboBox->setEnabled(false);
}

void dialogOficinas::on_comboBox_currentIndexChanged(int index) {
    this->setOf(ow->at(index).getOficinas());
}

void dialogOficinas::on_buttonBox_accepted() {
    if (modRowOficina != -1 && modRowOwner != -1) {
        of->at(modRowOficina).setNombre(ui->lineNombre->text().toStdString());
        of->at(modRowOficina).setPais(ui->linePais->text().toStdString());
        of->at(modRowOficina).setContinente(ui->lineCont->text().toStdString());
    } else {
        Oficina *newOf = new Oficina;
        newOf->setNombre(this->ui->lineNombre->text().toStdString());
        newOf->setPais(this->ui->linePais->text().toStdString());
        newOf->setContinente(this->ui->lineCont->text().toStdString());
        this->of->push_back(*newOf);
    }
}
