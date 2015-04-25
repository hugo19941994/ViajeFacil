#ifndef DIAGOWNER_H
#define DIAGOWNER_H

#include <QDialog>

namespace Ui {
class diagOwner;
}

class diagOwner : public QDialog
{
    Q_OBJECT

public:
    explicit diagOwner(QWidget *parent = 0);
    ~diagOwner();

private:
    Ui::diagOwner *ui;
};

#endif // DIAGOWNER_H
