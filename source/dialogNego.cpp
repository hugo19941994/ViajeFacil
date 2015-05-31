/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jimenez
 *  @author Estefania Ortego
 *  Se definen las funciones de la ventana grafica dialogNego,
 *  se muestra qué hará cada botón o campo que aparezca (en la ventana gráfica).
 */

#include "./ui_dialogNego.h"
#include "./dialogNego.hpp"
#include "./pelVector.hpp"

dialogNego::dialogNego(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogNego) {
    ui->setupUi(this);
}

dialogNego::~dialogNego() { delete ui; }

/**
 * @brief dialogNego::cargar
 * Carga el comboBox con los Owners
 */
void dialogNego::cargar(pel::Vector<Owner>* own) {
    for (auto &it : *own)
        ui->comboBox->addItem(it.getNombre().c_str());
}

/**
 * @brief Hacer click en aceptar
 * Si estamos editando un Nego lo modificamos. Si no significia
 * que estamos creando un Nego nuevo, pero solo señalamos que
 * hemos aceptado y el MainWindow se encarga de crearlo.
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
    }
}

/**
 * @brief Preparar la ventana para editar
 * Rellenamos los campos con la referencia del Owner pasada, y activamos
 * el flag de editar.
 */
void dialogNego::setNegoAEditar(Nego *neg) {
    editando = true;
    negoAEditar = neg;
    ui->lineDestino->setText(negoAEditar->getDestino().c_str());
    ui->lineOrigen->setText(negoAEditar->getOrigen().c_str());
    ui->linePlazas->
            setText(std::to_string(negoAEditar->getNumeroPlazas()).c_str());
    Fecha fech = negoAEditar->getFecha();
    QDate date(fech.getAnio(), fech.getMes(), fech.getDia());
    ui->dateEdit->setDate(date);

    // TODO(Hugo) - Mostrar el nego que corresponda en vez del primero
    // ui->comboBox->setItemText(ow->at(modRowOwner).getNombre().c_str());
    ui->comboBox->setEnabled(false);
}

/**
 * @brief Crear un nuevo Nego
 * Creamos un Nego con los campos que ha rellenado el usuario.
 * El mainWindow se encargará de meterlo en el Vector.
 */
Nego dialogNego::crear() {
    Fecha f{ui->dateEdit->date().day(),
            ui->dateEdit->date().month(),
            ui->dateEdit->date().year()};
    Nego neg {ui->lineDestino->text().toStdString(),
             ui->lineOrigen->text().toStdString(),
             ui->linePlazas->text().toUInt(), f};
    return neg;
}

/**
 * @brief Devolver el Owner seleccionado
 * Devolvemos el índice del Owner seleccionado para que el mainWindow
 * sepa en que Vector de Owners debe meter el nuevo Nego.
 */
int dialogNego::nivel() { return ui->comboBox->currentIndex(); }
