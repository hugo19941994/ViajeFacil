/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jimenez
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

/**
* Al crear el mainWindow desactivamos casi todo.
* Para activar el resto de funcionas hay que hacer login
*/
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

    // TODO - comprobar que exista un usuario admin
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
void mainWindow::on_listWidget_pressed(const QModelIndex &index) {
    auto ow = listaOw.at(index.row());
    ui->listWidget_2->clear();
    for (auto &it : ow.getNegos()) {
        // TODO:Se puede hacer en una linea?
        QString orDe = it->getOrigen().c_str();
        orDe.append(" - ");
        orDe.append(it->getDestino().c_str());
        ui->listWidget_2->addItem(orDe);
    }

    ui->listWidget_3->clear();
    // TODO:Se puede hacer en una linea?
    for (auto it : ow.getOficinas()) {
        QString nomPa = it.getNombre().c_str();
        ui->listWidget_3->addItem(nomPa);
    }
    ui->listWidget_4->clear();
}


void mainWindow::on_listWidget_3_pressed(const QModelIndex &index) {
    auto ow = listaOw.at(ui->listWidget->currentIndex().row());
    auto pe = ow.getOficinas().at(index.row()).getPeticiones();
    ui->listWidget_4->clear();
    for (auto it : pe) {
        QString orDe = std::to_string(it.getPlazasPedidas()).c_str();
        orDe.append(" (");
        orDe.append(it.neg->getOrigen().c_str());
        orDe.append(" - ");
        orDe.append(it.neg->getDestino().c_str());
        orDe.append(")");
        ui->listWidget_4->addItem(orDe);
    }
}

//////////////////////////// CREAR ////////////////////////////////////////////

/**
 * @brief Crear Un Owner nuevo
 * Se abre el dialogo de Owners vacio y al aceptar cogemos el
 * Owner creado y lo metemos en el Vector de Owners
 */
void mainWindow::on_actionCreOwner_triggered() {
    dialogOwner ow;
    ow.setModal(true);
    if (ow.exec() == QDialog::Accepted) {
        Owner own = ow.crear();
        listaOw.push_back(own);
    }

    ui->listWidget->clear();
    for (auto &it : listaOw) {
        ui->listWidget->addItem(it.getNombre().c_str());
    }

    guardarEnArchivo();
}

/**
 * @brief Crear un Nego nuevo
 * Se abre un dialogo de Negos vacio y al aceptar cogemos el
 * Nego creado y lo metemos en el Vector de Negos que corresponda.
 * Sabemos al Owner al que pertenece gracais a la funcion .nivel que
 * nos devuelve el Owner que el usuario ha escogido.
 */
void mainWindow::on_actionCreNego_triggered() {
    dialogNego ng;
    ng.cargar(&listaOw);
    ng.setModal(true);
    int nv = ui->listWidget->currentRow();  // PONER DENTRO DEL FOR??
    if (ng.exec() == QDialog::Accepted) {
        Nego neg = ng.crear();
        nv = ng.nivel();
        listaOw.at(nv).getNegos().push_back(std::make_shared<Nego>(neg));
    }

    guardarEnArchivo();

    // Refrescar la lista que corresponda
    ui->listWidget_2->clear();
}

/**
 * @brief Crear una Oficina nueva
 * Se abre un dialogo de Oficinas vacio y al aceptar cogemos la
 * Oficina creada y la metemos en el Vector de Oficinas que corresponda.
 * Sabemos al Owner al que pertenece gracais a la funcion .nivel que
 * nos devuelve el Owner que el usuario ha escogido.
 */
void mainWindow::on_actionCreOficina_triggered() {
    int nv = ui->listWidget->currentRow();
    dialogOficinas diagOf;
    diagOf.cargar(&listaOw);
    diagOf.setModal(true);
    if (diagOf.exec() == QDialog::Accepted) {
        Oficina ofi = diagOf.crear();
        nv = diagOf.nivel();
        listaOw.at(nv).getOficinas().push_back(ofi);
    }

    guardarEnArchivo();
    ui->listWidget_3->clear();
}

