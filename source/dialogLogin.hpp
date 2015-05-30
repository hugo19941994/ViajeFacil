/*DESCRIPCION: El usuario deberá registrarse primero que nada, para poder acceder a la aplicacion.
 * Deberá introducir un ID(nombre de usuario) y un PWD(contraseña), señalizar si es administrador o no.
 * AUTORES: Guillermo Gonzalez
 */

#ifndef dialogLogin_H
#define dialogLogin_H

#include <QDialog>
#include <string>

namespace Ui {
    class dialogLogin;
}

/**
 * @brief The dialogLogin class
 */
class dialogLogin : public QDialog {
    Q_OBJECT

 public:
    /**
     * @brief dialogLogin
     * @param parent
     */
    explicit dialogLogin(QWidget *parent = 0);

    /**
     * @brief setEstado
     * @param estado
     */
    void setEstado(int estado);

    ~dialogLogin();

 private slots:  // Slot: hacer click en aceptar
    /**
     * @brief on_buttonBox_accepted
     */
    void on_buttonBox_accepted();

 private:  // Se muestra en la ventana gráfica
    /**
     * @brief ui
     */
    Ui::dialogLogin *ui;

    /**
     * @brief estado_
     * 0 para dialogLogin, 1 para crear usuario
     */
    int estado_;

 signals:  // Se permite cambiar de usuario, varios usuarios pueden acceder, no necesariamente tiene que ser siempre el mismo.
    /**
     * @brief cambioDeUsuario
     */
    void cambioDeUsuario(std::string);  // Funcion para cambiar usuario
};

#endif  // dialogLogin_H
