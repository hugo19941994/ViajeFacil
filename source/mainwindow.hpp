//VENTANA PRINCIPAL
//AUTORES: Hugo Ferrando
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "./owner.hpp"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
     /**
      * @brief MainWindow
      * @param parent
      */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

 private slots:
    /**
    * @brief on_pushButton_2_clicked
    */
    void on_pushButton_2_clicked();
    /**
     * @brief cambiarUsuario
     * @param nombre
     */
    void cambiarUsuario(std::string nombre);
    /**
     * @brief guardarEnArchivo
     */
    void guardarEnArchivo();
    /**
     * @brief on_listWidget_2_pressed
     * @param index
     */
    void on_listWidget_2_pressed(const QModelIndex &index);
    /**
     * @brief on_actionCrePeticion_triggered
     */
    void on_actionCrePeticion_triggered();
    /**
     * @brief on_actionCreNego_triggered
     */
    void on_actionCreNego_triggered();
    /**
     * @brief on_actionCreOwner_triggered
     */
    void on_actionCreOwner_triggered();
    /**
     * @brief on_actionCreUsuario_triggered
     */
    void on_actionCreUsuario_triggered();
    /**
     * @brief on_actionBorOwner_triggered
     */
    void on_actionBorOwner_triggered();
    /**
     * @brief on_actionModOwner_triggered
     */
    void on_actionModOwner_triggered();
    /**
     * @brief on_actionModNego_triggered
     */
    void on_actionModNego_triggered();
    /**
     * @brief on_actionBorNego_triggered
     */
    void on_actionBorNego_triggered();

    void on_actionCreOficina_triggered();

    void on_listWidget_3_pressed(const QModelIndex &index);

    void on_actionBorOficina_triggered();

    void on_actionBorPeticion_triggered();

    void on_actionModOficina_triggered();

    void on_actionModPeticion_triggered();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

private:
    /**
     * @brief ui
     */
    Ui::MainWindow *ui;
    /**
     * @brief listaOw
     */
    std::vector<Owner> listaOw;
};

#endif  // MAINWINDOW_H
