/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author Sergio Candel
 *  @author David Jimenez
 *
 *  las peticiones son elaboradas por todas las partes de este proyecto,
 *  es decir, cada acción que se realice va a ser una petición que
 *  se quedará guardada en esta clase "peticiones"
 */

#ifndef dialogPeticiones_H
#define dialogPeticiones_H

#include <QDialog>
#include "./pel_vector.hpp"
#include "./peticion.hpp"
#include "./owner.hpp"

namespace Ui {
class dialogPeticiones;
}

/**
 * @brief The dialogPeticiones class
 */
class dialogPeticiones : public QDialog {
    Q_OBJECT

 public:
    /**
     * @brief dialogPeticiones
     * @param parent
     */
    explicit dialogPeticiones(QWidget *parent = 0);

    ~dialogPeticiones();  // Destructor

     void cargar(pel::vector<Owner>* own);

     void setPeticionAEditar(Peticion &pet);

     Peticion crear();

     int nivelOw();
     int nivelOf();
     int nivelNe();

 private slots:
     void on_comboBox_currentIndexChanged(int index);

     void on_buttonBox_accepted();

 private:
    /**
    * @brief ui
    * parte gráfica, se modificará y se mostrará el resultado final
    */
    Ui::dialogPeticiones *ui;

    bool editando = false;

    pel::vector<Owner> *ow;

    Peticion *peticionAEditar;

};

#endif  // dialogPeticiones_H