/**
 * @brief Crear una Peticion nueva
 * Se abre un dialogo de Peticiones vacio y al aceptar cogemos la
 * Peticion creada y la metemos en el Vector de Peticion que corresponda.
 *
 * Sabemos al Owner y la Oficina al que pertenece
 * gracais a la funcion .nivelOw y .nivelOf que
 * nos devuelve el Owner ya la Oficina que el usuario ha escogido.
 *
 * Quitamos al Nego que se ha escogido los asientos necesarios.
 *
 * Luego creamos una nueva entrada para el Historial y lo metemos en el Vector.
 */
void mainWindow::on_actionCrePeticion_triggered() {
    dialogPeticiones peticiones;

    int nvOw = 0;
    int nvOf = 0;

    peticiones.cargar(&listaOw);
    peticiones.setModal(true);

    if (peticiones.exec() == QDialog::Accepted) {
        Peticion pet = peticiones.crear();

        nvOw = peticiones.nivelOw();
        nvOf = peticiones.nivelOf();
        int nvNe = peticiones.nivelNe();
        pet.neg = std::shared_ptr<Nego>(listaOw.at(nvOw).getNegos().at(nvNe));

        if (static_cast<int>(pet.neg->getNumeroPlazas() -
                             pet.getPlazasPedidas()) >= 0) {
            pet.neg->setNumeroPlazas(pet.neg->getNumeroPlazas() -
                                     pet.getPlazasPedidas());
            listaOw.at(nvOw).getOficinas().at(nvOf)
                    .getPeticiones().push_back(pet);
        } else {
            QMessageBox::warning(this, "Warning",
                                 "No hay suficientes plazas");
        }

        entradaHistorial h {true, false, false, pet.getPlazasPedidas(),
                          pet.neg->getOrigen(), pet.neg->getDestino(),
                          listaOw.at(nvOw).getNombre(),
                    listaOw.at(nvOw).getOficinas().at(nvOf).getNombre(),
                    listaOw.at(nvOw).getOficinas().at(nvOf).getPais(),
                    listaOw.at(nvOw).getOficinas().at(nvOf).getContinente()};
        log.push_back(h);
    }

    guardarEnArchivo();
    ui->listWidget_4->clear();
}

/**
 * @brief Crear un Usuario nuevo
 * Abre una ventana de Usuarios. En la misma ventana se creara el usuario.
 */
void mainWindow::on_actionCreUsuario_triggered() {
    dialogLogin log;
    log.setModal(true);
    log.setEstado(1);
    log.exec();
}

//////////////////////////// MODIFICAR ////////////////////////////////////////

/**
 * @brief Modificar un Owner
 * Se selecciona un Owner en el listWidget y se abre una ventana de Owners
 * rellena con el nombre del Owner a modificar. El Owner se modifica en la
 * propia ventana. Luego refrescamos la lista de Owners.
 * Si no se seleccionó un Owner se emite un mensaje de error.
 */
void mainWindow::on_actionModOwner_triggered() {
    if (!ui->listWidget->selectedItems().isEmpty()) {
        Owner &own = listaOw.at(ui->listWidget->currentRow());

        dialogOwner ow;
        ow.setOwnerAEditar(own);
        ow.setModal(true);
        ow.exec();

        ui->listWidget->clear();
        for (auto &it : listaOw) {
            ui->listWidget->addItem(it.getNombre().c_str());
        }

        guardarEnArchivo();
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner seleccionado");
    }
}

/**
 * @brief Modificar un Nego
 * Se selecciona un Owner y un Nego en los listWidgets y se abre
 * una ventana de Negos con los campos del Nego.
 * El Nego se modifica en la propia ventana.
 * Luego refrescamo la lista de Owners.
 * Si no se seleccionó un Owner/Nego se emite un mensaje de error.
 */
