/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jimenez
 *  Ventana principal, definicion de todas las funciones para que
 *  se comuniquen los dialog y las clases
 */

#ifndef mainWindow_H
#define mainWindow_H

#include <QMainWindow>
#include <string>
#include "./pel_vector.hpp"
#include "./owner.hpp"
#include "./entradaHistorial.hpp"

namespace Ui {
class mainWindow;
}

/**
 * @brief Ventana Principal
 */
class mainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit mainWindow(QWidget *parent = 0);

    ~mainWindow();

 private slots:
    void on_actionCreOwner_triggered();
    void on_actionCreOficina_triggered();
    void on_actionCreNego_triggered();
    void on_actionCrePeticion_triggered();
    void on_actionCreUsuario_triggered();

    void on_actionBorOwner_triggered();
    void on_actionBorNego_triggered();
    void on_actionBorOficina_triggered();
    void on_actionBorPeticion_triggered();

    void on_actionModOwner_triggered();
    void on_actionModNego_triggered();
    void on_actionModOficina_triggered();
    void on_actionModPeticion_triggered();

    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_lineEdit_3_textChanged(const QString &arg1);
    void on_lineEdit_4_textChanged(const QString &arg1);
    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_listWidget_pressed(const QModelIndex &index);
    void on_listWidget_3_pressed(const QModelIndex &index);
    void on_listWidget_4_currentRowChanged(int currentRow);

    void on_pushButton_2_clicked();
    void cambiarUsuario(std::string nombre);
    void guardarEnArchivo();
    void on_actionLog_de_Peticiones_triggered();

 private:
    Ui::mainWindow *ui;

    /**
     * @brief Vector de Owners
     * En este Vector residen los Owners (que a su vez
     * incluyen Negos, oficinas y Peticiones)
     */
    pel::vector<Owner> listaOw;
    /**
     * @brief Historial de Peticiones
     * En este Vector se guardan entradas de acciones de Peticiones.
     * Cualquier acción (crear, modificar o borrar) de alguna peticion
     * se guarda en este vector
     */
    pel::vector<entradaHistorial> log;
};

#endif  // mainWindow_H
