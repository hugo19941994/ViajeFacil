#include "./dialogpeticiones.hpp"
#include "./ui_dialogpeticiones.h"

DialogPeticiones::DialogPeticiones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPeticiones) {
    ui->setupUi(this);
}

DialogPeticiones::~DialogPeticiones() {
    delete ui;
}

void DialogPeticiones::setOw(std::vector<Owner> &own)
{
    this->ow = &own;
}

void DialogPeticiones::setPe(std::vector<Peticion> &pet)
{
    this->pe = &pet;
}

/*void DialogPeticiones::cargar()  //NO SE PARA QUE SIRVE NI FUNCIONA
{
    for(auto &it : this->ow)
        this->ui->comboBox->addItem(it.getNombre().c_str());
}*/







void DialogPeticiones::on_comboBox_currentIndexChanged(int index)
{

}
