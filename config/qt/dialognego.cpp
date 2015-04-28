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
