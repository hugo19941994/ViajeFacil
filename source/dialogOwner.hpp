/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *
 *  Los owners: van a tener oficinas y negos (creado por la compañía).
 *  Son los que tienen oficinas que sirven de intermediario con los
 *  clientes, y gestionan las peticiones, les solicitan una serie de
 *  pasajes a los negos, los negos le dan unos billetes de avión
 *  o paquetes que los owners se encargan de responder esa petición
 *  a las oficinas.
 */

#ifndef DIAGOWNER_H
#define DIAGOWNER_H

#include <QDialog>
#include "./pelVector.hpp"
#include "./owner.hpp"

namespace Ui {
class dialogOwner;
}

/**
 * @brief Dialogo de Owners
 */
class dialogOwner : public QDialog {
    Q_OBJECT

 public:
    explicit dialogOwner(QWidget *parent = 0);

    ~dialogOwner();

    /**
     * @brief Edita el Owner
     * Edita el Owner que ha sido pasado por referencia
     */
    void setOwnerAEditar(Owner *ow);

    /**
     * @brief Crea un Owner
     * Crea un nuevo Owner y se lo devuelve a mainWindow,
     * el cual lo mete en su Vector
     */
    Owner crear();

    void setListaOwners(pel::Vector<Owner> const *lista){
        listaOw = lista;
    }

    void accept();
private slots:  // NOLINT - https://github.com/google/styleguide/issues/30
    void on_buttonBox_accepted();

 private:
    bool maybeSave = false;
    pel::Vector<Owner> const *listaOw;
    bool editando = false;
    Owner *ownerAEditar;
    Ui::dialogOwner *ui;
};

#endif  // DIAGOWNER_H
