/*DESCRIPCION: las peticiones son elaboradas por todas las partes de este proyecto, es decir, cada
 * acción que se realice va a ser una petición que se quedará guardada en esta clase "peticiones"
 * AUTORES: Sergio Candel, ayuda David Jimenez y Hugo Ferrando
 */
#ifndef dialogPeticiones_H
#define dialogPeticiones_H

#include <QDialog>
#include "./pel_vector.hpp"
#include "./peticion.hpp"  // va a participar la cabecera de peticiones y la de owner
#include "./owner.hpp"  // encontraremos datos de owners

namespace Ui {  // funcion que guardará la petición durante un periodo de tiempo, hasta que finalice el programa
class dialogPeticiones;  // clase dialogPeticiones
}

// se define la clase cómo va a ser y su contenido.
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
      */
     void setOw(pel::vector<Owner>& own);  // va a pedir como parámetro owners se guardaran en el vector owners y se podrá mostrar modificado
     /**
      * @brief setPe
      * @param pet
      */
     void setPe(pel::vector<Peticion>& pet);  // pide parámetro peticiones, devuelve vector peticiones ->lista peticiones
     /**
      * @brief cargar
      */
     void setOf(pel::vector<Oficina>& of);
     void setNe(pel::vector<std::shared_ptr<Nego>>& ne);
     void cargar();  // función cargar, archivo donde se guardan las peticiones
     void setRows(int modRowOwner, int modRowOficina, int modRowPeticion);


 private slots:
     void on_comboBox_currentIndexChanged(int index);

     void on_buttonBox_accepted();

     void on_buttonBox_rejected();

 private:
    /**
    * @brief ui
    */
    Ui::dialogPeticiones *ui;  // parte gráfica, se modificará y se mostrará el resultado final
    /**
     * @brief ow
     */
    pel::vector<Owner> *ow;  // lista de owners
    /**
     * @brief pe
     */
    pel::vector<Oficina> *of;  // vector peticiones
    pel::vector<Peticion> *pe;  // vector peticiones
    pel::vector<std::shared_ptr<Nego>> *ne;  // vector peticiones
    int modRowOwner = -1;
    int modRowOficina = -1;
    int modRowPeticion = -1;
};

#endif  // dialogPeticiones_H
