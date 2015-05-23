//AUTORES: HUGO FERRANDO
//Ventana principal, definicion de todas las funciones para que se comuniquen los dialog y las clases

#include <vector>
#include <fstream>
#include <string>
#include <QStringBuilder>
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

        this->ui->listWidget_2->clear();//carga la lista en mainwindow y la refresca poniendo lo nuevo introducido
        for (auto &it : listaOw) {
            this->ui->listWidget_2->addItem(it.getNombre().c_str());  // Convertir con c_string porque convierte implicitamente a QString
        }
    }
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
}

//cuando se seleccionen datos en el campo 2 de la ventana principal, owner asociados a negos  y viceversa
/**
 * @brief MainWindow::on_listWidget_2_pressed
 * @param index
 */
void MainWindow::on_listWidget_2_pressed(const QModelIndex &index) {
    auto ow = this->listaOw.at(index.row());
    this->ui->listWidget->clear();
    for (auto it : ow.getNegos()) {
        /**
         * @brief orDe
         */
        QString orDe = it.get()->getOrigen().c_str();  // TODO:Se puede hacer en una linea?
        orDe.append(" - ");
        orDe.append(it.get()->getDestino().c_str());
        this->ui->listWidget->addItem(orDe);
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
    this->ui->listWidget->clear();
}

/**
 * @brief MainWindow::on_actionCreOwner_triggered
 */
void MainWindow::on_actionCreOwner_triggered() {
    diagOwner ow;
    ow.setOw(this->listaOw);
    ow.setModal(true);
    ow.exec();

    this->ui->listWidget_2->clear();
    for (auto &it : listaOw) {
        this->ui->listWidget_2->addItem(it.getNombre().c_str());
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
    QListWidgetItem *selected = this->ui->listWidget_2->selectedItems().first();
    if(selected != NULL)  // ARREGLAR - NO FUNCIONA
        listaOw.erase(listaOw.begin() + this->ui->listWidget_2->row(selected));

    this->ui->listWidget_2->clear();
    for (auto &it : listaOw) {
        this->ui->listWidget_2->addItem(it.getNombre().c_str());
    }

    guardarEnArchivo();
}

/**
 * @brief MainWindow::on_actionModOwner_triggered
 */
void MainWindow::on_actionModOwner_triggered() {
    QListWidgetItem *selected = this->ui->listWidget_2->selectedItems().first();

    diagOwner ow;
    ow.setOw(this->listaOw);
    ow.setRow(this->ui->listWidget_2->row(selected)); // Le pasamos el indice del owner que queremos modificar
    ow.setModal(true);
    ow.exec();

    this->ui->listWidget_2->clear();
    for (auto &it : listaOw) {
        this->ui->listWidget_2->addItem(it.getNombre().c_str());
    }

   guardarEnArchivo();
}

/**
 * @brief MainWindow::on_actionModNego_triggered
 */
void MainWindow::on_actionModNego_triggered() {
    /**
    * @brief selectedOwner
    */
    QListWidgetItem *selectedOwner = this->ui->listWidget_2->selectedItems().first();
    /**
     * @brief selectedNego
     */
    QListWidgetItem *selectedNego = this->ui->listWidget->selectedItems().first();
    /**
     * @brief ng
     */
    DialogNego *ng = new DialogNego;
    ng->setOw(this->listaOw);
    ng->cargar();
    ng->setRows(this->ui->listWidget_2->row(selectedOwner),
                this->ui->listWidget->row(selectedNego));
    // TODO - IDEA en vez que pasarle el numero de fila pasar directamente
    // un puntero al nego que hay que modificar? alguna desventajas?
    ng->setModal(true);
    ng->exec();
    /**
     * @brief guardarEnArchivo
     */
    guardarEnArchivo();

    // Refrescar la lista que corresponda - por ahora se limpia y hay que volver a hacer click
    this->ui->listWidget->clear();
}

/**
 * @brief MainWindow::on_actionBorNego_triggered
 */
void MainWindow::on_actionBorNego_triggered() {
    /**
    * @brief selectedOwner
    */
    QListWidgetItem *selectedOwner = this->ui->listWidget_2->selectedItems().first();
    QListWidgetItem *selectedNego = this->ui->listWidget->selectedItems().first();
    /**
     * @brief listaNegos
     */
    pel::vector<std::shared_ptr<Nego>> &listaNegos = listaOw.at(this->ui->listWidget_2->row(selectedOwner)).getNegos();
    listaNegos.erase(listaNegos.begin() + this->ui->listWidget->row(selectedNego));

    // TODO: Refrescar la lista de negos que toque
    this->ui->listWidget->clear();
    /**
     * @brief guardarEnArchivo
     */
    guardarEnArchivo();
    // TODO - SI BORRAMOS NEGO HABRA QUE BORRAR SUS PETICIONES!
    // O POR LO MENOS AVISAR Y EVITAR QUE SE BORRE EL NEGO
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
    auto ow = this->listaOw.at(ui->listWidget_2->currentIndex().row());
    auto pe = ow.getOficinas().at(index.row()).getPeticiones();
    this->ui->listWidget_4->clear();
    for (auto it : pe) {
        QString orDe = std::to_string(it.getPlazasPedidas()).c_str();
        this->ui->listWidget_4->addItem(orDe);
    }
}

void MainWindow::on_actionBorOficina_triggered() {
    QListWidgetItem *selectedOwner = this->ui->listWidget_2->selectedItems().first();
    QListWidgetItem *selectedOficina = this->ui->listWidget_3->selectedItems().first();

    pel::vector<Oficina> &listaOficinas = listaOw.at(this->ui->listWidget_2->row(selectedOwner)).getOficinas();
    listaOficinas.erase(listaOficinas.begin() + this->ui->listWidget_3->row(selectedOficina));

    this->ui->listWidget_3->clear();
    guardarEnArchivo();
    // TODO - SI BORRAS OFICINAS SE BORRAN SUS PETICIONES
    // QUIZAS HAYA QUE AVISAR DE QUE ESA OFICINA TIENE PETICIONES
}

void MainWindow::on_actionBorPeticion_triggered() {
    QListWidgetItem *selectedOwner = this->ui->listWidget_2->selectedItems().first();
    QListWidgetItem *selectedOficinas = this->ui->listWidget_3->selectedItems().first();
    QListWidgetItem *selectedPeticion = this->ui->listWidget_4->selectedItems().first();

    pel::vector<Oficina> &listaOficinas = listaOw.at(this->ui->listWidget_2->row(selectedOwner)).getOficinas();
    pel::vector<Peticion> &listaPeticiones = listaOficinas.at(this->ui->listWidget_3->row(selectedOficinas)).getPeticiones();

    // Si borras peticion devolvemos las plazas al nego
    int asientos = listaPeticiones.at(this->ui->listWidget_4->row(selectedPeticion)).getPlazasPedidas();
    Nego &neg = *listaPeticiones.at(this->ui->listWidget_4->row(selectedPeticion)).neg;
    neg.setNumeroPlazas(neg.getNumeroPlazas() + asientos);
    listaPeticiones.erase(listaPeticiones.begin() + this->ui->listWidget_4->row(selectedPeticion));

    this->ui->listWidget_4->clear();
    guardarEnArchivo();
}

void MainWindow::on_actionModOficina_triggered() {
    QListWidgetItem *selectedOw = this->ui->listWidget_2->selectedItems().first();
    QListWidgetItem *selectedOf = this->ui->listWidget_3->selectedItems().first();

    DialogOficinas *of = new DialogOficinas;
    of->setOw(this->listaOw);
    of->cargar();
    of->setRows(this->ui->listWidget_2->row(selectedOw),
                this->ui->listWidget_3->row(selectedOf));

    of->setModal(true);
    of->exec();

    guardarEnArchivo();

}

void MainWindow::on_actionModPeticion_triggered() {

}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1) {
    this->ui->listWidget_2->clear();
    int i=0;
    for (auto it : listaOw) {
        QString str = it.getNombre().c_str();
        if (str.contains(arg1))
            this->ui->listWidget_2->addItem(str);
        else {  // Hay que añadir esto porque si no ya no concuerda el numero de linea - explicarlo mejor!!
            this->ui->listWidget_2->addItem(str);
            ui->listWidget_2->item(i)->setHidden(true);
        }
        i++;
    }
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1) {
    QListWidgetItem *selectedOwner = this->ui->listWidget_2->selectedItems().first();
    auto ow = this->listaOw.at(this->ui->listWidget_2->row(selectedOwner));

    this->ui->listWidget->clear();
    int i=0;
    for (auto it : ow.getNegos()) {

        QString orDe = it.get()->getOrigen().c_str();  // TODO:Se puede hacer en una linea?
        orDe.append(" - ");
        orDe.append(it.get()->getDestino().c_str());

        if (orDe.contains(arg1))
            this->ui->listWidget->addItem(orDe);
        else {  // Hay que añadir esto porque si no ya no concuerda el numero de linea - explicarlo mejor!!
            this->ui->listWidget->addItem(orDe);
            ui->listWidget->item(i)->setHidden(true);
        }
        i++;
    }
}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1) {
    QListWidgetItem *selectedOwner = this->ui->listWidget_2->selectedItems().first();
    auto ow = this->listaOw.at(this->ui->listWidget_2->row(selectedOwner));

    this->ui->listWidget_3->clear();
    int i=0;
    for (auto it : ow.getOficinas()) {

        QString orDe = it.getNombre().c_str();

        if (orDe.contains(arg1))
            this->ui->listWidget_3->addItem(orDe);
        else {  // Hay que añadir esto porque si no ya no concuerda el numero de linea - explicarlo mejor!!
            this->ui->listWidget_3->addItem(orDe);
            ui->listWidget_3->item(i)->setHidden(true);
        }
        i++;
    }
}
