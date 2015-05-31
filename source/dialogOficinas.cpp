/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 */

#include "./ui_dialogOficinas.h"
#include "./pel_vector.hpp"
#include "./dialogOficinas.hpp"

dialogOficinas::dialogOficinas(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogOficinas) {
    ui->setupUi(this);
}

dialogOficinas::~dialogOficinas() { delete ui; }

void dialogOficinas::cargar(pel::vector<Owner>* own) {
   for(auto &it : *own)
       ui->comboBox->addItem(it.getNombre().c_str());
}

void dialogOficinas::setOficinaAEditar(Oficina &ofi) {
    editando = true;
    oficinaAEditar = &ofi;

    ui->lineNombre->setText(ofi.getNombre().c_str());
    ui->linePais->setText(ofi.getPais().c_str());
    ui->lineCont->setText(ofi.getContinente().c_str());

    // ui->comboBox->setItemText(ow->at(modRowOwner).getNombre().c_str());
    ui->comboBox->setEnabled(false);
}

int dialogOficinas::nivel() { return ui->comboBox->currentIndex(); }

Oficina dialogOficinas::crear() {
    return Oficina {ui->lineNombre->text().toStdString(),
                ui->linePais->text().toStdString(),
                ui->lineCont->text().toStdString()};
}

void dialogOficinas::on_buttonBox_accepted() {
    if (editando) {
        oficinaAEditar->setNombre(ui->lineNombre->text().toStdString());
        oficinaAEditar->setPais(ui->linePais->text().toStdString());
        oficinaAEditar->setContinente(ui->lineCont->text().toStdString());
    }
}
