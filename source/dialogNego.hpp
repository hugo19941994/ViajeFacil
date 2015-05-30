/*DESCRIPCION: Los negos: una compañía crea negos, son los encargados de gestionar los paquetes
  y billetes aéreos, que le darán a los owners y estos a las oficinas correspondientes.
 *AUTORES: David Jimenez, ayuda Estefania Ortego, Hugo Ferrando añade retoques
 */

#ifndef dialogNego_H
#define dialogNego_H

// Va a tener negos y owners
#include <QDialog>
#include "pel_vector.hpp"
#include "./nego.hpp"
#include "./owner.hpp"


namespace Ui {  // se llamará a la clase nego.hpp

class dialogNego;
}
/**
 * @brief The dialogNego class
 */
// define el tipo que va a ser la clase dialogNego
class dialogNego : public QDialog {
    Q_OBJECT  // tipo objeto

 public:
    /**
     * @brief dialogNego
     * @param parent
     */
    explicit dialogNego(QWidget *parent = 0);

    ~dialogNego();  // Destructor
    /**
     * @brief setNe
     * @param neg
     */
    // Imprime vector nego y escribe nego nuevo
    void setNe(pel::vector<std::shared_ptr<Nego>>& neg);
    /**
     * @brief setOw
     * @param own
     */
    // Imprime vector owner y escribe nuevo owner
    void setOw(pel::vector<Owner>& own);
    /**
     * @brief cargar
     */
    void cargar();
    void setNegoAEditar(Nego &neg);

 private slots: // funciones cuando presionas los botones en la ventana de negos
    /**
     * @brief on_comboBox_currentIndexChanged
     * @param index
     */
    void on_comboBox_currentIndexChanged(int index);
    /**
     * @brief on_buttonOkCancel_accepted
     */

    void on_buttonOkCancel_accepted();  // boton ok-Cancelar

 private:
    bool editando = false;
    Nego *negoAEditar;
    /**
     * @brief ui
     */
    Ui::dialogNego *ui;  // ventana de nego modificada
    /**
     * @brief ow
     */
    // se modifica owner y se introducen owners en el vector
    pel::vector<Owner> *ow;
    /**
     * @brief ne
     */
    // vector nego, se modifican los negos
    pel::vector<std::shared_ptr<Nego>> *ne;

};

#endif  // dialogNego_H
