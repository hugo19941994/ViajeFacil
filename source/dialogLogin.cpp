/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 */

#include <QMessageBox>
#include <assert.h>
#include <fstream>
#include <string>
#include "./ui_dialogLogin.h"
#include "./bcrypt.h"
#include "./dialogLogin.hpp"

/**
 * @brief Dialogo de Login
 * Crea y loguea a usuarios
 */
dialogLogin::dialogLogin(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogLogin) {
      ui->setupUi(this);
      ui->checkBox->hide();  // Funcionalidad de administrador no finalizada
}

dialogLogin::~dialogLogin() {
    delete ui;
}

void dialogLogin::setEstado(int estado) {
    estado_ = estado;
    // Si vamos a hacer dialogLogin escondemos el boton "admin"
    if (estado_ == 0)
        ui->checkBox->hide();
}

void dialogLogin::on_buttonBox_accepted() {
    if (estado_ == 1) {  // estado_ 1 para crear usuario
        // Crear Salt aleatorio
        char salt[BCRYPT_HASHSIZE];
        char hash[BCRYPT_HASHSIZE];
        // Asegurarnos de que se creo correctamente
        assert(bcrypt_gensalt(12, salt) == 0);

        // Convertimos la contrasenia a un buffer de C
        std::string pass = ui->lineEdit->text().toStdString();
        const char * passC = pass.c_str();
        // Asegurarnos de que se creo correctamente
        assert(bcrypt_hashpw(passC, salt, hash) == 0);

        // Convertir el hash a un string de C++
        std::string cppHash(hash);
        std::ofstream myfile;
        myfile.open("../../data/usuarios.txt", std::ios_base::app);
        myfile << ui->lineEdit_2->text().toStdString() << "\n" <<
                  cppHash << "\n" <<
                  (ui->checkBox->isChecked() ? "1" : "0") << '\n';
        myfile.close();

    } else if (estado_ == 0) {
         // estado_ 0 para comprobar el dialogLogin
         char outhash[BCRYPT_HASHSIZE];

        // Coger el usuario y pasarlo a char * de C
        std::string usuario = ui->lineEdit_2->text().toStdString();
        if(usuario == ""){
                QMessageBox::warning(this, "Warning",
                                     "Obligatorio nombre");
                return;
            }

        // Coger la contraseña y pasarla a char * de C
        std::string pass = ui->lineEdit->text().toStdString();
        if(pass == ""){
            QMessageBox::warning(this, "Warning",
                                 "Olvidó la contraseña");
            return;
        }
        const char * passC = pass.c_str();

        // Abrimos el archivo en modo lectura
        std::ifstream myfile;
        myfile.open("../../data/usuarios.txt");

        // Cogemos el hash que corresponda
        std::string myString;
        std::string admin;
        while (std::getline(myfile, myString, '\n')) {
            if (myString == usuario) {
                std::getline(myfile, myString, '\n');
                std::getline(myfile, admin, '\n');
                break;
            } else {
                std::getline(myfile, myString, '\n');
                std::getline(myfile, myString, '\n');
            }
        }

        const char * myStringC = myString.c_str();

        // assert(bcrypt_hashpw(passC, myStringC, outhash) == 0);
        bcrypt_hashpw(passC, myStringC, outhash);
        // Poner en mainWindow el usuario
        if (strcmp(myStringC, outhash) == 0) {
            emit cambioDeUsuario(usuario);
        } else {
            QMessageBox::warning(this, "Warning",
                                 "Usuario no encontrado");
        }
    }
}
