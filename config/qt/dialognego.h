#ifndef DIALOGNEGO_H
#define DIALOGNEGO_H

#include <QDialog>

namespace Ui {
class DialogNego;
}

class DialogNego : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNego(QWidget *parent = 0);
    ~DialogNego();

private:
    Ui::DialogNego *ui;
};

#endif // DIALOGNEGO_H
