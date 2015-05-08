#ifndef DIALOGPETICIONES_H
#define DIALOGPETICIONES_H

#include <QDialog>
#include <vector>
#include "./peticion.hpp"
#include "./owner.hpp"

namespace Ui {
class DialogPeticiones;
}

class DialogPeticiones : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPeticiones(QWidget *parent = 0);
    ~DialogPeticiones();
     void setOw(std::vector<Owner>& own);
     void setPe(std::vector<Peticion>& pet);
     void cargar();

private slots:
     void on_comboBox_currentIndexChanged(int index);

private:
    Ui::DialogPeticiones *ui;
    std::vector<Owner> *ow;
    std::vector<Peticion> *pe;

};

#endif // DIALOGPETICIONES_H
