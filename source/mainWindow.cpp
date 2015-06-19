/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jiménez Cuevas
 *  Ventana principal, definicion de todas las funciones para que
 *  se comuniquen los dialog y las clases
 */

#include <QMessageBox>
#include <fstream>
#include <string>
#include "./ui_mainWindow.h"
#include "./mainWindow.hpp"
#include "./dialogLogin.hpp"
#include "./dialogOwner.hpp"
#include "./dialogNego.hpp"
#include "./dialogOficinas.hpp"
#include "./dialogPeticiones.hpp"
#include "./cereal/archives/json.hpp"
#include "./dialogInforme.hpp"
#include "./entradaHistorial.hpp"


mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::mainWindow) {
    ui->setupUi(this);

    std::ifstream myfile("../../data/data.json");  // crea archivo lectura
    if (myfile) {
        // Declaramos que va a ser un archivo JSON
        cereal::JSONInputArchive ar(myfile);
        // "Des-serializamos" listaOw
        ar(listaOw);
    }

    std::ifstream myPeticiones("../../data/logPeticiones.txt");
    if (myPeticiones)
        log.readFromFile("../../data/logPeticiones.txt");

    // TODO(Hugo) - comprobar que exista un usuario admin
    // Si existe un admin desactivar crear usuario
    ui->listWidget->setEnabled(false);
    ui->listWidget_2->setEnabled(false);
    ui->listWidget_3->setEnabled(false);
    ui->listWidget_4->setEnabled(false);
    ui->actionCreNego->setEnabled(false);
    ui->actionCreOficina->setEnabled(false);
    ui->actionCreOwner->setEnabled(false);
    ui->actionCrePeticion->setEnabled(false);
    ui->menuModificar->setEnabled(false);
    ui->menuConsultas->setEnabled(false);
    ui->menuBorrar->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_5->setEnabled(false);
}

mainWindow::~mainWindow() {
    delete ui;
}

//////////////////// LISTWIDGET PRESSED ///////////////////////////////////////
void mainWindow::on_listWidget_itemPressed(QListWidgetItem *item) {
    auto ow = listaOw.at(ui->listWidget->row(item));
    ui->listWidget_2->clear();
    for (auto &it : ow.getNegos()) {
        QString str = QString("%1 - %2")
                .arg(it->getOrigen().c_str(), it->getDestino().c_str());
        ui->listWidget_2->addItem(str);
    }

    ui->listWidget_3->clear();
    for (auto it : ow.getOficinas()) {
        ui->listWidget_3->addItem(it.getNombre().c_str());
    }
    ui->listWidget_4->clear();
}


void mainWindow::on_listWidget_3_itemPressed(QListWidgetItem *item) {
    if (!ui->listWidget->selectedItems().isEmpty()) {
        auto ow = listaOw.at(ui->listWidget->currentIndex().row());
        auto pe = ow.getOficinas().at(
            ui->listWidget_3->row(item)).getPeticiones();

        ui->listWidget_4->clear();
        for (auto it : pe) {
            QString str = QString("%1 (%2 - %3)")
                    .arg(std::to_string(it.getPlazasPedidas()).c_str(),
                         it.getNeg()->getOrigen().c_str(),
                         it.getNeg()->getDestino().c_str());
            ui->listWidget_4->addItem(str);
        }
    }
}


//////////////////////////// CREAR ////////////////////////////////////////////
void mainWindow::on_actionCreOwner_triggered() {
    dialogOwner ow;
    ow.setModal(true);
    if (ow.exec() == QDialog::Accepted) {
        //QDialog::Rejected
        Owner own = ow.crear();
        for(auto & it : listaOw) {
             if(own.getNombre() == it.getNombre()) {
                 QMessageBox::information(this, "",QString ("Ya hay un owner con este nombre"));
                 return;
             }
       }

        listaOw.push_back(own);
        ui->listWidget->clear();
        for (auto &it : listaOw) {
            ui->listWidget->addItem(it.getNombre().c_str());
        }

        int s = listaOw.size() - 1;
        ui->listWidget->setCurrentRow(s);
        ui->listWidget->itemPressed(ui->listWidget->item(s));
        guardarEnArchivo();
    }
}

