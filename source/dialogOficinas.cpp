#include "./ui_dialogOficinas.h"
#include "./pel_vector.hpp"
#include "./dialogOficinas.hpp"


dialogOficinas::dialogOficinas(QWidget *parent) :
    QDialog(parent), ui(new Ui::dialogOficinas) {
    ui->setupUi(this);
}

dialogOficinas::~dialogOficinas() {
    delete ui;
}

void dialogOficinas::setOw(pel::vector<Owner> *own) {
    ow = own;
}

void dialogOficinas::setOf(pel::vector<Oficina> *ofc) {
    of = ofc;
}

void dialogOficinas::setPe(pel::vector<Peticion> *pet) {
    pe = pet;
}

void dialogOficinas::cargar() {
   for(auto &it : *ow)
       ui->comboBox->addItem(it.getNombre().c_str());
}

void dialogOficinas::setOficinaAEditar(Oficina &ofi) {
    editando = true;
    oficinaAEditar = &ofi;

    ui->lineNombre->setText(ofi.getNombre().c_str());
    ui->linePais->setText(ofi.getPais().c_str());
    ui->lineCont->setText(ofi.getContinente().c_str());

    // ui->comboBox->setItemText(ow->at(modRowOwner).getNombre().c_str());
    ui->comboBox->setEnabled(false);
}

void dialogOficinas::on_comboBox_currentIndexChanged(int index) {
    setOf(&ow->at(index).getOficinas());
}

void dialogOficinas::on_buttonBox_accepted() {
    if (editando) {
        oficinaAEditar->setNombre(ui->lineNombre->text().toStdString());
        oficinaAEditar->setPais(ui->linePais->text().toStdString());
        oficinaAEditar->setContinente(ui->lineCont->text().toStdString());
    } else {
        Oficina *newOf = new Oficina;
        newOf->setNombre(ui->lineNombre->text().toStdString());
        newOf->setPais(ui->linePais->text().toStdString());
        newOf->setContinente(ui->lineCont->text().toStdString());
        of->push_back(*newOf);
    }
}
