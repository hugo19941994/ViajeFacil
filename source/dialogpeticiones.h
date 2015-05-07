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



private:
    Ui::DialogPeticiones *ui;
    std::vector<Owner> *ow;

}

#endif // DIALOGPETICIONES_H
