#ifndef DIALOGOFICINAS_H
#define DIALOGOFICINAS_H


#include <QDialog>
#include <vector>
#include "pel_vector.hpp"
#include "./owner.hpp"
#include "./oficina.hpp"
#include "./nego.hpp"
#include "./peticion.hpp"


namespace Ui {
class DialogOficinas;
}

class DialogOficinas : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOficinas(QWidget *parent = 0);
    ~DialogOficinas();
    void setOf(pel::vector<Oficina>& ofc);
    void setOw(pel::vector<Owner>& own);
    void setPe(pel::vector<Peticion>& pet);
    void setRows(int modRowOwner, int modRowOficina);
    void cargar();

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_buttonBox_accepted();

private:
    int modRowOwner = -1;
    int modRowOficina = -1;
    Ui::DialogOficinas *ui;
    pel::vector<Owner> *ow;
    pel::vector<Oficina> *of;
    pel::vector<Peticion> *pe;
};

#endif // DIALOGOFICINAS_H
