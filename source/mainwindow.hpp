#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "./owner.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

 private slots:
    void on_pushButton_2_clicked();

    void cambiarUsuario(std::string nombre);

    void guardarEnArchivo();

    void on_listWidget_2_pressed(const QModelIndex &index);

    void on_actionCrePeticion_triggered();

    void on_actionCreNego_triggered();

    void on_actionCreOwner_triggered();

    void on_actionCreUsuario_triggered();

    void on_actionBorOwner_triggered();

    void on_actionModOwner_triggered();

    void on_actionModNego_triggered();

    void on_actionBorNego_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<Owner> listaOw;
};

#endif  // MAINWINDOW_H
