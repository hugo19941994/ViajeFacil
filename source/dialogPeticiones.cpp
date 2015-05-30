/*AUTORES:  Sergio Candel, ayuda David Jimenez y Hugo Ferrando
 */

// se tendrá acceso a la cabecera y al cuerpo de dialogPeticiones para usar sus datos
#include <QMessageBox>
#include "./dialogPeticiones.hpp"
#include "./ui_dialogPeticiones.h"
#include "./pel_vector.hpp"

dialogPeticiones::dialogPeticiones(QWidget *parent) :  // tipo de ventana peticiones
    QDialog(parent),
    /**
    * @brief ui
    */
    ui(new Ui::dialogPeticiones) {
    ui->setupUi(this);
}

/**
 * @brief dialogPeticiones::~dialogPeticiones
 */
dialogPeticiones::~dialogPeticiones() {  // destructor
    delete ui;
}

/**
 * @brief dialogPeticiones::setOw
 * @param own
 */
void dialogPeticiones::setOw(pel::vector<Owner> &own) {  // introducir owners, se accede al vector owners
    this->ow = &own;
}

/**
 * @brief dialogPeticiones::setPe
 * @param pet
 */
void dialogPeticiones::setPe(pel::vector<Peticion> &pet) {
    this->pe = &pet;
}

/**
 * @brief dialogPeticiones::cargar
 */
void dialogPeticiones::cargar() {
    for (auto &it : *this->ow)
        this->ui->comboBox->addItem(it.getNombre().c_str());
}

void dialogPeticiones::setOf(pel::vector<Oficina>& of) {
    this->of = &of;
}
void dialogPeticiones::setNe(pel::vector<std::shared_ptr<Nego>>& ne) {
    this->ne = &ne;
}

void dialogPeticiones::on_comboBox_currentIndexChanged(int index) {
    // Owner *own = &this->ow->at(index);
    setOf(ow->at(index).getOficinas());
    setNe(ow->at(index).getNegos());

    ui->comboBox_2->clear();
    for (auto &it : *of) {
        ui->comboBox_2->addItem(it.getNombre().c_str());
    }

    ui->comboBox_3->clear();
    for (auto &it : *ne) {
        QString texto = it->getOrigen().c_str();
        texto.append(" - ");
        texto.append(it->getDestino().c_str());
        ui->comboBox_3->addItem(texto);
    }
}

void dialogPeticiones::setRows(int modRowOwner, int modRowOficina, int modRowPeticion) {
    this->modRowOwner = modRowOwner;  // datos modificados de owner
    this->modRowOficina = modRowOficina;  // datos modificados en oficina
    this->modRowPeticion = modRowPeticion;
    Owner *ow = &this->ow->at(modRowOwner);  // puntero de modificacion de owners en opcion modificar oficina
    // si no hay owners, no hay oficinas

    this->setOf(ow->getOficinas());
    Oficina *ofi = &of->at(modRowOficina);
    this->setPe(ofi->getPeticiones());

    // TODO - Quizas habria que dejarlos activados y poder cambiar?
    // Ademas podriamos cargarla entrada que corresponda
    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
    ui->comboBox_3->setEnabled(false);
    ui->lineEdit_3->setText(std::to_string(pe->at(modRowPeticion).getPlazasPedidas()).c_str());
}

void dialogPeticiones::on_buttonBox_accepted() {
    if (modRowOficina == -1 && modRowOwner == -1 && modRowPeticion == -1) {
        setPe(of->at(ui->comboBox_2->currentIndex()).getPeticiones());
        Peticion pet;
        pet.neg = std::shared_ptr<Nego>(ne->at(ui->comboBox_3->currentIndex()));
        pet.setPlazasPedidas(ui->lineEdit_3->text().toInt());

        if (static_cast<int>(pet.neg->getNumeroPlazas() - pet.getPlazasPedidas()) >= 0) {
            pet.neg->setNumeroPlazas(pet.neg->getNumeroPlazas() - pet.getPlazasPedidas());
            pe->push_back(pet);
        } else {
            QMessageBox::warning(this, "Warning", "No hay suficientes plazas");
        }
    } else {
        std::size_t plazasActuales = pe->at(modRowPeticion).neg->getNumeroPlazas();
        std::size_t plazasTotales = plazasActuales + pe->at(modRowPeticion).getPlazasPedidas();
        int diff = plazasTotales - ui->lineEdit_3->text().toInt();
        if (diff < 0) {
            QMessageBox::warning(this, "Warning", "No hay suficientes plazas");
        } else {
            pe->at(modRowPeticion).neg->setNumeroPlazas(diff);
            pe->at(modRowPeticion).setPlazasPedidas(ui->lineEdit_3->text().toInt());
        }
    }
    this->close();
}

void dialogPeticiones::on_buttonBox_rejected() {
    this->close();
}
