#ifndef dialogOficinas_H
#define dialogOficinas_H


#include <QDialog>
#include "./pel_vector.hpp"
#include "./owner.hpp"
#include "./oficina.hpp"
#include "./nego.hpp"
#include "./peticion.hpp"


namespace Ui {
class dialogOficinas;
}

class dialogOficinas : public QDialog {
    Q_OBJECT

 public:
    explicit dialogOficinas(QWidget *parent = 0);
    ~dialogOficinas();
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
    Ui::dialogOficinas *ui;
    pel::vector<Owner> *ow;
    pel::vector<Oficina> *of;
    pel::vector<Peticion> *pe;
};

#endif // dialogOficinas_H
