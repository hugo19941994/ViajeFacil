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

void DialogOficinas::setRows(int modRowOwner, int modRowOficina)
{
    this->modRowOwner = modRowOwner; //datos modificados de owner
    this->modRowOficina = modRowOficina; //datos modificados en oficina
    Owner *ow = &this->ow->at(modRowOwner);  //puntero de modificacion de owners en opcion modificar oficina
    //si no hay owners, no hay oficinas
    this->setOf(ow->getOficinas());

    //lugar donde se van a modificar los datos
    this->ui->lineNombre->setText(this->of->at(this->modRowOficina).getNombre().c_str());
    this->ui->linePais->setText(this->of->at(this->modRowOficina).getPais().c_str());
    this->ui->lineCont->setText(this->of->at(this->modRowOficina).getContinente().c_str());


    //this->ui->comboBox->setItemText(this->ow->at(modRowOwner).getNombre().c_str());
    this->ui->comboBox->setEnabled(false);
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
    this->of->push_back(*newOf);
}
