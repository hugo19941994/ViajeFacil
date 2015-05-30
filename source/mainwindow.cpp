//AUTORES: HUGO FERRANDO
//Ventana principal, definicion de todas las funciones para que se comuniquen los dialog y las clases

#include <vector>
#include <fstream>
#include <string>
#include <QStringBuilder>
#include <QMessageBox>
#include <QListWidgetItem>
#include "./mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "./login.hpp"
#include "./diagowner.hpp"
#include "./dialognego.hpp"
#include "./dialogOficinas.hpp"
#include "./cereal/archives/json.hpp"
#include "./cereal/types/vector.hpp"
#include "./cereal/types/memory.hpp"
#include "./dialogpeticiones.hpp"

/**
* @brief MainWindow::MainWindow
* @param parent
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //Cargar ficheros
    // TODO: Comprobar si existe
    std::ifstream myfile("../../data/data.json"); //crea archivo lectura
    //myfile.open("../../data/data.json");//abre el archivo
    if(myfile){
        cereal::JSONInputArchive ar(myfile);//tipo de archivo, asocia libreria con el archivo
        ar(this->listaOw);//carga la lista

        this->ui->listWidget->clear();//carga la lista en mainwindow y la refresca poniendo lo nuevo introducido
        for (auto &it : listaOw) {
            this->ui->listWidget->addItem(it.getNombre().c_str());  // Convertir con c_string porque convierte implicitamente a QString
        }
    }

    //TODO - comprobar que exista un usuario admin
    //Si existe desactivar crear usuario
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
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief MainWindow::on_pushButton_2_clicked
 */
void MainWindow::on_pushButton_2_clicked() {
    /**
     * @brief log
     */
    Login log;
    log.setEstado(0);
    log.setModal(true);
    // Signal & slot mechanism with new syntax http://wiki.qt.io/New_Signal_Slot_Syntax
    connect(&log, &Login::cambioDeUsuario, this, &MainWindow::cambiarUsuario);
    log.exec();
}

//Guardar archivos
/**
 * @brief MainWindow::guardarEnArchivo
 */
void MainWindow::guardarEnArchivo() {
    std::ofstream myfile; //Crea el archivo
    myfile.open("../../data/data.json"); //abre el archivo creado
    cereal::JSONOutputArchive archive(myfile); //Tipo de archivo creado
    archive(cereal::make_nvp("Owner", this->listaOw)); //guarda lista de owners en el archivo
}

//Funcion de cambiar usuario para acceder a la aplicacion
/**
 * @brief MainWindow::cambiarUsuario
 * @param nombre
 */
void MainWindow::cambiarUsuario(std::string nombre) {
    QString QNombre = QString::fromUtf8(nombre.c_str());
    this->ui->label_2->setText(QNombre);
    //TODO - si el usuario no es admin desactivar ciertas funciones
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
}

//cuando se seleccionen datos en el campo 2 de la ventana principal, owner asociados a negos  y viceversa
/**
 * @brief MainWindow::on_listWidget_pressed
 * @param index
 */
void MainWindow::on_listWidget_pressed(const QModelIndex &index) {
    auto ow = this->listaOw.at(index.row());
    this->ui->listWidget_2->clear();
    for (auto &it : ow.getNegos()) {
        /**
         * @brief orDe
         */
        QString orDe = it->getOrigen().c_str();  // TODO:Se puede hacer en una linea?
        orDe.append(" - ");
        orDe.append(it->getDestino().c_str());
        this->ui->listWidget_2->addItem(orDe);
    }

    this->ui->listWidget_3->clear();
    for (auto it : ow.getOficinas()) {
        QString nomPa = it.getNombre().c_str();  // TODO:Se puede hacer en una linea?
        this->ui->listWidget_3->addItem(nomPa);
    }
    ui->listWidget_4->clear();
}

/**
 * @brief MainWindow::on_actionCrePeticion_triggered
 */
