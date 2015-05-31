/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 */

#ifndef DIALOGINFORME_H
#define DIALOGINFORME_H

#include <QDialog>
#include <string>
#include "./pelVector.hpp"
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

    void cargar(pel::Vector<Owner>* own);
    void cargarH(pel::Vector<entradaHistorial>* his);
    void quickSort(rank arr[], int left, int right);
    std::string crearString(entradaHistorial h);

 private slots:  // NOLINT - https://github.com/google/styleguide/issues/30
    void on_radioButton_5_clicked();

    void on_radioButton_clicked();

 private:
    Ui::dialogInforme *ui;
    pel::Vector<Owner> *ow;
    pel::Vector<entradaHistorial> *hi;
};

#endif  // DIALOGINFORME_H
