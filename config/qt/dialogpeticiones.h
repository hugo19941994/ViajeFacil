#ifndef DIALOGPETICIONES_H
#define DIALOGPETICIONES_H

#include <QDialog>

namespace Ui {
class DialogPeticiones;
}

class DialogPeticiones : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPeticiones(QWidget *parent = 0);
    ~DialogPeticiones();

private:
    Ui::DialogPeticiones *ui;
};

#endif // DIALOGPETICIONES_H
