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
    if (editando) {
        negoAEditar->setOrigen(ui->lineOrigen->text().toStdString());
        negoAEditar->setDestino(ui->lineDestino->text().toStdString());
        negoAEditar->setNumeroPlazas(ui->linePlazas->text().toInt());
        Fecha fech;
        fech.setDia(ui->dateEdit->date().day());
        fech.setMes(ui->dateEdit->date().month());
        fech.setAnio(ui->dateEdit->date().year());
        negoAEditar->setFecha(fech);
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

void dialogNego::setNegoAEditar(Nego &neg){
    editando = true;
    negoAEditar = &neg;
    ui->lineDestino->setText(negoAEditar->getDestino().c_str());
    ui->lineOrigen->setText(negoAEditar->getOrigen().c_str());
    ui->linePlazas->setText(std::to_string(negoAEditar->getNumeroPlazas()).c_str());
    Fecha fech = negoAEditar->getFecha();
    QDate date(fech.getAnio(), fech.getMes(), fech.getDia());
    ui->dateEdit->setDate(date);  // TODO: No pone la fecha

    // TODO: Mostrar el nego que corresponda en vez del primero
    // this->ui->comboBox->setItemText(this->ow->at(modRowOwner).getNombre().c_str());
    ui->comboBox->setEnabled(false);
}
