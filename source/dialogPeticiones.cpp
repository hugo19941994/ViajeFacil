/*AUTORES:  Sergio Candel, ayuda David Jimenez y Hugo Ferrando
 */

// se tendrá acceso a la cabecera y al cuerpo de
//dialogPeticiones para usar sus datos

#include <QMessageBox>
#include "./ui_dialogPeticiones.h"
#include "./pel_vector.hpp"
#include "./dialogPeticiones.hpp"

dialogPeticiones::dialogPeticiones(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogPeticiones) {
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
 * introducir owners, se accede al vector owners
 */
void dialogPeticiones::setOw(pel::vector<Owner> *own) {
    ow = own;
}

/**
 * @brief dialogPeticiones::setPe
 * @param pet
 */
void dialogPeticiones::setPe(pel::vector<Peticion> *pet) {
    pe = pet;
}

/**
 * @brief dialogPeticiones::cargar
 */
void dialogPeticiones::cargar() {
    for (auto &it : *ow)
        ui->comboBox->addItem(it.getNombre().c_str());
}

void dialogPeticiones::setOf(pel::vector<Oficina>* ofi) {
    of = ofi;
}

void dialogPeticiones::setNe(pel::vector<std::shared_ptr<Nego>>* neg) {
    ne = neg;
}

void dialogPeticiones::on_comboBox_currentIndexChanged(int index) {
    // Owner *own = &ow->at(index);
    setOf(&ow->at(index).getOficinas());
    setNe(&ow->at(index).getNegos());

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

void dialogPeticiones::setPeticionAEditar(Peticion &pet) {
    editando = true;
    peticionAEditar = &pet;

    ui->lineEdit_3->setText(std::to_string(pet.getPlazasPedidas()).c_str());
    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
    ui->comboBox_3->setEnabled(false);
}

void dialogPeticiones::on_buttonBox_accepted() {
    if (editando) {
        std::size_t plazasActuales =
                peticionAEditar->neg->getNumeroPlazas();
        std::size_t plazasTotales =
                plazasActuales + peticionAEditar->getPlazasPedidas();
        int diff = plazasTotales - ui->lineEdit_3->text().toInt();
        if (diff < 0) {
            QMessageBox::warning(this, "Warning", "No hay suficientes plazas");
        } else {
            peticionAEditar->neg->setNumeroPlazas(diff);
            peticionAEditar->setPlazasPedidas(ui->lineEdit_3->text().toInt());
        }
    } else {
        setPe(&of->at(ui->comboBox_2->currentIndex()).getPeticiones());
        Peticion pet;
        pet.neg = std::shared_ptr<Nego>(ne->at(ui->comboBox_3->currentIndex()));
        pet.setPlazasPedidas(ui->lineEdit_3->text().toInt());

        if (static_cast<int>(pet.neg->getNumeroPlazas() - pet.getPlazasPedidas()) >= 0) {
            pet.neg->setNumeroPlazas(pet.neg->getNumeroPlazas() - pet.getPlazasPedidas());
            pe->push_back(pet);
        } else {
            QMessageBox::warning(this, "Warning", "No hay suficientes plazas");
        }
    }

    this->close();
}

void dialogPeticiones::on_buttonBox_rejected() {
    this->close();
}
