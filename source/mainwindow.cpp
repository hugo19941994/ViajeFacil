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
    std::ifstream myfile; //crea archivo lectura
    myfile.open("../../data/data.json");//abre el archivo
    cereal::JSONInputArchive ar(myfile);//tipo de archivo, asocia libreria con el archivo
    ar(this->listaOw);//carga la lista

    this->ui->listWidget_2->clear();//carga la lista en mainwindow y la refresca poniendo lo nuevo introducido
    for (auto &it : listaOw) {
        this->ui->listWidget_2->addItem(it.getNombre().c_str());  // Convertir con c_string porque convierte implicitamente a QString
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
        QString orDe = it.getOrigen().c_str();  // TODO:Se puede hacer en una linea?
        orDe.append(" - ");
        orDe.append(it.getDestino().c_str());
        this->ui->listWidget->addItem(orDe);
    }

    // TODO: Cuando este oficinas hecho agregar
    // aqui el codigo de refresco de oficinas
    for (auto it : ow.getOficinas()){
    QString nomPa = it.getNombre().c_str();  // TODO:Se puede hacer en una linea?
    nomPa.append(" - ");
    nomPa.append(it.getPais().c_str());
    nomPa.append(" - ");
    nomPa.append(it.getContinente().c_str());

    this->ui->listWidget_3->addItem(nomPa);
    }


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

    this->ui->listWidget_4->clear();
    for (auto &it : listaOw){
        this->ui->listWidget_4->addItem(it.getNombre().c_str());
    }
}

/**
 * @brief MainWindow::on_actionCreNego_triggered
 */
void MainWindow::on_actionCreNego_triggered()
{
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
void MainWindow::on_actionCreOwner_triggered()
{
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
void MainWindow::on_actionCreUsuario_triggered()
{
    Login log;
    log.setModal(true);
    log.setEstado(1);
    log.exec();
}

/**
 * @brief MainWindow::on_actionBorOwner_triggered
 */
void MainWindow::on_actionBorOwner_triggered()
{
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
void MainWindow::on_actionModOwner_triggered()
{
    QListWidgetItem *selected = this->ui->listWidget_2->selectedItems().first();

    diagOwner ow;
    ow.setOw(this->listaOw);
    ow.setRow(this->ui->listWidget_2->row(selected)); // Le pasamos el indice del owner que queremos modificar
    ow.setMod();
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
void MainWindow::on_actionModNego_triggered()
{
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
    ng->setMod();
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
void MainWindow::on_actionBorNego_triggered()
{
    /**
    * @brief selectedOwner
    */
    QListWidgetItem *selectedOwner = this->ui->listWidget_2->selectedItems().first();
    QListWidgetItem *selectedNego = this->ui->listWidget->selectedItems().first();
    /**
     * @brief listaNegos
     */
    std::vector<Nego> &listaNegos = listaOw.at(this->ui->listWidget_2->row(selectedOwner)).getNegos();
    listaNegos.erase(listaNegos.begin() + this->ui->listWidget->row(selectedNego));

    // TODO: Refrescar la lista de negos que toque
    this->ui->listWidget->clear();
    /**
     * @brief guardarEnArchivo
     */
    guardarEnArchivo();
}

void MainWindow::on_actionCreOficina_triggered()
{
    DialogOficinas *diagOf = new DialogOficinas;
    diagOf->setOw(this->listaOw);
    diagOf->cargar();
    diagOf->setModal(true);
    diagOf->exec();




}
