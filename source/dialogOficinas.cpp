#include "dialogOficinas.hpp"
#include "ui_dialogOficinas.h"

DialogOficinas::DialogOficinas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOficinas)
{
    ui->setupUi(this);
}

DialogOficinas::~DialogOficinas()
{
    delete ui;
}

void DialogOficinas::setOw(std::vector<Owner> &own)
{
    this->ow = &own;
}

void DialogOficinas::setOf(std::vector<Oficina> &ofc)
{
    this->of = &ofc;
}

void DialogOficinas::setPe(std::vector<Peticion> &pet)
{
    this->pe = &pet;
}

void DialogOficinas::cargar()
{
   for(auto &it : *this->ow)
       this->ui->comboBox->addItem(it.getNombre().c_str());
}



void DialogOficinas::on_comboBox_currentIndexChanged(int index)
{
    this->setOf(ow->at(index).getOficinas());
}

void DialogOficinas::on_buttonBox_accepted()
{
    Oficina *newOf = new Oficina;
    newOf->setNombre(this->ui->lineNombre->text().toStdString());
    newOf->setPais(this->ui->linePais->text().toStdString());
    newOf->setContinente(this->ui->lineCont->text().toStdString());

   /* newO->setOrigen(this->ui->lineOrigen->text().toStdString());
    newN->setDestino(this->ui->lineDestino->text().toStdString());
    newN->setNumeroPlazas(this->ui->linePlazas->text().toInt());
    Fecha fech;
    fech.setDia(this->ui->dateEdit->date().day());
    fech.setMes(this->ui->dateEdit->date().month());
    fech.setAnio(this->ui->dateEdit->date().year());
    newN->setFecha(fech);*/
    this->of->push_back(*newOf);
}
