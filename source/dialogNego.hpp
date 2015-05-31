/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jimenez
 *  @author Estefania Ortego
 *
 *  Los negos: una compañía crea negos, son los encargados de gestionar
 *  los paquetes y billetes aéreos, que le darán a los owners y estos
 *  a las oficinas correspondientes.
 */

#ifndef dialogNego_H
#define dialogNego_H

#include <QDialog>
#include "./pel_vector.hpp"
#include "./nego.hpp"
#include "./owner.hpp"


namespace Ui {
class dialogNego;
}

/**
 * @brief Dialogo de Negos
 */
class dialogNego : public QDialog {
    Q_OBJECT

 public:
    explicit dialogNego(QWidget *parent = 0);

    ~dialogNego();

    /**
     * @brief Carga los comboBox
     * Recorre el vector de Owners y rellena el comboBox
     */
    void cargar(pel::vector<Owner>* own);

    /**
     * @brief Edita el Nego
     * Edita el Nego que ha sido pasado por referencia
     */
    void setNegoAEditar(Nego &neg);

    /**
     * @brief Crea un Nego
     * Crea un nuevo Nego y se lo devuelve a mainWindow,
     * el cual lo mete en su vector correspondiente
     */
    Nego crear();

    /**
     * @brief Owner seleccionado
     * Devuelve el nivel del comboBox. Este nivel indica que Owner
     * ha sido seleccionado. Se pasa al mainWindow para que sepa
     * en que Owner tiene que insertar el Nego
     */
    int nivel();

 private slots:
    void on_buttonOkCancel_accepted();

 private:
    bool editando = false;
    Nego *negoAEditar;
    Ui::dialogNego *ui;
};

#endif  // dialogNego_H