void mainWindow::on_actionModNego_triggered() {
    if (!ui->listWidget->selectedItems().isEmpty()
            && !ui->listWidget_2->selectedItems().isEmpty()) {
        Nego &neg = *listaOw.at(ui->listWidget->currentRow())
                .getNegos().at(ui->listWidget_2->currentRow());

        dialogNego ng;
        ng.setNegoAEditar(neg);
        ng.setModal(true);
        ng.exec();

        guardarEnArchivo();
        ui->listWidget_2->clear();
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Nego seleccionado");
    }
}

void mainWindow::on_actionModOficina_triggered() {
    if (!ui->listWidget->selectedItems().isEmpty()
            && !ui->listWidget_3->selectedItems().isEmpty()) {
        Oficina &ofi = listaOw.at(ui->listWidget->currentRow())
                .getOficinas().at(ui->listWidget_3->currentRow());

        dialogOficinas of;
        of.setOficinaAEditar(ofi);
        of.setModal(true);
        of.exec();

        guardarEnArchivo();
        ui->listWidget_3->clear();
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Oficina seleccionado");
    }
}

void mainWindow::on_actionModPeticion_triggered() {
    if (!ui->listWidget->selectedItems().isEmpty()
            && !ui->listWidget_3->selectedItems().isEmpty()
            && !ui->listWidget_4->selectedItems().isEmpty()) {
        int n1 = ui->listWidget->currentRow();
        int n2 = ui->listWidget_3->currentRow();

        Peticion &pet = listaOw.at(ui->listWidget->currentRow())
                .getOficinas().at(ui->listWidget_3->currentRow())
                .getPeticiones().at(ui->listWidget_4->currentRow());

        dialogPeticiones pe;
        pe.setPeticionAEditar(pet);
        pe.setModal(true);
        pe.exec();

        ui->listWidget_4->clear();
        guardarEnArchivo();

        entradaHistorial h {false, true, false, pet.getPlazasPedidas(),
                          pet.neg->getOrigen(), pet.neg->getDestino(),
                          listaOw.at(n1).getNombre(),
                    listaOw.at(n1).getOficinas().at(n2).getNombre(),
                    listaOw.at(n1).getOficinas().at(n2).getPais(),
                    listaOw.at(n1).getOficinas().at(n2).getContinente()};
        log.push_back(h);

    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Oficina/Peticion"
                             " seleccionado");
    }
}

///////////////////////////// BORRAR //////////////////////////////////////////

/**
 * @brief mainWindow::on_actionBorOwner_triggered
 */
void mainWindow::on_actionBorOwner_triggered() {
    // TODO: Preguntar si estas seguro de borrar owner y mostrar datos

    // Calcular el indice del owner seleccionado y borrarlo
    if (!ui->listWidget->selectedItems().isEmpty()) {
        listaOw.erase(listaOw.begin() + ui->listWidget->currentRow());

        ui->listWidget->clear();
        for (auto &it : listaOw)
            ui->listWidget->addItem(it.getNombre().c_str());

        guardarEnArchivo();
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner seleccionado");
    }
}

/**
 * @brief mainWindow::on_actionBorNego_triggered
 */
void mainWindow::on_actionBorNego_triggered() {
    if (!ui->listWidget_2->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()) {
        pel::vector<std::shared_ptr<Nego>> &listaNegos =
                listaOw.at(ui->listWidget->currentRow()).getNegos();
        int curRow = ui->listWidget_2->currentRow();

        /**
         * Aprovechamos use_count del shared_ptr. Si devuelve mas de 1,
         * significa que hay otros shared_ptr (desde peticiones)
         * apuntando a este nego.
         */

        if (listaNegos.at(curRow).use_count() <= 1) {
            listaNegos.erase(listaNegos.begin() + curRow);
        } else {
            QMessageBox::warning(this, "Warning",
                                 "Hay peticiones de este Nego");
        }

        guardarEnArchivo();
        ui->listWidget_2->clear();
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Nego seleccionado");
    }
}