void MainWindow::on_actionCrePeticion_triggered() {
    DialogPeticiones peticiones;
    peticiones.setOw(this->listaOw);
    peticiones.cargar();
    peticiones.setModal(true);
    peticiones.exec();

    guardarEnArchivo();
}

/**
 * @brief MainWindow::on_actionCreNego_triggered
 */
void MainWindow::on_actionCreNego_triggered() {
    DialogNego *ng = new DialogNego;
    ng->setOw(this->listaOw);
    ng->cargar();
    ng->setModal(true);
    ng->exec();

    guardarEnArchivo();

    // Refrescar la lista que corresponda - por ahora se limpia y hay que volver a hacer click
    this->ui->listWidget_2->clear();
}

/**
 * @brief MainWindow::on_actionCreOwner_triggered
 */
void MainWindow::on_actionCreOwner_triggered() {
    diagOwner ow;
    ow.setOw(this->listaOw);
    ow.setModal(true);
    ow.exec();

    this->ui->listWidget->clear();
    for (auto &it : listaOw) {
        this->ui->listWidget->addItem(it.getNombre().c_str());
    }

   guardarEnArchivo();
}

/**
 * @brief MainWindow::on_actionCreUsuario_triggered
 */
void MainWindow::on_actionCreUsuario_triggered() {
    Login log;
    log.setModal(true);
    log.setEstado(1);
    log.exec();
}

/**
 * @brief MainWindow::on_actionBorOwner_triggered
 */
void MainWindow::on_actionBorOwner_triggered() {
    // TODO: Preguntar si estas seguro de borrar owner y mostrar datos

    // Calcular el indice del owner seleccionado y borrarlo
    if(!ui->listWidget->selectedItems().isEmpty()){
        QListWidgetItem *selected = this->ui->listWidget->selectedItems().first();
        if(selected != NULL)  // ARREGLAR - NO FUNCIONA
            listaOw.erase(listaOw.begin() + this->ui->listWidget->row(selected));

        this->ui->listWidget->clear();
        for (auto &it : listaOw) {
            this->ui->listWidget->addItem(it.getNombre().c_str());
        }

        guardarEnArchivo();
    }
}

/**
 * @brief MainWindow::on_actionModOwner_triggered
 */
void MainWindow::on_actionModOwner_triggered() {
    if(!ui->listWidget->selectedItems().isEmpty()){
        QListWidgetItem *selected = this->ui->listWidget->selectedItems().first();

        diagOwner ow;
        ow.setOw(this->listaOw);
        ow.setRow(this->ui->listWidget->row(selected)); // Le pasamos el indice del owner que queremos modificar
        ow.setModal(true);
        ow.exec();

        this->ui->listWidget->clear();
        for (auto &it : listaOw) {
            this->ui->listWidget->addItem(it.getNombre().c_str());
        }

       guardarEnArchivo();
    }
}

/**
 * @brief MainWindow::on_actionModNego_triggered
 */
void MainWindow::on_actionModNego_triggered() {
    if(!ui->listWidget_2->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()){
        /**
        * @brief selectedOwner
        */
        QListWidgetItem *selectedOwner = this->ui->listWidget->selectedItems().first();
        /**
         * @brief selectedNego
         */
        QListWidgetItem *selectedNego = this->ui->listWidget_2->selectedItems().first();
        /**
         * @brief ng
         */
        DialogNego *ng = new DialogNego;
        ng->setOw(this->listaOw);
        ng->cargar();
        ng->setRows(this->ui->listWidget->row(selectedOwner),
                    this->ui->listWidget_2->row(selectedNego));
        // TODO - IDEA en vez que pasarle el numero de fila pasar directamente
        // un puntero al nego que hay que modificar? alguna desventajas?
        ng->setModal(true);
        ng->exec();
        /**
         * @brief guardarEnArchivo
         */
        guardarEnArchivo();

        // Refrescar la lista que corresponda - por ahora se limpia y hay que volver a hacer click
        this->ui->listWidget_2->clear();
    }
}

