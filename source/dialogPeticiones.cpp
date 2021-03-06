/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author Sergio Candel
 *  @author David Jiménez Cuevas
 *  se tendrá acceso a la cabecera y al cuerpo de
 *  dialogPeticiones para usar sus datos
 */

#include <QMessageBox>
#include "./ui_dialogPeticiones.h"
#include "./pelVector.hpp"
#include "./dialogPeticiones.hpp"

dialogPeticiones::dialogPeticiones(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogPeticiones) {
    ui->setupUi(this);
}

dialogPeticiones::~dialogPeticiones() { delete ui; }

/**
 * @brief dialogPeticiones::cargar
 */
void dialogPeticiones::cargar(pel::Vector<Owner>* own) {
    ow = own;
    for (auto &it : *own)
        ui->comboBox->addItem(it.getNombre().c_str());
}

void dialogPeticiones::setPeticionAEditar(Peticion *pet) {
    editando = true;
    peticionAEditar = pet;

    ui->spinBox->setValue(pet->getPlazasPedidas());
    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
    ui->comboBox_3->setEnabled(false);
}

Peticion dialogPeticiones::crear() {
    Peticion pet {ui->spinBox->text().toUInt()};
    return pet;
}

int dialogPeticiones::nivelOw() { return ui->comboBox->currentIndex(); }
int dialogPeticiones::nivelOf() {
    if (ui->comboBox_2->count() == 0)
        return -1;
    else
        return ui->comboBox_2->currentIndex();
}
int dialogPeticiones::nivelNe() {
    if (ui->comboBox_2->count() == 0)
        return -1;
    else
        return ui->comboBox_3->currentIndex();
}

void dialogPeticiones::on_comboBox_currentIndexChanged(int index) {
        ui->comboBox_2->clear();
        for (auto &it : ow->at(index).getOficinas()) {
            ui->comboBox_2->addItem(it.getNombre().c_str());
        }

        ui->comboBox_3->clear();
        for (auto &it : ow->at(index).getNegos()) {
            QString texto = QString("%1 - %2").
                    arg(it->getOrigen().c_str(), it->getDestino().c_str());
            ui->comboBox_3->addItem(texto);
        }
}

void dialogPeticiones::on_buttonBox_accepted() {
    if (editando) {
        std::size_t plazasActuales =
                peticionAEditar->getNeg()->getNumeroPlazas();
        std::size_t plazasTotales =
                plazasActuales + peticionAEditar->getPlazasPedidas();
        int diff = plazasTotales - ui->spinBox->value();
        if (diff < 0) {
            QMessageBox::warning(this, "Warning", "No hay suficientes plazas");
        } else {
            peticionAEditar->getNeg()->setNumeroPlazas(diff);
            peticionAEditar->setPlazasPedidas(ui->spinBox->value());
        }
    }
}
