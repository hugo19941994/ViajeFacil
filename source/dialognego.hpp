/*DESCRIPCION: Los negos: una compañía crea negos, son los encargados de gestionar los paquetes
  y billetes aéreos, que le darán a los owners y estos a las oficinas correspondientes.
 *AUTORES: David Jimenez, ayuda Estefania Ortego, Hugo Ferrando añade retoques
 */

#ifndef DIALOGNEGO_H
#define DIALOGNEGO_H

//Va a tener negos y owners
#include <QDialog>
#include <vector>
#include "./nego.hpp"
#include "./owner.hpp"


namespace Ui { //se llamará a la clase nego.hpp

class DialogNego;
}
/**
 * @brief The DialogNego class
 */
class DialogNego : public QDialog { //define el tipo que va a ser la clase dialognego
    Q_OBJECT  //tipo objeto

 public:
    /**
     * @brief DialogNego
     * @param parent
     */
    explicit DialogNego(QWidget *parent = 0);

    ~DialogNego();//Destructor
    /**
     * @brief setNe
     * @param neg
     */
    void setNe(std::vector<Nego>& neg);  //imprime vector nego y escribe nego nuevo
    /**
     * @brief setOw
     * @param own
     */
    void setOw(std::vector<Owner>& own);  // imprime vector owner y escribe nuevo owner
    /**
     * @brief cargar
     */
    void cargar();
    /**
     * @brief setRows
     * @param modRowOwner
     * @param modRowNego
     */
    void setRows(int modRowOwner, int modRowNego);


 private slots: //funciones cuando presionas los botones en la ventana de negos
    /**
     * @brief on_comboBox_currentIndexChanged
     * @param index
     */
    void on_comboBox_currentIndexChanged(int index);
    /**
     * @brief on_buttonOkCancel_accepted
     */

    void on_buttonOkCancel_accepted();  //boton ok-Cancelar


 private:
    /**
     * @brief modRowOwner
     */
    int modRowOwner = -1;
    /**
     * @brief modRowNego
     */
    int modRowNego = -1;
    /**
     * @brief ui
     */
    Ui::DialogNego *ui; //ventana de nego modificada
    /**
     * @brief ow
     */
    std::vector<Owner> *ow; //se modifica owner y se introducen owners en el vector
    /**
     * @brief ne
     */
    std::vector<Nego> *ne; //vector nego, se modifican los negos

};

#endif  // DIALOGNEGO_H
