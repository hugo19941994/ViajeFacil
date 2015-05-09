#include <vector>
#include "./diagowner.hpp"
#include "./ui_diagowner.h"

diagOwner::diagOwner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::diagOwner) {
    ui->setupUi(this);
}

diagOwner::~diagOwner() {
    delete ui;
}

void diagOwner::on_buttonBox_accepted() {
    if(this->mod == true){
        this->ow->at(modRow).setNombre(this->ui->lineEdit->text().toStdString());
    }
    else{
        Owner *newO = new Owner;  // Va bien declararlo sin new? en el stack?
        newO->setNombre(this->ui->lineEdit->text().toStdString());
        this->ow->push_back(*newO);
    }
}

void diagOwner::setOw(std::vector<Owner> &own) {
    this->ow = &own;
}

void diagOwner::setRow(int index)
{
    this->modRow = index;
}

void diagOwner::setMod()
{
    this->mod = true;
    this->ui->lineEdit->setText(this->ow->at(modRow).getNombre().c_str());
}
