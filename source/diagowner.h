#ifndef DIAGOWNER_H
#define DIAGOWNER_H

#include <QDialog>
#include "owner.h"

namespace Ui {
class diagOwner;
}

class diagOwner : public QDialog
{
    Q_OBJECT

public:
    explicit diagOwner(QWidget *parent = 0);
    ~diagOwner();
    void setOw(std::vector<Owner>& own);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::diagOwner *ui;
    std::vector<Owner>* ow;
};

#endif // DIAGOWNER_H
