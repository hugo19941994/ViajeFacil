#ifndef DIAGOWNER_H
#define DIAGOWNER_H

#include <QDialog>
#include <vector>
#include "owner.hpp"

namespace Ui {
class diagOwner;
}

class diagOwner : public QDialog {
    Q_OBJECT

 public:
    explicit diagOwner(QWidget *parent = 0);
    ~diagOwner();
    void setOw(std::vector<Owner>& own);
    void setRow(int index);
    void setMod();

 private slots:
    void on_buttonBox_accepted();

 private:
    int modRow;
    bool mod = false;
    Ui::diagOwner *ui;
    std::vector<Owner>* ow;
};

#endif  // DIAGOWNER_H
