/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author Sergio Candel
 *  @author David Jimenez
 *  se tendrá acceso a la cabecera y al cuerpo de
 *  dialogPeticiones para usar sus datos
 */

#include <QMessageBox>
#include "./ui_dialogPeticiones.h"
#include "./pel_vector.hpp"
#include "./dialogPeticiones.hpp"

dialogPeticiones::dialogPeticiones(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogPeticiones) {
    ui->setupUi(this);
}

dialogPeticiones::~dialogPeticiones() { delete ui; }

/**
 * @brief dialogPeticiones::cargar
 */
void dialogPeticiones::cargar(pel::vector<Owner>* own) {
    ow = own;
    for (auto &it : *own)
        ui->comboBox->addItem(it.getNombre().c_str());
}

void dialogPeticiones::setPeticionAEditar(Peticion &pet) {
    editando = true;
    peticionAEditar = &pet;

    ui->lineEdit_3->setText(std::to_string(pet.getPlazasPedidas()).c_str());
    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
    ui->comboBox_3->setEnabled(false);
}

Peticion dialogPeticiones::crear() {
    Peticion pet {ui->lineEdit_3->text().toUInt()};
    return pet;
}

int dialogPeticiones::nivelOw() { return ui->comboBox->currentIndex(); }
int dialogPeticiones::nivelOf() { return ui->comboBox_2->currentIndex(); }
int dialogPeticiones::nivelNe() { return ui->comboBox_3->currentIndex(); }

void dialogPeticiones::on_comboBox_currentIndexChanged(int index) {
        ui->comboBox_2->clear();
        for (auto &it : ow->at(index).getOficinas()) {
            ui->comboBox_2->addItem(it.getNombre().c_str());
        }

        ui->comboBox_3->clear();
        for (auto &it : ow->at(index).getNegos()) {
            QString texto = it->getOrigen().c_str();
            texto.append(" - ");
            texto.append(it->getDestino().c_str());
            ui->comboBox_3->addItem(texto);
        }
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
    }
}
