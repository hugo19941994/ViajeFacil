/*AUTORES: Hugo Ferrando
 *DESCRIPCION: se van a implementar las funciones definidas previamente en diagowner.hpp
 *
 */

#include <vector>
#include "./diagowner.hpp"
#include "./ui_diagowner.h" //llamado a la ventana gráfica de owners

/**
 * @brief diagOwner::diagOwner
 * @param parent
 */
diagOwner::diagOwner(QWidget *parent) : //tipo de funcion del dialog owner

    QDialog(parent),
    /**
         * @brief ui
         */
    ui(new Ui::diagOwner) {

    ui->setupUi(this);
}
/**
 * @brief diagOwner::~diagOwner
 */
diagOwner::~diagOwner() {  //destructor, se destruirán el o los datos seleccionados en owners
    delete ui;
}

//Funcion de aceptar en ventana de owner
/**
 * @brief diagOwner::on_buttonBox_accepted
 */
void diagOwner::on_buttonBox_accepted() {
    //datos guardados en linea de texto nombre
    if(this->modRow != -1) {

        //definimos el tipo de campo que será NOMBRE
        this->ow->at(modRow).setNombre(this->ui->lineEdit->text().toStdString());

    }
    else{
        Owner *newO = new Owner;  // Va bien declararlo sin new? en el stack?
        newO->setNombre(this->ui->lineEdit->text().toStdString());//Se crea nuevo owner
        this->ow->push_back(*newO); //Devuelve el nuevo owner introducido perteneciente al vector owner
    }
}

/**
 * @brief diagOwner::setOw
 * @param own
 */
void diagOwner::setOw(std::vector<Owner> &own) {
    //Pide datos en owner y los muestra en lista
    this->ow = &own;

}
/**
 * @brief diagOwner::setRow
 * @param index
 */
void diagOwner::setRow(int index)
{   //Refresca los datos en la página principal en la parte de owners y pone los introducidos
    this->modRow = index;
    this->ui->lineEdit->setText(this->ow->at(modRow).getNombre().c_str());
}
