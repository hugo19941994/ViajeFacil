#include "login.h"
#include "ui_login.h"
#include <iostream>
#include <fstream>

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
    std::ofstream myfile;
    myfile.open ("../../texto/example.txt", std::ios_base::app);
    myfile << this->ui->lineEdit_2->text().toStdString() << ":" << this->ui->lineEdit->text().toStdString() << "\n" ;
    myfile.close();
}
