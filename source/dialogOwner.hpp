/*DESCRIPCION: Los owners: van a tener oficinas y negos (creado por la compañía).
 Son los que tienen oficinas que sirven de intermediario con los clientes, y gestionan
 las peticiones, les solicitan una serie de pasajes a los negos, los negos le dan unos
 billetes de avión o paquetes que los owners se encargan de responder esa petición a las oficinas.
 * AUTORES:Hugo Ferrando
 */
#ifndef DIAGOWNER_H
#define DIAGOWNER_H

#include <QDialog>
#include "./owner.hpp"
#include "./pel_vector.hpp"

namespace Ui {
/**
 *Funcion que llamará a la ventana de owner.cpp
 */
class dialogOwner;
}
/**
 * @brief The dialogOwner class
 */
class dialogOwner : public QDialog {
    Q_OBJECT

 public:
    /**
     * @brief dialogOwner
     * @param parent
     */
    explicit dialogOwner(QWidget *parent = 0);
    ~dialogOwner();  // destructor
    /**
     * @brief setOw
     * @param own
     */
    void setOw(pel::vector<Owner>& own);
    /**
     * @brief setRow
     * @param index
     */
    void setRow(int index);

 private slots:
    /**
     * @brief on_buttonBox_accepted
     * Presionar el boton aceptar para acceder a la ventana de diagowner.cpp
     */
    void on_buttonBox_accepted();

 private:
    /**
     * @brief modRow
     */
    int modRow = -1;
    /**
     * @brief ui
     */
    Ui::dialogOwner *ui;
    /**
     * @brief ow
     */
    pel::vector<Owner>* ow; //Se muestra la lista de owners en la parte(puntero) de owners

};

#endif  // DIAGOWNER_H
