/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 */

#ifndef DIALOGINFORME_H
#define DIALOGINFORME_H

#include <QDialog>
#include <string>
#include "./pel_vector.hpp"
#include "./owner.hpp"
#include "./entradaHistorial.hpp"

namespace Ui {
class dialogInforme;
}

struct rank {
    std::string name = "";
    int num = 0;
};

class dialogInforme : public QDialog {
    Q_OBJECT

 public:
    explicit dialogInforme(QWidget *parent = 0);
    ~dialogInforme();

    void cargar(pel::vector<Owner>* own);
    void cargarH(pel::vector<entradaHistorial>* his);
    void quickSort(rank arr[], int left, int right);
    std::string crearString(entradaHistorial h);

 private slots:
    void on_radioButton_5_clicked();

    void on_radioButton_clicked();

 private:
    Ui::dialogInforme *ui;
    pel::vector<Owner> *ow;
    pel::vector<entradaHistorial> *hi;
};

#endif // DIALOGINFORME_H
