/*AUTORES:  Sergio Candel, ayuda David Jimenez y Hugo Ferrando
 */

//se tendrá acceso a la cabecera y al cuerpo de dialogpeticiones para usar sus datos
#include "./dialogpeticiones.hpp"
#include "./ui_dialogpeticiones.h"

DialogPeticiones::DialogPeticiones(QWidget *parent) : //tipo de ventana peticiones
    QDialog(parent),
    /**
    * @brief ui
    */
    ui(new Ui::DialogPeticiones) {
    ui->setupUi(this);
}

/**
 * @brief DialogPeticiones::~DialogPeticiones
 */
DialogPeticiones::~DialogPeticiones() { //destructor
    delete ui;
}

/**
 * @brief DialogPeticiones::setOw
 * @param own
 */
void DialogPeticiones::setOw(std::vector<Owner> &own) //introducir owners, se accede al vector owners
{
    this->ow = &own;
}

/**
 * @brief DialogPeticiones::setPe
 * @param pet
 */
void DialogPeticiones::setPe(std::vector<Peticion> &pet)
{
    this->pe = &pet;
}

/**
 * @brief DialogPeticiones::cargar
 */
void DialogPeticiones::cargar()
{
    for(auto &it : *this->ow)
        this->ui->comboBox->addItem(it.getNombre().c_str());
}
