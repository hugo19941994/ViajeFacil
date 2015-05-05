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

void DialogNego::on_buttonBox_accepted() { //QUITAAAAR
    Nego newN;
    newN.setOrigen(this->ui->lineOrigen->text());
    newN.setDestino(this->ui->lineDestino->text());
    newN.setNumeroPlazas(this->ui->linePlazas->text().toInt());
    this->ne->push_back(newN);
}

void DialogNego::cargar(){
    for (std::vector<Owner>::iterator it = this->ow->begin(); it != this->ow->end(); ++it)
        this->ui->comboBox->addItem(it->getNombre());
}

void DialogNego::setNe(std::vector<Nego> &neg) {
    this->ne = &neg;
}

void DialogNego::setOw(std::vector<Owner> &own) {
    this->ow = &own;
}

void DialogNego::on_comboBox_currentIndexChanged(int index)
{
    //Repasar!!!
    Owner *ow = &this->ow->at(index);
    this->setNe(ow->getNegos());
}

void DialogNego::on_buttonOkCancel_accepted()
{
    Nego *newN = new Nego;
    newN->setOrigen(this->ui->lineOrigen->text());
    newN->setDestino(this->ui->lineDestino->text());
    newN->setNumeroPlazas(this->ui->linePlazas->text().toInt());
    this->ne->push_back(*newN);
}
