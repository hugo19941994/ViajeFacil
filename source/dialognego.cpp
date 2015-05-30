/*DESCRIPCION:Se definen las funciones de la ventana grafica dialogNego, se muestra qué hará cada botón
  o campo que aparezca (en la ventana gráfica).
 * AUTORES: David Jimenez, ayuda Estefania Ortego, Hugo Ferrando añade retoques
 */

#include "./ui_dialogNego.h"  // Se guardan los datos en la ventana gráfica de dialogNego
#include "./dialogNego.hpp"   // van a estar los datos de la cabecera de nego
#include "./pel_vector.hpp"

/**
 * @brief dialogNego::dialogNego
 * @param parent
 */
dialogNego::dialogNego(QWidget *parent) :  // Contenido de ventana grafica nego
    QDialog(parent),
    /**
         * @brief ui
         */
    ui(new Ui::dialogNego) {
    ui->setupUi(this);
}
/**
 * @brief dialogNego::~dialogNego
 */
dialogNego::~dialogNego() {  // Destructor, desaparecerán los datos cuando el usuario lo decida
    delete ui;
}

// Funcion de cargar y tipo de contenido que tendrá dicha funcion
/**
 * @brief dialogNego::cargar
 */
void dialogNego::cargar() {
    for (auto &it : *this->ow)
        this->ui->comboBox->addItem(it.getNombre().c_str());
}

// Funcion modificar owner y negos
/**
 * @brief dialogNego::setRows
 * @param modRowOwner
 * @param modRowNego
 */
void dialogNego::setRows(int modRowOwner, int modRowNego) {
    this->modRowOwner = modRowOwner;  // datos modificados de owner

    this->modRowNego = modRowNego;  // datos modificados en nego
    Owner *ow = &this->ow->at(modRowOwner);  // puntero de modificacion de owners en opcion modificar owner
    // si no hay owners, no hay negos
    this->setNe(ow->getNegos());  // los owners van a permitir que se muestren los negos

    // lugar donde se van a modificar los datos
    this->ui->lineDestino->setText(this->ne->at(this->modRowNego)->getDestino().c_str());
    this->ui->lineOrigen->setText(this->ne->at(this->modRowNego)->getOrigen().c_str());
    this->ui->linePlazas->setText(std::to_string(this->ne->at(this->modRowNego)->getNumeroPlazas()).c_str());
    Fecha fech = this->ne->at(modRowNego)->getFecha();
    QDate date(fech.getAnio(), fech.getMes(), fech.getDia());
    this->ui->dateEdit->setDate(date);  // TODO: No pone la fecha

    // TODO: Mostrar el nego que corresponda en vez del primero
    // this->ui->comboBox->setItemText(this->ow->at(modRowOwner).getNombre().c_str());
    this->ui->comboBox->setEnabled(false);
}

/**
 * @brief dialogNego::setNe
 * @param neg
 */
// Accede al vector de negos
void dialogNego::setNe(pel::vector<std::shared_ptr<Nego>> &neg) {
    this->ne = &neg;  // Negos modificados
}
/**
 * @brief dialogNego::setOw
 * @param own
 */
// vector de owner va a ser usado en ventana de nego
void dialogNego::setOw(pel::vector<Owner> &own) {
    this->ow = &own; // Owners modificados
}
// ventana principal aparecen los owners asociados a los negos cuando se hace clic sobre un owner
/**
 * @brief dialogNego::on_comboBox_currentIndexChanged
 * @param index
 */
void dialogNego::on_comboBox_currentIndexChanged(int index) {
    // Repasar!!!
    Owner *ow = &this->ow->at(index);
    this->setNe(ow->getNegos());
}

// Al acceder a la ventana nego,presionamos sobre los botones aceptar y cancelar
/**
 * @brief dialogNego::on_buttonOkCancel_accepted
 */
void dialogNego::on_buttonOkCancel_accepted() {
    if(this->modRowNego != -1 && this->modRowOwner != -1){ // modifica datos
        ne->at(modRowNego)->setOrigen(this->ui->lineOrigen->text().toStdString());
        ne->at(modRowNego)->setDestino(this->ui->lineDestino->text().toStdString());
        ne->at(modRowNego)->setNumeroPlazas(this->ui->linePlazas->text().toInt());
        Fecha fech;
        fech.setDia(this->ui->dateEdit->date().day());
        fech.setMes(this->ui->dateEdit->date().month());
        fech.setAnio(this->ui->dateEdit->date().year());
        ne->at(modRowNego)->setFecha(fech);
    } else {  // se crean los negos con la lista nueva de datos
        Nego *newN = new Nego;
        newN->setOrigen(this->ui->lineOrigen->text().toStdString());
        newN->setDestino(this->ui->lineDestino->text().toStdString());
        newN->setNumeroPlazas(this->ui->linePlazas->text().toInt());
        Fecha fech;
        fech.setDia(this->ui->dateEdit->date().day());
        fech.setMes(this->ui->dateEdit->date().month());
        fech.setAnio(this->ui->dateEdit->date().year());
        newN->setFecha(fech);
        std::shared_ptr<Nego> ptr(newN);
        this->ne->push_back(ptr);  // devuelve la lista
    }
}
