/*DESCRIPCION: las peticiones son elaboradas por todas las partes
 * de este proyecto, es decir, cada acción que se realice va a ser una petición
 * que se quedará guardada en esta clase "peticiones"
 * AUTORES: Sergio Candel, ayuda David Jimenez y Hugo Ferrando
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

    /**
      * @brief setOw
      * @param own
      * va a pedir como parámetro owners se guardaran
      * en el vector owners y se podrá mostrar modificado
      */
     void setOw(pel::vector<Owner>* own);

     /**
      * @brief setPe
      * @param pet
      * pide parámetro peticiones,
      * devuelve vector peticiones ->lista peticiones
      */
     void setPe(pel::vector<Peticion>* pet);

     /**
      * @brief cargar
      */
     void setOf(pel::vector<Oficina>* of);

     void setNe(pel::vector<std::shared_ptr<Nego>>* ne);

     void cargar();

     void setPeticionAEditar(Peticion &pet);

 private slots:
     void on_comboBox_currentIndexChanged(int index);

     void on_buttonBox_accepted();

     void on_buttonBox_rejected();

 private:
    /**
    * @brief ui
    * parte gráfica, se modificará y se mostrará el resultado final
    */
    Ui::dialogPeticiones *ui;

    /**
     * @brief ow
     * lista de owners
     */
    pel::vector<Owner> *ow;

    /**
     * @brief pe
     * vector peticiones
     */
    pel::vector<Oficina> *of;

    pel::vector<Peticion> *pe;  // vector peticiones

    pel::vector<std::shared_ptr<Nego>> *ne;  // vector peticiones

    bool editando = false;

    Peticion *peticionAEditar;

};

#endif  // dialogPeticiones_H
