/*DESCRIPCION: Los owners: van a tener oficinas y negos (creado por la compañía).
 Son los que tienen oficinas que sirven de intermediario con los clientes, y gestionan
 las peticiones, les solicitan una serie de pasajes a los negos, los negos le dan unos
 billetes de avión o paquetes que los owners se encargan de responder esa petición a las oficinas.
 * AUTORES:Hugo Ferrando
 */
#ifndef DIAGOWNER_H
#define DIAGOWNER_H

#include <QDialog>
#include <vector>
#include "owner.hpp"

namespace Ui {
/**
 *Funcion que llamará a la ventana de owner.cpp
 */
class diagOwner;
}
/**
 * @brief The diagOwner class
 */
class diagOwner : public QDialog {
    Q_OBJECT

 public:
    /**
     * @brief diagOwner
     * @param parent
     */
    explicit diagOwner(QWidget *parent = 0);
    ~diagOwner(); //destructor
    /**
     * @brief setOw
     * @param own
     */
    void setOw(std::vector<Owner>& own);
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
    Ui::diagOwner *ui;
    /**
     * @brief ow
     */
    std::vector<Owner>* ow; //Se muestra la lista de owners en la parte(punter) de owners

};

#endif  // DIAGOWNER_H