void mainWindow::on_actionCreNego_triggered() {
    if (!listaOw.empty()){
        dialogNego ng;
        ng.cargar(&listaOw);
        ng.setModal(true);

        if (ng.exec() == QDialog::Accepted) {
            int nv = 0;

            Nego neg = ng.crear();
            if(neg.getNumeroPlazas() <=0){
                    QMessageBox::warning(this, "Warning",
                                         "No puedes crear negos con 0 plazas");
                    return;

            }
            nv = ng.nivel();
            listaOw.at(nv).getNegos().push_back(std::make_shared<Nego>(neg));

            ui->listWidget->setCurrentRow(nv);
            ui->listWidget->itemPressed(ui->listWidget->item(nv));

            ui->listWidget_2->setCurrentRow(listaOw.at(nv).getNegos().size()-1);
            ui->listWidget_2->itemPressed(
                ui->listWidget->item(listaOw.at(nv).getNegos().size()-1));

            guardarEnArchivo();
        }
    } else {
        QMessageBox::warning(this, "Warning",
                             "No existe ningún Owner");
    }
}

void mainWindow::on_actionCreOficina_triggered() {
    if (!listaOw.empty()) {
        dialogOficinas diagOf;
        diagOf.cargar(&listaOw);
        diagOf.setModal(true);
        if (diagOf.exec() == QDialog::Accepted) {
            int nv = 0;

            Oficina ofi = diagOf.crear();
            nv = diagOf.nivel();
            listaOw.at(nv).getOficinas().push_back(ofi);

            ui->listWidget->setCurrentRow(nv);
            ui->listWidget->itemPressed(ui->listWidget->item(nv));

            ui->listWidget_3->setCurrentRow(listaOw.at(nv).getOficinas().size()-1);
            ui->listWidget_3->itemPressed(
                ui->listWidget_3->item(listaOw.at(nv).getOficinas().size()-1));

            guardarEnArchivo();
        }
    } else {
        QMessageBox::warning(this, "Warning",
                             "No existe ningún Owner");
    }
}

void mainWindow::on_actionCrePeticion_triggered() {
    if (!listaOw.empty()) {
        dialogPeticiones peticiones;

        peticiones.cargar(&listaOw);
        peticiones.setModal(true);

        if (peticiones.exec() == QDialog::Accepted) {
            Peticion pet = peticiones.crear();
            if(pet.getPlazasPedidas() <= 0){
                QMessageBox::warning(this, "Warning",
                                     "No puedes pedir 0 plazas");
                return;
            }

            int nvOw = peticiones.nivelOw();
            int nvOf = peticiones.nivelOf();
            int nvNe = peticiones.nivelNe();
            if((nvOf == -1 )|| (nvNe == -1)) {
                QMessageBox::warning(this, "Warning",
                                     "No existen Oficinas/Negos");
                return;
            }
            pet.setNeg(std::shared_ptr<Nego>(listaOw.at(nvOw).getNegos().at(nvNe)));

            if (static_cast<int>(pet.getNeg()->getNumeroPlazas() -
                                 pet.getPlazasPedidas()) >= 0) {
                pet.getNeg()->setNumeroPlazas(pet.getNeg()->getNumeroPlazas() -
                                         pet.getPlazasPedidas());
                listaOw.at(nvOw).getOficinas().at(nvOf)
                        .getPeticiones().push_back(pet);

                entradaHistorial h {true, false, false, pet.getPlazasPedidas(),
                                  pet.getNeg()->getOrigen(),
                                  pet.getNeg()->getDestino(),
                                  listaOw.at(nvOw).getNombre(),
                                  listaOw.at(nvOw).getOficinas().at(
                                      nvOf).getNombre(),
                                  listaOw.at(nvOw).getOficinas().at(nvOf).getPais(),
                                  listaOw.at(nvOw).getOficinas().at(
                                      nvOf).getContinente()};
                log.push_back(h);

                guardarEnArchivo();
                log.writeToFile("../../data/logPeticiones.txt");

                ui->listWidget->setCurrentRow(nvOw);
                ui->listWidget->itemPressed(ui->listWidget->item(nvOw));

                ui->listWidget_3->setCurrentRow(nvOf);
                ui->listWidget_3->itemPressed(ui->listWidget_3->item(nvOf));

                ui->listWidget_4->setCurrentRow(
                    listaOw.at(nvOw).getOficinas().at(
                        nvOf).getPeticiones().size()-1);
                ui->listWidget_4->itemPressed(
                    ui->listWidget_4->item(listaOw.at(nvOw).getOficinas().at(
                        nvOf).getPeticiones().size()-1));
            } else {
                QMessageBox::warning(this, "Warning",
                                     "No hay suficientes plazas");
            }
        }
    }  else {
        QMessageBox::warning(this, "Warning",
                             "No existe ningún Owner");
    }
}

