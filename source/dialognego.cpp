#include <vector>
#include "./ui_dialognego.h"
#include "./dialognego.hpp"

DialogNego::DialogNego(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNego) {
    ui->setupUi(this);
}

DialogNego::~DialogNego() {
    delete ui;
}

void DialogNego::cargar() {
    for (auto &it : *this->ow)
        this->ui->comboBox->addItem(it.getNombre().c_str());
}

void DialogNego::setRows(int modRowOwner, int modRowNego)
{
    this->modRowOwner = modRowOwner;
    this->modRowNego = modRowNego;
}

void DialogNego::setMod()
{
    Owner *ow = &this->ow->at(modRowOwner);
    this->setNe(ow->getNegos());

    this->mod = true;
    this->ui->lineDestino->setText(this->ne->at(this->modRowNego).getDestino().c_str());
    this->ui->lineOrigen->setText(this->ne->at(this->modRowNego).getOrigen().c_str());
    this->ui->linePlazas->setText(std::to_string(this->ne->at(this->modRowNego).getNumeroPlazas()).c_str());
    Fecha fech = this->ne->at(modRowNego).getFecha();
    QDate date(fech.getAnio(), fech.getMes(), fech.getAnio());
    this->ui->dateEdit->setDate(date);  // TODO: No pone la fecha

    // TODO: Mostrar el nego que corresponda en vez del primero
    //this->ui->comboBox->setItemText(this->ow->at(modRowOwner).getNombre().c_str());
    this->ui->comboBox->setEnabled(false);
}

void DialogNego::setNe(std::vector<Nego> &neg) {
    this->ne = &neg;
}

void DialogNego::setOw(std::vector<Owner> &own) {
    this->ow = &own;
}

void DialogNego::on_comboBox_currentIndexChanged(int index) {
    // Repasar!!!
    Owner *ow = &this->ow->at(index);
    this->setNe(ow->getNegos());
}

void DialogNego::on_buttonOkCancel_accepted() {
    if(this->mod == true){
        ne->at(modRowNego).setOrigen(this->ui->lineOrigen->text().toStdString());
        ne->at(modRowNego).setDestino(this->ui->lineDestino->text().toStdString());
        ne->at(modRowNego).setNumeroPlazas(this->ui->linePlazas->text().toInt());
        Fecha fech;
        fech.setDia(this->ui->dateEdit->date().day());
        fech.setMes(this->ui->dateEdit->date().month());
        fech.setAnio(this->ui->dateEdit->date().year());
        ne->at(modRowNego).setFecha(fech);
    }
    else{
        Nego *newN = new Nego;
        newN->setOrigen(this->ui->lineOrigen->text().toStdString());
        newN->setDestino(this->ui->lineDestino->text().toStdString());
        newN->setNumeroPlazas(this->ui->linePlazas->text().toInt());
        Fecha fech;
        fech.setDia(this->ui->dateEdit->date().day());
        fech.setMes(this->ui->dateEdit->date().month());
        fech.setAnio(this->ui->dateEdit->date().year());
        newN->setFecha(fech);
        this->ne->push_back(*newN);
    }
}
