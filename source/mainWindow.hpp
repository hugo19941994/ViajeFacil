/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jiménez Cuevas
 *  Ventana principal, definicion de todas las funciones para que
 *  se comuniquen los dialog y las clases
 */

#ifndef mainWindow_H
#define mainWindow_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <string>
#include "./pelVector.hpp"
#include "./owner.hpp"
#include "./entradaHistorial.hpp"

namespace Ui {
class mainWindow;
}

/**
 * @brief Ventana Principal
 * Al crear el mainWindow desactivamos casi todo.
 * Para activar el resto de funcionas hay que hacer login
 */
class mainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit mainWindow(QWidget *parent = 0);

    ~mainWindow();

 private slots:  // NOLINT - https://github.com/google/styleguide/issues/30
    /**
     * @brief Crear Un Owner nuevo
     * Se abre el dialogo de Owners vacio y al aceptar cogemos el
     * Owner creado y lo metemos en el Vector de Owners
     */
    void on_actionCreOwner_triggered();

    /**
     * @brief Crear una Oficina nueva
     * Se abre un dialogo de Oficinas vacio y al aceptar cogemos la
     * Oficina creada y la metemos en el Vector de Oficinas que corresponda.
     * Sabemos al Owner al que pertenece gracais a la funcion .nivel que
     * nos devuelve el Owner que el usuario ha escogido.
     */
    void on_actionCreOficina_triggered();

    /**
     * @brief Crear un Nego nuevo
     * Se abre un dialogo de Negos vacio y al aceptar cogemos el
     * Nego creado y lo metemos en el Vector de Negos que corresponda.
     * Sabemos al Owner al que pertenece gracais a la funcion .nivel que
     * nos devuelve el Owner que el usuario ha escogido.
     */
    void on_actionCreNego_triggered();

    /**
     * @brief Crear una Peticion nueva
     * Se abre un dialogo de Peticiones vacio y al aceptar cogemos la
     * Peticion creada y la metemos en el Vector de Peticion que corresponda.
     *
     * Sabemos al Owner y la Oficina al que pertenece
     * gracais a la funcion .nivelOw y .nivelOf que
     * nos devuelve el Owner ya la Oficina que el usuario ha escogido.
     *
     * Quitamos al Nego que se ha escogido los asientos necesarios.
     *
     * Luego creamos una nueva entrada para el Historial y lo metemos en el Vector.
     */
    void on_actionCrePeticion_triggered();

    /**
     * @brief Crear un Usuario nuevo
     * Abre una ventana de Usuarios. En la misma ventana se creara el usuario.
     */
    void on_actionCreUsuario_triggered();

    /**
     * @brief mainWindow::on_actionBorOwner_triggered
     */
    void on_actionBorOwner_triggered();

    /**
     * @brief mainWindow::on_actionBorNego_triggered
     */
    void on_actionBorNego_triggered();
    void on_actionBorOficina_triggered();
    void on_actionBorPeticion_triggered();

    /**
     * @brief Modificar un Owner
     * Se selecciona un Owner en el listWidget y se abre una ventana de Owners
     * rellena con el nombre del Owner a modificar. El Owner se modifica en la
     * propia ventana. Luego refrescamos la lista de Owners.
     * Si no se seleccionó un Owner se emite un mensaje de error.
     */
    void on_actionModOwner_triggered();

    /**
     * @brief Modificar un Nego
     * Se selecciona un Owner y un Nego en los listWidgets y se abre
     * una ventana de Negos con los campos del Nego.
     * El Nego se modifica en la propia ventana.
     * Luego refrescamo la lista de Owners.
     * Si no se seleccionó un Owner/Nego se emite un mensaje de error.
     */
    void on_actionModNego_triggered();
    void on_actionModOficina_triggered();
    void on_actionModPeticion_triggered();

    /**
     * @brief Filtrar Owners
     * Con esta funcion filtras la lista de Owners.
     * Solo aparecerean en la lista las files que coincidas
     * con lo que ha escrito el usuario
     */
    void on_lineEdit_2_textChanged(const QString &arg1);

    /**
     * @brief Filtrar Negos
     * Con esta funcion filtras la lista de Negos.
     * Solo aparecerean en la lista las files que coincidas
     * con lo que ha escrito el usuario
     */
    void on_lineEdit_3_textChanged(const QString &arg1);

    /**
     * @brief Filtrar Oficinas
     * Con esta funcion filtras la lista de Oficinas.
     * Solo aparecerean en la lista las files que coincidas
     * con lo que ha escrito el usuario
     */
    void on_lineEdit_4_textChanged(const QString &arg1);

    /**
     * @brief Filtrar Peticiones
     * Con esta funcion filtras la lista de Peticiones.
     * Solo aparecerean en la lista las files que coincidas
     * con lo que ha escrito el usuario
     */
    void on_lineEdit_5_textChanged(const QString &arg1);

    /**
     * @brief Hacer login
     * Indicamos a la ventana de Login que queremos hacer login.
     * Una vez se ha cerrado cogemos mediante signals & slots el nombre del
     * usuario y lo mostramos en la ventana.
     */
    void on_pushButton_2_clicked();

    /**
     * @brief mainWindow::cambiarUsuario
     * @param nombre
     * Funcion de cambiar usuario para acceder a la aplicacion
     */
    void cambiarUsuario(std::string nombre);

    /**
     * @brief Serializamos a un JSON con Cereal
     * Cereal serializa en un archivo JSON la lista de Owners (que a
     * su vez contiene los Negos, Oficinas y Peticiones)
     */
    void guardarEnArchivo();

    void on_actionLog_de_Peticiones_triggered();
    void on_actionInforme_Owners_que_mejor_consumen_Negos_triggered();

    void on_listWidget_itemPressed(QListWidgetItem *item);
    void on_listWidget_3_itemPressed(QListWidgetItem *item);

 private:
    Ui::mainWindow *ui;

    /**
     * @brief Vector de Owners
     * En este Vector residen los Owners (que a su vez
     * incluyen Negos, oficinas y Peticiones)
     */
    pel::Vector<Owner> listaOw;

    /**
     * @brief Historial de Peticiones
     * En este Vector se guardan entradas de acciones de Peticiones.
     * Cualquier acción (crear, modificar o borrar) de alguna peticion
     * se guarda en este Vector
     */
    pel::Vector<entradaHistorial> log;
};

#endif  // mainWindow_H
