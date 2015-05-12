/*DESCRIPCION: El usuario deberá registrarse primero que nada, para poder acceder a la aplicacion.
 * Deberá introducir un ID(nombre de usuario) y un PWD(contraseña), señalizar si es administrador o no.
 * AUTORES: Guillermo Gonzalez
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

/**
 * @brief The Login class
 */
class Login : public QDialog {
    Q_OBJECT

 public:
    /**
     * @brief Login
     * @param parent
     */
    explicit Login(QWidget *parent = 0);
    /**
     * @brief setEstado
     * @param estado
     */
    void setEstado(int estado);
    ~Login();

 private slots: //Slot: hacer click en aceptar
    /**
     * @brief on_buttonBox_accepted
     */
    void on_buttonBox_accepted();

 private: //Se muestra en la ventana gráfica
    /**
     * @brief ui
     */
    Ui::Login *ui;
    /**
     * @brief estado_
     */
    int estado_;  // 0 para login, 1 para crear usuario

 signals: //Se permite cambiar de usuario, varios usuarios pueden acceder, no necesariamente tiene que ser siempre el mismo.
    /**
     * @brief cambioDeUsuario
     */
    void cambioDeUsuario(std::string); //funcion para cambiar usuario
};

#endif  // LOGIN_H