void mainWindow::on_actionCreUsuario_triggered() {
    dialogLogin log;
    log.setModal(true);
    log.setEstado(1);
    log.exec();
}

//////////////////////////// MODIFICAR ////////////////////////////////////////
void mainWindow::on_actionModOwner_triggered() {
    if (!ui->listWidget->selectedItems().isEmpty()) {
        int posicion = ui->listWidget->currentRow();
        Owner &own = listaOw.at(posicion);

        dialogOwner ow;
        ow.setOwnerAEditar(&own);
        ow.setModal(true);
        ow.exec();

        ui->listWidget->clear();
        for (auto &it : listaOw) {
            ui->listWidget->addItem(it.getNombre().c_str());
        }


        ui->listWidget->setCurrentRow(posicion);
        ui->listWidget->itemPressed(ui->listWidget->item(posicion));

        guardarEnArchivo();
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner seleccionado");
    }
}

void mainWindow::on_actionModNego_triggered() {
    if (!ui->listWidget->selectedItems().isEmpty()
            && !ui->listWidget_2->selectedItems().isEmpty()) {
        int posicionOw = ui->listWidget->currentRow();
        int posicionNeg = ui->listWidget_2->currentRow();
        Nego &neg = *listaOw.at(posicionOw)
                .getNegos().at(posicionNeg);

        dialogNego ng;
        ng.setNegoAEditar(&neg);
        ng.setModal(true);
        ng.exec();

        ui->listWidget->setCurrentRow(posicionOw);
        ui->listWidget->itemPressed(ui->listWidget->item(posicionOw));

        ui->listWidget_2->setCurrentRow(posicionNeg);
        ui->listWidget_2->itemPressed(ui->listWidget_2->item(posicionNeg));

        guardarEnArchivo();
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Nego seleccionado");
    }
}

void mainWindow::on_actionModOficina_triggered() {
    if (!ui->listWidget->selectedItems().isEmpty()
            && !ui->listWidget_3->selectedItems().isEmpty()) {
        int posicionOw = ui->listWidget->currentRow();
        int posicionOf = ui->listWidget_3->currentRow();
        Oficina &ofi = listaOw.at(posicionOw)
                .getOficinas().at(posicionOf);

        dialogOficinas of;
        of.setOficinaAEditar(&ofi);
        of.setModal(true);
        of.exec();

        ui->listWidget->setCurrentRow(posicionOw);
        ui->listWidget->itemPressed(ui->listWidget->item(posicionOw));

        ui->listWidget_3->setCurrentRow(posicionOf);
        ui->listWidget_3->itemPressed(ui->listWidget_3->item(posicionOf));

        guardarEnArchivo();
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Oficina seleccionado");
    }
}

void mainWindow::on_actionModPeticion_triggered() {
    if (!ui->listWidget->selectedItems().isEmpty()
            && !ui->listWidget_3->selectedItems().isEmpty()
            && !ui->listWidget_4->selectedItems().isEmpty()) {
        int posicionOw = ui->listWidget->currentRow();
        int posicionOf = ui->listWidget_3->currentRow();
        int posicionPe = ui->listWidget_4->currentRow();

        Peticion &pet = listaOw.at(posicionOw)
                .getOficinas().at(posicionOf)
                .getPeticiones().at(posicionPe);

        dialogPeticiones pe;
        pe.setPeticionAEditar(&pet);
        pe.setModal(true);
        pe.exec();

        ui->listWidget->setCurrentRow(posicionOw);
        ui->listWidget->itemPressed(ui->listWidget->item(posicionOw));

        ui->listWidget_3->setCurrentRow(posicionOf);
        ui->listWidget_3->itemPressed(ui->listWidget_3->item(posicionOf));

        ui->listWidget_4->setCurrentRow(posicionPe);
        ui->listWidget_4->itemPressed(ui->listWidget_4->item(posicionPe));
        guardarEnArchivo();

        entradaHistorial h {false, true, false, pet.getPlazasPedidas(),
                          pet.getNeg()->getOrigen(), pet.getNeg()->getDestino(),
                          listaOw.at(posicionOw).getNombre(),
                    listaOw.at(posicionOw).getOficinas().at(
                        posicionOf).getNombre(),
                    listaOw.at(posicionOw).getOficinas().at(
                        posicionOf).getPais(),
                    listaOw.at(posicionOw).getOficinas().at(
                        posicionOf).getContinente()};
        log.push_back(h);
        log.writeToFile("../../data/logPeticiones.txt");

    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Oficina/Peticion"
                             " seleccionado");
    }
}

