/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 */

#include "./ui_dialogOficinas.h"
#include "./pelVector.hpp"
#include "./dialogOficinas.hpp"
#include <QMessageBox>

dialogOficinas::dialogOficinas(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogOficinas) {
    ui->setupUi(this);
}

dialogOficinas::~dialogOficinas() { delete ui; }

void dialogOficinas::cargar(pel::Vector<Owner>* own) {
    for (auto &it : *own)
        ui->comboBox->addItem(it.getNombre().c_str());
}

void dialogOficinas::setOficinaAEditar(Oficina *ofi) {
    editando = true;
    oficinaAEditar = ofi;

    ui->lineNombre->setText(ofi->getNombre().c_str());
    ui->linePais->setText(ofi->getPais().c_str());
    ui->lineCont->setText(ofi->getContinente().c_str());

    // ui->comboBox->setItemText(ow->at(modRowOwner).getNombre().c_str());
    ui->comboBox->setEnabled(false);
}

int dialogOficinas::nivel() { return ui->comboBox->currentIndex(); }

Oficina dialogOficinas::crear() {
    return Oficina {ui->lineNombre->text().toStdString(),
                ui->linePais->text().toStdString(),
                ui->lineCont->text().toStdString()};
}

void dialogOficinas::accept(){
    if (maybeSave) {
        done(1);  // Termina y emite accepted
    }
}

void dialogOficinas::on_buttonBox_accepted() {
   /* if (editando) {
        oficinaAEditar->setNombre(ui->lineNombre->text().toStdString());
        oficinaAEditar->setPais(ui->linePais->text().toStdString());
        oficinaAEditar->setContinente(ui->lineCont->text().toStdString());
    }*/

    maybeSave = true;
        if (editando) {
            if (ui->lineNombre->text().isEmpty()) {
                QMessageBox::information(this, "",QString ("Nombre no puede ser vacío"));
                maybeSave = false;
                accept();
            }

            if (ui->linePais->text().isEmpty()) {
                QMessageBox::information(this, "",QString ("Pais no puede ser vacío"));
                maybeSave = false;
                accept();
            }


            //Solo falta esta parte, los demas casos funcionan

            /*for(auto &iter : listaOw->at(1)->getOficinas()){
                if (ui->lineNombre->text().toStdString() == iter->getNombre()) {
                    QMessageBox::information(this, "",QString ("Ya hay una oficina con este nombre"));
                    maybeSave = false;
                    accept();
                }
            }*/

            if (maybeSave) {
                oficinaAEditar->setNombre(ui->lineNombre->text().toStdString());
                maybeSave = true;
                accept();
            }
        }
        else {  // Creando una oficina nuevo
            maybeSave = true;
            accept();
        }
    }

