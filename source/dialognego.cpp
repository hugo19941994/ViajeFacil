/*DESCRIPCION:Se definen las funciones de la ventana grafica dialognego, se muestra qué hará cada botón
  o campo que aparezca (en la ventana gráfica).
 * AUTORES: David Jimenez, ayuda Estefania Ortego, Hugo Ferrando añade retoques
 */

#include <vector>
#include "./ui_dialognego.h" //se guardan los datos en la ventana gráfica de dialognego
#include "./dialognego.hpp" //van a estar los datos de la cabecera de nego

/**
 * @brief DialogNego::DialogNego
 * @param parent
 */
DialogNego::DialogNego(QWidget *parent) :  //contenido de ventana grafica nego
    QDialog(parent),
    /**
         * @brief ui
         */
    ui(new Ui::DialogNego) {
    ui->setupUi(this);
}
/**
 * @brief DialogNego::~DialogNego
 */
DialogNego::~DialogNego() { //destructor, desaparecerán los datos cuando el usuario lo decida
    delete ui;
}

//Funcion de cargar y tipo de contenido que tendrá dicha funcion
/**
 * @brief DialogNego::cargar
 */
void DialogNego::cargar() {
    for (auto &it : *this->ow)
        this->ui->comboBox->addItem(it.getNombre().c_str());
}

//funcion modificar owner y negos
/**
 * @brief DialogNego::setRows
 * @param modRowOwner
 * @param modRowNego
 */
void DialogNego::setRows(int modRowOwner, int modRowNego)
{
    this->modRowOwner = modRowOwner; //datos modificados de owner

    this->modRowNego = modRowNego; //datos modificados en nego
}

/**
 * @brief DialogNego::setMod
 */
void DialogNego::setMod()
{
    /**
     * @brief ow
     */
    Owner *ow = &this->ow->at(modRowOwner);  //puntero de modificacion de owners en opcion modificar owner
    //si no hay owners, no hay negos
    this->setNe(ow->getNegos()); //los owners van a permitir que se muestren los negos

    this->mod = true; //datos a modificar de nego

    //lugar donde se van a modificar los datos
    this->ui->lineDestino->setText(this->ne->at(this->modRowNego).getDestino().c_str());
    this->ui->lineOrigen->setText(this->ne->at(this->modRowNego).getOrigen().c_str());
    this->ui->linePlazas->setText(std::to_string(this->ne->at(this->modRowNego).getNumeroPlazas()).c_str());
    Fecha fech = this->ne->at(modRowNego).getFecha();
    QDate date(fech.getAnio(), fech.getMes(), fech.getAnio());
    this->ui->dateEdit->setDate(date);  // TODO: No pone la fecha

    // TODO: Mostrar el nego que corresponda en vez del primero
    //this->ui->comboBox->setItemText(this->ow->at(modRowOwner).getNombre().c_str());
    this->ui->comboBox->setEnabled(false);

}

/**
 * @brief DialogNego::setNe
 * @param neg
 */
void DialogNego::setNe(std::vector<Nego> &neg) { //accede al vector de negos

    this->ne = &neg; //negos modificados
}
/**
 * @brief DialogNego::setOw
 * @param own
 */
void DialogNego::setOw(std::vector<Owner> &own) { //vector de owner va a ser usado en ventana de nego

    this->ow = &own; //owners modificados
}
 //ventana principal aparecen los owners asociados a los negos cuando se hace clic sobre un owner
/**
 * @brief DialogNego::on_comboBox_currentIndexChanged
 * @param index
 */
void DialogNego::on_comboBox_currentIndexChanged(int index) {
    // Repasar!!!
    Owner *ow = &this->ow->at(index);
    this->setNe(ow->getNegos());
}

//Al acceder a la ventana nego,presionamos sobre los botones aceptar y cancelar
/**
 * @brief DialogNego::on_buttonOkCancel_accepted
 */
void DialogNego::on_buttonOkCancel_accepted() {
    if(this->mod == true){ //modifica datos
        ne->at(modRowNego).setOrigen(this->ui->lineOrigen->text().toStdString());
        ne->at(modRowNego).setDestino(this->ui->lineDestino->text().toStdString());
        ne->at(modRowNego).setNumeroPlazas(this->ui->linePlazas->text().toInt());
        Fecha fech;
        fech.setDia(this->ui->dateEdit->date().day());
        fech.setMes(this->ui->dateEdit->date().month());
        fech.setAnio(this->ui->dateEdit->date().year());
        ne->at(modRowNego).setFecha(fech);
    }
    else{ //se crean los negos con la lista nueva de datos
        Nego *newN = new Nego;
        newN->setOrigen(this->ui->lineOrigen->text().toStdString());
        newN->setDestino(this->ui->lineDestino->text().toStdString());
        newN->setNumeroPlazas(this->ui->linePlazas->text().toInt());
        Fecha fech;
        fech.setDia(this->ui->dateEdit->date().day());
        fech.setMes(this->ui->dateEdit->date().month());
        fech.setAnio(this->ui->dateEdit->date().year());
        newN->setFecha(fech);
        this->ne->push_back(*newN); //devuelve la lista
    }
}