///////////////////////////// BORRAR //////////////////////////////////////////
void mainWindow::on_actionBorOwner_triggered() {
    // Calcular el indice del owner seleccionado y borrarlo
    if (!ui->listWidget->selectedItems().isEmpty()) {
        listaOw.erase(listaOw.begin() + ui->listWidget->currentRow());
        int posicion = ui->listWidget->currentRow();

        ui->listWidget->takeItem(posicion);
        if (ui->listWidget->count() > 0) {
            ui->listWidget->itemPressed(
                ui->listWidget->item(ui->listWidget->currentRow()));
        }
        else {
            ui->listWidget_2->clear();
            ui->listWidget_3->clear();
            ui->listWidget_4->clear();
        }

        guardarEnArchivo();
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner seleccionado");
    }
}

void mainWindow::on_actionBorNego_triggered() {
    if (!ui->listWidget_2->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()) {
        pel::Vector<std::shared_ptr<Nego>> &listaNegos =
                listaOw.at(ui->listWidget->currentRow()).getNegos();
        int curRow = ui->listWidget_2->currentRow();

        /**
         * Aprovechamos use_count del shared_ptr. Si devuelve mas de 1,
         * significa que hay otros shared_ptr (desde peticiones)
         * apuntando a este nego.
         */

        if (listaNegos.at(curRow).use_count() <= 1) {
            listaNegos.erase(listaNegos.begin() + curRow);

            ui->listWidget_2->takeItem(curRow);
            if (ui->listWidget_2->count() > 0) {
                ui->listWidget_2->itemPressed(
                    ui->listWidget_2->item(ui->listWidget_2->currentRow()));
            }
            guardarEnArchivo();


        } else {
            QMessageBox::warning(this, "Warning",
                                 "Hay peticiones de este Nego");
        }


    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Nego seleccionado");
    }
}

void mainWindow::on_actionBorOficina_triggered() {
    if (!ui->listWidget_3->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()) {
        pel::Vector<Oficina> &listaOficinas =
                listaOw.at(ui->listWidget->currentRow()).getOficinas();
        int curRow = ui->listWidget_3->currentRow();

        for (auto &it : listaOficinas.at(curRow).getPeticiones())
            it.getNeg()->devolverPlazas(it.getPlazasPedidas());

        listaOficinas.erase(listaOficinas.begin() + curRow);

        ui->listWidget_3->takeItem(curRow);
        if (ui->listWidget_3->count() > 0) {
            ui->listWidget_3->itemPressed(
                ui->listWidget_3->item(ui->listWidget_3->currentRow()));
        }
        guardarEnArchivo();
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Oficina seleccionado");
    }
}

void mainWindow::on_actionBorPeticion_triggered() {
    if (!ui->listWidget_4->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()
            && !ui->listWidget_3->selectedItems().isEmpty()) {
        pel::Vector<Peticion> &listPet =
                listaOw.at(ui->listWidget->currentRow()).getOficinas()
                .at(ui->listWidget_3->currentRow()).getPeticiones();
        int curOw = ui->listWidget->currentRow();
        int curOf = ui->listWidget_3->currentRow();
        int curRow = ui->listWidget_4->currentRow();

        Peticion pet = listPet.at(curRow);

        entradaHistorial h {false, false, true, pet.getPlazasPedidas(),
                          pet.getNeg()->getOrigen(), pet.getNeg()->getDestino(),
                          listaOw.at(curOw).getNombre(),
                    listaOw.at(curOw).getOficinas().at(curOf).getNombre(),
                    listaOw.at(curOw).getOficinas().at(curOf).getPais(),
                    listaOw.at(curOw).getOficinas().at(curOf).getContinente()};
        log.push_back(h);

        // Si borras peticion devolvemos las plazas al nego
        pet.getNeg()->devolverPlazas(pet.getPlazasPedidas());

        listPet.erase(listPet.begin() + curRow);

        ui->listWidget_4->takeItem(curRow);
        if (ui->listWidget_4->count() > 0) {
            ui->listWidget_4->itemPressed(
                ui->listWidget_4->item(ui->listWidget_4->currentRow()));
        }

        guardarEnArchivo();
        log.writeToFile("../../data/logPeticiones.txt");
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Oficina/Peticion"
                             " seleccionado");
    }
}