void mainWindow::on_actionBorOficina_triggered() {
    if (!ui->listWidget_3->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()) {
        pel::vector<Oficina> &listaOficinas =
                listaOw.at(ui->listWidget->currentRow()).getOficinas();
        int curRow = ui->listWidget_3->currentRow();

        for (auto &it : listaOficinas.at(curRow).getPeticiones())
            it.neg->devolverPlazas(it.getPlazasPedidas());

        listaOficinas.erase(listaOficinas.begin() + curRow);

        ui->listWidget_3->clear();
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
        pel::vector<Peticion> &listPet =
                listaOw.at(ui->listWidget->currentRow()).getOficinas()
                .at(ui->listWidget_3->currentRow()).getPeticiones();
        int curOw = ui->listWidget->currentRow();
        int curOf = ui->listWidget_3->currentRow();
        int curRow = ui->listWidget_4->currentRow();

        Peticion pet = listPet.at(curRow);

        entradaHistorial h {false, false, true, pet.getPlazasPedidas(),
                          pet.neg->getOrigen(), pet.neg->getDestino(),
                          listaOw.at(curOw).getNombre(),
                    listaOw.at(curOw).getOficinas().at(curOf).getNombre(),
                    listaOw.at(curOw).getOficinas().at(curOf).getPais(),
                    listaOw.at(curOw).getOficinas().at(curOf).getContinente()};
        log.push_back(h);

        // Si borras peticion devolvemos las plazas al nego
        pet.neg->devolverPlazas(pet.getPlazasPedidas());

        listPet.erase(listPet.begin() + curRow);

        ui->listWidget_4->clear();
        guardarEnArchivo();

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
    // TODO - seleccionar automaticamente la primera coincidencia?
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

/**
 * @brief Hacer login
 * Indicamos a la ventana de Login que queremos hacer login.
 * Una vez se ha cerrado cogemos mediante signals & slots el nombre del
 * usuario y lo mostramos en la ventana.
 */
void mainWindow::on_pushButton_2_clicked() {
    /**
     * @brief log
     */
    dialogLogin log;
    log.setEstado(0);
    log.setModal(true);

    // Signal & slot mechanism with new syntax
    // http://wiki.qt.io/New_Signal_Slot_Syntax

    connect(&log, &dialogLogin::cambioDeUsuario,
            this, &mainWindow::cambiarUsuario);
    log.exec();
}

/**
 * @brief Serializamos a un JSON con Cereal
 * Cereal serializa en un archivo JSON la lista de Owners (que a
 * su vez contiene los Negos, Oficinas y Peticiones)
 */
void mainWindow::guardarEnArchivo() {
    std::ofstream myfile("../../data/data.json");
    if (myfile) {
        // Declaramos que va a ser un archivo JSON
        cereal::JSONOutputArchive archive(myfile);
        // Serializamos listaOw
        archive(cereal::make_nvp("Owner", listaOw));
    }
}

/**
 * @brief mainWindow::cambiarUsuario
 * @param nombre
 * Funcion de cambiar usuario para acceder a la aplicacion
 */
void mainWindow::cambiarUsuario(std::string nombre) {
    QString QNombre = QString::fromUtf8(nombre.c_str());
    ui->label_2->setText(QNombre);
    // TODO - si el usuario no es admin desactivar ciertas funciones
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

void mainWindow::on_listWidget_4_currentRowChanged(int currentRow) {
    QColor green("green");
    QColor white("white");
    for (int i = 0; i < ui->listWidget_4->count(); ++i) {
        if (i == currentRow)
            ui->listWidget_4->item(i)->setBackgroundColor(green);
        else
            ui->listWidget_4->item(i)->setBackgroundColor(white);
    }
    // TODO - cambiar el color del Nego que corresponda
}

void mainWindow::on_actionLog_de_Peticiones_triggered() {
    dialogInforme di;
    di.setModal(true);
    di.cargar(&listaOw);
    di.cargarH(&log);
    di.exec();
}
