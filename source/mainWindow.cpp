// AUTORES: HUGO FERRANDO
// Ventana principal, definicion de todas las funciones para que
// se comuniquen los dialog y las clases

#include <fstream>
#include <QMessageBox>
#include "./ui_mainWindow.h"
#include "./mainWindow.hpp"
#include "./dialogLogin.hpp"
#include "./dialogOwner.hpp"
#include "./dialogNego.hpp"
#include "./dialogOficinas.hpp"
#include "./dialogPeticiones.hpp"
#include "./cereal/archives/json.hpp"

/**
* @brief mainWindow::mainWindow
* @param parent
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

        // Refrescamos la lista de Owners
        ui->listWidget->clear();
        for (auto &it : listaOw) {
            // c_str() necesario para la conversion implicita a QString
            ui->listWidget->addItem(it.getNombre().c_str());
        }
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

/**
 * @brief mainWindow::~mainWindow
 */
mainWindow::~mainWindow() {
    delete ui;
}

//////////////////// LISTWIDGET PRESSED ///////////////////////////////////////

/**
 * @brief mainWindow::on_listWidget_pressed
 * @param index
 * cuando se seleccionen datos en el campo 2 de la ventana principal,
 * owner asociados a negos  y viceversa
 */
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
        ui->listWidget_4->addItem(orDe);
    }
}

//////////////////////////// CREAR ////////////////////////////////////////////

/**
 * @brief mainWindow::on_actionCreOwner_triggered
 */
void mainWindow::on_actionCreOwner_triggered() {
    dialogOwner ow;
    ow.setOw(&listaOw);
    ow.setModal(true);
    ow.exec();

    ui->listWidget->clear();
    for (auto &it : listaOw) {
        ui->listWidget->addItem(it.getNombre().c_str());
    }

    guardarEnArchivo();
}

/**
 * @brief mainWindow::on_actionCreNego_triggered
 */
void mainWindow::on_actionCreNego_triggered() {
    dialogNego ng;
    ng.setOw(&listaOw);
    ng.cargar();
    ng.setModal(true);
    ng.exec();

    guardarEnArchivo();

    // Refrescar la lista que corresponda
    // por ahora se limpia y hay que volver a hacer click
    ui->listWidget_2->clear();
}


void mainWindow::on_actionCreOficina_triggered() {
    dialogOficinas diagOf;
    diagOf.setOw(&listaOw);
    diagOf.cargar();
    diagOf.setModal(true);
    diagOf.exec();

    guardarEnArchivo();
}

/**
 * @brief mainWindow::on_actionCrePeticion_triggered
 */
void mainWindow::on_actionCrePeticion_triggered() {
    dialogPeticiones peticiones;
    peticiones.setOw(&listaOw);
    peticiones.cargar();
    peticiones.setModal(true);
    peticiones.exec();

    guardarEnArchivo();
}

/**
 * @brief mainWindow::on_actionCreUsuario_triggered
 */
void mainWindow::on_actionCreUsuario_triggered() {
    dialogLogin log;
    log.setModal(true);
    log.setEstado(1);
    log.exec();
}

//////////////////////////// MODIFICAR ////////////////////////////////////////

/**
 * @brief mainWindow::on_actionModOwner_triggered
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
 * @brief mainWindow::on_actionModNego_triggered
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

        ui->listWidget_3->clear();

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

        Peticion &pet = listaOw.at(ui->listWidget->currentRow())
                .getOficinas().at(ui->listWidget_3->currentRow())
                .getPeticiones().at(ui->listWidget_4->currentRow());

        dialogPeticiones pe;
        pe.setPeticionAEditar(pet);
        pe.setModal(true);
        pe.exec();

        guardarEnArchivo();
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

        // TODO: Refrescar la lista de negos que toque
        ui->listWidget_2->clear();
        guardarEnArchivo();
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Nego seleccionado");
    }
}

void mainWindow::on_actionBorOficina_triggered() {
    if (!ui->listWidget_3->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()) {
        QListWidgetItem *selectedOwner = ui->listWidget->selectedItems().first();
        QListWidgetItem *selectedOficina = ui->listWidget_3->selectedItems().first();

        pel::vector<Oficina> &listaOficinas = listaOw.at(ui->listWidget->row(selectedOwner)).getOficinas();
        listaOficinas.erase(listaOficinas.begin() + ui->listWidget_3->row(selectedOficina));

        ui->listWidget_3->clear();
        guardarEnArchivo();
        // TODO - SI BORRAS OFICINAS SE BORRAN SUS PETICIONES
        // QUIZAS HAYA QUE AVISAR DE QUE ESA OFICINA TIENE PETICIONES
    } else {
        QMessageBox::warning(this, "Warning",
                             "No hay ningun Owner/Oficina seleccionado");
    }
}

void mainWindow::on_actionBorPeticion_triggered() {
    if (!ui->listWidget_4->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()
            && !ui->listWidget_3->selectedItems().isEmpty()) {
        QListWidgetItem *selectedOwner = ui->listWidget->selectedItems().first();
        QListWidgetItem *selectedOficinas = ui->listWidget_3->selectedItems().first();
        QListWidgetItem *selectedPeticion = ui->listWidget_4->selectedItems().first();

        pel::vector<Oficina> &listaOficinas = listaOw.at(ui->listWidget->row(selectedOwner)).getOficinas();
        pel::vector<Peticion> &listaPeticiones = listaOficinas.at(ui->listWidget_3->row(selectedOficinas)).getPeticiones();

        // Si borras peticion devolvemos las plazas al nego
        int asientos = listaPeticiones.at(ui->listWidget_4->row(selectedPeticion)).getPlazasPedidas();
        Nego &neg = *listaPeticiones.at(ui->listWidget_4->row(selectedPeticion)).neg;
        neg.setNumeroPlazas(neg.getNumeroPlazas() + asientos);
        listaPeticiones.erase(listaPeticiones.begin() + ui->listWidget_4->row(selectedPeticion));

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

////////////////////////////////OTROS//////////////////////////////////////////

/**
 * @brief mainWindow::on_pushButton_2_clicked
 * Boton de Login
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
 * @brief mainWindow::guardarEnArchivo
 * Guardar archivos
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
}
