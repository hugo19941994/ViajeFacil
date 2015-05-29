//AUTORES: Guillermo Gonzalez


#include <assert.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include "./login.hpp"
#include "./ui_login.h"
#include "./bcrypt.h"
#include "./mainwindow.hpp"


/**
 * @brief Login::Login
 * @param parent
 */
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login) {
      ui->setupUi(this);
}

/**
 * @brief Login::~Login
 */
Login::~Login() {
    delete ui;
}

/**
 * @brief Login::setEstado
 * @param estado
 */
void Login::setEstado(int estado) {
    this->estado_ = estado;
    if (this->estado_ == 0)  // Si vamos a hacer login escondemos el boton "admin"
    this->ui->checkBox->hide();
}

/**
 * @brief Login::on_buttonBox_accepted
 */
void Login::on_buttonBox_accepted() {
    if (this->estado_ == 1) {  // estado_ 1 para crear usuario
        // Crear Salt aleatorio
        char salt[BCRYPT_HASHSIZE];
        char hash[BCRYPT_HASHSIZE];
        assert(bcrypt_gensalt(12, salt) == 0);  // Asegurarnos de que se creo correctamente

        // Convertimos la contrasenia a un buffer de C
        std::string pass = this->ui->lineEdit->text().toStdString();
        const char * passC = pass.c_str();
        assert(bcrypt_hashpw(passC, salt, hash) == 0);  // Asegurarnos de que se creo correctamente

        // Convertir el hash a un string de C++
        std::string cppHash(hash);
        std::ofstream myfile;
        myfile.open("../../data/usuarios.txt", std::ios_base::app);
        myfile << this->ui->lineEdit_2->text().toStdString() << "\n" << cppHash << "\n";
        myfile.close();
    }
    else if (this->estado_ == 0) {
         // estado_ 0 para comprobar el login
         char outhash[BCRYPT_HASHSIZE];

        // Coger el usuario y pasarlo a char * de C
        std::string usuario = this->ui->lineEdit_2->text().toStdString();

        // Coger la contraseña y pasarla a char * de C
        std::string pass = this->ui->lineEdit->text().toStdString();
        const char * passC = pass.c_str();

        // Abrimos el archivo en modo lectura
        std::ifstream myfile;
        myfile.open("../../data/usuarios.txt");

        // Cogemos el hash que corresponda
        std::string myString;
        while (std::getline(myfile, myString, '\n')) {
          if (myString == usuario) {
              std::getline(myfile, myString, '\n');
              break;
          }
         else
             std::getline(myfile, myString, '\n');
        }

        const char * myStringC = myString.c_str();

        assert(bcrypt_hashpw(passC, myStringC, outhash) == 0);
        if (strcmp(myStringC, outhash) == 0) {  // Poner en mainWindow el usuario
            printf("The password matches\n");
            emit cambioDeUsuario(usuario);
        }
    }
}
