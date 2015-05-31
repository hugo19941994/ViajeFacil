/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *
 *  El usuario deberá registrarse primero que nada, para poder acceder a la
 *  aplicacion. Deberá introducir un ID (nombre de usuario) y un PWD
 * (contraseña), señalizar si es administrador o no.
 */

#ifndef dialogLogin_H
#define dialogLogin_H

#include <QDialog>
#include <string>

namespace Ui {
class dialogLogin;
}

/**
 * @brief Dialogo de Usuarios
 */
class dialogLogin : public QDialog {
    Q_OBJECT

 public:
    explicit dialogLogin(QWidget *parent = 0);

    /**
     * @brief setEstado
     * @param estado
     * Decide si la ventana se usará para crear
     * un usuario o para hacer login
     */
    void setEstado(int estado);

    ~dialogLogin();

 private slots:  // NOLINT - https://github.com/google/styleguide/issues/30
    void on_buttonBox_accepted();

 private:
    Ui::dialogLogin *ui;

    /**
     * @brief estado_
     * 0 para dialogLogin, 1 para crear usuario
     */
    int estado_;

 signals:
    /**
     * @brief cambioDeUsuario
     * Emite una señal con el nombre del usuario que acaba de
     * hacer login para mostrarse en el mainWindow
     */
    void cambioDeUsuario(std::string);  // Funcion para cambiar usuario
};

#endif  // dialogLogin_H
