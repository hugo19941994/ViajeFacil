#include <vector>
#include "./dialogoficina.h"
#include "./ui_dialogoficina.h"

DialogOficina::DialogOficina(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOficina) {
    ui->setupUi(this);
}

DialogOficina::~DialogOficina() {
    delete ui;
}

void DialogOficina::on_buttonBox_accepted() {
    Oficina newO;
    newO.setNombre(this->ui->lineNombre->text());
    newO.setPais(this->ui->linePais->text());
    newO.setContinente(this->ui->lineContinente->text());
    this->of->push_back(newO);
}

void DialogOficina::cargar(){
    for (std::vector<Owner>::iterator it = this->ow->begin(); it !=this->ow->end(); ++it)
        this->ui->comboBox->addItem(it->getNombre());
}

void DialogOficina::setOf(std::vector<Oficina>& ofi) {
    this->of = &ofi;
}

void DialogOficina::setOw(std::vector<Owner> &own) {
    this->ow = &own;
}

void DialogOficina::on_comboBox_currentIndexChanged(int index)
{
    Owner *ow = &this->ow->at(index);
    this->setOf(ow->getOficinas());
}
