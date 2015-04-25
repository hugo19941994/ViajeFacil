#include "diagowner.h"
#include "ui_diagowner.h"

diagOwner::diagOwner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::diagOwner)
{
    ui->setupUi(this);
}

diagOwner::~diagOwner()
{
    delete ui;
}