/**
 * @brief MainWindow::on_actionBorNego_triggered
 */
void MainWindow::on_actionBorNego_triggered() {
    if(!ui->listWidget_2->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()){
        /**
        * @brief selectedOwner
        */
        QListWidgetItem *selectedOwner = this->ui->listWidget->selectedItems().first();
        QListWidgetItem *selectedNego = this->ui->listWidget_2->selectedItems().first();
        /**
         * @brief listaNegos
         */
        pel::vector<std::shared_ptr<Nego>> &listaNegos = listaOw.at(this->ui->listWidget->row(selectedOwner)).getNegos();

        // Aprovechamos use_count del shared_ptr. Si devuelve mas de 1, significa que hay
        // otros shared_ptr (desde peticiones) apuntando a este nego.
        if(listaNegos.at(this->ui->listWidget_2->row(selectedNego)).use_count() <= 1) {
            listaNegos.erase(listaNegos.begin() + this->ui->listWidget_2->row(selectedNego));
        }
        else
            QMessageBox::warning(this, "Warning", "Hay peticiones de este Nego");

        // TODO: Refrescar la lista de negos que toque
        this->ui->listWidget_2->clear();
        /**
         * @brief guardarEnArchivo
         */
        guardarEnArchivo();
        // TODO - SI BORRAMOS NEGO HABRA QUE BORRAR SUS PETICIONES!
        // O POR LO MENOS AVISAR Y EVITAR QUE SE BORRE EL NEGO
    }
}

void MainWindow::on_actionCreOficina_triggered() {
    DialogOficinas *diagOf = new DialogOficinas;
    diagOf->setOw(this->listaOw);
    diagOf->cargar();
    diagOf->setModal(true);
    diagOf->exec();

    guardarEnArchivo();
}

void MainWindow::on_listWidget_3_pressed(const QModelIndex &index) {
    auto ow = this->listaOw.at(ui->listWidget->currentIndex().row());
    auto pe = ow.getOficinas().at(index.row()).getPeticiones();
    this->ui->listWidget_4->clear();
    for (auto it : pe) {
        QString orDe = std::to_string(it.getPlazasPedidas()).c_str();
        this->ui->listWidget_4->addItem(orDe);
    }
}

void MainWindow::on_actionBorOficina_triggered() {
    if(!ui->listWidget_3->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()){
        QListWidgetItem *selectedOwner = this->ui->listWidget->selectedItems().first();
        QListWidgetItem *selectedOficina = this->ui->listWidget_3->selectedItems().first();

        pel::vector<Oficina> &listaOficinas = listaOw.at(this->ui->listWidget->row(selectedOwner)).getOficinas();
        listaOficinas.erase(listaOficinas.begin() + this->ui->listWidget_3->row(selectedOficina));

        this->ui->listWidget_3->clear();
        guardarEnArchivo();
        // TODO - SI BORRAS OFICINAS SE BORRAN SUS PETICIONES
        // QUIZAS HAYA QUE AVISAR DE QUE ESA OFICINA TIENE PETICIONES
    }
}

void MainWindow::on_actionBorPeticion_triggered() {
    if(!ui->listWidget_4->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()
            && !ui->listWidget_3->selectedItems().isEmpty()){
        QListWidgetItem *selectedOwner = this->ui->listWidget->selectedItems().first();
        QListWidgetItem *selectedOficinas = this->ui->listWidget_3->selectedItems().first();
        QListWidgetItem *selectedPeticion = this->ui->listWidget_4->selectedItems().first();

        pel::vector<Oficina> &listaOficinas = listaOw.at(this->ui->listWidget->row(selectedOwner)).getOficinas();
        pel::vector<Peticion> &listaPeticiones = listaOficinas.at(this->ui->listWidget_3->row(selectedOficinas)).getPeticiones();

        // Si borras peticion devolvemos las plazas al nego
        int asientos = listaPeticiones.at(this->ui->listWidget_4->row(selectedPeticion)).getPlazasPedidas();
        Nego &neg = *listaPeticiones.at(this->ui->listWidget_4->row(selectedPeticion)).neg;
        neg.setNumeroPlazas(neg.getNumeroPlazas() + asientos);
        listaPeticiones.erase(listaPeticiones.begin() + this->ui->listWidget_4->row(selectedPeticion));

        this->ui->listWidget_4->clear();
        guardarEnArchivo();
    }
}

