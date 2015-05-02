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
    Owner *newO = new Owner;
    newO->setNombre(this->ui->lineEdit->text());
    this->ow->push_back(*newO);
}

void diagOwner::setOw(std::vector<Owner> &own) {
    this->ow = &own;
}
