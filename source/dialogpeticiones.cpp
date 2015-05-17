/*AUTORES:  Sergio Candel, ayuda David Jimenez y Hugo Ferrando
 */

//se tendrá acceso a la cabecera y al cuerpo de dialogpeticiones para usar sus datos
#include "./dialogpeticiones.hpp"
#include "./ui_dialogpeticiones.h"
#include <QMessageBox>

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
void DialogPeticiones::setOw(std::vector<Owner> &own) { //introducir owners, se accede al vector owners
    this->ow = &own;
}

/**
 * @brief DialogPeticiones::setPe
 * @param pet
 */
void DialogPeticiones::setPe(std::vector<Peticion> &pet) {
    this->pe = &pet;
}

/**
 * @brief DialogPeticiones::cargar
 */
void DialogPeticiones::cargar() {
    for(auto &it : *this->ow)
        this->ui->comboBox->addItem(it.getNombre().c_str());
}

void DialogPeticiones::setOf(std::vector<Oficina>& of) {
    this->of = &of;
}
void DialogPeticiones::setNe(std::vector<Nego>& ne) {
    this->ne = &ne;
}

void DialogPeticiones::on_comboBox_currentIndexChanged(int index) {
    //Owner *own = &this->ow->at(index);
    setOf(ow->at(index).getOficinas());
    setNe(ow->at(index).getNegos());

    ui->comboBox_2->clear();
    for(auto &it : *of) {
        ui->comboBox_2->addItem(it.getNombre().c_str());
    }

    ui->comboBox_3->clear();
    for(auto &it : *ne) {
        QString texto = it.getOrigen().c_str();
        texto.append(" - ");
        texto.append(it.getDestino().c_str());
        ui->comboBox_3->addItem(texto);
    }
}

void DialogPeticiones::on_pushButton_2_clicked() {
    setPe(of->at(ui->comboBox_2->currentIndex()).getPeticiones());
    Peticion pet;
    pet.neg = &ne->at(ui->comboBox_3->currentIndex());
    pet.setPlazasPedidas(ui->lineEdit_3->text().toInt());

    if(static_cast<int>(pet.neg->getNumeroPlazas() - pet.getPlazasPedidas()) >= 0) {
        pet.neg->setNumeroPlazas(pet.neg->getNumeroPlazas() - pet.getPlazasPedidas());
        pe->push_back(pet);
    }
    else
        QMessageBox::warning(this, "Warning", "No hay suficientes plazas");
}