///////////////////////////// FILTRAR /////////////////////////////////////////
void mainWindow::on_lineEdit_2_textChanged(const QString &arg1) {
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        if (ui->listWidget->item(i)->text().contains(arg1))
            ui->listWidget->item(i)->setHidden(false);
        else
            ui->listWidget->item(i)->setHidden(true);
    }
}

void mainWindow::on_lineEdit_3_textChanged(const QString &arg1) {
    for (int i = 0; i < ui->listWidget_2->count(); ++i) {
        if (ui->listWidget_2->item(i)->text().contains(arg1))
            ui->listWidget_2->item(i)->setHidden(false);
        else
            ui->listWidget_2->item(i)->setHidden(true);
    }
}

void mainWindow::on_lineEdit_4_textChanged(const QString &arg1) {
    for (int i = 0; i < ui->listWidget_3->count(); ++i) {
        if (ui->listWidget_3->item(i)->text().contains(arg1))
            ui->listWidget_3->item(i)->setHidden(false);
        else
            ui->listWidget_3->item(i)->setHidden(true);
    }
}

void mainWindow::on_lineEdit_5_textChanged(const QString &arg1) {
    for (int i = 0; i < ui->listWidget_4->count(); ++i) {
        if (ui->listWidget_4->item(i)->text().contains(arg1))
            ui->listWidget_4->item(i)->setHidden(false);
        else
            ui->listWidget_4->item(i)->setHidden(true);
    }
}

/////////////////////////////// OTROS /////////////////////////////////////////
void mainWindow::on_pushButton_2_clicked() {
    dialogLogin log;
    log.setEstado(0);
    log.setModal(true);

    // Signal & slot mechanism with new syntax
    // http://wiki.qt.io/New_Signal_Slot_Syntax

    connect(&log, &dialogLogin::cambioDeUsuario,
            this, &mainWindow::cambiarUsuario);
    log.exec();
}

void mainWindow::guardarEnArchivo() {
    std::ofstream myfile("../../data/data.json");
    if (myfile) {
        // Declaramos que va a ser un archivo JSON
        cereal::JSONOutputArchive archive(myfile);
        // Serializamos listaOw
        archive(cereal::make_nvp("Owner", listaOw));
    }
}

void mainWindow::cambiarUsuario(std::string nombre) {
    QString QNombre = QString::fromUtf8(nombre.c_str());
    ui->label_2->setText(QNombre);
    // TODO(Hugo) - si el usuario no es admin desactivar ciertas funciones
    ui->listWidget->setEnabled(true);
    ui->listWidget_2->setEnabled(true);
    ui->listWidget_3->setEnabled(true);
    ui->listWidget_4->setEnabled(true);
    ui->actionCreNego->setEnabled(true);
    ui->actionCreOficina->setEnabled(true);
    ui->actionCreOwner->setEnabled(true);
    ui->actionCrePeticion->setEnabled(true);
    ui->menuModificar->setEnabled(true);
    ui->menuConsultas->setEnabled(true);
    ui->menuBorrar->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    ui->lineEdit_3->setEnabled(true);
    ui->lineEdit_4->setEnabled(true);
    ui->lineEdit_5->setEnabled(true);

    // Refrescamos la lista de Owners
    ui->listWidget->clear();

    for (auto &it : listaOw) {
        // c_str() necesario para la conversion implicita a QString
        ui->listWidget->addItem(it.getNombre().c_str());
    }
}

void mainWindow::on_actionLog_de_Peticiones_triggered() {
    dialogInforme di;
    di.setModal(true);
    di.cargar(&listaOw);
    di.cargarH(&log);
    di.setRadio(0);
    di.exec();
}

void mainWindow::on_actionInforme_Owners_que_mejor_consumen_Negos_triggered() {
    dialogInforme di;
    di.setModal(true);
    di.cargar(&listaOw);
    di.cargarH(&log);
    di.setRadio(1);
    di.exec();
}
