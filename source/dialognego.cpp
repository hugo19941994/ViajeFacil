#include <vector>
#include "./ui_dialognego.h"
#include "./dialognego.hpp"

DialogNego::DialogNego(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNego) {
    ui->setupUi(this);
}

DialogNego::~DialogNego() {
    delete ui;
}

void DialogNego::on_buttonBox_accepted() {
    Nego *newN = new Nego;
    newN->setOrigen(this->ui->lineOrigen->text());
    this->ne->push_back(*newN);
}

void DialogNego::setNe(std::vector<Nego> &neg) {
    this->ne = &neg;
}

void DialogNego::setOw(std::vector<Owner> &own) {
    this->ow = &own;
}
