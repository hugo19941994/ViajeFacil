#include "login.h"
#include "ui_login.h"
#include "bcrypt.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string.h>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_buttonBox_accepted()
{
    //Crear Salt aleatorio
    char salt[BCRYPT_HASHSIZE];
    char hash[BCRYPT_HASHSIZE];
    assert(bcrypt_gensalt(12, salt) == 0); //Asegurarnos de que se creo correctamente

    //Convertimos la contrasenia a un buffer de C
    std::string pass = this->ui->lineEdit->text().toStdString();
    const char * passC = pass.c_str();
    assert(bcrypt_hashpw(passC, salt, hash) == 0); //Asegurarnos de que se creo correctamente

    //Convertir el hash a un string de C++
    std::string cppHash(hash);
    std::ofstream myfile;
    myfile.open ("../../texto/example.txt", std::ios_base::app);
    myfile << this->ui->lineEdit_2->text().toStdString() << ":" << cppHash << "\n" ;
    myfile.close();

    //Para comprobar
    //char outhash[BCRYPT_HASHSIZE];
    //assert(bcrypt_hashpw("thepassword", "expectedhash", outhash) == 0);
    //if (strcmp("expectedhash", outhash) == 0) {
    //    printf("The password matches\n");
}
