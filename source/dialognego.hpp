#ifndef DIALOGNEGO_H
#define DIALOGNEGO_H

#include <QDialog>
#include <vector>
#include "./nego.hpp"
#include "./owner.hpp"


namespace Ui {
class DialogNego;
}

class DialogNego : public QDialog {
    Q_OBJECT

 public:
    explicit DialogNego(QWidget *parent = 0);
    ~DialogNego();
    void setNe(std::vector<Nego>& neg);
    void setOw(std::vector<Owner>& own);
    void cargar();
    void setRows(int modRowOwner, int modRowNego);
    void setMod();

 private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_buttonOkCancel_accepted();

 private:
    int modRowOwner;
    int modRowNego;
    bool mod = false;
    Ui::DialogNego *ui;
    std::vector<Owner> *ow;
    std::vector<Nego> *ne;
};

#endif  // DIALOGNEGO_H
