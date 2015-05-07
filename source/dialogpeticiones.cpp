#include "dialogpeticiones.hpp"
#include "ui_dialogpeticiones.h"

DialogPeticiones::DialogPeticiones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPeticiones)
{
    ui->setupUi(this);
}

DialogPeticiones::~DialogPeticiones()
{
    delete ui;
}
