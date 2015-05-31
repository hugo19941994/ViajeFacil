/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 */

#ifndef dialogOficinas_H
#define dialogOficinas_H

#include <QDialog>
#include "./pelVector.hpp"
#include "./owner.hpp"
#include "./oficina.hpp"
#include "./nego.hpp"
#include "./peticion.hpp"

namespace Ui {
class dialogOficinas;
}

/**
 * @brief Dialogo de Oficinas
 */
class dialogOficinas : public QDialog {
    Q_OBJECT

 public:
    explicit dialogOficinas(QWidget *parent = 0);
    ~dialogOficinas();

    /**
     * @brief Carga los comboBox
     * Recorre el Vector de Owners y rellena el comboBox
     */
    void cargar(pel::Vector<Owner>* own);

    /**
     * @brief Edita la Oficina
     * Edita la Oficina que ha sido pasado por referencia
     */
    void setOficinaAEditar(Oficina *ofi);

    /**
     * @brief Owner seleccionado
     * Devuelve el nivel del comboBox. Este nivel indica que Owner
     * ha sido seleccionado. Se pasa al mainWindow para que sepa
     * en que Owner tiene que insertar la Oficina
     */
    int nivel();

    /**
     * @brief Crea una Oficina
     * Crea una nuevo Oficina y se lo devuelve a mainWindow,
     * el cual lo mete en su Vector correspondiente
     */
    Oficina crear();

 private slots:  // NOLINT - https://github.com/google/styleguide/issues/30
    void on_buttonBox_accepted();

 private:
    bool editando = false;
    Oficina *oficinaAEditar;
    Ui::dialogOficinas *ui;
};

#endif  // dialogOficinas_H
