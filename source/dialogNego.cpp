/*DESCRIPCION:Se definen las funciones de la ventana grafica dialogNego,
 * se muestra qué hará cada botón
  o campo que aparezca (en la ventana gráfica).
 * AUTORES: David Jimenez, ayuda Estefania Ortego, Hugo Ferrando añade retoques
 */

#include "./ui_dialogNego.h"  // Se guardan los datos en la ventana gráfica de dialogNego
#include "./dialogNego.hpp"   // van a estar los datos de la cabecera de nego
#include "./pel_vector.hpp"

/**
 * @brief dialogNego::dialogNego
 * @param parent
 * Contenido de ventana grafica nego
 */
dialogNego::dialogNego(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogNego) {
    ui->setupUi(this);
}

/**
 * @brief dialogNego::~dialogNego
 * Destructor
 */
dialogNego::~dialogNego() {
    delete ui;
}

/**
 * @brief dialogNego::cargar
 * Funcion de cargar y tipo de contenido que tendrá dicha funcion
 */
void dialogNego::cargar() {
    for (auto &it : *ow)
        ui->comboBox->addItem(it.getNombre().c_str());
}

/**
 * @brief dialogNego::setNe
 * @param neg
 * Accede al vector de negos
 */
void dialogNego::setNe(pel::vector<std::shared_ptr<Nego>> *neg) {
    ne = neg;  // Negos modificados
}

/**
 * @brief dialogNego::setOw
 * @param own
 * vector de owner va a ser usado en ventana de nego
 */
void dialogNego::setOw(pel::vector<Owner> *own) {
    ow = own; // Owners modificados
}

/**
 * @brief dialogNego::on_comboBox_currentIndexChanged
 * @param index
 */
void dialogNego::on_comboBox_currentIndexChanged(int index) {
    // Repasar!!!
    Owner *own = &ow->at(index);
    setNe(&own->getNegos());
}

/**
 * @brief dialogNego::on_buttonOkCancel_accepted
 * Al acceder a la ventana nego,presionamos sobre
 * los botones aceptar y cancelar
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
        newN->setOrigen(ui->lineOrigen->text().toStdString());
        newN->setDestino(ui->lineDestino->text().toStdString());
        newN->setNumeroPlazas(ui->linePlazas->text().toInt());
        Fecha fech;
        fech.setDia(ui->dateEdit->date().day());
        fech.setMes(ui->dateEdit->date().month());
        fech.setAnio(ui->dateEdit->date().year());
        newN->setFecha(fech);
        std::shared_ptr<Nego> ptr(newN);
        ne->push_back(ptr);  // devuelve la lista
    }
}

void dialogNego::setNegoAEditar(Nego &neg) {
    editando = true;
    negoAEditar = &neg;
    ui->lineDestino->setText(negoAEditar->getDestino().c_str());
    ui->lineOrigen->setText(negoAEditar->getOrigen().c_str());
    ui->linePlazas->setText(std::to_string(negoAEditar->getNumeroPlazas()).c_str());
    Fecha fech = negoAEditar->getFecha();
    QDate date(fech.getAnio(), fech.getMes(), fech.getDia());
    ui->dateEdit->setDate(date);  // TODO: No pone la fecha

    // TODO: Mostrar el nego que corresponda en vez del primero
    // ui->comboBox->setItemText(ow->at(modRowOwner).getNombre().c_str());
    ui->comboBox->setEnabled(false);
}
