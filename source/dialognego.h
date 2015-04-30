#ifndef DIALOGNEGO_H
#define DIALOGNEGO_H

#include <QDialog>
#include "nego.h"
#include "owner.h"


namespace Ui {
class DialogNego;
}

class DialogNego : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNego(QWidget *parent = 0);
    ~DialogNego();
    void setNe(std::vector<Nego>& neg);
    void setOw(std::vector<Owner>& own);


private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogNego *ui;
    std::vector<Owner> *ow;
    std::vector<Nego>* ne;
};

#endif // DIALOGNEGO_H
