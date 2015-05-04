#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog {
    Q_OBJECT

 public:
    explicit Login(QWidget *parent = 0);
    void setEstado(int estado);
    ~Login();

 private slots:
    void on_buttonBox_accepted();

 private:
    Ui::Login *ui;
    int estado_;  // 0 para login, 1 para crear usuario

 signals:
    void cambioDeUsuario(std::string);
};

#endif  // LOGIN_H
