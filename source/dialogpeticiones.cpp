/*AUTORES:  Sergio Candel, ayuda David Jimenez y Hugo Ferrando
 */

//se tendrá acceso a la cabecera y al cuerpo de dialogpeticiones para usar sus datos
#include "./dialogpeticiones.hpp"
#include "./ui_dialogpeticiones.h"
#include "pel_vector.hpp"
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
void DialogPeticiones::setOw(pel::vector<Owner> &own) { //introducir owners, se accede al vector owners
    this->ow = &own;
}

/**
 * @brief DialogPeticiones::setPe
 * @param pet
 */
void DialogPeticiones::setPe(pel::vector<Peticion> &pet) {
    this->pe = &pet;
}

/**
 * @brief DialogPeticiones::cargar
 */
void DialogPeticiones::cargar() {
    for(auto &it : *this->ow)
        this->ui->comboBox->addItem(it.getNombre().c_str());
}

void DialogPeticiones::setOf(pel::vector<Oficina>& of) {
    this->of = &of;
}
void DialogPeticiones::setNe(pel::vector<std::shared_ptr<Nego>>& ne) {
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
        QString texto = it.get()->getOrigen().c_str();
        texto.append(" - ");
        texto.append(it.get()->getDestino().c_str());
        ui->comboBox_3->addItem(texto);
    }
}

void DialogPeticiones::setRows(int modRowOwner, int modRowOficina, int modRowPeticion) {
    this->modRowOwner = modRowOwner; //datos modificados de owner
    this->modRowOficina = modRowOficina; //datos modificados en oficina
    this->modRowPeticion = modRowPeticion;
    Owner *ow = &this->ow->at(modRowOwner);  //puntero de modificacion de owners en opcion modificar oficina
    //si no hay owners, no hay oficinas

    this->setOf(ow->getOficinas());
    Oficina *ofi = &of->at(modRowOficina);
    this->setPe(ofi->getPeticiones());

    // TODO - Quoizas habria que dejarlos activados y poder cambiar?
    // Ademas podriamos cargarla entrada que corresponda
    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
    ui->comboBox_3->setEnabled(false);
    ui->lineEdit_3->setText(std::to_string(pe->at(modRowPeticion).getPlazasPedidas()).c_str());
}

void DialogPeticiones::on_buttonBox_accepted() {
    if(modRowOficina == -1 && modRowOwner == -1 && modRowPeticion == -1){
        setPe(of->at(ui->comboBox_2->currentIndex()).getPeticiones());
        Peticion pet;
        pet.neg = std::shared_ptr<Nego>(ne->at(ui->comboBox_3->currentIndex()).get());
        pet.setPlazasPedidas(ui->lineEdit_3->text().toInt());

        if(static_cast<int>(pet.neg->getNumeroPlazas() - pet.getPlazasPedidas()) >= 0) {
            pet.neg->setNumeroPlazas(pet.neg->getNumeroPlazas() - pet.getPlazasPedidas());
            pe->push_back(pet);
        }
        else
            QMessageBox::warning(this, "Warning", "No hay suficientes plazas");
    }
    else {
        std::size_t plazasActuales = pe->at(modRowPeticion).neg.get()->getNumeroPlazas();
        std::size_t plazasTotales = plazasActuales + pe->at(modRowPeticion).getPlazasPedidas();
        int diff = plazasTotales - ui->lineEdit_3->text().toInt();
        if (diff < 0)
            QMessageBox::warning(this, "Warning", "No hay suficientes plazas");
        else{
            pe->at(modRowPeticion).neg.get()->setNumeroPlazas(diff);
            pe->at(modRowPeticion).setPlazasPedidas(ui->lineEdit_3->text().toInt());
        }

    }
    this->close();
}

void DialogPeticiones::on_buttonBox_rejected()
{
    this->close();
}
