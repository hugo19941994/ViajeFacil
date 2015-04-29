#include "dialognego.h"
#include "ui_dialognego.h"

DialogNego::DialogNego(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNego)
{
    ui->setupUi(this);
}

DialogNego::~DialogNego()
{
    delete ui;
}


void DialogNego::on_buttonBox_accepted()
{
    Nego *newN = new Nego;
    newN->setNombre(this->ui->lineEdit->text());
    this->ne->push_back(*newN);
}

void DialogNego::setNe(std::vector<Nego> &neg)
{
    this->ne = &neg
}