void MainWindow::on_actionModOficina_triggered() {
    if(!ui->listWidget_3->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()){
        QListWidgetItem *selectedOw = this->ui->listWidget->selectedItems().first();
        QListWidgetItem *selectedOf = this->ui->listWidget_3->selectedItems().first();

        DialogOficinas *of = new DialogOficinas;
        of->setOw(this->listaOw);
        of->cargar();
        of->setRows(this->ui->listWidget->row(selectedOw),
                    this->ui->listWidget_3->row(selectedOf));

        of->setModal(true);
        of->exec();

        guardarEnArchivo();
    }

}

void MainWindow::on_actionModPeticion_triggered() {
    if(!ui->listWidget_4->selectedItems().isEmpty()
            && !ui->listWidget->selectedItems().isEmpty()
            && !ui->listWidget_3->selectedItems().isEmpty()){
        QListWidgetItem *selectedOw = this->ui->listWidget->selectedItems().first();
        QListWidgetItem *selectedOf = this->ui->listWidget_3->selectedItems().first();
        QListWidgetItem *selectedPe = this->ui->listWidget_4->selectedItems().first();

        DialogPeticiones *pe = new DialogPeticiones;
        pe->setOw(this->listaOw);
        pe->cargar();
        pe->setRows(this->ui->listWidget->row(selectedOw),
                    this->ui->listWidget_3->row(selectedOf),
                    this->ui->listWidget_4->row(selectedPe));
        pe->setModal(true);
        pe->exec();

        guardarEnArchivo();
    }
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1) {
    for(int i = 0; i < ui->listWidget->count(); ++i) {
        if(ui->listWidget->item(i)->text().contains(arg1))
            ui->listWidget->item(i)->setHidden(false);
        else
            ui->listWidget->item(i)->setHidden(true);
    }
    // TODO - seleccionar automaticamente la primera coincidencia?
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1) {
    for(int i = 0; i < ui->listWidget_2->count(); ++i) {
        if(ui->listWidget_2->item(i)->text().contains(arg1))
            ui->listWidget_2->item(i)->setHidden(false);
        else
            ui->listWidget_2->item(i)->setHidden(true);
    }
}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1) {
    for(int i = 0; i < ui->listWidget_3->count(); ++i) {
        if(ui->listWidget_3->item(i)->text().contains(arg1))
            ui->listWidget_3->item(i)->setHidden(false);
        else
            ui->listWidget_3->item(i)->setHidden(true);
    }
}

void MainWindow::on_lineEdit_5_textChanged(const QString &arg1) {
    for(int i = 0; i < ui->listWidget_4->count(); ++i) {
        if(ui->listWidget_4->item(i)->text().contains(arg1))
            ui->listWidget_4->item(i)->setHidden(false);
        else
            ui->listWidget_4->item(i)->setHidden(true);
    }
}

void MainWindow::on_listWidget_4_currentRowChanged(int currentRow) {
    QColor green("green");
    QColor white("white");
    for(int i = 0; i < ui->listWidget_4->count(); ++i) {
        if(i == currentRow)
            ui->listWidget_4->item(i)->setBackgroundColor(green);
        else
            ui->listWidget_4->item(i)->setBackgroundColor(white);
    }

    //Nego n = listaOw.at(ui->listWidget_2->row(ui->listWidget_2->selectedItems().first())).getOficinas().at(ui->listWidget_3->row(ui->listWidget_3->selectedItems().first())).getPeticiones().at(ui->listWidget_4->row(ui->listWidget_4->selectedItems().first())).neg;

}
