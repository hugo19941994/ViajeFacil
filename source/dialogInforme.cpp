/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 */

#include <string>
#include "./dialogInforme.hpp"
#include "./ui_dialogInforme.h"
#include "./pel_vector.hpp"
#include "./owner.hpp"

dialogInforme::dialogInforme(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogInforme) {
    ui->setupUi(this);
    QFont f("monospace");
    f.setStyleHint(QFont::Monospace);
    ui->textBrowser->setFont(f);
}

dialogInforme::~dialogInforme() {
    delete ui;
}

void dialogInforme::cargar(pel::vector<Owner>* own) {
    ow = own;
}

void dialogInforme::cargarH(pel::vector<entradaHistorial> *his) {
    hi = his;
}

std::string dialogInforme::crearString(entradaHistorial h) {
    std::string str;
    if (h.getBorrado())
        str = ("Borrada    | ");
    else if (h.getCreado())
        str = ("Creada     | ");
    else if (h.getModificado())
        str = ("Modificada | ");
    str.append("Owner: " + h.getOwner());
    str.append(" | Oficina: " + h.getOficina());
    str.append(" | Pais de Oficina: " + h.getPaisOficina());
    str.append(" | Continente de Oficina: " + h.getContinenteOficina());
    str.append(" | Origen: " + h.getOrigen());
    str.append(" | Destino: " + h.getDestino());
    str.append(" | Asientos: " + std::to_string(h.getAsientos()));
    return str;

}

void dialogInforme::on_radioButton_5_clicked() {
    struct rank* ranks = new rank[ow->size()];
    for (std::size_t i = 0; i < ow->size(); ++i) {
        ranks[i].name = ow->at(i).getNombre();
        for (std::size_t j = 0; j < ow->at(i).getOficinas().size(); ++j) {
            for (std::size_t k = 0; k < ow->at(i).getOficinas().at(j).getPeticiones().size(); ++k){
                ranks[i].num += ow->at(i).getOficinas().at(j).getPeticiones().at(k).getPlazasPedidas();
            }
        }
    }

    ui->textBrowser->clear();
    quickSort(ranks, 0, ow->size());
    for (int i = ow->size()-1; i >= 0; --i) {
        ui->textBrowser->append(ranks[i].name.c_str());
    }

    delete[] ranks;
}

void dialogInforme::quickSort(rank arr[], int left, int right) {
    int i = left, j = right;
    rank tmp;
    int pivot = arr[(left + right) / 2].num;

    /* partition */
    while (i <= j) {
        while (arr[i].num < pivot)
              i++;
        while (arr[j].num > pivot)
              j--;
        if (i <= j) {
              tmp = arr[i];
              arr[i] = arr[j];
              arr[j] = tmp;
              i++;
              j--;
        }
    }

    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

void dialogInforme::on_radioButton_clicked() {
    ui->textBrowser->clear();
    for (std::size_t i = 0; i < hi->size(); i++) {
        std::string str = crearString(hi->at(i));
        ui->textBrowser->append(str.c_str());
    }
}
